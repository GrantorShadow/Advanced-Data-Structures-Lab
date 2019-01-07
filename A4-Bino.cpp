#include<iostream>
#include<malloc.h>
using namespace std;

/// Structure of binomial heap
struct bino
{
        struct bino *parent;
        int key;
        int deg;
        struct bino *child;
        struct bino *sibling;
}*head;

/// crearion of the new node 
struct bino *create(int k)
{
  struct bino *t;
        t=(struct bino*)malloc(sizeof(struct bino));
        t->key=k;
        t->parent=NULL;
        t->sibling=NULL;
        t->child=NULL;
        t->deg=0;
        head=t;
        return head;
}

/// fuction to print the binomial heap
void print(struct bino *r)
{
  while(r!=NULL)
  {
    cout<<r->key<<"  ";
    if(r->child!=NULL)
    {
     print(r->child);
    }
    r=r->sibling;
  }
 
}

/// function to link the node of same order 
void link(struct bino *a,struct bino *b)
{
        // a goes left
  a->sibling=b->child;
        b->child=a;
  a->parent=b;
        b->deg++;
        
}

///merge function 
struct bino *merge(struct bino *h1,struct bino *h2)
{
        struct bino *p,*q;
  struct bino *head=NULL;
  struct bino *r;
        p=h1;
        q=h2;
  if(p!=NULL && q!=NULL)
  {
  if(p->deg <= q->deg)   
  {
    r=head=p;
    p=p->sibling;
  }
  else
  {
                r=head=q;
    q=q->sibling;
  }  
  }
  else
  { if(p==NULL) 
    {
         r=head=q; 
        // q=q->sibling;
         return q;
         //cout<<"p==NULL"<<endl;
    }
       else
    {
         r=head=p;
         //cout<<"q==NULL "<<endl;
        // p=p->sibling;
         return p;
    }
  }
  while(p!=NULL && q!=NULL)   
  {
    if(p->deg<q->deg)
    {
      r->sibling=p;
      r=r->sibling;
                        p=p->sibling;
    }
    else
    {
      r->sibling=q;
      r=r->sibling;
                        q=q->sibling;
    }
   }
   while(p!=NULL)
   {
                        r->sibling=p;
      r=r->sibling;
                        p=p->sibling;
   }
   while(q!=NULL)
   {
                        r->sibling=q;
      r=r->sibling;
                        q=q->sibling;
   }
 
  return head;
}

struct bino *uni (struct bino *h1,struct bino *h2)
{
  struct bino *h;
        struct bino *x,*prev_x,*nxt_x;
  struct bino *temp=NULL;

  h=merge(h1,h2);
  if(h==NULL)
                return h;
  prev_x=NULL;
        x=h;
        nxt_x=x->sibling;
  
        while(nxt_x!=NULL)
  {

        if(x->deg!=nxt_x->deg || nxt_x->sibling!=NULL && x->deg==nxt_x->sibling->deg)
        {
                        prev_x=x;
                        x=nxt_x;
                        nxt_x=nxt_x->sibling;
                }
                else if(x->key < nxt_x->key)
                     {
           if(nxt_x->sibling!=NULL)
                                           x->sibling=nxt_x->sibling;
                                         else
                                         x->sibling=NULL;
           if(nxt_x->sibling!=NULL)
             temp=nxt_x->sibling;
 
                             link(nxt_x,x);                // First goes left side
                 nxt_x=temp; 
                                 }
                                 else if(prev_x==NULL)
                                                        {
                                                                h=nxt_x;              // if nxt_x is smaller that x then change its head to nxt_x 
                                      // & x goes left
                                                                link(x,nxt_x);
                                                                x=nxt_x;
                                                                nxt_x=nxt_x->sibling;
                                                        }
                                                        else 
                                                        {
                                                                prev_x->sibling=nxt_x;
                                                                link(x,nxt_x);
                                                                x=nxt_x;
                                                                nxt_x=nxt_x->sibling;
                                                        }
 
   }

  return h;
}
        
struct bino *find_min(struct bino *head)
{
  int min=-1;
  struct bino *temp;   ///pointer pointing to min key node
  if(head!=NULL)
  {

    min=head->key;     /// intializing first node key as min 
    temp=head;
    if(head->sibling!=NULL)
     head=head->sibling;
    else 
     head=NULL;
  } 
    // linearly comparing with nxt node to find min
    while(head!=NULL)
    {
      if(min > head->key)
      {
        min=head->key;
        temp=head;      
      }
      head=head->sibling;
   }
  return temp;
}

struct bino *extract_min(struct bino *head)
{
   struct bino *temp1;              /// pointer pointing to min key node
   struct bino *exhead;             /// store the head of the new heap after extracting min
   struct bino *h2=head;            /// storing the head 
   struct bino *h_prev=NULL;        /// pointer pointing to node before min key node 
   struct bino *p,*q=NULL,*r=NULL;       /// for revesing 
   temp1=find_min(head);                /// temp1 pointing to min key node
   cout<<"MIN : "<<temp1->key<<endl;

   /// making min key node null 
   if(temp1->key==head->key)
    {
     h_prev=NULL; 
    }
   while(temp1->key!=head->key)
   {       
       h_prev=head;
       head=head->sibling;
   }

   /// all the conditions for setting head of intial list befor extract min  
   
   if(h_prev!=NULL && head->sibling!=NULL)
     h_prev->sibling=head->sibling;                        
   if(h_prev!=NULL && head->sibling==NULL)                 //  making min key node null (sibling of node before min key node)
     h_prev->sibling=NULL; 
   if(h_prev==NULL && head->sibling!=NULL)
     h2=head->sibling;
   if(h_prev==NULL && head->sibling==NULL)
     h2=NULL;
  
   
   p=temp1->child;
   temp1->child=NULL;              /// making the min key node child as NULL

