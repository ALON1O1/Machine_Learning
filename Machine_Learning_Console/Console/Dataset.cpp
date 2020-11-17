#include "Dataset.h"
#include <iostream>

Dataset::Dataset() {
	inputs = std::vector<std::vector<float>>();
	results = std::vector<std::vector<float>>();
	length = 0;
}
Dataset::~Dataset() {}
int Dataset::getLength() {
			return length;
		}
void Dataset::addData(std::vector<float> inputs, std::vector<float> results) {
			this->inputs.push_back(inputs);
			this->results.push_back(results);
			length++;
		}
std::vector<float> Dataset::getInputs(int index) {
	return inputs[index];
}
std::vector<float> Dataset::getResults(int index) {
	return results[index];
}
void Dataset::getData(int index, std::vector<float>& return_inputs, std::vector<float>& return_results) {
			return_inputs = inputs[index];
			return_results = results[index];
		}
void Dataset::getAllData(std::vector<std::vector<float>>& return_inputs, std::vector<std::vector<float>>& return_results) {
			return_inputs = inputs;
			return_results = results;
		}
void Dataset::getSaveString(std::vector<std::string>& saveString) {
			for (unsigned int i = 0; i < inputs.size() ; i++) {
				std::string s = std::to_string(inputs[i].size());
				for (unsigned int j = 0; j < inputs[i].size(); j++) {
					s += "," + std::to_string(inputs[i][j]);
				}
				s += "," + std::to_string(results[i].size());
				for (unsigned int j = 0; j < results[i].size(); j++) {
					s += "," + std::to_string(results[i][j]);
				}
				saveString.push_back(s);
			}
		}
void Dataset::removeData(int index) {
		inputs.erase(inputs.begin() + index);
		results.erase(results.begin() + index);
		length--;
	}
