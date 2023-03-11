#include "network.h"
#include "dataPrep.h"


//Main Function
int main() {
    
    // Start measuring time
    auto begin = std::chrono::high_resolution_clock::now();

    // Setting random seed as current time
    srand (static_cast<unsigned> (time(0)));

    
    vector<vector<string>> y = readCSV("Data/fake_bills.csv");
    vector<vector<string>> x_temp;
    splitCsvVec(y,x_temp,1);


    vector<vector<double>> x = convertTo2dDoubleVec(x_temp);
    
    vector<vector<double>> expected_y = calcExpectedOutputs(y);

    vector<int> Size = {6,10,10,2};
    
    vector<dataPoint> data;

    for (int i = 0; i < x.size(); i++)
    {
        dataPoint d(x.at(i),expected_y.at(i));
        data.push_back(d);
    }
    
        
    Neural_Net h(Size);

    for (int i = 0; i < 100; i++)
    {
        h.LearnCalc(data,0.05,0.1,0.9);
        
        cout << TotalLoss(x,expected_y,h) <<endl;
    }
    
    
    
    //h = getBestNnRandom(Size,x,expected_y,10);
    //h.loadNNfromFile("bestV1-1.42.txt");

    //getBestNnGradientDescent(&h,x,expected_y,5,0.14);
    
    //cout << MultiTotalLoss(x,expected_y,h);

    // Stop measuring time and calculate the elapsed time
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

    cout <<"TIME:: "<<elapsed.count() * 1e-9;
}