 /// making the parent of those child nodes as NULL (parent is min key node)
   r=p;
   p->parent=NULL;
   while(p->sibling!=NULL)        
   {
     q=p;
     p=p->sibling;
     p->parent=NULL;
   }
   
 /// Reversing the new tree 
   p=r;
   r=NULL;
   
   if(p->sibling!=NULL)
   {
    q=p->sibling;
    p->sibling=NULL;
    if(q->sibling!=NULL)
    {
      r=q->sibling;
    }
   }
   else
    exhead=p;             /// initial head of newly formed list after extract_min;
  
   while(q!=NULL)
   {
     //cout<<"Count"<<endl;
     q->sibling=p;
     p=q;
     /// changing head
     exhead=q;          
     q=r;  
     if(r!=NULL && r->sibling!=NULL)
       {
         r=r->sibling;
         //cout<<"HELL "<<endl;
       }
     else
       r=NULL;
   }
 
   temp1=NULL;    
   free(temp1);

   h2=uni(h2,exhead);   /// h2- inital list head &  exhead- head of newly formed heap 
                        /// function call to merge and union them
   return h2;
   //return exhead;
}

///function to search the required key 

struct bino *ret=NULL;                         /// search key node
void search_key(int key,struct bino *head)
{
  while(head!=NULL)
  {
    if(head->key==key)
     {
      ret=head;
      break;
     }
    if(head->child!=NULL)
    {
      search_key(key,head->child);    
    }
    head=head->sibling;  
  }
  
  /*while(r!=NULL)
  {
    cout<<r->key<<"  ";
    if(r->child!=NULL)
    {
     print(r->child);
    }
    r=r->sibling;
  }*/
}  

//Decrease_key function 

void decrease_key(struct bino *head,int key,int new_k)
{
  if(key<new_k)
    cout<<"ERROR "<<endl;
  else
  {
    struct bino *temp1,*z;
    int temp3; 
                search_key(key,head);
    if(ret==NULL)
     cout<<"WRONG KEY IS ENTERED "<<endl;
    /*else 
    {
      cout<<"SEARh "<<ret->key<<endl;
      ret=NULL;
    }*/
                ret->key=new_k;
    temp1=ret;  
    z=ret->parent;
    while(z!=NULL && temp1->key < z->key)
    {
                        temp3=temp1->key;
      temp1->key=z->key;
      z->key=temp3;
      temp1=z;
      z=z->parent;
      
    }
   cout<<"After decrease_key "<<endl;
   print(head);
   cout<<endl;
  }   
}
    
///Delete Function 
void delete_key(struct bino *head,int key)
{
   decrease_key(head,key,-99999999);
   head=extract_min(head);
   print(head);
   cout<<endl;
}
   

struct bino *prev=NULL;
int main()
{
  int n;  // no. of inputs
        int s;
  int no; // switch case element
        struct bino *h1=NULL;
  struct bino *h2=NULL;
  struct bino *exhead1=NULL;
  struct bino *p;
  while(1)
  {
  cout<<"ENTER 1 to CREATE BINOMIAL HEAP "<<endl;
  cout<<"ENTER 2 to FIND_MIN from BINOMIAL HEAP "<<endl;
  cout<<"ENTER 3 to EXTRACT_MIN from BINOMIAL HEAP "<<endl;
  cout<<"ENTER 4 to SEARCH_KEY from BINOMIAL HEAP "<<endl; 
  cout<<"ENTER 5 to DECREASE_KEY from BINOMIAL HEAP "<<endl;
  cout<<"ENTER 6 to DELETE KEY from BINOMIAL HEAP "<<endl;
  cout<<"ENTER 0 to exit "<<endl;
  cin>>no;
  switch(no)
  {
  case 1:
                cout<<"Enter how many elements "<<endl;
        cin>>n;
        cout<<"Enter the element 1 : "<<endl;
        cin>>s; 
        h2=create(s);
        for(int i=0;i<n-1;i++)
        {       
        cout<<"Enter the element "<<i+2<<" : "<<endl;
                        cin>>s;
        h1=create(s);
        h2=uni(h1,h2);
        cout<<endl;
                        print(h2);
        cout<<endl;
                }
        cout<<endl;
        cout<<"OUTPUT : "<<endl;
                print(h2);
        cout<<endl;
    break;

  case 2:
    p=find_min(h2);
    cout<<"MIN KEY : "<<p->key<<endl;
    break;

  case 3:
    cout<<"VALUES After extract_min"<<endl;
    h2=extract_min(h2);
    print(h2);
    cout<<endl;
    break;
  
  case 4:
   int key;
   cout<<"Enter the key to be searched "<<endl;
   cin>>key;
  // struct bino *search=NULL;
   search_key(key,h2);
   
   if(ret==NULL)
    cout<<"WRONG KEY IS ENTERED "<<endl;
   else 
    {
      cout<<"SEARh "<<ret->key<<endl;
      ret=NULL;
    }
   break;

  case 5:
   int key1,new_k;
   cout<<"Enter the key to decreased and new value of key "<<endl;
   cin>>key1;
   cin>>new_k;
   decrease_key(h2,key1,new_k);
   break;

  case 6:
   int k1; 
   cout<<"Enter the key to be deleted "<<endl; 
   cin>>k1;
   delete_key(h2,k1);
   break;
  }// switch
   if(no==0)
    break;
  }//while

}//main

