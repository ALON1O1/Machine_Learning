#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

#include "DatasetList.h"
#include "Dataset.h"
#include "NetworkList.h"
#include "Math/Vector.h"
#include "NeuralNetworks/Enums.h"
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
							while (line.length() > 0 && results_num > 0) {
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
					if (!datasetFile.good()) cout << "dataset \"" << command[1] << "\" could not be found" << endl;
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
							while (line.length() > 0 && results_num > 0) {
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
				if (command.size() != 3) cout << "wrong syntax! correct syntax for \"import_network\" is 'import_network <file address and name> <network name>" << endl;
				else {
					ifstream networkFile;
					networkFile.open(command[1] + ".csv", ios::in);
					if (!networkFile.good()) cout << "network \"" << command[2] << "\" could not be found" << endl;
					else {
						string network_string;
						string line;
						getline(networkFile, network_string);
						while (getline(networkFile, line)) network_string += "\n" + line;
						if (networks.addNetwork(NeuralNetwork::NeuralNetwork(network_string), command[2])) cout << "network '" + command[2] + "' was successfully loaded" << endl;
						else cout << "network could not be added, there is already a network named '" + command[2] + "'" << endl;
					}
				}
			}
			else if (command[0]._Equal("export_network")) {
				if (command.size() != 3) cout << "wrong syntax! correct syntax for \"export_network\" command is 'export_network <save path> <network name>" << endl;
				string s = networks.getNetwork(command[2]).getSaveString();
				ofstream networkFile(command[1] + "\\" + command[2] + ".csv");
				networkFile << s << endl;
				networkFile.close();
				cout << "network '" + command[2] + "' was saved successfully" << endl;
			}
			else if (command[0]._Equal("load_network")) {
				if (command.size() != 2) cout << "wrong syntax! correct syntax for \"load_network\" is 'load_network <network name>" << endl;
				else {
					ifstream networkFile;
					networkFile.open(networks_path + command[1] + ".csv", ios::in);
					if (!networkFile.good()) cout << "network \"" << command[1] << "\" could not be found" << endl;
					else {
						string network_string;
						string line;
						getline(networkFile, network_string);
						while (getline(networkFile, line)) network_string += "\n" + line;
						if (networks.addNetwork(NeuralNetwork::NeuralNetwork(network_string), command[1])) cout << "network '" + command[1] + "' was successfully loaded" << endl;
						else cout << "network could not be added, there is already a network named '" + command[1] + "'" << endl;
					}
				}
			}
			else if (command[0]._Equal("save_network")) {
				if (command.size() != 2) cout << "wrong syntax! correct syntax for \"save_network\" command is 'save_network <network name>" << endl;
				string s = networks.getNetwork(command[1]).getSaveString();
				ofstream networkFile(networks_path + command[1] + ".csv");
				networkFile << s << endl;
				networkFile.close();
				cout << "network '" + command[1] + "' was saved successfully" << endl;
			}
			else if (command[0]._Equal("show_network_list")) {
				vector<string> names = networks.getAllNames();
				if (names.size() == 0) cout << "no networks have been loaded" << endl;
				else for (string s : names) cout << s << endl;
			}
			else if (command[0]._Equal("remove_all_networks")) {
				networks.removeAll();
				cout << "networks list is now enpty" << endl;
			}
			else if (command[0]._Equal("create")) {
				bool cancel = false;
				string network_name = "";
				int inputs_num = 0;
				vector<NeuralNetwork::LayerType> layer_types;
				vector<NeuralNetwork::ActivationFunction> activation_functions;
				vector<int> sizes;
				NeuralNetwork::LossFunction loss_function = NeuralNetwork::LossFunction::unknown;
				while (!cancel) {
					vector<string> create_command = receiveCommand(">create>");
					if (create_command[0]._Equal("cancel")) cancel = true;
					else if (create_command[0]._Equal("name")) {
						if (create_command.size() != 2) cout << "wrong syntax! correct syntax for \"create name\" command is 'name <network name>" << endl;
						else if (networks.networkExists(create_command[1])) cout << "a network with the name '" + create_command[1] + "' has already been loaded, please choose another name" << endl;
						else network_name = create_command[1];
					}
					else if (create_command[0]._Equal("number_of_inputs")) {
						if (create_command.size() != 2) cout << "wrong syntax! correct syntax for \"create number_of_inputs\" command is 'number_of_inputs <inputs number>" << endl;
						else {
							int temp = std::stoi(create_command[1]);
							if (temp <= 0) cout << "number of inputs must be a positive integer" << endl;
							else inputs_num = temp;
						}
					}
					else if (create_command[0]._Equal("show_layer_data")) {
						if (create_command.size() != 2) cout << "wrong syntax! correct syntax for \"create show_layer_data\" is 'show_layer_data <layer index>" << endl;
						else {
							int index = std::stoi(create_command[1]);
							if (index < 0 || (unsigned)index >= sizes.size()) cout << "index must not be negative and must be smaller than the current number of layers" << endl;
							else {
								cout << "Layer Type: " + NeuralNetwork::enumOperations::getName(layer_types[index]) << endl;
								cout << "Activation Function: " + NeuralNetwork::enumOperations::getName(activation_functions[index]) << endl;
								cout << "number of perceptrons: " + std::to_string(sizes[index]) << endl;
							}
						}
					}
					else if (create_command[0]._Equal("show_data")) {
						cout << "name:" + network_name << endl;
						cout << "number of inputs:" + std::to_string(inputs_num) << endl;
						cout << "loss function:" + NeuralNetwork::enumOperations::getName(loss_function) << endl;
					}
					else if (create_command[0]._Equal("remove_layer")) {
						if (create_command.size() != 2) cout << "wrong syntax! correct syntax for \"create remove_layer\" command is 'remove_layer <layer index>'" << endl;
						int index = std::stoi(create_command[1]);
						if (index < 0 || (unsigned)index >= sizes.size()) cout << "index must not be negative and must be smaller than the current number of layers" << endl;
						else {
							sizes.erase(sizes.begin() + index);
							layer_types.erase(layer_types.begin() + index);
							activation_functions.erase(activation_functions.begin() + index);
						}
					}
					else if (create_command[0]._Equal("loss_function")) {
						if (create_command.size() != 2) cout << "wrong syntax! correct syntax for \"create loss_function\" command is 'loss_function <function name>'" << endl;
						else {
							loss_function = NeuralNetwork::enumOperations::getLossFunction(create_command[1]);
						}
					}
					else if (create_command[0]._Equal("finish")) {
						if (network_name.empty() || inputs_num == 0 || sizes.size() == 0 || loss_function == NeuralNetwork::LossFunction::unknown) cout << "please set all parameters before finishing" << endl;
						else cancel = networks.addNetwork(NeuralNetwork::NeuralNetwork(sizes, layer_types, activation_functions, inputs_num, loss_function), network_name);
					}
					else if (create_command[0]._Equal("add_layer")) {
						if (create_command.size() != 2) cout << "wrong syntax! correct syntax for \"create add_layer\" command is 'add_layer <layer type>'" << endl;
						else {
							switch (NeuralNetwork::enumOperations::getLayerType(create_command[1]))
							{
								case NeuralNetwork::LayerType::ANN: {
									bool innerCancel = false;
									int size = 0;
									NeuralNetwork::ActivationFunction aFunction = NeuralNetwork::ActivationFunction::unknown;
									while (!innerCancel) {
										vector<string> ann_command = receiveCommand(">create>add_layer_ANN>");
										if (ann_command[0]._Equal("cancel")) innerCancel = true;
										else if (ann_command[0]._Equal("size")) {
											if (ann_command.size() != 2) cout << "wrong syntax! correct syntax for \"create add_layer_ann size\" command is 'size <number of perceptrons>" << endl;
											else size = std::stoi(ann_command[1]);
										}
										else if (ann_command[0]._Equal("activation_function")) {
											if (ann_command.size() != 2) cout << "wrong syntax! correct syntax for \"create add_layer_ann activation_function\" command is 'activation_function <function name>" << endl;
											else aFunction = NeuralNetwork::enumOperations::getActivationFunction(ann_command[1]);
										}
										else if (ann_command[0]._Equal("finish")) {
											if (size == 0 || aFunction == NeuralNetwork::ActivationFunction::unknown) cout << "please enter all the parameters before finishing" << endl;
											else {
												sizes.push_back(size);
												activation_functions.push_back(aFunction);
												layer_types.push_back(NeuralNetwork::LayerType::ANN);
												innerCancel = true;
											}
										}
										else cout << command[0] + " is not a recognized command" << endl;
									}
								}
							default:
								break;
							}
						}
					}
					else if (create_command[0]._Equal("edit_layer")) {
						if (create_command.size() != 3) cout << "wrong syntax! correct syntax for \"create edit_layer\" command is 'edit_layer <layer index> <new layer type>'" << endl;
						else {
							int index = std::stoi(create_command[1]);
							if (index < 0 || (unsigned)index >= sizes.size())  cout << "index must not be negative and must be smaller than the current number of layers" << endl;
							else {
								switch (NeuralNetwork::enumOperations::getLayerType(create_command[2]))
								{
									case NeuralNetwork::LayerType::ANN: {
										bool innerCancel = false;
										int size = sizes[index];
										NeuralNetwork::ActivationFunction aFunction = activation_functions[index];
										while (!innerCancel) {
											vector<string> ann_command = receiveCommand(">create>add_layer_ANN>");
											if (ann_command[0]._Equal("cancel")) innerCancel = true;
											else if (ann_command[0]._Equal("size")) {
												if (ann_command.size() != 2) cout << "wrong syntax! correct syntax for \"create add_layer_ann size\" command is 'size <number of perceptrons>" << endl;
												else size = std::stoi(ann_command[1]);
											}
											else if (ann_command[0]._Equal("activation_function")) {
												if (ann_command.size() != 2) cout << "wrong syntax! correct syntax for \"create add_layer_ann activation_function\" command is 'activation_function <function name>" << endl;
												else aFunction = NeuralNetwork::enumOperations::getActivationFunction(ann_command[1]);
											}
											else if (ann_command[0]._Equal("finish")) {
												if (size == 0 || aFunction == NeuralNetwork::ActivationFunction::unknown) cout << "please enter all the parameters before finishing" << endl;
												else {
													sizes[index] = size;
													activation_functions[index] = aFunction;
													layer_types[index] = NeuralNetwork::LayerType::ANN;
													innerCancel = true;
												}
											}
											else cout << ann_command[0] + " is not a recognized command" << endl;
										}
									}
									default:
										break;
								}
							}
						}
					}
					else {
						cout << create_command[0] + " is not a recognized command" << endl;
					}
				}
			}
			else if (command[0]._Equal("test_network")) {
				if (command.size() != 4) cout << "wrong syntax! correct syntax for \"test_network\" command is 'test_network <network name> <dataset name> <target result miss>" << endl;
				else {
					NeuralNetwork::NeuralNetwork network = networks.getNetwork(command[1]);
					Dataset dataset;
					datasets.getDataset(command[2], dataset);
					float max_miss = std::stof(command[3]);
					cout << "network test started" << endl;
					vector<vector<float>> inputs = vector<vector<float>>();
					vector<vector<float>> target_results = vector<vector<float>>();
					dataset.getAllData(inputs, target_results);
					float avgMiss = 0;
					int success_counter = 0;
					for (unsigned int i = 0; i < inputs.size(); i++) {
						vector<float> results = network.feedForward(inputs[i]);
						std::vector<float> miss = Math::Vector::Sub(target_results[i], results);
						for (unsigned int j = 0; j < target_results[i].size(); j++) {
							if (miss[j] < 0) miss[j] = -miss[j];
							if (miss[j] < max_miss) success_counter++;
							avgMiss += miss[j];
						}
						miss.~vector();
						cout << i << "/" << inputs.size() << endl;
					}
					cout << "AvgMiss: " + std::to_string(avgMiss / (float)(target_results.size() * target_results[0].size())) + "	corrects: " + std::to_string(success_counter) + "/" + std::to_string(target_results.size() * target_results[0].size()) << endl;
					cout << "network test has ended" << endl;
				}
			}
			else if (command[0]._Equal("train_network")) {
				if (command.size() != 6) cout << "wrong syntax! correct syntax for \"train_network\" command is 'train_network <network name> <dataset name> <rate of change> <batch size> <number of repetitions>" << endl;
				else {
					NeuralNetwork::NeuralNetwork network = networks.getNetwork(command[1]);
					Dataset dataset;
					datasets.getDataset(command[2], dataset);
					float rate_of_change = stof(command[3]);
					unsigned int batch_size = stoi(command[4]);
					unsigned int repeats = stoi(command[5]);
					cout << "network training started" << endl;
					vector<vector<float>> inputs;
					vector<vector<float>> target_results;
					dataset.getAllData(inputs, target_results);
					float start_cost = network.getAverageCost(inputs, target_results);
					for (unsigned int i = 0; i < repeats; i++) {
						auto start_time = std::chrono::high_resolution_clock::now();
						network.stochasticBackPropagation(inputs, target_results, rate_of_change, batch_size);
						auto end_time = std::chrono::high_resolution_clock::now();
						cout << i + 1 << "/" << repeats << "	" << chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count() / 1000000000.0 << "s" << endl;
					}
					cout << "start cost:" << start_cost << "	end cost:" << network.getAverageCost(inputs, target_results) << endl;
					cout << "network training ended" << endl;
				}
			}
			else if (command[0]._Equal("show_results")) {
				if (command.size() != 4) throw std::invalid_argument("wrong syntax! correct syntax for \"show_results\" command is 'show_results <network name> <dataset name> <data sample index>");
				else {
					NeuralNetwork::NeuralNetwork network = networks.getNetwork(command[1]);
					Dataset dataset;
					datasets.getDataset(command[2], dataset);
					int index = stoi(command[3]);
					vector<float> inputs;
					vector<float> target_results;
					dataset.getData(index, inputs, target_results);
					vector<float> results = network.feedForward(inputs);
					cout << "results" << endl;
					for (float i : results) cout << i << "	";
					cout << endl << "target results" << endl;
					for (float i : target_results) cout << i << "	";
					cout << endl;
				}
			}
			else {
				cout << command[0] + " is not a recognized command" << endl;
			}
		}
		catch (exception& e) {
			cout << "EXCEPTION!!! " << e.what() << endl;
		}
	}
}