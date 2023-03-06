#include"dataPrep.h"

vector<vector<string>> readCSV(string fname){
    
 
	vector<vector<string>> content;
	vector<string> row;
	string line, word;
 
	fstream file(fname, ios::in);
	if(file.is_open())
	{
		while(getline(file, line))
		{
            
			row.clear();
            
			stringstream str(line);
            
			while(getline(str, word, ';')){

				row.push_back(word);
			}
			content.push_back(row);
		}
	}
	else
		cout<<"Could not open the file\n";
 
	
    content.erase(content.begin());
    
    return content;
}

int lenCsvVec(vector<vector<string>> csv){
    return csv[0].size();
}


void printCsvVecStr(vector<vector<string>> csv){
    for(int i=0;i<csv.size();i++)
	{
		for(int j=0;j<csv[i].size();j++)
		{
			cout<<csv[i][j]<<" ";
		}
		cout<<"\n";
	}
}

void printCsvVecDoub(vector<vector<double>> csv){
    for(int i=0;i<csv.size();i++)
	{
		for(int j=0;j<csv[i].size();j++)
		{
			cout<<csv[i][j]<<" ";
		}
		cout<<"\n";
	}
}

void splitCsvVec(vector<vector<string>> &vec1,vector<vector<string>> &vec2,int numColsToKeepInVec1){
    vector<string> temp;
    for(int i=0;i<vec1.size();i++){
        for(int j=numColsToKeepInVec1;j<vec1[i].size();){
            temp.push_back(vec1[i][j]);
            vec1[i].erase(vec1[i].begin()+j);
        }
        vec2.push_back(temp);
        temp.clear();
    }
};

vector<double> convertStrVecToDoubVec(const vector<string>& stringVector){
    vector<double> doubleVector(stringVector.size());
    transform(stringVector.begin(), stringVector.end(), doubleVector.begin(), [](const string& val)
                 {try{
						
                    	double temp = stod(val);
						
						return temp;

					}catch(...){
						cout<<val<<"###ERROR"<<endl;
						
					}
                    return stod(val);
                 });
    return doubleVector;
}

vector<vector<double>> convertTo2dDoubleVec(vector<vector<string>> csv){
    vector<vector<double>> csv2;

    for(int i=0;i<csv.size();i++){
        csv2.push_back(convertStrVecToDoubVec(csv[i]));
    }
    return csv2;
}

vector<vector<double>> calcExpectedOutputs(vector<vector<string>> inp){

    vector<vector<double>> temp; 
    for (int i = 0; i < inp.size(); i++)
    {
        if (inp[i][0] == "True"){
            vector<double> t = {1,-1};
            temp.push_back(t);
        }else if(inp[i][0] == "False"){
            vector<double> t = {-1,1};
            temp.push_back(t);
        }
    }
    return temp;
}