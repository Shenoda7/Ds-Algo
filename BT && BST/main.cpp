#include <iostream>
#include <assert.h>
#include <bits/stdc++.h>

using namespace std;

class BinarySearchTree {
private:
    struct BinaryNode {
        int data {};
        BinaryNode* left {};
        BinaryNode* right {};

        BinaryNode(int data) :
             data (data), left(nullptr), right(nullptr) {
        }
    };
    BinaryNode* root{};

    void insert_node(int target, BinaryNode* node) {
        if(target < node->data) {
            if(!node->left)
                node->left = new BinaryNode(target);
            else insert_node(target, node->left);
        }
        else if(target > node->data) {
            if(!node->right)
                node->right = new BinaryNode(target);
            else insert_node(target, node->right);
        }
    }

    BinaryNode* min_node(BinaryNode* cur) {
        while(cur && cur->left)
            cur = cur->left;
        return cur;
    }

    BinaryNode* delete_node(int target, BinaryNode* node) {
        if(!node)
            return nullptr;
        else if(target < node->data)
            node->left = delete_node(target, node->left);
        else if(target > node->data)
            node->right = delete_node(target, node->right);
        else {
            BinaryNode* tmp = node;

            if(!node->left && !node->right) {
                delete node;
                return nullptr;
            }
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
        return node;
    }

    void print_inorder(BinaryNode* node){
        if(!node)
            return;

        print_inorder(node->left);
        cout << node->data << " ";
        print_inorder(node->right);
    }

    bool Search(int target, BinaryNode* node) {
        if(!node)
            return false;

        if(target == node->data)
            return true;
        else if(target < node->data)
            return Search(target, node->left);

        return Search(target, node->right);
    }

public:

    void insert_value(int target) {
        if(!root)
            root = new BinaryNode(target);
        else
            insert_node(target, root);
    }

    void delete_value(int target) {
        if (root)
            root = delete_node(target, root);
    }
    bool Search(int target) {
        return Search(target, root);
    }

    void print_inorder() {
        print_inorder(root);
    }

    void level_order_traversal() {
        if(!root)
            return;

        queue<BinaryNode*> nodes_queue;
        nodes_queue.push(root);

        int level = 0;
        while(!nodes_queue.empty()) {
            int sz = nodes_queue.size();
            cout << "Level " << level << ": ";
            while(sz--) {
                BinaryNode* cur = nodes_queue.front();
                nodes_queue.pop();

                cout << cur->data << " ";
                if(cur->left)
                    nodes_queue.push(cur->left);
                if(cur->right)
                    nodes_queue.push(cur->right);
            }
            level++;
            cout << "\n";
        }
    }

};


class Binarytree{
private:
    int data {};
    Binarytree* left {};
    Binarytree* right {};
    Binarytree* parent{};


public:
    Binarytree(int data, Binarytree* parent = nullptr) : data(data), parent(parent) {
    }

    Binarytree(int data, Binarytree* left, Binarytree* right) :
        data(data), left(left), right(right) {
        }

    deque<int> preorder_d, inorder_d;
    Binarytree(deque<int> &preorder, deque<int> &inorder, int inorder_start = 0, int inorder_end = -1) {
        if(inorder_end == -1)
            inorder_end = (int) inorder.size() - 1;

        data = preorder[0];
        preorder.pop_front();

        for(int split = inorder_start; split <= inorder_end; ++split)
        if(inorder[split] == data) {
            if(inorder_start < split)
                left = new Binarytree(preorder, inorder, inorder_start, split - 1);
            if(split < inorder_end)
                right = new Binarytree(preorder, inorder, split + 1, inorder_end);
            break;
        }
    }

    Binarytree(deque<pair<int, int>> &preorder_deque) { //(value, is_leaf)..here it's a full binary tree
        pair<int, int> p = preorder_deque.front();
        preorder_deque.pop_front();
        data = p.first;
        //p.second refers to if the node is leaf or not

        if(!p.second) {//not a leaf
            left = new Binarytree(preorder_deque);
            right = new Binarytree(preorder_deque);
        }
    }

    void print_preorder_complete() { //here we will print the null nodes
        cout << data << " ";
        if(left)
            left->print_preorder_complete();
        else cout << "-1 ";

        if(right)
            right->print_preorder_complete();
        else cout << "-1 ";
    }

