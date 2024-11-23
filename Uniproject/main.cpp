#include <bits/stdc++.h>

using namespace std;

struct Branchdata {
    int id;
    string name;
    string location;
};

struct appoinment {
    string time;
    string patient_name;
};

struct Doctordata {
    int id;
    string name;
    string specialization;
    string hospital_branch;
    vector<appoinment> appoinments;
};

struct Patientdata {
    int id;
    string name;
    string address;
    string appoinment;
};

vector<Doctordata> all_doctors;
vector<Branchdata> all_branches;

template<typename T>
struct Node {
    T data;
    Node* next { };

    Node(T data) : data(data) , next(nullptr){
    }
};

class Hospital_Management_system {

private:

    struct Hospital{

        Hospital(){
        }

        ~Hospital(){
            for(Node<Branchdata>* cur = branches_head; cur;){
                Node<Branchdata>* tmp = cur;
                cur = cur->next;
                delete tmp;
            }
        }
        //functions for the hospital choice
        Node<Branchdata>* branches_head = nullptr;
        Node<Branchdata>* branches_tail = nullptr;
        int len = 0;

        void add_new_branch(){
            int id;
            string name_of_branch, location;
            cout << "Enter the ID, Name and the Location of the Branch: ";
            cin >> id >> name_of_branch >> location;

            if(len != 0){//if a branch already exists with the same name,,, how would you solve this problem ??
                for(Node<Branchdata>* cur = branches_head; cur; cur = cur->next){
                    if(cur->data.id == id){
                        cout << "Invalid ID, There's another branch with the same ID.\n";
                        return;
                    }
                    if(cur->data.name == name_of_branch){
                        cout << "Invalid Name, There's another branch with the same Name.\n";
                        return;
                    }
                }
            }

            Branchdata branch;
            branch.id = id;
            branch.name = name_of_branch;
            branch.location = location;

            all_branches.push_back(branch);

            Node<Branchdata>* new_node = new Node<Branchdata>(branch);
            new_node->next = nullptr;

            if(!branches_head)// len == 0
                branches_head = branches_tail = new_node;
            else {
                branches_tail->next = new_node;
                branches_tail = new_node;
            }
            len++;
            cout << "\n";

        }

        void Display_branches(){
            if(len == 0){
                cout << "There's no branches.\n\n";
                return;
            }
            for(Node<Branchdata>* cur = branches_head; cur; cur = cur->next){
                cout << "Branch name: " << cur->data.name << " " << "With ID: " << cur->data.id << " "
                     << "located at: " << cur->data.location << "\n";
            }
            cout << "\n";
        }

        Node<Branchdata>* get_previous_node(Node<Branchdata>* tmp){
            for(Node<Branchdata>* cur = branches_head; cur && cur->next; cur = cur->next){
                if(cur->next == tmp){
                    return cur;
                }
            }
            return nullptr;
        }

        Node<Branchdata>* search_branch_by_id(int id, bool delete_it = false){
            for(Node<Branchdata>* cur = branches_head; cur; cur = cur->next)
                if(cur->data.id == id){
                    if(delete_it)
                        cout << "We've deleted your Branch with the ID: " << cur->data.id << "\n\n";
                    else cout << "We've found your Branch with the ID: " << cur->data.id << "\n\n";

                    return cur;
                }
            cout << "There's no such ID.\n\n";
            return nullptr;
        }

        void remove_branch(int id) {
            Node<Branchdata>* cur = search_branch_by_id(id, true);
            if(cur == nullptr){
                return;
            }
            else{
                Node<Branchdata>* previous = get_previous_node(cur);
                if(previous != nullptr){//if cur is not the head
                    previous->next = cur->next;
                }
                else{
                    branches_head = cur->next;//next head
                }
                delete cur;
                len--;
            }
             for(auto it = all_branches.begin(); it != all_branches.end(); ++it){
                if(it->id == id){
                    all_branches.erase(it);
                    break;
                }
            }
        }

