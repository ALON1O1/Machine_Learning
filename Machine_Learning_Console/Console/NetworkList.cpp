#include "NetworkList.h"

NetworkList::NetworkList() {
	names = std::vector<std::string>();
	networks = std::vector<NeuralNetwork::NeuralNetwork>();
	length = 0;
}

bool NetworkList::addNetwork(NeuralNetwork::NeuralNetwork network, std::string name) {
	if (getNetworkIndex(name) != -1) return false;
	networks.push_back(network);
	names.push_back(name);
	length++;
	return true;
}
bool NetworkList::removeNetwork(std::string name) {
	int index = getNetworkIndex(name);
	if (index == -1) return false;
	names.erase(names.begin() + index);
	networks.erase(networks.begin() + index);
	length--;
	return true;
}
void NetworkList::removeAll() {
	networks.clear();
	names.clear();
	length = 0;
}

bool NetworkList::networkExists(std::string name) {
	return getNetworkIndex(name) != -1;
}

NeuralNetwork::NeuralNetwork NetworkList::getNetwork(std::string name) {
	return networks[getNetworkIndex(name)];
}
bool NetworkList::renameNetwork(std::string old_name, std::string new_name) {
	int index = getNetworkIndex(old_name);
	if (index == -1) return false;
	names[index] = new_name;
	return true;
}
int NetworkList::getNetworkIndex(std::string name) {
	unsigned int i = 0;
	while (i < names.size() && !name._Equal(names[i])) i++;
	if (i < names.size()) return i;
	return -1;
}
std::vector<std::string> NetworkList::getAllNames() {
	return names;
}
