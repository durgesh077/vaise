#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
vector<int>varr[10];
int n,m;
int mn=0;
int paSum[12];
struct trie
{
   map<int,trie*>next;
}*root;
trie* NN(){
   return new trie;
}
void add(trie*src,int pos,vector<int>&v){
   if(pos==v.size())
      return;
   
   if(src->next.count(v[pos]))
      add(src->next[v[pos]],pos+1,v);
   else 
      add(src->next[v[pos]]=NN(),pos+1,v);
}
int ttrec=0;
void getAns(int lev,int csum,trie*pntr){
   if(lev==n)
      return ;
   for(int i=varr[lev].size()-1;i>=0  and ttrec++<m+5;i--)
   {
      if(pntr->next.count(i)==0){
         mn=max(mn,csum+varr[lev][i]+paSum[lev+1]);
         return;
      }
      else{
         getAns(lev+1,csum+varr[lev][i],pntr->next[i]);
      }
   }
}
int main()
{
   ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
   #ifndef ONLINE_JUDGE
       freopen("C:\\Programs\\in.txt","r",stdin);
       //freopen("C:\\Programs\\out.txt","w",stdout);
       #endif
   cin>>n;
   root=NN();
   for(int i=0;i<n;i++)
   {
      int sz;
      cin>>sz;
      varr[i].resize(sz);
      for(int &b:varr[i])cin>>b;
   }
cin>>m;
   for(int i=0;i<m;i++)
   {
      vector<int>tmp(n);
      for(int &b:tmp)cin>>b,b--;
         add(root,0,tmp);
   }
   for(int i=n;i--;)
      paSum[i]=paSum[i+1]+varr[i].back();
   getAns(0,0,root);
   cout<<mn<<endl;
}