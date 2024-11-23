#include <iostream>
#include <assert.h>
#include <string>
#include <bits/stdc++.h>
using namespace std;


template<typename T>
class Stack{
private:
    vector<T> arr;
    int top{ };
    int sz { };

public:
    Stack(int sz) : sz(sz) ,top(-1){
        arr.resize(sz);
    }

    void display(){
        for(int i = 0; i <= top; i++)
            cout << arr[i] << " ";
        cout << "\n";
    }

    bool isEmpty(){
        return(top == -1);
    }

    bool isFull(){
        return top == sz - 1;
    }

    bool push(T value){
        arr.push_back(value);
        top++;
        return true;
    }

    T pop(){
        assert(!isEmpty());
        T value = arr.back();
        arr.pop_back();
        top--;
        return value;
    }

    T peek(){
        assert(!isEmpty());
        return arr.back();
    }

    void insert_bottom(int x){
        if(isEmpty()){
            push(x);
        }
        else{
            T cur = pop();

            insert_bottom(x);
            push(cur);
        }
    }

    void reverse_stack(){
        if(isEmpty())
            return;
        T cur = pop();
        reverse_stack();
        insert_bottom(cur);
    }

};

class Queue{
private:
    int sz;
    int added_elements { };
    Stack<int> s1;
    Stack<int> s2;

    void Move(Stack<int> &from, Stack<int> &to){
        while(!from.isEmpty())
            to.push(from.pop());
    }

public:
    Queue(int sz) :
        sz(sz), s1(Stack<int>(sz)), s2(Stack<int>(sz)){
    }
    bool isFull(){
        return added_elements == sz;
    }

    void enqueue(int x){
        assert(!isFull());
        s1.push(x);
        added_elements++;
    }

    int dequeue(){
       assert(!isEmpty());
       if(s2.isEmpty())
            Move(s1, s2);
       int re = s2.pop();
      // Move(s2, s1);
       added_elements--;
       return re;
    }

    bool isEmpty(){
        return added_elements == 0;
    }

};

int main(){

    Queue q(6);
    for(int i = 1; i <= 5; ++i) q.enqueue(i);

    cout << q.dequeue() << "\n";

    while(!q.isEmpty())
        cout << q.dequeue() << " ";


    return 0;
}
