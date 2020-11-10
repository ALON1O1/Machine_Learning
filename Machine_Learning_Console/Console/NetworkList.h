#pragma once
#include <vector>
#include <string>
#include "NeuralNetworks/NeuralNetwork.h"
class NetworkList
{
	private:
		std::vector<std::string> names;
		std::vector<NeuralNetwork::NeuralNetwork> networks;
		int length;
		int getNetworkIndex(std::string name);

	public:
		NetworkList();
		bool addNetwork(NeuralNetwork::NeuralNetwork network, std::string name);
		bool removeNetwork(std::string name);
		void removeAll();

		bool networkExists(std::string name);
		NeuralNetwork::NeuralNetwork getNetwork(std::string name);
		bool renameNetwork(std::string old_name, std::string new_name);
		std::vector<std::string> getAllNames();
};

