#pragma once
class Dataset
{
	public:
		Dataset();
		int getLength();
		void addData(float inputs[], float results[]);
		float* getInputs(int index);
		vector<float*>getAllInputs();
		vector<float*>getAllResults();
		float* getResults(int index);
		vector<string> getSaveString();
		void removeData(int index);
};

