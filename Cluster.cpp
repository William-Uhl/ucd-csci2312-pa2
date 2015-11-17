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

    //For PA3
    const char Cluster::POINT_CLUSTER_ID_DELIM = ':';

//    unsigned int Cluster::__id = 1;

//Copy constructor works
    Cluster::Cluster(const Cluster &inputCluster) {
        size = inputCluster.size;
        __centroid = inputCluster.__centroid;
        __validCen = true;
        idGen();
        if (inputCluster.points == nullptr)
            points = nullptr;
        else {
            //start the new link list
            LNodePtr curr = inputCluster.points;
            LNodePtr newNode = new LNode(curr->p,nullptr);
            points = newNode;
            curr = curr->next;
            LNodePtr prev = points;

            //moves down linklist creating new link list
            while(curr != NULL){
                LNodePtr newNode = new LNode(curr->p,nullptr);
                prev->next = newNode;
                prev = newNode;

                curr = curr->next;

            }

        }
    }

//overloaded operator= works
Cluster &Cluster::operator=(const Cluster &inputCluster) {
        if (this == &inputCluster)
            return *this;

        size = inputCluster.size;
        __centroid = inputCluster.__centroid;
        __validCen = true;
        idGen();

        if (inputCluster.points == nullptr)
            points = nullptr;
        else {
            //start the new link list
            LNodePtr curr = inputCluster.points;
            LNodePtr newNode = new LNode(curr->p,nullptr);
            points = newNode;
            curr = curr->next;
            LNodePtr prev = points;

            //moves down linklist creating new link list
            while(curr != NULL){
                LNodePtr newNode = new LNode(curr->p,nullptr);
                prev->next = newNode;
                prev = newNode;

                curr = curr->next;

            }

        }
}

//destructor
    Cluster::~Cluster() {
        LNodePtr delptr= points;
        while(delptr != NULL){
            LNodePtr forward = delptr->next;
            delete delptr;
            delptr = forward;
        }
    }

//function add a point works
    void Cluster::add(PointPtr const &ptr) {
        LNodePtr newNode = new LNode(ptr,nullptr);
        if (points == NULL){
            points = newNode;
        }
        else if(*(points->p) > *ptr)
        {
            newNode->next = points;
            points = newNode;
        }
        else{
            LNodePtr curr = points;
            LNodePtr nex = points->next;

            while(true){
                if(nex == nullptr || *(nex->p) > *ptr){
                    curr->next = newNode;
                    newNode->next = nex;
                    break;
                }
                else{
                    curr = nex;
                    nex = nex->next;
                }
            }
        }
        size++;

    }

//function remove a point works
PointPtr const &Cluster::remove(PointPtr const &ptr) {

        if (size == 0){
            std::cout << "Cluster is empty nothing to remove" << std::endl;
            return ptr;
        }
        else if(size == 1) {
            if(*(points->p) == *ptr){
                points = nullptr;
                size--;
                return ptr;

            }
            else{
                std::cout << "No point matches" << std::endl;
                return ptr;
            }
        }
        else {
            //traverse the cluster looking for the point to delete
            LNodePtr prev = points;
            LNodePtr curr = points->next;


            while (curr != nullptr) {
                if (*(curr->p) == *ptr){

                    prev->next = curr->next;
                    delete curr;
                    size--;
                    return ptr;
                }
                else {
                    prev = curr;
                    curr = curr->next;

                }
            }

            return ptr;
        }


}

//overload operator<< works
std::ostream &operator<<(std::ostream &os, const Cluster &cluster) {
        if (cluster.size == 0) {
            os << "Cluster is empty" << std::endl;
            return os;
        }


        LNodePtr current = cluster.points;
        //int counter =1;
        for( ; current != nullptr; current = current->next) {
           // os << "Point " << counter++ << std::endl;
            os << *(current->p) <<
            cluster.getID() << std::endl;

        }

        return os;


}


//overload operator>>
std::istream &operator>>(std::istream & inStream, Cluster &cluster) {

        std::string input;
        static const char DELIMINATOR = ',';
        while (getline(inStream,input)) {
            int num = std::count(input.begin(),input.end(),DELIMINATOR) + 1;

            cluster.setDim(num);
            PointPtr p;
            p = new Point(num);

            std::stringstream lineStream(input);
            lineStream >> *p;
            cluster.add(p);
        }
}

//overload operator== works
    bool operator==(const Cluster &lhs, const Cluster &rhs) {


        if (lhs.size != rhs.size)
            return false;
        if(lhs.size == 0 && rhs.size ==0)
            return true;

        LNodePtr left = lhs.points;
        LNodePtr right = rhs.points;

        while(left != nullptr && right != nullptr) {
            if (*(left->p) == *(right->p)) {
                left = left->next;
                right = right->next;
                }
            else{
                return false;
            }
        }
        return true;

    }

