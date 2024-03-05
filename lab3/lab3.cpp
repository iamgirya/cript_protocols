#include <iostream>
#include <chrono>
#include <random>
#include <vector>
#include <string>
#include <algorithm>
#include "windows.h"
#include <numeric>

using namespace std;
typedef long long ll;

class Polynom {
public:
	vector<bool> body;

	ll degree() {
		return body.size() - 1;
	}


	Polynom(vector<bool> body) {
		this->body = body;
	}

	static Polynom byDegree(ll degree)
	{
		vector<bool> newPoly(degree + 1, 0);
		newPoly[degree] = true;
		return Polynom(newPoly);
	}

	static Polynom byNumber(ll number)
	{
		vector<bool> newPoly;
		while (number) {
			newPoly.push_back(number % 2);
			number /= 2;
		}

		return Polynom(newPoly);
	}

	void print() {
		bool lastPrinted = false;
		for (ll i = this->degree(); i >= 0; i--) {
			if (this->body[i]) {
				if (lastPrinted) {
					cout << " + ";
				}
				if (i == 0) {
					cout << "1";
				}
				else {
					cout << "x^" << i;
				}
				lastPrinted = true;
			}
		}
		cout << endl;
	}

	Polynom operator+(Polynom& b) {
		ll newDegree = max(this->degree(), b.degree());
		vector<bool> newPoly(newDegree + 1, false);
		for (ll i = newDegree; i >= 0; i--) {
			if (i > this->degree()) {
				newPoly[i] = b.body[i];
			}
			else if (i > b.degree()) {
				newPoly[i] = this->body[i];
			}
			else {
				newPoly[i] = this->body[i] ^ b.body[i];
			}
		}
		ll zeroPadLeft = 0;
		for (ll i = newDegree; i >= 0; i--) {
			if (newPoly[i] == 0) {
				zeroPadLeft++;
			}
			else {
				break;
			}
		}
		newPoly.resize(newPoly.size() - zeroPadLeft);

		return Polynom(newPoly);
	}

	Polynom operator*(Polynom& b) {
		vector<bool> newPoly(this->degree() + b.degree() + 1, 0);
		for (ll i = this->degree(); i >= 0; i--) {
			if (!this->body[i]) {
				continue;
			}
			for (ll j = b.degree(); j >= 0; j--) {
				newPoly[i + j] = newPoly[i + j] ^ (this->body[i] * b.body[j]);
			}
		}

		return Polynom(newPoly);
	}

	bool operator>=(Polynom& b) {
		if (this->degree() == b.degree()) {
			for (ll i = b.degree(); i >= 0; i--) {
				if (this->body[i] != b.body[i]) {
					return this->body[i] > b.body[i];
				}
			}
			return true;
		}
		else
		{
			return this->degree() >= b.degree();
		}
	}

	Polynom operator/(Polynom& b) {
		Polynom dividedPoly = Polynom(this->body);
		while (dividedPoly.degree() > b.degree()) {
			ll divisionPartDegree = dividedPoly.degree() - b.degree();
			Polynom divisionPartPoly = Polynom::byDegree(divisionPartDegree);
			Polynom subPartPoly = b * divisionPartPoly;
			dividedPoly = dividedPoly + subPartPoly;
		}

		if (dividedPoly.degree() == b.degree()) {
			if (dividedPoly >= b) {
				dividedPoly = dividedPoly + b;
			}
		}

		return Polynom(dividedPoly);
	}
};

bool polynomIsIrreducible(Polynom& poly) {
	ll maxSearchDegree = poly.degree() / 2;
	ll maxSearchNumber = pow(2, maxSearchDegree+1)-1;
	for (ll i = 2; i <= maxSearchNumber; i++) {
		Polynom checkPoly = Polynom::byNumber(i);
		cout << "check: ";  checkPoly.print();
		Polynom remainder = poly / checkPoly;
		cout << "remainder is: ";  remainder.print();
		if (remainder.degree() == -1) {
			return false;
		}
	}
	return true;
}

bool polynomIsPrimitiveInGP(Polynom& poly, ll gpDegree) {
	if (polynomIsIrreducible(poly)) {
		ll maxDegree = pow(2, gpDegree) - 1;
		cout << endl;
		cout << "primitive check: " << endl;
		for (ll i = 1; i <= maxDegree; i++) {
			ll polyNumber = pow(2, i);
			Polynom checkPoly = Polynom::byNumber(polyNumber+1);
			cout << "check: ";  checkPoly.print();
			Polynom remainder = checkPoly / poly;
			cout << "remainder is: ";  remainder.print();
			if (remainder.degree() == -1) {
				return false;
			}
		}
		return true;
	}
	return false;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Polynom polyTrue = Polynom::byNumber(16+2+1);
	/*cout << polynomIsIrreducible(polyTrue) << endl << endl;


	Polynom polyFalse = Polynom::byNumber(128+1);
	cout << polynomIsIrreducible(polyFalse) << endl << endl;*/


	cout << polynomIsPrimitiveInGP(polyTrue, 4) << endl << endl;
}
