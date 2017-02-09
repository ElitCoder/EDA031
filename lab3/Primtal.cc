#include <iostream>


using namespace std;



	int lessThan = 99999;
	int m_prime = 200;



	int largestPrime(){

		bool notPrime(true);


		while(notPrime){
			notPrime = false;
			//while(start < lessThan){

			//från 100,000 och neråt tills största talet delbart med sig självt hittats!
			for (int i = lessThan - 1; i >= 2; i--){

				if (lessThan % i == 0) {
					notPrime = true;
					break;

				}



			}

			if(!notPrime) {
				return lessThan;
			}

			lessThan--;


		}



			return 0;
}





int main(){

// creates a string with length 200 and all chars P
	string primeLetters(m_prime, 'P');
//access a specific char spot in string with string[i]
	primeLetters[0] = 'C';
	primeLetters[1] = 'C';

//start on 2
	int startPrime = 2;
//vill inte gå längre än satta maxgräns
	while(startPrime < m_prime){

		int multiplePrime = startPrime * 2;

			while(multiplePrime < m_prime){

				primeLetters[multiplePrime] = 'C';
				multiplePrime = startPrime + multiplePrime;

		}

		startPrime++;
		//Börja på 2, gå sedan uppåt tills 200!
		while(primeLetters[startPrime] != 'P' && startPrime < m_prime){
			startPrime++;
		}

	}

	//skriv ut strängen, där det står P är det primtal!
	cout << "Primes between 0-200: " << primeLetters << "\n";



	cout << "The largest primenumber is: " << largestPrime() << "\n";

	return 0;
}
