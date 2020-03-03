/*******************************************************************************
 * Name    : gcd.cpp
 * Author  : Alexander Johnson
 * Version : 1.0
 * Date    : August 30th, 2019
 * Description : Computes the GCD of two command-line arguments.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

int gcd_iterative(int m, int n) {
	int gcd = 0;
	if(m < 0) {
		m = m * -1;
	}
	if(n < 0) {
		n = n * -1;
	}
	if(m == 0 || n == 0) {
		return m + n;
	}
	for(int i = 1; i <= m && i <= n; i++) {
		if(m % i == 0 && n % i == 0) {
			gcd = i;
		}
	}
	return gcd;
}

int gcd_recursive(int m, int n) {
	if(n != 0) {
		return gcd_recursive(n, m%n);
	} else {
		if(m < 0) {
			return m * -1;
		}
		return m;
	}
}


int main(int argc, char* const argv[]) {
    int m, n;
    istringstream iss;

    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <integer m> <integer n>"
             << endl;
        return 1;
    }
    iss.str(argv[1]);
    if ( !(iss >> m) ) {
        cerr << "Error: The first argument is not a valid integer."
             << endl;
        return 1;
    }
    iss.clear(); // clear the error code
    iss.str(argv[2]);
    if ( !(iss >> n) ) {
        cerr << "Error: The second argument is not a valid integer."
             << endl;
        return 1;
    }

    cout << "Iterative: gcd(" << m << ", " << n << ") = " << gcd_iterative(m,n) << endl;
    cout << "Recursive: gcd(" << m << ", " << n << ") = " << gcd_recursive(m,n) << endl;
    return 0;
}

