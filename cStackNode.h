#pragma once
#include <utility>
#include "Node.h"
#include <iostream>
#include "data.h"

class circularStack{
protected:
    int front=-1,rear=-1;
    int size=5;
    data array[4];
public:
    void push(data);
    data pop();
};

void circularStack::push(data d){
    if(rear == -1){
        front=rear=0;
    }else if( front == 0 && rear == (size-1) ){
        rear=0;
        delete array[front].node;
        front=1;
        //TODO: meory leak
    }else if( (rear+1)%size == front ){
        delete array[front].node;
        front = (front+1)%size;
        //TODO: meory leak
        rear = (rear+1)%size;
    }else{
        rear = (rear+1)%size;
    }
    // *std::cout<<rear<<"  "<<d.operation<<std::endl;
    array[rear] = d;
}

data circularStack::pop(){
    if( rear == -1 ){
        data temp;
        temp.node=NULL;
        temp.operation=-1;
        temp.location=-1;
        return temp;
    }
    data item=array[rear];
    if( front == rear ){
        front = rear = -1;
    }else if(rear == 0){
        rear=size-1;
    }else{
        rear--;
    }
    return item;
}

