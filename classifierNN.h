#ifndef CLASSIFIERNN_H
#define CLASSIFIERNN_H

#include "classifier.h"

class ClassifierNN : public Classifier
{
    public:
        ClassifierNN(){}
        std::vector<double> GetNearestNeighbours(int k);
        double Execute(std::vector<Object> trainingSet, std::vector<Object> testingSet, int k = 1);

    private:
        std::string Classify(Object testObject, std::vector<Object> trainingSet);
        double CalculateDistance(std::vector<float> trainFeatures, std::vector<float> testFeatures, int numberOfFeatures);
};


#endif // CLASSIFIERNN_H
