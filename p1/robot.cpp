#include <iostream>
#include <fstream>
#include <vector>
#include <string>

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
   vector< vector<string> > vector_map;
   string output;

	ifstream openFile;
	openFile.open(argv[1]);
	if(openFile.is_open())
	{
		vector<string> x;
		while(openFile.is_open() && !openFile.eof())
		{
			openFile >> output;
			if(output == "\n")
			{
				vector_map.push_back(x);
				x.clear();
			}
			else
			{
				x.push_back(output);
			}
		}
		openFile.close();
	}
	//openFile >> output; //if newline move to a diffrent vector.
			//cout<<output<<" ";
			for(vector< vector<string> >::iterator xt = vector_map.begin(); xt != vector_map.end(); ++xt)
			{
				for(vector<string>::iterator yt = xt->begin(); yt != xt->end(); ++yt)
				{
					cout<<*yt<<" ";
				}
			} 
	return 0;
}