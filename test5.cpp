/*

You get an array of arrays.
If you sort the arrays by their length, you will see, that their length-values are consecutive.
But one array is missing!


You have to write a method, that return the length of the missing array.

Example:
[[1, 2], [4, 5, 1, 1], [1], [5, 6, 7, 8, 9]] --> 3


If the array of arrays is null/nil or empty, the method should return 0.

When an array in the array is null or empty, the method should return 0 too!
There will always be a missing element and its length will be always between the given arrays. 

Have fun coding it and please don't forget to vote and rank this kata! :-)

I have created other katas. Have a look if you like coding and challenges.

*/

#include <limits>
#include <stdexcept>
#include <set>
#include <vector>
// return type should be typename std::vector<std::vector<TYPE>>::size_type 
template<class TYPE>
int getLengthOfMissingArray(std::vector<std::vector<TYPE>> arrayOfArrays)
{	
	// save sizes in ordered set
	std::set<int> sizes;
	if (arrayOfArrays.empty()) return 0;
	for (const auto& array: arrayOfArrays){
		if (!array.size()) return 0;	// exercise requires that an empty array should return 0
    	// excercise requires int return value
		else if (array.size() > std::numeric_limits<int>::max())
			throw std::out_of_range("array lengths too large");	
		else sizes.insert(array.size()); // O(log(n))
	}
	// iterate over set, find missing. O(n)
	int i = *sizes.cbegin(); // min element;
	for (auto it = sizes.cbegin(); it != sizes.cend(); ++i, ++it)
		if (i != *it) return i;
}
#include <iostream>
int main(){
	std::vector<std::vector<int>> testInput = { { 1, 2 }, { 4, 5, 1, 1 }, { 1 }, { 5, 6, 7, 8, 9 } };
	int actual = getLengthOfMissingArray(testInput);
	std::cout << actual << std::endl;
}