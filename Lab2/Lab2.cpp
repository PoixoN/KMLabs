#include <iostream>
#include <cmath>

using namespace std;

double f(double x, double y) {
    return (1) / (x * x + y * y);
}

void MRK(double a, double b, double h) {
    double n = (b - a) / h;
    const int size = (int)((2 - 1) / 0.1);
    double X[size];
    double K1[size];
    double K2[size];
    double Y[size];

    X[0] = a; Y[0] = 1.1323;

    for (int i = 1; i <= n; i++) {
        X[i] = a + i * h;
        K1[i] = h * f(X[i - 1], Y[i - 1]);
        K2[i] = h * f(X[i - 1] + h / 2.0, Y[i - 1] + K1[i] / 2.0);
        Y[i] = Y[i - 1] + K2[i];
    }

    for (int i = 0; i <= n; i++) {
        cout << "=================================" << endl;
        cout << "Iteration " << i + 1 << endl;
        cout << "X[" << i << "]=" << X[i] << endl;
        cout << "Y[" << i << "]=" << Y[i] << endl;
    }

    cin >> n;
}

int main() {
    double a = 1; 
    double b = 2; 
    double h = 0.1;

    MRK(a, b, h);

    return 0;
}