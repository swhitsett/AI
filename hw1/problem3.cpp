/**
	This is a program that  finds the nearest neighbors using 
	Euclidean distance.

	The hanhattan distance (qArray) is hard codded. change if neccary
**/

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
		   
		   while(iss >> number)
		      x.push_back(number);

		   inputMatrix.push_back(x);

		   x.clear();
		}
		openFile.close();
	}

	int qArray[3] ={4,3,2} ;
	for(int y=0;y<inputMatrix.size()-1;y++)
	{
		double tmp = 0.0;
		for(int i=0;i<3;i++)
		{
			tmp += pow(qArray[i] - inputMatrix[y][i], 2.0);
		}
		inputMatrix[y][4] = sqrt(tmp);
		cout<<inputMatrix[y][4]<<endl;
	}
	
	return 0;
}