//overload operator+=    Maybe WORK
Cluster &Cluster::operator+=(const Cluster &rhs) {


        LNodePtr left = this->points;
        LNodePtr right = rhs.points;

        bool same = false;

            while (left != nullptr) {

                while (right != nullptr) {
                    if (left->p == right->p) {

                        same = true;
                    }

                    right = right->next;
                }
                if (same == false) {
                    this->add(left->p);
                    this->size++;
                }
                left = left->next;
            }
        return *this;
}

//overload operator-=    Maybe WORK
Cluster &Cluster::operator-=(const Cluster &rhs) {

        LNodePtr left = this->points;
        LNodePtr right = rhs.points;

        bool same = false;

        if(this->size == 0) {
            return *this;
        }

        else{

            while (left != nullptr) {

                while (right != nullptr) {
                    if (left->p == right->p) {

                        same = true;
                    }
                    right = right->next;

                }
                if (same == true) {
                    this->remove(left->p);
                    this->size--;
                }
                left = left->next;
            }
        }

        return *this;
}

//overload operator+=  works
Cluster &Cluster::operator+=(const Point &rhs) {

        PointPtr n = new Point(rhs);
        this->add(n);
        return *this;

}

//overload operator-=  works
Cluster &Cluster::operator-=(const Point &rhs) {

       if(size == 0)
           return *this;

        if(size == 1){
            if (*(this->points->p) == rhs){
                points = nullptr;
                size--;
                return *this;
            }
            else
                return *this;
        }

        LNodePtr prev = points;
        LNodePtr curr = points->next;

        while(curr != nullptr){
            if(*(curr->p)== rhs){
                prev->next = curr->next;
                delete curr;
                size--;
                return *this;
            }
            prev= prev->next;
            curr=curr->next;
        }
        return *this;
}

//overload operator+ with two clusters  CLOSE BUT DOES NOT WORK
const Cluster operator+(const Cluster &lhs, const Cluster &rhs) {

//        Cluster c(lhs);
//        c+= rhs;
//        return c;

        LNodePtr left = lhs.points;
        LNodePtr right = rhs.points;
        Cluster c(rhs);
        bool same = false;

        while (left != nullptr) {

            while (right != nullptr) {
                if (left->p == right->p) {

                    same = true;
                }

                right = right->next;
            }
            if (same == false) {
                c.add(left->p);
                c.size++;
            }
            left = left->next;
        }
        return c;
}

//overload operator- with two clusters      CLOSE BUT DOES NOT WORK
const Cluster operator-(const Cluster &lhs, const Cluster &rhs) {

        Cluster c(lhs);
        c-=rhs;
        return c;
//        LNodePtr left = lhs.points;
//        LNodePtr right = rhs.points;
//        Cluster c = Cluster();
//        bool same = false;
//
//        if(lhs.size == 0) {
//            return c;
//        }
//
//        else{
//
//            while (left != nullptr) {
//
//                while (right != nullptr) {
//                    if (left->p == right->p) {
//
//                        same = true;
//                    }
//                    right = right->next;
//
//                }
//                if (same == false) {
//                    c.add(left->p);
//                    c.size++;
//                }
//                left = left->next;
//            }
//        }
//
//
//        return c;
}

//overload operator+ with a cluster and a point WORKS
    const Cluster operator+(const Cluster &lhs, PointPtr const &rhs) {

        Cluster newCluster(lhs);
        newCluster.add(rhs);
        return newCluster;

    }

