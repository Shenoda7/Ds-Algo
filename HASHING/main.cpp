#include <bits/stdc++.h>
using namespace std;
#define loop(n) for(int i = 0; i < n; ++i)

int hash_string_lower_upper_digits(string str, int n = 65407) {
    int base = 2 * 26 + 10;
    long long nn = n;
    long long sum = 0;
    for(int i = 0; i < (int) str.size(); ++i) {
        int value = 0;
        if(islower(str[i]))
            value = str[i] - 'a';
        else if(isupper(str[i]))
            value = 26 + str[i] - 'A';//why we added 26 here ?it helps differentiate between uppercase and lowercase letters in the hash, and it ensures upper values are distinct from lower values.
        else if(isdigit(str[i]))
            value = 26 + 26 + str[i] - '0';
        else
            assert(false);

        sum = (sum * base + value) % nn;
    }
    return sum % nn;
}

int hash_string(string str, int n = 65407) {
	long long nn = n;
	long long sum = 0;
	for (int i = 0; i < (int) str.size(); ++i)
		sum = (sum * 26 + str[i] - 'a') % nn;
	return sum % nn;
}

int hash_string_folding(string str, int n = 65407) {
    long long nn = n;
    long long sum = 0;
    for(int i = 0; i < (int) str.size(); i+=4) {
        string block = str.substr(i, 4);
        sum += hash_string(block);
        sum %= nn;
    }
    return sum;
}

int key_based_on_different_varaibales(int number, string str1, string str2, int n = 65407) {
    long long nn = n;
    long long sum = 0;

    sum += hash_string(str1 + str2)  % nn;
    sum += number % nn;

    return sum % nn;
}

struct PhoneEntry {
    const static int INTERNAL_LIMIT = 65407;
    string name; //key
    string phone_number;//data

    int hash() {
        return hash_string(name, INTERNAL_LIMIT);
    }

    PhoneEntry(string name, string phone_number) :
            name(name), phone_number(phone_number) {
            }

    void print() {
        cout << "(" << name << ", " << phone_number << ") ";
    }
};

class PhoneHashTable {//chaining
private:
    int table_size;
    double limit_load_factor;
    vector<vector<PhoneEntry> > table;
    int total_elements = 0;

public:
    PhoneHashTable(int table_size = 10, double limit_load_factor = 0.75) :
            table_size(table_size) {
        table.resize(table_size);
    }

    void put(PhoneEntry phone) {
        int idx = phone.hash() % table_size;

        for(int i = 0; i < (int) table[idx].size(); ++i) {
            if(table[idx][i].name == phone.name) {
                //exist => update
                table[idx][i] = phone;
                return;
            }
        }
        table[idx].push_back(phone);
        total_elements++;
        rehashing();

    }

    bool remove(PhoneEntry phone) {
        int idx = phone.hash() % table_size;
        for(int i = 0; i < (int) table[idx].size(); ++i) {
            if(table[idx][i].name == phone.name) {
                //swap with last and remove last in o(1)
                swap(table[idx][i], table[idx].back());
                table[idx].pop_back();
                total_elements--;
                return true;
            }
        }
        return false;
    }

    bool get(PhoneEntry &phone) {
        int idx = phone.hash() % table_size;
        for(int i = 0; i < (int) table[idx].size(); ++i) {
            if(table[idx][i].name == phone.name) {
                phone = table[idx][i];
                return true;
            }
        }
        return false;
    }

    void print_all() {
        for(int hash = 0; hash < table_size; ++hash) {
            if(table[hash].size() == 0)
                continue;

            cout << "Hash " << hash << ": ";
            for(int i = 0; i < (int) table[hash].size(); ++i)
                table[hash][i].print();
            cout << "\n";
        }
    }

    void rehashing() {
        double cur_load_factor = (double) total_elements/table_size;
        if(cur_load_factor < limit_load_factor)
            return;

        PhoneHashTable new_table(2 * table_size, limit_load_factor);

        for(int hash_val = 0; hash_val < table_size; ++hash_val) {
            if(table[hash_val].size() == 0)
                continue;

            for(int i = 0; i < (int) table[hash_val].size(); ++i)
                new_table.put(table[hash_val][i]);
        }

        table_size *= 2;
        table = new_table.table;

        //print_all();
    }
};


class PhoneHashTable2 {
private:
    int table_size;
    vector<PhoneEntry*> table;
    PhoneEntry* deleted = new PhoneEntry("", "");
public:
    PhoneHashTable2(int table_size) :
            table_size(table_size) {
        table.resize(table_size);
        }

