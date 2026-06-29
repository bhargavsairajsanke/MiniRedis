#include <iostream>
#include <string>
#include <vector>

#include "KeyValueStore.h"
#include "CommandParser.h"
#include "Persistence.h"

using namespace std;

void printHelp() {
    cout << "SET <key> <value>          : Store a key-value pair\n";
    cout << "SET <key> <value> NX       : Store only if key is absent\n";
    cout << "GET <key>                  : Retrieve value\n";
    cout << "DELETE <key>               : Remove a key\n";
    cout << "EXISTS <key>               : Check if key exists\n";
    cout << "KEYS                       : List all keys\n";
    cout << "COUNT                      : Show number of keys\n";
    cout << "CLEAR                      : Remove all keys\n";
    cout << "SAVE                       : Save database to file\n";
    cout << "LOAD                       : Load database from file\n";
    cout << "HELP                       : Show this message\n";
    cout << "EXIT                       : Quit program\n";
    cout << "SET <key> <value> EXPIRE <sec> : Store key with expiry\n";
}

int main() {
    KeyValueStore store;
    CommandParser parser;
    Persistence persistence("database.txt");

    string input;

    cout << "=====================================\n";
    cout << "      MiniRedis v1.1 (C++)\n";
    cout << "  Type HELP to view all commands.\n";
    cout << "=====================================\n";

    while (true) {
        cout << "> ";
        getline(cin, input);

        if (input.empty())
            continue;

        Command cmd = parser.parse(input);

       if (cmd.name == "SET") {

    if (cmd.args.size() < 2) {
        cout << "Usage: SET <key> <value>\n";
        continue;
    }

    string key = cmd.args[0];
    string value = cmd.args[1];

    if (cmd.args.size() == 4 &&
        cmd.args[2] == "EXPIRE") {

        int ttl = stoi(cmd.args[3]);

        if (ttl <= 0) {
            cout << "TTL must be positive.\n";
        }
        else {
            store.setWithExpiry(key, value, ttl);
            cout << "OK\n";
        }
    }

    else if (cmd.args.size() == 3 &&
             cmd.args[2] == "NX") {

        if (store.exists(key)) {
            cout << "Key already exists.\n";
        }
        else {
            store.set(key, value);
            cout << "OK\n";
        }
    }

    else {
        store.set(key, value);
        cout << "OK\n";
    }
}

        else if (cmd.name == "GET") {
            if (cmd.args.size() < 1) {
                cout << "Usage: GET <key>\n";
                continue;
            }

            string value;
            if (store.get(cmd.args[0], value))
                cout << value << endl;
            else
                cout << "Key not found\n";
        }

        else if (cmd.name == "DELETE") {
            if (cmd.args.size() < 1) {
                cout << "Usage: DELETE <key>\n";
                continue;
            }

            if (store.remove(cmd.args[0]))
                cout << "Deleted\n";
            else
                cout << "Key not found\n";
        }

        else if (cmd.name == "EXISTS") {
            if (cmd.args.size() < 1) {
                cout << "Usage: EXISTS <key>\n";
                continue;
            }

            cout << (store.exists(cmd.args[0]) ? "true" : "false") << endl;
        }

        else if (cmd.name == "KEYS") {
            vector<string> keys = store.getAllKeys();

            if (keys.empty())
                cout << "(empty)\n";
            else {
                for (const string& key : keys)
                    cout << key << endl;
            }
        }

        else if (cmd.name == "COUNT") {
            cout << store.count() << endl;
        }

        else if (cmd.name == "CLEAR") {
            store.clear();
            cout << "Database cleared.\n";
        }

        else if (cmd.name == "SAVE") {
            store.removeExpiredKeys();
            cout << (persistence.save(store)
                     ? "Database saved successfully.\n"
                     : "Failed to save database.\n");
        }

        else if (cmd.name == "LOAD") {
            cout << (persistence.load(store)
                     ? "Database loaded successfully.\n"
                     : "No database file found.\n");
        }

        else if (cmd.name == "HELP") {
            printHelp();
        }

        else if (cmd.name == "EXIT") {
            cout << "Exiting MiniRedis...\n";
            break;
        }

        else {
            cout << "Unknown command. Type HELP.\n";
        }
    }

    return 0;
}
