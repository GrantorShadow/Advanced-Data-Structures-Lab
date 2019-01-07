#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<typeinfo>
using namespace std;


template <class T>//for interfacing with java
struct stud
{
  T u;//creation of data item
};

//k is type of keys maintained, v is the mapped values
template <class T,class K>//creation of template java 
class rbt
{
  public:
  T key;
  K value;
  char color;
  struct rbt* left;
  struct rbt* right;
  struct rbt* parent;
  
  //public:
  
  rbt(T key,K value)//initialzation of rbt values
  {
  	this->key=key;
  	this->value=value;
  	this->color='r';
  	left=NULL;
  	right=NULL;
  	parent=NULL;
  }
};

template <class T,class K>
class TreeMap// decalring class template 
{
  int size1;
  rbt<T,K>* head;
	
	
	public:
	
	TreeMap()// constructor, constructs a new tree mao using its natural ordering of keys
	{
		head=NULL;
		this->size1=0;
	}
	
	//insert a node
	K put(T key,K value) 
	{
	  rbt<T,K>* node=NULL;   //for allocating new node
	  rbt<T,K>* trailing=NULL; 
	  rbt<T,K>* temp=head;  // travarse pointer
	  if(head!=NULL)     // if its not the first node
	  {
	       
	    
	    while(temp!=NULL && temp->key!=key)//starting at root and checking left and right
	    {
	      if(temp->key>key)
	      {
	        trailing=temp;
	        temp=temp->left;
	      }
	      else
	      {
	      	trailing=temp;
	      	temp=temp->right;
	      }
	    }
	    
	    if(temp==NULL)    //key is not present in the tree
	    {
	      node=new rbt<T,K>(key,value);
	      size1++;
	      if(trailing->key>key)
	      {
	      	node->parent=trailing;
	        trailing->left=node;
	      }
	      else
	      {
	        node->parent=trailing;
	      	trailing->right=node;
	      }
	    }
	    else
	    {
	      K l=temp->value;
	      temp->key=key;
	      return l;
	    }
    }
    else
    {
      size1++;
    	node=new rbt<T,K>(key,value);
    	head=node;
    	head->color='b';
    }
    
    check(node);
    return (K)NULL;
	}
	
	// for performing rotations and color changes
	void check(rbt<T,K>* x)
	{
		
		while(x!=head && x->parent!=NULL && x->parent->color=='r' && x->color=='r')
  	{
    	if(x->parent->parent!=NULL && x->parent->parent->left == x->parent) //left side
   	  {
    	  if(x->parent->parent->right!=NULL && x->parent->parent->right->color=='r') //uncle is red LLr LRr
    	  {
    	     x->parent->color='b';
    	     x->parent->parent->right->color='b';
         
    	     if(x->parent->parent!=head)
   		       x->parent->parent->color='r';
    	     x=x->parent->parent;
   	    }  
   	    else //uncle is black
        {
        	if(x->parent->left==x) // LLb
        	{
        	  rotate_right(x->parent,1);//rotate right
        	}
        	else //LRb
        	{
        	  rotate_left(x,0);
        	  rotate_right(x,1);                              
        	}
      	}	
    	}
    	else //right side
    	{
      	if(x->parent->parent->left!=NULL && x->parent->parent->left->color=='r') //uncle is red RRr RLr
      	{
      	  x->parent->color='b';
      	  x->parent->parent->left->color='b';
      	  if(x->parent->parent!=head)
      	    x->parent->parent->color='r';
      	}
      	else
      	{
        	if(x->parent->right==x) // RRb
        	{
        	  rotate_left(x->parent,1);//rotate left
        	}
        	else //RLb
        	{
        	  rotate_right(x,0);
        	  rotate_left(x,1);
        	}
      	}
     
    	}
    
 
  	}
	}

