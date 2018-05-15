#pragma once
#ifndef __Neuron__
	#define __Neuron__
#endif // !__Neuron__


#ifndef _VECTOR_
	#include <vector>
#endif 

#include <iostream>
#include <stdlib.h>


class Neuron
{
public:
	Neuron();
	~Neuron();

	double initNeuron() { return ((double)rand() / (RAND_MAX)); }

	std::vector<double>& getListOfWeightIn() { return listOfWeightIn; }
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
