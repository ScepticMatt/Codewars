/*
Common denominators

You will have a list of rationals in the form

 { {numer_1, denom_1} , ... {numer_n, denom_n} }
or

 [ [numer_1, denom_1] , ... [numer_n, denom_n] ]
or

 [ (numer_1, denom_1) , ... (numer_n, denom_n) ]
where all numbers are positive ints.

You have to produce a result in the form

 (N_1, D) ... (N_n, D)
or

 [ [N_1, D] ... [N_n, D] ]
or

 [ (N_1', D) , ... (N_n, D) ]
or

{{N_1, D} ... {N_n, D}}
depending on the language (See Example tests)

in which D is as small as possible and

 N_1/D == numer_1/denom_1 ... N_n/D == numer_n,/denom_n.
Example:

convertFracs [(1, 2), (1, 3), (1, 4)] `shouldBe` [(6, 12), (4, 12), (3, 12)]*/

#include <unordered_map>
#include <vector>
#include <set>
#include <string>
#include <sstream>


class Fracts
{
public:
	static std::string convertFrac(std::vector<std::vector<unsigned long long>> &lst);
public:	// from another of my Kata solutions
	static std::unordered_map<unsigned long long, unsigned long long> primeFactors;
	static std::set<long long> primes;	
	static std::vector<bool> sieve;
	static void generatePrimes(unsigned long long max);
};
std::set<long long> Fracts::primes{2};
std::vector<bool> Fracts::sieve{true,true,true};	// zero and 1 are not primes
std::unordered_map<unsigned long long, unsigned long long> Fracts::primeFactors{};

std::string Fracts::convertFrac(std::vector<std::vector<unsigned long long>> &lst){
	// calculate lowest common denominator
	primeFactors.clear();
	for (const auto& fraction: lst){
		unsigned long long left = fraction.at(1);	// get denominator
		// calcluate LCD
		for (auto it = primes.cbegin(); left != 1 && it!= primes.cend(); ++it){
			const auto prime = *it;
			// calculate prime factors
			if (left % prime == 0){
				unsigned long long count;
				for (count = 0; left%prime == 0; ++count, left/=prime);
				auto it = primeFactors.find(prime);
				if (it == primeFactors.end()) 
					primeFactors[prime] = count;
				else
					primeFactors[prime] = std::max(primeFactors[prime],count);
			}
			if (std::next(it) == primes.cend())
				generatePrimes(left);	// could be done in separate thread
		}
	}
	unsigned long long lcd = 1;	// could do multiply with less complexity
	for (auto it = primeFactors.cbegin(); it != primeFactors.cend();++it)
		for (auto count = 0; count != it->second; ++count)
			lcd*=it->first;	// might overflow
	// output result:
	std::string output;
	for (const auto& fraction: lst){
		// might overflow
		const unsigned long long nominator = (lcd/fraction.at(1)) * fraction.at(0) ;
		std::ostringstream os;
		os << '(' << nominator << ',' << lcd << ')';
		output+=os.str();
	}	
	return output;
}
void Fracts::generatePrimes(unsigned long long max){	// from another Kata solution
	const unsigned long long old_max = sieve.size()-1;
	if (max <= old_max) return;	// nothing to do
	// extend sieve with existing primes
	sieve.resize(max+1);	// reserve space for sieve, including 0
	for (const auto& prime: primes){
		for (auto multiples = old_max-old_max%prime; multiples <= max; multiples += prime)
			sieve[multiples] = true;
	}
	// continue with new primes
	for (auto number = old_max+1; number <= max; ++number){	
		if (sieve[number]) continue;	// not a prime
		primes.insert(number);
		for (auto multiples = number; multiples+number <= max; multiples += number)
			sieve[multiples] = true;
	}
}

// test
#include <iostream>
int main(){
	std::vector<std::vector<unsigned long long>> r1 = { {1, 5262}, {1, 11111111}, {1, 255689} };
	// should be 589416
	//std::vector<std::vector<unsigned long long>> r1 = { {1, 12}, {1, 3}, {1, 30} };
	std::string ans1 = Fracts::convertFrac(r1);
	std::cout << ans1;
	/*Fracts::generatePrimes(100);
	for (const auto& elem: Fracts::primes)
		std::cout << elem << " ";
	std::cout << std::endl;
	for (auto i = 0; i< Fracts::sieve.size(); ++i)
		std::cout << i << " " << Fracts::sieve[i] << std::endl;*/
}