    string parenthesize() {
        string repr = "(";
        repr += to_string(data);

        if(left)
            repr += left->parenthesize();
        else
            repr += "()";

        if(right)
            repr += right->parenthesize();
        else
            repr += "()";

        repr += ")";
        return repr;
    }

    string parenthesize_canonical() {
        string repr = "(" + to_string(data);

        vector<string> v;
        if(left)
            v.push_back(left->parenthesize_canonical());
        else
            v.push_back("()");

        if(right)
            v.push_back(right->parenthesize_canonical());
        else
            v.push_back("()");

        sort(v.begin(), v.end());
        for(int i = 0; i < (int)v.size(); ++i)
            repr += v[i];

        repr += ")";
        return repr;
    }

    bool is_mirror(Binarytree* first, Binarytree* second) {
         if(!first && !second)
            return true;

         if(first->data != second->data || !first && second || !second && first)
            return false;

            return is_mirror(first->left, second->right) && is_mirror(first->right, second->left);

        return true;
    }


    string parenthesizee(bool left_first = true) {
        string repr = "(" + to_string(data);

        if(left_first) {
            if(left)
                repr += left->parenthesizee(left_first);
            else
                repr += "()";
            if(right)
                repr += right->parenthesizee(left_first);
            else
                repr += "()";
        }
        else {
            if(right)
                repr += right->parenthesizee(left_first);
            else
                repr += "()";
            if(left)
                repr += left->parenthesizee(left_first);
            else
                repr += "()";
        }
        repr += ")";

        return repr;
    }

    bool is_symmetric(Binarytree* ) {
        if(!left && !right)
            return true;
        if(!left && right || !right && left)
            return false;

        return left->parenthesizee() == right->parenthesizee(false);
    }

    deque<int> return_preorder_deq() {
        preorder(preorder_d);
        return preorder_d;
    }

    deque<int> return_inorder_deq() {
        inorder(inorder_d);
        return inorder_d;
    }

    ~Binarytree() {
        //clearr();
        delete left;
        delete right;
    }


    void inorder(deque<int>&inorder_d) {
        if(left)
            left->inorder(inorder_d);
        //cout << data << " ";
        inorder_d.push_back(data);
        if(right)
            right->inorder(inorder_d);
        //return inorder_d;
    }
    void preorder(deque<int>&preorder_d) {
        cout << data << " ";
        preorder_d.push_back(data);
        if(left)
            left->preorder(preorder_d);
        if(right)
            right->preorder(preorder_d);
        //return preorder_d;
    }
    void inorder_iteration() {
        if(left)
            left->inorder_iteration();
        cout << data << " ";
        if(right)
            right->inorder_iteration();
    }


    void postorder() {
        if(left)
            left->postorder();
        if(right)
            right->postorder();
        cout << data << " ";
    }

    void add(vector<int> value, vector<char> direction) {
        assert(value.size() == direction.size());

        Binarytree* cur = this;
        for(int i = 0; i < (int) direction.size(); ++i) {
            if(direction[i] == 'L') {
                if(!cur->left)
                    cur->left = new Binarytree(value[i], cur);

                else assert(cur->left->data == value[i]);
                cur = cur->left;
            }
            else {
                if(!cur->right)
                    cur->right = new Binarytree(value[i], cur);

                else assert(cur->right->data == value[i]);
                cur = cur->right;
            }
        }
    }

    int tree_max() {
        int mx = data;
        if(left)
            mx = max(mx, left->tree_max());
        if(right)
            mx = max(mx, right->tree_max());

        return mx;
    }

    int tree_min() {
        int mn = data;
        if(left)
            mn = min(mn, left->tree_min());
        if(right)
            mn = min(mn, right->tree_min());

        return mn;
    }

    int tree_height() {
        int left_h = 0, right_h = 0;
        if(left)
            left_h = left->tree_height();
        if(right)
            right_h = right->tree_height();

        return 1 + max(left_h, right_h);
    }

    int cnt_all_nodes() {
        int cnt = 1;
        if(left)
            cnt += left->cnt_all_nodes();
        if(right)
            cnt += right->cnt_all_nodes();

        return cnt;
    }

