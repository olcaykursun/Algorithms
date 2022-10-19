/*
Priority Queues demonstration on 2D and 3D points.
Created on Mon Oct 17 11:19:00 2022
@author: Dr. Olcay Kursun, Fall 2022, AUM Dept. of Computer Science
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
    double getX() const { return x; };
    friend ostream& operator<<(ostream& out, const Point2D& p);
    bool operator<(const Point2D& p2) const;
};

class Point3D : public Point2D
{
private:
    double z;
public:
    Point3D(double x, double y, double z) : Point2D(x,y), z(z) {};
    friend ostream& operator<<(ostream& out, const Point3D& p);
};

bool Point2D::operator<(const Point2D& p2) const    //member operator overloading
{
    return y > p2.y;      //returns true if lhs has lower priority
};

ostream& operator<<(ostream& out, const Point2D& p)  //non-member friend function to access the private data members
{
    out << p.x << "," << p.y;
    return out;
};

class IsLowerX {   //returns true if lhs has lower priority than rhs
public:
    bool operator()(const Point2D& p1, const Point2D& p2) const { return p1.getX() > p2.getX(); };
};


//Works for both 2D and 3D
template <typename T, typename C>
void printQ(string name, priority_queue<T, vector<T>, C> q)   //pass-by-value to preserve the original
{
    cout << name <<" = [ ";
    while (!q.empty())
    {
        cout << "(" << q.top() << ") ";
        q.pop();
    }
    cout << "]\n";
}


ostream& operator<<(ostream& out, const Point3D& p)  //non-member friend function to access the private data members
{
    out << (const Point2D&)p << "," << p.z;
    return out;
};


int main()
{
    srand(time(NULL));
    const int N = 5;

    priority_queue<Point2D, vector<Point2D>, IsLowerX> q1;  //this is more flexible, just choose your comparator function
    priority_queue<Point2D> q2;  //this one is limited because it simply uses the overloaded operator< sorting by y-coord

    for (int i = 0; i < N; i++)
    {
        Point2D* newPoint = new Point2D(rand() % 20, rand() % 20);
        cout << *newPoint << "\n";
        q1.push(*newPoint);
        q2.push(*newPoint);
    }

    printQ("q1 (left to right sorted points)", q1);
    printQ("q2 (just use operator< for in increasing order of y)", q2);
    
    Point3D* point1 = new Point3D(3,4,25);
    Point3D* point2 = new Point3D(2,2,5);
    Point3D* point3 = new Point3D(1,6,15);
    priority_queue<Point3D> q_for3D;
    q_for3D.push(*point1);
    q_for3D.push(*point2);
    q_for3D.push(*point3);
    printQ("point3D queue, sorted by y-coord", q_for3D);
    
    //Practice: How do we sort it by x-coord using IsLowerX?
}
