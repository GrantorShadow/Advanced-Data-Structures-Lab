#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <map>
#include <iterator>
#include <utility>
#include<cmath>
#define infinity -99999
using namespace std;
/*
 * Node Declaration
 */
struct node
{
    int dist;
    int node_num;
    int degree;
    node* parent;
    node* child;
    node* left;
    node* right;
    char mark;
    char C;
};
/*
 * Class Declaration
 */
class FibonacciHeap
{
    private:
        int nH;
        node *H;
        multimap<int, node*>map;
    public:
        void viewmap();
        int Fibonnaci_link(node*, node*, node*);
        node *Create_node(int);
        node *Insert(int key,int n);
        node *Union(node *, node *);
        node *Extract_Min();
        int Consolidate(node *);
        int Display(node *);
        node *Find( int);
        int Decrease_key(node *, int, int);
        int Delete_key(node *,int);
        int Cut(node *, node *, node *);
        int Cascase_cut(node *, node *);
        FibonacciHeap()
        {
            H = NULL;
            nH=0;
        }
};
/*
 * Initialize Heap
 */

/*
 * Create Node
 */
node* FibonacciHeap::Create_node(int value)
{
    node* x = new node;
    x->dist = value;
    return x;
}
/*
 * Insert Node
 */
 
// bool fibonacci::insert(int key) {
//    if (H == NULL) 
//	
//	{
//        this->min = new node(key);
//        map.insert(pair<int, node*>(key, this->min));
//        this->n = this->n + 1;
//        return true;
//    } else {
//
//        node* newnode = new node(key);
//        newnode->rightsibling = this->min;
//        newnode->leftsibling = this->min->leftsibling;
//        this->min->leftsibling->rightsibling = newnode;
//        this->min->leftsibling = newnode;
//        if (this->min->key > key)
//            this->min = newnode;
//        map.insert(pair<int, node*>(key, newnode));
//        return true;
//    }
//}

node* FibonacciHeap::Insert(int key,int n)
{
   node* x = NULL;
   x=Create_node(key);
    x->degree = 0;
    x->node_num=n;
    x->parent = NULL;
    x->child = NULL;
    x->left = x;
    x->right = x;
    x->mark = 'F';
    x->C = 'N';
    if (this->H != NULL)
    {
        (H->left)->right = x;
        x->right = H;
        x->left = H->left;
        H->left = x;
        if (x->dist < H->dist)
            H = x;
            
        map.insert(pair<int, node*>(H->dist, H));
    }
    else
    {
        H = x;
        map.insert(pair<int, node*>(x->dist, x));
    }
    nH = nH + 1;
    return H;
}


void FibonacciHeap::viewmap() 
{
    cout << "Elements in m: " << endl;
    for (multimap<int,node*>::iterator it = map.begin(); it != map.end(); ++it) {
        cout << "  [" << (*it).first << ", " << (*it).second << "]" << endl;

    }
}
/*
 * Link Nodes in Fibonnaci Heap
 */
int FibonacciHeap::Fibonnaci_link(node* H1, node* y, node* z)
{
    //cout<<"\n in link";
    (y->left)->right=y->right;
    (y->right)->left=y->left;
    if(z->right==z)
      H1=z;
     y->left=y;
     y->right=y;
    y->parent=z;
    if(z->child==NULL)
      z->child=y;
    y->right=z->child;
    y->left=(z->child)->left;
    ((z->child)->left)->right=y;
    (z->child)->left=y;
    if(y->dist<(z->child)->dist)
      z->child=y;
   // cout<<"\nthe node made as parent="<<z->n<<" and node made as child="<<y->n;
    //cout<<"\nusing z";
   // DISPLAY(z);
    z->degree++;
    //cout<<"\nexiting link!!";
}
/*
 * Union Nodes in Fibonnaci Heap
 */
