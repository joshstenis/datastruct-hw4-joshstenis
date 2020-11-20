#include <iostream>
#include <vector>
using namespace std;

class DirectAddress {
    private:
        vector<char> data = {};

    public:
        DirectAddress() {
            this->data = {};
        }

        DirectAddress(vector<int> keys, vector<char> values) {
            for(int i=0; i< values.size(); i++)         // Populate data field with '*'
                data.push_back('*');

            for(int i=0; i < values.size(); i++)
                this->add(keys[i], values[i]);
            cout << "POPULATED" << endl;
        }

        /**
         * Add value to table
         * @param key the key
         * @param value the value
         */
        void add(int key, char value) {
            try {
                data.insert(data.begin()+key, value);
            } catch(const out_of_range& e) {
                while(data.size() <= key) {
                    data.push_back('*');
                } data.insert(data.begin()+key, value);
            }
        }
        
        /**
         * Remove value from table
         * @param x key value
         */
        void remove(int x) {
            data.erase(data.begin()+x);
        }

        /**
         * Returns the value at given key
         * @param x the key
         * @return the value
         */
        string toString(int x) {
            return "" + data[x];
        }

        /**
         * Returns several values from the table
         * @param searchKeys the keys to the desired values
         * @return the string of satellite values
         */
        string toString(vector<int> searchKeys) {
            string ret = toString(searchKeys[0]);

            for(int i=1; i < searchKeys.size(); i++) {
                ret += " " + toString(searchKeys[i]);
            } return ret;
        }
};

class HashTable {
    private:
        int mod, collision;
        vector<char> data;

    public:
        HashTable(int mod, int collision) {
            this->data = {'*'};
            this->mod = mod;
            this->collision = collision;
        }

        HashTable(vector<int> keys, vector<char> values, int mod, int collision) {
            this->data = {'*'};
            for(int i=0; i < values.size(); i++)
                this->add(keys[i], values[i]);
            this->mod = mod;
            this->collision = collision;
        }

        /**
         * Apply hash function to key value
         * @param x key value
         * @return the index of the key value
         */
        int hash(int x) {
            return x % mod;
        }

        /**
         * Handles collisions in table
         * @param AR Add/Remove indicator: indicates whether the collision is being added (1) or removed/accessed (-1)
         */
        void collide(int AR) {
            switch(AR) {
                case 1:
                {
                    // Adding collision
                    if(collision == 1) {
                        // separate chaining
                    } else if(collision == 2) {
                        // quadratic probing
                    }
                } break;

                case -1:
                {
                    // Removing collision
                    if(collision == 1) {
                        // separate chaining
                    } else if(collision == 2) {
                        // quadratic probing
                    }
                } break;

                default: break;
            }
        }

        /**
         * Add value after running hash function
         * @param key the key
         * @param value the value associated with key
         */
        void add(int key, char value) {
            data.insert(data.begin()+hash(key), value);
            
            // try {
            //     data.insert(data.begin()+hash(key), value);
            // } catch(const out_of_range& e) {
            //     while(data.size() <= hash(key)) {
            //         data.push_back(NULL);
            //     } data.insert(data.begin()+hash(key), value);
            // }
        }

        /**
         * Remove value at given key
         * @param key key value
         */
        void remove(int x) {
            data.erase(data.begin()+hash(x));
        }

        /**
         * Returns data at given key
         * @param x key value
         * @return the satellite value
         */
        string toString(int x) {
            return "" + data[hash(x)];
        }

        /**
         * Returns several values
         * @param searchKeys the keys to the desired values
         * @return the string of satellite values
         */
        string toString(vector<int> searchKeys) {
            string ret = toString(searchKeys[0]);

            for(int i=1; i < searchKeys.size(); i++)
                ret += " " + toString(searchKeys[i]);
            return ret;
        }
};

int main() {
    int val, modulus, impTable, mod;
    char satVal;
    vector<char> satData;
    vector<int> tableKeys, searchKeys;

    while(!cin.fail()) {                // Take in data
        cin >> val;
        if(val == -1) break;
        tableKeys.push_back(val);
    }

    cin.ignore(1, '\n');
    while(!cin.fail()) {                // Take in satellite data
        cin >> satVal;
        if(satVal == '*') break;
        satData.push_back(satVal);
    }

    cin >> impTable;
    cin >> mod;

    cin.ignore(1, '\n');
    while(!cin.fail()) {                // Take in search keys
        cin >> val;
        if(val == -1) break;
        searchKeys.push_back(val);
    }

    switch(impTable) {
        case 0:
        {
            DirectAddress *table = new DirectAddress(tableKeys, satData);
            cout << table->toString(searchKeys);
        } break;

        case 1 || 2:
        {
            HashTable *table = new HashTable(tableKeys, satData, mod, impTable);
            cout << table->toString(searchKeys);
        } break;

        default: break;
    }
}