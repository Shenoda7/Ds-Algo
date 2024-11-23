#include<bits/stdc++.h>
#include<iostream>
using namespace std;

#define ll long long
#define ld long double
#define loop(n) for(int i = 0; i < n; ++i)
#define Shenoda ios_base::sync_with_stdio(false); cin.tie(NULL);

struct Node{
    int data;
    Node* next{};

    Node(int data):data(data){}

    ~Node(){
     //   cout << "Destroy value: " << data << " at address " << this << "\n";
    }
};

class linked_list{
private:
    Node *head{ };
    Node *tail{ };
    int length = 0;
public:
    linked_list() {
    }

    linked_list(const linked_list&) = delete;
    linked_list &operator=(const linked_list &another) = delete;


    ~linked_list(){
       // cout << "Destructor activated.\n";
        for(Node* cur = head; cur;){
            Node* tmp = cur;
            cur = cur->next;
            delete tmp;
        }
    }

    /////////////////FOR DEBUGGING///////////////////
    vector<Node*> debug_data;
    void debug_add_node(Node* node){
        debug_data.push_back(node);
    }
    void debug_remove_node(Node* node){
        auto it = std::find(debug_data.begin(), debug_data.end(), node);
        if(it == debug_data.end())
            cout << "Node does not exist\n";
        else
            debug_data.erase(it);
    }

    int get_size_of_debug(){
        return debug_data.size();
    }
    void debug_verify_data_integrity(){
        if(length == 0){//making sure that the head and tail are in a proper case
            assert(head == nullptr);
            assert(tail == nullptr);
        }else{
            assert(head != nullptr);
            assert(tail != nullptr);
            if(length == 1)
                assert(head == tail);
            else
                assert(head != tail);
            assert(!tail->next);
        }
        int len = 0;//making sure that my length is right
        for(Node* cur = head; cur; cur = cur->next, len++)
            assert(len < 10000);//consider infinite cycle if you linked your list in a wrong way
        assert(length == len);
        assert(length == (int)debug_data.size());
    }

    string debug_to_string(){
        if(length == 0)
            return "";
        ostringstream oss;
        for(Node* cur = head; cur; cur = cur->next){
            oss << cur->data;
            if(cur->next)
                oss << " ";
        }
        return oss.str();
    }

    void debug_print_node(Node* node, bool is_separate = false){
        if (is_separate)
            cout << "Sep: ";
        if (node == nullptr){
            cout << "nullptr\n";
            return;
        }
        cout << node->data << " ";
        if(node->next == nullptr)
            cout << "X ";
        else
            cout << node->next->data << " ";

        if(node == head)
            cout << "head\n";
        else if(node == tail)
            cout << "tail\n";
        else
            cout << "\n";
    }

    void debug_print_list(string msg = "") {
        if(msg != "")
            cout << msg << "\n";
        for(int i = 0; i < (int) debug_data.size(); ++i)
            debug_print_node(debug_data[i]);
        cout << "***********************\n" << flush;
    }



    /////////////////FUNCTIONS//////////////////////////////

    int get_len(){
        return length;
    }
    void print(){
        if(length == 0){
            cout << "List is empty.\n";
            return;
        }
        for(Node* cur = head; cur; cur = cur->next)
            cout << cur->data << " ";
        cout << "\n";
    }

    void insert_end(int value){
        length++;
        Node* new_node = new Node(value);
        new_node->next = nullptr;

        if(!head)
            head = tail = new_node;
        else{
            tail->next = new_node;
            tail = new_node;
        }
        debug_add_node(new_node);
    }

    void insert_front(int value){
        length++;
        Node* new_node = new Node(value);

        new_node->next = head;
        head = new_node;

        if(length == 1)
            tail = head = new_node;

        debug_add_node(new_node);
        debug_verify_data_integrity();
    }

    int Search(int value){
        int idx = 0;
        for(Node* cur = head; cur; cur = cur->next, idx++){
            if(cur->data == value){
                return idx;
            }
        }
        return -1;//not found
    }

    Node* get_nth(int n){
        int cnt = 0;
        for(Node* cur = head; cur; cur = cur->next){
            if(++cnt == n)
                return cur;
        }
        return nullptr;
    }

    Node* get_nth_from_the_back(int n){
        if(length < n) return nullptr;
        return get_nth(length - n + 1);
    }

    int improved_search(int value){
        int idx = 0;
        for(Node* cur = head, *prv = nullptr; cur; prv = cur, cur = cur->next, idx++){
            if(cur->data == value){
                if(!prv)
                    return idx;
                swap(prv->data, cur->data);
                return idx - 1;
            }
        }
        return -1;
    }

    Node* get_tail(){
        if(!head)
            return nullptr;
        Node* cur = head;
        for(; cur; cur = cur->next)
            ;
        return cur;
    }

    bool is_Same(const linked_list &List2){
        if(List2.length != length)
            return false;

        Node* cur_list2 = List2.head;
        for(Node* cur = head; cur; cur = cur->next){
            if(cur->data != cur_list2->data)
                return false;

            cur_list2 = cur_list2->next;
        }
        return true;
    }

    bool is_Same_without_len(const linked_list &List2){
        Node* cur_list2 = List2.head;
        if(!head && !cur_list2) return true;//both empty

        Node* cur = head;
        while(cur && cur_list2){
            if(cur->data != cur_list2->data)
                return false;

            cur = cur->next;
            cur_list2 = cur_list2->next;
        }
        return !cur && !cur_list2;
    }


