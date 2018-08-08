#pragma once

class LevenbergMarquardt:public Backpropagation
{
public:
	LevenbergMarquardt();
	~LevenbergMarquardt();

	NeuralNet& train(NeuralNet& n);

private:
	Matrix* jacobian;
	Matrix* error;
	const double damping = 0.1;

	void buildJacobianMatrix(NeuralNet& n, const size_t row);
	NeuralNet& updateWeights(NeuralNet& n);
};

LevenbergMarquardt::LevenbergMarquardt() : Backpropagation()
{
}

LevenbergMarquardt::~LevenbergMarquardt()
{
	delete error;
	delete jacobian;
}

inline NeuralNet & LevenbergMarquardt::train(NeuralNet & n)
{
	int epoch = 0;
	setMse(1.0);
	while (getMse() > n.getTargetError()) {
		if (epoch >= n.getMaxEpochs())break;
		size_t rows = n.getTrainSet().size();
		double sumErrors = 0.0;
		for (size_t rows_i = 0; rows_i < rows; rows_i++) {
			n = forward(n, rows_i);
			buildJacobianMatrix(n, rows_i);
			sumErrors += n.getErrorMean();
		}
		setMse(sumErrors / rows);
		n = updateWeights(n);
		std::cout << getMse() << std::endl;
		epoch++;
	}
	std::cout << "Number of epochs: " << epoch<<std::endl;
	return n;
}

inline void LevenbergMarquardt::buildJacobianMatrix(NeuralNet & n, const size_t row)
{
	NeuralNet nb = Backpropagation::backpropagation(n, row);
	std::vector<Neuron>outputLayer = n.getOutputLayer().getListOfNeurons();
	std::vector<Neuron>hiddenLayer = n.getListOfHiddenLayer()[0].getListOfNeurons();
	
	size_t numberOfInputs = n.getInputLayer().getNumberOfNeuronsInLayer();
	size_t numberOfHiddenNeurons = n.getHiddenLayer().getNumberOfNeuronsInLayer();
	size_t numberOfOutputs = n.getOutputLayer().getNumberOfNeuronsInLayer();
	if (jacobian == nullptr) 
		jacobian = new Matrix(n.getTrainSet().size(), numberOfInputs*(numberOfHiddenNeurons - 1) + numberOfHiddenNeurons*numberOfOutputs);
	int i = 0;
	for (std::vector<Neuron>::iterator it = hiddenLayer.begin(); it != hiddenLayer.end(); it++,i++) {
		std::vector<double>hiddenLayerInputWeights = it->getListOfWeightIn();
		if (hiddenLayerInputWeights.size() > 0) {
			for (size_t j = 0; j < n.getInputLayer().getNumberOfNeuronsInLayer(); j++) {
				double number = it->getSensibility()*n.getTrainSet()[row][j] / n.getErrorMean();
				jacobian->setValue(row, ((i - 1)*numberOfInputs) + j,number);
			}
		}
		else {
			// jacobian.setValue(row,i*(numberOfInputs),1.0); 
		}
		// Bias woll have no effect
	}
	if (error == NULL)
		error = new Matrix(n.getTrainSet().size(), 1);
	// Output layer
	i = 0;
	for (std::vector<Neuron>::iterator it = outputLayer.begin(); it != outputLayer.end(); it++, i++) {
		int j = 0;
		for (std::vector<Neuron>::iterator it2 = hiddenLayer.begin(); it2 != hiddenLayer.end(); it2++, j++) {
			jacobian->setValue(row,
				(numberOfInputs)*(numberOfHiddenNeurons - 1) +
				(i*(numberOfHiddenNeurons)) + j,
				(it->getSensibility() * it2->getOutputValue()) / n.getErrorMean());
		}
		// Bias will have no effect
		//jacobian.setValue(row,(numberOfInputs)*(numberOfHiddenNeurons-1)+(i*(numberOfHiddenNeurons))+numberOfHiddenNeurons,1.0); 
	}
	error->setValue(row, 0, n.getErrorMean());
}

inline NeuralNet & LevenbergMarquardt::updateWeights(NeuralNet & n)
{
	// delta = inv(J`J + damping I ) * J` error
	IdentityMatrix* Ident = new IdentityMatrix(jacobian->getNumberOfColumns());
	Matrix term1 = jacobian->transpose().multiply(*jacobian).add((*Ident).multiply(damping)); delete Ident;
	Matrix term2 = jacobian->transpose().multiply(*error);
	Matrix delta = term1.inverse().multiply(term2);
	delta.Print();
	std::vector<Neuron> outputLayer = n.getOutputLayer().getListOfNeurons();
	std::vector<Neuron> hiddenLayer = n.getListOfHiddenLayer()[0].getListOfNeurons();

	size_t numberOfInputs = n.getInputLayer().getNumberOfNeuronsInLayer();
	size_t numberOfHiddenNeurons = n.getHiddenLayer().getNumberOfNeuronsInLayer();
	size_t numberOfOutputs = n.getOutputLayer().getNumberOfNeuronsInLayer();

	size_t i = 0;
	for (std::vector<Neuron>::iterator it = hiddenLayer.begin(); it != hiddenLayer.end();it++) {
		if (it->getListOfWeightIn().size() > 0) {
			double newWeight = 0.0;
			for (size_t j = 0; j < n.getInputLayer().getNumberOfNeuronsInLayer(); j++) {
				newWeight = it->getListOfWeightIn()[i] + delta.getValue(i*numberOfInputs + j, 0);
				it->getListOfWeightIn()[i] = newWeight;
			}
			i++;
		}
	}
	n.getListOfHiddenLayer()[0].setListOfNeurons(hiddenLayer);///////////////////

	for (i = 0; i < outputLayer.size(); i++) {
		double newWeight = 0.0;
		for (size_t j = 0; j < hiddenLayer.size(); j++) {
			newWeight = hiddenLayer[j].getListOfWeightOut()[i] + delta.getValue((numberOfInputs*(numberOfHiddenNeurons - 1)) + (i*numberOfHiddenNeurons) + j, 0);
			hiddenLayer[j].getListOfWeightOut()[i] = newWeight;
		}
	}
	n.getListOfHiddenLayer()[0].setListOfNeurons(hiddenLayer);
	return n;
}
