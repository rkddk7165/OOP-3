#include <iostream>
using namespace std;
struct Term {
    int coef;
    int deg;
    Term* next;

    Term(int c, int d) : coef(c), deg(d), next(nullptr) {}
};

class Polynomial {
private:
    Term* head;

    void insertTerm(int coef, int deg) {

        if (coef == 0) return;

        if (!head || head->deg < deg) {
            Term* newTerm = new Term(coef, deg);
            newTerm->next = head;
            head = newTerm;
            return;
        }

        Term* current = head;

        while (current->next && current->next->deg > deg) {
            current = current->next;
        }

        if (current->next && current->next->deg == deg) {

            current->next->coef += coef;

            if (current->next->coef == 0) {
                Term* temp = current->next;
                current->next = temp->next;
                delete temp;
            }
        }


        else {
            Term* newTerm = new Term(coef, deg);
            newTerm->next = current->next;
            current->next = newTerm;
        }
    }

public:
    Polynomial() : head(nullptr) {}

    ~Polynomial() {
        Term* current = this->head;
        while (current) {
            Term* temp = current;
            current = current->next;
            delete temp;
        }
    }

    void addTerm(int coef, int deg) {
        insertTerm(coef, deg);
    }

    Polynomial operator+(const Polynomial& other) const {
        Polynomial result;

        Term* p1 = this->head;
        Term* p2 = other.head;

        while (!(p1 == nullptr || p2 == nullptr)) {
            if (p1->deg > p2->deg) {
                result.addTerm(p1->coef, p1->deg);
                p1 = p1->next;
            }
            else if (p1->deg < p2->deg) {
                result.addTerm(p2->coef, p2->deg);
                p2 = p2->next;
            }
            else {
                result.addTerm(p1->coef + p2->coef, p1->deg);
                p1 = p1->next;
                p2 = p2->next;
            }
        }
        if (p1 != nullptr) {
            while (p1) {
                result.addTerm(p1->coef, p1->deg);
                p1 = p1->next;
            }
        }
        else if (p2 != nullptr) {
            while (p2) {
                result.addTerm(p2->coef, p2->deg);
                p2 = p2->next;

            }
        }
        return result;
    }

    Polynomial operator-(const Polynomial& other) const {
        Polynomial result;

        Term* p1 = this->head;
        Term* p2 = other.head;

        while (!(p1 == nullptr || p2 == nullptr)) {
            if (p1->deg > p2->deg) {
                result.addTerm(p1->coef, p1->deg);
                p1 = p1->next;
            }
            else if (p1->deg < p2->deg) {
                result.addTerm(-(p2->coef), p2->deg);
                p2 = p2->next;
            }
            else {
                result.addTerm(p1->coef - p2->coef, p1->deg);
                p1 = p1->next;
                p2 = p2->next;
            }
        }
        if (p1 != nullptr) {
            while (p1) {
                result.addTerm(p1->coef, p1->deg);
                p1 = p1->next;
            }
        }
        else if (p2 != nullptr) {
            while (p2) {
                result.addTerm(-(p2->coef), p2->deg);
                p2 = p2->next;

            }
        }
        return result;
    }

    double calculate(double x) const {
        Term* p = this->head;
        double sum = 0;
        while (p) {
            double tmp = 1;
            for (int i = 0; i < p->deg; i++) {
                tmp *= x;
            }
            tmp = tmp * p->coef;

            sum += tmp;
            p = p->next;
        }
        return sum;
    }

    Polynomial differentiation() const {
        Polynomial result;
        Term* p = this->head;

        while (p) {
            int new_coef = p->coef * p->deg;
            int new_deg = p->deg - 1;
            
            result.addTerm(new_coef, new_deg);
            p = p->next;

        }
        return result;
    }

    void print() const {
        Term* p = this->head;

        if (!p) { 
            cout << "0 " << endl; 
            return;
        }

        if (p->coef >= 0) {
            cout << p->coef << "x^" << p->deg << " ";
            p = p->next;
        }

        
        while (p) {
            if (p->coef >= 0) {
                cout << "+" << p->coef << "x^" << p->deg << " ";
                
            }
            else {
                cout << "-" << -(p->coef) << "x^" << p->deg << " ";
            }
            p = p->next;
        }
        cout << endl;
    }
};

int main() {
    Polynomial p1, p2;
    int c, d;
    char input = 0;

    while (1) {
        cin >> c >> d;

        if (c == -1 && d == -1) {
            cout << "P1: ";
            p1.print();
            break;
        }
        
        p1.addTerm(c, d);
    }

    while (1) {
        cin >> c >> d;

        if (c == -1 && d == -1) {
            cout << "P2: ";
            p2.print();
            break;
        }
        p2.addTerm(c, d);
    }

    while (1) {
        cin >> input;

        if (input == '+') {
            Polynomial result = p1 + p2;
            cout << "P1 + P2: ";
            result.print();
        }

        else if (input == '-') {
            Polynomial result = p1 - p2;
            cout << "P1 - P2: ";
            result.print();
        }
        
        else if (input == 'd') {
            Polynomial result = p1.differentiation();
            cout << "P1': ";
            result.print();
        }

        else if (input == 'v') {
            double x;
            cin >> x;
            double result = p1.calculate(x);
            cout << result << " " << endl;
        }

        else if (input == 'q') {
            break;
        }
        
    }
    cout << "Program exit!" << endl;
    return 0;
}