        void display_all_appoinments_in_each_branch(){
            for(auto& b : all_branches){
                cout << "Branch: " << b.name << " has the following appoinments: " << "\n";
                for(auto& d : all_doctors){
                    if(d.hospital_branch == b.name){
                        for(auto& app : d.appoinments){
                            cout << "Appoinment time: " << app.time << ", Patient name: " <<
                                app.patient_name << "\n";
                        }
                    }
                }
                cout << "\n";
            }
        }

        void menu(){
            int choice1 = -1;
            cout << "Here are options for the Hospital: \n";

            while(choice1 == -1){
                cout << "1) Add new branch.\n";
                cout << "2) Display branches.\n";
                cout << "3) Search for branch by ID.\n";
                cout << "4) Remove branch.\n";
                cout << "5) Display all appoinments in each branch.\n";
                cout << "6) Get back to the Main menu.\n";

                cin >> choice1;
                cout << "\n";
                if(!(choice1 >= 1 && 6 >= choice1)){
                    choice1 = -1;
                    cout << "Invalid option, please try again.\n\n";
                }
                if(choice1 == 1){
                    add_new_branch();
                    choice1 = -1;
                }
                else if(choice1 == 2){
                    Display_branches();
                    choice1 = -1;
                }
                else if(choice1 == 3){
                    int id;
                    cout << "Enter the ID of the branch you wanna find: ";
                    cin >> id;
                    search_branch_by_id(id);
                    choice1 = -1;
                }
                else if(choice1 == 4){
                    int id;
                    cout << "Enter the ID of the branch you wanna remove: ";
                    cin >> id;
                    remove_branch(id);
                    choice1 = -1;
                }
                else if(choice1 == 5){
                    display_all_appoinments_in_each_branch();
                    choice1 = -1;
                }
                else if(choice1 == 6){
                    return;
                }
            }
        }

    } hospital;

    struct Doctors {
        Doctors(){
        }

        ~Doctors(){
            for(Node<Doctordata>* cur = doctors_head; cur;){
                Node<Doctordata>* tmp = cur;
                cur = cur->next;
                delete tmp;
            }
        }

        Node<Doctordata>* doctors_head = nullptr;
        Node<Doctordata>* doctors_tail = nullptr;
        int len = 0;

        void add_new_doctor(){
            cout << "Enter Doctor's ID, Name, Specialization and Hospital branch: ";
            int id;
            string name;
            string spec;
            string hos_branch;

            cin >> id >> name >> spec >> hos_branch;
            if(len != 0){
                for(Node<Doctordata>* cur = doctors_head; cur; cur = cur->next){
                    if(cur->data.id == id){
                        cout << "Invalid ID, There's another Doctor with the same ID.\n";
                        return;
                    }
                }
            }

            Doctordata doctor;
            doctor.id = id;
            doctor.name = name;
            doctor.specialization = spec;
            doctor.hospital_branch = hos_branch;

            all_doctors.push_back(doctor);

            Node<Doctordata>* new_node = new Node<Doctordata>(doctor);
            new_node->next = nullptr;

            if(!doctors_head){
                doctors_head = doctors_tail = new_node;
            }
            else{
                doctors_tail->next = new_node;
                doctors_tail = new_node;
            }
            len++;
            cout << "\n";
        }

        void remove_doctor(int id){
            Node<Doctordata>* tmp = nullptr;
            Node<Doctordata>* prev = nullptr;
            for(Node<Doctordata>* cur = doctors_head; cur; prev = cur, cur = cur->next){
                if(cur->data.id == id){
                    tmp = cur;
                    if(prev == nullptr){//then here my cur node = to the head
                        doctors_head = doctors_head->next;
                    }
                    else{
                        prev->next = cur->next;
                    }
                    break;
                }
            }
            if(tmp != nullptr){
                cout << "We've deleted the Doctor.\n";
                delete tmp;
                len--;
            }
            else{
                cout << "There's no such Doctor with the ID you entered.\n";
            }
            for(auto it = all_doctors.begin(); it != all_doctors.end(); ++it){
                if(it->id == id){
                    all_doctors.erase(it);
                    break;
                }
            }
            cout << "\n";
        }

