#include <bits/stdc++.h>

using namespace std;

class MaxHeap {
private:
    int *array{};
    int sz {};
    int capacity{ 1000 };

    int left(int node) {
        int p = 2*node + 1;
        if(p >= sz)
            return -1;
        return p;
    }
    int right(int node) {
        int p = 2*node + 2;
        if(p >= sz)
            return -1;
        return p;
    }

    int parent(int node) {
        return node == 0 ? -1 : (node - 1)/2;
    }

    void heapify_up(int child_pos) {
        int parent_pos = parent(child_pos);

        if(child_pos == 0 || array[parent_pos] >= array[child_pos])
            return;

        swap(array[parent_pos], array[child_pos]);
        heapify_up(parent_pos);
    }

    void heapify_down(int parent_pos) {
        int child_pos = left(parent_pos);
        int right_child = right(parent_pos);

        if(child_pos == -1)
            return;

        if(right_child != -1 && array[right_child] > array[child_pos])
            child_pos = right_child;

        if(array[child_pos] >= array[parent_pos]) {
            swap(array[child_pos], array[parent_pos]);
            heapify_down(child_pos);
        }
    }

public:

    MaxHeap() {
        array = new int [capacity] {};
        sz = 0;
    }

    ~MaxHeap() {
        delete[] array;
        array = nullptr;
    }

    MaxHeap(const vector<int> &v) {
        assert((int)v.size() <= capacity);
        array = new int[capacity] {};
        sz = v.size();

        for(int i = 0; i < (int) v.size(); ++i)
            array[i] = v[i];

        heapify();
    }

    void heapify() {
        for(int i = sz/2 - 1; i >= 0; --i)
            heapify_down(i);
    }

    bool isempty() {
        return sz == 0;
    }

    void push(int key) {
        assert(sz + 1 <= capacity);
        array[sz++] = key;
        heapify_up(sz - 1);
    }

    void pop() {
        assert(!isempty());
        array[0] = array[--sz];
        heapify_down(0);
    }

    int top() {
        assert(!isempty());
        return array[0];
    }
};

class MinHeap {
private:
    int *array {};
    int sz{};
    int capacity { 1000 };

    int left (int node_pos) {
        int p = 2 * node_pos + 1;
        if(p >= sz)
            return -1;
        return p;
    }
    int right (int node_pos) {
        int p = 2 * node_pos + 2;
        if(p >= sz)
            return -1;
        return p;
    }
    int parent(int node) {
        return node == 0 ? -1 : (node - 1) / 2;
    }

    void heapify_up(int child_pos) {
        int parent_pos = parent(child_pos);
        if(child_pos == 0 || array[parent_pos] <= array[child_pos])
            return;

        swap(array[child_pos], array[parent_pos]);
        heapify_up(parent_pos);
    }

    void heapify_down(int parent_pos) {
        int child_pos = left(parent_pos);
        int right_child = right(parent_pos);

        if(child_pos == -1)
            return;

        if(right_child != -1 && array[child_pos] > array[right_child])
            child_pos = right_child;

        if(array[parent_pos] > array[child_pos]) {
            swap(array[parent_pos], array[child_pos]);
            heapify_down(child_pos);
        }
    }

    void print_less_than(int val, int parent_pos = 0) {
        if(parent_pos == -1 || array[parent_pos] >= val)
            return;

        cout << array[parent_pos] << " ";
        print_less_than(val, left(parent_pos));
        print_less_than(val, right(parent_pos));
    }

    int find_min_idx(int *p, int n, int i) {
        int mn = INT_MAX, mn_j{};
        for(int j = i; j < n; ++j) {
            if(p[j] < mn) {
                mn_j = j;
                mn = p[j];
            }
        }
        return mn_j;
    }


