#pragma once

#ifndef __InputLayer__
#define __InputLayer__
#endif 

#ifndef __Layer__
#include "Layer.h"
#endif

class InputLayer : public Layer
{
public:
	InputLayer() ;
	~InputLayer() ;

	InputLayer& initLayer(InputLayer& inputLayer);
	void printLayer(const InputLayer& inputLayer) const;

private:

};

InputLayer::InputLayer() :  Layer()
{
}

InputLayer::~InputLayer()
{
}

inline InputLayer& InputLayer::initLayer(InputLayer& inputLayer)
{
	std::vector<double> listOfWeightInTemp;
	std::vector<Neuron>listOfNeurons;

	for (int i = 0; i < inputLayer.getNumberOfNeuronsInLayer(); i++) {
		Neuron neuron;
		listOfWeightInTemp.push_back(neuron.initNeuron());

		neuron.setListOfWeightIn(listOfWeightInTemp);
		listOfNeurons.push_back(neuron);

		listOfWeightInTemp.clear();
	}
	inputLayer.setListOfNeurons(listOfNeurons);
	return inputLayer;
}

inline void InputLayer::printLayer(const InputLayer & inputLayer) const
{
	std::cout << "### INPUT LAYER ###"<<std::endl;
	int n = 1;
	for (Neuron neuron : inputLayer.getListOfNeurons()) {
		std::cout << "Neuron #" << n << ":"<<std::endl;
		std::cout << "Input Weights:"<<std::endl;
		std::vector<double> weights = neuron.getListOfWeightIn();
		for (double weight : weights) {
			std::cout << weight << std::endl;
		}
		n++;
	}
}
