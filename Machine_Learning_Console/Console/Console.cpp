#include <iostream>
#include <fstream>
#include <string>
#include <vector>

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

	bool shouldContinue = true;
	while (shouldContinue) {
		try {
			vector<string> command = receiveCommand(">");
			if (command[0]._Equal("quit")) shouldContinue = false;
			else if (command[0]._Equal("show_dataset")) {
				cout << 1 << endl;
			}
			else if(command[0]._Equal("remove_dataset")) {
				cout << 2 << endl;
			}
			else if (command[0]._Equal("rename_dataset")) {
				cout << 3 << endl;
			}
			else if (command[0]._Equal("import_dataset")) {
				cout << 4 << endl;
			}
			else if (command[0]._Equal("export_dataset")) {
				cout << 5 << endl;
			}
			else if (command[0]._Equal("load_dataset")) {
				cout << 6 << endl;
			}
			else if (command[0]._Equal("save_dataset")) {
				cout << 7 << endl;
			}
			else if (command[0]._Equal("show_dataset_list")) {
				cout << 8 << endl;
			}
			else if (command[0]._Equal("remove_all_datasets")) {
				cout << 9 << endl;
			}
			else if (command[0]._Equal("show_network")) {
				cout << 10 << endl;
			}
			else if (command[0]._Equal("remove_network")) {
				cout << 11 << endl;
			}
			else if (command[0]._Equal("rename_network")) {
				cout << 12 << endl;
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
		catch (int e) {
			cout << "EXCEPTION!!! " << e << endl;
		}
	}
}