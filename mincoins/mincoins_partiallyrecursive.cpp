#include <iostream>
#include <algorithm>
using namespace std;

#define D 3
int d[D] = { 1, 3, 4 };

//We wrote this recursive function before
int minc(int k)
{
    if (k < 0) return INT_MAX;
    else if (k == 0) return 0;
    else return 1 + std::min({ minc(k - 1), minc(k - 3), minc(k - 4) });
}

int main()
{
    int n = 10;   //find the solution for 10 cents
    
    //let us use the recursive function to lead us to the best choice
    while (n > 0)
    {
        int minCombinationSize = minc(n - d[0]);
        int selectedCoin = 0;   //index of coin that leads to best combination
        for (int i = 1; i < D; i++)
        {
            int temp = minc(n - d[i]);
            if (temp < minCombinationSize)
            {
                minCombinationSize = temp;
                selectedCoin = i;
            }
        }
        cout << d[selectedCoin] << " ";  //give that best coin
        n -= d[selectedCoin];     //compute the remaining amount
    }
    cout << endl;
}
