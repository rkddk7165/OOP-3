#include <iostream>
#include <string>
using namespace std;

class Student {
protected:
    string name;
    int id;
    string major;

public:

    Student (string n, int i, string m) : name(n), id(i), major(m) {}

    virtual void printInfo() const = 0;

    int getId() const {
        return id;
    }

    bool operator==(const Student& other) const {
        return this->id == other.id;
    }

    virtual ~Student(){}

};

class Undergraduate : public Student {
private:
    int year;

public:

    Undergraduate(string n, int i, string m, int y) : Student(n, i, m), year(y){}

    virtual void printInfo() const{
        cout << "[Undergraduate] Name: " << name << ", ID: " << id << ", Major: " <<
            major << ", Year: " << year << endl;
    }

};

class Graduate : public Student {
private:
    string advisor;

public:

    Graduate(string n, int i, string m, string a) : Student(n, i, m), advisor(a) {}

    virtual void printInfo() const {
        cout << "[Graduate] Name: " << name << ", ID: " << id << ", Major: " <<
            major << ", Advisor: " << advisor << endl;
    }
};

struct Node {
    Student* student;
    Node* next;

    Node(Student* s) : student(s), next(nullptr) {}
};

class StudentList {
private:
    Node* head;

public:
    StudentList() : head(nullptr) {}

    ~StudentList() {
        Node* current = head;
        while (current) {
            Node* tmp = current;
            current = current->next;
            delete tmp->student;
            delete tmp;
        }
    }

    void AddStudent(Student* s) {
        Node* newNode = new Node(s);

        if (!head || head->student->getId() > s->getId()) {
            newNode->next = head;
            head = newNode;
            return;
        }

        Node* current = head;
        Node* prev = nullptr;

        while (current && current->student->getId() < s->getId()) {
            prev = current;
            current = current->next;
        }

        prev->next = newNode;
        newNode->next = current;
    }

    void PrintAll() const {
        if (!head) return;

        Node* current = head;
        while (current) {
            current->student->printInfo();
            current = current->next;
        }
    }

    void FindStudent(int targetID) const {
        if (!head) return;

        Node* current = head;
        while (current) {
            if (current->student->getId() == targetID) {
                current->student->printInfo();
                return;
            }
            current = current->next;
        }
        cout << "Student not found" << endl;
    }

    
};

int main() {
    string command;
    StudentList list;

    while (1) {
        cin >> command;

        if (command == "ADD") {
            string name, type;
            int id;
            string major;
            

            cin >> type;

            if (type == "UG") {
                int year;
                cin >> name >> id >> major >> year;
                list.AddStudent(new Undergraduate(name, id, major, year));
            }

            else if (type == "GR") {
                string advisor;
                cin >> name >> id >> major >> advisor;
                list.AddStudent(new Graduate(name, id, major, advisor));
            }
        }

        else if (command == "FIND") {
            int id;
            cin >> id;
            list.FindStudent(id);
        }

        else if (command == "PRINT") {
            list.PrintAll();
        }

        else if (command == "EXIT") {
            break;
        }
    }

    return 0;
}