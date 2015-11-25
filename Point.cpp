//
// Created by Tres on 9/15/2015.
//
#include "Point.h"
#include "Cluster.h"
#include <cmath>
#include <assert.h>
#include <cstdlib>
#include<fstream>
#include <sstream>
#include <algorithm>

using namespace std;

namespace Clustering {

//constructor
    template <typename T,int dim>
    Point<T,dim>::Point() {
        genID();
        for (int i = 0; i < dim; i++)
            values.push_back(0);
    }

//copy constructor
    template <typename T,int dim>
    Point<T,dim>::Point(const Point<T,dim> &rhs) {
        id = rhs.getID();
        __dim = rhs.__dim;
        values = rhs.values;

    }

//overloaded operator=
    template <typename T,int dim>
    Point<T,dim> &Point<T,dim>::operator=(const Point<T,dim> &rhs) {
//        if (this == &rhs)
//            return *this;  //prevent self assignment TODO throw error
            __dim = rhs.__dim;
            values = rhs.values;
            id = rhs.getID();
        return *this;
    }

//destructor
    template <typename T,int dim>
    Point<T,dim>::~Point() {

        delete[] values;
    }

//get the points value
    template <typename T,int dim>
    double Point<T,dim>::getValue(int dimension) const {
        //checks to make sure input is of a valid dimension for the point
        if (dimension >= 1 && dimension <= dim) //TODO add exception
            return values[dimension - 1];
        return 0;
    }

//set the value of the point
    template <typename T,int dim>
    void Point<T,dim>::setValue(int i, T input) {
        values[i] = input;
    }

//function gets the distance between points
    template <typename T,int dim>
    double Point<T,dim>::distanceTo(const Point<T,dim> &other) const {
        //if dimensions are not the same return nothing TODO THrow err
        if (other.__dim == __dim) {
            double sum = 0;
            for (int i = 0; i < __dim; i++) {
                double difference = values[i] - other.values[i];
                sum += difference * difference;
            }
            return sqrt(sum);
        }
        return 0;
    }

//overload operator*=
    template <typename T,int dim>
    Point<T,dim> &Point<T,dim>::operator*=(double d) {
        for (int i = 0; i < __dim; i++)
            values[i] = values[i] * d;
        return *this;
    }

//overload operator/=
    template <typename T,int dim>
    Point<T,dim> &Point<T,dim>::operator/=(double d) {
        assert(d != 0.0); //TODO throw exception
        for (int i = 0; i < __dim; i++)
            values[i] /= d;
        return *this;
    }

//overload operator*
    template <typename T,int dim>
    const Point<T,dim> Point<T,dim>::operator*(double d) const {
        for (int i = 0; i < __dim; i++)
            values[i] *= d;
        return *this;

    }


//overload operator/
    template <typename T,int dim>
    const Point<T,dim> Point<T,dim>::operator/(double d) const {
        assert(d != 0.0); //TODO throw exception
        for (int i = 0; i < __dim; i++)
            values[i] /= d;
        return *this;

    }

//overload operator+=
    template <typename T,int dim>
    Point<T,dim> &operator+=(Point<T,dim> &lhs, const Point<T,dim> &rhs) {
        //TODO throw exception for dim mismatch
        if (&lhs == &rhs) {
            return lhs *= 2;
        }
        else{
            for (int i = 0; i < lhs.__dim; i++)
                lhs.values[i] += rhs.values[i];
            return lhs;
        }
    }

//overload operator-=
    template <typename S, int dim>
    Point<S,dim> &operator-=(Point<S,dim> &lhs, const Point<S,dim> &rhs) {
        //TODO throw exception for dim mismatch
        if (lhs.__dim == rhs.__dim) {
            for (int i = 0; i < lhs.__dim; i++)
                lhs.values[i] -= rhs.values[i];
            return lhs;
        }
        else {
            //if dimensions not the same return original point
            cout << "Dimensions do not match could not subtract" << endl;
            return lhs;
        }
    }

//overload operator+
    template <typename S, int dim>
    const Point<S,dim> operator+(const Point<S,dim> &lhs, const Point<S,dim> &rhs) {
        //TODO throw mismatch
        if (lhs.__dim == rhs.__dim) {
            Point<S,dim> newPoint(lhs);
            for (int i = 0; i < lhs.__dim; i++)
                newPoint.values[i] += rhs.values[i];
            return newPoint;
        }

    }

//overload operator-
    template <typename S, int dim>
    const Point<S,dim> operator-(const Point<S,dim> &lhs, const Point<S,dim> &rhs) {
        //TODO throw mismatch
        if (lhs.__dim == rhs.__dim) {
            Point<S, dim> newPoint(lhs);
            for (int i = 0; i < lhs.__dim; i++)
                newPoint.values[i] -= rhs.values[i];
            return newPoint;
        }
    }

//overload operator==
    template <typename S, int dim>
    bool operator==(const Point<S,dim> &lhs, const Point<S,dim> &rhs) {

        if (lhs.__dim != rhs.__dim)
            return false;
        bool answer = false;

        for (int i = 0; i < lhs.__dim; i++) {
            if (lhs.values[i] == rhs.values[i])
                answer = true;
            else answer = false;
        }
        return answer;

    }

//overload operator!=
    template <typename S, int dim>
    bool operator!=(const Point<S,dim> &lhs, const Point<S,dim> &rhs) {
        if (lhs.__dim != rhs.__dim)
            return true;
        bool answer = false;
        for (int i = 0; i < lhs.__dim; i++) {
            if (lhs.values[i] != rhs.values[i])
                answer = true;
            else answer = false;
        }
        return answer;
    }

// CONVENTION: MORE DIMENSIONS MEANS POINT IS GREATER

//overload operator<
    template <typename S, int dim>
    bool operator<(const Point<S,dim> &lhs, const Point<S,dim> &rhs) {
        if (lhs.__dim < rhs.__dim)
            return true;
        bool answer = false;

        for (int i = 0; i < lhs.__dim; i++) {
            if (lhs.values[i] < rhs.values[i])
                answer = true;
            else answer = false;
        }
        return answer;
    }

//overload operator>
    template <typename S, int dim>
    bool operator>(const Point<S,dim> &lhs, const Point<S,dim> &rhs) {
        if (lhs.__dim > rhs.__dim)
            return true;
        bool answer = false;
        for (int i = 0; i < lhs.__dim; i++) {
            if (lhs.values[i] > rhs.values[i])
                answer = true;
            else answer = false;
        }
        return answer;
    }

//overload operator<=
    template <typename S, int dim>
    bool operator<=(const Point<S,dim> &lhs, const Point<S,dim> &rhs) {
        if (lhs.__dim <= rhs.__dim)
            return true;
        bool answer = false;
        for (int i = 0; i < lhs.__dim; i++) {
            if (lhs.values[i] <= rhs.values[i])
                answer = true;
            else answer = false;
        }
        return answer;
    }

//overload operator>=
    template <typename S, int dim>
    bool operator>=(const Point<S,dim> &lhs, const Point<S,dim> &rhs) {
        if (lhs.__dim >= rhs.__dim)
            return true;
        bool answer = false;
        for (int i = 0; i < lhs.__dim; i++) {
            if (lhs.values[i] >= rhs.values[i])
                answer = true;
            else
                answer = false;
        }
        return answer;
    }

//overload operator<<
    template <typename S, int dim>
    std::ostream &operator<<(std::ostream &os, const Point<S,dim> &point) {

        for (int i = 0; i < point.__dim - 1; i++)
            os << point.values[i] << ", ";
        os << point.values[point.__dim - 1];
        os << " : ";
        return os;
    }

//overload operator>>
    template <typename S, int dim>
    std::istream &operator>>(std::istream &istream, Point<S,dim> &point) {
        std::string number;
        double num;
        int dimension = 0;
        static const char DELIMINATOR = ',';

        while (getline(istream,number,DELIMINATOR)) {

            num = atof(number.c_str());
            point.setValue(dimension,num);
            dimension++;
        }
    }

    template <typename T,int dim>
    void Point<T,dim>::genID() {
        static int newid = 1;
        id = newid++;
    }
}
