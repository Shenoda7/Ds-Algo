#include <iostream>
#include<assert.h>

using namespace std;

struct Node{
    int data;
    int index;
    Node* next{ };
    Node* prev{ };

    Node(int data, int index) :
        data(data), index(index){
        }

//    void Set(Node* next, Node* prev){
//        this->next = next;
//        this->prev = prev;
//    }
};

class ArrayLinkedList {

private:
    Node* head { };
    Node* tail { };
    int length = 0;
    int array_length = { };


    void link(Node* first, Node* second){
        if(first)
            first->next = second;
        if(second)
            second->prev = first;
    }

    Node* embed_after(Node* node_before, int data, int index){
        Node* middle = new Node(data, index);
        length++;

        Node* node_after = node_before->next;
        link(node_before, middle);

        if(!node_after)
            tail = middle;
        else
            link(middle, node_after);

        return middle;
    }

    Node* get_index(int index, bool is_create_if_missing){
        Node* prev_index = head;

        while(prev_index->next && prev_index->next->index < index)
            prev_index = prev_index->next;

        bool found = prev_index->next && prev_index->next->index == index;

        if(found)
            return prev_index->next;
        if(!is_create_if_missing)
            return nullptr;

        return embed_after(prev_index, 0, index);
    }

public:
    ArrayLinkedList(int array_length) :
        array_length(array_length){

        head = tail = new Node(0, -1);
        ++length;
     }

    ~ArrayLinkedList(){
        for(Node* cur = head; cur;){
            Node* tmp = cur;
            cur = cur->next;
            delete tmp;
        }
    }

    void print_array(){
        Node* cur = head->next;

        for(int c = 0; c < array_length; ++c){
            if(cur && cur->index == c){
                cout << cur->data << " ";
                cur = cur->next;
            } else {
                cout << "0 ";
            }
        }
        cout << "\n";
    }

    void print_array_non_zero(){
        for(Node* cur = head->next; cur; cur = cur->next)
               cout << cur->data << " ";
        cout << "\n";
    }

    void set_value(int value, int pos){
        get_index(pos, true)->data = value;
    }

    int get_value(int pos){
        Node* node = get_index(pos, false);
        if(!node)
            return 0;
        return node->data;
    }

    void add(ArrayLinkedList &other) {
		assert(array_length == other.array_length);

		// Iterate on the other first, and add it to the current one
		for (Node* other_cur = other.head->next; other_cur; other_cur = other_cur->next) {
			get_index(other_cur->index, true)->data += other_cur->data; // **
		}
		// ** We can make this function more efficient, but let's keep simple
	}

};

int main(){

    ArrayLinkedList arr(10);
    arr.print_array();

    arr.set_value(30, 1);
    arr.set_value(60, 3);
    arr.set_value(50, 5);
    arr.set_value(80, 6);
    arr.set_value(20, 2);
    arr.set_value(70, 7);
    arr.set_value(40, 4);
    arr.set_value(44, 9);
    arr.set_value(600, 8);
    arr.print_array();

    arr.print_array_non_zero();
    cout << arr.get_value(7) << "\n";

    ArrayLinkedList arr2(10);
    arr2.set_value(1, 4);
    arr2.set_value(3, 7);
    arr2.set_value(4, 6);

    arr.add(arr2);

    arr.print_array();
    return 0;
}
