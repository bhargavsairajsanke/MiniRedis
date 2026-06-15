#ifndef KEYVALUESTORE_H
#define KEYVALUESTORE_H

#include <string>
#include <unordered_map>
#include <vector>
#include <ctime>

class KeyValueStore {
private:
    std::unordered_map<std::string, std::string> database;
    std::unordered_map<std::string, std::time_t> expiryTime;

    void removeExpired(const std::string& key);

public:
    void set(const std::string& key, const std::string& value);

    void setWithExpiry(
        const std::string& key,
        const std::string& value,
        int seconds
    );

    bool get(const std::string& key, std::string& value);
    bool remove(const std::string& key);
    bool exists(const std::string& key);

    std::vector<std::string> getAllKeys();
    void clear();
    size_t count();

    const std::unordered_map<std::string, std::string>& getData() const;
    void loadData(
        const std::unordered_map<std::string, std::string>& data
    );
};

#endif