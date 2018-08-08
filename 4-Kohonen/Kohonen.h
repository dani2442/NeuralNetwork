#pragma once
#include <algorithm>


class Kohonen: public Training,public Validation
{
public:
	Kohonen();
	~Kohonen();
	
	NeuralNet& train(NeuralNet& n);
	void netValidation(NeuralNet& n);

private:
	NeuralNet & initNet(NeuralNet& n);
	std::vector<double> calcEuclideanDistance(NeuralNet& n, std::vector<std::vector<double>>& data, size_t row);
	NeuralNet& fixWinnerWeights(NeuralNet& n, size_t winnerNeuron, size_t trainSetRow);

};

Kohonen::Kohonen():Training(),Validation()
{
}

Kohonen::~Kohonen()
{
}

inline NeuralNet & Kohonen::train(NeuralNet & n)
{
	size_t rows = n.getTrainSet().size();
	n = this->initNet(n);
	std::vector<double>  listOfDistances;
	std::vector<std::vector<double>>trainData = n.getTrainSet();
	for (size_t epoch = 0; epoch < n.getMaxEpochs(); epoch++) {
		for (size_t row_i = 0; row_i < rows; row_i++) {
			listOfDistances = calcEuclideanDistance(n, trainData, row_i);
			size_t winnerNeuron = std::distance(listOfDistances.begin(), std::min_element(listOfDistances.begin(), listOfDistances.end()));
			n = fixWinnerWeights(n, winnerNeuron, row_i);
		}
	}
	return n;
}

inline void Kohonen::netValidation(NeuralNet & n)
{
	size_t rows = n.getValidationSet().size();
	std::vector<double>listOfDistances;
	std::vector<std::vector<double>>validationData = n.getValidationSet();
	for (size_t row_i = 0; row_i < rows; row_i++)
	{
		listOfDistances = calcEuclideanDistance(n,validationData,row_i);
		size_t winnerNeuron = std::distance(listOfDistances.begin(), std::min_element(listOfDistances.begin(), listOfDistances.end()));
		std::cout << "### VALIDATION RESULT ###" << std::endl;
		switch (winnerNeuron) {
		case 0:
		{
			std::cout << "Cluster 1" << std::endl;
			break;
		}
		case 1:
		{
			std::cout << "Cluster 2" << std::endl;
			break;
		}
		default:
			std::cout << "Error! without neural clustering...";
		}
	}
}

inline NeuralNet & Kohonen::initNet(NeuralNet & n)
{
	std::vector<double> listOfWeightOut;
	size_t size = n.getInputLayer().getNumberOfNeuronsInLayer()*n.getOutputLayer().getNumberOfNeuronsInLayer();
	for (size_t i = 0;i<size; i++)
		listOfWeightOut.push_back(0.0);
	n.getInputLayer().getListOfNeurons()[0].setListOfWeightOut(listOfWeightOut);
	return n;
}

inline std::vector<double> Kohonen::calcEuclideanDistance(NeuralNet & n, std::vector<std::vector<double>>& data, size_t row)
{
	std::vector<double>listOfDistances;
	size_t weight_i = 0;
	for (size_t cluster_i = 0; cluster_i < n.getOutputLayer().getNumberOfNeuronsInLayer(); cluster_i++) {
		double distance = 0;
		for (size_t input_j = 0; input_j < n.getInputLayer().getNumberOfNeuronsInLayer();input_j++) {
			double wieght = n.getInputLayer().getListOfNeurons()[0].getListOfWeightOut()[weight_i];
			distance += pow(data[row][input_j] - wieght, 2.0);
			weight_i++;
		}
		listOfDistances.push_back(distance);
	}
	return listOfDistances;
}

inline NeuralNet & Kohonen::fixWinnerWeights(NeuralNet & n, size_t winnerNeuron, size_t trainSetRow)
{
	size_t start, last;
	start = winnerNeuron * n.getInputLayer().getNumberOfNeuronsInLayer();
	last = start + n.getInputLayer().getNumberOfNeuronsInLayer();
	std::vector<double> listOfOldWeights(n.getInputLayer().getListOfNeurons()[0].getListOfWeightOut().begin()+start, n.getInputLayer().getListOfNeurons()[0].getListOfWeightOut().begin()+last);
	std::vector<double>listOfWeights = n.getInputLayer().getListOfNeurons()[0].getListOfWeightOut();

	size_t col_i = 0;
	for (size_t j = start; j < last; j++) {
		double trainSetValue = n.getTrainSet()[trainSetRow][col_i];
		double newWeight = listOfOldWeights[col_i] + n.getLearningRate()*(trainSetValue - listOfOldWeights[col_i]);
		
		listOfWeights[j] = newWeight;
		col_i++;
	}
	n.getInputLayer().getListOfNeurons()[0].setListOfWeightOut(listOfWeights);
	return n;
}


