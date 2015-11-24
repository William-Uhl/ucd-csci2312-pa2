//
// Created by Tres on 9/15/2015.
//

#ifndef UHL_PA2_CLUSTER_H
#define UHL_PA2_CLUSTER_H



#include "Point.h"
#include <forward_list>
#include <unordered_map>

namespace Clustering {
    template <typename T, int dim>
    class Cluster {
    private:
        unsigned int __id;
        int __dims;
        T __centroid;
        int size;
        std::forward_list<T> points;
        bool __validCen;
        static std::unordered_map<int, double> distMap;

    public:

        //hashmap function
        int genHash( int, int) const;

        //New centroid function
        void setCentroid(const T &);
        bool centroidValid() { return __validCen;}
        const T getCentroid();
        void computeCentroid();
        void invalidCentroid();

        //id for cluster
        void idGen();
        unsigned int getID() const {return __id;}


        // for use with operator<<
        static const char POINT_CLUSTER_ID_DELIM;


        //New cluster functionality
        void setDim(const int dim);
        void pickPoints(int k, std::vector<T> &);
        int getSize() {return size;}
        double intraClusterDistance() const;
        double interClusterDistance(const Cluster<T,dim> &c1, const Cluster<T,dim> &c2);
        int getClusterEdges();

        template <typename S, int _dim>
        friend double interClusterEdges(const Cluster<S,dim> &c1, const Cluster<S,dim> &c2);

        //default constructor
        Cluster() : size(0), points(nullptr), __centroid(0) {};

        // The big three: cpy ctor, overloaded operator=, dtor
        Cluster(const Cluster &);
        Cluster &operator=(const Cluster &);
        ~Cluster();

        //remove and add a point
        void add(const T &);
        const T &remove(const T &);

        // Overloaded operators

        // IO
        template <typename S, int _dim>
        friend std::ostream &operator<<(std::ostream &, const Cluster<S,_dim> &);

        template <typename S, int _dim>
        friend std::istream &operator>>(std::istream &, Cluster<S,_dim> &);

        // Set-preserving operators (do not duplicate points in the space)
        // - Friends
        template <typename S, int _dim>
        friend bool operator==(const Cluster<S,_dim> &lhs, const Cluster<T,_dim> &rhs);

        // - Members
        Cluster<T,dim> &operator+=(const Cluster<T,dim> &rhs); // union
        Cluster<T,dim> &operator-=(const Cluster<T,dim> &rhs); // (asymmetric) difference

        Cluster<T,dim> &operator+=(const T &rhs);  // add point
        Cluster<T,dim> &operator-=(const T &rhs); // remove point

        // Set-destructive operators (duplicate points in the space)
        // - Friends
        template <typename S, int _dim>
        friend const Cluster<S,_dim> operator+(const Cluster<S,_dim> &lhs, const Cluster<S,_dim> &rhs);

        template <typename S, int _dim>
        friend const Cluster<S,_dim> operator-(const Cluster<S,_dim> &lhs, const Cluster<S,_dim> &rhs);

        template <typename S, int _dim>
        friend const Cluster<S,_dim> operator+(const Cluster<S,_dim> &lhs, const S &rhs);

        template <typename S, int _dim>
        friend const Cluster<S,_dim> operator-(const Cluster<S,_dim> &lhs, const S &rhs);


        //Inner class Move
        class Move{
                private:
                    T ptr;
                    Cluster<T,dim> *from, *to;
                public:
                    Move(T &ptr,Cluster<T,dim> *from, Cluster<T,dim> *to) :
                    ptr(ptr), from(from), to(to)
                    {}
                    void perform() {to->add(from->remove(ptr));};


        };

        T &operator[](int i){
            T curr = this->points;
            for(int j = 0; j<i; j++){
                if (curr->next != NULL)
                    curr = curr->next;
            }
        }
        //Kmeans
        class Kmeans{
        private:


        public:
            static constexpr double SCORE_DIFF_THRESHOLD = .001;
            double computeClusteringScore(int k, Cluster<T,dim> *cluster);
            void runKmeans(int k,int dim);


        };

    };

}
#endif //UHL_PA2_CLUSTER_H
