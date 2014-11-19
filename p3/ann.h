class Ann
{
	public:
		void run();
		void recordMatrix(ifstream&, vector< vector<double> >&);
		void recordArray(ifstream&, vector< int >&);
		void createEncoding(vector< vector<double> >&);
	private:
		vector< vector<double> > out_encoding;
		vector< vector<double> > train_input;
		vector< vector<double> > test_input;
		vector< vector<double> > weights;
		vector< int > train_output;
		vector< int > test_output;
		vector< int > structure_input;
		int itterations;	
};