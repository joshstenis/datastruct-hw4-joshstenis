#include <iostream>
#include <vector>
using namespace std;

/**
 * Nodes that will store key/value pairs while separate chaining
 */
struct Node {
    char value;
    int key;
    Node* next;

    Node(char v, int k, Node* n) : value(v), key(k), next(n) {}
};

class DirectAddress {
        vector<char> data = {};

    public:
        DirectAddress() {
            this->data = {};
        }

        DirectAddress(vector<int> keys, vector<char> values) {
            for(int i=0; i < values.size(); i++)
                this->add(keys[i], values[i]);
        }

        /**
         * Add value to table
         * @param value the value
         * @param key the key
         */
        void add(char value, int key) {
            if(key >= data.size())
                data.resize(key+1, '*');
            data.insert(data.begin()+key, value);
        }
        
        /**
         * Remove value from table
         * @param k key value
         */
        void remove(int k) {
            data.erase(data.begin()+k);
        }

        /**
         * Returns the value at given key
         * @param k the key
         * @return the value
         */
        string toString(int k) {
            return "" + data[k];
        }

        /**
         * Returns several values from the table
         * @param searchKeys the keys to the desired values
         * @return the string of satellite values
         */
        string toString(vector<int> searchKeys) {
            string ret;

            for(int i : searchKeys)
                ret += toString(searchKeys[i]) + " ";
            ret.pop_back();

            return ret;
        }
};

class HashTable {
        int mod, collision;
        vector<Node*> data;

    public:
        HashTable(int mod, int collision) {
            this->mod = mod;
            this->collision = collision;
        }

        HashTable(vector<char> values, vector<int> keys, int mod, int collision) {
            for(int i : values)
                this->add(values[i], keys[i]);
            this->mod = mod;
            this->collision = collision;
        }

        /**
         * Apply hash function to key value
         * @param k key value
         * @return the index of the key value
         */
        int hash(int k) {
            return k % mod;
        }

        /**
         * Add value after running hash function
         * @param value the value associated with key
         * @param key the key
         */
        void add(char value, int key) {
            if(data[hash(key)]->value != '*' && this->collision == 1) {                 // Separate chaining
                Node* n = data[hash(key)];
                while(data[hash(key)]->value != '*')
                    n = n->next;
                Node* node = new Node(value, key, NULL);
                n->next = node;
            } else if (data[hash(key)]->value != '*' && this->collision == 2) {         // Quadratic probing
                // bruh
            } else {
                if(hash(key) >= data.size()) data.resize(hash(key)+1, new Node('*', 0, NULL));
                data.insert(data.begin()+hash(key), new Node(value, key, NULL));
            }
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
         * @param k key value
         * @return the satellite value
         */
        string toString(int k) {
            return "" + data[hash(k)]->value;
        }

        /**
         * Returns several values
         * @param searchKeys the keys to the desired values
         * @return the string of satellite values
         */
        string toString(vector<int> searchKeys) {
            string ret;

            for(int i : searchKeys)
                ret += toString(searchKeys[i]) + " ";
            ret.pop_back();

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
            DirectAddress* table = new DirectAddress(tableKeys, satData);
            cout << table->toString(searchKeys);
        } break;

        case 1 || 2:
        {
            HashTable* table = new HashTable(satData, tableKeys, mod, impTable);
            cout << table->toString(searchKeys);
        } break;

        default: break;
    }
}