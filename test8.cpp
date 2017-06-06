#include <stdexcept>
#include <vector>
#include <limits>
class Kata
{
public:
	// runs should rather be unsigned
	// return value should hold bigger values
	// should be static, or namespace instead of class
    std::vector<int> foldArray(std::vector<int> array, int runs)
    {
    	if (runs < 0) throw std::invalid_argument("runs must be >= 0");
    	for (int i = 0; i != runs; ++i){
    		auto beg = array.begin(), end = array.end()-1;
    		if (beg == end) break;
    		do{
    			// check for overflow/underflow.
    			constexpr int max = std::numeric_limits<int>::max();
				constexpr int min = std::numeric_limits<int>::min();
    			if ((*beg > 0) && (*end > max - *beg))
    				throw std::overflow_error("integer overflow");
    			if ((*beg < 0) && (*end < min - *beg))
    				throw std::underflow_error("integer underflow");
    			else 	// no underflow or overflow
    				*beg += *end;
    		} while(++beg != end && beg != --end);

    		array.erase(end+(array.size()%2), array.end());
    	}
        return array;
    }
};


#include <iostream>
int main(){
	constexpr int max = std::numeric_limits<int>::max();
	constexpr int min = std::numeric_limits<int>::min();
	std::vector<int> ivec{ -9, 9, -8, 8, 66, 23};
	Kata myKata; 	// need object foldArray not static;
	auto result =  myKata.foldArray(ivec, 1);
	for (const auto& elem: result) std::cout << elem << " ";
	unsigned i = 2* std::numeric_limits<int>::max();
	//std::cout << i << std::endl << std::numeric_limits<int>::max();
	//if (i > std::numeric_limits<int>::max())
}