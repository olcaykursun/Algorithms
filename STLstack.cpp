//  reverseStack and printStack bottom to top
//     but really if you need printing of a stack, maybe you should use something else
//  Created by Olcay Kursun on 2/9/23.

#include <iostream>
#include <stack>

//Reverses a stack
void reverseStack(std::stack<int>& S)
{
    std::stack<int> tempStack;
    while (!S.empty())
    {
        tempStack.push(S.top());
        S.pop();
    }
    S = tempStack;
}

//Print bottom of the stack first and print the top as the last
void printStack(std::stack<int> S)
{
    reverseStack(S);
    while (!S.empty())
    {
        std::cout << S.top();
        S.pop();
    }
    std::cout << std::endl;
}

//Don't try this at home (we can take a look at the lines 34-50 at school
//it's just trying to show you there is a container inside the stack class
template <class T>
class _stack : public std::stack<T>
{
public:
    void print() const   //one const leads to another we end up here
    {
        for (const auto& elem : this->c)    //accessing the protected container
            std::cout << elem;
        std::cout << std::endl;
    }
};

void printStack2(const std::stack<int>& S)
{
    auto s = reinterpret_cast<const _stack<int>*>(&S);
    s->print();
}

int main()
{
    std::stack<int> myStack;
    myStack.push(5);
    myStack.push(6);
    myStack.push(7);
    myStack.push(9);
    myStack.pop();
    myStack.push(8);
    
    printStack(myStack);
    reverseStack(myStack);
    printStack(myStack);
    printStack2(myStack);

    return 0;
}
