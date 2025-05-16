#include <iostream>
#include <string>
using namespace std;

int main() {
    int n;
    cin >> n;

    int sum = 0;
    string input;

    for (int i = 0; i < n; i++) {
        cin >> input;
        try {
            int num = stoi(input);
            sum += num;
        }
        catch (...) {
            cout << "Error occurred" << endl;
        }
    }

    cout << "Total sum: " << sum << endl;
    return 0;
}