//
// Created by William Uhl on 9/15/2015.
//

#include "Cluster.h"

namespace Clustering {

//Copy constructor works
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

//overloaded operator= works
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
            os << *(current->p) << std::endl;


        }
        return os;


}

    //Will do this for the next PA assignment
//overload operator>>
//std::istream &operator>>(std::istream &istream, Cluster &cluster) {
   // return <#initializer#>;
//}

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

//overload operator+=    DOES NOT WORK
Cluster &Cluster::operator+=(const Cluster &rhs) {


        LNodePtr left = this->points;
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

//overload operator-=    DOES NOT WORK
Cluster &Cluster::operator-=(const Cluster &rhs) {

        LNodePtr left = this->points;
        LNodePtr right = rhs.points;
        Cluster c = Cluster(*this);
        bool same = false;

        if(this->size == 0) {
            return c;
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
                    c.remove(left->p);
                    c.size--;
                }
                left = left->next;
            }
        }

        return c;
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
        LNodePtr left = lhs.points;
        LNodePtr right = rhs.points;
        Cluster c = Cluster();
        bool same = false;

        if(lhs.size == 0) {
            return c;
        }

        else{

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
        }


        return c;
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
}
