#pragma once

class NeuralNet;
#include "InputLayer.h"
#include "OutputLayer.h"
#include "HiddenLayer.h"
#include "enum.h"


class NeuralNet
{
public:
	NeuralNet();
	~NeuralNet();

	NeuralNet initNet(int numberOfInputNeurons,int numberOfHiddenLayers,int numberOfNeuronsInHiddenLayer,int numberOfOutputNeurons);
	NeuralNet& trainNet(NeuralNet& n);

	void printNet(const NeuralNet& n) const;
	void printTrainedNetResult(const NeuralNet& n) const;
	
private:
	InputLayer inputLayer;
	HiddenLayer hiddenLayer;
	std::vector<HiddenLayer> listOfHiddenLayer;
	OutputLayer outputLayer;
	int numberOfHiddenLayers;

	std::vector<std::vector<double>> trainSet;
	std::vector<double> realOutputSet;
	int maxEpochs;
	double learningRate;
	double targetError;
	double trainingError;
	std::vector<double>listOfMSE;
	ActivationFncENUM activationFnc;
	TrainingTypesENUM trainType;

public:
	const InputLayer & getInputLayer()const { return inputLayer; }
	void setInputLayer(const InputLayer& inputLayer) { this->inputLayer = inputLayer; }

	const HiddenLayer& getHiddenLayer() const { return hiddenLayer; }
	void setHiddenLayer(const HiddenLayer& hiddenLayer) { this->hiddenLayer = hiddenLayer; }

	const std::vector<HiddenLayer>& getListOfHiddenLayer() const { return listOfHiddenLayer; }
	void setListOfHiddenLayer(const std::vector<HiddenLayer>& listOfHiddenLayer) { this->listOfHiddenLayer = listOfHiddenLayer; }

	const OutputLayer& getOutputLayer() const { return outputLayer; }
	void setOutputLayer(const OutputLayer& ouputLayer) { this->outputLayer = ouputLayer; }

	const int getNumberOfHiddenLayers()const { return numberOfHiddenLayers; }
	void setNumberOfHiddenLayers(const int numberOfHiddenLayers) { this->numberOfHiddenLayers= numberOfHiddenLayers; }

	const std::vector<std::vector<double>>& getTrainSet() const { return trainSet; }
	void setTrainSet(std::vector<std::vector<double>>& trainSet) { this->trainSet = trainSet; }

	const std::vector<double> getRealOutputSet() const { return realOutputSet; }
	void setRealOutputSet(std::vector<double>& realOutputSet) { this->realOutputSet = realOutputSet; }

	const int getMaxEpochs()const { return maxEpochs; }
	void setMaxEpochs(const int maxEpochs) { this->maxEpochs = maxEpochs; }

	const double getTargetError() const { return targetError; }
	void setTargetError(double targetError) { this->targetError = targetError; }

	const double getLearningRate() const { return learningRate; }
	void setLearningRate(double learningRate) { this->learningRate = learningRate; }

	const double getTrainingError() const { return trainingError; }
	void setTrainingError(double trainingError) { this->trainingError = trainingError; }

	const ActivationFncENUM getActivationFnc() const { return activationFnc; }
	void setActivationFnc(ActivationFncENUM activationFnc) { this->activationFnc = activationFnc; }

	const TrainingTypesENUM getTrainType() const { return trainType; }
	void setTrainType(const TrainingTypesENUM trainType) { this->trainType = trainType; }

	std::vector<double>& getListOfMSE()  { return listOfMSE; }
	void setListOfMSE(const std::vector<double>& listOfMSE) { this->listOfMSE = listOfMSE; }
};

NeuralNet::NeuralNet()
{
}

NeuralNet::~NeuralNet()
{
}


NeuralNet NeuralNet::initNet(
	int numberOfInputNeurons, 
	int numberOfHiddenLayers,
	int numberOfNeuronsInHiddenLayer, 
	int numberOfOutputNeurons)
{
	
	inputLayer.setNumberOfNeuronsInLayer(numberOfInputNeurons);
	for (int i = 0; i < numberOfHiddenLayers; i++) {
		hiddenLayer.setNumberOfNeuronsInLayer(numberOfNeuronsInHiddenLayer);
		listOfHiddenLayer.push_back(hiddenLayer);
	}

	outputLayer.setNumberOfNeuronsInLayer(numberOfOutputNeurons);
	inputLayer = inputLayer.initLayer(inputLayer);

	if (numberOfHiddenLayers > 0) {
		listOfHiddenLayer = hiddenLayer.initLayer(hiddenLayer, listOfHiddenLayer,inputLayer,outputLayer);
	}
	outputLayer = outputLayer.initLayer(outputLayer);

	NeuralNet newNet;
	newNet.setInputLayer(inputLayer);
	newNet.setHiddenLayer(hiddenLayer);
	newNet.setListOfHiddenLayer(listOfHiddenLayer);
	newNet.setNumberOfHiddenLayers(numberOfHiddenLayers);
	newNet.setOutputLayer(outputLayer);

	return newNet;
}
	


inline void NeuralNet::printNet(const NeuralNet& n) const
{
	inputLayer.printLayer(n.getInputLayer());
	std::cout<<std::endl;
	hiddenLayer.printLayer(listOfHiddenLayer);
	std::cout<<std::endl;
	outputLayer.printLayer(outputLayer);
}
#include "Training.h"
#include "Perceptron.h"
#include "Adaline.h"
inline void NeuralNet::printTrainedNetResult (const NeuralNet & n)const
{
	switch (n.trainType) {
	case TrainingTypesENUM::PERCEPTRON:
	{
		Perceptron t;
		t.printTrainedNetResult(n);
		break;
	}
	case TrainingTypesENUM::ADALINE:
	{
		Adaline a;
		a.printTrainedNetResult(n);
		break;
	}
	}
}

NeuralNet& NeuralNet::trainNet(NeuralNet & n)
{
	switch (n.trainType) {
	case TrainingTypesENUM::PERCEPTRON:
	{
		Perceptron t;
		n = t.train(n);
		return n;
	}
	case TrainingTypesENUM::ADALINE:
	{
		Adaline a;
		n = a.train(n);
		return n;
	}
	default:
	{
		std::cout << "Error return---NeuralNet::trainNet()" << std::endl;
		return n;
	}
	}
}

