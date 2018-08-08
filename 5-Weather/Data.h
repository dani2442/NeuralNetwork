#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <stdio.h>
#include <sstream>
#include <algorithm>
#include <filesystem>

#include "enum.h"
#include "File.h"

#if __cplusplus < 201703L
    namespace fs = std::experimental::filesystem;
#else
    namespace fs = std::filesystem;
#endif

class Data
{
public:
	Data();
	Data(std::string path, std::string fileName);
	~Data();

	std::vector<std::vector<double>> joinArrays(std::vector<std::vector<std::vector<double>>> listOfArraysToJoin);
	std::vector<std::vector<double>> normalize(std::vector<std::vector<double>> rawMatrix, NormalizationTypesENUM normType);
	std::vector<std::vector<double>> denormalize(std::vector<std::vector<double>> rawMatrix, std::vector<std::vector<double>>matrixNorm, NormalizationTypesENUM normTypes);
	std::vector<std::vector<double>> rawData2Matrix(Data& r);

	// Getters and Setters

	std::string getPath() { return path; }
	void setPath(std::string path) { this->path = path; }

	std::string getFileName() { return fileName; }
	void setFileName(std::string fileName) { this->fileName = fileName; }

private:
	std::string path;
	std::string fileName;

	std::string defineAbsoluteFilePath(Data& r);
};

Data::Data()
{
}

inline Data::Data(std::string path, std::string fileName):
	path(path),
	fileName(fileName)
{
}

Data::~Data()
{
}

inline std::vector<std::vector<double>> Data::joinArrays(std::vector<std::vector<std::vector<double>>> listOfArraysToJoin)
{
	size_t rows = listOfArraysToJoin[0].size();
	size_t cols = listOfArraysToJoin.size();

	std::vector<std::vector<double>>matrix(rows, std::vector<double>(cols));
	for (size_t cols_i = 0; cols_i < cols; cols_i++) {
		for (size_t rows_i = 0; rows_i < rows; rows_i++) {
			matrix[rows_i][cols_i] = listOfArraysToJoin[cols_i][rows_i][0];
		}
	}
	return matrix;
}

inline std::vector<std::vector<double>> Data::normalize(std::vector<std::vector<double>> rawMatrix, NormalizationTypesENUM normType)
{
	size_t rows = rawMatrix.size();
	size_t cols = rawMatrix[0].size();

	std::vector<std::vector<double>> matrixNorm(rows, std::vector<double>(cols));
	for (size_t cols_i = 0; cols_i < cols; cols_i++) {
		std::vector<double> listColumn;
		for (int rows_j = 0; rows_j < rows; rows_j++)
			listColumn.push_back(rawMatrix[rows_j][cols_i]);

		std::vector<double>::iterator minColValue = std::min_element(listColumn.begin(), listColumn.end());
		std::vector<double>::iterator maxColValue = std::max_element(listColumn.begin(), listColumn.end());

		for (size_t rows_j = 0; rows_j < rows; rows_j++) {
			switch (normType) {
			case NormalizationTypesENUM::MAX_MIN :
				matrixNorm[rows_j][cols_i] = rawMatrix[rows_j][cols_i] / abs(*maxColValue);
				break;
			case NormalizationTypesENUM::MAX_MIN_EQUALIZED:
				if (cols_i > 0)
					matrixNorm[rows_j][cols_i] = (rawMatrix[rows_j][cols_i] - *minColValue) / (*maxColValue - *minColValue);
				else
					matrixNorm[rows_j][cols_i] = rawMatrix[rows_j][cols_i];
				break;
			default:
				throw std::exception("Data.h >> normalize >> default");
			}
		}
	}
	return matrixNorm;
}

inline std::vector<std::vector<double>> Data::denormalize(std::vector<std::vector<double>> rawMatrix, std::vector<std::vector<double>> matrixNorm, NormalizationTypesENUM normType)
{
	size_t rows = matrixNorm.size();
	size_t cols = matrixNorm[0].size();

	std::vector<std::vector<double>> matrixDenorm(rows, std::vector<double>(cols));
	for (size_t cols_i = 0; cols_i < cols; cols_i++) {
		std::vector<double>listColumn;
		for (size_t rows_j = 0; rows_j < rows; rows_j++)
			listColumn.push_back(rawMatrix[rows_j][cols_i]);

		std::vector<double>::iterator minColValue = std::min_element(listColumn.begin(), listColumn.end());
		std::vector<double>::iterator maxColValue = std::max_element(listColumn.begin(), listColumn.end());
		for (size_t rows_j = 0; rows_j < rows; rows_j++) {
			switch (normType) {
			case NormalizationTypesENUM::MAX_MIN:
				matrixDenorm[rows_j][cols_i] = matrixNorm[rows_j][cols_i] * abs(*maxColValue);
				break;
			case NormalizationTypesENUM::MAX_MIN_EQUALIZED:
				if (cols_i > 0)
					matrixDenorm[rows_j][cols_i] = (matrixNorm[rows_j][cols_i] * (*maxColValue - *minColValue)) + *minColValue;
				else
					matrixDenorm[rows_j][cols_i] = matrixNorm[rows_j][cols_i];
				break;
			default:
				throw std::exception("Data.h >> denormalize >> default");
			}
		}
	}
	return matrixDenorm;
}

inline std::vector<std::vector<double>> Data::rawData2Matrix(Data & r)
{
	std::string fullPath = defineAbsoluteFilePath(r);
	std::ifstream file(fullPath);
	std::string line,builder;
	getline(file, line);
	size_t columns = std::count(line.begin(), line.end(), ',') + 1;
	size_t rows = 0;
	while (getline(file,line)) {
		rows++;
	}
	file=std::ifstream(fullPath);
	std::vector<std::vector<double>>matrix(rows+1, std::vector<double>(columns));
	rows = 0;
	double num;
	while (getline(file, line)) {
		std::stringstream ss(line);
		size_t i = 0;
		while (ss>>num) {
			matrix[rows][i] = num;
			if (ss.peek() == ',')
				ss.ignore();
			i++;
		}
		rows++;
	}
	return matrix;
}

inline std::string Data::defineAbsoluteFilePath(Data & r)
{
	std::string absoluteFilePath;
#ifdef _WIN32
	fs::path workingDir = fs::canonical(r.getPath()+"\\"+r.getFileName());
#else
	fs::path workingDir = fs::canonical(r.getPath()+"/"+r.getFileName());
#endif
	File::isFile(workingDir.string());
	return workingDir.string();
}
