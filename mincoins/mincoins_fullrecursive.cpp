#include <iostream>
#include <vector>
using namespace std;

#define D 3
int d[D] = { 1, 3, 4 };

vector<int> minc(int k)
{
    vector<int> best;
    if (k > 0)
    {
        int best_coin = 0;
        best = minc(k - d[0]);
        for (int i = 1; i < D; i++)
        {
            if (k - d[i] >= 0)
            {
                vector<int> temp = minc(k - d[i]);
                if (temp.size() < best.size())
                {
                    best = temp;
                    best_coin = i;
                }
            }
        }
        best.push_back(d[best_coin]);
    }
    return best;
}

int main()
{
    for (auto i : minc(10))  //find the solution for 10 cents
        cout << i << " "; 
    cout << endl;
}
