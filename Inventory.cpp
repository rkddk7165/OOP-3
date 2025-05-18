#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

class Book {
    char* title;
    char* author;
    char* isbn;
    double price;

    void copyString(char*& dest, const char* src) {
        int len = 0;
        while (src[len] != '\0') len++;

        dest = new char[len + 1];

        for (int i = 0; i <= len; i++) {
            dest[i] = src[i];
        }
    }

    bool myStrcmp(const char* a, const char* b) const {
        int i = 0;
        while (a[i] && b[i]) {
            if (a[i] != b[i]) return false;
            i++;
        }
        return a[i] == '\0' && b[i] == '\0';
    }

public:
    Book(const char* t, const char* a, const char* i, double p) {
        copyString(title, t);
        copyString(author, a);
        copyString(isbn, i);
        price = p;
    }

    Book(const Book& other){
        copyString(title, other.title);
        copyString(author, other.author);
        copyString(isbn, other.isbn);
        price = other.price;
    }

    ~Book() {
        delete[] title;
        delete[] author;
        delete[] isbn;
    }

    bool operator==(const Book& other) const {
        return myStrcmp(this->getISBN(), other.isbn);
    }

    const char* getISBN() const {
        return isbn;
    }

    void printInfo() const {
        cout << "[" << title << "] by " << author <<
            " (ISBN: " << isbn << ", Price: " << price << ")" << endl;
    }

    
};



class Inventory {
    Book** books;
    int size;
    int capacity;

    void resize() {
        capacity *= 2;
        Book** newBooks = new Book * [capacity];
        for (int i = 0; i < size; i++) {
            newBooks[i] = books[i];
        }
        delete[] books;
        books = newBooks;
    }

    bool myStrcmp(const char* a, const char* b) const {
        int i = 0;
        while (a[i] && b[i]) {
            if (a[i] != b[i]) return false;
            i++;
        }
        return a[i] == '\0' && b[i] == '\0';
    }

public:
    Inventory(int cap = 10) {
        size = 0;
        capacity = cap;
        books = new Book * [capacity];
    }

    ~Inventory() {
        for (int i = 0; i < size; i++) {
            delete books[i];
        }
        delete[] books;
    }

    void addBook(const Book& b) {
        for (int i = 0; i < size; i++) {
            if (*books[i] == b) {
                throw runtime_error("Duplicate book!");
            }
        }
        if (size == capacity) resize();
        books[size++] = new Book(b);
        cout << "Book Added!" << endl;
    }

    void removeBook(const char* isbn) {
        for (int i = 0; i < size; i++) {
            if (myStrcmp(books[i]->getISBN(), isbn)) {
                delete books[i];
                for (int j = i; j < size - 1; j++) {
                    books[j] = books[j + 1];
                }
                size--;
                cout << "Book Removed!" << endl;
                return;
            }
        }
        throw runtime_error("Book not found!");
    }

    Book* searchBook(const char* isbn) {
        for (int i = 0; i < size; i++) {
            if (myStrcmp(books[i]->getISBN(), isbn)) {
                return books[i];
            }
        }
        return nullptr;
    }

    void printAll() const {
        cout << "Book List:" << endl;
        for (int i = 0; i < size; i++) {
            books[i]->printInfo();
        }
    }
};

int main() {
    Inventory inv;
    int choice;

    while (true) {
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            char t[100], a[100], i[100];
            double p;
            cout << "Enter title, author, isbn, price:\n";
            cin.getline(t, 100);
            cin.getline(a, 100);
            cin.getline(i, 100);
            cin >> p;
            cin.ignore();

            try {
                inv.addBook(Book(t, a, i, p));
            }
            catch (exception& e) {
                cout << "Error: " << e.what() << endl;
            }
        }
        else if (choice == 2) {
            char i[100];
            cin.getline(i, 100);
            try {
                inv.removeBook(i);
            }
            catch (exception& e) {
                cout << "Error: " << e.what() << endl;
            }
        }
        else if (choice == 3) {
            char i[100];
            cin.getline(i, 100);
            Book* b = inv.searchBook(i);
            if (b) b->printInfo();
            else cout << "Book not found!\n";
        }
        else if (choice == 4) {
            inv.printAll();
        }
        else if (choice == 5) {
            cout << "Program exit!" << endl;
            break;
        }
    }

    return 0;
}

