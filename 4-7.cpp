#include <iostream>
using namespace std;

struct Term {
    int coeff;
    int power;
    Term* next;

    Term(int c, int p) : coeff(c), power(p), next(nullptr) {}
};

class Polynomial {
private:
    Term* head;

public:

    Polynomial() : head(nullptr) {}

    ~Polynomial() {
        Term* current = head;
        while (current) {
            Term* temp = current;
            current = current->next;
            delete temp;
        }
    }

    void addTerm(int coeff, int power){
        if (coeff == 0) return;

        if (!head || head->power < power) {
            Term* newTerm = new Term(coeff, power);
            newTerm->next = head;
            head = newTerm;
            return;
        }

        Term* current = head;

        while (current->next && current->next->power > power) {
            current = current->next;
        }

        if (current->next && current->next->power == power) {

            current->next->coeff += coeff;

            if (current->next->coeff == 0) {
                Term* temp = current->next;
                current->next = temp->next;
                delete temp;
            }
        }


        else {
            Term* newTerm = new Term(coeff, power);
            newTerm->next = current->next;
            current->next = newTerm;
        }
        
    }

    Polynomial operator+(const Polynomial& other) const {
        Polynomial result;

        Term* p1 = this->head;
        Term* p2 = other.head;

        while (!(p1 == nullptr || p2 == nullptr)) {
            if (p1->power > p2->power) {
                result.addTerm(p1->coeff, p1->power);
                p1 = p1->next;
            }
            else if (p1->power < p2->power) {
                result.addTerm(p2->coeff, p2->power);
                p2 = p2->next;
            }
            else {
                result.addTerm(p1->coeff + p2->coeff, p1->power);
                p1 = p1->next;
                p2 = p2->next;
            }
        }
        if (p1 != nullptr) {
            while (p1) {
                result.addTerm(p1->coeff, p1->power);
                p1 = p1->next;
            }
        }
        else if (p2 != nullptr) {
            while (p2) {
                result.addTerm(p2->coeff, p2->power);
                p2 = p2->next;

            }
        }
        return result;
    }

    void print() const {
        Term* p = this->head;

        

        bool first = true;
        while (p) {
            if (!first) cout << " ";
            cout << p->coeff << "x^" << p->power;
            first = false;
            p = p->next;
        }
        cout << endl;
    }

};
int main() {
    Polynomial p1, p2;
    int n1, n2;
    int c, p;

    cin >> n1;
    for (int i = 0; i < n1; i++) {
        cin >> c >> p;
        p1.addTerm(c, p);
    }

    cin >> n2;
    for (int i = 0; i < n2; i++) {
        cin >> c >> p;
        p2.addTerm(c, p);
    }

    Polynomial result = p1 + p2;

    result.print();
    

    return 0;
}