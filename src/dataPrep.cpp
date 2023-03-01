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
            
			while(getline(str, word, ';'))

				row.push_back(word);

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


void printCsvVec(vector<vector<string>> csv){
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
    for(int i=0;i<vec1.size();i++){
        
    }
};