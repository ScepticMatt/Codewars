#include <set>
#include <vector>
#include <string>

class WhichAreIn
{
// std::vector is not an array! should use const reference here
// does not make sense to use class for one static method in C++,
public:
	using svec = std::vector<std::string>;
	static svec inArray(const svec &array1, const svec &array2){
		std::set<std::string> result;	// sorts automatically
		for (const auto& elem1: array1)
			for (const auto& elem2: array2)
				if (elem2.find(elem1) != std::string::npos)
					result.insert(elem1);
		return svec(result.cbegin(), result.cend());
	}
};

#include <iostream>
int main(){
	std::vector<std::string> arr1 = { "arp", "live", "strong" };
	std::vector<std::string> arr2 = { "lively", "alive", "harp", "sharp", "armstrong" };
	std::vector<std::string> ans1 = WhichAreIn::inArray(arr1, arr2);
	for (const auto& elem: ans1)
		std::cout << elem << " ";
}