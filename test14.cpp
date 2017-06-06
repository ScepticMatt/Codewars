#include <vector>
#include <stdexcept>
#include <limits>
class PrimeConsec
{
private:
    // should rather use unsigned argument
    static int countPrimeDiv(long long n);
public:
    // should rather use const reference type and larger return type
    static int consecKprimes(int k, std::vector<long long> &arr);
};
#include <iostream>
int PrimeConsec::countPrimeDiv(long long n){
    if (n < 1) throw std::invalid_argument("number does not have a decomposition");
    // count prime factors
    long long factor = 2;
    int count = 0;  // can't overflow because max is log(n)/log(2)
    while (n != 1){
        if (n%factor)
            ++factor;
        else {
            n /= factor;
            ++count;
        }       
    }
    return count;
}
int PrimeConsec::consecKprimes(int k, std::vector<long long> &arr){
    int count{0};
    for (auto it = arr.begin(); it!= arr.cend()-1; ++it)
        if (countPrimeDiv(*it) == k && countPrimeDiv(*(it+1)) == k ){
            if (count == std::numeric_limits<int>::max())
                throw std::overflow_error("count too large");
            ++count;
        }
    return count;
}

int main(){
    std::vector<long long> a = {10081, 10071, 10077, 10065, 10060, 10070, 10086, 10083, 10078, 10076, 10089, 10085, 10063, 10074, 10068, 10073, 10072, 10075};
    std::cout << PrimeConsec::consecKprimes(2,a);
    //std::cout << PrimeConsec::countPrimeDiv(1024);
}