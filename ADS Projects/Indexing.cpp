#include<iostream>
#include<malloc.h>
#include <fstream>
#include<string.h>
#include<sstream>
using namespace std;

typedef struct btree
{
  int m;
  int * key;
  int* line;
  struct btree** child;
  int n;
  struct btree* parent;
  int leaf;
}btree;


btree* insert(btree*,int,btree*,int);
btree* split(btree*,int,int,btree*,btree*,int);
void initialise(btree*);
int search(btree*,int);


int main()
{
  btree* head=NULL;

  int key;
  int line=1,co=1;
  string line1;


//File Handling
  int offset=0;
  ifstream myfile ("example1.txt");
  ifstream my("example1.txt");
  while(!myfile.eof()) //Temporarily trying with 10 records from file
  {
  	int i=0;
 	int k=0;
  	if (myfile.is_open())
  	{
    	while ( i!=3 ) //To fetch GR Number as it is the 3rd field in file
    	{
    	  getline (myfile,line1,',');
    	  k+=line1.length()+1;
    	  i++;
    	}
    	stringstream geek(line1);  //Convert String to long

    	geek>>key;
    	head=insert(head,offset,NULL,key);
    	//inorder(head,0);
    	for(int i=0;i<2;i++)
    	{
      		getline (myfile,line1,',');
      		k+=line1.length()+1;
    	}
    	getline (myfile,line1);
    	k+=line1.length()+1;
  	}
  	offset+=k;
  
  }
  int c=0;
  int grno;
  while(c==0)
  {
    
  	cout<<"\nenter gr no of canditate\n";
    cin>>grno;
    if(grno==-1)
    	c=1;
    else
    {
  		int t=search(head,grno);
  		my.seekg(t,ios::cur);
  		getline(my,line1);
        int k=line1.length();
        my.seekg(-(t+k+1),ios::cur);
  		cout<<"\ndetails are\n"<<line1<<"\n";//getline(my,line1);cout<<"\ndetails are\n"<<line1;
    }
  }



  myfile.close();

  return 0;
}


btree* insert(btree* head,int l,btree* p,int  key)
{
  if(head==NULL)
  {
    head=new btree;
    initialise(head);
    head->leaf=1;
    head->key[0]=key;
    head->line[0]=l;
    (head->n)++;
    return head;
  }
  else
  {

     p=head;

    while(p!=NULL && p->leaf!=1) // find the node where key is to be inserted
    {
      int i;
      for( i=0;i<p->n;i++)
      {
        if(key<=p->key[i])
          break;
      }
        if(p->leaf==0)
          p=p->child[i];
        else
          break;

    }

    if(p->n==p->m-1)  // node is full
    {

      head=split(p,key,l,NULL,head,0); // sibling node
    }
    else // not full
    {

      int i;
      for(i=0;i<p->n;i++)
      {
        if(key<p->key[i])
          break;
      }
      if(i!=p->n) //shift the keys
      {
        for(int j=p->n-1;j>=i;j--)
        {
           p->key[j+1]=p->key[j];
           p->line[j+1]=p->line[j];
        }
      }
      p->key[i]=key;
      p->line[i]=l;
      p->n++;
    }
    return head;
  }
}

btree* split(btree* p,int key,int line,btree* q,btree* head,int child)
//btree* split(btree* p,int child,btree* q,btree* head,long  key)
{
  int temp[p->m];  // for finding median
  int temp1[p->m];
  int i=0;
  
  btree* s=NULL;



  if(p->n!=p->m-1) // if node is not full
  {


    for(i=0;i<p->n;i++)
    {
      if(key<p->key[i])
        break;
    }

      if(i!=p->n) //shift the keys
      {
        for(int j=p->n-1;j>=i;j--)
        {
           p->key[j+1]=p->key[j];
           p->line[j+1]=p->line[j];
        }
        for(int j=p->n;j>=i+1;j--)
        {
          p->child[j+1]=p->child[j];
        }
      }
      p->key[i]=key;
      p->line[i]=line;
      p->child[i+1]=q;
      p->child[i+1]->parent=p;
      p->n++;

  }
  else  // if the node is full
  {

    if(p->parent==NULL ) // if p is root
    {
      s=new btree;  //cout<<"hi new root";
      initialise(s);
      head=s; //update the head
      s->n++;
      p->parent=s;
      s->leaf=0;
      s->child[0]=p; // make first child of s as p
    }



    while(p->key[i]<key && i<p->m-1)
    {
      temp[i]=p->key[i];
      temp1[i]=p->line[i];
      i++;
    }

    temp[i]=key;
    temp1[i]=line;

    while(i<=p->m-1)
    {
      temp[i+1]=p->key[i];
      temp1[i+1]=p->line[i];
      i++;
    }

    long  median=temp[p->m/2];
    int median1=temp1[p->m/2];
    for(int i=0;i<(p->m/2);i++)
    {
      p->key[i]=temp[i];
      p->line[i]=temp1[i];
    }
    p->n=p->m/2;  //update n



    btree* z=new btree;
    initialise(z);
    z->parent=s;
    if(p->leaf==0)
      z->leaf=0;
    else
      z->leaf=1;

    for(int i=p->m/2+1;i<p->m;i++)
    {
      z->key[i-(p->m/2 + 1)]=temp[i];
      z->line[i-(p->m/2+1)]=temp1[i];
    }
    z->n=p->m/2; //update sibling node's n


   if(s!=NULL )
   {

      s->key[0]=median;// put median in new root node
      s->line[0]=median1;
      s->child[1]=z;

   }
   else
   {

     int i;
     for(i=0;i<p->parent->n;i++)
     {
       if(p==p->parent->child[i])
         break;
     }

      head=split(p->parent,median,median1,z,head,i+1);
   }


    if(q!=NULL)
    {

      if(child<=p->m/2)
      {
         for(int i=p->m/2;i<p->m;i++)
         {
           z->child[i-p->m/2]=p->child[i];
           z->child[i-p->m/2]->parent=z;
         }
         for(int i=child;i<p->m/2;i++)
         {
           p->child[i+1]=p->child[i];
         }
         p->child[child]=q;
         q->parent=p;
      }
      else
      {
        for(int i=p->m/2+1;i<child;i++)
        {
          z->child[i-p->m/2-1]=p->child[i];
          z->child[i-p->m/2-1]->parent=z;
         }
         z->child[child-p->m/2-1]=q;
         q->parent=z;
         for(int i=child;i<p->m;i++)
         {
           z->child[i-p->m/2]=p->child[i];
           z->child[i-p->m/2]->parent=z;
         }
      }
    }

  }
  return head;
}


int search(btree* t,int  key)
{
  int present=0;

  for(int i=0;i<t->n;i++)
  {
    if(t->key[i]==key)
    {
      present=1;
      return t->line[i];
      break;
    }
    else if(t->key[i]>key && t->leaf!=1)
    {
      present=search(t->child[i],key);
      break;
    }
    else if(t->n-1==i && t->leaf!=1)
    {
      present=search(t->child[i+1],key);
    }
    else if(t->leaf==1 && i==t->n-1)
      present=0;
  }
  return present;
}

void initialise(btree* head)
{
  head->m=15;
  head->parent=NULL;
  head->key=new int[head->m-1];
  head->line=new int[head->m-1];
  head->child=(btree**)malloc(head->m*sizeof(btree*));
  head->leaf=1;
  head->n=0;
  for(int i=0;i<head->m;i++)
  {
    head->child[i]=NULL;
    if(i<head->m-1)
    {
      head->key[i]=0;
      head->line[i]=0;
    }
  }
}
