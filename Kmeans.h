//
// Created by Tres
//

#ifndef UHL_PA2_KMEANS_H
#define UHL_PA2_KMEANS_H

#include "Cluster.h"
#include "Point.h"

namespace Clustering{

    template <typename T,int k, int dim>
    class Kmeans {
    private:


    public:
        static constexpr double SCORE_DIFF_THRESHOLD = .001;
        double computeClusteringScore();
        void runKmeans(int k,int dim);


    };
};

#include "Kmeans.cpp"
#endif //UHL_PA2_KMEANS_H
