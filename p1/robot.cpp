#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
	/**
		first command line input is the mapfile
		second is the %error
		third is the directions ie. NS EW
		EX...
		./robot Project1_input1.txt 0.1 SW NS NE W
		North, South, West, East
	**/
   vector< vector<int> > vector_map;
   int output;

	ifstream openFile;
	openFile.open(argv[1]);
	if(openFile.is_open())
	{
		while(openFile.is_open() && !openFile.eof())
		{
			openFile >> output; //if newline move to a diffrent vector.
			//cout<<output<<" ";
			for(int i=0;while(output != "\n"),i++)
			{
				vector<int> tempVector_colum;
				for(int y=0; y<)
			}
			vector_map.push_back(output);
			// for(vector<vector<int>>::iterator xt = vector_map.begin(); xt != vector_map.end(); ++xt)
			// {
			// 	for(vector<int>::iterator yt = xt->begin(); yt != it->end(); ++yt)
			// 	{
			// 		cout<<*yt;
			// 	}
			// }
		}
		openFile.close();

	} 
	return 0;
}