	void rotate_left(rbt<T,K>* t,int flag)
	{
  	rbt<T,K>* temp=t->parent->parent;
 
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
    	if(temp!=NULL && temp->left == t->left) //  grand grandfather left child is grandfather
    	  temp->left=t;
   	  else if(temp!=NULL && temp->right==t->left)//grand grandfather right child is grandfather
     	 temp->right=t;
  	}
	}	
	
	void rotate_right(rbt<T,K>* t,int flag)
	{
  	rbt<T,K>* temp=t->parent->parent;
 
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
  
  	if(t->parent==NULL) //head is to be  changed
  	{
  	  head=t;
  	  head->parent=NULL;
    
  	}
  	else
  	{
  	  if(temp!=NULL && temp->left== t->right) //  grand grandfather left child is grandfather
  	  { 
  	     temp->left=t;
  	     t->parent=temp;
  	  }  
  	  else if(temp!=NULL && temp->right==t->right) //  grand grandfather right child is grandfather
  	  { 
  	    temp->right=t;
  	    t->parent=temp;
  	  }
  	}		
	}
	
  void inorderR(rbt<T,K>* r)//function to display inorder O/P
	{
  	if(r!=NULL)
  	{
  	  inorderR(r->left);
  	  cout<<r->key<<" "<<r->color<<" "<<r->value<<endl;
  	  inorderR(r->right);
    }
  }	
	
	//searching a value flag 0 for string used in contains key
	bool search(rbt<T,K>* r,int i,K value)
	{
	  static bool b=false;
  	  if(r!=NULL)
  	  {
  	    search(r->left,i,value);//recursively calls itself to traverse and search
  	    if(i==0)
  	    {
  	    // cout<<strcmp(r->value,value);
  	     if(!strcmp(r->value,value))// compares each string to check for value
  	       b=true;
  	  }
  	  else
  	  {
  	    if(r->value==value)//if value is at root
  	      b=true;
  	  }
  	  //cout<<r->key<<" "<<r->color<<" "<<r->value<<endl;
  	  search(r->right,i,value);//recursively travel right
    }
    return b;
  }	
  
    //to print the values
	void print()
	{
	  rbt<T,K>* r=head;
	  inorderR(r);
	}
	
	//returns size of value
	int size()
	{
	  return size1;
	}
	
	// search for a key
	bool containsKey(T key)
	{
		rbt<T,K>* temp=head; 
		while(temp!=NULL && temp->key!=key)
	  {
	    if(temp->key>key)
	    {
	     // trailing=temp;
	      temp=temp->left;
      }
	    else
	    {
	      //trailing=temp;
	      temp=temp->right;
	    }
	  }
	  
	  if(temp==NULL)
	    return false;
	  else
	    return true;
	}
	
	
	// searches for a value
	bool containsValue(K value)
	{
		bool b=false; 
		char* c="hello";
		
		//to check whether its string or not
		if( typeid(value) == typeid(c))
		{
		  b=search(head,0,value);
		}
		else
		{
		  b=search(head,1,value);
	  }
	  
	  return b;//returns if present or not
	}
	
	// returns value for the key
	K get(T key)
	{
	  rbt<T,K>* temp=head; 
		while(temp!=NULL && temp->key!=key)
	  {
	    if(temp->key>key)
	    {
	     // trailing=temp;
	      temp=temp->left;
      }
	    else
	    {
	      //trailing=temp;
	      temp=temp->right;
	    }
	  }
	  
	  if(temp==NULL)
	    return (K)NULL;
	  else
	    return temp->value;
	}
	
  //returns least value from list
  rbt<T,K>* firstEntry()
  {
    rbt<T,K>* temp=head;
    
    while(temp->left!=NULL)
      temp=temp->left;
    
    return temp;
  }
  
  //returns max value
  rbt<T,K>* lastEntry()
  {
    rbt<T,K>* temp=head;
    
    while(temp->right!=NULL)
      temp=temp->right;
    
    return temp;
  }
  
    
   rbt<T,K>* lowerEntry(T key)  //greatest key strictly less than the given key
   {
    rbt<T,K>* temp=head;
 
		while(temp->right!=NULL )
	  {
	    if(temp->key>key)
	    {
	     // trailing=temp;
	      temp=temp->right;
	      
        }
	    else
	    {
	        //break;
	      //trailing=temp;
	      temp=temp->right;
	    }
	  
	  /*if(temp==NULL)
	    return NULL;
	  else
	  {
	    temp=temp->left;
	    while(temp->right!=NULL)
	      temp=temp->right;
	      
	    return temp;
    }*/
	}    
    if(temp->key>key)
    return temp;
    else
    return NULL;
  }
  
 
  
  
   rbt<T,K>* higherEntry(T key)  // least key greater than or equal to the given key
  {
    rbt<T,K>* temp=head;
 
		while(temp!=NULL )
	  {
	    if(temp->key>key)
	    {
	     // trailing=temp;
	        break;
	     // temp=temp->left;
      }
	    else
	    {
	      //trailing=temp;
	      
	      temp=temp->right;
	    }
	  }
	  
	/*  if(temp==NULL)
	    return NULL;
	  else
	  {
	    temp=temp->right;
	    while(temp->left!=NULL)
	      temp=temp->left;
	      
	    return temp;
    }*/
	    
    if(temp->key>key)
    return temp;
    else
    return NULL;
  }

