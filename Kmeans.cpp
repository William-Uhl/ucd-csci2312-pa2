//
// Created by Tres


template <typename T, int k, int dim>
double Kmeans<T,k,dim>::computeClusteringScore() {
    double dIN = 0;
    double dOUT = 0;
    double pIN = 0;
    double pOUT = 0;
    for (int i = 0; i < k; i++)
        dIN = dIN + cluster[i].intraClusterDistance();

    for (int i = 0; i < k - 1; i++) {
        for (int j = i; j < k; j++) {
            Cluster<T,dim> c = cluster[i];
            Cluster<T,dim> c2 = cluster[j];

            dOUT = dOUT + cluster->interClusterDistance(c,c2);
        }
    }


    for(int i =0;i<k;i++)
        pIN = pIN + cluster[i].getClusterEdges();

    for(int i = 0;i<k-1; i++){
        for(int j=i+1;j<k; j++) {
            Cluster<T,dim> c = cluster[i];
            Cluster<T,dim> c2 = cluster[j];

            pOUT = pOUT + interClusterEdges(c,c2);
        }
    }
    double betaCV = (dIN/pIN)/(dOUT/pOUT);
    return betaCV;
}


template <typename T, int k, int dim>
void Kmeans<T,k,dim>::runKmeans() {

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

#include "Kmeans.h"
