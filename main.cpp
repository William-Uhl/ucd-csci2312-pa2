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
    std::cout << p << std::endl;
    std::cout << "This is P" << std::endl;
    std::cout << p << std::endl;

    Point p2(p);
    p2 *= 5;
    std::cout << "This is P2" << std::endl;
    std::cout << p2 << std::endl;

    Point p3 = p2 - p;
    std::cout << "This is P3" << std::endl;
    std::cout << p3 << std::endl;


    Point p4 = p * 2;
    std::cout << "This is P4" << std::endl;
    std::cout << p4 << std::endl;

    Point p5 = p2 / 2;
    std::cout << "This is P5" << std::endl;
    std::cout << p5 << std::endl;

    Point p6(7);
    std::cout << "This is P6" << std::endl;
    std::cout << p6 << std::endl;
    double dist = p4.distanceTo(p5);
    std::cout << dist << std::endl;

    std::cout << "Cluster testing---------------" << std::endl;

    Point pc(3);
    pc.setValue(0,1);
    pc.setValue(1,2);
    pc.setValue(2,3);

    Point pc2(pc);
    pc2 *=2;
    Point pc3 = pc;
    pc3 *= 3;

    std::cout << pc << std::endl << pc2 << std::endl << pc3 <<std::endl << std::endl;

    //add and cout work
    Cluster c;
    c.add(&pc);
    c.add(&pc2);
    c.add(&pc3);
    std::cout << c;  //should print
    std::cout << "next test" << std::endl;
    c.remove(&p3);
    std::cout << c;

    //test bool operators: == works,
    Cluster c2;
    c2.add(&p3);
    c2.add(&p4);
    c2.add(&p5);
    if(c2 == c)
        std::cout << "Clusters are equal" << std::endl;
    else
        std::cout << "Clusters are not equal" << std::endl;
    std::cout << "next test is addition" << std::endl;


    //test addition constructor appears working
    Cluster c3;
    c3.add(&pc);
    Cluster c4;
    c4.add(&pc2);
    Cluster c5 = c4 + c3;
    std::cout << c5;
    std::cout <<"next test is subtraction" << std::endl;

    //test subtraction does not work
    Cluster c6 = c5 - c4;
    std::cout << c6;
    std::cout << "next test is copy constructor" << std::endl;

    //test copy constructor
    Cluster cempty;
    Cluster c7(c);
    std::cout << c7;
    std::cout << "next test is assignment operator" << std::endl;

    //test assignment operator
    Cluster c8 = c7;
    std::cout << c8;
    std::cout << "next test remove function" << std::endl;

    //test remove function
    c8.remove(&pc3);
    std::cout << c8;
    std::cout << "next test " << std::endl;
    return 0;
}
