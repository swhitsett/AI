//./ann train_input.txt train_output.txt test_input.txt test_output.txt structure.txt weights.txt k

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstring>
#include <stdlib.h>
using namespace std;

vector< vector<double> > out_encoding;
vector< vector<double> > train_input;
vector< vector<double> > test_input;
vector< vector<double> > weights;
vector< vector<double> > neural_network;
vector< int > train_output;
vector< int > test_output;
vector< int > structure_input;
int itterations;

void recordMatrix(ifstream&, vector< vector<double> >&);
void recordArray(ifstream&, vector< int >&);
void createEncoding(vector< vector<double> >&);
void run();

int main (int argc, char *argv[])
{
   if (argc == 8)
   {

		ifstream openFile;
      //train input
		openFile.open(argv[1]);
      recordMatrix(openFile,train_input);
      //train output
      openFile.open(argv[2]);
      recordArray(openFile, train_output);
      //test input
      openFile.open(argv[3]);
      recordMatrix(openFile, test_input);
      //test output
      openFile.open(argv[4]);
      recordArray(openFile, test_output);
      // structure
      openFile.open(argv[5]);
      recordArray(openFile, structure_input);
      // weights
      openFile.open(argv[6]);
      recordMatrix(openFile,weights);
      //k aka itterations
      itterations = atoi(argv[7]);
      //create encoding
      createEncoding(out_encoding);
      //run back propragation
      run();
   } 
   return 0;
}
void run()
{
   double new_weight;
   int struct_postion = 0;
   for(int itter; itter<itterations; itter++)
   {
      for (int tRow=0; tRow<train_input.size()-1; tRow++)                  //tRow = move y in trainI
      {
         for(int i=1; i<structure_input.size(); i++)                       //i = move throught structure *
         {
            for(int j=0; j<structure_input[i]; j++)
            {
               neural_network[i][j] = asdfasfd
            }
            // for(int j=0; j<structure_input[i]; j++)                        //j = move through nodes in hidden layer top>down
            // {
            //    for(int k=0; k<train_input.at(1).size(); k++)               //k = move x in trainI
            //    {
            //       for(int l=struct_postion; l<structure_input[i-1]; l++)   //l = move y in weights
            //       {
            //          for(int m=0; m<weights.at(l).size(); m++)             //m = move x in weights
            //          {
            //             new_weight = new_weight + (train_input[tRow][k] * weights[l][m]);
            //             // calculated_layer_values.at(i-1).push_back( new_weight );
            //          }
            //          calculated_layer_values.push_back( 0.01 + new_weight );
            //       }
            //       struct_postion = struct_postion + structure_input[i-1];
            //    }
            // }
         }
      }
   }
   // for(int i=0; i<train_input.size()-1; i++)         //i = train input y
   // {
   //    for(int j=0;j<structure[x];j++)  //j = train input x
   //    {
   //       for(int k=0;k<structure.at(j).size();k++)   //k = weights itterator
   //       {

   //          calculated_layer_values[point_of_structure][layer] = calculated_layer_values[][] + (train_input[i][j] * weights[j][k])
   //       }
   //    }
   // }
}
void recordArray(ifstream& file, vector< int >& vec)
{
   if(file.is_open())
   {
      while(!file.eof())
      {
         int number;
         file >> number;
         vec.push_back(number);
      }
      file.close();
   }
}

void recordMatrix(ifstream& file, vector< vector<double> >& vec)
{
   if(file.is_open())
   {
      vector<double> y;
      string current_line;

      while(!file.eof())
      {
         getline(file, current_line);

         double x;
         istringstream iss(current_line);

         while(iss >> x)
            y.push_back(x);

         vec.push_back(y);
         y.clear();
      }
      file.close();
   }
}

void createEncoding(vector< vector< double> >& vec)
{
   for(int y=0; y<10; y++)
   {
      vector<double> v;
      for(int x=0;x<10; x++)
      {
         double num;
         if(y == x)
            num = 0.1;
         else
            num = 0.9;

         v.push_back(num);
      }
      vec.push_back(v);
   }
}