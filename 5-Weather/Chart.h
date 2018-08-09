#pragma once
#include <vector>
#include "infix_iterator.h"

class Chart
{
public:
	Chart();
	~Chart();

	template<class T>
	static void plotXYData(std::vector<std::vector<T>> data,std::string name,std::string X,std::string Y);

	template<typename T>
	static void plotXData(std::vector<T>data,std::string name,std::string X,std::string Y);
private:

};

Chart::Chart()
{
}

Chart::~Chart()
{
}

template<class T>
inline void Chart::plotXYData(std::vector<std::vector<T>> data,std::string name,std::string X,std::string Y)
{
	std::ofstream output_file("results/" + name + ".csv");
	output_file << (X + "," + Y+'\n');
	infix_ostream_iterator<T> output_iterator(output_file, ",");
	for (std::vector<T>&e : data) {
		std::copy(e.begin(), e.end(), output_iterator);
		output_file << std::endl;
	}
	output_file.close();
}

template<class T>
inline void Chart::plotXData(std::vector<T> data,std::string name,std::string X,std::string Y)
{
	std::ofstream output_file("results/" + name + ".csv");
	output_file << (X + '\n');
	std::ostream_iterator<T> output_iterator(output_file, "\n");
	std::copy(data.begin(), data.end(), output_iterator);
	output_file.close();
}
