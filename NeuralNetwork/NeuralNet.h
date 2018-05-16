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
	void printNet() const;

private:
	InputLayer inputLayer;
	HiddenLayer hiddenLayer;
	std::vector<HiddenLayer> listOfHiddenLayer;
	OutputLayer outputLayer;
	int numberOfHiddenLayers;

};

NeuralNet::NeuralNet()
{
}

NeuralNet::~NeuralNet()
{
}

inline void NeuralNet::initNet()
{
	inputLayer.setNumberOfNeuronsInLayer(2); // Input layer neurons
	numberOfHiddenLayers = 2;	// Number of hidden layers

	for (int i = 0; i < numberOfHiddenLayers; i++) {
		hiddenLayer.setNumberOfNeuronsInLayer(3); // Number of neurons in layer
		listOfHiddenLayer.push_back(hiddenLayer);
	}

	outputLayer.setNumberOfNeuronsInLayer(1); // Output layer neurons
	
	// Init 
	inputLayer = inputLayer.initLayer(inputLayer);
	listOfHiddenLayer = hiddenLayer.initLayer(hiddenLayer, listOfHiddenLayer, inputLayer, outputLayer);
	outputLayer = outputLayer.initLayer(outputLayer);
}

inline void NeuralNet::printNet() const
{
	inputLayer.printLayer(inputLayer);
	std::cout<<std::endl;
	hiddenLayer.printLayer(listOfHiddenLayer);
	std::cout<<std::endl;
	outputLayer.printLayer(outputLayer);

	getchar();
}
//		Input			Hidden			Ouput
//		
//		2 Neurons		3 Layers*		1 neuron
//						3 Neuron
//
//
//
//
//
//
