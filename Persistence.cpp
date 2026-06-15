#include "Persistence.h"

#include <fstream>
#include <unordered_map>

using namespace std;

Persistence::Persistence(const string& file)
    : filename(file) {}

bool Persistence::save(const KeyValueStore& store) const {
    ofstream outFile(filename);

    if (!outFile.is_open())
        return false;

    const unordered_map<string, string>& data = store.getData();

    for (const auto& entry : data)
        outFile << entry.first << "=" << entry.second << "\n";

    outFile.close();
    return true;
}

bool Persistence::load(KeyValueStore& store) const {
    ifstream inFile(filename);

    if (!inFile.is_open())
        return false;

    unordered_map<string, string> data;
    string line;

    while (getline(inFile, line)) {
        size_t pos = line.find('=');

        if (pos == string::npos)
            continue;

        string key = line.substr(0, pos);
        string value = line.substr(pos + 1);

        data[key] = value;
    }

    inFile.close();

    store.loadData(data);

    return true;
}