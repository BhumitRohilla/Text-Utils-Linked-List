#include<iostream>
#include<string>
#include<conio.h>
#include<fstream>
#include "Node.h"
#include "cStackNode.h"
#include<utility>
#include "Node.h"
#include "rStack.h"
using std::string;



class mstring{
    static string removeSpaces(string);
    circularStack undoStack;
    circularRStack redoStack;
    Node* head=NULL;
public:
    void insert();
    void append();
    void update(string,string);
    void save();
    void undo();
    void redo();
    void push(int,Node*,int);
    void print();
    void del(string);
    int search(string);
};

string mstring::removeSpaces(string str){
    string result="";
    for(char i:str){
        if(i!=' '){
            result+=i;
        }
    }
    return result;
}

void mstring::insert(){
    push(0,head,-1);
    head=NULL;
    Node* temp=NULL;
    string str="";
    while (true)
    {
        char test = getc(stdin);
        if(test=='`'){
            //*std::cout<<"End the file"<<std::endl;
            str=removeSpaces(str);
            if(str!=""){
                if( head == NULL ){
                    this->head= new Node;
                    temp=head;
                }else{
                    temp->next= new Node;
                    temp=temp->next;
                }
                temp->data=str;
                str="";
            }
            return ;
        }else if(test=='\n'||test==' '){
            str=removeSpaces(str);
            if(str!=""){
                if(head==NULL){
                    this->head= new Node;
                    temp=head;
                }else{
                    temp->next= new Node;
                    temp=temp->next;
                }
                temp->data=str;
                str="";
            }
        }else{
            str+=test;
        }
    }
}

void mstring::update(string word , string wordToAdd){
    if(this->head == NULL){
        std::cout<<"String is empty"<<std::endl<<std::endl;
        return ;
    }

    int index = search(word);

    if(index==-1){
        std::cout<<"Word not found"<<std::endl<<std::endl;
        return ;
    }

    Node* wordToEn=new Node;
    push(1,wordToEn,index);
    if(index==0){
        wordToEn->data=wordToAdd;
        wordToEn->next=this->head;
        this->head=wordToEn;
    }else{
        Node *temp=head;
        for(int i=0;i<index-1;++i){
            temp=temp->next;
        }
        wordToEn->data = wordToAdd;
        wordToEn->next=temp->next;
        temp->next=wordToEn;
    }

}

void mstring::print(){
    Node *temp=this->head;
    if(temp==NULL){
        std::cout<<"String is empty "<<std::endl;
        return ;
    }
    while(temp!=NULL){
        std::cout<<temp->data;
        if(temp->next!=NULL){
            std::cout<<" ";
        }
        temp=temp->next;
    }
    std::cout<<std::endl;
}

void mstring::append(){
    if(this->head==NULL){
        insert();
        return ;
    }
    string str="";
    Node* temp=head;
    int count=0;
    while(temp->next!=NULL){
        temp=temp->next;
        count++;
    }
    push(2,temp,count);
    while(true){
        char test = getc(stdin);
        if(test == '`'){
            str=removeSpaces(str);
            if(str!=""){
                temp->next=new Node;
                temp=temp->next;
                temp->data=str;
            }
            return ;
        }else if( test == '\n' || test==' '){
            if(str!=""){
                temp->next=new Node;
                temp=temp->next;
                temp->data=str;
                str="";
            }
        }else{
            str+=test;
        }
    }
}

int mstring::search(string searchString){
    if(this->head==NULL){
        return -11;
    }else if(searchString==""){
        return -12;
    }
    Node *temp=head;
    int count=0;
    while(temp!=NULL && temp->data!=searchString){
        temp=temp->next;
        count++;
    }
    if(temp==NULL){
        return -1;
    }
    return count;
}

void mstring::save(){
    string fName;
    std::cin>>fName;
    std::ofstream out(fName);
    if(head==NULL){
        out << "File is Null";
    }
    Node *temp=head;
    while(temp!=NULL){
        out<<temp->data;
        out<<" ";
        temp=temp->next;
    }
}

void mstring::del(string word){
    int index = this->search(word);
    if(index==-11){

    }else if(index==-12){

    }else if(index == -1){

    }else{
        Node* temp=this->head;
        if(index == 0){    // Delete from the start
            push(3,head,0);
            this->head=this->head->next;
            return ;
        }
        for(int i=0;i<index-1;++i){   // Delete from other 
            temp=temp->next;
        }
        push(3,temp->next,index);
        temp->next=temp->next->next;
    }
}



void mstring::push(int num, Node *node,int location){
    data temp;
    temp.node = node;
    temp.operation = num;
    temp.location = location;
    this->undoStack.push(temp);
    this->redoStack.empty();
}