    int cnt_leaf_nodes() {
        int res = !left && !right;
        if(left)
           res += left->cnt_leaf_nodes();
        if(right)
           res += right->cnt_leaf_nodes();

        return res;
    }

    bool is_exists(int item) {
        bool res = (data == item);
        if(!res && left)
            res = left->is_exists(item);
        if(!res && right)
            res = right->is_exists(item);

        return res;
    }

    bool is_perfect() {
        return (pow(2, tree_height()) - 1 == cnt_all_nodes());
    }

    bool is_perfect2(int h = -1) {
		if (h == -1)	// first call
			h = tree_height();

		// All leaves must be on the same last level
		if (!left && !right)
			return h == 0;

		if (!left && right || left && !right)
			return false;	// one child!

		// perfect on level h is perfect on h-1 for children
		return left->is_perfect2(h - 1) && right->is_perfect2(h - 1);
	}


    void clearr() {
        if(left) {
            delete left;
            left = nullptr;
        }
        if(right) {
            delete right;
            right = nullptr;
        }
    }

    void print_inorder_iterative(){//using stack
        stack<pair<Binarytree*, bool> > nodes;

        nodes.push(make_pair(this, false));//pushing the root

        while(!nodes.empty()) {
            Binarytree* current = nodes.top().first;
            bool is_done = nodes.top().second;
            nodes.pop();

            if(is_done)
                cout << current->data << " ";
            else {
                if(current->right)
                    nodes.push(make_pair(current->right, false));
                nodes.push(make_pair(current, true));
              //  cout << " **we pushed **" << current->data << "**  ";

                if(current->left)
                    nodes.push(make_pair(current->left, false));
            }
        }
    }


    void print_postorder_iterative() {
        stack<pair<Binarytree*, bool> > nodes;
        nodes.push(make_pair(this, false));

        while(!nodes.empty()) {
            Binarytree* cur = nodes.top().first;
            bool is_done = nodes.top().second;
            nodes.pop();

            if(is_done)
                cout << cur->data << " ";
            else {
                if(cur->right)
                    nodes.push(make_pair(cur->right, false));

                if(cur->left)
                    nodes.push(make_pair(cur->left, false));

                nodes.push(make_pair(cur, true));
            }
        }
    }

    void print_preorder_iterative() {
        stack<pair<Binarytree*, bool> > nodes;
        nodes.push(make_pair(this, false));

        while(!nodes.empty()) {
            Binarytree* cur = nodes.top().first;
            bool is_done = nodes.top().second;
            nodes.pop();

            if(is_done)
                cout << cur->data << " ";
            else {
                nodes.push(make_pair(cur, true));

                if(cur->right)
                    nodes.push(make_pair(cur->right, false));

                if(cur->left)
                    nodes.push(make_pair(cur->left, false));
            }
        }
    }

    void print_tree_boundry() {
        cout << data << " ";
        if(left)
            left->print_tree_boundry();
        else if(right)
            right->print_tree_boundry();
    }

    pair<int, int> tree_diameter() {
        pair<int, int> res = make_pair(0, 0);

        if(!left && !right)
            return res;

        pair<int, int> left_diam = make_pair(0, 0);
        pair<int, int> right_diam = make_pair(0, 0);

        if(left)
            left_diam = left->tree_diameter(), res.first += 1 + left_diam.second;
        if(right)
            right_diam = right->tree_diameter(), res.first += 1 + right_diam.second;

        res.first = max(res.first, max(left_diam.first, right_diam.first));
        res.second = 1 + max(left_diam.second, right_diam.second);
    }

    int find_diameter() {
        int diameter = 0;
        height(this, diameter);
        return diameter;
    }

    int height(Binarytree* node, int &diameter) {
        if(!node)
            return 0;
        int lh = height(node->left, diameter);
        int rh = height(node->right, diameter);
        diameter = max(diameter, lh + rh);
        return 1 + max(lh, rh);
    }


    //level order traversals//
    void level_order_traversal() {
        queue<Binarytree*> nodes;
        nodes.push(this);

        while(!nodes.empty()) {
            Binarytree* cur = nodes.front();
            nodes.pop();

            cout << cur->data << " ";
            if(cur->left)
                nodes.push(cur->left);
            if(cur->right)
                nodes.push(cur->right);
        }
    }

