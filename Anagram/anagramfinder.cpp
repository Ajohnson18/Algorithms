/*******************************************************************************
 * Name          : anagramfinder.cpp
 * Author        : Alex Johnson
 * Pledge        : I pledge my honor that I have abided by the Stevens Honor System.
 * Date          : 11/15/19
 * Description   : Finds all of the anagrams in a file of words
 ******************************************************************************/
#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <string>
#include <vector>

using namespace std;

// Global Variables
size_t max_anagrams = 0;
const int primes[] = {
	2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43,
	47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103,
	107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163,
	167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227,
	229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281,
	283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353,
	359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421,
	431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487,
	491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569,
	571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631,
	641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701,
	709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773,
	787, 797, 809, 811, 821, 823, 827, 829, 839, 853, 857,
	859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937,
	941, 947, 953, 967, 971, 977, 983, 991, 997
};


// Finds the prime value for each word
int getPrimeValue(string s) {
	int total = 1;
	for(char i: s) {
		if(int(i) < 32 || int(i) > 126) continue;
		if(int(i) > 64 && int(i) < 97) i += 32;
		total *= primes[i-33];
	}
	return total;
}

// compares the first element of two vectors
bool sortcol(vector<string>& v1, vector<string>& v2) {
	return v1[0] < v2[0];
}

// Prints all of the anagrams
void printAnagrams(map<int, vector<string>> words) {

	map<int, vector<string>>::iterator it;
	vector<vector<string>> result;

	// Find max number of anagrams
	for(it = words.begin(); it != words.end(); ++it) {
		if(it->second.size() > max_anagrams) {
			max_anagrams = it->second.size();
		}
	}

	// Print amount of anagrams
	if(max_anagrams > 1) {
		cout << "Max anagrams: " << max_anagrams << endl;
	} else {
		cout << "No anagrams found." << endl; 
		return;
	}

	// Puts all the vectors with size of max anagram into result
	for(it = words.begin(); it != words.end(); ++it) {
		if(it->second.size() == max_anagrams) {
			result.push_back(it->second);
		}
	}

	// Sorts all subsets
	for(vector<string>& v: result) {
		sort(v.begin(), v.end());
	}

	// Sort the vector
	sort(result.begin(), result.end(), sortcol);

	// Print the words
	for(vector<string> v: result) {
		for(string s: v) {
			cout << s << endl;
		}
		cout << endl;
	}
}

int main(int argc, char* argv[]) {

	// Check to see if the command is correct
	if(argc != 2) {
		cout << "Usage: ./anagramfinder <dictionary file>" << endl;
		return 1;
	}

	// Construct the vector words and put all of the lines of words into it.	
	//vector<pair<string, int>> words;
	map<int, vector<string>> words;
	ifstream dictFile(argv[1]);
	if(dictFile.is_open()) {
		string line;
		while(getline(dictFile, line)) {
			int value = getPrimeValue(line);
			if(words.find(value) == words.end()) {
				words.insert(pair<int, vector<string>>(value, vector<string>()));
				words[value].push_back(line);
			} else {
				words[value].push_back(line);
			}
		}
	} else {
		cout << "Error: File '"<< argv[1] << "' not found." << endl;
		return 1;
	}

	printAnagrams(words);

	return 0;
}