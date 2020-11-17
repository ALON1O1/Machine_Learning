#pragma once

#include <vector>
#include <string>

class Dataset
{
	private:
		std::vector<std::vector<float>> inputs;
		std::vector<std::vector<float>> results;
		int length;

	public:
		Dataset();
		~Dataset();
		int getLength();
		std::vector<float> getInputs(int index);
		std::vector<float> getResults(int index);
		void addData(std::vector<float> inputs, std::vector<float> results);
		void getData(int index, std::vector<float>& return_inputs, std::vector<float>& return_results);
		void getAllData(std::vector<std::vector<float>>& return_inputs, std::vector<std::vector<float>>& return_results);
		void getSaveString(std::vector<std::string>& saveString);
		void removeData(int index);
};

