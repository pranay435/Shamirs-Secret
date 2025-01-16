#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;

long long decodeBaseValue(const string& value, int base) {
    long long decodedValue = 0;
    long long power = 1;
    for (int i = value.size() - 1; i >= 0; --i) {
        int digit = value[i] - '0';
        decodedValue += digit * power;
        power *= base;
    }
    return decodedValue;
}

double lagrangeInterpolation(const vector<long long>& x, const vector<long long>& y, int n, long long xp) {
    double yp = 0;
    for (int i = 0; i < n; ++i) {
        double p = 1;
        for (int j = 0; j < n; ++j) {
            if (i != j) {
                p = p * (xp - x[j]) / (x[i] - x[j]);
            }
        }
        yp = yp + p * y[i];
    }
    return yp;
}

void processTestCase(const string& filename) {
    ifstream inputFile(filename);
    json data;
    inputFile >> data;

    int n = data["keys"]["n"];
    int k = data["keys"]["k"];
    
    vector<long long> x, y;

    for (auto& item : data.items()) {
        if (item.key() != "keys") {
            int index = stoi(item.key());
            string base = item.value()["base"];
            string value = item.value()["value"];
            
            long long decodedValue = decodeBaseValue(value, stoi(base));
            
            x.push_back(index);
            y.push_back(decodedValue);
        }
    }

    cout << "Decoded points (x, y) for " << filename << ":\n";
    for (size_t i = 0; i < x.size(); ++i) {
        cout << "x[" << i + 1 << "] = " << x[i] << ", y[" << i + 1 << "] = " << y[i] << endl;
    }

    double constantTerm = lagrangeInterpolation(x, y, k, 0);
    
    cout << "\nConstant term (c) for " << filename << " is: " << constantTerm << endl;
}

int main() {
    processTestCase("testcase1.json");
    processTestCase("testcase2.json");
    return 0;
}
