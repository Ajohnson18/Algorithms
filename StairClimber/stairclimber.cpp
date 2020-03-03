/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Alex Johnson
 * Date        : 9/29/19
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

vector< vector<int> > get_ways(int num_stairs) {
    vector<vector<int>> ways;
    if(num_stairs <= 0) {
        ways.push_back(vector<int>());
    } else {
        for(int i = 1; i < 4; i++) {
            if(num_stairs >= i) {
                vector<vector<int>> result = get_ways(num_stairs-i);
                for(int j = 0; j < int(result.size()); j++) {
                    result[j].insert(result[j].begin(), i);
                }
                for(int k = 0; k < int(result.size()); k++) {
                    ways.push_back(result[k]);
                }
            }
        }---
    }
    return ways;
}

void display_ways(const vector< vector<int> > &ways) {
    for(int i = 0; i < int(ways.size()); i++) {
        if(i+1 < 10 && ways.size() >= 10) {
            cout << " " << (i+1) << ". [";
        } else {
            cout << (i+1) << ". [";
        }
        for(int j = 0; j < int(ways[i].size()); j++) {
            cout << ways[i][j];
            if(j != int(ways[i].size()-1)) {
                cout << ", ";
            }
        }
        cout << "]" << endl;
    }
}

int main(int argc, char * const argv[]) {
    if(argc != 2) {
        cout << "Usage: " << argv[0] << " <number of stairs>" << endl;
        return 0;
    }
    if(atoi(argv[1]) <= 0) {
        cout << "Error: Number of stairs must be a positive integer." << endl;
        return 0;
    }
    vector<vector<int>> ways = get_ways(atoi(argv[1]));
    if(atoi(argv[1]) == 1) {
        cout << "1 way to climb 1 stair." << endl;
    } else {
        cout << ways.size() << " ways to climb " << argv[1] << " stairs." << endl; 
    }
    display_ways(ways);
    return 0;
}
