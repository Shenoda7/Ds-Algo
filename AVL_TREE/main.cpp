#include <bits/stdc++.h>
using namespace std;

class AVLTree {
private:
    struct BinaryNode {
        int data { };
        int height { };
        int cnt { 1 };
        BinaryNode* left { };
        BinaryNode* right { };

        BinaryNode(int data) :
             data(data) {
        }

        int ch_height(BinaryNode* node) {
            if(!node)
                return -1; //-1 for null
            return node->height;//0 for leaf
        }

        int ch_count(BinaryNode* node) {
            if(!node)
                return 0;
            return node->cnt;
        }


        void update() { //call in end of insert function
            height = 1 + max(ch_height(left), ch_height(right));
            cnt = 1 + ch_count(left) + ch_count(right);
        }

        int balance_factor() {
            return ch_height(left) - ch_height(right);
        }
    };
    BinaryNode* root {};

    bool search(int target, BinaryNode* node) {
        if(!node)
            return false;

        if(target == node->data)
            return true;

        if(target < node->data)
           return search(target, node->left);

        return search(target, node->right);
    }

    BinaryNode* right_rotation(BinaryNode* Q) {
       // cout << "Right rotation: " << Q->data << "\n";
        BinaryNode* P = Q->left;
        Q->left = P->right;
        P->right = Q;
        Q->update();
        P->update();
        return P;//new root
    }

    BinaryNode* left_rotation(BinaryNode* P) {
       // cout << "Left rotation: " << P->data << "\n";
        BinaryNode* Q = P->right;
        P->right = Q->left;
        Q->left = P;
        P->update();
        Q->update();
        return Q;//new root
    }

    BinaryNode* balance(BinaryNode* node) {
        if(node->balance_factor() == 2) {//heavy on left
            if(node->left->balance_factor() == -1) { //left right ?
                node->left = left_rotation(node->left);//to left left
            }
            node = right_rotation(node);//balance left left
        }
        else if(node->balance_factor() == -2) {//heavy on right
            if(node->right->balance_factor() == 1) {//right left ?
                node->right = right_rotation(node->right);//to right right
            }
            node = left_rotation(node);//balance right right
        }
        return node;
    }

    BinaryNode* insert_node(int target, BinaryNode* node) {
        if(target < node->data) {
            if(!node->left)
                node->left = new BinaryNode(target);
            else
                node->left = insert_node(target, node->left);
        }
        else if(target > node->data) {
            if(!node->right)
                node->right = new BinaryNode(target);
            else
                node->right = insert_node(target, node->right);
        }
        node->update();
        return balance(node);
    }

    BinaryNode* min_node(BinaryNode* cur) {
		while (cur && cur->left)
			cur = cur->left;
		return cur;
	}

	BinaryNode* max_node(BinaryNode* cur) {
        while(cur && cur->right)
            cur = cur->right;
        return cur;
	}

    BinaryNode* delete_node(int target, BinaryNode* node) {
        if(!node)
            return nullptr;
        if(target < node->data)
            node->left = delete_node(target, node->left);
        else if(target > node->data)
            node->right = delete_node(target, node->right);

        else {
            BinaryNode* tmp = node;
            if(!node->left && !node->right)
                node = nullptr;
            else if(!node->right)
                node = node->left;
            else if(!node->left)
                node = node->right;
            else {
                BinaryNode* mn = min_node(node->right);
                node->data = mn->data;
                node->right = delete_node(node->data, node->right);
                tmp = nullptr;
            }

            if(tmp)
                delete tmp;
        }

        if(node) {
            node->update();
            node = balance(node);
        }
        return node;
    }


    BinaryNode* lower_bound(int target, BinaryNode* node) {
        if(!node)
            return nullptr;

        if(target <= node->data) {
            BinaryNode* ans = lower_bound(target, node->left);
            if(ans)
                return ans;
            return node;
        }
        return lower_bound(target, node->right);
    }

    BinaryNode* upper_bound(int target, BinaryNode* node) {
        if(!node)
            return nullptr;

        if(target < node->data) {
            BinaryNode* ans = upper_bound(target, node->left);
            if(ans)
                return ans;
            return node;
        }
        return upper_bound(target, node->right);
    }

    int upper_bound_cnt(int target, BinaryNode* node) {
        if(!node)
            return 0;

        if(target < node->data) {
            int sum = 1;
            if(node->right)
                sum += node->right->cnt;
            sum += upper_bound_cnt(target, node->left);
            return sum;
        }
        return upper_bound_cnt(target, node->right);
    }

public:
    void insert_value(int target) {
        if(!root)
            root = new BinaryNode(target);
        else
            root = insert_node(target, root);
    }

    void delete_value(int target) {
        if(root) {
            root = delete_node(target, root);
        }
    }

    pair<bool, int> lower_boundd(int target) {
        if(root) {
            BinaryNode* res = lower_bound(target, root);
            if(!res)
                return make_pair(false, -1);
            return make_pair(true, res->data);
        }
        return make_pair(false, -1);
    }

    pair<bool, int> upper_boundd(int target) {
        if(root) {
            BinaryNode* res = upper_bound(target, root);
            if(!res)
                return make_pair(false, -1);
            return make_pair(true, res->data);
        }
        return make_pair(false, -1);
    }

    int count_inversions(const vector<int> &v) {
        int sum = 0;

        for(int i = 0; i < (int) v.size(); ++i) {
            insert_value(v[i]);
            sum += upper_bound_cnt(v[i], root);
        }
        return sum;
    }

};

