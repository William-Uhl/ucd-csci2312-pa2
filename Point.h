//
// Created by William Uhl on 9/15/2015.
//

#ifndef UHL_PA2_POINT_H
#define UHL_PA2_POINT_H
#include <iostream>

// Namespace clustering
namespace Clustering {

    class Point {
        //number of dimensions the point has
        int dim;
        //values of the point
        double *values;

    public:

        //constructors
        Point(int);


        // Big three, copy constructor, overloaded operator=, destructor
        Point(const Point &);
        Point &operator=(const Point &);
        ~Point();

        // Accessors & mutators
        int getDims() const { return dim; }
        void setValue(int, double);
        double getValue(int) const;

        // Functions
        double distanceTo(const Point &) const;

        // Overloaded operators

        // Members
        Point &operator*=(double);
        Point &operator/=(double);
        const Point operator*(double) const; // prevent (p1*2) = p2;
        const Point operator/(double) const;

        //overload array [] operator
        double &operator[](int index) { return values[index - 1]; }

        // Friends
        friend Point &operator+=(Point &, const Point &);
        friend Point &operator-=(Point &, const Point &);
        friend const Point operator+(const Point &, const Point &);
        friend const Point operator-(const Point &, const Point &);

        friend bool operator==(const Point &, const Point &);
        friend bool operator!=(const Point &, const Point &);

        friend bool operator<(const Point &, const Point &);
        friend bool operator>(const Point &, const Point &);
        friend bool operator<=(const Point &, const Point &);
        friend bool operator>=(const Point &, const Point &);

        friend std::ostream &operator<<(std::ostream &, const Point &);
        friend std::istream &operator>>(std::istream &, Point &);
    };

}
#endif //UHL_PA2_POINT_H
