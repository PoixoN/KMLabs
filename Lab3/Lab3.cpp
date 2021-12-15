#include <iostream>
#include <cmath>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <clocale>
#include <map>
#include <vector>

using namespace std;

double stepsAmount = 10;
double intervalStart = 0;
double intervalEnd = 1;
double h = 0.1; // (intervalEnd - intervalStart) / stepsAmount;

class TridiagonalMatrixElement
{
public:
	double first;
	double middle;
	double last;
	double result;
};

class TridiagonalMatrixTempElement
{
public:
	double y;
	double alpha;
	double betta;
	double result;
};

double f(double x) {
	return 3;
}

double p(double x) {
	return 2 * x;
}

double q(double x) {
	return 2;
}

map<double, double> Progonka(vector<TridiagonalMatrixElement> elements) {
	vector<TridiagonalMatrixTempElement> tridiagonalTempElements;
	TridiagonalMatrixTempElement tmte;
	double y1 = elements[0].middle;

	tmte.y = y1;
	tmte.alpha = -elements[0].last / y1;
	tmte.betta = elements[0].result / y1;

	tridiagonalTempElements.push_back(tmte);

	for (int i = 1; i < elements.size(); i++)
	{
		auto matrixElement = elements[i];

		double y_i = matrixElement.middle + matrixElement.first * tridiagonalTempElements[i - 1].alpha;

		tmte.y = y_i;
		tmte.alpha = -matrixElement.last / y_i;
		tmte.betta = (matrixElement.result - matrixElement.first * tridiagonalTempElements[i - 1].betta) / y_i;
		tridiagonalTempElements.push_back(tmte);
	}

	pair<double, double> p;
	p.first = 0.0;
	p.second = 0.0;
	vector<pair<double, double>> resultList(elements.size(), p);

	p.first = intervalEnd;
	p.second = tridiagonalTempElements[tridiagonalTempElements.size() - 1].betta;

	resultList[elements.size() - 1] = p;

	for (int i = elements.size() - 2; i > 0; i--)
	{
		auto previousTempElement = tridiagonalTempElements[i];

		p.first = intervalStart + i * h;
		p.second = previousTempElement.alpha * resultList[i + 1].second + previousTempElement.betta;

		resultList[i] = p;
	}

	map<double, double> resultMap;

	for (pair<double, double> e : resultList)
	{
		resultMap[e.first] = e.second;
	}


	return resultMap;
}


map<double, double> MakeMatrix() {
	vector<TridiagonalMatrixElement> tridiagonalElements;;
	TridiagonalMatrixElement tme;

	tme.first = -1;
	tme.middle = 1;
	tme.last = 0;
	tme.result = 1;

	tridiagonalElements.push_back(tme);

	for (int position = 1; position < stepsAmount; position++)
	{
		double newX = intervalStart + position * h;

		tme.first = 1 / h / h - p(newX) / h / 2;
		tme.middle = q(newX) - 2 / h / h;
		tme.last = 1 / h / h + p(newX) / h / 2;
		tme.result = f(newX);

		tridiagonalElements.push_back(tme);
	}

	tme.first = 0.1;
	tme.middle = 1;
	tme.last = 0;
	tme.result = 0;

	tridiagonalElements.push_back(tme);

	return Progonka(tridiagonalElements);
}


void main()
{
	map<double, double> points = MakeMatrix();

	for (auto p : points)
	{
		cout << "x = " << p.first << "\ty = " << p.second << endl;
	}

	system("pause");
}