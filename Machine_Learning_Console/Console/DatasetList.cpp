#include "DatasetList.h"

DatasetList::DatasetList() {
	datasets = std::vector<Dataset>();
	names = std::vector<std::string>();
	length = 0;
}
DatasetList::~DatasetList() {
	names.~vector();
	datasets.~vector();
}
bool DatasetList::addDataset(Dataset dataset, std::string name) {
	if (nameIndex(name) != -1)return false;
	datasets.push_back(dataset);
	names.push_back(name);
	length++;
	return true;
}
bool DatasetList::removeDataset(std::string name) {
	int index = nameIndex(name);
	if (index == -1) return false;
	datasets.erase(datasets.begin() + index);
	names.erase(names.begin() + index);
	length--;
	return true;
}
bool DatasetList::renameDataset(std::string old_name, std::string new_name) {
	int index = nameIndex(old_name);
	if (index == -1) return false;
	names[index] = new_name;
	return true;
}
bool DatasetList::getDataset(std::string name, Dataset& dataset) {
	int index = nameIndex(name);
	if (index == -1) return false;
	dataset = datasets[index];
	return true;
}
void DatasetList::getNames(std::vector<std::string>& return_names) {
	return_names = names;
}
void DatasetList::getAll(std::vector<Dataset>& return_datasets) {
	return_datasets = datasets;
}
void DatasetList::removeAll() {
	datasets.clear();
	names.clear();
	length = 0;
}

int DatasetList::nameIndex(std::string name) {
	int i = 0;
	while (i < length && !names[i]._Equal(name)) i++;
	if (i == length) return -1;
	return i;
}