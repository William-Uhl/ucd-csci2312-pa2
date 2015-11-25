//
// Created by William Uhl on 9/15/2015.
//

#ifndef UHL_PA2_POINT_H
#define UHL_PA2_POINT_H
#include <iostream>
#include <vector>

// Namespace clustering
namespace Clustering {
    template <typename T, int dim>
    class Point {
        //number of dimensions the point has
        int __dim;
        //values of the point
        std::vector<T> values;
        int id;
    public:

        //PA4 new
        void genID();
        int getID() const {return id;}
        //new stuff for PA3
        static const char POINT_VALUE_DELIM;

        //constructors
        Point();


        // Big three, copy constructor, overloaded operator=, destructor
        Point(const Point<T,dim> &);
        Point &operator=(const Point<T,dim> &);
        ~Point();

        // Accessors & mutators
        int getDims() const { return __dim; }
        void setValue(int, T);
        double getValue(int) const;

        // Functions
        double distanceTo(const Point<T,dim> &) const;

        // Overloaded operators

        // Members
        Point &operator*=(double);
        Point &operator/=(double);
        const Point operator*(double) const; // still need to prevent (p1*2) = p2;
        const Point operator/(double) const;

        //overload array [] operator
        T &operator[](int index) { return values[index - 1]; }

        // Friends
        template <typename S, int _dim>
        friend Point<S,_dim> &operator+=(Point<S,_dim> &, const Point<S,_dim> &);

        template <typename S, int _dim>
        friend Point<S,_dim> &operator-=(Point<S,_dim> &, const Point<S,_dim> &);

        template <typename S, int _dim>
        friend const Point<S,_dim> operator+(const Point<S,_dim> &, const Point<S,_dim> &);

        template <typename S, int _dim>
        friend const Point<S,_dim> operator-(const Point<S,_dim> &, const Point<S,_dim> &);

        template <typename S, int _dim>
        friend bool operator==(const Point<S,_dim> &, const Point<S,_dim> &);

        template <typename S, int _dim>
        friend bool operator!=(const Point<S,_dim> &, const Point<S,_dim> &);

        template <typename S, int _dim>
        friend bool operator<(const Point<S,_dim> &, const Point<S,_dim> &);

        template <typename S, int _dim>
        friend bool operator>(const Point<S,_dim> &, const Point<S,_dim> &);

        template <typename S, int _dim>
        friend bool operator<=(const Point<S,_dim> &, const Point<S,_dim> &);

        template <typename S, int _dim>
        friend bool operator>=(const Point<S,_dim> &, const Point<S,_dim> &);

        template <typename S, int _dim>
        friend std::ostream &operator<<(std::ostream &, const Point<S,_dim> &);

        template <typename S, int _dim>
        friend std::istream &operator>>(std::istream &, Point<S,_dim> &);
    };

}
#endif //UHL_PA2_POINT_H
