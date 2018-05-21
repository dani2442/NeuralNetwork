#pragma once
#include "Neuron.h"

class Layer
{
public:
	Layer(){}
	~Layer(){}

	void printLayer() const{}

	const std::vector<Neuron>& getListOfNeurons()const { return listOfNeurons; }
	void setListOfNeurons(const std::vector<Neuron>& listOfNeurons) { this->listOfNeurons = listOfNeurons; }

	int getNumberOfNeuronsInLayer() const{ return numberOfNeuronInLayer; }
	void setNumberOfNeuronsInLayer(int numberOfNeuronInLayer) { this->numberOfNeuronInLayer = numberOfNeuronInLayer; }

protected:
	std::vector<Neuron> listOfNeurons;
	int numberOfNeuronInLayer;
};
