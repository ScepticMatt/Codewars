/*To participate in a prize draw each one gives his/her firstname.

Each letter of a firstname has a value which is its rank in the English alphabet. A and a have rank 1, B and b rank 2 and so on.

The length of the firstname is added to the sum of these ranks hence a number n. An array of random weights is linked to the firstnames and each n is multiplied by its corresponding weight to get what they call a winning number.

Example: names: COLIN,AMANDBA,AMANDAB,CAROL,PauL,JOSEPH weights: [1, 4, 4, 5, 2, 1]

PAUL -> n = length of firstname + 16 + 1 + 21 + 12 = 4 + 50 -> 54 The weight associated with PAUL is 2 so Paul's winning number is 54 * 2 = 108.

Now one can sort the firstnames in decreasing order of the winning numbers. When two people have the same winning number sort them alphabetically by their firstnames.

#Task:

parameters: st a string of firstnames, we an array of weights, n a rank

return: the firstname of the participant whose rank is n (ranks are numbered from 1)

#Example: names: COLIN,AMANDBA,AMANDAB,CAROL,PauL,JOSEPH weights: [1, 4, 4, 5, 2, 1] n: 4

The function should return: PauL

#Note: If st is empty return "No participants".

If n is greater than the number of participants then return "Not enough participants".*/


#include <string>
#include <vector>
#include <limits>    // numeric_limits
#include <stdexcept> // overflow_error, invalid_argument
#include <numeric>   // accumulate
#include <cctype>    // isalpha
#include <map>       // multimap
#include <set>      
constexpr size_t max = std::numeric_limits<size_t>::max();
class Rank
{
public:
    // in C++, Why put it in a class if you only use one static non-operator method?
    // Why is the second argument a non-const reference?
    // Should use clearer parameter names
    // e.g. static std::string nthRank(const std::string &firstNames, std::vector<int> &weights, int rank);
    static std::string nthRank(const std::string &st, std::vector<int> &we, int n);
};
size_t sum (size_t value, int c){
    if (!isalpha(c)) throw std::invalid_argument("invalid firstnames argument");
    auto charval = static_cast<size_t>(toupper(c)-64);  // a or A have value 1
    if ( charval > max - value) throw std::overflow_error("overflow occurred");
    return value + charval;
}
std::string Rank::nthRank(const std::string &st, std::vector<int> &we, int n){
    if (n < 0) throw std::invalid_argument("invalid rank argument");
    if (st.empty()) return "No participants";
    // automatically sorts participants, by greater rank and first name alphabetically
    using rank = size_t;
    std::map<rank, std::set<std::string>, std::greater<rank>> participants;
    // iterate over all first names
    size_t begin = 0, end = 0, index = 0;   // index necesarry for weights
    bool last = false;
    // separates first names by comma
    while ((end = st.find_first_of(',', end)) != std::string::npos || !last){
        // extract next first name
        if (begin == end) throw std::invalid_argument("invalid firstnames argument");
        std::string firstname = st.substr(begin, end-begin);
        if (end == std::string::npos)
            last = true;
        else{
            begin = end+1;
            ++end;      
        }
        // calculate winning number
        rank winningNr = std::accumulate(firstname.cbegin(),firstname.cend(),0ULL, sum);
        if (firstname.length() > max - winningNr) throw std::overflow_error("overflow occurred");
        else winningNr+=firstname.length();
        // throws if we.size() < number of participants
        size_t factor = static_cast<size_t>(we.at(index++)); 
        if (factor > max/winningNr) throw std::overflow_error("overflow occurred");
        winningNr*=factor;
        // insert, automatically sorts
        participants[winningNr].insert(firstname);
    }   

    // return name for a given rank
    auto it = participants.cbegin();
    for (index = 1; it != participants.cend(); ++it)
        for (auto it2 = it->second.cbegin(); it2 != it->second.cend(); ++it2, ++index)
            if (index == n) return *it2;
    return "Not enough participants";
}

#include <iostream>
int main(){
    std::vector<int> weights{1, 3, 5, 5, 3, 6};
    const std::string firstnames{"Elijah,Chloe,Elizabeth,Matthew,Natalie,Jayden"};
    /*size_t begin = 0, end = 0;
    bool last = false;
    while((end = firstnames.find_first_of(',',end)) != std::string::npos || !last ){
        std::cout << firstnames.substr(begin, end-begin) << std::endl;
        if (end == std::string::npos)
            last = true;
        else{
            begin = end+1;
            ++end;      
        }

    }*/
    //rank winningNr = std::accumulate(firstname.cbegin(),firstname.cend(),0ULL, sum);
    std::cout << Rank::nthRank(firstnames,weights,2) << std::endl;
}