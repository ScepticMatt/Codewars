#include <sstream>
#include <map>
#include <algorithm>
#include <iterator>
class StockList
{
public:
  static std::string stockSummary(std::vector<std::string> &lstOfArt, std::vector<std::string> &categories);
};
std::string StockList::stockSummary(std::vector<std::string> &lstOfArt, std::vector<std::string> &categories){
  if (lstOfArt.empty()) return "";
  std::map<char, unsigned> matching;
  // get begin of digits:
  std::string::size_type first_digit =  lstOfArt[0].find_last_not_of("0123456789") + 1;
  for (const auto& elem: lstOfArt){
    // check if code is in category
    auto found = std::find_if(categories.cbegin(),categories.cend(),[&elem](std::string x){return x[0] == elem[0];});
    // extract number
    auto count = std::stoi(elem.substr(first_digit));
    // create matching, sorted
    if (found != categories.cend()){
      char key = (*found)[0];
      matching[key] += count; //insert if needed;
      }
  }
  // output results:
  std::ostringstream os;
  if (matching.cbegin() == matching.cend()) return "";
  for (auto it = matching.cbegin(); it != matching.cend(); ++it){
    os << "(" << it->first << " : " << it->second << ")";
    if (std::next(it) != matching.cend()) os << " - ";
  }
  return os.str();
}
