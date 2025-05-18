#include <iostream>
#include <string>
using namespace std;

struct Term {
    int coef;   // Coefficient
    int deg;    // Degree
    Term* next;

    Term(int c, int d) : coef(c), deg(d), next(nullptr) {}
};

class Polynomial {
private:
    Term* head;

    void insertTerm(int coef, int deg) {
        if (coef == 0) return;

        Term* newTerm = new Term(coef, deg);

        if (!head || deg > head->deg) {
            newTerm->next = head;
            head = newTerm;
            return;
        }

        Term* current = head;
        Term* prev = nullptr;

        while (current && current->deg > deg) {
            prev = current;
            current = current->next;
        }

        if (current && current->deg == deg) {
            current->coef += coef;
            if (current->coef == 0) {
                if (prev) prev->next = current->next;
                else head = current->next;
                delete current;
            }
            delete newTerm;
        } else {
            newTerm->next = current;
            if (prev) prev->next = newTerm;
            else head = newTerm;
        }
    }

public:
    Polynomial() : head(nullptr) {}

    ~Polynomial() {
        while (head) {
            Term* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void addTerm(int coef, int deg) {
        insertTerm(coef, deg);
    }

    Polynomial operator+(const Polynomial& other) const {
        Polynomial result;
        Term* p1 = head;
        Term* p2 = other.head;

        while (p1 || p2) {
            if (p1 && (!p2 || p1->deg > p2->deg)) {
                result.addTerm(p1->coef, p1->deg);
                p1 = p1->next;
            } else if (p2 && (!p1 || p2->deg > p1->deg)) {
                result.addTerm(p2->coef, p2->deg);
                p2 = p2->next;
            } else {
                result.addTerm(p1->coef + p2->coef, p1->deg);
                p1 = p1->next;
                p2 = p2->next;
            }
        }
        return result;
    }

    Polynomial operator-(const Polynomial& other) const {
        Polynomial result;
        Term* p1 = head;
        Term* p2 = other.head;

        while (p1 || p2) {
            if (p1 && (!p2 || p1->deg > p2->deg)) {
                result.addTerm(p1->coef, p1->deg);
                p1 = p1->next;
            } else if (p2 && (!p1 || p2->deg > p1->deg)) {
                result.addTerm(-p2->coef, p2->deg);
                p2 = p2->next;
            } else {
                result.addTerm(p1->coef - p2->coef, p1->deg);
                p1 = p1->next;
                p2 = p2->next;
            }
        }
        return result;
    }

    double calculate(double x) const {
        double result = 0.0;
        for (Term* current = head; current; current = current->next) {
            double termResult = current->coef;
            for (int i = 0; i < current->deg; ++i)
                termResult *= x;
            result += termResult;
        }
        return result;
    }

    Polynomial differentiation() const {
        Polynomial result;
        for (Term* current = head; current; current = current->next) {
            if (current->deg != 0) {
                result.addTerm(current->coef * current->deg, current->deg - 1);
            }
        }
        return result;
    }

    void print() const {
        if (!head) {
            cout << "0 ";
            return;
        }
        Term* current = head;
        while (current) {
            if (current != head && current->coef > 0) cout << "+";
            cout << current->coef << "x^" << current->deg << " ";
            current = current->next;
        }
    }
};

Polynomial readPolynomial() {
    Polynomial p;
    int coef, deg;
    while (cin >> coef >> deg && !(coef == -1 && deg == -1)) {
        p.addTerm(coef, deg);
    }
    return p;
}

int main() {
    Polynomial P1 = readPolynomial();
    Polynomial P2 = readPolynomial();

    string cmd;
    while (cin >> cmd) {
        if (cmd == "+") {
            cout << "P1: "; P1.print(); cout << endl;
            cout << "P2: "; P2.print(); cout << endl;
            cout << "P1 + P2: "; (P1 + P2).print(); cout << endl;
        } else if (cmd == "-") {
            cout << "P1: "; P1.print(); cout << endl;
            cout << "P2: "; P2.print(); cout << endl;
            cout << "P1 - P2: "; (P1 - P2).print(); cout << endl;
        } else if (cmd == "d") {
            cout << "P1: "; P1.print(); cout << endl;
            cout << "P2: "; P2.print(); cout << endl;
            cout << "P1': "; P1.differentiation().print(); cout << endl;
        } else if (cmd == "v") {
            double x; cin >> x;
            cout << P1.calculate(x) << " " << endl;
        } else if (cmd == "q") {
            cout << "Program exit!" << endl;
            break;
        }
    }
    return 0;
}
