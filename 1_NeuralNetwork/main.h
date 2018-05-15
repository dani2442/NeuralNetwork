#ifndef _MAIN_H

#define _MAIN_H
#include <math.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

const double randMax = 3;

class NN
{
public:
	NN(double, double);
	~NN();
	double sigmoid(double);
private:
	double z;
	double w1, w2;
	double b;
};

NN::NN(double m1, double m2)
{
	w1 =(double)rand() / (RAND_MAX+1.0);
	w2 = (double)rand() / (RAND_MAX + 1.0);
	b = (double)rand() / (RAND_MAX + 1.0);
	z = m1 * w1 + m2 * w2;
	z = sigmoid(z);
	cout << w1 << endl;
	cout << w2 << endl;
	cout << b << endl;
	cout << z;
}

NN::~NN()
{
}

inline double NN::sigmoid(double x)
{
	return 1 / (1 + exp(-x));
}
#endif // !_MAIN_H