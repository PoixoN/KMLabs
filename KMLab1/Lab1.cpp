#include <math.h>
#include <iostream>

using namespace std;

const double A = 0.00000000001;
const double B = 5;
const double E = 0.05;

double f(double x)
{
	return 1 / (sqrt(x * (1 + x * x)));
}

double SimsonMethod() {
	double I = 0, I1 = -E - 1;

	for (int N = 2; (N <= 666) || (fabs(I1 - I) / 15 > E); N *= 2)
	{
		double h, sumA = 0, sumB = 0, sum = 0;
		h = (B - A) / (2 * N);

		for (int i = 1; i <= 2 * N - 1; i += 2)
		{
			sumB += f(A + h * i);
			sumA += f(A + h * (i + 1));
		}

		sum = f(A) + 4 * sumB + 2 * sumA + f(B);
		I = I1;
		I1 = (h / 3) * sum;
	}

	return I1;
}

int main() {
	cout << "Maevskiy Lubomyr Laba 1" << endl;
	cout << "result: " << SimsonMethod() << endl;
	return 0;
}