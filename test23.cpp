/*The prime numbers are not regularly spaced. For example from 2 to 3 the gap is 1. From 3 to 5 the gap is 2. From 7 to 11 it is 4. Between 2 and 50 we have the following pairs of 2-gaps primes: 3-5, 5-7, 11-13, 17-19, 29-31, 41-43

A prime gap of length n is a run of n-1 consecutive composite numbers between two successive primes (see: http://mathworld.wolfram.com/PrimeGaps.html).

We will write a function gap with parameters:

g (integer >= 2) which indicates the gap we are looking for

m (integer > 2) which gives the start of the search (m inclusive)

n (integer >= m) which gives the end of the search (n inclusive)

In the example above gap(2, 3, 50) will return [3, 5] or (3, 5) or {3, 5} which is the first pair between 3 and 50 with a 2-gap.

So this function should return the first pair of two prime numbers spaced with a gap of g between the limits m, n if these numbers exist otherwise nil or null or None or Nothing (depending on the language). In C++ return in such a case {0, 0}.

#Examples: gap(2, 5, 7) --> [5, 7] or (5, 7) or {5, 7}

gap(2, 5, 5) --> nil or in C++ {0, 0}

gap(4, 130, 200) --> [163, 167] or (163, 167) or {163, 167}

([193, 197] is also such a 4-gap primes between 130 and 200 but it's not the first pair)

gap(6,100,110) --> nil or {0, 0} : between 100 and 110 we have 101, 103, 107, 109 but 101-107is not a 6-gap because there is 103in between and 103-109is not a 6-gap because there is 107in between.
*/

#include <iostream>
#include <set>
#include <stdexcept>
#include <algorithm>
class GapInPrimes
{
public:
    static std::pair <long long, long long> gap(int g, long long m, long long n);
private:
	
	static std::set<long long> primes;	
	static std::vector<bool> sieve;
	static void generate(long long max);
};
std::set<long long> GapInPrimes::primes{};
std::vector<bool> GapInPrimes::sieve{true,true};	// zero and 1 are not primes


std::pair <long long, long long> GapInPrimes::gap(int g, long long m, long long n){	
	// O(n*loglog(n))
	if (n < m) throw std::invalid_argument("end smaller than begin");
	if (n < 1 || m <1) throw std::invalid_argument("arguments must be natural numbers");
	if (g < 0) throw std::invalid_argument("gap must be a non-negative integer");
	generate(n); // O(n*loglog(n))
	auto begin = primes.lower_bound(m); // O(log(n))
	auto end = primes.upper_bound(n);	// O(log(n))
	using std::next;
	for (auto it = begin; next(it) != end; ++it)	// O(log(n)), see pi(x)/x
		if (*next(it) - *it == g) 
			return {*it, *next(it)};
	return {0,0};

}
// if max > old_max find primes between old_max and max.
void GapInPrimes::generate(long long max){
	const long long old_max = sieve.size()-1;
	if (max <= old_max) return;	// nothing to do
	// extend sieve with existing primes
	sieve.resize(max+1);	// reserve space for sieve, including 0
	for (const auto& prime: primes){
		for (auto multiples = old_max-old_max%prime+prime; multiples <= max; multiples += prime)
			sieve[multiples] = true;
	}
	// continue with new primes
	for (auto number = old_max+1; number <= max; ++number){	
		if (sieve[number]) continue;	// not a prime
		primes.insert(number);
		for (auto multiples = number; multiples <= max; multiples += number)
			sieve[multiples] = true;
	}
}
// test
int main(){
	//GapInPrimes::generate(100000000);
	//std::cout << *GapInPrimes::primes.rbegin();
}