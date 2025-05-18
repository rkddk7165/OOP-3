#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class Complex {
private:
    double real;
    double imag;

public:
    Complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}

    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }

    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imag - other.imag);
    }

    Complex operator*(const Complex& other) const {
        double r = real * other.real - imag * other.imag;
        double i = real * other.imag + imag * other.real;
        return Complex(r, i);
    }

    Complex operator/(const Complex& other) const {
        double denominator = other.real * other.real + other.imag * other.imag;
        double r = (real * other.real + imag * other.imag) / denominator;
        double i = (imag * other.real - real * other.imag) / denominator;
        return Complex(r, i);
    }

    void print(const string& label) const {
        cout << label << fixed << setprecision(1) << real;
        if (imag >= 0)
            cout << " + " << imag << "i" << endl;
        else
            cout << " - " << -imag << "i" << endl;
    }
};

int main() {
    double r1, i1, r2, i2;
    cin >> r1 >> i1;
    cin >> r2 >> i2;

    Complex c1(r1, i1);
    Complex c2(r2, i2);

    (c1 + c2).print("Addition result: ");
    (c1 - c2).print("Subtraction result: ");
    (c1 * c2).print("Multiplication result: ");
    (c1 / c2).print("Division result: ");

    return 0;
}
