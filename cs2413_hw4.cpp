#include <iostream>
#include <vector>
using namespace std;

class DirectAddress {

        vector<char> data;
        
    public:
        DirectAddress(vector<int> keys, vector<char> values) {
            for(int i=0; i < values.size(); i++)
                this->add(values[i], keys[i]);
        }

        /**
         * TESTING PURPOSES ONLY: Prints contents of data vector
         */
        void printData() {
            for(char i : data)
                cout << i << " ";
        }

        /**
         * Add value to table
         * @param value the value
         * @param key the key
         */
        void add(char value, int key) {
            if(key >= data.size())
                data.resize(key+1, '*');
            data[key] = value;
        }

        /**
         * Returns the value at given key
         * @param k the key
         * @return the value
         */
        char toChar(int k) {
            return data[k];
        }

        /**
         * Outputs several values from the table
         * @param searchKeys the keys to the desired values
         * @return the string of satellite values
         */
        void search(vector<int> searchKeys) {
            cout << toChar(searchKeys[0]);

            for(int i=1; i < searchKeys.size(); i++)
                cout << " " << toChar(searchKeys[i]);
        }
};

/**
 * Nodes that will store key/value pairs while separate chaining
 */
struct Node {
    char value;
    int key;
    Node* next;

    Node(char v, int k, Node* n) : value(v), key(k), next(n) {}
};

class HashTable {
        int mod, collision;
        vector<Node*> data;

    public:
        HashTable(vector<char> values, vector<int> keys, int mod, int collision) {
            for(int i=0; i < values.size(); i++)
                this->add(values[i], keys[i]);
            this->mod = mod;
            this->collision = collision;
        }

        /**
         * TESTING PURPOSES ONLY: Prints contents of data vector
         */
        void printData() {
            for(Node* i : data)
                cout << i << " ";
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
        char toChar(int k) {
            return data[hash(k)]->value;
        }

        /**
         * Outputs several search values
         * @param searchKeys the keys to the desired values
         * @return the string of satellite values
         */
        string search(vector<int> searchKeys) {
            cout << toChar(searchKeys[0]);
            for(int i=1; i < searchKeys.size(); i++)
                cout << " " << toChar(searchKeys[i]);
        }
};

int main() {
    int key, impTable, mod;
    char satVal;
    vector<char> satData;
    vector<int> tableKeys, searchKeys;

    while(!cin.fail()) {                // Take in data
        cin >> key;
        if(key == -1) break;
        tableKeys.push_back(key);
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
        cin >> key;
        if(key == -1) break;
        searchKeys.push_back(key);
    }

    switch(impTable) {
        case 0:
        {
            DirectAddress* table = new DirectAddress(tableKeys, satData);
            table->search(searchKeys);
        } break;

        case 1 || 2:
        {
            HashTable* table = new HashTable(satData, tableKeys, mod, impTable);
            table->search(searchKeys);
        } break;

        default: break;
    }
}