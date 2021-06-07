#include<iostream>
#include<string>
#include<fstream>
#define A_Size 26
using namespace std;

struct Node{
   struct Node *children[A_Size]; 
   bool isWord;
   Node(){
       isWord=false;
       for(int i=0;i<A_Size;++i){ 
           children[i]=NULL;
       }
   }
};

class Dictionary{
   public:
       Dictionary();
       Dictionary(string file);
       void addWord(string word);
       bool isWord(string word);
       bool isPrefix(string word);
       void printWords(string prefix);
       int wordCount();

private:
       Node *root;
       int numWords;
       void printWordRecursive(Node *temp,string word);
};

Dictionary::Dictionary(){
   root=new Node();
   numWords=0;
}

Dictionary::Dictionary(string file){
   ifstream f(file.c_str());
   if(!f.is_open()){
       cout<<"File can't be opened. Please, make the dictionary empty"<<endl;
       Dictionary();
       
       return;
   }
   
   numWords=0;
   root=new Node();
   string line;
   while(!f.eof()){
       getline(f,line);
       int start=0;
       int end=line.find(" ");
       string word;
       while(end!=string::npos){
           word=line.substr(start,end-start);
           addWord(word);
           start=end+1;
           end=line.find(" ",start);
       }
       
       word=line.substr(start,end);
       addWord(word);
   }
}

void Dictionary::addWord(string word){
   
   if(isWord(word)) return;
   ++numWords;
   Node *temp=root;
   int n=word.length();
   for(int i=0;i<n;++i){
       int index=(int)word[i]-(int)'a';
       if(temp->children[index]==NULL){
           temp->children[index]=new Node();
       }
       temp=temp->children[index];
   }
   
   temp->isWord=true;
}

bool Dictionary::isPrefix(string word){
   
   int n=word.length();
   Node *temp=root;
   for(int i=0;i<n;++i){
       int index=(int)word[i]-(int)'a';
       if(temp->children[index]==NULL)
           return false;
       temp=temp->children[index];
   }
   
   return true;
}

bool Dictionary::isWord(string word){
   
   int n=word.length();
   Node *temp=root;
   for(int i=0;i<n;++i){
       int index=(int)word[i]-(int)'a';
       if(temp->children[index]==NULL)
           return false;
       temp=temp->children[index];
   }
  
   return (temp!=NULL && temp->isWord==true);
}


int Dictionary::wordCount(){

   return numWords; 
}

void Dictionary::printWords(string prefix){
   int n=prefix.length();
   Node *temp=root;
   
   for(int i=0;i<n;++i){
       int index=(int)prefix[i]-(int)'a';
       
       if(temp->children[index]==NULL){
           return;
          
       }
       temp=temp->children[index];
   }
   
   printWordRecursive(temp,prefix);
}

void Dictionary::printWordRecursive(Node *temp,string word){
   
   if(temp->isWord){
       cout<<word<<endl;
   }

   for(int i=0;i<A_Size;++i){
       if(temp->children[i]!=NULL){
           
           printWordRecursive(temp->children[i],word+(char)(97+i));
       }
   }
}

