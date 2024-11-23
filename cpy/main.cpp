//Project done by Shenoda
//Inspired by a c++ course by Mostafa Saad

#include <iostream>
#include<string>
#include<algorithm>

using namespace std;

int numofbooks;
int numofusers;

const int MAX = 100;



struct Book{
    int id;
    string name;
    int total_quantity;
    int total_borrowed;

    Book(){
        name = "";
        id = -1;
        total_borrowed = total_quantity = 0;
    }
    void read(){
        cout << "Enter book info: id & name & total quantity: ";
        cin >> id >> name >> total_quantity;
    }
    bool borrow(int user_id){
        if(total_borrowed - total_quantity == 0)
            return false;
        total_borrowed++;
        return true;
    }
    void return_cpy(){
        if(total_borrowed > 0)
            --total_borrowed;
    }
    bool has_prefix(string prefix){//this is more readable
        if(prefix.size() > name.size()) return false;

        string pre_of_name = name.substr(0, prefix.size());
        if(prefix != pre_of_name) return false;

        return true;
    }
    void print(){
        cout << "id " << id << " name " << name
             << " total borrowed " << total_borrowed
             << " total quantity " << total_quantity << "\n";
    }
};


bool comparebyid(const Book &a, const Book &b){
    return a.id < b.id;
}

bool comparebyname(const Book &a, const Book &b){
    return a.name < b.name;
}

struct User{
    int id;
    string name;
    int borrowed_books_ids[MAX];
    int len;

    User(){
        name = "";
        len = 0;
        id = -1;
    }
    void read(){
        cout << "Enter user name & national id: ";
        cin >> name >> id;
    }
    void borrow(int book_id){
        borrowed_books_ids[len++] = book_id;
    }
    void return_cpy(int book_id){
        bool removed = false;
        for(int i = 0; i < len; ++i){
            if(borrowed_books_ids[i] == book_id){
                for(int j = i; j < len; ++j){
                    borrowed_books_ids[j] = borrowed_books_ids[j + 1];
                }
                removed = true;
                --len;
                break;
            }
        }
        if(!removed){
            cout << "User " << name << " never borrowed book id " << book_id
                 << "\n";
        }
    }
    bool is_borrowed(int book_id){
        for(int i = 0; i < len; ++i){
            if(borrowed_books_ids[i] == book_id)
                return true;
        }
        return false;
    }
    void print(){

        sort(borrowed_books_ids, borrowed_books_ids + len);
        cout << "User " << name << " borrowed books with ids: ";
        for(int i = 0; i < len; ++i){
            cout << borrowed_books_ids[i] << " ";
        }
        cout << "\n";
    }

};

User users[MAX];
Book books[MAX];



bool show_once = 1;
struct library_system {
    int total_books;
    Book books[MAX];
    User users[MAX];
    int total_users;

    library_system(){
        total_books = total_users = 0;
    }

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

    void run(){
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

    void add_book(){
        books[total_books++].read();
    }
    void search_books_by_prefix(){
        cout << "Enter book name prefix: ";
        string prefix;
        cin >> prefix;

        int cnt = 0;
        for(int i = 0; i < total_books; ++i){
            if(books[i].has_prefix(prefix)) {
                cnt++;
                cout << books[i].name << "\n";
            }
        }
    }

    void add_user(){
        users[total_users++].read();
    }

    int find_book_idx_by_name(string name){
        for(int i = 0; i < total_books; ++i){
            if(books[i].name == name) return i;
        }
        return -1;
    }

    int find_user_idx_by_name(string name){
        for(int i = 0; i < total_users; ++i){
            if(users[i].name == name) return i;
        }
        return -1;
    }

    bool read_user_name_and_book_name(int &user_idx, int &book_idx, int trials = 3){
        string user_name;
        string book_name;

        while(trials){
            cout << "Enter user name and book name: ";
            cin >> user_name >> book_name;

            user_idx = find_user_idx_by_name(user_name);
            if(user_idx == -1){
                cout << "Invalid user name. Try again\n";
                continue;
            }

            book_idx = find_book_idx_by_name(book_name);
            if(book_idx == -1){
                cout << "Invalid book name. Try again\n";
                continue;
            }
            return true;
        }
        cout << "You did several trials. Try again later\n";
        return false;
    }

    void user_borrow_book(){
        int user_idx, book_idx;

        if(!read_user_name_and_book_name(user_idx, book_idx)) return;

        int user_id = users[user_idx].id;
        int book_id = books[book_idx].id;

        if(!books[book_idx].borrow(user_id)){
            cout << "No more copies available\n";
        }
        else{
            users[user_idx].borrow(book_id);
        }
    }

    void user_return_book(){
        int user_idx, book_idx;

        if(!read_user_name_and_book_name(user_idx, book_idx))
            return;

        int book_id = books[book_idx].id;
        books[book_idx].return_cpy();
        users[user_idx].return_cpy(book_id);
    }

    void print_library_by_id(){
        sort(books, books + total_books, comparebyid);

        cout << "\n";
        for(int i = 0; i < total_books; ++i){
            books[i].print();
        }
    }

    void print_library_by_name(){
        sort(books, books + total_books, comparebyname);

        cout << "\n";
        for(int i = 0; i < total_books; ++i){
            books[i].print();
        }
    }

    void print_users(){
        for(int i = 0; i < total_users; ++i){
            users[i].print();
        }
    }

    void print_who_borrowed_book_by_name(){
        string book_name;
        cout << "Enter book name: ";
        cin >> book_name;

        int book_idx = find_book_idx_by_name(book_name);
        if(book_idx == -1){
            cout << "Invalid book name\n";
            return;
        }
        int book_id = books[book_idx].id;
        if(books[book_idx].total_borrowed == 0){
            cout << "No borrowed copies\n";
            return;
        }

        for(int i = 0; i < total_users; ++i){
            if(users[i].is_borrowed(book_id)){
                cout << users[i].name << "\n";
            }
        }
    }

};

int main(){
    library_system library;
    library.run();
    return 0;
}
