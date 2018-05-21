#pragma once
#include <vector>
#include <iostream>
#include <stdlib.h>


class Neuron
{
public:
	Neuron();
	~Neuron();

	double initNeuron() { return ((double)rand() / (RAND_MAX)); }

	const std::vector<double>& getListOfWeightIn() const{ return listOfWeightIn; }
	std::vector<double>& getListOfWeightOut(){ return listOfWeightOut; }

	void setListOfWeightIn(const std::vector<double>& listOfWeightIn) { this->listOfWeightIn = listOfWeightIn; }
	void setListOfWeightOut(const std::vector<double>& listOfWeightOut) { this->listOfWeightOut = listOfWeightOut; }

private:
	std::vector<double> listOfWeightIn;
	std::vector<double> listOfWeightOut;
};

inline Neuron::Neuron()
{
}

inline Neuron::~Neuron()
{
}
