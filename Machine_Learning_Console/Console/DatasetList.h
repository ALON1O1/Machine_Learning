#pragma once

#include <vector>
#include <string>
#include "Dataset.h"

class DatasetList
{
	private:
		std::vector<Dataset> datasets;
		std::vector<std::string> names;
		int length;
		int nameIndex(std::string name);

	public:
		DatasetList();
		~DatasetList();
		bool addDataset(Dataset dataset, std::string name);
		bool removeDataset(std::string name);
		bool renameDataset(std::string old_name, std::string new_name);
		bool getDataset(std::string name, Dataset& dataset);
		void getNames(std::vector<std::string>& return_names);
		void getAll(std::vector<Dataset>& return_datasets);
		void removeAll();
};

