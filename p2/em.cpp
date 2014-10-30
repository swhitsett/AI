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
	if(argc == 6)
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
	   			BLMsensory[0][0] = -log2(line);
	   			BLMsensory[0][1] = -log2(1.0 - line);
	   		}
	   		else if (i == 1)
	   		{
	   			BLMsensory[1][0] = -log2(line);
	   			BLMsensory[1][1] = -log2(1.0 -line);
	   		}
	   		else if (i == 2)
	   		{
	   			BLMsensory[2][0] = -log2(line);
	   			BLMsensory[2][1] = -log2(1.0 - line);
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
	   int backTraceTable[3][observationInput.size()+1];
	   for(int i = 0; i < 3; i++)
	   	ViterbiTable[i][0] = -log2(0.333333333); 							// assuming that the states are 3 aka 1/3
	   for(int i = 0; i < 3; i++)													//backtrace Table Initlization.
	   	backTraceTable[i][0] = 0;

	   int rowWalk = observationInput.size()+1;
		for(int c = 1; c < rowWalk; c++) 										// this is 1 to avoid the spot where x is inputed
		{																					//for verbiti table colum
			double min = 0.0;
			for(int r = 0; r < 3; r++)												//for verbiti tabel row
			{
				int forBackTrace = 0;
				bool initalize = false;
				for(int x = 0; x < 3; x++) 										//for transition table colum
				{
					double calc = ViterbiTable[x][c-1] + BLMtransition[r][x];
					if(!initalize)
					{
						initalize = true;
						min = calc;
						backTraceTable[r][c] = x;
					}

					if(calc < min && initalize)
					{
						min = calc;
						backTraceTable[r][c] = x;
					}
				}

				char observed[observationInput.size()];
				for(int a=0;a<observationInput.size();a++)
					observed[a] = observationInput[a]; 

				if(observed[c-1] == 'H') 											// c-1 will set to the start ofthe input string
					min = min + BLMsensory[r][0];
				else
					min = min + BLMsensory[r][1];

				ViterbiTable[r][c] = min;
			}
			// cout<<backTrace1<<endl;

		}
		for(int i=0; i<observationInput.size()+1;i++)
			cout<<backTraceTable[0][i]<<" ";
		cout<<"\n";
		for(int i=0; i<observationInput.size()+1;i++)
			cout<<backTraceTable[1][i]<<" ";
		cout<<"\n";
		for(int i=0; i<observationInput.size()+1;i++)
			cout<<backTraceTable[2][i]<<" ";
		cout<<"\n";
// ------------------------------------creating backtrack array----------------------------------------
		int backTrace2[observationInput.size()];
		int minFinalValue = 0;
		double curVal = ViterbiTable[0][observationInput.size()];
		for(int i=0; i<3; i++)
		{
			if( ViterbiTable[i][observationInput.size()] < curVal)
				minFinalValue = i;
		}

		backTrace2[observationInput.size()] = minFinalValue;

		for(int i=observationInput.size(); i > 0; i--)
		{
			backTrace2[i-1] = backTraceTable[minFinalValue][i]; 
			minFinalValue = backTraceTable[minFinalValue][i];
		}
		// for(int i=0; i<observationInput.size()+1;i++)
		// 	cout<<backTrace2[i]<<" ";
		// cout<<"\n";
//---------------------------original table creation above-----------------plus backtrack table-----------
		double amountInString = 0.0;
		double relationCount = 0.0;

		double newTable[3][3];
		int curLetter[3] = {0, 1, 2};
		// char observed[originalInput.size()];
		// for(int a=0;a<originalInput.size();a++)
		// 	observed[a] = originalInput[a]; 

		int L = 0;  //B|L
		for(int j=0; j<3; j++) // table row
		{
			for(int l=0; l<3; l++) // table colum
			{
				for(int i=1;i<originalInput.size()+1;i++) 				// observation itteration
				{
					if(backTrace2[i-1] == curLetter[l])   // changed the curLetter[j] to curLetter[l] to get it to work.
					{
						amountInString++;
					}
					if(backTrace2[i] == curLetter[j] && backTrace2[i-1] == curLetter[l])
					{
						relationCount++;
					}
				}
				cout<<relationCount<<" + 1/ "<< amountInString<<" + 3*1"<<endl;;
				//cout<<(amountInString + relationCount*1)<<endl;
				newTable[j][l] = (relationCount + 1)/(amountInString + 3*1);
				amountInString = 0.0;
				relationCount = 0.0;
			}


		}	
		for(int i=0; i<3;i++)
			cout<<newTable[0][i]<<" ";
		cout<<"\n";
		for(int i=0; i<3;i++)
			cout<<newTable[1][i]<<" ";
		cout<<"\n";
		for(int i=0; i<3;i++)
			cout<<newTable[2][i]<<" ";
		cout<<"\n";

	}
	return 0;
}