    void level_order_traversal2() {
        queue<Binarytree*> nodes;
        nodes.push(this);

        int level = 0;
        while(!nodes.empty()) {
            int sz = nodes.size();

            cout << "Level: " << level << ": ";
            while(sz--) {
                Binarytree* cur = nodes.front();
                nodes.pop();

                cout << cur->data << " ";
                if(cur->left)
                    nodes.push(cur->left);
                if(cur->right)
                    nodes.push(cur->right);
            }
            level++;
            cout << "\n";
        }
    }


    void level_order_traversal_spiral() {
        deque<Binarytree*> nodes_queue;
        nodes_queue.push_back(this);

        int level = 0;
        bool forward_level = true;
        while(!nodes_queue.empty()) {
            int sz = nodes_queue.size();

            cout << "Level: " << level << ": ";
            while(sz--) {
                Binarytree* cur;

                if(forward_level) {
                    cur = nodes_queue.front();
                    nodes_queue.pop_front();

                    if(cur->left)
                        nodes_queue.push_back(cur->left);
                    if(cur->right)
                        nodes_queue.push_back(cur->right);
                }
                else {
                    cur = nodes_queue.back();
                    nodes_queue.pop_back();

                    if(cur->right)
                        nodes_queue.push_front(cur->right);
                    if(cur->left)
                        nodes_queue.push_front(cur->left);
                }
                cout << cur->data << " ";
            }
            cout << "\n";
            forward_level = !forward_level;
            level++;
        }
    }

    void print_nodes_level(int level) {
        if(level == 0)
            cout << data << " ";
        else if(level) {
            left->print_nodes_level(level - 1);
            right->print_nodes_level(level - 1);
        }
    }

    void level_order_traversal_recursion() {
        int h = tree_height();
        for(int level = 0; level <= h; ++level)
            print_nodes_level(level);
    }

    bool is_complete() {
        queue<Binarytree*> nodes_queue;
        nodes_queue.push(this);

        bool no_more_allowed = false;

        while(!nodes_queue.empty()) {
            int sz = nodes_queue.size();

            while(sz--) {
                Binarytree* cur = nodes_queue.front();
                nodes_queue.pop();

                if(cur->left) {
                    if(no_more_allowed)
                        return false;
                    nodes_queue.push(cur->left);
                }
                else
                    no_more_allowed = true;

                if(cur->right) {
                    if(no_more_allowed)
                        return false;
                    nodes_queue.push(cur->right);
                }
                else no_more_allowed = true;
            }
        }
        return true;
    }

    //Binary search treeeeeeeeeeeeeeeeeeeeeeeeeee//
    bool Search(int target) {
        if(data == target)
            return true;

        if(target < data)
            return left && left->Search(target);

        return right && right->Search(target);
    }

    Binarytree* search_get(int target) {
        if(data == target)
            return this;

        return left ? left->search_get(target) : nullptr;


        return right ? right->search_get(target) : nullptr;
    }



    bool iterative_search(int target) {
        Binarytree* node = this;
        while(node) {
            if(target == node->data)
                return true;
            if(target > node->data)
                node = node->right;
            else node = node->left;
        }
        return false;
    }

    Binarytree* build_balanced_bst_tree(vector<int> &values, int start = 0, int endd = -10) {
        if(endd == -10)
            endd = values.size() - 1;

        if(start > endd)
            return nullptr;

        int mid = (start + endd) / 2;
        Binarytree* left = build_balanced_bst_tree(values, start, mid - 1);
        Binarytree* right = build_balanced_bst_tree(values, mid + 1, endd);
        Binarytree* root = new Binarytree(values[mid], left, right);

        return root;
    }

    void build_bst() {
        vector<int> values = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        Binarytree* tree = build_balanced_bst_tree(values);
        values.clear();
        tree->get_inorder(values);
        for(int x : values) cout << x << " ";
        cout << "\n";
        assert(tree->is_bst1());


    }

    void get_inorder (vector<int> &inorder) {
        if(left)
            left->get_inorder(inorder);
        inorder.push_back(data);
        if(right)
            right->get_inorder(inorder);
    }

