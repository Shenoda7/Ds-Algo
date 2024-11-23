#include <iostream>
#include <bits/stdc++.h>

using namespace std;

struct Node{
    int data;
    Node* next{};
    Node* prev{};

    Node(int data) : data(data){}

    void Set(Node* next, Node* prev){
        this->next = next;
        this->prev = prev;
    }
};

class DoublyLinkedList{
private:
    Node* head { nullptr };
    Node* tail { nullptr };
    Node* prev { nullptr };
    int length = 0;

public:

    DoublyLinkedList(){
    }
    DoublyLinkedList(const DoublyLinkedList&) = delete;
    DoublyLinkedList &operator=(const DoublyLinkedList &another) = delete;

    ~DoublyLinkedList(){
        for(Node* cur = head; cur;){
            Node* tmp = cur;
            cur = cur->next;
            delete tmp;
        }
    }
    /////////////////debugging////////////////////////
    vector<Node*> debug_data;
    void debug_add_node(Node* node){
        debug_data.push_back(node);
    }

    void debug_remove_node(Node* node){
        auto it = find(debug_data.begin(), debug_data.end(), node);
        if(it == debug_data.end())
            cout << "Node does not exist.\n";
        else
            debug_data.erase(it);

    }

    void debug_verify_data_integrity(){
        if(length == 0){
            assert(head == nullptr);
            assert(tail == nullptr);
        }
        else{
            assert(head != nullptr);
            assert(tail != nullptr);
            if(length == 1)
                assert(head == tail);
            else
                assert(head != tail);

            assert(!tail->next);
        }
        int len = 0;
        for(Node* cur = head; cur; cur = cur->next, len++)
            assert(len < 10000);

        assert(length == len);
        assert(length == (int)debug_data.size());
    }

    string debug_to_string(){
        if(length == 0)
            return "";
        ostringstream oss;
        for(Node* cur = head; cur; cur = cur->next) {
            oss << cur->data;
            if(cur->next)
                oss << " ";
        }
        return oss.str();
    }
    ////////////functions////////////////


    void print_reversed(){
        for(Node* cur = tail; cur; cur = cur->prev)
            cout << cur->data << " ";
        cout << "\n";
    }

    void print(){
        for(Node* cur = head; cur; cur = cur->next)
            cout << cur->data << " ";
        cout << "\n";
    }

    void link(Node* first, Node* second){
        if(first)
            first->next = second;
        if(second)
            second->prev = first;

    }

    void insert_end(int value){
        length++;
        Node* new_node = new Node(value);
        new_node->next = nullptr;

        if(!head)
            head = tail = new_node;
        else{
            link(tail, new_node);
            tail = new_node;
        }
        debug_add_node(new_node);
        debug_verify_data_integrity();
    }

    void insert_front(int value){
        length++;
        Node* new_node = new Node(value);

        if(!head){
            head = tail = new_node;
        }
        else {
            link(new_node, head);
            head = new_node;
        }
        debug_add_node(new_node);
        debug_verify_data_integrity();
    }

    void embed_after(Node* before, int value){
        Node* middle = new Node(value);
        Node* after = before->next;
        ++length;
        debug_add_node(middle);

        link(before, middle);
        link(middle, after);

    }

    void insert_sorted(int value){
        if(!length || head->data >= value)
            insert_front(value);
        else if(tail->data <= value)
            insert_end(value);
        else{
            for(Node* cur = head; cur; cur = cur->next){
                if(cur->data >= value){
                    embed_after(cur->prev, value);
                    break;
                }
            }
        }
        debug_verify_data_integrity();
    }

    void delete_node(Node* node){
        --length;
        debug_remove_node(node);
        delete node;
    }

    void delete_end(){
        if(!head){
            cout << "List is empty.\n";
            return;
        }
        Node* prv_tail = tail->prev;
        delete_node(tail);

        tail = prv_tail;

        if(tail)
            tail->next = nullptr;
        else if(!length)
            tail = nullptr;

        debug_verify_data_integrity();
    }

