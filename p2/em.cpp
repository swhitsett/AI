// Sam Whitsett
// AI Project 2	

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <stdlib.h>

using namespace std;

string observationInput; //observation aka ththhht
double transitionsB[3];
double transitionsL[3];
double transitionsM[3];


int main (int argc,char* argv[])
{
	//./em observations.txt transition.txt sensory.txt original.txt k
	if(argc == 4)
	{
	   ifstream openFile;
	   openFile.open(argv[1]);
	   if(openFile.is_open())
	   {
			getline(openFile,observationInput);
	   }
	   openFile.close();

	   ifstream openFile2;
	   openFile2.open(argv[2]);
	   if(!openFile2.eof())
	   {
	   		openFile2 >> transitionsB[0];
	   }
	   openFile2.close();

	   ifstream openFile3;
	   openFile3.open(argv[3]);
	   if(openFile3.is_open())
	   {
	   		string line;
	   		getline(openFile3, line);

	   		cout<<line<<endl;
	   }
	}
	return 0;
}