    bool is_bst1(int mn = INT_MIN, int mx = INT_MAX) {
        bool statues = mn < data && mx > data;

        if(!statues)
            return false;

        bool left_bst = !left || left->is_bst1(mn, data);
        if(!left_bst)
            return false;

        bool right_bst = !right || right->is_bst1(data, mx);
        return right_bst;
    }

    bool is_bst2() {
        vector<int> values;
        get_inorder(values);
        for(int i = 1; i < (int) values.size(); ++i)
            if(values[i] <= values[i - 1])
                return false;
        return true;
    }

    int kth_smallest_number(int k) {
        vector<int> values;
        get_inorder(values);

        return values[k - 1];
    }

    int kth_smallest_number2(int &k) {//return to this problem later on
        if(k == 0)
            return -1234;

        if(left) {
            int res = kth_smallest_number(k);
            if(k == 0)
                return res;
        }

        --k;
        if(k == 0)
            return data;
        if(right)
            return right->kth_smallest_number2(k);

        return -1234;
    }

    int lca(int x, int y) {
        if(x < data && y < data)
            return left->lca(x, y);
        if(x > data && y > data)
            return right->lca(x, y);

        return data;
    }

    void Insert(int target) {
        if(target > data) {
            if(!right) {
                right = new Binarytree(target, this);
            }
            else right->Insert(target);
        }
        else if(target < data) {
            if(!left) {
                left = new Binarytree(target, this);
            }
            else left->Insert(target);
        }
    }

    Binarytree* get_parent() {
        return parent;
    }

   int bst_min() {
       Binarytree* cur = this;
       while(cur && cur->left)
            cur = cur->left;
       return cur->data;
   }

   int bst_mx() {
        Binarytree* cur = this;
        while(cur && cur->right)
            cur = cur->right;
        return cur->data;
   }

   pair<bool, int> succ(int target) {//using parent link but it ain't working i don't know why yet..!!!
        Binarytree* child = search_get(target);
        if(!child)
            return make_pair(false, -1);

        if(child->right)
            return make_pair(true, child->right->bst_min());

        Binarytree* parent = child->get_parent();
        while(parent && parent->right == child)
            child = parent, parent = child->get_parent();

        if(parent)
            return make_pair(true, parent->data);
        return make_pair(false, -1);
   }



   bool find_chain(vector<Binarytree*> &ancestors, int target) {
        ancestors.push_back(this);

        if(target == data)
            return true;
        if(target < data)
            return left && left->find_chain(ancestors, target);
        return right && right->find_chain(ancestors, target);
   }

   Binarytree* get_next(vector<Binarytree*> &ancestors) {
        if(ancestors.size() == 0)
            return nullptr;
        Binarytree* node = ancestors.back();
        ancestors.pop_back();
        return node;
   }

   pair<bool, int> inorder_successor(int target) {
        vector<Binarytree*> ancestors;

        if(!find_chain(ancestors, target))
            return make_pair(false, -1);

        Binarytree* child = get_next(ancestors);
        if(child->right)
            return make_pair(true, child->right->bst_min());

        Binarytree* parent = get_next(ancestors);
        while(parent && parent->right == child)
            child = parent, parent = get_next(ancestors);

        if(parent)
            return make_pair(true, parent->data);

        return make_pair(false, -1);
   }

   pair<bool, int> predecessor_successor(int target) {
        vector<Binarytree*> ancestors;

        if(!find_chain(ancestors, target))
            return make_pair(false, -1);

        Binarytree* child = get_next(ancestors);
        if(child->left)
            return make_pair(true, child->left->bst_min());

        Binarytree* parent = get_next(ancestors);
        while(parent && parent->left == child)
            child = parent, parent = get_next(ancestors);

        if(parent)
            return make_pair(true, parent->data);

        return make_pair(false, -1);
   }

   void successor(deque<int> &queries, vector<int> &answer, vector<int> &traversal) {
        if(queries.empty())
            return;
        if(left && queries.front() < data) {
            left->successor(queries, answer, traversal);

            if(queries.empty())
                return;
        }
        if(!traversal.empty() && traversal.back() == queries.front()) {
            answer.push_back(data);
            queries.pop_front();

            if(queries.empty())
                return;
        }
        traversal.push_back(data);

        if(right && queries.front() >= data) {
            right->successor(queries, answer, traversal);
        }
   }