    bool is_Heap(int parent_pos) {
        if(parent_pos == -1)
            return true;

        int left_child = left(parent_pos);
        int right_child = right(parent_pos);

        if(left_child != -1 && array[parent_pos] > array[left_child])
            return false;
        if(right_child != -1 && array[parent_pos] > array[left_child])
            return false;

        return is_Heap(left_child) && is_Heap(right_child);
    }



public:
    MinHeap () {
        array = new int [capacity] {};
        sz = 0;
    }
    ~MinHeap() {
        delete []array;
        array = nullptr;
    }

    MinHeap(const vector<int> &v) {
        assert((int)v.size() <= capacity);
        array = new int [capacity] {};
        sz = v.size();

        for(int i = 0; i < (int)v.size(); ++i)
            array[i] = v[i];

        heapify();
    }
    void heapify() {
        for(int i = sz/2 - 1; i >= 0; --i)
            heapify_down(i);
    }

    void push(int key) {
        assert(sz + 1 <= capacity);
        array[sz++] = key;
        heapify_up(sz - 1);
    }

    int top() {
        assert(!isempty());
        return array[0];
    }

    bool isempty() {
        return sz == 0;
    }

    void pop() {
        assert(!isempty());
        array[0] = array[--sz];
        heapify_down(0);
    }
    void print_less(int val) {
        print_less_than(val);
    }
    bool is_heap_array(int *p, int n) {
        int *old_arr = array;
        int old_sz = sz;

        array = p;
        sz = n;

        bool res = is_Heap(0);

        array = old_arr;
        sz = old_sz;

        return res;
    }

    void heap_sort(int *p, int n) {
        if(n <= 1)
            return;

        int *old_arr = array;
        int old_sz = sz;

        array = p;
        sz = n;

        heapify();//build our array

        //here we will just use the pop algorithm step by step
        while(sz--) {
            swap(array[0], array[sz]);
            heapify_down(0);
        }
        for(int i = 0; i < n/2; ++i)
            swap(array[i], array[n - i - 1]);

        for(int i = 0; i < n; ++i)
            cout << array[i] << " ";


        sz = old_sz;
        array = old_arr;
    }

    void print() {
        for(int i = 0; i < sz; ++i)
            cout << array[i] << " ";
    }

};

class MaxHeap2 {//hw 2
private:
    MinHeap heap;

    vector<int> multiply_neg(const vector<int> &v) {
        vector<int> res = v;
        for(int i = 0; i < v.size(); ++i) {
            res[i] *= -1;
        }
        return res;
    }

public:
    MaxHeap2() {
    }
    MaxHeap2(const vector<int> &v) : heap(multiply_neg(v)) {
    }

    void push(int key) {
        heap.push(-key);
    }

    void pop() {
        heap.pop();
    }

    bool isempty() {
        return heap.isempty();
    }
    int top() {
       return -heap.top();

    }
};



void test1() {
    vector<int> v { 2, 17, 22, 10, 8, 37, 14, 19, 7, 6, 5, 12, 25, 30 };
//    MaxHeap2 heap(v);
//    while(!heap.isempty()) {
//        cout << heap.top() << " ";
//        heap.pop();
//    }
    MinHeap heap2, heap(v);
    int arr[14] = { 2, 17, 22, 10, 8, 37, 14, 19, 7, 6, 5, 12, 25, 30 };
    heap2.heap_sort(arr, 14);
    cout << "\n";
//    heap.print();

}

void test2() {
    vector<int> v { 2, 17, 22, 10, 8, 37, 14, 19, 7, 6, 5, 12, 25, 30 };
    MaxHeap2 heap(v);

    cout << "Top element in the adjusted max heap is: " << heap.top() << "\n";
    cout << "Elements in the max heap is: ";
    while(!heap.isempty()) {
        cout << heap.top() << " ";
        heap.pop();
    }
}

int main() {
    //test1();
	//test2();

	priority_queue<int > heap;
	int x;
	int tmp {};
	while(cin >> x) {
        heap.push(x);
        if(k == heap.size()) {
            tmp = heap.top();
        }
	}
	cout << tmp;
    return 0;
}
