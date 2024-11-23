//Project done by Shenoda
//Inspired by a c++ course by Mostafa Saad

#include <iostream>
#include<bits/stdc++.h>

using namespace std;

int numofbooks;
int numofusers;

const int MAX = 1000;

struct Book{
    int id;
    string name;
    int quantity;
    int total_borrowed = 0;
};

struct User{
    int national_id;
    string name;
    int nof_borrowed_books = 0;//for each user
    string borrowed_book_names[MAX];
    int borrowed_ids[MAX];
};

User users[MAX + 1];
Book books[MAX + 1];


bool comparebyid(const Book &a, const Book &b){
    return a.id < b.id;
}

bool comparebyname(const Book &a, const Book &b){
    return a.name < b.name;
}

void print_library_by_id(){
    sort(books, books + numofbooks, comparebyid);
    for(int i = 0; i < numofbooks; ++i){
        cout << "id = " << books[i].id << " name = " << books[i].name << " total quantity = " << books[i].quantity
             << " total borrowed = " << books[i].total_borrowed;
        cout << "\n";
    }
}

void print_library_by_name(){
    sort(books, books + numofbooks, comparebyname);
    for(int i = 0; i < numofbooks; ++i){
        cout << "id = " << books[i].id << " name = " << books[i].name << " total quantity = " << books[i].quantity
             << " total borrowed = " << books[i].total_borrowed;
        cout << "\n";
    }
}

void add_book(){

    int id;
    string name;
    int total_quntity;
    cout << "Enter your book info : id & name & total quantity : ";
    cin >> id >> name >> total_quntity;

    books[numofbooks].id = id;
    books[numofbooks].name = name;
    books[numofbooks].quantity = total_quntity;
    numofbooks++;
}

void search_books_by_prefix(){
    string prefix;
    cout << "Enter book name prefix: ";
    cin >> prefix;

    bool found = 0;
    int pre_len = prefix.size();
    int len = numofbooks;
    for(int i = 0; i < len; ++i){
        if(books[i].name.substr(0, pre_len) == prefix){
            cout << books[i].name << "\n";
            found = 1;
        }
    }
    if(!found) cout << "No books with such prefix\n";
}

void print_who_borrowed_book_by_name(){
    string book_name;

    cout << "Enter book name: ";
    cin >> book_name;

    bool found = 0;
    int len = numofusers;
    for(int i = 0; i < len; ++i){
        if(users[i].nof_borrowed_books > 0){
            int len2 = users[i].nof_borrowed_books;
            for(int j = 0; j < len2; ++j){
                if(users[i].borrowed_book_names[j] == book_name){
                    cout << users[i].name << "\n";
                    found = 1;
                    break;
                }
            }
        }
    }
    if(!found) cout << "Invalid book name\n";
}

void add_user(){
    string user_name;
    int id;

    cout << "Enter user name & national id: ";
    cin >> user_name >> id;

    users[numofusers].national_id = id;
    users[numofusers].name = user_name;
    numofusers++;
}

void user_borrow_book(){
    string user_name, book_name;

    cout << "Enter user name and book name: ";
    cin >> user_name >> book_name;

    int len2 = numofbooks;
    int id_borrowed_book{};
    for(int i = 0; i < len2; ++i){
        if(books[i].name == book_name){
            //books[i].quantity--;//if you wanna keep track with the quantity that's okay,, note that you could subtract total_borrowed from total quantity to know what's left
            books[i].total_borrowed++;
            id_borrowed_book = books[i].id;
            break;
        }
    }

    int len = numofusers;
    for(int i = 0; i < len; ++i){
        if(users[i].name == user_name){
            int c = users[i].nof_borrowed_books;
            users[i].borrowed_book_names[c] = book_name;
            users[i].borrowed_ids[c] = id_borrowed_book;
            users[i].nof_borrowed_books++;
            break;
        }
    }
}

void print_users(){
    int len = numofusers;
    for(int i = 0; i < len; ++i){
        cout << "user " << users[i].name << " id " << users[i].national_id << " borrowed books ids: ";

        int len2 = users[i].nof_borrowed_books;
        sort(users[i].borrowed_ids ,users[i].borrowed_ids + users[i].nof_borrowed_books);
        for(int j = 0; j < len2; ++j)
            cout << users[i].borrowed_ids[j] << " ";

        cout << "\n";
    }
}

void shift_left(int pos, string borrowed_book_names[], int borrowed_book_ids[], int& nof_borrowed_books){
    int len = nof_borrowed_books;
    for(int i = pos; i < len - 1; ++i){
        borrowed_book_ids[i] = borrowed_book_ids[i + 1];
        borrowed_book_names[i] = borrowed_book_names[i + 1];
    }
    nof_borrowed_books--;
}

void user_return_book(){
    string user_name, book_name;

    cout << "Enter your user name & book name: ";
    cin >> user_name >> book_name;

    int id_of_borrowed_book{};
    int len = numofbooks;
    for(int i = 0; i < len; ++i){
        if(books[i].name == book_name){
            books[i].total_borrowed--;
            books[i].quantity++;
            id_of_borrowed_book = books[i].id;
            break;
        }
    }
    int len2 = numofusers;
    int idx_remove{};
    for(int i = 0; i < len2; ++i){
        if(users[i].name == user_name){
            int c = users[i].nof_borrowed_books;
            for(int j = 0; j < c; ++j){
                if(users[i].borrowed_ids[j] == id_of_borrowed_book){
                    idx_remove = j;
                    break;
                }
            }
           shift_left(idx_remove, users[i].borrowed_book_names, users[i].borrowed_ids, users[i].nof_borrowed_books);
        }
    }
}


bool show_once = 1;
int menu(){
    int choice = -1;
    while(choice == -1){
        if(show_once){
            cout << "1) Add a book\n";
            cout << "2) search books by prefix\n";
            cout << "3) print who borrowed book by name\n";
            cout << "4) print library by id\n";
            cout << "5) print library by name\n";
            cout << "6) add user\n";
            cout << "7) user borrow book\n";
            cout << "8) user return book\n";
            cout << "9) print users\n";
            cout << "10) Exit\n";

            show_once = 0;
        }
        cout << "Enter your menu choice [1 - 10]: ";
        cin >> choice;

        if(!(1 <= choice && choice <= 10)){
            cout << "Invalid choice, please try again\n";
            choice = -1;
        }
    }
    return choice;
}

void library_system(){
    while(true){
        int choice = menu();

        if(choice == 1) add_book();
        else if(choice == 2) search_books_by_prefix();
        else if(choice == 3) print_who_borrowed_book_by_name();
        else if(choice == 4) print_library_by_id();
        else if(choice == 5) print_library_by_name();
        else if(choice == 6) add_user();
        else if(choice == 7) user_borrow_book();
        else if(choice == 8) user_return_book();
        else if(choice == 9) print_users();
        else break;
    }
}

int main(){
    library_system();
    return 0;
}
