#include <iostream>
using namespace std;

class Complex {
private:
    double real;
    double imag;

    void checkAndPrint(double value) const {

        if (value == static_cast<int>(value)) {
            cout << static_cast<int>(value);
        }

        else {
            cout << fixed;
            cout.precision(1);
            cout << value;
        }
    }
public:

    Complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}

    Complex operator+(const Complex& other) const {
        double rst_real = this->real + other.real;
        double rst_imag = this->imag + other.imag;

        return Complex(rst_real, rst_imag);
    }

    Complex operator-(const Complex& other) const {
        double rst_real = this->real - other.real;
        double rst_imag = this->imag - other.imag;

        return Complex(rst_real, rst_imag);
    }

    Complex operator*(const Complex& other) const {
        double rst_real = this->real * other.real - this->imag * other.imag;
        double rst_imag = this->real * other.imag + this->imag * other.real;

        return Complex(rst_real, rst_imag);
    }

    Complex operator/(const Complex& other) const {
        double denominator = other.real * other.real + other.imag * other.imag;

        if (denominator == 0) return Complex();

        double numerator_real = this->real * other.real + this->imag * other.imag;
        double numerator_imag = this->imag * other.real - this->real * other.imag;

        double rst_real = numerator_real / denominator;
        double rst_imag = numerator_imag / denominator;

        return Complex(rst_real, rst_imag);
    }

    void print(const string& str) const {
        
        cout << str;
        checkAndPrint(real);

        if (imag >= 0) {
            cout << " + ";
            checkAndPrint(imag);
            cout << "i" << endl;
        }
        else {
            cout << " - ";
            checkAndPrint(-imag);
            cout << "i" << endl;
        }
    }
};

int main() {
    

    double r1, i1, r2, i2;

    cin >> r1 >> i1;
    cin >> r2 >> i2;

    Complex c1(r1, i1);
    Complex c2(r2, i2);

    Complex add = c1 + c2;
    Complex sub = c1 - c2;
    Complex mul = c1 * c2;
    Complex div = c1 / c2;

    add.print("Addition result: ");
    sub.print("Subtraction result: ");
    mul.print("Multiplication result: ");
    div.print("Division result: ");
    

    return 0;
}