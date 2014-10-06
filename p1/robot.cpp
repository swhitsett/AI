#include <iostream>
#include <fstream> //to read in a file

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
}