/*******************************************************************************
 * Name          : shortestpath.cpp
 * Author        : Alex Johnson && Andrew Johnson
 * Pledge        : I pledge my honor that I have abided by the Stevens Honor System.
 * Date          : 12/5/19
 * Description   : Finds the shortest path in a weighted graph.
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

int vertices = 0;
const long INF = 10147483648;
long** matrix;
long** paths;
long**  intermediate;

int len(long num) {
   	int count = 0;
   	while(num != 0) {
   		num = num/10;
   		count++;
   	}
   	return count;
}

void addValue(char i, char j, int weight) {
	matrix[i-'A'][j-'A'] = weight;
}

/**
* Displays the matrix on the screen formatted as a table.
*/
void display_table(long** const matrix, const string &label, const bool use_letters = false) {
	 cout << label << endl;
	 long max_val = 0;
	 for (int i = 0; i < vertices; i++) {
		 for (int j = 0; j < vertices; j++) {
		 	long cell = matrix[i][j];
		 	if (cell < INF && cell > max_val) {
		 		max_val = matrix[i][j];
			}
		 }
	 }

	 int max_cell_width = use_letters ? len(max_val) :
	 len(max(static_cast<long>(vertices), max_val));
	 cout << ' ';
	 for (int j = 0; j < vertices; j++) {
	 	if(label.compare("Intermediate vertices:") == 0 && vertices == 1)
	 		cout << setw(max_cell_width + 1) << " " << static_cast<char>(j + 'A');
	 	else cout << setw(max_cell_width + 1) << static_cast<char>(j + 'A');
	 }
	 cout << endl;

	 for (int i = 0; i < vertices; i++) {
	 	cout << static_cast<char>(i + 'A');
		 for (int j = 0; j < vertices; j++) {
		 	cout << " " << setw(max_cell_width);

			 if (matrix[i][j] == INF) {
			 	cout << "-";
			 } else if (use_letters) {
			 	cout << static_cast<char>(matrix[i][j] + 'A');
			 } else {
			 	cout << matrix[i][j];
			 }
	 	}
		cout << endl;
	 }
	 cout << endl;
}

int val(string s) {
	int result = 0;
	for(char c: s) {
		result *= 10;
		if(int(c) < 48 || int(c) > 57) {
			return -1;
		} else {
			result += (int(c)-48);
		}
	}
	return result;
}

bool processArgs(vector<string> seperated, int linenumber) {
	if(linenumber == 1) {

		// Test values to see if valid
		try {
			vertices = stoi(seperated[0]);
			if(vertices == 0) {
				cout << "Error: Invalid number of vertices '"<< seperated[0] <<"' on line 1.";
				return 0;
			}
		} catch(exception& e) {
			cout << "Error: Invalid number of vertices '"<< seperated[0] <<"' on line 1.";
			return 0;
		}

		// Tests have passed. Fill Matrix
		matrix = new long*[vertices];
		for(int i = 0; i < vertices; i++) {
			matrix[i] = new long[vertices];
			fill_n(matrix[i], vertices, INF);
		}

	} else {

		// Test values to see if valid

		if(seperated.size() != 3 && linenumber != 1) {
			cout << "Error: Invalid edge data '"<< seperated[0] << " " << seperated[1] <<"' on line " << linenumber << "." << endl;
			return 0;
		}

		char first = seperated[0][0];
		char second = seperated[1][0];
		int weight = val(seperated[2]);

		if(((first < 'A' || first > 'A' + vertices) || seperated[0].length() > 1) && linenumber != 1) {
			cout << "Error: Starting vertex '" << seperated[0] << "' on line " << linenumber << " is not among valid values A-" << static_cast<char>('A' + vertices - 1) << "." << endl;
			return 0;
		}

		if(((second < 'A' || second > 'A' + vertices) || seperated[1].length() > 1) && linenumber != 1) {
			cout << "Error: Ending vertex '" << seperated[1] << "' on line " << linenumber << " is not among valid values A-" << static_cast<char>('A' + vertices - 1) << "." << endl;
			return 0;
		}

		if(weight < 1) {
			cout << "Error: Invalid edge weight '" << seperated[2] << "' on line " << linenumber << "." << endl;
			return 0;
		}


		// Tests have passed, Add value to matrix
		addValue(first,second,weight);

	} 

	return 1;

}

