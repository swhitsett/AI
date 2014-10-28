// Sam Whitsett
// AI Project 2	

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <vector>
#include <math.h>

using namespace std;

string observationInput; //observation aka ththhht
string originalInput;
double BLMarray[3][3];
double BLMsensory[3][2];


int main (int argc,char* argv[])
{
	//./em observations.txt transition.txt sensory.txt original.txt k
	if(argc == 4)
	{
		//observations
	   ifstream openFile;
	   openFile.open(argv[1]);
	   if(openFile.is_open())
	   {
			getline(openFile,observationInput);
	   }
	   openFile.close();

	   // Transitions
	   openFile.open(argv[2]);
	   if(openFile.is_open())
	   {
	   	int i = 0;

		   while(!openFile.eof())
		   {
		   	double num;
		   	openFile >> num;

			   if(i < 3)
			   	BLMarray[0][i] = num; 
			   if(i < 6)
			   	BLMarray[1][i-3] = num;
			   if(i < 9)
			   	BLMarray[2][i-6] = num;
			   i++;
			}
			openFile.close();
		}

		//sensory
	   openFile.open(argv[3]);
	   if(openFile.is_open())
	   {
	   	int i = 0;
	   	while(!openFile.eof())
	   	{
	   		double line;
	   		openFile >> line;

	   		if(i == 0)
	   		{
	   			BLMsensory[0][0] = line;
	   			BLMsensory[0][1] = 1.0 -line;
	   		}
	   		else if (i == 1)
	   		{
	   			BLMsensory[1][0] = line;
	   			BLMsensory[1][1] = 1.0 -line;
	   		}
	   		else if (i == 3)
	   		{
	   			BLMsensory[2][0] = line;
	   			BLMsensory[2][1] = 1.0 -line;
	   		}
	   		i++;
	   		//cout<<line<<endl;
	   	}
	   	openFile.close();
	   }

	   //original
	   openFile.open(argv[4]);
	   if(openFile.is_open())
	   {
			getline(openFile,originalInput);
	   }
	   openFile.close();
//--------------------------- read in functions above-------------------------
	   double ViterbiTable[3][observationInput.size()];
	   for(int i = 0; i < 3; i++)
	   	ViterbiTable[i][0] = -log2(0.333333);

	   cout<<ViterbiTable[0][0];

	}
	return 0;
}