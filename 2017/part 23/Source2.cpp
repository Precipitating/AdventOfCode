#include <iostream>


bool isPrime(int n)
{

    // Corner case
    if (n <= 1)
        return false;

    // Check from 2 to n-1
    for (int i = 2; i <= n / 2; i++)
        if (n % i == 0)
            return false;

    return true;
}
int main() 
{
    int a = 1, b = 57, c = 0, d = 0, e = 0, f = 0, g = 0, h = 0;

    // Set initial values
    b = b * 100 + 100000;
    c = b + 17000;

    
    for (int i = b; i <= c; i += 17)
    {
        if (!isPrime(i))
        {
            ++h;
        }
    }

    std::cout << h;

    return 0;
}