#include "NeuralNet.h"
#include "NeuralNetTest.h"

int main() {
	NeuralNetTest test;
	//test.testPerceptron();
	//test.testAdaline();
	//test.testLMA();
	//test.testBackpropagation();

	test.testKohonen();
	getchar();
}