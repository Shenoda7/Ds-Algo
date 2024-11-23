#include<bits/stdc++.h>
#include<iostream>
using namespace std;

#define ll long long
#define ld long double
#define loop(n) for(int i = 0; i < n; ++i)

class Queue{
private:
    int Size { };
    int Front { 0 };
    int Rear { 0 };
    int added_elements { };
    int* arr { };

public:
    Queue(int sz = 0){
        Size = sz;
        Front = Rear = added_elements = 0;
        arr = new int[Size];
    }

    ~Queue(){
        delete[] arr;
    }

    void display(){
        cout << "Front: " << Front << ", Rear: " << Rear << "\n";
        if(isFull())
            cout << "is Full.";
        else if(isEmpty()){
            cout << "is Empty.\n";
            return;
        }
        cout << "\n";
        for(int cur = Front, step = 0; step < added_elements;
                ++step, cur = next(cur))
            cout << arr[cur] << " ";
        cout << "\n\n";
    }

    int next(int pos){
        //return (pos + 1) % Size;
        ++pos;
        if(pos == Size)
            pos = 0;
        return pos;
    }

    int prev(int pos){
        --pos;
        if(pos == -1)
            pos = Size - 1;
        return pos;
    }

    bool isEmpty(){
        return added_elements == 0;
    }
    bool isFull(){
        return added_elements == Size;
    }

   void enqueue(int value){
        assert(!isFull());
        arr[Rear] = value;
        Rear = next(Rear);
        added_elements++;
    }

    int dequeue(){
        assert(!isEmpty());
        int value = arr[Front];
        Front = next(Front);
        --added_elements;
        return value;
    }

    int get_added_elements(){
        return added_elements;
    }

    int front_val(){
        return arr[Front];
    }
};


void insert_bottome(int x){
    if()
}

int main() {

    Stack stk(3);//here's the error
    stk.push(10);
    stk.push(20);
    stk.push(30);

    while(!stk.isEmpty()){
        cout << stk.peek() << " ";
        stk.pop();
    }

    return 0;
}
