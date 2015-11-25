//
// Created by William Uhl on 9/15/2015.
//


#include "Cluster.h"
#include <string>
#include <fstream>
#include <sstream>
#include <bits/stl_algo.h>
#include <ctime>

using std::string;

namespace Clustering {

//    unsigned int Cluster::__id = 1;

//Copy constructor works
    template <typename T, int dim>
    Cluster<T,dim>::Cluster(const Cluster<T,dim> &inputCluster) {
        size = inputCluster.size;
        __centroid = inputCluster.__centroid;
        __validCen = false;
        __dims = inputCluster.__dims;
        idGen();
        points = inputCluster.points;
//        if (inputCluster.points == nullptr)
//            points = nullptr;
//        else {
//            //start the new link list
//            LNodePtr curr = inputCluster.points;
//            LNodePtr newNode = new LNode(curr->p,nullptr);
//            points = newNode;
//            curr = curr->next;
//            LNodePtr prev = points;
//
//            //moves down linklist creating new link list
//            while(curr != NULL){
//                LNodePtr newNode = new LNode(curr->p,nullptr);
//                prev->next = newNode;
//                prev = newNode;
//
//                curr = curr->next;
//
//            }
//        }
    }

//overloaded operator= works
template <typename T, int dim>
Cluster<T,dim> &Cluster<T,dim>::operator=(const Cluster<T,dim> &inputCluster) {
        //TODO throw exception to prevent self assignment
//              if (this == &inputCluster)
//            return *this;
        points.clear();
        size = inputCluster.size;
        __centroid = inputCluster.__centroid;
        __validCen = false;
        idGen();

        if (inputCluster.points.empty())
            points = nullptr;
        else
            points = inputCluster.points;
}

//destructor
    template <typename T, int dim>
    Cluster<T,dim>::~Cluster() {
        points.clear();
    }

//function add a point
    template <typename T, int dim>
    void Cluster<T,dim>::add(T const &ptr) {
        bool flag = false;
        if (points.empty()){
            points.push_front(ptr);
        }
//        else if(*(points->p) > *ptr)
//        {
//            newNode->next = points;
//            points = newNode;
//        }
        else{
            auto curr = points.begin();
            auto nex = points.begin();
            nex++;
            if(ptr <= *curr){
                points.push_front(ptr);
            }
            else if (size == 1){
                points.insert_after(curr,ptr);
            }
            else {
                while (nex != points.end()) {
                    if (ptr <= *nex) {
                        points.insert_after(curr,ptr);
                        flag = true;
                        break;
                    }
                    else {
                        curr++;
                        nex++;
                    }
                }
            }
        }
        size++;
        if(!flag)
            points.insert_after(points.end(),ptr);
        this->invalidCentroid();

    }

//function remove a point FIX
    template <typename T, int dim>
     const  T &Cluster<T,dim>::remove(const T &ptr) {

        if (size == 0){
            // TODO throw error no point to remove
        }
        else if(size == 1) {
            if(points.front() == *ptr){
                points.pop_front();
                size--;
                invalidCentroid();
                return ptr;

            }
            else{
                //TODO throw error no matching point
            }
        }
        else {
            //traverse the cluster looking for the point to delete
            bool flag = false;
            auto curr = points.begin();
            auto nex = points.begin();
            nex++;

            while (*nex != ptr && nex!=points.end()) {
                curr++;
                nex++;
            }

                if (*nex == *ptr){
                    points.erase_after(curr);
                    size--;
                    this->invalidCentroid();
                    return ptr;
                }
                else {
                    //TODO throw exception point not found
                }


            return ptr;
        }


}

//overload operator<< works
    template <typename S, int dim>
std::ostream &operator<<(std::ostream &os, const Cluster<S,dim> &cluster) {
        if (cluster.size == 0) {
            os << "Cluster is empty" << std::endl;
            return os;
        }

        auto curr = cluster.points.begin();

        while(curr != cluster.points.end()){
            os << *curr;
            os << cluster.getID() << std::endl;
            curr++;
        }
        return os;
}


//overload operator>>
    template <typename S, int dim>
    std::istream &operator>>(std::istream & inStream, Clustering::Cluster<S,dim> &cluster) {

        std::string input;
        static const char DELIMINATOR = ',';
        while (getline(inStream,input)) {
            int num = std::count(input.begin(),input.end(),DELIMINATOR) + 1;
            if (num != dim){
                //TODO throw error
            }

            S *p;
            p = new S;

            std::stringstream lineStream(input);
            lineStream >> *p;
            cluster.add(*p);
        }
        return inStream;
}

//overload operator== works
    template <typename S, int dim>
    bool operator==(const Cluster<S,dim> &lhs, const Cluster<S,dim> &rhs) {


        if (lhs.size != rhs.size)
            return false;
        if(lhs.size == 0 && rhs.size ==0)
            return true;

        auto leftIt = lhs.points.begin();
        auto rightIt = rhs.points.begin();

        while(leftIt!=lhs.points.end() && rightIt != rhs.points.end()) {
            if (*(leftIt) == *(rightIt)) {
                leftIt++;
                rightIt++;
                }
            else{
                return false;
            }
        }
        return true;

    }

//overload operator+=
    template <typename T, int dim>
Cluster<T,dim> &Cluster<T,dim>::operator+=(const Cluster<T,dim> &rhs) {
        bool same = false;

        auto rightIt = rhs.points.begin();
            while (rightIt != rhs.points.end()) {

                auto leftIt = this->points.begin();
                while (leftIt != this->points.end()) {
                    if (*rightIt == *leftIt) {
                        same = true;
                    }

                    leftIt++;
                }
                if (!same) {
                    this->add(*rightIt);
                    this->size++;
                    this->invalidCentroid();
                }
                rightIt++;
            }
        return *this;
}

//overload operator-=
    template <typename T, int dim>
Cluster<T,dim> &Cluster<T,dim>::operator-=(const Cluster<T,dim> &rhs) {

        bool same = false;

        if(this->size == 0) {
            return *this;
        }

        auto rightIt = rhs.points.begin();

            while (rightIt != rhs.points.end()) {

                auto leftIt = this->points.begin();
                while (leftIt != this->points.end()) {
                    if (*leftIt == *rightIt) {
                        same = true;
                    }
                    leftIt++;

                }
                if (!same) {
                    this->remove(*rightIt);
                    this->size--;
                    this->invalidCentroid();
                }
                rightIt++;
            }


        return *this;
}

//overload operator+=  works
template <typename T, int dim>
Cluster<T,dim> &Cluster<T,dim>::operator+=(const T &rhs) {
        this->add(rhs);
        return *this;

}

//overload operator-=  works
template <typename T, int dim>
Cluster<T,dim> &Cluster<T,dim>::operator-=(const T &rhs) {
    this->remove(rhs);
        return *this;
}

//overload operator+ with two clusters
    template <typename S, int dim>
const Cluster<S,dim> operator+(const Cluster<S,dim> &lhs, const Cluster<S,dim> &rhs) {

        Cluster<S,dim> c(rhs);
        c+=lhs;
        return c;
}

//overload operator- with two clusters
    template <typename S, int dim>
const Cluster<S,dim> operator-(const Cluster<S,dim> &lhs, const Cluster<S,dim> &rhs) {

        Cluster<S,dim> c(lhs);
        c-=rhs;
        return c;
}

//overload operator+ with a cluster and a point WORKS
    template <typename S, int dim>
    const Cluster<S,dim> operator+(const Cluster<S,dim> &lhs, S const &rhs) {

        Cluster<S,dim> newCluster(lhs);
        newCluster.add(rhs);
        return newCluster;

    }

//overload operator- with a cluster and a point WORKS
    template <typename S, int dim>
    const Cluster<S,dim> operator-(const Cluster<S,dim> &lhs, S const &rhs) {
        Cluster<S,dim> newCluster(lhs);
        newCluster.remove(rhs);
        return newCluster;

    }