class PriorityQueue {//using AVL implementation
private:
    struct BinaryNode {
        int priority { };
        vector<int> tasks_id { };
        int height { };
        BinaryNode* left { };
        BinaryNode* right { };

        BinaryNode(int task_id, int priority) :
             priority(priority) {
             tasks_id.push_back(task_id);
        }

        int ch_height(BinaryNode* node) {
            if(!node)
                return -1; //-1 for null
            return node->height;//0 for leaf
        }

        int update() { //call in end of insert function
           return height = 1 + max(ch_height(left), ch_height(right));
        }

        int balance_factor() {
            return ch_height(left) - ch_height(right);
        }
    };
    BinaryNode* root {};

    bool search(int target, BinaryNode* node) {
        if(!node)
            return false;

        if(target == node->priority)
            return true;

        if(target < node->priority)
           return search(target, node->left);

        return search(target, node->right);
    }

    BinaryNode* right_rotation(BinaryNode* Q) {
       // cout << "Right rotation: " << Q->data << "\n";
        BinaryNode* P = Q->left;
        Q->left = P->right;
        P->right = Q;
        Q->update();
        P->update();
        return P;//new root
    }

    BinaryNode* left_rotation(BinaryNode* P) {
       // cout << "Left rotation: " << P->data << "\n";
        BinaryNode* Q = P->right;
        P->right = Q->left;
        Q->left = P;
        P->update();
        Q->update();
        return Q;//new root
    }

    BinaryNode* balance(BinaryNode* node) {
        if(node->balance_factor() == 2) {//heavy on left
            if(node->left->balance_factor() == -1) { //left right ?
                node->left = left_rotation(node->left);//to left left
            }
            node = right_rotation(node);//balance left left
        }
        else if(node->balance_factor() == -2) {//heavy on right
            if(node->right->balance_factor() == 1) {//right left ?
                node->right = right_rotation(node->right);//to right right
            }
            node = left_rotation(node);//balance right right
        }
        return node;
    }

    BinaryNode* insert_node(int task_id, int priority, BinaryNode* node) {
        if(priority < node->priority) {
            if(!node->left)
                node->left = new BinaryNode(task_id, priority);
            else
                node->left = insert_node(task_id, priority, node->left);
        }
        else if(priority > node->priority) {
            if(!node->right)
                node->right = new BinaryNode(task_id, priority);
            else
                node->right = insert_node(task_id, priority, node->right);
        }
        else {
            node->tasks_id.push_back(task_id);
        }

        node->update();
        return balance(node);
    }

    BinaryNode* min_node(BinaryNode* cur) {
		while (cur && cur->left)
			cur = cur->left;
		return cur;
	}

	BinaryNode* max_node(BinaryNode* cur) {
        while(cur && cur->right)
            cur = cur->right;
        return cur;
	}

    BinaryNode* delete_node(int priority, BinaryNode* node) {
        if(!node)
            return nullptr;
        if(priority < node->priority)
            node->left = delete_node(priority, node->left);
        else if(priority > node->priority)
            node->right = delete_node(priority, node->right);

        else {
            BinaryNode* tmp = node;
            if(!node->left && !node->right)
                node = nullptr;
            else if(!node->right)
                node = node->left;
            else if(!node->left)
                node = node->right;
            else {
                BinaryNode* mn = min_node(node->right);
                node->priority = mn->priority;
                node->right = delete_node(node->priority, node->right);
                tmp = nullptr;
            }

            if(tmp)
                delete tmp;
        }

        if(node) {
            node->update();
            node = balance(node);
        }
        return node;
    }

public:
    void enqueue(int task_id, int task_priority) {
        if(!root)
            root = new BinaryNode(task_id, task_priority);
        else
            root = insert_node(task_id, task_priority, root);
    }

    int dequeue() {
        assert(!isempty());

        BinaryNode* mx = max_node(root);
        assert(mx->tasks_id.size() > 0);
        int ret = mx->tasks_id.back();
        mx->tasks_id.pop_back();
        if(mx->tasks_id.size() == 0)
            root = delete_node(mx->priority, root);

        return ret;
    }

    bool isempty() {
        return root == nullptr;
    }
};

void test_priority_queue() {

    PriorityQueue q;
    q.enqueue(1131, 1);
    q.enqueue(3111, 3);
    q.enqueue(2211, 2);
    q.enqueue(3161, 3);
    q.enqueue(7761, 7);

    cout << q.dequeue() << "\n";
    cout << q.dequeue() << "\n";

    q.enqueue(1535, 1);
    q.enqueue(2815, 2);
    q.enqueue(3845, 3);
    q.enqueue(3145, 3);

    while(!q.isempty()) {
        cout << q.dequeue() << " "<<flush;
    }
    cout << "\n";

    cout << "bye\n";

//    getchar();
}

void test_upper() {
    AVLTree tree;

    vector<int> v = {10, 5, 8, 2, 12, 6};
    cout << "Number of inverstions is: " << tree.count_inversions(v) << "\n";
}

void test1() {
    AVLTree tree;
    tree.insert_value(2);
    tree.insert_value(5);
    tree.insert_value(10);
    tree.insert_value(13);
    tree.insert_value(15);
    tree.insert_value(20);
    tree.insert_value(40);
    tree.insert_value(50);
    tree.insert_value(70);

    pair<bool, int> p = tree.lower_boundd(11);
    cout << p.second << "\n";

    pair<bool, int> px = tree.upper_boundd(50);
    cout << px.second << "\n";

}

int main(){
    //test1();
    //test_upper();
    test_priority_queue();
    return 0;
}