        void display_all_appoinments(){
            for(auto &cur : all_doctors){
                cout << "Doctor: " << cur.name << "\nAppoinments: ";
                for(auto &appoin : cur.appoinments){
                    cout << "Patient " << appoin.patient_name << ", Time: " << appoin.time << "\n";
                }
            cout << "\n";
        }
    }

        void menu(){
            int choice2 = -1;
            cout << "Here are some options for the Doctor: \n";
            while(choice2 == -1){
                cout << "1) Add new doctor.\n";
                cout << "2) Remove a doctor.\n";
                cout << "3) Display all appointments.\n";
                cout << "4) Get back to the Main menu.\n";

                cin >> choice2;
                if(!(choice2 >= 1 && 4 >= choice2)){
                    choice2 = -1;
                    cout << "Invalid option, please try again.\n";
                }
                if(choice2 == 1){
                    add_new_doctor();
                    choice2 = -1;
                }

                else if(choice2 == 2){
                    cout << "Enter the ID of the Doctor you want to remove: ";
                    int id; cin >> id;
                    remove_doctor(id);
                    choice2 = -1;
                }

                else if(choice2 == 3){
                    display_all_appoinments();
                    choice2 = -1;
                }

                else if(choice2 == 4){
                    return;
                }
            }
        }

        Node<Doctordata>* find_doctor_by_id(int id){
            for(Node<Doctordata>* cur = doctors_head; cur; cur = cur->next){
                if(cur->data.id == id){
                    return cur;
                }
            }
            return nullptr;
        }

    } doctors;


    struct Patients {
        //functions for the patients choice
        Patients(){
        }
        ~Patients(){
            for(Node<Patientdata>* cur = Patients_head; cur;){
                Node<Patientdata>* tmp = cur;
                cur = cur->next;
                delete tmp;
            }
        }

        Node<Patientdata>* Patients_head = nullptr;
        Node<Patientdata>* patients_tail = nullptr;
        int len = 0;

        void add_new_patient(){
            int id;
            string name, address;
            cout << "Enter Patient's ID, Name and Address: ";
            cin >> id >> name >> address;

            if(len != 0){
                for(Node<Patientdata>* cur = Patients_head; cur; cur = cur->next){
                    if(cur->data.id == id){
                        cout << "Invalid ID, There's another patient with the same ID.\n\n";
                        return;
                    }
                }
            }

            Patientdata patient;
            patient.id = id;
            patient.name = name;
            patient.address = address;

            Node<Patientdata>* new_node = new Node<Patientdata>(patient);
            new_node->next = nullptr;

            if(!Patients_head){
                Patients_head = patients_tail = new_node;
            }
            else{
                patients_tail->next = new_node;
                patients_tail = new_node;
            }
            len++;
            cout << "\n";
        }

        void remove_patient(int id){
            Node<Patientdata>* prev = nullptr;
            Node<Patientdata>* tmp = nullptr;

            for(Node<Patientdata>* cur = Patients_head; cur; prev = cur, cur = cur->next){
                if(cur->data.id == id){
                    tmp = cur;
                    if(prev == nullptr){
                        Patients_head = Patients_head->next;
                    }
                    else{
                        prev->next = cur->next;
                    }
                    break;
                }
            }
            if(tmp != nullptr){//here i didn't delete the tmp inside the loop cuz tmp is equal to cur ,so if i deleted the tmp we can't use the cur anymore cuz we would access deleted memory
                cout << "We've deleted the patient.\n";
                delete tmp;
            }
            else{
                cout << "There's no such Patient with the given ID.\n";
            }
            len--;
            cout << "\n";
        }

        Node<Patientdata>* find_patient_by_id(int id){
            for(Node<Patientdata>* cur = Patients_head; cur; cur = cur->next){
                if(cur->data.id == id){
                    return cur;
                }
            }
            return nullptr;
        }


        void book_appoinment(int patient_id, int doctor_id, string time){
            Node<Patientdata>* patient = find_patient_by_id(patient_id);
            Doctordata* doctor = nullptr;

            for(auto& d : all_doctors){
                if(d.id == doctor_id){
                    doctor = &d;
                    break;
                }
            }

            if(!doctor || !patient){
                cout << "Invalid Patient or Doctor ID.\n";
                return;
            }
            appoinment new_appoinment;
            new_appoinment.patient_name = patient->data.name;
            new_appoinment.time = time;

            doctor->appoinments.push_back(new_appoinment);
            patient->data.appoinment = time;

            cout << "Appoinment booked successfully.\n";
        }

