#include <iostream>
#include <assert.h>

using namespace std;

class Stack{
private:

    struct Node{
        int data { };
        Node* next { };

        Node(int data) : data(data) {
        }
    };

    Node* head { nullptr };

    bool Empty(){
        return !head;
    }

public:
    void display(){
        for(Node* cur = head; cur; cur = cur->next)
            cout << cur->data << " ";
        cout << "\n";
    }

    void push(int value){
        //by design always new node = head
        //great match with stack
        Node* item = new Node(value);
        item->next = head;
        head = item;
    }

    int pop(){
        assert(!Empty());
        int element = head->data;
        Node* temp = head;
        head = head->next;
        delete temp;
        return element;
    }

    int peek(){
        assert(!Empty());
        int element = head->data;
        return element;
    }

    void delete_middle(){
        if(!head || !head->next){
            delete head;
            return;
        }
        Node* slow = head;
        Node* fast = head;
        Node* prev{};

        while(fast != nullptr && fast->next != nullptr){
            prev = slow;
            slow = slow->next;
            fast = fast->next->next;
        }
        prev->next = slow->next;
        delete slow;
    }
};


int main(){
    Stack st;
    st.push(1);
    st.push(2);
    st.push(3);
    st.push(4);
    st.push(5);

    st.display();
    st.delete_middle();
    st.display();
    cout << "Hello world!" << endl;
    return 0;
}
