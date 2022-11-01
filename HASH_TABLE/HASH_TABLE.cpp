#include <iostream>
#include <list>
#include <string>

class HashTable {
private:
	static const int hashGroups = 10; //seperate chaining methid requires you to specify the no. of groups
	std::list<std::pair<int, std::string>> table[hashGroups];
public:
	bool isEmpty() const;
	int hashFunction(int key);
	void insertItem(int key, std::string value);
	void removeItem(int key);
	std::string searchTable(int key);
	void printTable();
};

bool HashTable::isEmpty() const
{
	int sum = 0;
	for (int i = 0; i < hashGroups; i++) {
		sum += (int)table[i].size();
	}
	if (!sum) {
		return true;
	}
	else {
		return false;
	}
}

int HashTable::hashFunction(int key)
{
	return key % hashGroups; //condenses larger key numbers into the list
}

void HashTable::insertItem(int key, std::string value) //inserting key value pair
{
	int hashValue = hashFunction(key);
	auto& cell = table[hashValue]; //
	bool keyExists = false;
	for (auto bItr = begin(cell); bItr != end(cell); bItr++) {
		if (bItr->first == key) {
			keyExists = true;
			bItr->second = value;
			std::cout << "[WARNING] The key already exists. Value Replaced." << std::endl;
			break;
		}
	}
	if (!keyExists) {
		cell.emplace_back(key, value);
	}
	return;
}

void HashTable::removeItem(int key)
{
	int hashValue = hashFunction(key); //find hash of key
	auto& cell = table[hashValue]; //find list of interest
	bool keyExists = false; //assume the key does not exist
	for (auto bItr = begin(cell); bItr != end(cell); bItr++) {
		if (bItr->first == key) {
			keyExists = true;
			bItr = cell.erase(bItr); //delete and replace the iterator
			std::cout << "[INFO] Item removed." << std::endl;
			break;
		}
	}
	if (!keyExists) {
		std::cout << "[INFO] No such key to remove." << std::endl;
	}
	return;
}

void HashTable::printTable() {
	for (int i = 0; i < hashGroups; i++) {
		if (table[i].size() == 0) {
			continue;
		}
		for (auto bItr = table[i].begin(); bItr != table[i].end(); bItr++) {
			std::cout << "[INFO] Key: " << bItr->first << " Value: " << bItr->second << std::endl;
		}
	}
	return;
}

std::string HashTable::searchTable(int key)
{
	//int hashValue = hashFunction(key); //find hash of key
	//auto& cell = table[hashValue]; //find list of interest
	//bool keyExists = false;
	std::string str;
	for (int i = 0; i < hashGroups; i++) {
		if (table[i].size() == 0) {
			continue;
		}
		for (auto bItr = table[i].begin(); bItr != table[i].end(); bItr++) {
			if (bItr->first == key) {
				std::cout << "Key found!" << std::endl;
				return str = "Key found!";
			}
			else {
				continue;
			}
		}
	}
	std::cout << "No key found!" << std::endl;
	return str = "No key found!";
}

int main()
{
	HashTable HT;

	if (HT.isEmpty()) {
		std::cout << "Hash table initialised: Currently empty." << std::endl;
	}
	else {
		std::cout << "Uh oh, hash isn't empty." << std::endl;
	}

	HT.insertItem(07424324, "Jack");
	HT.insertItem(07424356, "John");
	HT.insertItem(07424560, "Rob");
	HT.insertItem(07422347, "Nathan");
	HT.insertItem(07476530, "Phil");
	HT.insertItem(07456700, "Shane");
	HT.insertItem(07424567, "Todd");

	HT.insertItem(07424567, "David");

	HT.printTable();

	HT.removeItem(07424356);
	HT.removeItem(07424565);

	HT.searchTable(07424560);
	HT.searchTable(07424565);

	if (HT.isEmpty()) {
		std::cout << "Uh oh, the hash is currently empty?" << std::endl;
	}
	else {
		std::cout << "Nice, the hash table is holding stuff." << std::endl;
	}

	return 0;
}