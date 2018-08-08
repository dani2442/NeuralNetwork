#pragma once

class NeuralNet;
#include <iterator>
#include <list>
#include "InputLayer.h"
#include "OutputLayer.h"
#include "HiddenLayer.h"
#include "enum.h"
#include "Matrix.h"
#include "IdentityMatrix.h"
#include "Validation.h"

class NeuralNet
{
public:
	NeuralNet();
	~NeuralNet();

	NeuralNet initNet(int numberOfInputNeurons,int numberOfHiddenLayers,int numberOfNeuronsInHiddenLayer,int numberOfOutputNeurons);
	NeuralNet trainNet(NeuralNet& n);
	void netValidation(NeuralNet& n);

	void printNet( NeuralNet& n) ;
	void printTrainedNetResult( NeuralNet& n) ;
	
private:
	InputLayer inputLayer;
	HiddenLayer hiddenLayer;
	std::vector<HiddenLayer> listOfHiddenLayer;
	OutputLayer outputLayer;
	int numberOfHiddenLayers;

	std::vector<std::vector<double>> trainSet;
	std::vector<std::vector<double>> validationSet;
	std::vector<double> realOutputSet;
	std::vector<std::vector<double>> realMatrixOutputSet;

	int maxEpochs;
	double learningRate;
	double targetError;
	double trainingError;
	double errorMean;

	std::vector<double>listOfMSE;
	ActivationFncENUM activationFnc;
	ActivationFncENUM activationFncOutputLayer;
	TrainingTypesENUM trainType;


public:
	InputLayer & getInputLayer() { return inputLayer; }
	void setInputLayer(const InputLayer& inputLayer) { this->inputLayer = inputLayer; }

	 HiddenLayer& getHiddenLayer()  { return hiddenLayer; }
	void setHiddenLayer(const HiddenLayer& hiddenLayer) { this->hiddenLayer = hiddenLayer; }

	 std::vector<HiddenLayer>& getListOfHiddenLayer()  { return listOfHiddenLayer; }
	void setListOfHiddenLayer(const std::vector<HiddenLayer>& listOfHiddenLayer) { this->listOfHiddenLayer = listOfHiddenLayer; }

	 OutputLayer& getOutputLayer()  { return outputLayer; }
	void setOutputLayer(const OutputLayer& ouputLayer) { this->outputLayer = ouputLayer; }

	 int getNumberOfHiddenLayers() { return numberOfHiddenLayers; }
	void setNumberOfHiddenLayers(const int numberOfHiddenLayers) { this->numberOfHiddenLayers= numberOfHiddenLayers; }

	 std::vector<std::vector<double>>& getTrainSet()  { return trainSet; }
	void setTrainSet(const std::vector<std::vector<double>>& trainSet) { this->trainSet = trainSet; }

	std::vector<std::vector<double>>& getValidationSet() { return validationSet; }
	void setValidationSet(const std::vector<std::vector<double>> validationSet) { this->validationSet = validationSet; }

	 std::vector<double> getRealOutputSet()  { return realOutputSet; }
	void setRealOutputSet(const std::vector<double>& realOutputSet) { this->realOutputSet = realOutputSet; }

	 std::vector<std::vector<double>>& getRealMatrixOutputSet() { return realMatrixOutputSet; }
	void setRealMatrixOutputSet(const std::vector<std::vector<double>>& realMatrixOutputSet) { this->realMatrixOutputSet = realMatrixOutputSet; }

	 int getMaxEpochs() { return maxEpochs; }
	void setMaxEpochs(const int maxEpochs) { this->maxEpochs = maxEpochs; }

	 double getTargetError()  { return targetError; }
	void setTargetError(const double targetError) { this->targetError = targetError; }

	 double getLearningRate()  { return learningRate; }
	void setLearningRate(const double learningRate) { this->learningRate = learningRate; }

	 double getTrainingError()  { return trainingError; }
	void setTrainingError(const double trainingError) { this->trainingError = trainingError; }

	 double getErrorMean() { return errorMean; }
	void setErrorMean(const double errorMean) { this->errorMean = errorMean; }

	 ActivationFncENUM getActivationFnc()  { return activationFnc; }
	void setActivationFnc(ActivationFncENUM activationFnc) { this->activationFnc = activationFnc; }

	 ActivationFncENUM getActivationFncOutputLayer() { return activationFncOutputLayer; }
	void setActivationFncOutputLayer(const ActivationFncENUM activationFncOutputLayer) { this->activationFncOutputLayer = activationFncOutputLayer; }

	 TrainingTypesENUM getTrainType()  { return trainType; }
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
	
inline void NeuralNet::printNet( NeuralNet& n) {
	inputLayer.printLayer(n.getInputLayer());
	std::cout<<std::endl;
	hiddenLayer.printLayer(listOfHiddenLayer);
	std::cout<<std::endl;
	outputLayer.printLayer(outputLayer);
}
#include "Training.h"
#include "Perceptron.h"
#include "Adaline.h"
#include "Backpropagation.h"
#include "Kohonen.h"
#include "LevenbergMartquardt.h"

inline void NeuralNet::printTrainedNetResult (NeuralNet & n)
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
	case TrainingTypesENUM::BACKPROPAGATION:
	{
		Backpropagation b;
		b.printTrainedNetResult(n);
		break;
	}
	}
}

NeuralNet NeuralNet::trainNet(NeuralNet & n)
{
	NeuralNet trainedNet;
	switch (n.trainType) {
	case TrainingTypesENUM::PERCEPTRON:
	{
		Perceptron t;
		trainedNet = t.train(n);
		return trainedNet;
	}
	case TrainingTypesENUM::ADALINE:
	{
		Adaline a;
		trainedNet = a.train(n);
		return trainedNet;
	}
	case TrainingTypesENUM::BACKPROPAGATION:
	{
		Backpropagation b;
		trainedNet = b.train(n);
		return trainedNet;
	}
	case TrainingTypesENUM::LEVENBERG_MARQUARDT:
	{
		LevenbergMarquardt mq;
		trainedNet = mq.train(n);
		return trainedNet;
	}
	case TrainingTypesENUM::KOHONEN:
	{
		Kohonen k;
		trainedNet = k.train(n);
		return trainedNet;
	}
	default:
	{
		std::cout << "Error return---NeuralNet::trainNet()" << std::endl;
		return n;
	}
	}
}

inline void NeuralNet::netValidation(NeuralNet & n)
{
	switch (n.trainType) {
	case TrainingTypesENUM::KOHONEN:
	{
		Kohonen k;
		k.netValidation(n);
		break;
	}
	default:
	{
		std::cout << n.trainType << " does not exist in TrainingTypesENUM" << std::endl;
		break;
	}
	}
}

