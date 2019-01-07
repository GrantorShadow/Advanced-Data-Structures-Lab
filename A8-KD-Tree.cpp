#include<iostream>
#include<math.h>
using namespace std;


typedef struct kd_tree
{
    int* data;
    int dim;
    struct kd_tree* left;
    struct kd_tree* right;
}kd_tree;


kd_tree* initialise(int dim,int* arr)
{
    kd_tree* t=new kd_tree();
    t->data=new int[dim];
    
    for(int i=0;i<dim;i++)
        t->data[i]=arr[i];
    t->left=t->right=NULL;
}


kd_tree* insert(kd_tree* t,int* arr,int dim,int cut)
{
    if(t==NULL)
    {
        t=initialise(dim,arr);
        return t;
    }
    if(arr[cut]>=t->data[cut])
        t->right=insert(t->right,arr,dim,(cut+1)%dim);
    else
        t->left=insert(t->left,arr,dim,(cut+1)%dim);
    return t;
}

void print(kd_tree* t,int dim)
{
    if(t!=NULL)
    {
        print(t->left,dim);
        for(int i=0;i<dim;i++)
            cout<<t->data[i]<<" ";
        cout<<endl;
        print(t->right,dim);
    }
}


bool compare(int* arr1,int* arr2,int dim)
{
    int i;
    for( i=0;i<dim;i++)
    {
        if(arr1[i]!=arr2[i])
            break;
    }
    if(i==dim)
        return true;
    else
        return false;
}

bool search(kd_tree* root,int* arr,int dim,int cut)
{
    static bool flag=false;
    
    if(root!=NULL)
    {
        if(compare(root->data,arr,dim))
            flag=true;
        else if(root->data[cut]>arr[cut])
            search(root->left,arr,dim,(cut+1)%dim);
        else
            search(root->right,arr,dim,(cut+1)%dim);
    }
    return flag;
}


kd_tree* min(kd_tree* a1,kd_tree* a2,kd_tree* a3,int req_dim)
{
    kd_tree* min;
    
    if(a1==NULL && a2==NULL)
        return a3;
    else if(a2==NULL)
        a1->data[req_dim]<a3->data[req_dim]?min=a1:min=a3;
    else if(a1==NULL)
        a2->data[req_dim]<a3->data[req_dim]?min=a2:min=a3;    
    else
        a1->data[req_dim]<a2->data[req_dim]?a1->data[req_dim]<a3->data[req_dim]?min=a1:min=a3:a2->data[req_dim]<a3->data[req_dim]? \
        min=a2:min=a3;
    
    return min;
    
}

kd_tree* min_dim(kd_tree* t,int req_dim,int dim,int cut)
{
    if(t==NULL)
      return NULL;
    if(cut==req_dim)
    {
        if(t->left!=NULL)
            return min_dim(t->left,req_dim,dim,(cut+1)%dim);
        else
            return t;
    }
    else
    {
        return( min(min_dim(t->left,req_dim,dim,(cut+1)%dim),min_dim(t->right,req_dim,dim,(cut+1)%dim),t,req_dim));  
    }
}


int dist(int* a1,int* a2,int dim)
{
    int dis=0;
    for(int i=0;i<dim;i++)
        dis+=pow(a1[i]-a2[i],2);
    return ceil(sqrt(dis));
}

kd_tree* nearest_neighbour(kd_tree* n,int* q,int dim,int cut)
{
    static kd_tree* p=NULL;
    static int w=99999;
    
    if(n->left==NULL && n->right==NULL)
    {
        int w1=dist(n->data,q,dim);
        if(w1 < w)
        {
               
            p=n;
            w=w1;
           
        }
    }
    else
    {
        bool flag=false;
        if(n->data[cut]>q[cut])
            flag=true;
            
        if(flag) //left
        {
            
            if(n->left!=NULL && q[cut]-w<n->data[cut])
                nearest_neighbour(n->left,q,dim,(cut+1)%dim);
            int w1=dist(n->data,q,dim);
            if(w1 < w)
            {
                         
                w=w1;
                p=n;
            }
            if(n->right!=NULL && q[cut]+w>=n->data[cut])
                nearest_neighbour(n->right,q,dim,(cut+1)%dim);
        }
        else //right
        {
            if(n->right!=NULL && q[cut]+w>=n->data[cut])
                nearest_neighbour(n->right,q,dim,(cut+1)%dim);
            int w1=dist(n->data,q,dim);

            if(w1 < w)
            {
             
                
                w=w1;
                p=n;
            }
            if(n->left!=NULL && q[cut]-w<n->data[cut])
                nearest_neighbour(n->left,q,dim,(cut+1)%dim);
        }
    }
    
    return p;
}


kd_tree* delete_tree(kd_tree* root,int* a,int dim,int cut)
{
    kd_tree* t=root,*q=root;
    
    while(t!=NULL && !compare(t->data,a,dim))
    {
        q=t;
        if(t->data[cut]>a[cut])
            t=t->left;
        else
            t=t->right;
        cut=(cut+1)%dim;    
    }
    kd_tree* temp=t;
    if(t!=NULL)
    {
        if(t->left==NULL && t->right==NULL)
          //cout<<"why";
        {
            //cout<<"hi";
           if(q->left==t)
               q->left=NULL;
           else
               q->right=NULL;
            if(t==root)
                root=NULL;
            delete t;   
            return root;
         }
         if(t->right!=NULL)
        {
            kd_tree* min=min_dim(t->right,cut,dim,(cut+1)%dim);
           
            for(int i=0;i<dim;i++)
            {
                t->data[i]=min->data[i];
                
            }
            t->right=delete_tree(t->right,min->data,dim,(cut+1)%dim);
        }
        else if(t->left!=NULL)
        {
            kd_tree* min=min_dim(t->left,cut,dim,(cut+1)%dim);
            
            for(int i=0;i<dim;i++)
            {
                t->data[i]=min->data[i];
               
            }
            
            t->right=t->left;
            t->left=NULL;
            t->right=delete_tree(t->right,min->data,dim,(cut+1)%dim);
        }
        
    }
    return root;
}


int main()
{

    int dim;
    cin>>dim;
    int arr[dim];
    int n;
    cin>>n;
    kd_tree* root=NULL;
    
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<dim;j++)
            cin>>arr[j];
        
        root=insert(root,arr,dim,0);
      
    }
    cout<<"\n \n";
    cout<<"the tree structure is \n";
      print(root,dim);
        cout<<endl;
    int x=10,y=20,z=30;
   
    arr[0]=50;arr[1]=80;
    cout<<"searching for 50 80 \n";
    cout<<search(root,arr,dim,0)<<endl<<endl;
    arr[0]=35;arr[1]=90;
    cout<<"deleting 35 90 \n";
    delete_tree(root,arr,dim,0);
    print(root,dim);cout<<endl;
    kd_tree* p=NULL;
    p=min_dim(root,0,dim,0);
    
    cout<<"min in dim 0 is "<<p->data[0]<<" "<<p->data[1]<<endl;
    int w=99999;
    arr[0]=60;arr[1]=60;
    p=nearest_neighbour(root,arr,dim,0);
    
    cout<<"nearest neighbour of 60 60 is "<<p->data[0]<<" "<<p->data[1]<<endl;
    return 0;
}

