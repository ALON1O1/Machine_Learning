#pragma once
class Dataset
{
	public:
		Dataset();
		int getLength();
		void addData(float inputs[], float results[]);
		void getData(vector<float[]> inputs, vector<float[]> results);
		float* getInputs(int index);
		vector<float[]>getAllInputs();
		vector<float[]>getAllResults();
		float* getResults(int index);
		string* getSaveString();
		void removeData(int index);
};

