#include<iostream>
#include<fstream>
#include<string>
#include<stdio.h>
using namespace std;

int found=0;

class node{
    public:
        char info;
        string Word;
        class node* ptrs[256];
        node(){
            for(int i=0;i<256;i++){
                ptrs[i]=NULL;
            }

			info=0;
			 Word="";
			 //Word=NULL;
        }
};


void insertword(string word,int pos,class node *root){
    if(word.length()==pos){
        root->Word=word;
        return;
    }
    if( root-> ptrs[word[pos]]==NULL ){
        node *newnode;
        newnode= new node;
        newnode->info=word[pos];
        root->ptrs[word[pos]]=newnode;
        insertword(word,pos+1,root->ptrs[word[pos]]);
    }
    else
        insertword(word,pos+1,root->ptrs[word[pos]]);
}

void find(string key,int pos, class node * root){
    if((key != root->Word) && (root->ptrs[key[pos]] != NULL))
        find(key,pos+1,root->ptrs[key[pos]]);
    else if(key==root->Word){
        cout<<"The spelling of the word '"<<root->Word<<"' is correct"<<endl;
        found=1;
    }
}

void printall(class node * root){
    for(int i=0;i<256;i++)
        if(root->ptrs[i]!=NULL){
            printall(root->ptrs[i]);
        }
    if(root->Word != "")
        cout<<" -> "<<root->Word<<endl;
}

void suggest(string key,int pos, class node * root){
    if((key != root->Word) && (root->ptrs[key[pos]] != NULL)){
            suggest(key,pos+1,root->ptrs[key[pos]]);
    }
    else{
            printall(root);
    }
}

int main(){
    ifstream in("wordlist.txt");
    string word,current="",key;
    int ch;
    node *root;
    root = new node;
    while(in){
        in>>word;
        insertword(word,0,root);
    }
    in.close();
    cout<<endl<<"Trie Construction Successful"<<endl;
    //printall(root);

    cout<<"Enter the word to be searched for : ";
    cin>>key;
    find(key,0,root);
    //cout<<"Do u want to continue ?if yes enter 1 else 0";
        //cin>>ch;

    if(!found){
        cout<<endl<<"The spelling is , Possible suggestions are :"<<endl;
        suggest(key,0,root);


    }
//getch();

    return 0;
    //getch();
}
