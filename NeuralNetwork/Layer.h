#pragma once
#ifndef __Layer__
#define __Layer__
#endif // !__Layer__

#ifndef __Neuron__
#include "Neuron.h"
#endif


class Layer
{
public:
	Layer(){}
	~Layer(){}

	void printLayer() const{}

	std::vector<Neuron> getListOfNeurons()const { return listOfNeurons; }
	void setListOfNeurons(const std::vector<Neuron>& listOfNeurons) { this->listOfNeurons = listOfNeurons; }

	int getNumberOfNeuronsInLayer() const{ return numberOfNeuronInLayer; }
	void setNumberOfNeuronsInLayer(int numberOfNeuronInLayer) { this->numberOfNeuronInLayer = numberOfNeuronInLayer; }

private:
	std::vector<Neuron> listOfNeurons;
	int numberOfNeuronInLayer;
};
