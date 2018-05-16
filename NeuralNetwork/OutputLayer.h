#pragma once

#ifndef __OutputLayer__
#define __OutputLayer__
#endif 

#ifndef __Layer__
#include "Layer.h"
#endif

class OutputLayer : public Layer
{
public:
	OutputLayer();
	~OutputLayer();

	OutputLayer& initLayer(OutputLayer &ouputLayer);
	void porintLayer(const OutputLayer& outputLayer);
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

inline void OutputLayer::porintLayer(const OutputLayer & outputLayer)
{
	std::cout << "### OUTPUT lAYER ###";
	int n = 1;
	for (Neuron neuron : outputLayer.getListOfNeurons()) {
		std::cout << "Neuron #" << n << ":";
		std::cout << "Input Weights:";
		std::vector<double> weights = neuron.getListOfWeightIn();
		for (double weight : weights) {
			std::cout << weight << " ";
		}
		n++;
}
