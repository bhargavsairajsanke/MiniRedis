#include "KeyValueStore.h"

using namespace std;

void KeyValueStore::removeExpired(const string& key) {
    auto it = expiryTime.find(key);

    if (it != expiryTime.end()) {
        if (time(nullptr) >= it->second) {
            database.erase(key);
            expiryTime.erase(it);
        }
    }
}

void KeyValueStore::removeExpiredKeys()
{
    std::vector<std::string> expired;

    for (const auto& item : expiryTime)
    {
        if (time(nullptr) >= item.second)
            expired.push_back(item.first);
    }

    for (const std::string& key : expired)
    {
        database.erase(key);
        expiryTime.erase(key);
    }
}

void KeyValueStore::set(
    const string& key,
    const string& value
) {
    database[key] = value;
    expiryTime.erase(key);   // remove any old TTL
}

void KeyValueStore::setWithExpiry(
    const string& key,
    const string& value,
    int seconds
) {
    database[key] = value;
    expiryTime[key] = time(nullptr) + seconds;
}

bool KeyValueStore::get(
    const string& key,
    string& value
) {
    removeExpired(key);

    auto it = database.find(key);

    if (it == database.end())
        return false;

    value = it->second;
    return true;
}

bool KeyValueStore::remove(const string& key) {
    expiryTime.erase(key);
    return database.erase(key) > 0;
}

bool KeyValueStore::exists(const string& key) {
    removeExpired(key);
    return database.find(key) != database.end();
}

vector<string> KeyValueStore::getAllKeys() {

    removeExpiredKeys();

    vector<string> keys;

    for (const auto& entry : database)
        keys.push_back(entry.first);

    return keys;
}

void KeyValueStore::clear() {
    database.clear();
    expiryTime.clear();
}

size_t KeyValueStore::count() {
    removeExpiredKeys();
    return database.size();
}

const unordered_map<string, string>&
KeyValueStore::getData() const {
    return database;
}

void KeyValueStore::loadData(
    const unordered_map<string, string>& data
) {
    database = data;
    expiryTime.clear();   // TTLs are not persisted in V1
}
