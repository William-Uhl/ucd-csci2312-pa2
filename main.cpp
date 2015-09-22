#include <iostream>
#include "Cluster.h"

using namespace Clustering;

int main() {

    //testing

    Point p(3);
    p.setValue(0,1);
    p.setValue(1,2);
    p.setValue(2,3);
    std::cout << p;

    p *= 2;
    std::cout << p;
    p /= 2;
    std::cout << p;

    Point p2(p);
    std::cout << p2;

    Point p3 = p2 - p;
    std::cout << p3;

    //Multiplication fails
   // Point p4 = p * p2;
   // std::cout << p4;



    return 0;
}
