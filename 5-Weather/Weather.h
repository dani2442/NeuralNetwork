#pragma once
#include "Data.h"
#include "enum.h"
#include "NeuralNet.h"
#include "Chart.h"

class Weather
{
public:
	Weather();
	~Weather();

private:

};

Weather::Weather()
{
	Data weatherDataInput("data", "inmet_13_14_input.csv");
	Data weatherDataOutput("data", "inmet_13_14_output.csv");
		
	Data weatherDataInputTestRNA("data", "inmet_13_14_input_test.csv");
	Data weatherDataOutputTestRNA("data", "inmet_13_14_output_test.csv");
		
	NormalizationTypesENUM NORMALIZATION_TYPE = NormalizationTypesENUM::MAX_MIN_EQUALIZED;

	std::vector<std::vector<double>> matrixInput = weatherDataInput.rawData2Matrix(weatherDataInput);
	std::vector<std::vector<double>> matrixOutput = weatherDataOutput.rawData2Matrix(weatherDataOutput);

	std::vector<std::vector<double>> matrixInputTestRNA = weatherDataOutput.rawData2Matrix(weatherDataInputTestRNA);
	std::vector<std::vector<double>> matrixOutputTestRNA = weatherDataOutput.rawData2Matrix(weatherDataOutputTestRNA);

	std::vector<std::vector<double>> matrixInputNorm = weatherDataInput.normalize(matrixInput, NORMALIZATION_TYPE);
	std::vector<std::vector<double>> matrixOutputNorm = weatherDataOutput.normalize(matrixOutput, NORMALIZATION_TYPE);

	std::vector<std::vector<double>> matrixInputTestRNANorm = weatherDataOutput.normalize(matrixInputTestRNA, NORMALIZATION_TYPE);
	std::vector<std::vector<double>> matrixOutputTestRNANorm = weatherDataOutput.normalize(matrixOutputTestRNA, NORMALIZATION_TYPE);

	NeuralNet n1;
	n1 = n1.initNet(4, 1, 4, 1);

	n1.setTrainSet(matrixInputNorm);
	n1.setRealMatrixOutputSet(matrixOutputNorm);

	n1.setMaxEpochs(1000);
	n1.setTargetError(0.00001);
	n1.setLearningRate(0.25);
	n1.setTrainType(TrainingTypesENUM::BACKPROPAGATION);
	n1.setActivationFnc(ActivationFncENUM::SIGLOG);
	n1.setActivationFncOutputLayer(ActivationFncENUM::LINEAR);

	NeuralNet n1Trained;
	n1Trained = n1.trainNet(n1);
	std::cout << std::endl;

	// ERROR:
	//Chart c1;
	//c1.plotXYData(n1.getListOfMSE().toArray(),"MSE Error","Epochs","MSE Value");
	Chart::plotXData(n1.getListOfMSE(), "MSE Error", "MSEValue", "Epochs");

	// TRAINING:
	std::vector<std::vector<double>> matrixOuputRNA = n1Trained.getNetOutputValues(n1Trained);
	Data* temp = new Data();
	std::vector<std::vector<double>> matrixOutputRNADenorm = temp->denormalize(matrixOutput, matrixOuputRNA, NORMALIZATION_TYPE);

	std::vector<std::vector<std::vector<double>>> listOfArraysToJoin;
	listOfArraysToJoin.push_back(matrixOutput);
	listOfArraysToJoin.push_back(matrixOutputRNADenorm);

	std::vector<std::vector<double>> matrixOuputsJoined = temp->joinArrays(listOfArraysToJoin);

	//Chart c2;
	//c2.plotXYData(matrixOuputsJoined,"Real x Estimated - Trainig Data","Temperature (Celsius)",ChartPlotTypeENUM::COMPARISON);
	Chart::plotXYData(matrixOuputsJoined, "Real x Estimated - Trainig Data","Weather Data", "Temperature (Celsius)");

	//TEST:
	n1Trained.setTrainSet(matrixInputTestRNANorm);
	n1Trained.setRealMatrixOutputSet(matrixOutputTestRNANorm);

	std::vector<std::vector<double>> matrixOutputRNATest = n1Trained.getNetOutputValues(n1Trained);
	std::vector<std::vector<double>> matrixOutputRNADenormTest = temp->denormalize(matrixOutputTestRNA, matrixOutputRNATest, NORMALIZATION_TYPE);	

	std::vector<std::vector<std::vector<double>>> listOfArraysToJoinTest;
	listOfArraysToJoinTest.push_back(matrixOutputTestRNA);
	
	listOfArraysToJoinTest.push_back(matrixOutputRNADenormTest);
	
	std::vector<std::vector<double>> matrixOuputsJoinedTest = temp->joinArrays(listOfArraysToJoinTest);
	delete temp;
	//Chart c3;
	//c3.plotXYData(matrixOuputsJoinedTest, "Real x Eestimated - Test Data", "Wather Data", "Temperature (Celsius)", ChartPlotTypeENUM::COMPARISON);
	Chart::plotXYData(matrixOuputsJoinedTest, "Real x Estimated - Test Data","Weather Data","Temperature (Celsius)");
}

Weather::~Weather()
{
}