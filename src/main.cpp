#include "network.h"
#include "dataPrep.h"

//Main Function
int main() {
    
    // Start measuring time
    auto begin = std::chrono::high_resolution_clock::now();

    // Setting random seed as current time
    srand(static_cast<unsigned>(time(0)));

    vector<vector<string>> y = readCSV("Data/fake_bills_normalized.csv");
    vector<vector<string>> x_temp;
    splitCsvVec(y, x_temp, 1);

    vector<vector<double>> x = convertTo2dDoubleVec(x_temp);
    vector<vector<double>> expected_y = calcExpectedOutputs(y);

    vector<dataPoint> data;

    for (int i = 0; i < x.size(); i++) {
        dataPoint d(x.at(i), expected_y.at(i));
        data.push_back(d);
    }

    Neural_Net h({6, 10, 10, 10, 2});

    // Call LearnCalc once to handle epochs and batches
    h.LearnCalc(data, 0.01, 0.1, 0.9,10000,false);

    // Stop measuring time and calculate the elapsed time
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

    cout << "TIME:: " << elapsed.count() * 1e-9;

    return 0;
}
