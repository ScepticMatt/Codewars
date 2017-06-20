/*
Your task is to determine the Next Lower Power of 2 to a given input number - or something like that...;-)

Here it's easy, you don't have to check errors or incorrect input values, every thing is ok without bad tricks, only int numbers as input and output;-)...

And please consider: You have to use bit shift operations to solve this "problem", no multiplication, no Math.Pow() or **...

Some easy examples:

Input: 2     => Output: 1 
Input: 7     => Output: 4
Input: 0     => Output: ?
Input: -128  => Output: -256
There are some static tests at the beginning and many random tests if you submit your solution.
 
Perhaps you can look at Shifting Bits Next Higher Power too;-)?
*/

int nextLower(int n)
{
	if (n==0) return -1;
	bool isPowerOfTwo = true;
	int result = 1;
	while (n != 1 && n != -1){
		if (n%2) isPowerOfTwo = false;
		n>>=1;
		result<<=1;
	}
	if (isPowerOfTwo){	// go to next lower number for exact powers of two
		if (n>0) result>>=1;
		else result<<=1;
	}
	return (n>0)?result:-result;
}

// test
#include <iostream>
int main(){
	int n;
	std::cin >> n;
	std::cout << nextLower(n) << std::endl;
	std::cout << (-1>>1);
}
