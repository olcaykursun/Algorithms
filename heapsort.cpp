/*
Heapsort
Created on Wed Mar 31 08:55:58 2022
@author: Dr. Olcay Kursun, Spring 2022, AUM Dept. of Computer Science
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

void print(string msg, int a[], int n)
{
    cout << msg << '[';
    for (int i = 1; i <= n; i++)
    {
        cout << a[i] << ' ';
    }
    cout << "]\n";
}

void sink(int a[], int n, int i)
{
    int v = a[i];
    int k = i;
    bool heap = false;
    while (!heap && k * 2 <= n)
    {
        int j = 2 * k;
        if (j < n && a[j] < a[j + 1])
            j = 2 * k + 1;

        if (a[j] < v)
            heap = true;
        else
        {
            a[k] = a[j];
            k = j;
        }
    }
    a[k] = v;
}

void heapify(int a[], int n)
{
    for (int i = n / 2; i > 0; i--)
        sink(a, n, i);
}

void heapsort(int a[], int n)
{
    heapify(a, n);
    print("Heapified: ", a, n);
    for (int i = n; i > 1; i--)
    {
        swap(a[1], a[i]);
        sink(a, i - 1, 1);
        print("Index-"+to_string(i)+": ", a, n);
    }
}

int main()
{
    const int N = 6;
    int arr[N+1] = { 0, 2, 9, 7, 6, 5, 8 };
    print("Unsorted: ", arr, N);
    heapsort(arr, N);
    print("Sorted: ", arr, N);
}