    void delete_front(){
        if(!head){
            cout << "List is empty.\n";
            return;
        }
        Node* after_head = head->next;
        delete_node(head);

        head = after_head;

        if(head)
            head->prev = nullptr;
        else if(!length)
            tail = nullptr;

        debug_verify_data_integrity();
    }

    Node* delete_and_link(Node* cur){
        Node* ret = cur->prev;
        link(cur->prev, cur->next);
        delete_node(cur);


        return ret;
    }

    void delete_node_with_key(int key){
        if(!length)
            return;
        else if(head->data == key)
            delete_front();
        else{
            for(Node* cur = head; cur; cur = cur->next){
                if(cur->data == key){
                    cur = delete_and_link(cur);

                    if(!cur->next) //if we removed last node
                        tail = cur;

                    break;
                }
            }
        }
    }

    void delete_all_key(int key){
        if(!length)
            return;

        insert_front(-key);

        for(Node* cur = head; cur;){
            if(cur->data == key){
                cur = delete_and_link(cur);

                if(!cur->next)
                    tail = cur;
            }
            else{
                cur = cur->next;
            }
        }
        delete_front();
    }

    void delete_even_positions(){
        if(length <= 1)
            return;

        for(Node* cur = head; cur && cur->next; cur = cur->next){
            delete_and_link(cur->next);

            if(!cur->next){
                tail = cur;
            }
        }
        debug_verify_data_integrity();
    }

    void delete_odd_positions(){
        insert_front(-1);
        delete_even_positions();
        delete_front();

        debug_verify_data_integrity();
    }

    typedef Node* Lnode;
    bool is_palindrome(){
        if(length <= 1)
            return true;

        int len = length / 2;
        Lnode start {head}, eend {tail};

        while(len--){
            if(start->data != eend->data)
                return false;
            start = start->next;
            eend = eend->prev;
        }
        return true;
    }

    Node* get_middle(){
        if(!head){
            return nullptr;
        }
        Node* slow = head;
        Node* fast = head;

        while(fast != nullptr && fast->next != nullptr){
            slow = slow->next;
            fast = fast->next->next;
        }

        return slow;
    }

    void delete_middle(){
        if(!head || head == nullptr){
            delete head;
            return;
        }
        Node* middle = get_middle();
        delete_and_link(middle->prev, middle->next);
    }
};

void test1(){
    DoublyLinkedList list1;

    list1.insert_end(1);
    list1.insert_end(4);
    list1.insert_end(1);
    list1.insert_end(4);
    list1.insert_end(1);

    cout << list1.is_palindrome() << "\n";
    list1.print();
    string expected = "1 4 1 4 1";
    string result = list1.debug_to_string();
    if(expected != result){
        cout << "no match:\nExpected: " <<
                expected << "\nResult: " << result << "\n";
        assert(false);
    }
}
//
//void test2(){
//    DoublyLinkedList list1;
//
//    list1.insert_end(1);
//    list1.insert_end(4);
//    list1.insert_end(1);
//    list1.insert_end(8);
//    list1.insert_end(1);
//
//    list1.delete_even_positions();
//    list1.print();
//
//    string expected = "1 1 1";
//    string result = list1.debug_to_string();
//    if(expected != result){
//        cout << "no match:\nExpected: " <<
//                expected << "\nResult: " << result << "\n";
//        assert(false);
//    }
//}
//
//void test3(){
//    DoublyLinkedList list1;
//
//    list1.insert_sorted(1);
//    list1.insert_sorted(4);
//    list1.insert_sorted(1);
//    list1.insert_sorted(8);
//    list1.insert_sorted(1);
//
//    list1.delete_odd_positions();
//    list1.print();
//
//    string expected = "1 4";
//    string result = list1.debug_to_string();
//    if(expected != result){
//        cout << "no match:\nExpected: " <<
//                expected << "\nResult: " << result << "\n";
//        assert(false);
//    }
//}

int main(){
    test1();
//    test2();
//    test3();

    cout << "\n\nNO RTE\n";
    return 0;
}
