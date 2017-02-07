#include <iostream>
#include <string>

using namespace std;

enum {
    MAX_PRIME = 200
};

int largest() {
    int start = 99999;

    while(true) {
        bool prime(true);

        for(int i = 2; i < start / 2; i++) {
            if(start % i == 0) {
                prime = false;

                break;
            }
        }

        if(prime) {
            return start;
        }

        start--;
    }

    return -1;
}

int main() {
    string primes(MAX_PRIME, 'P');
    primes[0] = primes[1] = 'C';

    short prime = 2;

    while(prime < MAX_PRIME) {
        short multiple = prime * 2;

        while(multiple < MAX_PRIME) {
            primes[multiple] = 'C';

            multiple += prime;
        }

        cout << "Prime: " << prime << "\n" << primes << '\n';

        prime++;

        while(primes[prime] == 'C') {
            prime++;
        }
    }

    cout << "\nLargest prime under 100000 is: " << largest() << '\n';

    return 0;
}