void InitializeMatrix() {

	//Initialize paths with original matrix
	paths = new long*[vertices];
	for(int i = 0; i < vertices; i++) {
		paths[i] = new long[vertices];
		for(int j = 0; j < vertices; j++) {
			paths[i][j] = matrix[i][j];
		}
	}

	//Initialize intermediate with INF
	intermediate = new long*[vertices];
	for(int i = 0; i < vertices; i++) {
		intermediate[i] = new long[vertices];
		fill_n(intermediate[i], vertices, INF);
	}

}

void floyds(long** matrix) {
	for(int k = 0; k < vertices; k++) {
		for(int i = 0; i < vertices; i++) {
			for(int j = 0; j < vertices; j++) {
				if(paths[i][k] != INF && paths[k][j] != INF && paths[i][j] > (paths[i][k] + paths[k][j])) {
					paths[i][j] = paths[i][k] + paths[k][j];
					intermediate[i][j] = k;
				}
				if(i == j) {
					paths[i][j] = 0;
					intermediate[i][j] = INF;
				}
			}
		}
	}
}

vector<char> backtrack_helper(int i, int j) {
	vector<char> result;
	char c1, c2;

	//Base case
	if(intermediate[i][j] == INF) {
		c1 = 'A' + i;
		c2 = 'A' + j;
		result.push_back(c2);
		if(c1 != c2) {
			result.push_back(c1);
		}
		return result;
	}

	result = backtrack_helper(i, intermediate[i][j]);
	vector<char> temp = backtrack_helper(intermediate[i][j], j);
	temp.insert(temp.end(), result.begin()+1, result.end());

	return temp;

}

void backtrack() {
	for(int i = 0; i < vertices; i++) {
		for(int j = 0; j < vertices; j++) {
			if(paths[i][j] == INF)
			cout << static_cast<char>('A' + i) << " -> " << static_cast<char>('A' + j) << ", distance: infinity, path: ";
			else
			cout << static_cast<char>('A' + i) << " -> " << static_cast<char>('A' + j) << ", distance: " << paths[i][j] << ", path: ";

			vector<char> path = backtrack_helper(i,j);
			reverse(path.begin(), path.end());

			if(paths[i][j] < INF) {
				cout << path[0];
				for(size_t i = 1; i < path.size(); ++i) {
					cout << " -> " << path[i];
				}
			} else {
				cout << "none";
			}
			cout << endl;
		}
	}
}

int main(int argc, char* argv[]) {

	// Check to see if the command is correct
	if(argc != 2) {
		cout << "Usage: ./shortestpaths <filename>" << endl;
		return 1;
	}

	ifstream dictFile(argv[1]);
	if(dictFile.is_open()) {
		string line;
		int linenumber = 1;
		while(getline(dictFile, line)) {
			istringstream iss(line);
			vector<string> seperated;

			do {

				string word;
				iss >> word;

				if(!(word.compare("") == 0)) {
					seperated.push_back(word);
				}

			} while (iss);

			if(!processArgs(seperated, linenumber)) {
				return 1;
			}

			++linenumber;

		}



	} else {
		cout << "Error: Cannot open file '"<< argv[1] << "'." << endl;
		return 1;
	}

	// Set major diagnol to 0
	for(int i = 0; i < vertices; i++) {
		matrix[i][i] = 0;
	}

	InitializeMatrix();

	floyds(matrix);

	display_table(matrix, "Distance matrix:");
	display_table(paths, "Path lengths:");
	display_table(intermediate, "Intermediate vertices:", true);

	backtrack();

	for(int i = 0; i < vertices; i++) {
		delete matrix[i];
		delete paths[i];
		delete intermediate[i];
	}

	return 0;
}