#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> test = {0, 1, 2};
    test.insert(test.begin()+4, 4);
    cout << " Index 3: " << test[3] << endl;
    cout << " Index 4: " << test[4] << endl;
}