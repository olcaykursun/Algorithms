// mergesort by utilizing the standard library and following the pseudocode in Levitin's book... We are using lists (and advance) rather than vectors (and +)
//  Created by Olcay Kursun on 4/3/23.

#include<iostream>
#include<list>
#include<algorithm>

void mergesort(std::list<int>& A)
{
    if (A.size() > 1)
    {
        std::list<int> B, C;
        std::list<int>::iterator mid = A.begin();
        std::advance(mid, A.size() / 2);

        std::copy(A.begin(), mid, std::back_inserter(B));
        std::copy(mid, A.end(), std::back_inserter(C));

        mergesort(B);
        mergesort(C);
        std::merge(B.begin(), B.end(), C.begin(), C.end(), A.begin());
    }
}

int main()
{
    std::list<int> arr = { 111, 112, 75, 11, 15, 25, 5, 120, 1, 160, 20 };
    mergesort(arr);
    for (const auto& i : arr) std::cout << i << ' ';
    std::cout << '\n';
    for (std::list<int>::iterator p = arr.begin(); p != arr.end(); ++p)
        std::cout << *p << ' ';
    std::cout << '\n';
    
    //We dont have ".at()" or subscript operator for lists, so we cannot do this:
    //    for (int i = 0; i < arr.size(); ++i)
    //    {
    //        std::cout << arr[i] << ' ';
    //    }

    //You can advance one by one or by i
    for (int i = 0; i < arr.size(); ++i)
    {
        auto it = arr.begin();
        std::advance(it, i);
        std::cout << *it << ' ';
    }

    std::cout << '\n';
    
    auto it = arr.begin();
    for (int i = 0; i < arr.size(); ++i)
    {
        std::cout << *it << ' ';
        it = std::next(it);
    }

}
