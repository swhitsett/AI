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
vector< vector<double> > transivity_Matrix;

string toBinary(int);
void printArray();
void probOfError(double);
bool foundIn(string,string);
int numberOfNeighbors(int);

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
	string directionArray[argc]; //may need to be i - 3 need to repari code below
	int directionValues[argc - 3];
	int x_component;
	int y_component;

	probOfError(atof(argv[2]));

	for(int i=3;i < argc;i++)
		directionArray[i-3] = argv[i];

	for(int i= 0; i < argc -3;i++)
	{
		int value = 0;
		string temp_word = directionArray[i];

		if(foundIn(temp_word,"N")) value += 8;
		if(foundIn(temp_word,"S")) value += 4;
		if(foundIn(temp_word,"W")) value += 2;
		if(foundIn(temp_word,"E")) value += 1;

		directionValues[i] = value;
	}

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

		   x_component = x.size();
		   y_component = vector_map.size();

		   x.clear();
		}
		openFile.close();
	}

	int matrix_length = x_component * y_component;
	//double transivity_Matrix[matrix_length][matrix_length];
	double test[vector_map.size()][vector_map.at(0).size()];

	for(int j = 0; j < matrix_length; j++)
		for(int i = 0; i < matrix_length;i++) // set to 0
			transivity_Matrix.at(j).push_back(0.0);

	for(int j = 0; j < vector_map.size(); j++)
	{
		for(int i = 0; i < vector_map.at(j).size();i++)
		{
			/**cout<<vector_map[j][i]<< " ";  damit its backwards**/

			int neighbor_num = numberOfNeighbors(vector_map[j][i]); 				// returns amount of neighbors int
			string binary_cell_value = toBinary(vector_map[j][i]);            // returns the string version of the binary value

			//cout<< binary_cell_value<<endl;
			if(binary_cell_value[0] == '0') transivity_Matrix[j][i] = 1.0/neighbor_num;
			if(binary_cell_value[1] == '0') transivity_Matrix[j][i] = 1.0/neighbor_num;
			if(binary_cell_value[2] == '0') transivity_Matrix[j][i-1] = 1.0/neighbor_num;
			if(binary_cell_value[3] == '0') transivity_Matrix[j][i+1] = 1.0/neighbor_num;
		}
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
	for(vector< vector<int> >::iterator yt = vector_map.begin(); yt != vector_map.end(); ++yt)
	{
		for(vector<int>::iterator xt = yt->begin(); xt != yt->end(); ++xt)
		{
			cout<< *xt<<" ";
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

bool foundIn(string word, string letter)
{
  	if (word.find(letter) != std::string::npos)
    	return true;
  	else
   	return false; 
}

int numberOfNeighbors(int direction_value)
{
	int diff_amount = 0;
	string binary_val = toBinary(direction_value);
	string binary_denomator = toBinary(15);   //all ones 1111


	for(int i=0;i<5;i++)
		if(binary_val[i] != binary_denomator[i]) 
			diff_amount++;


	return diff_amount;
}