    bool put(PhoneEntry phone) {
        int idx = phone.hash() % table_size;
        for(int steps = 0; steps < table_size; ++steps) {
            if(table[idx] == deleted || !table[idx]) {
                table[idx] = new PhoneEntry(phone.name, phone.phone_number);
                return true;
            }
            else if(table[idx]->name == phone.name) {
                table[idx]->phone_number = phone.phone_number; //update
                return true;
            }
            idx = (idx + 1) % table_size;
        }
        return false; //can't insert full table
    }

    bool remove(PhoneEntry phone) {
        int idx = phone.hash() % table_size;

        for(int steps = 0; steps < table_size; ++steps) {
            if(!table[idx])
                break;
            if(table[idx] != deleted && table[idx]->name == phone.name) {
                delete table[idx];
                table[idx] = deleted;
                return true;
            }
            idx = (idx + 1) % table_size;
        }
        return false;
    }

    bool get(PhoneEntry &phone) {
        int idx = phone.hash() % table_size;

        for(int steps = 0; steps < table_size; ++steps) {
            if(!table[idx])
                break;
            if(table[idx] != deleted && table[idx]->name == phone.name) {
                phone.phone_number = table[idx]->phone_number;
                return true;
            }
            idx = (idx + 1) % table_size;
        }
        return false;
    }

    void print_all() {
        for(int hash_val = 0; hash_val < table_size; ++hash_val) {
            cout << hash_val << ": ";
            if(table[hash_val] == deleted)
                cout << " X ";
           else if(!table[hash_val])
                cout << " E ";
            else
                table[hash_val]->print();
            cout << "\n";
        }
        cout << "*****************************\n";
    }
};

void test1() {//chaining
    PhoneHashTable table(3);
	table.put(PhoneEntry("mostafa", "604-401-120"));
	table.put(PhoneEntry("mostafa", "604-401-777"));	// update
	table.put(PhoneEntry("ali", "604-401-343"));
	table.put(PhoneEntry("ziad", "604-401-17"));
	table.put(PhoneEntry("hany", "604-401-758"));
	table.put(PhoneEntry("belal", "604-401-550"));
	table.put(PhoneEntry("john", "604-401-223"));

	PhoneEntry e("mostafa", "");
	if (table.get(e))
		cout << e.phone_number << "\n";	// 604-401-777

    table.print_all();
    cout << table.remove(PhoneEntry("smith", "")) << "\n";
    cout << table.remove(PhoneEntry("hany", "")) << "\n";
    cout << table.remove(PhoneEntry("belal", "")) << "\n";

    table.print_all();
}

void test2() {
    PhoneHashTable2 table(11);
    table.put(PhoneEntry("mostafa", "604-401-120"));
    table.put(PhoneEntry("mostafa", "604-401-777"));
    table.put(PhoneEntry("ali", "604-401-343"));
    table.put(PhoneEntry("ziad", "604-401-17"));
    table.put(PhoneEntry("hany", "604-401-758"));
    table.put(PhoneEntry("belal", "604-401-550"));
    table.put(PhoneEntry("john", "604-401-223"));

    table.print_all();

    cout << table.remove(PhoneEntry("smith", "")) << "\n";
    cout << table.remove(PhoneEntry("hany", "")) << "\n";
    cout << table.remove(PhoneEntry("john", "")) << "\n";
    table.print_all();


    PhoneEntry e("belal", "");
    if(table.get(e))
        cout << e.phone_number << "\n";

    table.put(PhoneEntry("hany", "604-401-555"));
    table.print_all();
}

int count_common_substrs(string s1, string s2) {
    unordered_set<string> st1;
    for(int i = 0; i < (int) s1.size(); ++i) {
        for(int j = 0; j < (int) s1.size(); ++j) {
            st1.insert(s1.substr(i, j));
        }
    }

    unordered_set<string> st2;
    for(int i = 0; i < (int) s2.size(); ++i) {
        for(int j = 0; j < (int) s2.size(); ++j) {
            st2.insert(s2.substr(i, j));
        }
    }

    int cnt = 0;
    for(string str : st1)
        cnt += st2.count(str);

    return cnt;
}

int unique_angrams(string s1) {
    unordered_set<string> st1;
    for(int i = 0; i < (int) s1.size(); ++i) {
        for(int j = 0; j < (int) s1.size(); ++j) {
            string block = s1.substr(i, j);
            sort(block.begin(), block.end());
            st1.insert(block);
        }
    }

    return st1.size();
}

int main(){
    //test1();
    //test2();

    int res = unique_angrams("abcba");
    cout << res;
    return 0;
}
