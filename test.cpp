#include <iostream>
#include <stdlib.h>

using namespace std;

typedef struct NODE{
    float data;
    struct NODE *next;
    struct NODE *pre;
}linklist,*plinklist;

const int maxsize=6;

class LinkListFun
{
private:
    plinklist head;
    plinklist rear;
public:
    LinkListFun();
    ~LinkListFun();
    plinklist creat(float data);
    void del();
    friend class Stack;

};

class Stack
{
private:
    plinklist top;
    LinkListFun s1;
public:
    Stack():s1()
    {
        cout<<"Stack initialized."<<endl;
    }
    ~Stack()
    {
         cout<<"stack destroyed."<<endl;
    }
    bool isEmpty();
    void push(float a);
    float pop();
};


LinkListFun::LinkListFun()
{
    head = new linklist;
    head->pre = NULL;
    rear = head;
}

LinkListFun::~LinkListFun()
{
    while(rear->pre!=NULL)
    {
        del();
    }
    delete head;
}

plinklist LinkListFun::creat(float data)
{
    plinklist p;
    p = new linklist;
    p->pre = rear;
    rear->next = p;
    rear = p;
    rear->data = data;

}

void LinkListFun::del()
{
    plinklist temp;
    temp = rear->pre;
    delete rear;
    rear = temp;
}


bool Stack::isEmpty()
{
    return (s1.rear==s1.head)?true:false;
}

void Stack::push(float a)
{
   s1.creat(a);
   cout<<a<<" push success!"<<endl;
}

float Stack::pop()
{
    float temp;
    if(isEmpty())
    {
        cout<<"stack is empty!"<<endl;
        exit(1);
    }
    else
    {
        cout<<"pop "<<s1.rear->data<<" success!"<<endl;
        temp = s1.rear->data;
        s1.del();
        return temp;
    }
}

int main()
{
    Stack s1;
    for(int i=0;i<maxsize;i++)
    {
        s1.push(i);

    }
    while(!s1.isEmpty())
    {
        cout<<s1.pop()<<endl;
    }

    return 0;
}

