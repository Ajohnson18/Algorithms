/*******************************************************************************
 * Name          : quickselect.cpp
 * Author        : Alex Johnson
 * Pledge        : I pledge my honor that I have abided by the Stevens Honor System.
 * Date          : 10/18/19
 * Description   : Implements the quickselect algorithm found on page 160 in
 *                 Algorithms, 3e by Anany Levitin.
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>

using namespace std;

size_t lomuto_partition(int array[], size_t left, size_t right) {
    int p = array[left];
    int s = left;
    for(size_t i = s+1; i < right; ++i) {
        if(array[i] > p) {
            ++s;
            swap(array[i], array[s]);
        }
    }
    swap(array[s], array[right]);
    return s;
}

int quick_select(int array[], size_t left, size_t right, size_t k) {
    size_t s = lomuto_partition(array, left, right);
    if(s == k-1) return array[s];
    else if(s > left + k - 1) return quick_select(array, left, s-1, k);
    else return quick_select(array, s+1, k-1-s, k);
}

int quick_select(int array[], const size_t length, size_t k) {
    return quick_select(array, 0, length - 1, k);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <k>" << endl;
        return 1;
    }

    int k;
    istringstream iss;
    iss.str(argv[1]);
    if ( !(iss >> k) || k <= 0 ) {
        cerr << "Error: Invalid value '" << argv[1] << "' for k." << endl;
        return 1;
    }

    cout << "Enter sequence of integers, each followed by a space: " << flush;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    iss.clear();
    while (true) {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }

    int num_values = values.size();
    if (num_values == 0) {
        cerr << "Error: Sequence of integers not received." << endl;
        return 1;
    }

    if(atoi(argv[1]) > (int)values.size()) {
        cout << "Error: Cannot find smallest element " << argv[1] << " with only " << values.size() << " value";
        if(values.size() > 1) {
            cout << "s.";
        } else {
            cout << ".";
        }
    } else {
        int *arr = new int[values.size()];

        copy(values.begin(), values.end(), arr);
        cout << "Smallest element " << argv[1] << ": " << quick_select(arr, values.size(), atoi(argv[1])) << endl;
    }

    return 0;
}