void mstring::undo(){
    data temp=this->undoStack.pop();
    getch();
    if(temp.operation==-1){
        std::cout<<"Undo Stack is empty"<<std::endl<<std::endl;
        return ;
    }
    getch();
    switch (temp.operation)
    {
        case 0:{
            data rtemp;
            rtemp.operation=0;
            rtemp.node=this->head;
            rtemp.location=-1;
            this->redoStack.push(rtemp);
            this->head=temp.node;
            break;}
        case 1:{
            data rtemp;
            rtemp.operation=3;
            rtemp.location=temp.location;
            rtemp.node = temp.node;
            std::cout<<std::endl<<rtemp.operation<<"  "<<rtemp.location<<std::endl;
            this->redoStack.push(rtemp);
            Node * itr=this->head;
            if(temp.location == 0){
                this->head=this->head->next;
            }else{
                while(itr->next != temp.node ){
                    itr=itr->next;
                }
                itr->next=itr->next->next;
            }
            break;
        }
        case 2:{
            data rtemp;
            rtemp.operation=2;
            rtemp.location=temp.location;
            rtemp.node = temp.node->next;
            this->redoStack.push(rtemp);
            Node *itr = this->head;
            while(itr!=temp.node){
                itr=itr->next;
            }
            itr->next=NULL;
            break;
        }
        case 3:{
            data rtemp;
            rtemp.operation = 1;
            rtemp.node=temp.node;
            rtemp.location=temp.location;
            this->redoStack.push(rtemp);
            int count=temp.location;
            Node *itr = this->head;
            if(temp.location == 0){
                temp.node->next=this->head;
                this->head = temp.node;
            }else{
                while(count!=0){
                    itr=itr->next;
                    count--;
                }
                temp.node->next = itr->next;
                itr->next = temp.node;
            }
            break;
        }
        default:
            break;
    }
}

void mstring::redo(){
    data temp = redoStack.pop();
    if(temp.operation == -1){
        std::cout<<"Redo Stack is empty"<<std::endl;
        return ;
    }
    switch (temp.operation)
    {
        case 0:{
            data utemp;
            utemp.operation=0;
            utemp.node = this->head;
            utemp.location = -1;
            this->undoStack.push(utemp);
            this->head=temp.node;
            break;
        }
        case 1:{
            data utemp;
            utemp.operation = 3;
            utemp.location = temp.location;
            utemp.node = temp.node;
            std::cout<<std::endl<<utemp.operation<<" "<<utemp.location<<std::endl;
            this->undoStack.push(utemp);
            Node *itr = this->head;
            if(temp.location == 0){
                this->head = this->head->next;
            }else{
                while(itr->next != temp.node){
                    itr=itr->next;
                }
                itr->next = itr->next->next;
            }
            break;
        }
        case 2:{
            data utemp;
            utemp.operation=2;
            utemp.location=temp.location;
            Node* itr=this->head;
            while(itr->next!=NULL){
                itr=itr->next;
            }
            utemp.node=itr;
            this->undoStack.push(utemp);
            itr->next=temp.node;
            break;
        }
        case 3:{
            data utemp;
            utemp.operation=1;
            utemp.node = temp.node;
            utemp.location = temp.location;
            this->undoStack.push(utemp);
            int count=temp.location;
            Node * itr = this->head;
            if(temp.location == 0){
                temp.node->next = this->head;
                this->head=temp.node;
            }else{
                while(count!=0){
                    itr=itr->next;
                    count--;
                }
                temp.node->next=itr->next;
                itr->next=temp.node;
            }
            break;
        }
    
    default:
        break;
    }

}

int main(){
    mstring file;
    std::cout<<"NOTE:   use ` for ending string input"<<std::endl<<std::endl;
    while (true)
    {
        std::cout<<"*******************************************************"<<std::endl;
        std::cout<<"* Select Options"<<std::endl<<"* i for insert"<<std::endl<<"* u for update"<<std::endl<<"* a for append"<<std::endl<<"* s for search"<<std::endl<<"* d for delete"<<std::endl<<"* p for print data"<<std::endl<<"* o for undo"<<std::endl<<"* r for redo"<<std::endl<<"* x for save"<<std::endl<<"* e for exit"<<std::endl;
        std::cout<<"*******************************************************"<<std::endl;
            //string buffer;
        switch (getch())
        {
            case 'i':{
                std::cout<<"Insert Mode"<<std::endl;
                file.insert();
                break;
            }
            case 'u':{
                std::cout<<"Update Mode"<<std::endl;
                std::cout<<"Enter word before you want to add "<<std::endl;
                string word;std::cin>>word;
                std::cout<<"Enter word you want to enter"<<std::endl;
                string wordToSearch; std::cin>>wordToSearch;
                file.update(word,wordToSearch);
                break;
            }
            case 'a':{
                std::cout<<"Append Mode"<<std::endl;
                file.append();
                break;
            }
            case 's':{
                std::cout<<"Search Mode"<<std::endl;
                file.print();
                string eleToSearch;
                std::cin>>eleToSearch;
                int result=file.search(eleToSearch);
                if( result == -11 ){
                    std::cout<<"String is empty"<<std::endl;
                }else if( result == -12 ){
                    std::cout<<"Word is empty"<<std::endl;
                }else if(result == -1){
                    std::cout<<"Word not found"<<std::endl;
                }else{
                    std::cout<<"Word found at:  "<<result<<std::endl;
                }
                break;
            }
            case 'd':{
                std::cout<<"Delete Mode"<<std::endl;
                std::cout<<"Enter word you want to delete"<<std::endl;
                string str;std::cin>>str;
                file.del(str);
                break;
            }
            case 'p':{
                std::cout<<"Printing Mode"<<std::endl;
                file.print();
                break;
            }
            case 'o':{
                std::cout<<"Undo Mode"<<std::endl;
                file.undo();
                break;
            }
            case 'r':{
                std::cout<<"Redo Mode"<<std::endl;
                file.redo();
                break;
            }
            case 'x':{
                std::cout<<"Save Mode"<<std::endl;
                file.save();
                break;
            }
            case 'e':{
                exit(0);
                break;
            }
            case '/':{
                system("CLS");
            }
        }
        fflush(stdin);
   }
}