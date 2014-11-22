//./ann train_input.txt train_output.txt test_input.txt test_output.txt structure.txt weights.txt k
//./ann train_input2.txt train_output2.txt test_input2.txt test_output2.txt structure2.txt weights2.txt 10000
#include "ann.h"
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

void ann::run()
{
    initalize();
   //neural_network.push_back(train_input.at(0));

   for(int iter=0; iter<itterations; iter++)
   {
      for (int tRow=0; tRow<train_input.size()-1; tRow++)                  //tRow = move y in trainI
      {
        neural_network[0] = train_input.at(tRow);// neural_network.push_back(train_input.at(tRow));

        for(int i=1; i<structure_input.size(); i++)                       //i = move throught structure *
        {
          for(int a=0; a<neural_network.at(i).size(); a++)
          {
             neural_network[i][a] =  (1.0 / (1.0 + exp(-inCalc(i,a))));// v.push_back(1.0 / (1.0 + exp(-inCalc(i,a))));
          }
        }

        calcError(tRow);

        recalcError();
        
        calcDummy();

        calcWeight();
      }
    }
}
void ann::recalcError()
{
  for(int a = neural_network.size() - 2; a >= 0; a--)
  {
    for(int k = 0; k < neural_network[a].size(); k++)
    {
      double ai = neural_network[a][k];
      double sum = 0;
      double prvError = 0;
      double weig = 0;

      for(int l = 0; l < structure_input.at(a+1); l++)
      {
        int offset = 0;
        for(int i = 0; i < a; i++)
          offset += structure_input.at(i);

        prvError = error_network[a+1][l];
        weig = weights.at(offset + k)[l]; 
        sum += prvError*weig;
      }
      error_network[a][k] = ai*(1-ai)*sum;
    }
  }
}
void ann::calcWeight()
{
  for(int a = 0; a < weights.size(); a++)
  {
    for(int k = 0; k < weights.at(a).size(); k++)
    {
        int layer = FromWeightRow(a);
        double prev = weights.at(a)[k];
        double dj = error_network[layer][k];
        double ai = neural_network[FromWeightRow(a)][k];
        weights.at(a)[k] = prev + (0.01 * ai * dj);
    }
  }
}
void ann::calcError(int r)
{
  for(int k = 0; k < neural_network.back().size(); k++)
  {
    double aj = neural_network.back()[k];
    double yj = out_encoding[train_output.at(r)][k];
    error_network.back()[k] = aj*(1 - aj)*(yj - aj);
  }
}
void ann::calcDummy()
{
  for(int a = 0; a < open_table.size(); a++)
    for(int k = 0; k < open_table[a].size(); k++)
      open_table[a][k] = open_table[a][k] + (0.01 * error_network[a][k]);
}
void ann::initalize()
{
  neural_network.resize(structure_input.size());
  error_network.resize(structure_input.size());
  for(int i = 0; i < neural_network.size(); i++)
  {
      neural_network[i].resize(structure_input.at(i));
      error_network[i].resize(structure_input.at(i));
  }
  for(int i = 0; i < neural_network.size(); i++)
  {
      vector<double> row;
      for(int a = 0; a < neural_network[i].size(); a++)
      {
          row.push_back(0.0);
      }
      open_table.push_back(row);
  }
}
int ann::FromWeightRow(int pRow)
{
    int sum = 0;
    int index = 0;
    for(; pRow < sum; index++, sum += structure_input.at(index));
    return index;
}
void ann::printthis()
{
  int lastHiddenLayer = structure_input.size() - 2;
  int offset = 0;

  for(int i = 0; i < lastHiddenLayer; i++)
    offset += structure_input.at(i);

  for(int i = 0; i < structure_input.at(lastHiddenLayer + 1); i++)
  {
      printf("%.16f\n", weights.at(offset)[i]);
  }
  printf("\n%f%%\n", (total_correct / test_output.size())*100);

}

double ann::inCalc(int i, int a)
{
   int indexBuffer = 0;
   for(int iter = 0; iter < i-1; iter++)
     indexBuffer += structure_input.at(iter);

   double result = 0.0;// = neural_network[i-1][a];
   for(int x=0; x<structure_input[i -1]; x++)
   {
      result += neural_network[i-1][x] * weights[indexBuffer + x][a];
   }
   return result + 0.01;
}

void ann::recordArray(ifstream& file, vector< int >& vec)
{
      string value;
      while(getline(file, value))
      {
          vec.push_back(atoi(value.c_str()));        
      }
      file.close();
}

void ann::recordMatrix(ifstream& file, vector< vector<double> >& vec)
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

void ann::createEncoding()
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
      out_encoding.push_back(v);
   }
}
