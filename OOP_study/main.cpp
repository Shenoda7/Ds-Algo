#include <iostream>

using namespace std;

class Quote{
private:
    int internal;

    string GetQuote(){
        return "The way to get started....blah blah blah..\n";
    }

public:
    int external;

    Quote(){
        internal = 3, external = 7;
    }

    void print(){
        cout << GetQuote() << "\n";
    }
};


int main(){

    Quote q;
    cout << q.external << "\n";
    q.print();

    return 0;
}
