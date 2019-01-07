#include<iostream>
#include<malloc.h>
#include<math.h>
using namespace std;
struct VEB
{
int min;
int max;
int u;
struct VEB* summary;
struct VEB** cluster;
};
int cluster(int x,int u)
{
int y,k;
k=sqrt(u);
y=x/k;
return y;
}
int index(int x,int u)
{
int y,k;
k=sqrt(u);
y=x%k;
return y;
}
int key(int x,int y,int u)
{
int z;
z=x*sqrt(u)+y;
return z;
}
struct VEB* create_VEB(int u)
{
int i;
struct VEB* v;
if(u==2)
{
v=(struct VEB*)malloc(sizeof(struct VEB));
v->max='\0';
v->min='\0';
v->u=u;
return v;
}
else
{
v=(struct VEB*)malloc(sizeof(struct VEB));
v->max='\0';
v->min='\0';
v->u=u;
v->cluster=(struct VEB**)malloc(sqrt(u)*sizeof(struct VEB));
v->summary=create_VEB(sqrt(u));
for(i=0;i<=sqrt(u)-1;i++)
{
v->cluster[i]=create_VEB(sqrt(u));

}
return v;
}
}
struct VEB* empty_insert(struct VEB*v,int x)
{
v->min=x;
v->max=x;
return v;
}
struct VEB* insert_veb(struct VEB* v,int x)
{
if(v->min==NULL)
{
v->max=v->min=x;
return v;
}
else if(x<v->min)
{
int temp=x;
x=v->min;
v->min=temp;
}
if(v->u>2 )
{
if(v->cluster[cluster(x,v->u)]->min==NULL)
{
insert_veb(v->summary,cluster(x,v->u));
insert_veb(v->cluster[cluster(x,v->u)],index(x,v->u));
}
else
{
insert_veb(v->cluster[cluster(x,v->u)],index(x,v->u));
}
}
if(v->max<x)
{
v->max=x;
}

return v;
}
int successor(struct VEB* v,int x)
{
int i,j;
i=cluster(x,v->u);
if(v->u==2)
{
if(x==0 && v->max==1)
return 1;
else
return NULL;
}
else if (x<v->min)
{
return v->min;
}
if(index(x,v->u)< v->cluster[i]->max) // successor in same cluster
{
j=successor(v->cluster[i],index(x,v->u));
}
else // find the next set cluster
{
i=successor(v->summary,cluster(x,v->u));
if(i==NULL)
return NULL;
else
j=v->cluster[i]->min;
}
return key(i,j,v->u);

}
int member(struct VEB* v,int x)
{
/*if(v->min!='\0'&&(x==v->min||x==v->max))
cout<<"Is a member\n";
else if(v->u==2&&v->min=='\0'&&v->max=='\0')
cout<<"Is not a member\n";
else
{
return member(v->cluster[cluster(x,v->u)],index(x,v->u));
} */
if(x==v->min || x==v->max)
return 1;
else if (x<v->min || x>v->max)
return 0;
else
return (member(v->cluster[cluster(x,v->u)],index(x,v->u)));
}

int main()
{
int u,n,x,key,a,m,dd;
struct VEB* v,*k;
cout<<"Enter the universe size\n";
cin>>u;
v=create_VEB(u);
k=v;
cout<<"Enter the keyv of elements\n";
cin>>n;
m=n;
while(n)
{
cout<<"Enter the element\n";
cin>>x;
v=insert_veb(v,x);
n--;
}
/*cout<<"Enter the key\n";
cin>>key;
a=cluster(key,v->u);
if(v->cluster[a]->cluster[cluster(key,sqrt(v->u))]->min!='\0')
cout<<"true\n";
else
cout<<"false\n";
*/
//while(m)
/*cout<<"Enter the key\n";
cin>>key;
a=successor(v,key);
cout<<"The successor is "<<a<<endl; */
//
m=m+5;
cout<<"Enter the member key\n";
cin>>key;
a=member(v,key);
if(a==0)
cout<<"Not a member\n";
else
cout<<"Member\n";

}
