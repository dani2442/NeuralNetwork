#pragma once

#ifndef __HiddenLayer__
#define __HiddenLayer__
#endif 

#ifndef __Layer__
#include "Layer.h"
#endif

#include "InputLayer.h"
#include "OutputLayer.h"

class HiddenLayer : public Layer
{
public:
	HiddenLayer();
	~HiddenLayer();

	std::vector<HiddenLayer>& initLayer(const HiddenLayer&, std::vector<HiddenLayer>& ,const InputLayer& ,const OutputLayer& );
	void printLayer(const std::vector<HiddenLayer>&)const;

private:

};

HiddenLayer::HiddenLayer() : Layer()
{
}

HiddenLayer::~HiddenLayer()
{
}

inline std::vector<HiddenLayer>& HiddenLayer::initLayer(
	const HiddenLayer &					hiddenLayer, 
	std::vector<HiddenLayer>&			listOfHiddenLayer,
	const InputLayer &					inputLayer,
	const OutputLayer &					outputLayer)
{
	std::vector<double> listOfWeightIn;
	std::vector<double> listOfWeightOut;
	std::vector<Neuron> listOfNeurons;

	size_t numberOfHiddenLayers = listOfHiddenLayer.size();

	for (int i = 0; i < numberOfHiddenLayers; i++) {
		for (int j = 0; j < hiddenLayer.getNumberOfNeuronsInLayer(); j++) {
			Neuron neuron;

			int limitIn;
			int limitOut;

			if (i == 0) {
				limitIn = inputLayer.getNumberOfNeuronsInLayer();
				if (numberOfHiddenLayers > 1) {
					limitOut = listOfHiddenLayer[i + 1].getNumberOfNeuronsInLayer();
				}
				else {
					limitOut = listOfHiddenLayer[i].getNumberOfNeuronsInLayer();
				}
			}
			else if (i == numberOfHiddenLayers - 1) {
				limitIn = listOfHiddenLayer[i - 1].getNumberOfNeuronsInLayer();
				limitOut = outputLayer.getNumberOfNeuronsInLayer();
			}
			else {
				limitIn = listOfHiddenLayer[i - 1].getNumberOfNeuronsInLayer();
				limitOut = listOfHiddenLayer[i - 1].getNumberOfNeuronsInLayer();
			}
			for (int k = 0; k < limitIn; k++) {
				listOfWeightIn.push_back(neuron.initNeuron());
			}
			for (int k = 0; k < limitOut; k++) {
				listOfWeightOut.push_back(neuron.initNeuron());
			}

			neuron.setListOfWeightIn(listOfWeightIn);
			neuron.setListOfWeightOut(listOfWeightOut);
			listOfNeurons.push_back(neuron);

			listOfWeightIn.clear();
			listOfWeightOut.clear();
		}
		listOfHiddenLayer[i].setListOfNeurons(listOfNeurons);
		listOfNeurons.clear();
	}
	return listOfHiddenLayer;
}

inline void HiddenLayer::printLayer(const std::vector<HiddenLayer>& listOfHiddenLayer) const
{
	std::cout << "### HIDDEN lAYER ###"<<std::endl;
	int h = 1;
	for (HiddenLayer hiddenLayer : listOfHiddenLayer) {
		std::cout << "Hidden Layer #" << h<<std::endl;
		int n = 1;
		for (Neuron neuron:hiddenLayer.getListOfNeurons()) {
			std::cout << "Neuron #"<<n<<std::endl;
			std::cout << "Input Weights:"<<std::endl;
			std::vector<double> weights = neuron.getListOfWeightIn();
			for (double weight : weights) {
				std::cout << weight << " ";
			}
			std::cout <<std::endl<< "Output weights:"<<std::endl;
			weights = neuron.getListOfWeightOut();
			for (double weight : weights) {
				std::cout << weight << " ";
			}
			std::cout << std::endl;
			n++;
		}
		h++;
	}
}


