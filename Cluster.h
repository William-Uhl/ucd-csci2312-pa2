//
// Created by Tres on 9/15/2015.
//

#ifndef UHL_PA2_CLUSTER_H
#define UHL_PA2_CLUSTER_H



#include "Point.h"

namespace Clustering {

    typedef Point *PointPtr;
    typedef struct LNode *LNodePtr;

    struct LNode {
        PointPtr p;
        LNodePtr next;

        //LNode constructor
        LNode(PointPtr,  LNodePtr);

    };

    class Cluster {
    private:

        unsigned int __id;

        int __dims;
        PointPtr __centroid;
        int size;
        LNodePtr points;
        bool __validCen;

    public:

        //New centroid function
        void setCentroid(const Point &);
        bool centroidValid() { return __validCen;}
        const Point getCentroid();
        void computeCentroid();
        void invalidCentroid();

        //id for cluster
        void idGen();
        unsigned int getID() const {return __id;}


        // for use with operator<<
        static const char POINT_CLUSTER_ID_DELIM;


        //New cluster functionality
        void setDim(const int dim);
        void pickPoints(int k, PointPtr *pointArray);
        int getSize() {return size;}
        double intraClusterDistance() const;
        double interClusterDistance(const Cluster &c1, const Cluster &c2);
        int getClusterEdges();
        friend double interClusterEdges(const Cluster &c1, const Cluster &c2);
        Point getPoint(int num) const;

        //default constructor
        Cluster() : size(0), points(nullptr), __centroid(0) {};

        // The big three: cpy ctor, overloaded operator=, dtor
        Cluster(const Cluster &);
        Cluster &operator=(const Cluster &);
        ~Cluster();

        // Set functions: They allow calling c1.add(c2.remove(p));
        void add(const PointPtr &);
        void del();
        void ins(LNodePtr,LNodePtr,LNodePtr);
        void cpy(LNodePtr);

        const PointPtr &remove(const PointPtr &);

        // Overloaded operators

        // IO
        friend std::ostream &operator<<(std::ostream &, const Cluster &);
        friend std::istream &operator>>(std::istream &, Cluster &);

        // Set-preserving operators (do not duplicate points in the space)
        // - Friends
        friend bool operator==(const Cluster &lhs, const Cluster &rhs);

        // - Members
        Cluster &operator+=(const Cluster &rhs); // union
        Cluster &operator-=(const Cluster &rhs); // (asymmetric) difference

        Cluster &operator+=(const Point &rhs);  // add point
        Cluster &operator-=(const Point &rhs); // remove point

        // Set-destructive operators (duplicate points in the space)
        // - Friends
        friend const Cluster operator+(const Cluster &lhs, const Cluster &rhs);
        friend const Cluster operator-(const Cluster &lhs, const Cluster &rhs);

        friend const Cluster operator+(const Cluster &lhs, const PointPtr &rhs);
        friend const Cluster operator-(const Cluster &lhs, const PointPtr &rhs);


        //Inner class Move
        class Move{
                private:
                    PointPtr ptr;
                    Cluster *from, *to;
                public:
                    Move(PointPtr &ptr,Cluster *from, Cluster *to) :
                    ptr(ptr), from(from), to(to)
                    {}
                    void perform() {to->add(from->remove(ptr));};


        };

        LNodePtr operator[](int i){
            LNodePtr curr = this->points;
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
            double computeClusteringScore(int k, Cluster *cluster);
            void runKmeans(int k,int dim);


        };

    };

}
#endif //UHL_PA2_CLUSTER_H
