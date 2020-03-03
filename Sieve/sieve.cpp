/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Alex Johnson
 * Date        : 9/11/19
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit);

    ~PrimesSieve() {
        delete [] is_prime_;
    }

    int num_primes() const {
        return num_primes_;
    }

    void display_primes() const;

private:
    // Instance variables
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    // Method declarations
    int count_num_primes() const;
    void sieve();
    static int num_digits(int num);
};

PrimesSieve::PrimesSieve(int limit) :
        is_prime_{new bool[limit + 1]}, limit_{limit} {
    sieve();
}

void PrimesSieve::display_primes() const {

    cout << "Number of primes found: " << count_num_primes() << endl;
    cout << "Primes up to " << limit_ << ":" << endl;
    const int max_prime_width = num_digits(max_prime_), primes_per_row = (80 / (max_prime_width + 1));
    int counter=0;
    for(int i = 2; i < limit_+1; i++) {
    	if(count_num_primes() > primes_per_row) {
    		  cout << setw(max_prime_width);
    	}
    	if(is_prime_[i]) {
    		counter++;
    		cout << i;
    		if(i != max_prime_ && counter != primes_per_row) {
    			cout << " ";
    		}
    	}
		if(counter == primes_per_row) {
    		cout << "\n";
    		counter = 0;
    	}
    }
}

int PrimesSieve::count_num_primes() const {
	int count = 0;
    for(int i = 2; i < limit_+1; i++) {
    	if(is_prime_[i] == true) {
    		++count;
    	}
    }
    return count;
}

void PrimesSieve::sieve() {
	for(int i = 0; i < limit_+1; i++) {
		if(i < 2) {
			is_prime_[i] = false;
		} else {
			is_prime_[i] = true;
		}
	}
	for(int i = 2; i <= floor(sqrt(limit_)); i++) {
		if(is_prime_[i]) {
			for(int j = i*i; j <= limit_; j = j + i) {
				is_prime_[j] = false;
			}
		}
	}
	for(int i = 0; i < limit_ +1; i++) {
		if(is_prime_[i]) {
			max_prime_ = i;
		}
	}
}

int PrimesSieve::num_digits(int num) {
    int count = 0;
    while(num != 0) {
    	count++;
    	num = num / 10;
    }
    return count;
}

int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    cout << endl;

    PrimesSieve obj1(limit);

    obj1.display_primes();

    return 0;
}
