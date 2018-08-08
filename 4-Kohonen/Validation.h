#pragma once
#include "NeuralNet.h"

class Validation
{
public:
	Validation();
	~Validation();

	virtual void netValidation(NeuralNet& n) {}; // TODO virtual in this function
private:

};

Validation::Validation()
{
}

Validation::~Validation()
{
}