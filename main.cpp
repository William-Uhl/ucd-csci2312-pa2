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
    std::cout << "This is P" << std::endl;
    std::cout << p;

    Point p2(p);
    std::cout << "This is P2" << std::endl;
    std::cout << p2;

    Point p3 = p2 - p;
    std::cout << "This is P3" << std::endl;
    std::cout << p3;


    Point p4 = p * 2;
    std::cout << "This is P4" << std::endl;
    std::cout << p4;

    Point p5 = p2 / 2;
    std::cout << "This is P5" << std::endl;
    std::cout << p5;

    Point p6(7);
    std::cout << "This is P6" << std::endl;
    std::cout << p6;

    double dist = p4.distanceTo(p5);
    std::cout << dist << std::endl;

    std::cout << "Cluster testing---------------" << std::endl;

    //add and cout work
    Cluster c;
    c.add(&p);
    c.add(&p2);
    c.add(&p3);
    c.add(&p4);
    std::cout << c;

    c.remove(&p4);
    std::cout << c;

    Cluster c2;
    c2.add(&p3);
    c2.add(&p4);
    c2.add(&p5);
    if(c2 == c)
        std::cout << "Clusters are equal" << std::endl;
    else
        std::cout << "Clusters are not equal" << std::endl;


    Cluster c3;
    c3.add(&p);
    Cluster c4;
    c4.add(&p2);

    Cluster c5 = c4 + c3;
    std::cout << c5;


    //subtraction does not work
    Cluster c6 = c5 - c3;
    std::cout << c6;
    

    return 0;
}
