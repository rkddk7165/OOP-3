#include <iostream>
#include <string>

using namespace std;

class MyString {
private:
    char* str;

public:
    MyString(const char* s = "") {
        str = new char[myStrlen(s) + 1];
        myStrcpy(str, s);
    }

    ~MyString() {
        delete[] str;
    }

    MyString& operator=(const MyString& other) {
        if (this == &other) return *this;

        delete[] this->str;
        this->str = new char[myStrlen(other.str) + 1];
        myStrcpy(this->str, other.str);

        return *this;

    }

    MyString operator+(const MyString& other) const {
        char* result = new char[myStrlen(str) + myStrlen(other.getString()) + 1];
        myStrcpy(result, str);
        myStrcat(result, other.getString());

        MyString result_string(result);
        delete[] result;

        return result_string;
    }

    bool operator==(const MyString& other) const {

        if (myStrlen(str) != myStrlen(other.getString())) return false;

        else {
            for (int i = 0; i < myStrlen(str); i++) {
                if (str[i] != other.getString()[i]) return false;
            }
            return true;
        }

    }

    friend ostream& operator<<(ostream& os, const MyString& s) {
        os << s.str;
        return os;
        
    }

    const char* getString() const {
        return str;
    }

private:

    size_t myStrlen(const char* s) const {
        size_t length = 0;
        while (s[length] != '\0') {
            length++;
        }
        return length;
    }

    void myStrcpy(char* dest, const char* src) const {
        size_t i = 0;
        while (src[i] != '\0') {
            dest[i] = src[i];
            i++;
        }
        dest[i] = '\0';
    }

    void myStrcat(char* dest, const char* src) const {
        size_t destLen = myStrlen(dest);
        size_t i = 0;
        while (src[i] != '\0') {
            dest[destLen + i] = src[i];
            i++;
        }
        dest[destLen + i] = '\0';
    }

};

void initialize(char[]);

int main() {
    char str1[100] = { 0 };
    char str2[100] = { 0 };
    string input;

    cin.getline(str1, 100);
    cin.getline(str2, 100);

    MyString s1(str1), s2(str2);

    while (getline(cin, input)) {
        
        if (input == "0") {
            break;
        }

        else if (input == "+") {
            MyString result = s1 + s2;
            cout << result << endl;
        }

        else if (input == "=") {
            if (s1 == s2) {
                cout << "Equal" << endl;
            }
            else cout << "Not equal" << endl;
        }

        else if (input == "f") {
            initialize(str1);
            cin.getline(str1, 100);
            s1 = MyString(str1);
        }

        else if (input == "s") {
            initialize(str2);
            cin.getline(str2, 100);
            s2 = MyString(str2);
        }

    }

    cout << "Program exit!" << endl;
    return 0;
}

void initialize(char arr[]) {
    for (int i = 0; i < 100; i++) {
        arr[i] = 0;
    }
}