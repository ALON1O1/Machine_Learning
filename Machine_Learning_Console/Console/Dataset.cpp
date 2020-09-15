#include "Dataset.h"
#include <vector>
#include <string>

using namespace std;
class Dataset {

	private:
		vector<float[]> inputs = vector<float[]>();
		vector<float[]> results = vector<float[]>();
		int length = 0;

	public:
		Dataset() {
			
		}

		int getLength() {
			return length;
		}
		void addData(float inputs[], float results[]) {

		}
		void getData(vector<float[]> inputs, vector<float[]> results) {

		}
		float* getInputs(int index) {

		}
		vector<float[]> getAllInputs() {
			return inputs;
		}
		vector<float[]> getAllResults() {
			return results;
		}
		float* getResults(int index) {

		}
		string* getSaveString() {

		}
		void removeData(int index) {

		}
};
