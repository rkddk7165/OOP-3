#include <iostream>
#include <string>
using namespace std;


template <typename K, typename V>
class TABLE {
private:
    K key[100];
    V value[100];
    int table_size;

public:
    TABLE () : table_size(0) {}


    void put(K k, V v) {
        for (int i = 0; i < table_size; i++) {
            if (key[i] == k) {
                value[i] = v;
                return;
            }   
        }

        if (table_size < 100) {
            key[table_size] = k;
            value[table_size++] = v;

        }
    }

    void get(K k) {
        for (int i = 0; i < table_size; i++) {
            if (key[i] == k) {
                cout << value[i] << endl;
                return;
            }
        }
        cout << "None" << endl;
    }

    void size() {
        cout << table_size << endl;
    }
};

int main() {
    string key_type, value_type;
    int n;
    cin >> key_type >> value_type;
    cin >> n;

    if (key_type == "string" && value_type == "int") {
        TABLE<string, int> table;
        for (int i = 0; i < n; i++) {
            string cmd;
            cin >> cmd;
            if (cmd == "put") {
                string k;
                int v;
                cin >> k >> v;
                table.put(k, v);
            }
            else if (cmd == "get") {
                string k;
                cin >> k;
                table.get(k);
            }
            else if (cmd == "size") {
                table.size();
            }
        }
    }
    else if (key_type == "int" && value_type == "string") {
        TABLE<int, string> table;
        for (int i = 0; i < n; i++) {
            string cmd;
            cin >> cmd;
            if (cmd == "put") {
                int k;
                string v;
                cin >> k >> v;
                table.put(k, v);
            }
            else if (cmd == "get") {
                int k;
                cin >> k;
                table.get(k);
            }
            else if (cmd == "size") {
                table.size();
            }
        }
    }
}