    void delete_node(Node* node){
        --length;
        debug_remove_node(node);
        delete node;
    }
    int delete_first(){
        if(head){
            Node* cur = head;
            int re = cur->data;
            head = head->next;
            delete_node(cur);

            if(!head) //head == nullptr
                tail = nullptr;

            debug_verify_data_integrity();
            return re;
        }
    }
    void delete_last(){
        if(length <= 1){
            delete_first();
            return;
        }
        Node* prv = get_nth(length - 1);

        delete_node(tail);
        tail = prv;
        tail->next = nullptr;

        debug_verify_data_integrity();
    }

    void delete_nth_node(int n){
        if(n < 1 || n > length){
            cout << "Invalid position.\n";
        }
        else if(n == 1){
            delete_first();
        }
        else{
            Node* prv = get_nth(n - 1);
            Node* cur = prv->next;
            bool is_tail = (cur == tail);
            prv->next = cur->next;
            if(is_tail)
                tail = prv;

            delete_node(cur);
        }
    }

    void delete_next_node(Node* node){
        assert(node);
        Node* to_delete = node->next;
        bool is_tail = to_delete == tail;

        node->next = node->next->next;
        delete_node(to_delete);

        if(is_tail)
            tail = node;
    }

    void delete_node_with_key(int value){
        if(!length)
            cout << "Empty list.\n";
        else if(head->data == value)
            delete_first();
        else{
            for(Node* cur = head, *prv = nullptr; cur; prv = cur, cur = cur->next){
                if(cur->data == value){
                    delete_next_node(prv);
                    return;
                }
            }
        }
        debug_verify_data_integrity();
    }

    void swap_pairs(){//2
        for(Node* cur = head; cur; cur = cur->next->next){
            if(cur->next)
                swap(cur->data, cur->next->data);
        }
    }

    void reverse_list(){
        if(length <= 1) return;

        tail = head;
        Node* prv = head;
        head = head->next;
        while(head){
            Node* next = head->next;
            head->next = prv;

            prv = head;
            head = next;
        }
        head = prv;
        tail->next = nullptr;
    }




    void delete_even_positions(){
        if(length <= 1)
            return;

        for(Node* cur = head->next, *prv = head; cur;){
            delete_next_node(prv);

            if(!prv->next)
                break;

            cur = prv->next->next;
            prv = prv->next;
        }

        debug_verify_data_integrity();
    }

    void embed_after(Node* node, int value){
        Node* item = new Node(value);
        item->next = node->next;
        node->next = item;
        debug_add_node(item);
        length++;
    }

    void insert_to_be_sorted(int value){
        if(!length || head->data >= value)
            insert_front(value);
        else if(tail->data <= value)
            insert_end(value);
        else{
            for(Node* cur = head, *prv = nullptr; cur; prv = cur, cur = cur->next){
                if(cur->data >= value){
                    embed_after(prv, value);
                    break;
                }
            }
        }
        debug_verify_data_integrity();
    }
    void swap_headandtail(){
       // cout << head->data << " " << tail->data << "\n";
         Node* sec_last_node = get_nth(length - 1);//gets the node at position length -1 which is the second last..

         tail->next = head->next;
         sec_last_node->next = head;
         head->next = nullptr;

        swap(head, tail);
        debug_verify_data_integrity();
    }

    void left_rotate(int k){
        if(length <= 1 || k % length == 0)
            return;

        k %= length;
        Node* nth = get_nth(k);
        tail->next = head;

        tail = nth;
        head = nth->next;

        tail->next = nullptr;
    }

    void remove_duplicated_not_sorted(){
        if(length <= 1) return;

        for(Node* cur = head; cur; cur = cur->next){
            for(Node* cur2 = cur->next, *prv = cur; cur2;){

                if(cur->data == cur2->data){
                    delete_next_node(prv);
                    cur2 = prv->next;
                }
                else{
                    prv = cur2;
                    cur2 = cur2->next;
                }
            }
        }
        debug_verify_data_integrity();
    }

    void remove_last_occurence(int key){
        if(length <= 1) return;

        Node* delete_my_next_node = nullptr;
        bool is_found = 0;

        for(Node* cur = head, *prv = nullptr; cur; prv = cur, cur = cur->next){
            if(cur->data == key){
                is_found = 1, delete_my_next_node = prv;
            }
        }
        if(is_found){
            if(delete_my_next_node)
                delete_next_node(delete_my_next_node);
            else
                delete_first();
        }
        debug_verify_data_integrity();
    }

    Node* move_to_end(Node* cur, Node* prv){
        Node* next = cur->next;
        tail->next = cur;

        if(prv)
            prv->next = next;
        else
            head = next;

        tail = cur;
        tail->next = nullptr;
        return next;
    }

    void move_key_occurence_to_end(int key){
        if(length <= 1)
            return;

        int len = length;
        for(Node* cur = head, *prv = nullptr; len--;){
            if(cur->data == key)
               cur = move_to_end(cur, prv);
            else
                prv = cur, cur = cur->next;
        }
        debug_verify_data_integrity();
    }


    int maxx(Node* head = nullptr, bool is_first_call = true){
        if(is_first_call){
            return maxx(this->head, false);
        }
        if(head == nullptr)
            return INT_MIN;

        return std::max(head->data, maxx(head->next ,false));
    }
};


class Queue{
    linked_list list1;

public:
    void enqueue(int value){
        list1.insert_end(value);
    }

    int dequeue() {
        return list1.delete_first();
    }

    void display(){
        list1.print();
    }
    bool isEmpty(){
        return list1.get_len() == 0;
    }

};

int main(){

    cout << "Hello world!" << endl;
    return 0;
}
