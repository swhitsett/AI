#include <iostream>
<<<<<<< HEAD
#include <fstream>
#include <vector>
=======
#include <fstream> //to read in a file
>>>>>>> 7ba39f017a16a2b675ac5d496e3539f6209ed244

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
<<<<<<< HEAD
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
=======
	int map_file[][];//string line;
    ifstream inputFile (argv[1]);
    if (inputFile.is_open())
    {
       while ( getline (inputFile,line) )
       {
          cout << line << '\n';
       }
       inputFile.close();
    }

  else cout << "Unable to open file";
	int map_array [sizeX][sizeY];

	int** ary = new int*[sizeX];
	for(int i = 0; i < sizeX; ++i)
	    ary[i] = new int[sizeY];
		return 0;
>>>>>>> 7ba39f017a16a2b675ac5d496e3539f6209ed244
}