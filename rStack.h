#pragma once

#include "Node.h"
#include "data.h"
#include "cStackNode.h"


class circularRStack:public circularStack{
    public:
    void empty(){
        //TODO: handle memory leak
        if(front==rear && rear==-1){
            return;
        }
        while (rear!=-1)
        {
            data temp=this->pop();
            delete temp.node;
        }
    }
};