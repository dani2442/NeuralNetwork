#pragma once
#include "Layer.h"


class OutputLayer : public Layer
{
public:
	OutputLayer();
	~OutputLayer();

	OutputLayer& initLayer(OutputLayer &ouputLayer);
	void printLayer(const OutputLayer& outputLayer)const;
private:

};

OutputLayer::OutputLayer() : Layer()
{
}

OutputLayer::~OutputLayer()
{
}

inline OutputLayer & OutputLayer::initLayer(OutputLayer & outputLayer)
{
	std::vector<double>listOfWeightOutTemp;
	std::vector<Neuron> listOfNeurons;

	for (int i = 0; i < outputLayer.getNumberOfNeuronsInLayer(); i++) {
		Neuron neuron;

		listOfWeightOutTemp.push_back(neuron.initNeuron());

		neuron.setListOfWeightOut(listOfWeightOutTemp);
		listOfNeurons.push_back(neuron);

		listOfWeightOutTemp.clear();
	}
	outputLayer.setListOfNeurons(listOfNeurons);
	return outputLayer;
}


inline void OutputLayer::printLayer(const OutputLayer & outputLayer)const
{
	std::cout << "### OUTPUT lAYER ###"<<std::endl;
	int n = 1;
	for (Neuron neuron : outputLayer.getListOfNeurons()) {
		std::cout << "Neuron #" << n << ":"<<std::endl;
		std::cout << "Input Weights:"<<std::endl;
		std::vector<double> weights = neuron.getListOfWeightOut();
		for (double weight : weights) {
			std::cout << weight << " ";
		}
		n++;
	}
}
