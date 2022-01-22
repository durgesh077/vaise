class Treap{
typedef struct node{
    int prior,size,val,sum,lazy;
    //value in array,info of segtree,lazy update
    struct node *l,*r;
}node;typedef node* pnode;
pnode root;
mt19937 Rand;

public:
 
Treap():root(nullptr),Rand(time(0)){
}
Treap(vector<int>v):root(nullptr),Rand(time(0)){
    for(int i=0;i<v.size();i++)
        insert(v[i],i);
}

int sz(pnode t){
    return t?t->size:0;
}
size_t size(){
    return root->size;
}
void upd_sz(pnode t){
    if(t)t->size=sz(t->l)+1+sz(t->r);
}

void lazy(pnode t){
    if(!t || !t->lazy)return;
    t->val+=t->lazy;//operation of lazy
    t->sum+=t->lazy*sz(t);
    if(t->l)t->l->lazy+=t->lazy;//propagate lazy
    if(t->r)t->r->lazy+=t->lazy;
    t->lazy=0;
}

void reset(pnode t){
    if(t)t->sum = t->val;//lazy already propagated
}

void combine(pnode& t,pnode l,pnode r){//combine segtree ranges
    if(!l || !r)return void(t = l?l:r);
    t->sum = l->sum + r->sum;
}
void operation(pnode t){//operation of segtree
    if(!t)return;
    reset(t);//node represents single element of array
    lazy(t->l);lazy(t->r);//imp:propagate lazy before combining l,r
    combine(t,t->l,t);combine(t,t,t->r);
}
void split(pnode t,pnode &l,pnode &r,int pos,int add=0){
    if(!t)return void(l=r=NULL);
    lazy(t);int curr_pos = add + sz(t->l);
    if(curr_pos<=pos)//element at pos goes to "l"
        split(t->r,t->r,r,pos,curr_pos+1),l=t;
    else    split(t->l,l,t->l,pos,add),r=t;
    upd_sz(t);operation(t);
}

void merge(pnode &t,pnode l,pnode r){//result/left/right array
    lazy(l);lazy(r);
    if(!l || !r) t = l?l:r;
    else if(l->prior>r->prior)merge(l->r,l->r,r),t=l;
    else    merge(r->l,l,r->l),t=r;
    upd_sz(t);operation(t);
}

int prod(int l,int r){//[l,r]
    pnode L,mid,R;
    split(root,L,mid,l-1);split(mid,root,R,r-l);//note: r-l!!
    int ans = root->sum;
    merge(mid,L,root);merge(root,mid,R);
    return ans;
}
void range_update(int l,int r,int val){//[l,r]
    pnode t=root;
    pnode L,mid,R;
    split(t,L,mid,l-1);split(mid,t,R,r-l);//note: r-l!!
    t->lazy+=val; //lazy_update
    merge(mid,L,t);merge(t,mid,R);
}

pnode init(int val){
    auto nnode=new node;
    nnode->val=val;
    nnode->prior=Rand();
    nnode->size=0;
    nnode->sum=nnode->lazy=0;
    nnode->l=nnode->r=nullptr;
    return nnode;
}

void output (pnode t,vector<int>&v) {
    if (!t)  return;
    operation(t);
    output (t->l,v);
    v.push_back(t->val);
    output (t->r,v);
}
vector<int> output(){
    vector<int>v;
    output(root,v);
    return v;
}

void insert(int val,int key){
    pnode l=nullptr,r=l;
    split(root,l,r,key-1);
    root=init(val);
    merge(root,l,root);
    merge(root,root,r);
}
int operator[](int key){
    return prod(key,key);
}
void erase(int key,int key2=-1){
    if(key2==-1)
        key2=key;
    pnode leftL,leftR,rightL,rightR;
    split(root,leftL,rightR,key2);
    split(leftL,leftL,leftR,key-1);
    merge(root,leftL,rightR);
}
};
