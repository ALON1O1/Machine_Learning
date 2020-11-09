#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "DatasetList.h"
#include "Dataset.h"
#include "NetworkList.h"
#include "NeuralNetworks/NeuralNetwork.h"

using namespace std;

vector<string> receiveCommand(const char* msg) {
	cout << msg;
	string temp;
	getline(cin, temp);
	vector<string> temp1;
	while (temp.length() > 0) {
		int index = temp.find(" ", 0);
		if (index == -1) index = temp.length();
		temp1.push_back(temp.substr(0, index));
		temp.erase(0, index + 1);
	}
	return temp1;
}

int main() {
	enum commands {create};
	string networks_path = "resources\\networks\\";
	string dataset_path = "resources\\datasets\\";
	DatasetList datasets = DatasetList();
	NetworkList networks = NetworkList();

	bool shouldContinue = true;
	while (shouldContinue) {
		try {
			vector<string> command = receiveCommand(">");
			if (command[0]._Equal("quit")) shouldContinue = false;
			else if (command[0]._Equal("show_dataset")) {
				if (command.size() != 2) cout << "wrong syntax! correct syntax for \"show_dataset\" is 'show_dataset <dataset name>'" << endl;
				else {
					Dataset dataset = Dataset();
					if (datasets.getDataset(command[1], dataset)) {
						vector<string> strings = vector<string>();
						dataset.getSaveString(strings);
						cout << strings.size() << endl;
						for (string i : strings) {
							cout << i << endl;
						}
					}
					else {
						cout << "dataset '" + command[1] + "' could not be found" << endl;
					}
				}
			}
			else if(command[0]._Equal("remove_dataset")) {
				if (command.size() != 2) cout << "wrong syntax! correcto syntax for \"remove_dataset\" command is 'remove_dataset <dataset name>'" << endl;
				else {
					if (datasets.removeDataset(command[1]))cout << "dataset '" + command[1] + "' was successfully removed" << endl;
					else cout << "dataset '" + command[1] + "' could not be found" << endl;
				}
			}
			else if (command[0]._Equal("rename_dataset")) {
				if (command.size() != 3) cout << "wrong syntax! correct syntax for \"rename_dataset\" command is 'rename_dataset <dataset name>'" << endl;
				else {
					if (datasets.renameDataset(command[1], command[2])) cout << "dataset '" + command[1] + "' was successfully renamed to '" + command[2] + "'" << endl;
					else cout << "dataset '" + command[1] + "' could not be found" << endl;
				}
			}
			else if (command[0]._Equal("import_dataset")) {
				if (command.size() != 3) cout << "wrong syntax! correct syntax for \"import_dataset\" is 'import_dataset <filepath and name> <dataset name>'" << endl;
				else {
					ifstream datasetFile;
					datasetFile.open(command[1] + ".csv", ios::in);
					if (!datasetFile.good()) cout << "file \"" << command[1] << "\" could not be found" << endl;
					else {
						string line;
						Dataset dataset;
						while (getline(datasetFile, line)) {
							vector<float> inputs;
							vector<float> results;
							int index = line.find(",", 0);
							if (index == -1) index = line.length();
							int inputs_num = stoi(line.substr(0, index));
							line.erase(0, index + 1);
							while (line.length() > 0 && inputs_num > 0) {
								index = line.find(",", 0);
								if (index == -1) index = line.length();
								inputs.push_back(stof(line.substr(0, index)));
								line.erase(0, index + 1);
								inputs_num--;
							}
							index = line.find(",", 0);
							if (index == -1) index = line.length();
							int results_num = stoi(line.substr(0, index));
							line.erase(0, index + 1);
							while (line.length() > 0 && inputs_num > 0) {
								index = line.find(",", 0);
								if (index == -1) index = line.length();
								results.push_back(stof(line.substr(0, index)));
								line.erase(0, index + 1);
								results_num--;
							}
							dataset.addData(inputs, results);
						}
						if (datasets.addDataset(dataset, command[2])) cout << "successfully imported dataset '" + command[2] + "'" << endl;
						else cout << "dataset could not be added, there is already a dataset named '" + command[2] + "'" << endl;
					}
				}
			}
			else if (command[0]._Equal("export_dataset")) {
				if (command.size() != 3) cout << "wrong syntax! correct syntax for \"export_dataset\" command is 'export_dataset <path to export location> <dataset name>'" << endl;
				else {
					Dataset dataset;
					if (!datasets.getDataset(command[2], dataset)) cout << "dataset '" + command[2] + "' could not be found" << endl;
					else {
						vector<string> strings;
						dataset.getSaveString(strings);
						ofstream datasetFile(command[1] + "\\" + command[2] + ".csv");
						for (string i : strings) {
							datasetFile << i << endl;
						}
						datasetFile.close();
						cout << "dataset '" + command[2] + "' was saved successfully" << endl;
					}
				}
			}
			else if (command[0]._Equal("load_dataset")) {
				if (command.size() != 2) cout << "wrong syntax! correct syntax for \"load_dataset\" is 'load_dataset <dataset name>" << endl;
				else {
					ifstream datasetFile;
					datasetFile.open(dataset_path + command[1] + ".csv", ios::in);
					if (!datasetFile.good()) cout << "file \"" << command[1] << "\" could not be found" << endl;
					else {
						string line;
						Dataset dataset;
						while (getline(datasetFile, line)) {
							vector<float> inputs;
							vector<float> results;
							int index = line.find(",", 0);
							if (index == -1) index = line.length();
							int inputs_num = stoi(line.substr(0, index));
							line.erase(0, index + 1);
							while (line.length() > 0 && inputs_num > 0) {
								index = line.find(",", 0);
								if (index == -1) index = line.length();
								inputs.push_back(stof(line.substr(0, index)));
								line.erase(0, index + 1);
								inputs_num--;
							}
							index = line.find(",", 0);
							if (index == -1) index = line.length();
							int results_num = stoi(line.substr(0, index));
							line.erase(0, index + 1);
							while (line.length() > 0 && inputs_num > 0) {
								index = line.find(",", 0);
								if (index == -1) index = line.length();
								results.push_back(stof(line.substr(0, index)));
								line.erase(0, index + 1);
								results_num--;
							}
							dataset.addData(inputs, results);
						}
						if (datasets.addDataset(dataset, command[1])) cout << "successfully loaded dataset '" + command[1] + "'" << endl;
						else cout << "dataset could not be added, there is already a dataset named '" + command[1] + "'" << endl;
					}
				}
			}
			else if (command[0]._Equal("save_dataset")) {
				if (command.size() != 2) cout << "wrong syntax! correct syntax for \"save_dataset\" command is 'save_dataset <dataset name>'" << endl;
				else {
					Dataset dataset;
					if (!datasets.getDataset(command[1], dataset)) cout << "dataset '" + command[1] + "' could not be found" << endl;
					else {
						vector<string> strings;
						dataset.getSaveString(strings);
						ofstream datasetFile(dataset_path + command[1] + ".csv");
						for(string i : strings) {
							datasetFile << i << endl;
						}
						datasetFile.close();
						cout << "dataset '" + command[1] + "' was saved successfully" << endl;
					}
				}

			}
			else if (command[0]._Equal("show_dataset_list")) {
				vector<string> names;
				datasets.getNames(names);
				if (names.size() == 0) cout << "no datasets have been loaded" << endl;
				else {
					for (string i : names) cout << i << endl;
				}
			}
			else if (command[0]._Equal("remove_all_datasets")) {
				datasets.removeAll();
				cout << "dataset list is now empty" << endl;
			}
			else if (command[0]._Equal("show_network")) {
				if (command.size() != 2) cout << "wrong syntax! correct syntax for \"show_network\" command is 'show_network <network name>'" << endl;
				else {
				cout << networks.getNetwork(command[1]).toString() << endl;
				}
			}
			else if (command[0]._Equal("remove_network")) {
				if (command.size() != 2) cout << "wrong syntax! correct syntax for \"remove_network\" command is 'remove_network <network name>'" << endl;
				else {
					if (networks.removeNetwork(command[1])) cout << "network '" + command[1] + "' was successfully removed" << endl;
					else cout << "could not find network '" + command[1] + "'" << endl;
				}
			}
			else if (command[0]._Equal("rename_network")) {
				if (command.size() != 3) cout << "wrong syntax! correct syntax for \"rename_network\" command is 'remove_network <old network name> <new network name>'" << endl;
				else {
					if (networks.renameNetwork(command[1], command[2])) cout << "network '" + command[1] + "' was successfully renamed to '" + command[2] + "'" << endl;
					else cout << "could not find network '" + command[1] + "'" << endl;
				}
			}
			else if (command[0]._Equal("import_network")) {
				cout << 13 << endl;
			}
			else if (command[0]._Equal("export_network")) {
				cout << 14 << endl;
			}
			else if (command[0]._Equal("load_network")) {
				cout << 15 << endl;
			}
			else if (command[0]._Equal("save_network")) {
				cout << 16 << endl;
			}
			else if (command[0]._Equal("show_network_list")) {
				cout << 17 << endl;
			}
			else if (command[0]._Equal("remove_all_networks")) {
				cout << 18 << endl;
			}
			else if (command[0]._Equal("create")) {
				cout << 19 << endl;
			}
			else if (command[0]._Equal("test_network")) {
				cout << 20 << endl;
			}
			else if (command[0]._Equal("train_network")) {
				cout << 21 << endl;
			}
			else if (command[0]._Equal("show_results")) {
				cout << 22 << endl;
			}
			else {
				cout << 23 << endl;
			}
		}
		catch (exception& e) {
			cout << "EXCEPTION!!! " << e.what() << endl;
		}
	}
}