void delete_rbt(int data,rbt<T,K>* t)    //  t is to be deleted, data is the key to be deleted
{
  if(t==NULL)   // node to be deleted is not given
  {
    t=head;
    
    while(t!= NULL && t->key!=data) 
    {
      if(t->key>data)
        t=t->left;
      else
        t=t->right;
    }
    
    if(t==NULL)
    {
      cout<<"key is not present";
      return ;
    }
    else if(t == head && t->left==NULL && t->right==NULL)   // node deleted is the head and its the only node
    {
      delete t;
      head=NULL;
      return ; 
    }
    
  }
  
   
  if( (t->left==NULL && t->right==NULL)  ) // leaf node
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
    else      // leaf node is black so both u,v is black
    {
      if(t->parent->left!=NULL && t->parent->left==t) // t(leaf node) is left child
      {
        if(t->parent->right!=NULL && ( (t->parent->right->left!=NULL && t->parent->right->left->color=='r') ||
            (t->parent->right->right!=NULL && t->parent->right->right->color=='r') ) ) // sibling is b and atleast one of its child is r
        {
            
          if(t->parent->right->right!=NULL)  // sibling has right  child so RRb
          {
            if(t->parent->color=='b')
              t->parent->right->right->color='b';
            rotate_left(t->parent->right,0);
          }
          else  //sibling has a left child so RLb 
          {
            if(t->parent->color=='b')
              t->parent->right->left->color='b';
            else
              t->parent->color='b';
            rotate_right(t->parent->right->left,0);
            rotate_left(t->parent->right,0);
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
            rotate_left(t->parent->right,0);
          else  //RLb
          { 
            rotate_right(t->parent->right->left,0);
            rotate_left(t->parent->right,0);
          }
          
          if( (t->parent->right->left!=NULL && t->parent->right->left->color=='r') &&   // sibling's left child has 2 r childs
              (t->parent->right->right!=NULL && t->parent->right->right->color=='r') )
          {
            rotate_left(t->parent->right,1);
            
            t->parent->color='b';
            t->parent->parent->right->color='b';
            if(t->parent->parent!=head)
               t->parent->parent->color='r';
            
            
          }
          else if( t->parent->right->right!=NULL && t->parent->right->right->color=='r' ) // sibling's left child has only 1 r right child
          {
           
            rotate_left(t->parent->right,1);  // LLb
            
          }
          else if( t->parent->right->left!=NULL && t->parent->right->left->color=='r' ) // sibling's left child has only 1 r left child
          {
            rotate_right(t->parent->right->left,0);  //LRb  
            rotate_left(t->parent->right,1); 
          }
         
          t->parent->left=NULL;
          delete t;
          
          
        }
        else if(t->parent->color=='r' && t->parent->right!=NULL && t->parent->right->color=='b' &&
                (t->parent->right->left==NULL || t->parent->right->left->color=='b') && (t->parent->right->right == NULL || 
                t->parent->right->right->color=='b') )   // parent is red and sibling and its childs are b
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
          rbt<T,K>* temp=t;

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
      else  // t(leaf node) is right child
      {
        if(t->parent->left!=NULL && ( (t->parent->left->left!=NULL && t->parent->left->left->color=='r') ||
          (t->parent->left->right!=NULL && t->parent->left->right->color=='r') ) ) // sibling is b and atleast one of its child is r
        {
            
          if(t->parent->left->left!=NULL)  // sibling has left  child so LLb
          {
            if(t->parent->color=='b')
              t->parent->left->left->color='b';
            rotate_right(t->parent->left,0);
          }
          else  //sibling has a right child so LRb 
          {
            if(t->parent->color=='b')
              t->parent->left->right->color='b';
            else 
              t->parent->color='b';
            rotate_left(t->parent->left->right,0);
            rotate_right(t->parent->left,0);
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
            rotate_right(t->parent->left,0);
          else  //LRb
          { 
            rotate_left(t->parent->left->right,0);
            rotate_right(t->parent->left,0);
          }
          
          if( (t->parent->left->left!=NULL && t->parent->left->left->color=='r') &&   // sibling's left child has 2 r childs
              (t->parent->left->right!=NULL && t->parent->left->right->color=='r') )
          {
            rotate_right(t->parent->left,1);
            
            t->parent->color='b';
            t->parent->parent->left->color='b';
            if(t->parent->parent!=head)
               t->parent->parent->color='r';
            
          }
          else if( t->parent->left->left!=NULL && t->parent->left->left->color=='r' ) // sibling's left child has only 1 r left child
          {
            rotate_right(t->parent->left,1);
            
          }
          else if( t->parent->left->right!=NULL && t->parent->left->right->color=='r' ) // sibling's left child has only 1 r right child
          {
            rotate_left(t->parent->left->right,0);
            rotate_right(t->parent->left,1);
          }
 
          t->parent->right=NULL;
          delete t;
          
          
        }
        else if(t->parent->color=='r' && t->parent->left!=NULL && t->parent->left->color=='b' &&
                (t->parent->left->left==NULL || t->parent->left->left->color=='b') && (t->parent->left->right == NULL || 
                t->parent->left->right->color=='b') )   //parent is red and sibling and its childs are b
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
          rbt<T,K>* temp=t;
          
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

        rbt<T,K>* temp=t->right;  //temp will be its successor
        
        while(temp->left!=NULL)
          temp=temp->left;
        
        t->key=temp->key;
        t->value=temp->value;
        
        delete_rbt(0,temp);
        
    } 
    else  //it has a left child
    {
      rbt<T,K>* temp=t->left;   //temp will be its predeccessor
        
        while(temp->right!=NULL)
          temp=temp->right;
        
            t->key=temp->key;
        t->value=temp->value;
        
        delete_rbt(0,temp);
    }
  }
  else  // it has two childs
  {
    rbt<T,K>* temp=t->right;  //temp will be its successor
        
        while(temp->left!=NULL)
          temp=temp->left;
        
            t->key=temp->key;
        t->value=temp->value;   
        
        delete_rbt(0,temp);
  }
 
}
  
  
};





int main()
{
  TreeMap <int,char*>* h1=new TreeMap<int,char*>();//new treemap class template created
  
  h1->put(10,"bat");
  h1->put(20,"cat");
  h1->put(30,"kaggle");
  h1->put(25,"music");
  h1->put(67,"quad");
  h1->put(56,"tusk");
  h1->put(14,"fat");
  h1->print();
  //containsKey containsValue put get First entry Last entry lowerentry  
  cout<<"size "<<h1->size()<<endl;// returns size of value
  cout<<"contains ce "<<h1->containsValue("ce")<<endl;//contains value function is called and checked for that value
  cout<<"contains fat "<<h1->containsValue("fat")<<endl;
  cout<<"get value at 10 "<<h1->get(10)<<endl;//returns value at 10th node
  rbt<int,char*>* b=h1->firstEntry();
  cout<<"first entry "<<b->key<<b->value<<endl;
  b=h1->lastEntry();
  cout<<"last entry "<<b->key<<b->value<<endl;
  b=h1->lowerEntry(60);
  cout<<"lower entry highest less than 60 "<<b->key<<" "<<b->value<<endl;
  b=h1->higherEntry(25);
  cout<<"higher entry least value greater than 25 "<<b->key<<" "<<b->value<<endl;
  cout<<"deleting 25 from list\n";
  h1->delete_rbt(25,NULL);
  h1->print();
  return 0;
}



rbtp.cpp
Page 14 of 15 Page 13 of 15
