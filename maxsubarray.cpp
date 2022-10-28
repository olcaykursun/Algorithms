/*
Maximum Subarray problem by Brute Force and Recursive (Divide&Conquer) solutions
Dr. Olcay Kursun, Data Structures, Spring 2022, AUM Dept. of Computer Science
*/

#include<iostream>
#include<vector>
#include<algorithm>
#include<time.h>
using namespace std;

constexpr int N = 64;    //number of integers

void print(vector<int>& x)
{
    for (auto i : x) cout << i << ' ';   //range based loop to print the integers in the vector
    cout << "\n";
}

int bruteForceMaxSubArray(vector<int>& x)
{
    int maxsum = INT_MIN;
    for (auto i = x.begin(); i != x.end(); ++i)   //following the formula on Wiki, https://en.wikipedia.org/wiki/Maximum_subarray_problem
        for (auto j = i; j != x.end(); ++j)       //for every possible 0<=i<=j<N combinations find the sum of the subarray
        {
            int sum = 0;
            for (auto k = i; k <= j; ++k)
                sum += *k;
            if (sum > maxsum)
                maxsum = sum;
        }
    return maxsum;
}

int recursiveMaxSubArray(vector<int>::iterator left, vector<int>::iterator right)
{
    if (left + 1 == right)
        return *left;      //have to return the item if it is the only one (empty subsets are not allowed)

    vector<int>::iterator mid = left + (right - left) / 2;  //midpoint

    int leftside = recursiveMaxSubArray(left, mid);  //check the left for the max subarray
    int rightside = recursiveMaxSubArray(mid, right);//check the right for the max subarray

    //But what if the maximum subarray is crossing the center?
    int partial_left = 0;
    int max_partial_left = INT_MIN;
    vector<int>::iterator i = mid;
    while (i != left)             //scan from the mid to all the way to the leftmost of the current input
    {                             //I used while because to use "for" I believe we need reverse_iterators
        --i;
        partial_left += *i;
        if (partial_left > max_partial_left)  //keep track of the max sum we obtain cumulatively
            max_partial_left = partial_left;
    }

    int partial_right = 0;       //scan from the mid to all the way to the rightmost of the current input
    int max_partial_right = INT_MIN;
    for (auto i = mid; i < right; i++)
    {
        partial_right += *i;
        if (partial_right > max_partial_right)  //keep track of the max sum we obtain cumulatively
            max_partial_right = partial_right;
    }

    //the max of these three is the maxsubarray
    return max({ leftside, rightside, max_partial_left + max_partial_right });
}

int main()
{
    srand(time(NULL));    //random enough for our purposes
    vector<int> x;
    x.reserve(N);   //so that the capacity does not have to be incremented 

    for (int i = 0; i < N; i++)
    {
        x.push_back(rand() % 11 - 4);   //Generate random numbers here between -4 and +6 or some other range
//        cout << x.capacity() << "\n";
    }
    print(x);
    
    int bruteForceAnswer = bruteForceMaxSubArray(x);
    int divideConquerAnswer = recursiveMaxSubArray(x.begin(), x.end());
    cout << divideConquerAnswer << " vs " << bruteForceAnswer << endl;
}
