//./ann train_input.txt train_output.txt test_input.txt test_output.txt structure.txt weights.txt k

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

vector< vector<double> > train_matrix;

int main (int argc, char *argv[])
{
   if (argc == 7)
   {
   		ifstream openFile
   		openFile.open(argv[1]);
   		if(openFile.is_open())
   		{
   			vector<double> x;
   			string current_line;

   			while(!openFIle.eof())
   			{
   				getline(openFile, current_line);

   				double number;
   				istringstream iss(current_line);

   				while(iss >> number)
   					x.push_back(number);

   				train_matrix.push_back(x);

   				// x_component = x.size();  //for getting the size of the array prob not needed.
   				// y_component = train_matrix.size();
   				x.clear();
   			}
   			openFile.close();
   		}
   } 
   return 0;
}

