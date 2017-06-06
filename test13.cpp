/*Given a node object representing a binary tree:

Node:
  value: <int>,
  left: <Node> or null,
  right: <Node> or null
In C++:


write a function that returns the sum of all values, including the root.*/

#include <stdexcept>
#include <limits>
struct node
{
  int value;
  node* left;
  node* right;
};
int sumTheTreeValues(node* root) {
// recursion
  	if (!root) return 0;
  	auto left = sumTheTreeValues(root->left);
  	auto right = sumTheTreeValues(root->right);
// check for overflow/underflow
  	constexpr auto max = std::numeric_limits<int>::max();
  	constexpr auto min = std::numeric_limits<int>::min();
  	if (right > 0 && left > max - right) 
  		throw std::overflow_error("Overflow occurred");
  	else if (right < 0 && left > min - right) 
  		throw std::overflow_error("Underflow occurred");
  	const auto sum = left + right, value = root->value;
  	if (sum > 0 && value > max - sum) 
  		throw std::overflow_error("Overflow occurred");
  	else if (sum < 0 && value < min - sum) 
  		throw std::overflow_error("Underflow occurred");
// return result
  	return sum + value;

}
int main(){
	
}