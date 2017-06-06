#include <vector>
class SqInRect
{
  public:
  static std::vector<int> sqInRect(int lng, int wdth);
  
  private:
  int s(int lng, int wdth);
  std::vector<int> results;
};
std::vector<int> SqInRect::sqInRect(int lng, int wdth){
  std::vector<int> result;
  while(wdth){  // no Area left, abort
    // 1) split off sqares with length = wdth
    auto count = lng/wdth;
    auto rest = lng%wdth;
    result.insert(result.end(), count, wdth);
    // 2) rotate resulting rectangle, go to 1)  
    lng = wdth;
    wdth = rest;
  }
  return result;
}


int main(){
  auto result = SqInRect::sqInRect(281,123);
  for (const auto& elem: result)
    std::cout << elem << " ";
}