        bool Search_for_patient_by_name(string name){
            for(Node<Patientdata>* cur = Patients_head; cur; cur = cur->next){
                if(cur->data.name == name){
                    cout << "We've found the patient with the given name.\n\n";
                    return true;
                }
            }
            cout << "There's no such patient with the given Name.\n";
            return false;
        }

        void update_patient_data(int id){
            int updated_id;
            string updated_name, updated_address;
            cout << "Enter The information you want to update (ID, Name, Address): ";
            cin >> updated_id >> updated_name >> updated_address;

            bool found = 0;
            for(Node<Patientdata>* cur = Patients_head; cur; cur = cur->next){
                if(cur->data.id == id){
                    cur->data.id = updated_id;
                    cur->data.name = updated_name;
                    cur->data.address = updated_address;

                    found = 1;
                    break;
                }
            }
            if(!found) cout << "There's no such patient with the given ID.\n";
            cout << "\n";
        }

        void print_all_patients(){
            if(len == 0){
                cout << "There are no patients at the moment.\n\n";
                return;
            }
            for(Node<Patientdata>* cur = Patients_head; cur; cur = cur->next){
                cout << "Patient: " << cur->data.name << " ,with ID: " << cur->data.id
                    << " ,with address: " << cur->data.address << "\n";
            }
            cout << "\n";

        }

        void menu() {
            int choice3 = -1;
            cout << "Here are some options for the Patient: \n";
            while(choice3 == -1){
                cout << "1) Add new patient.\n";
                cout << "2) Remove a patient.\n";
                cout << "3) Book Appointment.\n";
                cout << "4) Search for patient by Name.\n";
                cout << "5) Update patient information.\n";
                cout << "6) Print all patients.\n";
                cout << "7) Get back to the Main menu.\n";

                cin >> choice3;
                if(!(choice3 >= 1 && 7 >= choice3)){
                    choice3 = -1;
                    cout << "Invalid option, please try again.\n";
                }

                if(choice3 == 1){
                    add_new_patient();
                    choice3 = -1;
                }
                else if(choice3 == 2){
                    int id;
                    cout << "Enter the id of the patient you want to remove: ";
                    cin >> id;
                    remove_patient(id);
                    choice3 = -1;
                }
                else if(choice3 == 3){
                    int p_id, d_id;
                    string time;
                    cout << "Enter your ID and Doctor's ID and the desired time: ";
                    cin >> p_id >> d_id >> time;
                    book_appoinment(p_id, d_id, time);
                    choice3 = -1;
                }
                else if(choice3 == 4){
                    string name;
                    cout << "Enter his Name: ";
                    cin >> name;

                    Search_for_patient_by_name(name);
                    choice3 = -1;
                }
                else if(choice3 == 5){
                    int id;
                    cout << "Enter the ID of the patient you wanna update his data: ";
                    cin >> id;
                    update_patient_data(id);
                    choice3 = -1;
                }
                else if(choice3 == 6){
                    choice3 = -1;
                    print_all_patients();
                }
                else if(choice3 == 7){
                    return;
                }
            }
        }

    } patients;

public:

    bool main_menu(){
        int option = -1;
        cout << "What option do you wanna apply ?\n";

        while(option == -1){
            cout << "1) Hospital.\n";
            cout << "2) Doctors.\n";
            cout << "3) Patients.\n";
            cout << "4) Exsit prgram.\n";

            cin >> option;
            if(!(option >= 1 && 4 >= option)){
                option = -1;
                cout << "Invalid option, please try again.\n";
            }
            if(option == 1)
                hospital.menu();

            else if(option == 2)
                doctors.menu();

            else if(option == 3)
                patients.menu();

            else if(option == 4)
                return false;
        }
        return true;
    }
};

int main(){
    Hospital_Management_system h;
    while (true) {
        if(!h.main_menu()) // h.main_menu() == false
            break;
    }
    return 0;
}
