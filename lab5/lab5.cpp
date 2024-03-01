#include <iostream>
#include <fstream>
#include <chrono>
#include <random>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <algorithm>
#include "windows.h"
#include <numeric>

using namespace std;
typedef long long ll;

bool fullSquareRootTest(ll n) {
	for (ll i = 2; i < (n - 1) / 2; i++) {
		if (i * i % n == 1) {
			return false;
		}
	}
	return true;
}

bool makeSquareRootTestByNumber(ll n, ll number) {
	number = max(number, 2);
	if (number < (n - 1) / 2) {
		if ((number * number) % n == 1) {
			return false;
		}
	}
	return true;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	ofstream output("out.txt");
	ofstream outputOnly100("outOnly100.txt");

	srand(100);

	for (ll i = 2; i <= 1000000000;i ++) { 
		ll j;
		for (j = 1; j <= 100; j++) {
			int testNum = rand() % (i-1)/2 + 1;
			if (!makeSquareRootTestByNumber(i, testNum)) {
				break;
			}
		}
		if (j == 101) {
			output << i << ' ' << "Простое";
			output << endl;
		}
		else {
			output << i << ' ' << "Непростое на тесте " << j;
			output << endl;

			if (j == 100) {
				outputOnly100 << i << ' ' << "Непростое на тесте " << j;
				outputOnly100 << endl;
			}
		}
	}
}
