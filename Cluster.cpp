//
// Created by William Uhl on 9/15/2015.
//

#include "Cluster.h"

namespace Clustering {

//Copy constructor
    Cluster::Cluster(const Cluster &inputCluster) {
        size = inputCluster.size;

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

//overloaded operator=
Cluster &Cluster::operator=(const Cluster &inputCluster) {
        if (this == &inputCluster)
            return *this;

        size = inputCluster.size;

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

//function add a point
    void Cluster::add(PointPtr const &ptr) {

        if (size == 0){
            points = new LNode(ptr, nullptr);
        }
        else{
            LNodePtr curr = points;
            LNodePtr nex = points->next;
            LNodePtr newNode = new LNode(ptr,nullptr);
            while(*(curr->p) <= *ptr){
                if(nex == nullptr || *(newNode->p) > *ptr){
                    break;
                }
                else{
                    curr = nex;
                    nex = nex->next;
                }
            }
            ins(curr,newNode,nex);
        }
        size++;

    }

//function remove a point
PointPtr const &Cluster::remove(PointPtr const &ptr) {

        if (size == 0){
            std::cout << "Cluster is empty nothing to remove" << std::endl;
            return ptr;
        }
        else if(size == 1) {
            if(points->p == ptr){
                points = nullptr;
                size--;
                return ptr;
            }

        }
        else {
            //traverse the cluster looking for the point to delete
            LNodePtr prev = points;
            LNodePtr curr = points->next;


            while (curr != nullptr) {
                if (curr->p == ptr){

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

//overload operator<<
std::ostream &operator<<(std::ostream &os, const Cluster &cluster) {
        if (cluster.size == 0) {
            os << "Cluster is empty" << std::endl;
            return os;
        }

        LNodePtr current = cluster.points;
        //int counter =1;
        for( ; current != nullptr; current = current->next) {
           // os << "Point " << counter++ << std::endl;
            os << *(current->p) << std::endl;


        }
        return os;


}

    //Will do this for the next PA assignment
//overload operator>>
//std::istream &operator>>(std::istream &istream, Cluster &cluster) {
   // return <#initializer#>;
//}

//overload operator==
    bool operator==(const Cluster &lhs, const Cluster &rhs) {


        if (lhs.size != rhs.size)
            return false;

        LNodePtr left = lhs.points;
        LNodePtr right = rhs.points;

        while(left != nullptr && right !=nullptr){
            if (left != right)
                return false;
            left = left->next;
            right = right->next;

        }
        return true;

    }

//overload operator+=
Cluster &Cluster::operator+=(const Cluster &rhs) {


        LNodePtr left = this->points;
        LNodePtr right = rhs.points;
        Cluster c = Cluster();

        while(left != nullptr || right !=nullptr){
            if (left == right){
                c.add(left->p);
                c.size++;
            }
            else{
                c.add(left->p);
                c.add(right->p);
                c.size = c.size +2;
            }
            if(left!=nullptr)
                left = left->next;
            if(right!=nullptr)
                right = right->next;

        }


        return c;

}

//overload operator-=
Cluster &Cluster::operator-=(const Cluster &rhs) {

        LNodePtr left = this->points;
        LNodePtr right = rhs.points;
        Cluster c = Cluster();

        while(left != nullptr || right !=nullptr){
            if (left == right){
                c.add(left->p);
                c.size++;
            }
            else{
                c.add(left->p);
                c.add(right->p);
                c.size = c.size +2;
            }

                left = left->next;
            if(right!=nullptr)
                right = right->next;

        }


        return c;
}

//overload operator+=
//Cluster &Cluster::operator+=(const Point &rhs) {
//
//        this->add(&rhs);
//
//        return *this;
//}

////overload operator-=
//Cluster &Cluster::operator-=(const Point &rhs) {
//
//        this->remove(&rhs);
//
//    return *this;
//}

//overload operator+ with two clusters
const Cluster operator+(const Cluster &lhs, const Cluster &rhs) {

        LNodePtr left = lhs.points;
        LNodePtr right = rhs.points;
        Cluster c = Cluster();

        while(left != nullptr || right !=nullptr){
            if (left == right){
                c.add(left->p);
                c.size++;
            }
            else{
                c.add(left->p);
                c.add(right->p);
                c.size = c.size +2;
            }
            if(left!=nullptr)
                left = left->next;
            if(right!=nullptr)
                right = right->next;

        }


        return c;
}

//overload operator- with two clusters
const Cluster operator-(const Cluster &lhs, const Cluster &rhs) {
        LNodePtr left = lhs.points;
        LNodePtr right = rhs.points;
        Cluster c = Cluster();

        while(left != nullptr || right !=nullptr){
            if (left != right) {
                c.add(left->p);
                c.size++;
            }
            if(left!=nullptr)
                left = left->next;
            if(right!=nullptr)
                right = right->next;
        }


        return c;
}

//overload operator+ with a cluster and a point
//    const Cluster operator+(const Cluster &lhs, PointPtr const &rhs) {
//
//
//        //is this even doing what i want?????
//        Cluster *c = &lhs;
//        c->add(rhs);
//
//
//        return *c;
//    }

////overload operator- with a cluster and a point
//    const Cluster operator-(const Cluster &lhs, PointPtr const &rhs) {
//
//        //Again is this even close?
//        Cluster c = &lhs;
//        c->remove(rhs);
//
//        return *c;
//    }

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


    //inserts a LNode intro a cluster
    void Cluster::ins(LNodePtr first, LNodePtr add, LNodePtr last){
        first->next = add;
        add->next = last;
    }

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


    //constructor for LNode
    LNode::LNode(PointPtr ptr, LNodePtr nodePtr) {

        p = ptr;
        next = nodePtr;

    }
}
