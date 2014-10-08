#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdlib.h> // for atof
#include <math.h> // for pow
#include <bitset> // for binary conversion

using namespace std;

double percent_error;
double errorArray[5];
vector< vector<int> > vector_map;

string toBinary(int);
void printArray();
void probOfError(double);

int main(int argc, char *argv[])
{
	/**
		first command line input is the mapfile
		second is the %error
		third is the directions ie. NS EW
		EX...
		./robot Project1_input1.txt 0.1 SW NS NE W
		North, South, West, East

		e = NE or SW
		epslon = % error 0,1
		d = number of bits that differ from e (ie 1010 to 1110 diff is 1)
			-- coresponding value?? the one before?

	**/

	probOfError(atof(argv[2]));
	string directionArray[argc];

	for(int i=3;i < argc -1;i++)
		directionArray[i-3] = argv[i];

   ifstream openFile;
   openFile.open(argv[1]);
   if(openFile.is_open())
   {
   	   vector<int> x;
   	   string line_of_file;

	   while(openFile.is_open() && !openFile.eof())
	   {
		   getline(openFile,line_of_file);

		   istringstream iss(line_of_file);
		   int number;

		   while(iss >> number)
		      x.push_back(number);

		   vector_map.push_back(x);
		   x.clear();
		}
		openFile.close();
	}
	return 0;
}

//Functions below..............
//

string toBinary(int val)
{
	bitset<4> x(val);
	return x.to_string();
}

void printArray()
{
	for(vector< vector<int> >::iterator xt = vector_map.begin(); xt != vector_map.end(); ++xt)
	{
		for(vector<int>::iterator yt = xt->begin(); yt != xt->end(); ++yt)
		{
			cout<< *yt<<" ";
		}
		cout<<"\n";
	}
}

void probOfError(double error)
{
	double result;

	for(int i=0;i<5;i++)
	{
		errorArray[i] = pow(error, i)*pow((1 - error),(4-i));
		//cout<<errorArray[i]<<endl;
	}
}
