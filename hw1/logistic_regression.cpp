/**
	This is an implimatation of Logistic regression.
	
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
		   
		   x.push_back(1);
		   while(iss >> number)
		      x.push_back(number);

		   inputMatrix.push_back(x);

		   x.clear();
		}
		openFile.close();
	}

	openFile.open(argv[2]);
	if(openFile.is_open())
	{
		while(!openFile.eof())
		{
			int i = 0;
			openFile >> i;
			classLables.push_back(i);
		}

		openFile.close();
	}

	itterations = atoi(argv[3]);

	for(int i=0;i<4;i++)
		initalWeights.push_back(1.0);
	
	for(int i=0;i<itterations;i++)
	{
		for(int c=0;c<inputMatrix.size();c++)
		{
			double wxVariable = 0.0;
			double hVariable = 0.0;

			// srand(time(NULL));
			// int randChoice = rand()% inputMatrix.size();
			// cout<<randChoice<<endl;
			wxVariable = ( initalWeights[0]*inputMatrix[c][0] + 
						   initalWeights[1]*inputMatrix[c][1] +
						   initalWeights[2]*inputMatrix[c][2] + 
						   initalWeights[3]*inputMatrix[c][3] );

			// cout<< randChoice <<endl;
			hVariable = 1.0 / (1.0 + exp(-wxVariable));

			//cout<<hVariable<<endl;

			double weight = 0.0;

			for(int v=0;v<4;v++)
			{
				initalWeights[v] = initalWeights[v] + alpha *
								   ((double)classLables[c] - hVariable) * 
								   hVariable * (1.0 - hVariable) * 
								   inputMatrix[c][v];
			}
		}
	}
	for(int i=0;i<4;i++)
		cout<<setprecision(16)<<initalWeights[i]<<endl;
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