    template <typename T, int dim>
    void Cluster<T,dim>::setCentroid(const T &point) {
        __centroid = point;
        __validCen = true;
    }

    template <typename T, int dim>
    const T Cluster<T,dim>::getCentroid() {
        return __centroid;
    }

    template <typename T, int dim>
    void Cluster<T,dim>::computeCentroid() {
        if (points.empty())
            __centroid = NULL;  //TODO throw exception
        T cent(__dims);
        auto it = points.begin();
        while (it != points.end()){
            cent += (*it)/size;
            it++;
        }
        this->setCentroid(cent);
        __validCen = true;
    }

    template <typename T, int dim>
    void Cluster<T,dim>::idGen() {
        static unsigned int id = 1;
        __id = id++;

    }

    template <typename T, int dim>
    void Cluster<T,dim>::invalidCentroid() {
        __validCen = false;
    }


    template <typename T, int dim>
    void Cluster<T,dim>::pickPoints(int k, std::vector<T> &pointArray) {
        auto it = this->points.begin();
        int size= this->size;
        int num = size/k;


        for(int i = 0;i<k;i++){
            pointArray.push_back(*it);
            for(int j = 0; j<num; j++)
                it++;

        }

    }

    template <typename T, int dim>
    double Cluster<T,dim>::intraClusterDistance() const {
        auto it = this->points.begin();
        auto it2 = this->points.begin();
        it2++;
        double dist = 0;
        while(it != points.end()){

            while (it2 != points.end()) {
                if(*it != *it2) {
                    int hashID = genHash(it->getID(),it2->getID());
                    if(!(this->distMap.count(hashID))) {
                        double diff = it->distanceTo(*it2);
                        distMap[hashID] = diff;
                        dist = dist + diff;
                    }
                    else
                        dist = dist + distMap[hashID];
                }
                it2++;
            }
            it++;
            it2 = this->points.begin();
            }
}

    template <typename S, int dim>
    double Cluster<S,dim>::interClusterDistance(const Cluster<S,dim> &c1, const Cluster<S,dim> &c2) {
        auto it1 = c1.points.begin();
        auto it2 = c2.points.begin();

        double dist = 0;

        while (it1 != c1.points.end()) {

            while (it2 != c2.points.end()) {
                if (*it1 != *it2) {
                    int hashID = genHash(it1->getID(), it2->getID());
                    if (!(this->distMap.count(hashID))) {
                        double diff = it1->distanceTo(*it2);
                        distMap[hashID] = diff;
                        dist = dist + diff;
                    }
                    else
                        dist = dist + distMap[hashID];
                }
                it2++;

            }
            it1++;
            it2 = c2.points.begin();
        }
        return dist;
    }

    template <typename T, int dim>
    int Cluster<T,dim>::getClusterEdges() {
        return((this->size)*((this->size) - 1)/2);

    }

    template <typename T, int dim>
    double interClusterEdges(const Cluster<T,dim> &c1, const Cluster<T,dim> &c2) {
        double size1 = c1.size;
        double size2 = c2.size;
        double edges = (size1 *(size2 - 1))/2;
        return edges;

    }

    template <typename T, int dim>
    int Cluster<T,dim>::genHash(int i, int i1) const {
        //cantors functions
        if(i > i1){
            int hash = .5*((i + i1)*(i+i1+1))+i1;
            return hash;
        }
        else{
            int hash = .5*((i1 + i)*(i1+i+1))+i;
            return hash;
        }
    }
}