node* FibonacciHeap::Union(node* H1, node* H2)
{
    node* np;
    node* H = NULL;
    H = H1;
    (H->left)->right = H2;
    (H2->left)->right = H;
    np = H->left;
    H->left = H2->left;
    H2->left = np;
    return H;
    
    
    

}
/*
 * Display Fibonnaci Heap
 */
int FibonacciHeap::Display(node* H)
{
    node* p = H;
    if (p == NULL)
    {
        cout<<"The Heap is Empty"<<endl;
        return 0;
    }
    cout<<"The root nodes of Heap are: "<<endl;
    do
    {
        cout<<p->dist;
        p = p->right;
        if (p != H)
        {
            cout<<"-->";
        }
    }
    while (p != H && p->right != NULL);
    cout<<endl;
}
/*
 * Extract Min Node in Fibonnaci Heap
 */
node* FibonacciHeap::Extract_Min()
{
    node* H1=this->H;
    node* p;
    node* ptr;
    node* z = H1;
    p = z;
    ptr = z;
    if (z == NULL)
        return z;
    node* x;
    node* np;
    x = NULL;
    if (z->child != NULL)
        x = z->child;
    if (x != NULL)
    {
        ptr = x;
        do
        {
            np = x->right;
            (H1->left)->right = x;
            x->right = H1;
            x->left = H1->left;
            H1->left = x;
            if (x->dist < H1->dist)
                H1 = x;
            x->parent = NULL;
            x = np;
        }
        while (np != ptr);
    }
    (z->left)->right = z->right;
    (z->right)->left = z->left;
    H1 = z->right;
    if (z == z->right && z->child == NULL)
        H = NULL;
    else
    {
        H1 = z->right;
        Consolidate(H1);
    }
    nH = nH - 1;
    return p;
}
/*
 * Consolidate Node in Fibonnaci Heap
 */
int FibonacciHeap::Consolidate(node* H1)
{
    int d, i;
    float f = (log(nH)) / (log(2));
    int D = f;
    node* A[D];
    for (i = 0; i <= D; i++)
        A[i] = NULL;
    node* x = H1;
    node* y;
    node* np;
    node* pt = x;
    do
    {
        pt = pt->right;
        d = x->degree;
        while (A[d] != NULL)
        {
            y = A[d];
            if (x->dist > y->dist)
            {
                np = x;
                x = y;
                y = np;
            }
            if (y == H1)
                H1 = x;
            Fibonnaci_link(H1, y, x);
            if (x->right == x)
                H1 = x;
                A[d] = NULL;
            d = d + 1;
        }
        A[d] = x;
        x = x->right;
    }
    while (x != H1);
    H = NULL;
    for (int j = 0; j <= D; j++)
    {
        if (A[j] != NULL)
        {
            A[j]->left = A[j];
            A[j]->right =A[j];
            if (H != NULL)
            {
                (H->left)->right = A[j];
                A[j]->right = H;
                A[j]->left = H->left;
                H->left = A[j];
                if (A[j]->dist < H->dist)
                H = A[j];
            }
            else
            {
                H = A[j];
            }
            if(H == NULL)
                H = A[j];
            else if (A[j]->dist < H->dist)
                H = A[j];
        }
    }
}
  

/*
 * Decrease key of Nodes in Fibonnaci Heap
 */
int FibonacciHeap::Decrease_key( node* ptr,int x, int k)
{
	node *H1=this->H;
    node* y;
    if (H1 == NULL)
    {
        cout<<"The Heap is Empty"<<endl;
        return 0;
    }
   // node* ptr = Find(H1, x);
    if (ptr == NULL)
    {
        cout<<"Node not found in the Heap"<<endl;
        return 1;
    }
    if (ptr->dist < k)
    {
        cout<<"Entered key greater than current key"<<endl;
        return 0;
    }
    ptr->dist = k;
    y = ptr->parent;
    if (y != NULL && ptr->dist < y->dist)
    {
        Cut(H1, ptr, y);
        Cascase_cut(H1, y);
    }
    if (ptr->dist < H->dist)
        H = ptr;
    return 0;
}
/*
 * Cut Nodes in Fibonnaci Heap
 */
