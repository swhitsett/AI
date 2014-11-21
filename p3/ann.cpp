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
      // for(int i=0; i<structure_input.size(); i++)
      //   cout<<structure_input[i]<<endl;
      run();
      
      printthis();
   } 
   return 0;
}
void run()
{
   neural_network.resize(structure_input.size());
    error_network.resize(structure_input.size());
    for(int i = 0; i < neural_network.size(); i++)
    {
        neural_network[i].resize(structure_input.at(i));
        error_network[i].resize(structure_input.at(i));
    }
   //neural_network.push_back(train_input.at(0));

   for(int iter=0; iter<itterations; iter++)
   {
      for (int tRow=0; tRow<train_input.size()-1; tRow++)                  //tRow = move y in trainI
      {
         neural_network[0] = train_input.at(tRow);// neural_network.push_back(train_input.at(tRow));

         for(int i=1; i<structure_input.size(); i++)                       //i = move throught structure *
         {
            for(int j=0; j<neural_network.at(i).size(); j++)
            {
               neural_network[i][j] =  (1.0 / (1.0 + exp(-inCalc(i,j))));// v.push_back(1.0 / (1.0 + exp(-inCalc(i,j))));
            }
         }
         for(int k = 0; k < neural_network.back().size(); k++)
          {
              double aj = neural_network.back()[k];
              double yj = out_encoding[train_output.at(tRow)][k];
              // error_network.back()[k] = aj*(1 - aj)*(yj - aj);
          }
      }
   }
}

void printthis()
{
   for(int a=0; a<neural_network.size(); a++)
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
     indexBuffer += structure_input.at(iter);

   double result = 0.0;// = neural_network[i-1][j];
   for(int x=0; x<structure_input[i -1]; x++)
   {
      result += neural_network[i-1][x] * weights[indexBuffer + x][j];
   }
   return result + 0.01;
}

void recordArray(ifstream& file, vector< int >& vec)
{
      string value;
      while(getline(file, value))
      {
          vec.push_back(atoi(value.c_str()));        
      }
      file.close();
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
