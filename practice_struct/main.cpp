#include <iostream>
#include<bits/stdc++.h>
using namespace std;

const int MAX_QUEUE = 5;
const int MAX_SPEC = 20;

struct hospital_queue{
    string names[MAX_QUEUE + 1];
    int statues[MAX_QUEUE + 1];
    int len, spec;


    hospital_queue(){
        len = 0;
        spec = -1;
    }

    hospital_queue(int _spec){
        len = 0;
        spec = _spec;
    }

    bool add_end(string name, int st){
        if(len >= MAX_QUEUE){
            cout << "Sorry we can't add more patients\n";
            return false;
        }
        names[len] = name;
        statues[len] = st;
        len++;
        return true;
    }

    bool add_front(string name, int st){

        if(len >= MAX_QUEUE){
            cout << "Sorry we can't add more patients\n";
            return false;
        }
        for(int i = len - 1; i >= 0; --i){
            names[i + 1] = names[i];
            statues[i + 1] = statues[i];
        }
        names[0] = name;
        statues[0] = st;
        len++;
        return true;
    }

    void print(){
        if(len == 0) return;

        cout << "There are " << len << " patients in specialization " << spec << "\n";
        for(int i = 0; i < len; ++i){
            cout << names[i] << " ";
            if(statues[i]) cout << "Urgent\n";
            else cout << "Regular\n";
        }
        cout << "\n";
    }

    string remove_front(){
        if(len == 0){
            cout << "No patients at the moment, please have rest.\n";
            return "";
        }
        string nxt_patient = names[0];
        for(int i = 1; i < len; ++i){
            names[i - 1] = names[i];
            statues[i - 1] = statues[i];
        }
        --len;
        return nxt_patient;
    }
};

struct hospital_system{
    hospital_queue queues[MAX_SPEC];

    hospital_system(){
        for(int i = 0; i < MAX_SPEC; ++i){
            queues[i] = hospital_queue(i);
        }
    }

    void run(){
        while(true){
            int choice = menu();

            if(choice == 1){
                add_patient();
            }
            else if(choice == 2){
                print_all_patients();
            }
            else if(choice == 3){
                get_nxt_patient();
            }
            else {
                break;
            }
        }
    }

    int menu(){
        int choice = -1;
        while(choice == -1){
            cout << "Enter your choice\n";
            cout << "1) add a new patient\n";
            cout << "2) print all patients\n";
            cout << "3) get next patient\n";
            cout << "4) Exist\n";

            cin >> choice;

            if(!(1 <= choice && choice <= 4)){
                cout << "Invalid choice, please try again\n";
                choice = -1;
            }
        }
        return choice;
    }

    bool add_patient(){
        int spec;
        string name;
        bool st;

        cout << "Enter specialization, name and statues: ";
        cin >> spec >> name >> st;

        int len = queues[spec].len;
        if(len >= MAX_QUEUE){
            cout << "Sorry we can't add more patients for this specialization\n";
            return false;
        }

        if(st)
            queues[spec].add_front(name, st);
        else
            queues[spec].add_end(name, st);
        return true;
    }

    void print_all_patients(){
        cout << "***************************\n";
        for(int i = 0; i < MAX_SPEC; ++i){
            queues[i].print();
        }
        cout << "\n";
    }

    void get_nxt_patient(){
        int spec;
        cout << "Enter specialization: ";
        cin >> spec;

        int len = queues[spec].len;
        if(len == 0){
            cout << "No patients at the moment, please have some rest.\n";
        }
        else{
            cout << queues[spec].remove_front() << " please go with the Dr.\n";
        }
    }
};

int main(){

    hospital_system hospital = hospital_system();
    hospital.run();
    return 0;
}
