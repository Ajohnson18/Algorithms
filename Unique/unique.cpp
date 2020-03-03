/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Alex Johnson
 * Date        : 9/19/19
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <cctype>

using namespace std;

bool is_all_lowercase(const string &s) {
    for(char const &c: s) {
        if(int(c) < 97 || int(c) > 122) {
            return false;
        }
    }
    return true;
}

bool all_unique_letters(const string &s) {
    unsigned int checker = 0;
    for(char const &c: s) {
        unsigned int num = 1 << (int(c) - 97);
        if((checker & num) == 0) {
            checker = checker ^ num;
        } else {
            return false;
        }
    }
    return true;
}

int main(int argc, char * const argv[]) {
    if(argc != 2) {
        cout << "Usage: ./unique <string>" << endl;
        return 0;
    }
    if(!is_all_lowercase(argv[1])) {
        cout << "Error: String must contain only lowercase letters." << endl;
        return 0;
    }
    if(all_unique_letters(argv[1])) {
        cout << "All letters are unique." << endl;
    } else {
        cout << "Duplicate letters found." << endl;
    }
    return 1;
}
