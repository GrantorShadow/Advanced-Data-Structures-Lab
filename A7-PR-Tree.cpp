#include<iostream>

using namespace std;

typedef struct point
{
    int x;
    int y;
}point; 

typedef struct quad_tree
{
    struct quad_tree* nw;
    struct quad_tree* ne;
    struct quad_tree* sw;
    struct quad_tree* se;
    point* data;
    point* bl;
    point* tr;
}quad_tree;


quad_tree* initialise()
{
    quad_tree* t=new quad_tree();
    t->nw=NULL;
    t->ne=NULL;
    t->se=NULL;
    t->sw=NULL;
    t->data=NULL;
    t->bl=new point();
    t->tr=new point();
    return t;
}


void insert(quad_tree* root,point* p)
{
    quad_tree* t=NULL;
    if(p->x >= root->bl->x && p->x <= root->tr->x && p->y >= root->bl->y && p->y <= root->tr->y)
    {
       
        if(root->data==NULL && root->nw==NULL && root->ne==NULL && root->sw==NULL && root->se==NULL)
        {
            root->data=new point();
            root->data->x=p->x;
            root->data->y=p->y;
            return;
        }
        else
        {
            if( (root->bl->x+root->tr->x)/2 > p->x )
            {
                if( (root->bl->y+root->tr->y)/2 > p->y )
                {
      
                    if(root->sw==NULL)
                    {
                    
                        t=initialise();
                        t->bl->x=root->bl->x;
                        t->bl->y=root->bl->y;
                        t->tr->x=(root->bl->x+root->tr->x)/2;
                        t->tr->y=(root->bl->y+root->tr->y)/2;
                       
                        root->sw=t;
                    }
                    //else
                    {
                        insert(root->sw,p);
                    }
                    if(root->data!=NULL)
                    {
                       point* e=root->data;
                        root->data=NULL;
                        insert(root,e);
                    }
                    
                }
                else
                {
        
                    if(root->nw==NULL)
                    {
                        t=initialise();
                        t->tr->x=(root->bl->x+root->tr->x)/2;
                        t->tr->y=root->tr->y;
                        t->bl->x=root->bl->x;
                        t->bl->y=(root->bl->y+root->tr->y)/2;
                      
                        root->nw=t;
                    }
                    //else
                    {
                        insert(root->nw,p);
                    }  
                    if(root->data!=NULL)
                    {
                        point* e=root->data;
                        root->data=NULL;
                        insert(root,e);
                    }  
                }
            }
            else
            {
                if( (root->bl->y+root->tr->y)/2 > p->y )
                {
                    if(root->se==NULL)
                    {
          //              cout<<"se\n";
                        t=initialise();
                        t->bl->x=(root->bl->x+root->tr->x)/2;
                        t->bl->y=root->bl->y;
                        t->tr->x=root->tr->x;
                        t->tr->y=(root->bl->y+root->tr->y)/2;
                        
                        root->se=t;
                        
                    }
                    //else
                    {
                        insert(root->se,p);
                    }
                    if(root->data!=NULL)
                    {
                       
                        point* e=root->data;
                        root->data=NULL;
                        insert(root,e);
                        
                    }
                    
                }
                else
                {
            //        cout<<"ne\n";
                    
                    if(root->ne==NULL)
                    {
                        t=initialise();
                        t->bl->x=(root->bl->x+root->tr->x)/2;
                        t->bl->y=(root->bl->y+root->tr->y)/2;
                        t->tr->x=root->tr->x;
                        t->tr->y=root->tr->y;
                      
                        root->ne=t;
                    }
                    //else
                    {
                        insert(root->ne,p);
                    } 
                    if(root->data!=NULL)
                    {
                        point* e=root->data;
                        root->data=NULL;
                        insert(root,e);
                    }   
                }
            }
            
        }// if
      
    }
     
}


