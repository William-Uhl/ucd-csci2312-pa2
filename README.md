# ucd-csci2312-pa2
This program is for University of Colorado Denver class CSCI2312 in the fall semester of 2015.
Created by William Uhl
9/15/2015

Intro:
The program contains two classes, a point class and a cluster class.  Following the guidelines of the assignment the point class 
and cluster class have different member variables and functions.  Almost every operator is also overloaded.  This assinment
focuses of the implementation of classes in C++, dynamically allocating memory, and overloading operators.

Point Class:
The point class is set up to make points that can be of any dimension, for example in three dimensions a point would be (x,y,z).
The class will dynamically allocate the memory for points and clean up the memory once it is done being used.  Many of the common
operators will be overloaded so that points can be compared to each other, i.e. <,==, and others.  Also the points can be used
with simple arithmatic that makes sense such as the +,- and *= operators.

Cluster Class:
The cluster class will have similar processes to the point class but the cluster class will hold an arbitrary amount of points.
Similar to the point class the cluster class will overload many of the operators to help in comparisions or class arithmatic.
The cluster class will also use dynamically allocated link lists to organize the information contained in the cluster. 

Compiler:
The compiler used for this program is MinGW.