//overload operator- with a cluster and a point WORKS
    const Cluster operator-(const Cluster &lhs, PointPtr const &rhs) {
        Cluster newCluster(lhs);
        newCluster.remove(rhs);
        return newCluster;

    }

    //delete function  clears points in other clusters as well. but works
    void Cluster::del() {

        if(size!=0){
            LNodePtr c= points;
            LNodePtr n = points->next;
            delete c->p;

            while(n!=nullptr) {
                c = n;
                n = n->next;
                delete c->p;
                delete c;
            }

        }
        points=nullptr;
        size = 0;

    }


    //inserts a LNode intro a cluster  works
    void Cluster::ins(LNodePtr first, LNodePtr add, LNodePtr last){
        first->next = add;
        add->next = last;
    }

    //copy  works
    void Cluster::cpy(LNodePtr ptr) {
        LNodePtr end = ptr;
        LNodePtr curr = new LNode(end->p, nullptr);
        points = curr;
        LNodePtr prev = curr;
        end = end->next;

        for( ; end != nullptr; end = end->next){
            curr = new LNode(end->p, nullptr);
            prev->next = curr;
            prev = curr;
        }

    }


    //constructor for LNode  works
    LNode::LNode(PointPtr ptr, LNodePtr nodePtr) {

        p = ptr;
        next = nodePtr;

    }

    void Cluster::setCentroid(const Point &point) {
        PointPtr cent = new Point(point);
        __centroid = cent;
        __validCen = true;
    }

    const Point Cluster::getCentroid() {
        return *__centroid;
    }

    void Cluster::computeCentroid() {
        Point cent(__dims);
        LNodePtr curr = points;
        if (curr == NULL)
            __centroid = NULL;
        for(int i=0;i <= size; i++){
            cent += *(curr->p)/size;
            curr = curr->next;
        }
        PointPtr c = new Point(cent);
        __centroid = c;
        __validCen = true;
    }

    void Cluster::idGen() {
        static unsigned int id = 1;
        __id = id++;

    }

    void Cluster::invalidCentroid() {
        __validCen = false;
    }

    void Cluster::setDim(const int dim) {
        __dims = dim;

    }

    void Cluster::pickPoints(int k, PointPtr *pointArray) {

        int size= this->size;
        int num = size/k;
        LNodePtr curr = this->points;

        for(int i = 0;i<k;i++){
            pointArray[i] = curr->p;
            for(int j = 0; j<num; j++)
                curr = curr->next;

        }

    }

    double Cluster::intraClusterDistance() const {
        LNodePtr curr = this->points;
        double dist = 0;
        while(curr != NULL){
            LNodePtr other = this->points;
            while (other != NULL) {
                dist = (dist + curr->p->distanceTo(*(other->p))) / 2;
                other = other->next;
            }
            curr = curr->next;
        }

    return dist;
    }

    double Cluster::interClusterDistance(const Cluster &c1, const Cluster &c2) {
        LNodePtr curr = c1.points;
        double dist = 0;
        while(curr != NULL){
            LNodePtr other = c2.points;
            while (other != NULL) {
                dist = (dist + curr->p->distanceTo(*(other->p))) / 2;
                other = other->next;
            }
            curr = curr->next;
        }

        return dist;
    }

    int Cluster::getClusterEdges() {
        return((this->size)*((this->size) - 1)/2);

    }

    double interClusterEdges(const Cluster &c1, const Cluster &c2) {
        double size1 = c1.size;
        double size2 = c2.size;
        double edges = (size1 *(size2 - 1))/2;
        return edges;

    }

    Point Cluster::getPoint(int num) const {


    }

    double Cluster::Kmeans::computeClusteringScore(int k, Cluster *cluster) {
        double dIN = 0;
        double dOUT = 0;
        double pIN = 0;
        double pOUT = 0;
        for (int i = 0; i < k; i++)
            dIN = dIN + cluster[i].intraClusterDistance();

        for (int i = 0; i < k - 1; i++) {
            for (int j = i; j < k; j++) {
                Cluster c = cluster[i];
                Cluster c2 = cluster[j];

                dOUT = dOUT + cluster->interClusterDistance(c,c2);
            }
        }


        for(int i =0;i<k;i++)
            pIN = pIN + cluster[i].getClusterEdges();

        for(int i = 0;i<k-1; i++){
            for(int j=i+1;j<k; j++) {
                Cluster c = cluster[i];
                Cluster c2 = cluster[j];

                pOUT = pOUT + interClusterEdges(c,c2);
            }
        }
        double betaCV = (dIN/pIN)/(dOUT/pOUT);
        return betaCV;
    }



    void Cluster::Kmeans::runKmeans(int k, int dim) {

        PointPtr centArray[k];
        Cluster point_space;

        std::ifstream csv("points.txt");
        point_space.setDim(dim);
        csv >> point_space;
        point_space.pickPoints(k,centArray);
        point_space.setCentroid(*centArray[k]);

        Cluster *cArr = new Cluster[k];
        cArr[k] = point_space;


        for(int i = 0; i<k-1; i++){
            Cluster *add = new Cluster;
            add->setDim(dim);
            add->setCentroid(*centArray[i]);
            cArr[i] = *add;
        }

        double score = computeClusteringScore(k,cArr);
        double prevScore;
        double scoreDiff = SCORE_DIFF_THRESHOLD + 1;

        while(scoreDiff > SCORE_DIFF_THRESHOLD){
            //loop through clusters
            for(int i =0; i < k; i++){
                //loop through points
                for(int j=0;j<cArr[i].getSize();j++){
                    Cluster *move = NULL;
                    //loop through centroids
                    for(int l = 0;l < k; l++){
                        PointPtr curr = cArr[i][j]->p;
                        if (curr->distanceTo(cArr[i].getCentroid()) > curr->distanceTo(cArr[l].getCentroid())){

                            move = &cArr[l];
                        }

                    }

                     Move(cArr[i][j]->p, &cArr[i], move);


                }
            }
            for(int i = 0;i< k; i++){
                if(!(cArr[i].centroidValid()))
                    cArr[i].computeCentroid();
            }
            prevScore = score;

            score = computeClusteringScore(k,cArr);
            scoreDiff = fabs(score-prevScore);
        }


        std::ofstream out("output.txt");
        for(int j = 0;j<k;j++)
            out << cArr[j];
        out.close();

    }


}