void print(quad_tree* t)
{
    
    if(t->data!=NULL)
    cout<<"data "<<t->data->x<<","<<t->data->y<<endl;
    
    if(t->sw!=NULL)
    print(t->sw);
    if(t->nw!=NULL)
    print(t->nw);
   if(t->ne!=NULL)
    print(t->ne);
    if(t->se!=NULL)
    print(t->se);
}

bool search(quad_tree* root,point* p)
{
    static bool flag=false;
    if(p->x >= root->bl->x && p->x <= root->tr->x && p->y >= root->bl->y && p->y <= root->tr->y)
    {
        
         if(root->data!=NULL && root->data->x==p->x && root->data->y==p->y)
         {
            flag=true;
            return flag;
         }
         if( (root->bl->x+root->tr->x)/2 > p->x )
         {
             if( (root->bl->y+root->tr->y)/2 > p->y )
             {
                if(root->sw!=NULL)
                    search(root->sw,p);
             }
             else
             {
                if(root->nw!=NULL)
                    search(root->nw,p);
             }
         }
         else
         {
             if( (root->bl->y+root->tr->y)/2 > p->y )
             {
                if(root->se!=NULL)
                    search(root->se,p);
             }
             else
             {
                
                if(root->ne!=NULL)
                {
                    search(root->ne,p);}
             }   
         }
         return flag;
    }
}

point* range(quad_tree* root,point* bl,point* tr,int *n)
{
    static point p[100];
    if(p->x >= root->bl->x || p->x <= root->tr->x || p->y >= root->bl->y || p->y <= root->tr->y)
    {
        
         if(root->data!=NULL && root->data->x>=bl->x && root->data->x<=tr->x && root->data->y>=bl->y && root->data->y<=tr->y)
         {
            p[*n].x=root->data->x;
            p[*n].y=root->data->y;
            (*n)++;
            
         }
         if(root->sw!=NULL && !( (root->sw->bl->x>tr->x || root->sw->bl->y>tr->y) && (root->sw->tr->x<bl->x || root->sw->tr->y<bl->y)))
         {
      //     cout<<"sw";
            range(root->sw,bl,tr,n);
         }
         if(root->se!=NULL && !( (root->se->bl->x>tr->x || root->se->bl->y>tr->y) && (root->se->tr->x<bl->x || root->se->tr->y<bl->y)))
         {
        // cout<<"se";
            range(root->se,bl,tr,n);
         }
         if(root->nw!=NULL && !( (root->nw->bl->x>tr->x || root->nw->bl->y>tr->y) && (root->nw->tr->x<bl->x || root->nw->tr->y<bl->y)))
         {
          // cout<<"nw";
            range(root->nw,bl,tr,n);
         }
         if(root->ne!=NULL && !( (root->ne->bl->x>tr->x || root->ne->bl->y>tr->y) && (root->ne->tr->x<bl->x || root->ne->tr->y<bl->y)))
         {
         // cout<<"ne";
            range(root->ne,bl,tr,n);
         }
         return p;
    }
    
}

int main()
{
    int n;
    cin>>n;
    point* p=new point();
    quad_tree* root=initialise();
    root->bl->x=root->bl->y=-128;
    root->tr->y=root->tr->x=128;
    for(int i=0;i<n;i++)
    {
        
        cin>>p->x>>p->y;
        insert(root,p);

    }
    cout<<"tree is\n";
    cout<<"***\n";
    print(root);
    cout<<"***\n";
    p->x=-55;p->y=81;
    cout<<endl<<endl;
    cout<<"searching 55 80 ";
    cout<<search(root,p)<<endl;
    point* x=new point(),*y=new point();
    x->x=-64;x->y=64;y->x=128;y->y=128;
    int n1=0;
    p=range(root,x,y,&n1);

    cout<<"point in range 64,68 and 1228,128 is\n";
    for(int i=0;i<n1;i++)
        cout<<p[i].x<<","<<p[i].y<<endl;
    
    return 0;
}
