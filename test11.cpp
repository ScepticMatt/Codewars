/*class TreeNode 
{
  public:
    TreeNode(int value, TreeNode* left, TreeNode* right)
      : m_value(value), m_left(left), m_right(right)
    {
    }

    TreeNode(int value)
      : m_value(value), m_left(NULL), m_right(NULL)
    {
    }

    bool operator==(const TreeNode& rhs) const
    {
        ... // Already implemented for you and used in test cases 
    }
    ...
}*/


class TreeNode 
{
  public:
    TreeNode(int value, TreeNode* left, TreeNode* right)
      : m_value(value), m_left(left), m_right(right)
    {
    }

    TreeNode(int value)
      : m_value(value), m_left(nullptr), m_right(nullptr)
    {
    }

    bool operator==(const TreeNode& rhs) const
    {
        //... // Already implemented for you and used in test cases 
    }
    TreeNode* m_left, *m_right;
    int m_value;
    //...
};


#include <vector>

class Solution
{
public:
    // recursive solution
    static TreeNode* arrayToTree(std::vector<int> arr) 
    {  
        if (arr.empty()) return nullptr;
        return arrayToTreeRecursive(arr, 0);   
    }
private:
    static TreeNode* arrayToTreeRecursive(const std::vector<int>& arr, decltype(arr.size()) index){
        if (index > arr.size()-1) return nullptr;   // no node
        // recursion
        TreeNode* left = arrayToTreeRecursive(arr, 2*index+1);
        TreeNode* right = arrayToTreeRecursive(arr, 2*index+2);
        return new TreeNode(arr[index], left, right);
    } 
};
#include <iostream>
void printTree(TreeNode* tree){
    if (!tree) return;
    printTree(tree->m_left);
    std::cout << " " <<  tree->m_value << " ";
    printTree(tree->m_right);
}
int main(){
    std::vector<int> ivec = {17, 0, -4, 3, 15};
    auto result = Solution::arrayToTree(ivec);
    printTree(result);
}