/*
Priority Queues demonstrated on finding points closer to (or further from) the origin. 
Created on Tue Apr 12 12:19:11 2022
@author: Dr. Olcay Kursun, Spring 2022, AUM Dept. of Computer Science
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <time.h>

using namespace std;

class Point2D {
private:
    double x, y;
public:
    Point2D(double x, double y) : x(x), y(y) {};
    double distToOrigin() const { return sqrt(x * x + y * y); };
    friend ostream& operator<<(ostream& out, const Point2D& p);
    bool operator<(const Point2D& p2) const;
};

bool Point2D::operator<(const Point2D& p2) const    //member operator overloading
{ 
    return distToOrigin() > p2.distToOrigin();      //returns true if lhs has lower priority
};

/*
// http://courses.washington.edu/css342/zander/css332/opoverload.html
bool operator<(const Point2D& p1, const Point2D& p2) //non-member operator overloading is an alternative
{
    cout << p1 << " vs " << p2 << "\n";
    return p1.distToOrigin() > p2.distToOrigin(); 
};
*/

bool operator>(const Point2D& p1, const Point2D& p2)  //expected to give higher priority to further ones
{
    return p1.distToOrigin() < p2.distToOrigin();   //expected to return true if lhs has lower priority
};                                                  //so, it checks lhs must be closer to the origin

ostream& operator<<(ostream& out, const Point2D& p)  //non-member friend function to access the private data members
{
    out << "(" << p.x << "," << p.y << ")";
    return out;
};

class FurtherToOrigin {
public:     //operator() is the one that will be used by comparisons
    //returns true if lhs has lower priority than rhs
    bool operator()(const Point2D& p1, const Point2D& p2) const { return p1 > p2; };
};

class CloserToOrigin {   //returns true if lhs has lower priority than rhs
public:     
    bool operator()(const Point2D& p1, const Point2D& p2) const { return p1.distToOrigin() > p2.distToOrigin(); };
};

template <typename T>
void printQ(string name, priority_queue<Point2D, vector<Point2D>, T> q)   //pass-by-value to preserve the original
{
    cout << name <<" = [ ";
    while (!q.empty())
    {
        cout << q.top() << " ";
        q.pop();
    }
    cout << "]\n";
}

int main()
{
    srand(time(NULL));
    const int N = 5;

    priority_queue<Point2D, vector<Point2D>, CloserToOrigin> q1;
    priority_queue<Point2D, vector<Point2D>, FurtherToOrigin> q2;
    priority_queue<Point2D> q3;  //this one is limited because it simply uses the overloaded operator<

    // We can also use decltype with a lambda function instead of defining a class with operator() as the only function
    auto comp = [](const Point2D& p1, const Point2D& p2) { return p1 > p2; };
    priority_queue<Point2D, vector<Point2D>, decltype(comp) > q4(comp);

    for (int i = 0; i < N; i++)
    {
        Point2D* newPoint = new Point2D(rand() % 20, rand() % 20);
        cout << *newPoint << "\n";
        q1.push(*newPoint);
        q2.push(*newPoint);
        q3.push(*newPoint);
        q4.push(*newPoint);
    }

    printQ("q1 (closer to the origin higher the priority)", q1);
    printQ("q2 (further to the origin higher the priority)", q2);
    printQ("q3 (just use operator<)", q3);
    printQ("q4 (using lambda)", q4);
}