int FibonacciHeap::Cut(node* H1, node* x, node* y)
{
    if (x == x->right)
        y->child = NULL;
    (x->left)->right = x->right;
    (x->right)->left = x->left;
    if (x == y->child)
        y->child = x->right;
    y->degree = y->degree - 1;
    x->right = x;
    x->left = x;
    (H1->left)->right = x;
    x->right = H1;
    x->left = H1->left;
    H1->left = x;
    x->parent = NULL;
    x->mark = 'F';
}
 
/*
 * Cascade Cutting in Fibonnaci Heap
 */
int FibonacciHeap::Cascase_cut(node* H1, node* y)
{
    node* z = y->parent;
    if (z != NULL)
    {
        if (y->mark == 'F')
        {
            y->mark = 'T';
	}
        else
        {
            Cut(H1, y, z);
            Cascase_cut(H1, z);
        }
    }
}
 
/*
 * Find Nodes in Fibonnaci Heap
 */
node* FibonacciHeap::Find(   int k)
{
    node* x = H;
    x->C = 'Y';
    node* p = NULL;
    if (x->dist == k)
    {
        p = x;
        x->C = 'N';
        return p;
    }
    if (p == NULL)
    {
        if (x->child != NULL )
            p = Find(x->child, k);
        if ((x->right)->C != 'Y' )
            p = Find(x->right, k);
    }
    x->C = 'N';
    return p;
}
/*
 * Delete Nodes in Fibonnaci Heap
 */
int FibonacciHeap::Delete_key(node* H1, int k)
{
    node* np = NULL;
    int t;
    t = Decrease_key(H1, k, -5000);
    if (!t)
        np = Extract_Min();
    if (np != NULL)
        cout<<"Key Deleted"<<endl;
    else
        cout<<"Key not Deleted"<<endl;
    return 0;
}

int main()
{
    int n=500, m, l;
    FibonacciHeap fh;
    node* p;
    node* H= NULL;

     int g[500][500],k;
     int i,j,s;

 //printf("\nEnter the adjacency matrix:\n");
 for(i=0;i<500;i++)
 {
  for(j=0;j<500;j++)
  {
       g[i][j]=rand()%1000 ;
   }
 }
 int distance[500],from[500];//visited[max];
 int min_distance1=infinity;
 for(i=0;i<500;i++)
 {
  for(j=0;j<500;j++)
  {
   if(g[i][j]==0)
    g[i][j]=infinity;
   else
    g[i][j]=g[i][j];
  }
}


  for(j=0;j<500;j++)
  {
      fh.Insert(g[0][j],j);
      cout<<g[0][j]<<"\n";

  }
   for(i=0;i<500;i++)
  {
  distance[i]=g[0][i];
  from[i]=0;
  }


 int count=1,next;
 
 node *min=NULL;
 node* dec=NULL;
 while(count<n-1)
 {
   min=fh.Extract_Min();
  min_distance1=min->dist;
  next=min->node_num;
  cout<<"\n\n\n"<<"fhjgh   "<<min_distance1<<"\n\n"<<"node_num    "<<next;
  

  //next gives the node at min distance
   //check if the better path exists
 for(i=1;i<n;i++)
 {
    if(min_distance1+g[next][i]<distance[i])
  {
     distance[i]=min_distance1+g[next][i];
     for (multimap<int,node*>::iterator it = map.begin(); it != map.end(); ++it){
     	if((*it).first==i){
		   		dec=(*it).second;
				break;
		}
	 }
     fh.Decrease_key(dec,dec->dist,distance[i]);
	 
	 //from[i]=next;
  }
 }
count++;
}

//print the path and distance of each node

for(i=0;i<n;i++)
    if(i!=s)
    {
        printf("\nDistance of node%d=%d",i,distance[i]);
        printf("\n path=%d",i);
        j=i;
        do
        {
            j=from[j];
            printf("<-%d",j);

        }while(j!=s);
    }
}
