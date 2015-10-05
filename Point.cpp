//
// Created by Tres on 9/15/2015.
//

#include <math.h>
#include <assert.h>
#include "Point.h"
using namespace std;

namespace Clustering {
//constructor
   Point::Point(int dimensions) {
        if (dimensions == 0)
            dimensions = 2; //reset dimensions to prevent a dimensionless point
        dim = dimensions;
        values = new double[dim];
        for (int i = 0; i < dim; i++)
            values[i] = 0.0;
    }

//copy constructor
    Point::Point(const Point &rhs) {
        dim = rhs.dim;
        values = new double[dim];
        for (int i = 0; i < dim; i++)
            values[i] = rhs.values[i];

    }

//overloaded operator=
    Point &Point::operator=(const Point &rhs) {
        if (this == &rhs)
            return *this;  //prevent self assignment
        else {
            dim = rhs.dim;
            values = new double[dim];
            for (int i = 0; i < rhs.dim; i++)
                values[i] = rhs.getValue(i);
        }
        return *this;
    }

//destructor
    Point::~Point() {

        delete[] values;
    }

//get the points value
    double Point::getValue(int dimension) const {
        //checks to make sure input is of a valid dimension for the point
        if (dimension >= 1 && dimension <= dim)
            return values[dimension - 1];
        return 0;
    }

//set the value of the point
    void Point::setValue(int i, double input) {
        values[i] = input;
    }

//function gets the distance between points
    double Point::distanceTo(const Point &other) const {
        //if dimensions are not the same return nothing
        if (other.dim == dim) {
            double sum = 0;
            for (int i = 0; i < dim; i++) {
                double difference = values[i] - other.values[i];
                sum += difference * difference;
            }
            return sqrt(sum);
        }
        return 0;
    }

//overload operator*=
    Point& Point::operator*=(double d) {
        for (int i = 0; i < dim; i++)
            values[i] = values[i]* d;
        return *this;
    }

//overload operator/=
    Point &Point::operator/=(double d) {
        assert(d != 0.0);
        for (int i = 0; i < dim; i++)
            values[i] /= d;
        return *this;
    }

//overload operator*
    const Point Point::operator*(double d) const {
        for (int i = 0; i < dim; i++)
            values[i] *= d;
        return *this;

    }


//overload operator/
    const Point Point::operator/(double d) const {
        assert(d != 0.0);
        for (int i = 0; i < dim; i++)
            values[i] /= d;
        return *this;

    }

//overload operator+=
    Point &operator+=(Point &lhs, const Point &rhs) {
        if (&lhs == &rhs) {
            return lhs *= 2;
        }
        else if (lhs.dim == rhs.dim) {
            for (int i = 0; i < lhs.dim; i++)
                lhs.values[i] += rhs.values[i];
            return lhs;
        }
        else {
            //if dimensions not the same return original point
            cout << "Dimensions do not match could not add" << endl;
            return lhs;
        }
    }

//overload operator-=
   Point &operator-=(Point &lhs, const Point &rhs) {
        if (lhs.dim == rhs.dim) {
            for (int i = 0; i < lhs.dim; i++)
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
    const Point operator+(const Point &lhs, const Point &rhs) {
        if (lhs.dim == rhs.dim) {
            Point newPoint(lhs);
            for (int i = 0; i < lhs.dim; i++)
                newPoint.values[i] += rhs.values[i];
            return newPoint;
        }
        else {
            //if dimensions not the same return original point
            cout << "Dimensions do not match could not add" << endl;
            return 0;
        }

    }

//overload operator-
    const Point operator-(const Point &lhs, const Point &rhs) {
        if (lhs.dim == rhs.dim) {
            Point newPoint(lhs);
            for (int i = 0; i < lhs.dim; i++)
                newPoint.values[i] -= rhs.values[i];
            return newPoint;
        }
        else {
            //if dimensions not the same return original point
            cout << "Dimensions do not match could not subtract" << endl;
            return 0;
        }

    }

//overload operator==
    bool operator==(const Point &lhs, const Point &rhs) {
        if (lhs.dim != rhs.dim)
            return false;
        bool answer = false;

        for (int i = 0; i < lhs.dim; i++) {
            if (lhs.values[i] == rhs.values[i])
                answer = true;
            else answer = false;
        }
        return answer;

    }

//overload operator!=
    bool operator!=(const Point &lhs, const Point &rhs) {
        if (lhs.dim != rhs.dim)
            return true;
        bool answer = false;
        for (int i = 0; i < lhs.dim; i++) {
            if (lhs.values[i] != rhs.values[i])
                answer = true;
            else answer = false;
        }
        return answer;
    }

// CONVENTION: MORE DIMENSIONS MEANS POINT IS GREATER

//overload operator<
    bool operator<(const Point &lhs, const Point &rhs) {
        if (lhs.dim < rhs.dim)
            return true;
        bool answer = false;

        for (int i = 0; i < lhs.dim; i++) {
            if (lhs.values[i] < rhs.values[i])
                answer = true;
            else answer = false;
        }
        return answer;
    }

//overload operator>
    bool operator>(const Point &lhs, const Point &rhs) {
        if (lhs.dim > rhs.dim)
            return true;
        bool answer = false;
        for (int i = 0; i < lhs.dim; i++) {
            if (lhs.values[i] > rhs.values[i])
                answer = true;
            else answer = false;
        }
        return answer;
    }

//overload operator<=
    bool operator<=(const Point &lhs, const Point &rhs) {
        if (lhs.dim <= rhs.dim)
            return true;
        bool answer = false;
        for (int i = 0; i < lhs.dim; i++) {
            if (lhs.values[i] <= rhs.values[i])
                answer = true;
            else answer = false;
        }
        return answer;
    }

//overload operator>=
    bool operator>=(const Point &lhs, const Point &rhs) {
        if (lhs.dim >= rhs.dim)
            return true;
        bool answer = false;
        for (int i = 0; i < lhs.dim; i++) {
            if (lhs.values[i] >= rhs.values[i])
                answer = true;
            else
                answer = false;
        }
        return answer;
    }

//overload operator<<
    std::ostream &operator<<(std::ostream &os, const Point &point) {

        for (int i = 0; i < point.dim -1; i++)
            os << point.values[i] << ", ";
        os << point.values[point.dim - 1] ;

        return os;
    }

//overload operator>>
    std::istream &operator>>(std::istream &istream, Point &point) {
        for (int i = 0; i < point.dim; i++)
            istream >> point.values[i];
        return istream;
    }
}