   bool is_degenrate(vector<int> &preorder) {
        if(preorder.size() <= 2)
            return true;

        int mn = 0, mx = 1000;

        for(int i = 1; i < preorder.size(); ++i) {
            if(preorder[i] < mn || preorder[i] > mx)
                return false;

            if(preorder[i] > preorder[i - 1])
                mn = preorder[i - 1] + 1;
            else
                mx = preorder[i - 1] - 1;
        }
        return true;
   }


   //Binary search tree deletion...it's fun tbh
   Binarytree* min_node() {
        Binarytree* cur = this;
        while(cur && cur->left)
            cur = cur->left;
        return cur;
   }

   void delete_value(int target) {
        if(target == data && !left && !right) //single node which is root
            return;
        delete_node(target, this);//this -->root
   }

   Binarytree* delete_node(int target, Binarytree* node) {
        if(!node)
            return nullptr;

        if(target < node->data)
            node->left = delete_node(target, node->left);
        else if(target > node->data)
            node->right = delete_node(target, node->right);
        else {
            //found the node, handle deletion..
            Binarytree* tmp = node;

            if(!node->left && !node->right) {
                delete node;
                return nullptr;
            }
            else if(!node->left) {
                node->special_delete(node->right);
            }
            else if(!node->right) {
                node->special_delete(node->left);
            }
            else {
//                Binarytree* mn = node->right->min_node();
//                node->data = mn->data;
//                node->right = delete_node(node->data, node->right);
//                tmp = nullptr;

                //we'll try to replcae recursion to delete the node
                Binarytree* parent = node;
                Binarytree* child = parent->right;
                while(child->left)
                    parent = child, child = child->left;//getting the min

                node->data = child->data;

                if(parent->right == child)//which is if there's no left
                    parent->right = child->right;
                else
                    parent->left = child->right;
                tmp = child;
            }
            if(tmp)
                delete tmp;
        }
        return node;
   }

   Binarytree* max_node() {
        Binarytree* cur = this;
        while(cur && cur->right)
            cur = cur->right;
        return cur;
   }

   void special_delete(Binarytree* child) {
        //instead of deleting the node i want to delete and then returning it's child
        //we could just move our child data to the node (which i wanna delete) and remove the child
        data = child->data;
        left = child->left;
        right = child->right;

        delete child;
   }

