#include <iostream>
#include <vector>
using namespace std;

class DirectAddress {
    private:
        vector<int> data = {};

    public:
        DirectAddress() {
            this->data = {};
        }

        /**
         * Add key value
         * @param x key value
         */
        void add(int x) {
            data.insert(data.begin()+x, x);
        }
        
        /**
         * Remove key value
         * @param x key value
         */
        void remove(int x) {
            data.erase(data.begin()+x);
        }

        /**
         * Output key value
         * @param x key value
         * @return the key value
         */
        string toString(int x) {
            return "" + data[x];
        }

        /**
         * Overload: Returns several probed values from the DA table
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
        vector<int> data;

    public:
        HashTable(int mod, int collision) {
            this->data = {};
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
         * Add key value after running hash function
         * @param x key value
         */
        void add(int key, int value) {
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
         * Remove key value
         * @param key value
         */
        void remove(int x) {
            data.erase(data.begin()+hash(x));
        }

        /**
         * Output key value
         * @param x key value
         * @return the key value
         */
        string toString(int x) {
            return "" + data[hash(x)];
        }

        /**
         * Overload: Returns several probed values from the hash table
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

    while(!cin.fail()) {                // Take in search keys
        cin >> val;
        if(val == -1) break;
        searchKeys.push_back(val);
    }

    switch(impTable) {
        case 0:
        {
            DirectAddress *table = new DirectAddress();
            cout << table->toString(searchKeys);
        } break;

        case 1 || 2:
        {
            HashTable *table = new HashTable(mod, impTable);
            cout << table->toString(searchKeys);
        } break;

        default: break;
    }
}