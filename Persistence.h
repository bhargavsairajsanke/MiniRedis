#ifndef PERSISTENCE_H
#define PERSISTENCE_H

#include <string>
#include "KeyValueStore.h"

class Persistence {
private:
    std::string filename;

public:
    Persistence(const std::string& file = "database.txt");

    bool save(const KeyValueStore& store) const;
    bool load(KeyValueStore& store) const;
};

#endif