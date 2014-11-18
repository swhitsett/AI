//./ann train_input.txt train_output.txt test_input.txt test_output.txt structure.txt weights.txt k

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

vector< vector<double> > train_input;
vector< vector<double> > test_input;
vector< vector<double> > weights;
vector< int > train_output;
vector< int > test_output;
vector< int > structure_input;
int itterations;

void recordMatrix(string, vector< vector<double> >&);
void recordArray(string, vector< int >&);

int main (int argc, char *argv[])
{

   if (argc == 7)
   {

		ifstream openFile;
      //train input
		openFile.open(argv[1]);
		if(openFile.is_open())
		{
			vector<double> y;
			string current_line;

			while(!openFile.eof())
			{
				getline(openFile, current_line);

				double x;
				istringstream iss(current_line);

				while(iss >> x)
					y.push_back(x);

				train_input.push_back(y);

				// x_component = x.size();  //for getting the size of the array prob not needed.
				// y_component = train_input.size();
				y.clear();
			}
			openFile.close();
		}
      //train output
      openFile.open(argv[2]);
      if(openFile.is_open())
      {
         while(!openFile.eof())
         {
            int number;
            openFile >> number;
            train_output.push_back(number);
         }
         openFile.close();
      }
      //test input
      openFile.open(argv[3]);
      if(openFile.is_open())
      {
         vector<double> y;
         string current_line;

         while(!openFile.eof())
         {
            getline(openFile, current_line);

            double x;
            istringstream iss(current_line);

            while(iss >> x)
               y.push_back(x);

            test_input.push_back(y);

            // x_component = x.size();  //for getting the size of the array prob not needed.
            // y_component = train_input.size();
            y.clear();
         }
         openFile.close();
      }
      //test output
      openFile.open(argv[4]);
      if(openFile.is_open())
      {
         while(!openFile.eof())
         {
            int number;
            openFile >> number;
            test_output.push_back(number);
         }
         openFile.close();
      }
      // structure
      openFile.open(argv[5]);
      if(openFile.is_open())
      {
         while(!openFile.eof())
         {
            int number;
            openFile >> number;
            structure_input.push_back(number);
         }
         openFile.close();
      }
      // weights
      openFile.open(argv[6]);
      if(openFile.is_open())
      {
         vector<double> y;
         string current_line;

         while(!openFile.eof())
         {
            getline(openFile, current_line);

            double x;
            istringstream iss(current_line);

            while(iss >> x)
               y.push_back(x);

            weights.push_back(y);

            // x_component = x.size();  //for getting the size of the array prob not needed.
            // y_component = train_input.size();
            y.clear();
         }
         openFile.close();
      }
      // k
      openFile.open(argv[7]);
      if(openFile.is_open())
         cin >> itterations;
   } 
   return 0;
}
