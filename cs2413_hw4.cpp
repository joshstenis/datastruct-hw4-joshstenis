#include <iostream>
#include <vector>
using namespace std;

class DATable {
    private:
        vector<int> data = {};

    public:
        DATable() {
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
};

class HashTable {
    private:
        int mod;
        vector<int> data;

    public:
        HashTable(int mod) {
            this->data = {};
            this->mod = mod;
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
         * Add key value after running hash function
         * @param x key value
         */
        void add(int x) {
            data.insert(data.begin()+hash(x), x);
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
};

int main() {
    int val, modulus;
    string satVal;

    while(!cin.fail()) {                // Take in data
        cin >> val;
        if(val == -1) break;
    }

    cin.ignore(1, '\n');
    while(!cin.fail()) {                // Take in satellite data
        cin >> satVal;
        if(satVal == "*") break;
    }
}