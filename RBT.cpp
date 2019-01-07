/*********************************************************************************************************************************
ASSIGNMENT : Write C or C++ program to Implement Red Black Tree Data Structure for storing set of integer keys.
and perform the following operations.
1. Insert()
2. Delete()
3. Search()
After each operation (insert,delete) Display the corresponding rotation or color change that took place
NAME : SHAUNAK JOSHI
CLASS : SY-H
ROLL NO : 41
GR: 161042
**********************************************************************************************************************************
*/
#include<iostream>
using namespace std;
typedef struct rbt
{
int data;
char color;
struct rbt* left;
struct rbt* right;
struct rbt* parent;
}rbt;
rbt* rotate_right(rbt*,int,rbt*);
rbt* rotate_left(rbt*,int,rbt*);
rbt* insert(rbt*,int);
rbt* add_bst(rbt*,int);
rbt* delete_rbt(int,rbt*,rbt*);
int search(rbt*, int);
void levelorderR(rbt*,int);
void printlevelorder(rbt*);
int heightr(rbt*);
void inorderR(rbt*);
int main()
{
rbt* head=NULL;
int n;
cin>>n;
for(int i=0;i<n;i++)
{
int data;
cout<<"enter the element to be inserted\n";
cin>>data;
cout<<"rbt in level order is";
head=insert(head,data);
printlevelorder(head);
}
cout<<endl<<endl;
printlevelorder(head);
cout<<endl<<"inorder"<<endl;
inorderR(head);
int data=1;
int key;
cout<<"enter the element to be searched";
cin>>key;
if(search(head,key))
cout<<"present";
else
cout<<"not present";
while(data!=-1)
{
cout<<"enter the element to be deleted";
cin>>data;
head=delete_rbt(data,head,NULL);
cout<<"tree after deletion";
cout<<endl<<endl;
cout<<"level order";
printlevelorder(head);
cout<<endl<<"inorder"<<endl;
inorderR(head);
}

return 0;
}
rbt* rotate_right(rbt* t,int flag,rbt* head)
{
rbt* temp=t->parent->parent;
if(t->right == NULL)
{
t->parent->left=t->right;
}
else
{
t->parent->left=t->right;
t->right->parent=t->parent;
}
t->parent->parent=t;
t->right=t->parent;
t->parent=temp;
if(flag == 1)
{
t->right->color='r';
t->color='b';
}
if(t->parent==NULL) //head is to be changed
{
head=t;
head->parent=NULL;
}
else
{
if(temp!=NULL && temp->left== t->right) // grand grandfather left child is grandfather
{
temp->left=t;
t->parent=temp;
}
else if(temp!=NULL && temp->right==t->right) // grand grandfather right child is grandfather
{
temp->right=t;
t->parent=temp;
}
}
return head;
}
rbt* rotate_left(rbt* t,int flag,rbt* head)
{
rbt* temp=t->parent->parent;
if(t->left == NULL)
{
t->parent->right=t->left;
}
else
{
t->parent->right=t->left;
t->left->parent=t->parent;
}
t->parent->parent=t;
t->left=t->parent;
t->parent=temp;
if(flag == 1)
{
t->left->color='r';
t->color='b';
}
if(t->parent == NULL) // head is changed
{
head=t;
head->parent=NULL;
}
else
{

if(temp!=NULL && temp->left == t->left) // grand grandfather left child is grandfather
temp->left=t;
else if(temp!=NULL && temp->right==t->left)//grand grandfather right child is grandfather
temp->right=t;
}
return head;
}
int i=0;
rbt* insert(rbt* t,int data)
{
rbt* x=add_bst(t,data);
if( t == NULL)
t=x;
while(x!=t && x->parent!=NULL && x->parent->color=='r')
{
if(x->parent->parent!=NULL && x->parent->parent->left == x->parent) //left side
{
if(x->parent->parent->right!=NULL && x->parent->parent->right->color=='r') //uncle is red LLr LRr
{
x->parent->color='b';
x->parent->parent->right->color='b';
if(x->parent->parent!=t)
x->parent->parent->color='r';
x=x->parent->parent;
}
else //uncle is black
{
if(x->parent->left==x) // LLb
{
t=rotate_right(x->parent,1,t);//rotate right
}
else //LRb
{
t=rotate_left(x,0,t);
t=rotate_right(x,1,t);
}
}
}
else //right side
{
if(x->parent->parent->left!=NULL && x->parent->parent->left->color=='r') //uncle is red RRr RLr
{
x->parent->color='b';
x->parent->parent->left->color='b';
if(x->parent->parent!=t)
x->parent->parent->color='r';
}
else
{
if(x->parent->right==x) // RRb
{
t=rotate_left(x->parent,1,t);//rotate left
}
else //RLb
{
t=rotate_right(x,0,t);
t=rotate_left(x,1,t);
}
}
}
}
return t;
}
rbt* add_bst(rbt* t,int data)
{
rbt* pre_t=NULL;
rbt* parent_pre_t=NULL;
if(t==NULL)
{
t=new rbt();
t->data=data;
t->color='b';

t->left=NULL;
t->right=NULL;
t->parent=NULL;
return t;
}
else
{
rbt* new_t=new rbt();
new_t->data=data;
new_t->color='r';
new_t->left=NULL;
new_t->right=NULL;
while(t!=NULL)
{
if(t->data > data)
{
pre_t=t;
t=t->left;
}
else
{
pre_t=t;
t=t->right;
}
}
if(pre_t->data > data)
{
pre_t->left=new_t;
new_t->parent=pre_t;
}
else
{
pre_t->right=new_t;
new_t->parent=pre_t;
}
return new_t;
}
}
rbt* delete_rbt(int data,rbt* head,rbt* t) // t is to be deleted, data is the key to be deleted
{
if(t==NULL) // node to be deleted is not given
{
t=head;
while(t!= NULL && t->data!=data)
{
if(t->data>data)
t=t->left;
else
t=t->right;
}
if(t==NULL)
{
cout<<"key is not present";
return head;
}
else if(t == head && t->left==NULL && t->right==NULL) // node deleted is the head and its the only node
{
delete t;
return NULL;
}
}
if( (t->left==NULL && t->right==NULL) ) // leaf node
{
if( t->color=='r' )// leaf node is red
{
if(t->parent->left==t)
{
t->parent->left=NULL;
}
else
{
t->parent->right=NULL;
}
delete t;

}
else // leaf node is black so both u,v is black
{
if(t->parent->left!=NULL && t->parent->left==t) // t(leaf node) is left child
{
if(t->parent->right!=NULL && ( (t->parent->right->left!=NULL && t->parent->right->left->color=='r') ||
(t->parent->right->right!=NULL && t->parent->right->right->color=='r') ) ) // sibling is b and atleast one of its child is r
{
if(t->parent->right->right!=NULL) // sibling has right child so RRb
{
if(t->parent->color=='b')
t->parent->right->right->color='b';
head=rotate_left(t->parent->right,0,head);
}
else //sibling has a left child so RLb
{
if(t->parent->color=='b')
t->parent->right->left->color='b';
else
t->parent->color='b';
head=rotate_right(t->parent->right->left,0,head);
head=rotate_left(t->parent->right,0,head);
}
t->parent->left=NULL;
delete t;
}
else if(t->parent->right!=NULL && t->parent->right->color=='r' && (t->parent->right->left==NULL || t->parent->right->left->color=='b')
&& (t->parent->right->right == NULL || t->parent->right->right->color=='b') ) // parent is b,sibling is r and has two b children
{
t->parent->right->color='b'; // make color changes and RRb
if(t->parent->right->left!=NULL)
t->parent->right->left->color='r';
if( t->parent->right->right!=NULL) //RRb
head=rotate_left(t->parent->right,0,head);
else //RLb
{
head=rotate_right(t->parent->right->left,0,head);
head=rotate_left(t->parent->right,0,head);
}
if( (t->parent->right->left!=NULL && t->parent->right->left->color=='r') && // sibling's left child has 2 r childs
(t->parent->right->right!=NULL && t->parent->right->right->color=='r') )
{
head=rotate_left(t->parent->right,1,head);
t->parent->color='b';
t->parent->parent->right->color='b';
if(t->parent->parent!=head)
t->parent->parent->color='r';
}
else if( t->parent->right->right!=NULL && t->parent->right->right->color=='r' ) // sibling's left child has only 1 r right child
{
head=rotate_left(t->parent->right,1,head); // LLb
}
else if( t->parent->right->left!=NULL && t->parent->right->left->color=='r' ) // sibling's left child has only 1 r left child
{
head=rotate_right(t->parent->right->left,0,head); //LRb
head=rotate_left(t->parent->right,1,head);
}
t->parent->left=NULL;
delete t;
}
else if(t->parent->color=='r' && t->parent->right!=NULL && t->parent->right->color=='b' &&
(t->parent->right->left==NULL || t->parent->right->left->color=='b') && (t->parent->right->right == NULL ||
t->parent->right->right->color=='b') ) // parent is red and sibling and its childs are b
{
t->parent->right->color='r';
t->parent->color='b';
t->parent->left=NULL;
delete t;

}
else if(t->parent->color=='b' && t->parent->right!=NULL && t->parent->right->color=='b' &&
(t->parent->right->left==NULL || t->parent->right->left->color=='b') && (t->parent->right->right == NULL ||
t->parent->right->right->color=='b') ) // parent is b and silbling and its childs are b
{
rbt* temp=t;
while(t!=head)
{
if(t->parent->left == t) // t is left child
t->parent->right->color='r';
else
t->parent->left->color='b';
t=t->parent;
}
temp->parent->left=NULL;
delete temp;
}
}
else // t(leaf node) is right child
{
if(t->parent->left!=NULL && ( (t->parent->left->left!=NULL && t->parent->left->left->color=='r') ||
(t->parent->left->right!=NULL && t->parent->left->right->color=='r') ) ) // sibling is b and atleast one of its child is r
{
if(t->parent->left->left!=NULL) // sibling has left child so LLb
{
if(t->parent->color=='b')
t->parent->left->left->color='b';
head=rotate_right(t->parent->left,0,head);
}
else //sibling has a right child so LRb
{
if(t->parent->color=='b')
t->parent->left->right->color='b';
else
t->parent->color='b';
head=rotate_left(t->parent->left->right,0,head);
head=rotate_right(t->parent->left,0,head);
}
t->parent->right=NULL;
delete t;
}
else if(t->parent->left!=NULL && t->parent->left->color=='r' && (t->parent->left->left==NULL || t->parent->left->left->color=='b')
&& (t->parent->left->right == NULL || t->parent->left->right->color=='b') ) // parent is b,sibling is r and has two b children
{
t->parent->left->color='b'; // make color changes
if(t->parent->left->right!=NULL)
t->parent->left->right->color='r';
if( t->parent->left->left!=NULL) //LLb
head=rotate_right(t->parent->left,0,head);
else //LRb
{
head=rotate_left(t->parent->left->right,0,head);
head=rotate_right(t->parent->left,0,head);
}
if( (t->parent->left->left!=NULL && t->parent->left->left->color=='r') && // sibling's left child has 2 r childs
(t->parent->left->right!=NULL && t->parent->left->right->color=='r') )
{
head=rotate_right(t->parent->left,1,head);
t->parent->color='b';
t->parent->parent->left->color='b';
if(t->parent->parent!=head)
t->parent->parent->color='r';
}
else if( t->parent->left->left!=NULL && t->parent->left->left->color=='r' ) // sibling's left child has only 1 r left child
{
head=rotate_right(t->parent->left,1,head);
}
else if( t->parent->left->right!=NULL && t->parent->left->right->color=='r' ) // sibling's left child has only 1 r right child
{
head=rotate_left(t->parent->left->right,0,head);
head=rotate_right(t->parent->left,1,head);
}

t->parent->right=NULL;
delete t;
}
else if(t->parent->color=='r' && t->parent->left!=NULL && t->parent->left->color=='b' &&
(t->parent->left->left==NULL || t->parent->left->left->color=='b') && (t->parent->left->right == NULL ||
t->parent->left->right->color=='b') ) //parent is red and sibling and its childs are b
{
t->parent->left->color='r';
t->parent->color='b';
t->parent->right=NULL;
delete t;
}
else if(t->parent->color=='b' && t->parent->left!=NULL && t->parent->left->color=='b' &&
(t->parent->left->left==NULL || t->parent->left->left->color=='b') && (t->parent->left->right == NULL ||
t->parent->left->right->color=='b') ) // parent is b and sibling and its childs are b
{
rbt* temp=t;
while(t!=head)
{
if(t->parent->right==t)
t->parent->left->color='r';
else
t->parent->right->color='r';
t=t->parent;
}
temp->parent->right=NULL;
delete temp;
}
}
}
}
else if( t->left==NULL || t->right==NULL) // one child node
{
if(t->left==NULL) // it has a right child
{
rbt* temp=t->right; //temp will be its successor
while(temp->left!=NULL)
temp=temp->left;
t->data=temp->data;
head=delete_rbt(0,head,temp);
}
else //it has a left child
{
rbt* temp=t->left; //temp will be its predeccessor
while(temp->right!=NULL)
temp=temp->right;
t->data=temp->data;
head=delete_rbt(0,head,temp);
}
}
else // it has two childs
{
rbt* temp=t->right; //temp will be its successor
while(temp->left!=NULL)
temp=temp->left;
t->data=temp->data;
head=delete_rbt(0,head,temp);
}
return head;
}
int search(rbt* t, int data)
{

while(t!= NULL && t->data!=data)
{
if(t->data>data)
t=t->left;
else
t=t->right;
}
if(t==NULL)
{
return 0;
}
else
{
return 1;
}
}

void levelorderR(rbt* r,int level)
{
if(r==NULL)
return;
if(level==1)
cout<<r->data<<" "<<r->color<<endl;
else if(level>1)
{
levelorderR(r->left,level-1);
levelorderR(r->right,level-1);
}
}
void printlevelorder(rbt *r)
{
int h=heightr(r);
cout<<endl;
for(int i=1;i<=h;i++)
{
levelorderR(r,i);
}
}
int heightr(rbt* r)
{
if(r==NULL)
return 0;
else
{
int lh=heightr(r->left);
int rh=heightr(r->right);
if(lh>rh)
return lh+1;
else
return rh+1;
}
}
void inorderR(rbt* r)
{
if(r!=NULL)
{
inorderR(r->left);
cout<<r->data<<" "<<r->color<<endl;
inorderR(r->right);
}
}
