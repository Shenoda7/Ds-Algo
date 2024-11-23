#include <bits/stdc++.h>
using namespace std;

//hey compiler this is template. Use Type.
/*template<typename Type>
Type MyMax(Type a, Type b){
    if(a > b)
        return a;
    return b;
}

struct Employee{};

int main(){
    cout << MyMax(2, 5) << "\n";                     //5: Gussed as int.
    cout << MyMax<int>(2, 5) << "\n";                //5
    cout << MyMax<double>(2.5, 5.4) << "\n";         //5.4
    cout << MyMax('X', 'A') << "\n";                //X

    //cout << MyMax(2, 5.4) << "\n";                //CE: can't guess.
    cout << MyMax<int>(2, 5.4) << "\n";             //5
    cout << MyMax<double>(2, 5.4) << "\n";          //5.4

    Employee a, b;
    //cout << MyMax<Employee>(a, b) << "\n";        //CE: can't compapre.
    return 0;
}*/
//============================================================================================

/*template<class Type1, class Type2> //here you could use class or typename.
Type1 sum(Type1 a, Type2 b){
    Type1 r = a + b;
    return r;
}

int main(){

    cout << sum(1, 10) << "\n";                  //11
    cout << sum(1, 10.5) << "\n";                //11
    cout << sum(1.2, 10.5) << "\n";             //11.7
    cout << sum(1.2, 10) << "\n";               //11.2
    cout << sum<int, int>(1.2, 10) << "\n";     //11
    cout << sum('A', 1) << "\n";                //B
    cout << sum(1, 'A') << "\n";                //66

    //cout << sum("I am", "mostafa") << "\n";   //CE: *char here is using a character pointer, right down is using a class.
    cout << sum(string("I am "), string("Shenoda")) << "\n";    //IamShenoda

    return 0;
}*/

//=============================================================================================
//                                    STATIC VARIABLE
/*int global_var = 0;

template<typename T>
void increament_me(T x){
    static int i = 0;
    cout << ++i << " " << ++global_var << "\n";
    return;
}

int main(){
    //one static variable for each generated function

    increament_me(5);  //1 1
    increament_me(5);  //2 2
    increament_me(5);  //3 3


    increament_me(2.4); // 1 4
    increament_me(2.4); // 2 5
    increament_me(2.4); // 3 6

    return 0;
}*/

//=============================================================================================
//                      FUNCTION TEMPLATE SPECIALIZATOIN
//                  WHAT IF A SPECIFIC DATATYPE SHOULD BE HANDLED DIFFERENTLY ?
/*template<class T>
T add(T a, T b){
    return a + b;
}

template<class T>
T multiply(T a, int factor){
    return a*factor;
}
//THE SYNTAX TO SPECIFY IS AS FOLLOWING

template<> //U write the word template but you don't write a type over here <>
string multiply(string str, int factor){ // and you write your whole function as you would write it in the normal case
    //we can't multiply strings
    string res = "";
    while(factor--)
        res += str;
    return res;
}

int main(){
    string s = "Magic";

    cout << add(10, 4) << "\n";         //14
    cout << add(s, s) << "\n";          //MagicMagic

    cout << multiply(10, 4) << "\n";    //40.
    cout << multiply(s, 4) << "\n";     //MagicMagicMagicMagic

    return 0;
}*/
//===============================================================================================
template<typename T>
struct MyQueue{
    T arr[100];
    int pos;

    MyQueue(){  pos = 0; }
    MyQueue(T param_arr[], int len){
        for(int i = 0; i < len; ++i)
            arr[i] = param_arr[i];
        pos = len;
    }

    void add_front(T elem){
        arr[pos++] = elem;
    }

    template<typename Type>
    void sum_and_add(Type a, Type b){
        arr[pos++] = a + b;
    }

    void print(){
        for(int i = 0; i < pos; ++i)
            cout << arr[i] << " ";
        cout << "\n";
    }
};

int main(){
    MyQueue<string> q_str;
    q_str.add_front("shenoda");
    q_str.add_front("makram");
    q_str.print();     //shenoda makram

    MyQueue<int> q_dob;
    q_dob.add_front(3);
    q_dob.add_front(2);
    q_dob.sum_and_add<double>(2.5, 3.9);
    q_dob.print();     //3 2 6

    return 0;
}
