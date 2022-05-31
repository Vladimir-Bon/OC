#include <iostream>
#include <vector>

using namespace std;

const long long INF = 100000000005LL;

vector <long long> arr;

long long num;

int binSer(int q) {
	int r = num;
	int l = 0;
	while (l != r) {
		int t = (l + r) / 2;
		if (arr[t] >= q)
			r = t; 
		else l = t + 1;
	}
	return l;
}

int binSer1(int q) {
	int r = num;
	int l = 0;
	while (l != r) {
		int m = (l + r) / 2;
		if (arr[m] > q)
			r = m;
		else l = m + 1;
	}
	return l;
}

int main() {
	cin >> num;
	arr.resize(num);
	for (int i = 0; i < num; i++) {
		cin >> arr[i];
	}
	arr.push_back(INF);
	int j, x;
	cin >> j;
	for (int i = 0; i < j; i++) {
		cin >> x;
		int p1 = binSer(x);
		int p2 = binSer1(x);
		if (arr[p1] == x) 
			cout << 1 << " " << p1 << " " << p2 << endl;
		else cout << 0 << " " << p1 << " " << p2 << endl;
	}
	return 0;
}