   Binarytree* delete_node_p(int target, Binarytree* node) {
        if(!node)
            return nullptr;
        else if(target < node->data)
            node->left = delete_node_p(target, node->left);
        else if(target > node->data)
            node->right = delete_node_p(target, node->right);
        else {
            Binarytree* tmp = node;
            if(!node->left && !node->right) {
                delete node;
                return nullptr;
            }
            else if(!node->right)
                node->special_delete(node->left);//think about the testcase which i have    10
            else if(!node->left) //                                                         /
                node->special_delete(node->right);//                                       5
                //so if i wanna delete 10  my 10 will be NULL connected to 5 and i can't do that cuz 10 is my root so the special delete copies child's data(which is 5) to the root and then delete the child..
                //we can't delete 10 cuz we can't delete (this) it can't destroy itself
            else {
                Binarytree* mx = node->left->max_node();
                node->data = mx->data;
                node->left = delete_node_p(node->data, node->left);
                tmp = nullptr;
            }
            if(tmp)
                delete tmp;
        }
        return node;
   }

};

void test1() {//binary tree
    Binarytree tree(5);
    tree.add( {7, 8}, { 'L', 'L'} );
    tree.add( { 7, 10}, { 'L', 'R'} );
    tree.add( { 3, 1}, { 'R', 'R'} );
    tree.add( {3, 2},  { 'R', 'L' } );


    cout << "\n";    cout << "Tree max: " << tree.tree_max() << "\n";
    cout << "Tree min: " << tree.tree_min() << "\n";
    cout << "Tree height: " << tree.tree_height() << "\n";
    cout << "Number of all nodes: " << tree.cnt_all_nodes() << "\n";
    cout << "Number of all leaf nodes: " << tree.cnt_leaf_nodes() << "\n";
    cout << "If a specific number exists: " << tree.is_exists(4) << "\n";
    cout << "If the tree is perfect: " << tree.is_perfect2() << " " << tree.is_perfect() << "\n";
    cout << "Tree inorder using stack: "; tree.print_inorder_iterative();
    cout << "\n";
    cout << "Tree postorder using stack: "; tree.print_postorder_iterative();
    cout << "\n";
    cout << "Tree preorder using stack: "; tree.print_preorder_iterative();
    cout << "\n";
    cout << "Left tree boundry: "; tree.print_tree_boundry();
    cout << "\n";
    cout << "Level order traversal: "; tree.level_order_traversal();
    cout << "\n";
    cout << "Level order traversal2: \n"; tree.level_order_traversal2();
    cout << "\n";
    cout << "Level order traversal spiral: \n"; tree.level_order_traversal_spiral();
    cout << "\n";
    cout << "Is it a complete binary tree? \n"; cout << tree.is_complete();
    cout << "\n";

    deque<int> preorder_data = {1, 2, 4, 5, 3};
    cout << "\n";
    deque<int> inorder_data = {4, 2, 5, 1, 3};

    Binarytree my_tree(preorder_data, inorder_data);
    cout << "My new tree generation of a preorder deque and inorder deque: ";
    my_tree.inorder_iteration(); cout << "\n";
    cout << my_tree.is_perfect() << "\n";

    deque<pair<int, int>> preorder = { make_pair(1, 0), make_pair(2, 1), make_pair(3, 1)};
    Binarytree my_tree2(preorder);
    cout << "My new tree generation of a preorder deque of a value and is_leaf? boolean: ";
    my_tree2.inorder_iteration(); cout << "\n";


    cout << my_tree2.parenthesize() << "\n";
    cout << tree.parenthesize_canonical() << "\n";
    cout << tree.find_diameter() << "\n";
}


void test2() {//binary search tree
    Binarytree tree(50);
    tree.add({20, 15}, {'L', 'L'});
    tree.add({20, 45, 35}, {'L', 'R', 'L'});
    tree.add({70, 73}, {'R', 'R'});
    tree.add({70, 60}, {'R', 'L'});

    cout << tree.Search(45) << " " << "While iterative search outputs: " << tree.iterative_search(45) << "\n";
    tree.inorder_iteration(); cout << "\n";
    cout << tree.bst_min() << " " << tree.bst_mx() << "\n";
    cout << "Is this tree a BST: " << tree.is_bst1() << " " << tree.is_bst2() << "\n";
    int k = 1;
    cout << "Find kth smalles integer: " << tree.kth_smallest_number(k) << " While in recursion: " << tree.kth_smallest_number2(k) <<"\n";//here wrong output
    cout << "Here we made a function that calls the build balanced bst tree function and that's the output : "; tree.build_bst();
    cout << "\n";
    cout << "LCA: " << tree.lca(60, 70) << "\n";

    int x = 50;
    cout << "Inorder successor of my queue is: ";//using recursion
    deque<int> q;
    q.push_back(20);
    q.push_back(50);
    q.push_back(60);
    vector<int> ans, trav;
    tree.successor(q, ans, trav);
    for(int x : ans) cout << x << " ";
    cout << "\n";

    cout << "Inorder successor of " << x << " is:" << tree.inorder_successor(x).second << "\n";
    cout << "predecessor of " << x << " is: " <<tree.predecessor_successor(x).second << "\n";//here is wrong output..
    int g = 20;
    tree.delete_value(g);
    cout << "This our tree after deleting " << g << ": ";
    tree.inorder_iteration();

    cout << "\n";
}

void test3() {//here we create a new bst with internal class NODE
    BinarySearchTree tree;
    tree.insert_value(10);
    tree.insert_value(5);
    tree.insert_value(6);
    tree.insert_value(15);
    tree.insert_value(11);
    tree.insert_value(17);

    tree.delete_value(11);
    tree.print_inorder();
    cout << "\n";
    tree.level_order_traversal();

}

int main(){

//    test1();
//     test2();
    test3();
    return 0;
}
