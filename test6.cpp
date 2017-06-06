/*###Task:

You have to write a function pattern which creates the following Pattern(See Examples) upto n(parameter) number of rows.

####Rules/Note:

If the Argument is 0 or a Negative Integer then it should return "" i.e. empty string.
All the lines in the pattern have same length i.e equal to the number of characters in the last line.
Range of n is (-∞,100]
###Examples:

pattern(5):

    1    
   121   
  12321  
 1234321 
123454321
pattern(10):

         1         
        121        
       12321       
      1234321      
     123454321     
    12345654321    
   1234567654321   
  123456787654321  
 12345678987654321 
1234567890987654321
pattern(15):

              1              
             121             
            12321            
           1234321           
          123454321          
         12345654321         
        1234567654321        
       123456787654321       
      12345678987654321      
     1234567890987654321     
    123456789010987654321    
   12345678901210987654321   
  1234567890123210987654321  
 123456789012343210987654321 
12345678901234543210987654321
pattern(20):

                   1                   
                  121                  
                 12321                 
                1234321                
               123454321               
              12345654321              
             1234567654321             
            123456787654321            
           12345678987654321           
          1234567890987654321          
         123456789010987654321         
        12345678901210987654321        
       1234567890123210987654321       
      123456789012343210987654321      
     12345678901234543210987654321     
    1234567890123456543210987654321    
   123456789012345676543210987654321   
  12345678901234567876543210987654321  
 1234567890123456789876543210987654321 
123456789012345678909876543210987654321*/

#include <string>
#include <stdexcept>
std::string pattern(int n)
{
    if (n < 1) return "";   //  n <= 0 should return empty string
    if (n > 100 )
        throw std::out_of_range("n outside of range (-inf,100]");
    std::string result;
    result.reserve(2*n*n);  // avoid string relocations
    for (auto i = 1; i != n+1; ++i){
        result.append(n-i,' ');
        for (auto j = 1; j != i; ++j) result += std::to_string(j%10);
        result += std::to_string(i%10);
        for (auto j = i-1; j != 0; --j) result += std::to_string(j%10);
        result.append(n-i,' ');
        result += '\n';
    }
    result.pop_back();  // remove last '\n', required by exercise
    return result;
}

#include <iostream>
int main(){
    std::cout << pattern(15);
}