//./ann train_input.txt train_output.txt test_input.txt test_output.txt structure.txt weights.txt k
//./ann train_input2.txt train_output2.txt test_input2.txt test_output2.txt structure2.txt weights2.txt 10000
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstring>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
using namespace std;

vector< vector<double> > out_encoding;
vector< vector<double> > train_input;
vector< vector<double> > test_input;
vector< vector<double> > weights;
vector< vector<double> > neural_network;
vector< vector<double> > error_network;
vector< int > train_output;
vector< int > test_output;
vector< int > structure_input;
int itterations;

void recordMatrix(ifstream&, vector< vector<double> >&);
void recordArray(ifstream&, vector< int >&);
void createEncoding(vector< vector<double> >&);
double inCalc(int,int);
void calculateError(int);
void run();
void printthis();

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
      
      printthis();
   } 
   return 0;
}
void run()
{
   vector<double> v;
   double new_weight;
   int struct_postion = 0;

   //neural_network.push_back(train_input.at(0));
   neural_network.push_back(train_input.at(0));

   for(int iter; iter<itterations; iter++)
   {
      for (int tRow=0; tRow<train_input.size()-1; tRow++)                  //tRow = move y in trainI
      {
         // neural_network.push_back(train_input.at(tRow));

         for(int i=1; i<structure_input.size()-1; i++)                       //i = move throught structure *
         {
            for(int j=0; j<neural_network.at(i-1).size(); j++)
            {
               v.push_back(1.0 / (1.0 + exp(-inCalc(i,j))));
            }
            neural_network.push_back(v);
            v.clear();
         }
         // cout<<neural_network[tRow][0] <<" "<<neural_network[tRow][1]<<endl;
         // if( tRow == 2)
         //    assert(false);
         //printthis();
         //calculateError(tRow);
         //poop();
         // for(int asdf=0;asdf<4; asdf++)
         //    cout<<"hi";
      }
   }
   // for(int asdf=0;asdf<4; asdf++)
   // {
   //    cout<<"hi";
   // }
}

void printthis()
{
   for(int a=0; a<neural_network.size()-1; a++)
   {
      for(int b=0; b<neural_network.at(a).size(); b++)
      {
         cout<<neural_network[a][b]<< " ";
      }
      cout<<"\n";
   }
}

double inCalc(int i, int j)
{
   int indexBuffer = 0;
   for(int iter = 0; iter < i-1; iter++)
   {
     indexBuffer += structure_input.at(iter);
   }

   double result = 0.0;// = neural_network[i-1][j];
   for(int x=0; x<structure_input[i -1]; x++)
   {
      result += neural_network[i-1][x] * weights[indexBuffer + x][j];
   }
   return result + 0.01;
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
