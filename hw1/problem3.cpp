#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <time.h>
#include <iomanip>

using namespace std;
vector< vector<double> > inputMatrix;
vector<int> classLables;
vector<double> initalWeights;
double alpha = 0.01;
int itterations = 0;

int main(int argc, char* argv[])
{
	ifstream openFile;
	openFile.open(argv[1]);
	if(openFile.is_open())
	{
		   vector<double> x;
		   string line;

	   while(!openFile.eof())
	   {
		   getline(openFile,line);

		   istringstream iss(line);
		   double number;
		   
		   //x.push_back(1);
		   while(iss >> number)
		      x.push_back(number);

		   inputMatrix.push_back(x);

		   x.clear();
		}
		openFile.close();
	}

	// openFile.open(argv[2]);
	// if(openFile.is_open())
	// {
	// 	while(!openFile.eof())
	// 	{
	// 		int i = 0;
	// 		openFile >> i;
	// 		classLables.push_back(i);
	// 	}

	// 	openFile.close();
	// }

	int mrArray[3] ={3,2,3} ;
	for(int y=0;y<inputMatrix.size();y++)
	{
		double tmp = 0.0;
		for(int i=0;i<3;i++)
		{
			tmp += pow(mrArray[i] - inputMatrix[y][i], 2.0);
		}
		inputMatrix[y][4] = sqrt(tmp);
	}

	
	
	// for(int i=0;i<4;i++)
	// 	cout<<setprecision(16)<<inputMatrix[i][4]<<endl;
	//cout<<inputMatrix[0][0]<<endl;
	// for(vector< vector<int> >::iterator yt = inputMatrix.begin(); yt != inputMatrix.end(); ++yt)
	// {
	// 	for(vector<int>::iterator xt = yt->begin(); xt != yt->end(); ++xt)
	// 	{
	// 		cout<< *xt<<" ";
	// 	}
	// 	cout<<"\n";
	// }
	

	return 0;
}
