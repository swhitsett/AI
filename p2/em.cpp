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
double BLMtransition[3][3];
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
			   	BLMtransition[0][i] = -log2(num); 
			   if(i < 6)
			   	BLMtransition[1][i-3] = -log2(num);
			   if(i < 9)
			   	BLMtransition[2][i-6] = -log2(num);
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
	   double ViterbiTable[3][observationInput.size()+1];
	   for(int i = 0; i < 3; i++)
	   	ViterbiTable[i][0] = -log2(0.333333); // assuming that the states are 3 aka 1/3

	   int rowWalk = observationInput.size();
		for(int c = 1; c < rowWalk; c++) // this is 1 to avoid the spot where x is inputed
		{											//for verbiti table colum
			double min = 0.0;
			for(int r = 0; r < 3; r++)		//for verbiti tabel row
			{
				bool initalize = false;
				for(int x = 0; x < 3; x++) //for transition table colum
				{
					double calc = ViterbiTable[r][c-1] + BLMtransition[r][x];
					if(!initalize)
					{
						initalize = true;
						min = calc;
					}

					if(calc < min && initalize)
						min = calc;
				}

				initalize = false;

				// if(observed[c-1] == 'H') // c-1 will set to the start ofthe input string
				// 	min = min * BLMsensory[r][0];
				// else
				// 	min = min * BLMsensory[r][1];

				// ViterbiTable[r][c] = min;
			}
			//for observationInput[c] == h
			// min * observationInput[c];
		}

	}
	return 0;
}