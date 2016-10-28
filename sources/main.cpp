#include <iostream>
#include <cmath>
#include "mylist.h"
#include "sorter.h"

using namespace algo;

class Point {
public:
  Point() { x = 0.0; y = 0.0; }
  Point(double xx,double yy) { x = xx; y = yy; }
  void Print() {
    std::cout<<"("<<x<<","<<y<<")";
  }

  bool operator==(const Point& p) {
    if(p.x == this->x && p.y == this->y) return true;
    return false;
  }
  double getx() const {return x;}
  double gety() const {return y;}
private:
  double x,y;
};

bool compare1(Point* const& arg1, Point* const& arg2) {
  return arg1->getx() < arg2->getx();
}


int main() {

using namespace std;

    /*MyList<Point> mylist;
    for(int i=0; i<=10; ++i)
    mylist.push_back(Point(i,i));

    Point* p = new Point(20,20);
    if(mylist.exist(*p)) cout<<"isnieje"<<endl;
    else cout<<"nie istnieje"<<endl;*/

    /*MyList<unsigned char> chars;
    for(int i=65; i<10000; ++i)
    chars.push_back(i%100);

    while(true) {


    for(int i=0; i<chars.getSize(); ++i) {
      cout<<chars[i];
      if(i%120 == 0) cout<<endl;
    }

    }*/

    const int pnumber = 20;
    MyList<Point*> points;
    for(int i=0; i<pnumber; ++i) {
      points.push_back(new Point(i,i));
    }

    for(int i=0; i<points.getSize(); ++i) {
      points[i]->Print(); cout<<"\n";
    }

    cout<<"\n After desc sorting: \n";
    Qsort<Point*>::sort(points, compare1, 0);

    for(int i=0; i<points.getSize(); ++i) {
      points[i]->Print(); cout<<"\n";
    }


    cout<<"\n Replacing first with the last element: \n";
    points.replace(0, pnumber-1);

    for(int i=0; i<points.getSize(); ++i) {
      points[i]->Print(); cout<<"\n";
    }

    //if element exists
    if(points.exist(points[rand()%pnumber])) {
      cout<<"This element exists\n";
    } else {
      cout<<"This element is not exists\n";
    }

    //Stack class
    cout<<"STACK \n";
    Stack<int> mystack;
    for(int i=0; i<10; ++i) {
      mystack.push(i);
    }

    //print and remove from stack
    while(!mystack.empty()) {
      int value = mystack.top();
      mystack.pop();
      cout<<value<<"\n";
    }

    //Queue class
    cout<<"QUEUE\n";
    Queue<int> queue;
    for(int i=0; i<10; ++i) {
      queue.push(i);
    }

    //print and remove from queue
    while(!queue.empty()) {
      int value = queue.top();
      queue.pop();
      cout<<value<<"\n";
    }

    
  return 0;
}
