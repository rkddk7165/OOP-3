#include <iostream>
using namespace std;

void go(int n, int start, int end, int tmp) {
	if (n == 1) {
		cout << start << " " << end << endl;
		return;
	}

	go(n - 1, start, tmp, end);
	cout << start << " " << end << endl;
	go(n - 1, tmp, end, start);

}

int main() {
	int n;
	cin >> n;

	int tmp = 1;
	for (int i = 0; i < n; i++) {
		tmp *= 2;
	}
	tmp--;

	cout << tmp << endl;
	go(n, 1, 3, 2);

	return 0;
}