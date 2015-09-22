//
// Created by William Uhl on 9/15/2015.
//

#include "Cluster.h"

namespace Clustering {
//Copy constructor
    Clustering::Cluster::Cluster(const Clustering::Cluster &inputCluster) {
        size = inputCluster.size;

        if (inputCluster.points == nullptr)
            points = nullptr;
        else {

        }
    }

//overloaded operator=
//Clustering::Cluster &Clustering::Cluster::operator=(const Clustering::Cluster &cluster) {
    //return <#initializer#>;
//}

//destructor
    Clustering::Cluster::~Cluster() {

    }

//function add a point
    void Clustering::Cluster::add(Clustering::PointPtr const &ptr) {


    }

//function remove a point
//Clustering::PointPtr const &Clustering::Cluster::remove(Clustering::PointPtr const &ptr) {
    //  return <#initializer#>;
//}

//overload operator<<
//std::ostream &operator<<(std::ostream &ostream, const Clustering::Cluster &cluster) {
    //return <#initializer#>;
//}

//overload operator>>
//std::istream &operator>>(std::istream &istream, Clustering::Cluster &cluster) {
    //return <#initializer#>;
//}

//overload operator==
    bool operator==(const Clustering::Cluster &lhs, const Clustering::Cluster &rhs) {
        return false;
    }

//overload operator+=
//Clustering::Cluster &Clustering::Cluster::operator+=(const Clustering::Cluster &rhs) {
    //return <#initializer#>;
//}

//overload operator-=
//Clustering::Cluster &Clustering::Cluster::operator-=(const Clustering::Cluster &rhs) {
    //return <#initializer#>;
//}

//overload operator+=
//Clustering::Cluster &Clustering::Cluster::operator+=(const Clustering::Point &rhs) {
    //return <#initializer#>;
//}

//overload operator-=
//Clustering::Cluster &Clustering::Cluster::operator-=(const Clustering::Point &rhs) {
    //return <#initializer#>;
//}

//overload operator+ with two clusters
//const Clustering::Cluster operator+(const Clustering::Cluster &lhs, const Clustering::Cluster &rhs) {
    // return Clustering::Cluster();
//}

//overload operator- with two clusters
//const Clustering::Cluster operator-(const Clustering::Cluster &lhs, const Clustering::Cluster &rhs) {
    //return Clustering::Cluster();
//}

//overload operator+ with a cluster and a point
    const Clustering::Cluster operator+(const Clustering::Cluster &lhs, Clustering::PointPtr const &rhs) {
        return Clustering::Cluster();
    }

//overload operator- with a cluster and a point
    const Clustering::Cluster operator-(const Clustering::Cluster &lhs, Clustering::PointPtr const &rhs) {
        return Clustering::Cluster();
    }
}
