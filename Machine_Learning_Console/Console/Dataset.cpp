//#include "Dataset.h"
#include <vector>
#include <string>

using namespace std;
class Dataset {

	private:
		vector<float*> inputs;
		vector<float*> results;
		int length;

	public:
		Dataset() {
			inputs = vector<float*>();
			results = vector<float*>();
			length = 0;
		}
		int getLength() {
			return length;
		}
		void addData(float inputs[], float results[]) {
			this->inputs.push_back(inputs);
			this->results.push_back(results);
		}
		float* getInputs(int index) {
			static float* returnValue = inputs[index];
			return returnValue;
		}
		vector<float*> getAllInputs() {
			return inputs;
		}
		vector<float*> getAllResults() {
			return results;
		}
		float* getResults(int index) {
			static float* returnValue = results[index];
			return returnValue;
		}
		vector<string> getSaveString() {
			vector<string> returnValues = vector<string>();
			for (int i = 0; i < (int)(inputs.size()); i++) {
				string s = inputs.size() + "";
				for (int j = 0; j < sizeof(inputs[i]); j++) {
					s += "," + to_string(inputs.at(i)[j]);
				}
				s += "," + results.size();
				for (int j = 0; j < sizeof(results[i]); j++) {
					s += "," + to_string(inputs.at(i)[j]);
				}
				returnValues.push_back(s);
			}
			return returnValues;
		}
		void removeData(int index) {
			inputs.erase(inputs.begin() + index);
			results.erase(results.begin() + index);
		}
};
