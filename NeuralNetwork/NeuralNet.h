#pragma once

#ifndef __NeuralNet__
#define __NeuralNet__
#endif 

#include "HiddenLayer.h"
#include "InputLayer.h"
#include "OutputLayer.h"

class NeuralNet
{
public:
	NeuralNet();
	~NeuralNet();

	void initNet();
	void printNet();

private:
	InputLayer inputLayer;
	HiddenLayer hiddenLayer;
	std::vector<HiddenLayer> listOfHiddenLayer;
	OutputLayer outputLayer;
	int numberOfHiddenLayer;

};

NeuralNet::NeuralNet()
{
}

NeuralNet::~NeuralNet()
{
}