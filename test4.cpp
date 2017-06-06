#include <vector>
#include <numeric>
class Johnann
{
public:
    static std::vector<long long> john(long long n);
    static std::vector<long long> ann(long long n);
    static long long sumJohn(long long n);
    static long long sumAnn(long long n);
private:
    static std::vector<long long> kataJohn, kataAnn;
    static void fill_n(long long n);
    static void fill(long long n, long long done);
};
std::vector<long long> Johnann::kataJohn{0};	// KataJohn[0] = 0
std::vector<long long> Johnann::kataAnn{1};		// KataAnn[0] = 1
// calculate missing kata amounts iteratively, save results
inline void Johnann::fill_n(long long n){
	kataJohn.reserve(n); kataAnn.reserve(n);	// reserve space
	for (auto next = kataJohn.size(); next != n+1; ++next){
		kataJohn[next] = next - kataAnn[kataJohn[next-1]];
		kataAnn[next] = next - kataJohn[kataAnn[next-1]];
	}
}

std::vector<long long> Johnann::john(long long n){
	if (kataJohn.size() < n) fill_n(n);
	return std::vector<long long>(kataJohn.begin(),kataJohn.begin()+n);
}
std::vector<long long> Johnann::ann(long long n){
	if (kataAnn.size() < n) fill_n(n);
	return std::vector<long long>(kataAnn.begin(),kataAnn.begin()+n);
}
long long Johnann::sumJohn(long long n){
	if (kataJohn.size() < n) fill_n(n);
	long long result = 0;
	return std::accumulate(kataJohn.begin(),kataJohn.begin()+n,result);
}
long long Johnann::sumAnn(long long n){
	if (kataJohn.size() < n) fill_n(n);
	long long result = 0;
	return std::accumulate(kataAnn.begin(),kataAnn.begin()+n,result);
}
// test
#include <iostream>
int main(){
	auto result = Johnann::john(10);
	result = Johnann::john(100);
	for (const auto& elem: result) std::cout << elem << " ";
	std::cout << Johnann::sumJohn(100);
}