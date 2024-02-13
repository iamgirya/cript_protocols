#include <iostream>
#include <chrono>
#include <random>
#include <vector>

using namespace std;
typedef long long ll;

ll gcd(ll a, ll b) {
    while (a && b)
        if (a > b) a %= b;
        else b %= a;
    return a + b;
}

ll firstEuler(ll num) {
    ll sum = 1;
    for (int i = 2; i < num; i++) {
        if (gcd(num, i) == 1) {
            sum += 1;
        }
    }
    return sum;
}

ll secondEuler(ll num) {
    ll ret = 1, i, pow;
    for (i = 2; i <= sqrt(num) && num != 1; i++)
    {
        pow = 1;
        while (!(num % i))
        {
            num /= i;
            pow *= i;
        }
        ret *= (pow - (pow / i));
    }
    if (num != 1)
        ret *= (num - 1);
    return ret;
}

void testEulersByNumbersCount(ll num) {
    auto begin = chrono::system_clock::now();
    auto end = chrono::system_clock::now();
    auto diff = end - begin;

    vector<ll> randNumbers = vector<ll>(num);
    for (int i = 0; i < num; i++) {
        ll randNum = rand();
        if (randNum <= 10000000)
            randNum += 10000000;
        randNumbers[i] = randNum;
    }

    begin = chrono::system_clock::now();
    for (int i = 0; i < num; i++)
        firstEuler(randNumbers[i]);
    end = chrono::system_clock::now();
    diff = end - begin;
    cout << chrono::duration <double, milli>(diff).count() / 1000 << "s of fisrt" << endl;

    begin = chrono::system_clock::now();
    for (int i = 0; i < num; i++)
       secondEuler(randNumbers[i]);
    end = chrono::system_clock::now();
    diff = end - begin;
    cout << chrono::duration <double, milli>(diff).count() / 1000 << "s of second" << endl;
}


int main()
{
    testEulersByNumbersCount(100);
}
// 1 - 80 секунд.
// 2 - 0.000838 секунд
