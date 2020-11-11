#include <iostream>
#include <vector>
using namespace std;

struct DATable {
    private:
        vector<int> data = {};

    public:

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
        vector<int> data;

    public:
        HashTable() {
            this->data = {};
        }

        /**
         * Apply hash function to key value
         * @param x key value
         * @return the index of the key value
         */
        int hash(int x) {
            return x % 10;
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

}