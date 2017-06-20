/*
In Germany we have "LOTTO 6 aus 49". That means that 6 of 49 numbers are drawn as winning combination.
There is also a "Superzahl", an additional number, which can increase your winning category.

In this kata you have to write two methods.

std::vector<int> numberGenerator()

int checkForWinningCategory(std::vector<int> checkCombination, std::vector<int> winningCombination)
The first method is for drawing the lottery numbers.
You have to create an array with 7 random numbers. 6 from these are from 1 - 49.
Of Course every number may only occure once.
And the 7th number is the "Superzahl". A number from 0 - 9. This number is independent from the first six numbers.
The first 6 numbers have to be in ascending order.

A result could be:
4, 9, 17, 22, 25, 35, 0
Or:
4, 18, 22, 34, 41, 44, 4

The second method should check a given number against the winning combination and have to return the winning category:

1  - 6 numbers and Superzahl match
2  - 6 numbers match
3  - 5 numbers and Superzahl match
4  - 5 numbers match
5  - 4 numbers and Superzahl match
6  - 4 numbers match
7  - 3 numbers and Superzahl match
8  - 3 numbers match
9  - 2 numbers and Superzahl match
-1 - if the numbers do not match any of the rules above
*/
#include <vector>
#include <random>
#include <chrono>
#include <stdexcept>
#include <iostream>
#include <set>
std::vector<int> numberGenerator()
{
	// adapted from another of my kata solutions
	// if non-deterministic random has entropy left, use it
	// otherwise, use backup mersenne-twister engine
	std::set<int> winningNumbers;
	std::random_device rd;
	// use system time in nanoseconds as backup seed
	auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	// backup mersenne twister engine, used if rd has no entropy left
	std::mt19937 mt(rd.entropy()?rd():seed);
	// allowed number ranges:
	std::uniform_int_distribution<unsigned> normalzahl(1,49); 
	std::uniform_int_distribution<unsigned> superzahl(0,9);   
	while(winningNumbers.size() != 6)
		winningNumbers.insert(rd.entropy()?normalzahl(rd):normalzahl(mt));
	std::vector<int> result{winningNumbers.cbegin(),winningNumbers.cend()};
	result.push_back(rd.entropy()?superzahl(rd):superzahl(mt));
	//if (!rd.entropy()) std::clog << "Warning: system does not have a real random source" << std::endl;
	return result;
}

int checkForWinningCategory(std::vector<int> checkCombination, std::vector<int> winningCombination)
{
	if (checkCombination.size() != 7 || winningCombination.size() != 7)
		throw std::invalid_argument("Combinations must contain 7 numbers");
	// TODO: other pre-checks
	unsigned matches=0;
	auto it = checkCombination.cbegin(), it_end = checkCombination.cend()-1;
	auto it2 = winningCombination.cbegin(), it2_end = winningCombination.cend()-1;
	while (it != it_end && it2 != it2_end){
		if (*it == *it2){
			++matches;
			++it;++it2;
		}
		else if (*it > *it2) ++it2;
		else if (*it < *it2) ++it;
	}
	bool superzahl = checkCombination[6]==winningCombination[6];
	switch(matches){
		case 6: return superzahl?1:2; break;
		case 5: return superzahl?3:4; break;
		case 4: return superzahl?5:6; break;
		case 3: return superzahl?7:8; break;
		case 2: return superzahl?9:-1; break;
		default: return -1;
	}
}
// test
#include <iostream>
int main(){
	/*auto vec = numberGenerator();
	for (const auto& elem: vec)
		std::cout << elem << " ";*/
	std::cout << checkForWinningCategory({ 1, 2, 3, 4, 5, 6, 7 }, { 1, 2, 3, 4, 5, 6, 7 });
	std::cout << checkForWinningCategory({ 1, 2, 3, 4, 5, 6, 0 }, { 1, 2, 3, 4, 5, 6, 7 });
	std::cout << checkForWinningCategory({ 1, 2, 3, 34, 35, 39, 1 }, { 1, 2, 3, 4, 5, 6, 7 });
}