// mergesort by utilizing the standard library and following the pseudocode in Levitin's book 
//  Created by Olcay Kursun on 3/25/23.

#include<iostream>
#include<vector>
#include<algorithm>

void mergesort(std::vector<int>& A)
{
    if (A.size() > 1)
    {
        std::vector<int> B, C;
        std::vector<int>::iterator mid = A.begin() + A.size() / 2;

        std::copy(A.begin(), mid, std::back_inserter(B));
        std::copy(mid, A.end(), std::back_inserter(C));

        mergesort(B);
        mergesort(C);
        std::merge(B.begin(), B.end(), C.begin(), C.end(), A.begin());
    }
}

int main()
{
    std::vector<int> arr = { 111, 112, 75, 11, 15, 25, 5, 120, 1, 160, 20 };
    mergesort(arr);
    for (const auto& i : arr) std::cout << i << ' ';
}
