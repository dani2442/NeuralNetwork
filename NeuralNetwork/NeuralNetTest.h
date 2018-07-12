#pragma once

class NeuralNetTest
{
public:
	NeuralNetTest();
	~NeuralNetTest();

	void testPerceptron();
	void testAdaline();
	void testLMA();
	void testBackpropagation();

private:

};

NeuralNetTest::NeuralNetTest()
{
}

NeuralNetTest::~NeuralNetTest()
{
}

inline void NeuralNetTest::testPerceptron()
{
	NeuralNet testNet;
	testNet = testNet.initNet(2, 0, 0, 1);

	std::cout << "---------PERCEPTRON INIT NET------------" << std::endl;
	testNet.printNet(testNet);

	NeuralNet trainedNet;

	std::vector<std::vector<double>>v = { { 1.0, 0.0, 0.0 },{ 1.0, 0.0, 1.0 },{ 1.0, 1.0, 0.0 },{ 1.0, 1.0, 1.0 } };
	testNet.setTrainSet(v);
	std::vector<double>t = { 0.0, 0.0, 0.0, 1.0 };
	testNet.setRealOutputSet(t);
	testNet.setMaxEpochs(10);
	testNet.setTargetError(0.002);
	testNet.setLearningRate(1.0);
	testNet.setTrainType(TrainingTypesENUM::PERCEPTRON);
	testNet.setActivationFnc(ActivationFncENUM::STEP);

	trainedNet = testNet.trainNet(testNet);

	std::cout << std::endl;
	std::cout << "-----------PERVEPTRON TRAINED NET--------------" << std::endl;
	testNet.printNet(trainedNet);

	std::cout << std::endl;
	std::cout << "------------PERCEPTRON PRINT RESULT--------------" << std::endl;
	testNet.printTrainedNetResult(trainedNet);
}

inline void NeuralNetTest::testAdaline()
{
	NeuralNet testNet;
	testNet = testNet.initNet(3, 0, 0, 1);
	std::cout << "-----------ADALINE INIT NET----------------" << std::endl;

	testNet.printNet(testNet);
	NeuralNet trainedNet;

	testNet.setTrainSet(std::vector<std::vector<double>>() = { { 1.0, 0.98, 0.94, 0.95 },
		{ 1.0, 0.60, 0.60, 0.85 },{ 1.0, 0.35, 0.15, 0.15 },
		{ 1.0, 0.25, 0.30, 0.98 },{ 1.0, 0.75, 0.85, 0.91 },
		{ 1.0, 0.43, 0.57, 0.87 },{ 1.0, 0.05, 0.06, 0.01 } });
	testNet.setRealOutputSet(std::vector<double>() = { 0.80, 0.59, 0.23, 0.45, 0.74,0.63, 0.10 });
	testNet.setMaxEpochs(10);
	testNet.setTargetError(0.0001);
	testNet.setLearningRate(0.5);
	testNet.setTrainType(TrainingTypesENUM::ADALINE);
	testNet.setActivationFnc(ActivationFncENUM::LINEAR);

	trainedNet = testNet.trainNet(testNet);

	std::cout << std::endl;
	std::cout << "-----------ADALINE TRAINED NET--------------" << std::endl;
	testNet.printNet(trainedNet);

	std::cout << std::endl;
	std::cout << "------------ADALINE PRINT RESULT--------------" << std::endl;

	testNet.printTrainedNetResult(trainedNet);

	std::cout << std::endl;
	std::cout << "--------------ADALINE MSE BY EPOCH-------------" << std::endl;
	std::vector<double> n = trainedNet.getListOfMSE();
	for (size_t i = 0; i < n.size(); i++) {
		std::cout << n[i] << std::endl;
	}
}

inline void NeuralNetTest::testLMA()
{
	NeuralNet testNet;
	testNet=testNet.initNet(2, 1, 3, 2);
	std::cout << "-------------LEVENBERH-MARQUARDT NET-------------" << std::endl;
	testNet.printNet(testNet);
	NeuralNet trainedNet;
	// Forst column has BIAS
	testNet.setTrainSet(std::vector<std::vector<double>>() = {
		{ 1.0, 1.0, 0.73 }, { 1.0, 1.0, 0.81 }, { 1.0, 1.0, 0.86 },
		{ 1.0, 1.0, 0.95 }, { 1.0, 0.0, 0.45 }, { 1.0, 1.0, 0.70 },
		{ 1.0, 0.0, 0.51 }, { 1.0, 1.0, 0.89 }, { 1.0, 1.0, 0.79 }, { 1.0, 0.0, 0.54 } 
		});
	testNet.setRealMatrixOutputSet(std::vector<std::vector<double>>() = { 
		{ 1.0, 0.0 },{ 1.0, 0.0 },{ 1.0, 0.0 },
		{ 1.0, 0.0 },{ 1.0, 0.0 },{ 0.0, 1.0 },
		{ 0.0, 1.0 },{ 0.0, 1.0 },{ 0.0, 1.0 },{ 0.0, 1.0 } 
		});
	testNet.setMaxEpochs(1000);
	testNet.setTargetError(0.002);
	testNet.setLearningRate(0.1);
	testNet.setTrainType(TrainingTypesENUM::LEVENBERG_MARQUARDT);
	testNet.setActivationFnc(ActivationFncENUM::SIGLOG);
	testNet.setActivationFncOutputLayer(ActivationFncENUM::LINEAR);

	trainedNet = testNet.trainNet(testNet);
	std::cout << std::endl;
	std::cout << "------------BACKPROPAGATION TRAINED NET---------------" << std::endl;
	testNet.printNet(trainedNet);
}

inline void NeuralNetTest::testBackpropagation()
{
	NeuralNet testNet;
	testNet.initNet(2, 1, 3, 2);
	std::cout << "-------------BACKPROPAGATION INET NET----------------" << std::endl;
	testNet.printNet(testNet);
	NeuralNet trainedNet;
	testNet.setTrainSet(std::vector<std::vector<double>>() = {
		{ 1.0, 1.0, 0.73 },{ 1.0, 1.0, 0.81 },{ 1.0, 1.0, 0.86 },
		{ 1.0, 1.0, 0.95 },{ 1.0, 0.0, 0.45 },{ 1.0, 1.0, 0.70 },
		{ 1.0, 0.0, 0.51 },{ 1.0, 1.0, 0.89 },{ 1.0, 1.0, 0.79 },{ 1.0, 0.0, 0.54 } 
		});
	testNet.setRealMatrixOutputSet(std::vector<std::vector<double>>()= { 
		{ 1.0, 0.0 },{ 1.0, 0.0 },{ 1.0, 0.0 },
		{ 1.0, 0.0 },{ 1.0, 0.0 },{ 0.0, 1.0 },
		{ 0.0, 1.0 },{ 0.0, 1.0 },{ 0.0, 1.0 },{ 0.0, 1.0 }
		});
	testNet.setMaxEpochs(1000);
	testNet.setTargetError(0.002);
	testNet.setLearningRate(0.1);
	testNet.setTrainType(TrainingTypesENUM::BACKPROPAGATION);
	testNet.setActivationFnc(ActivationFncENUM::SIGLOG);
	testNet.setActivationFncOutputLayer(ActivationFncENUM::LINEAR);

	trainedNet = testNet.trainNet(testNet);
	std::cout << std::endl;
	std::cout << "-------------BACKPROPAGATION TRAINED NET----------------" << std::endl;
	testNet.printNet(trainedNet);
}

