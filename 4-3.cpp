#include<iostream>
using namespace std;

class Time {
public:
    int H, M, S;
    Time(int h, int m, int s) : H(h), M(m), S(s){}

    Time operator+(const Time& input) {
        int totalS = S + input.S;
        int totalM = M + input.M + totalS / 60;
        int totalH = H + input.H + totalM / 60;
        return Time(totalH % 24, totalM % 60, totalS % 60);
    }

    Time operator-(const Time& input) {
        int t1 = H * 3600 + M * 60 + S;
        int t2 = input.H * 3600 + input.M * 60 + input.S;

        int diff = t1 - t2;
        if (diff < 0) return Time(0, 0, 0);

        return Time((diff / 3600), (diff % 3600) / 60, diff % 60);
    }

    void print_time() {
        cout << H << ":" << M << ":" << S << endl;
    }
};

Time operator*(const Time& t, int n) {
    int total_seconds = (t.H * 3600 + t.M * 60 + t.S) * n;

    int new_h = (total_seconds / 3600) % 24;
    int new_m = (total_seconds % 3600) / 60;
    int new_s = total_seconds % 60;

    return Time(new_h, new_m, new_s);
}

Time operator*(int n, const Time& t) {
    return t * n;
}

int main() {
    int a, b, c;
    int d, e, f;
    int num1, num2;

    cin >> a >> b >> c;
    cin >> d >> e >> f;
    cin >> num1 >> num2;

    Time t1(a, b, c);
    Time t2(d, e, f);

    Time sum = t1 + t2;
    Time diff = t1 - t2;
    Time mul1 = t1 * num1;
    Time mul2 = num2 * t2;

    sum.print_time();
    diff.print_time();
    mul1.print_time();
    mul2.print_time();

    return 0;
}