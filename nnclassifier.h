#ifndef NNCLASSIFIER_H
#define NNCLASSIFIER_H

#include <string>
#include <vector>
#include <math.h>
#include <map>

#include "object.h"

class NNClassifier
{
private:
    std::string classify(std::vector<Object> trainingSet, Object testingObject);
    double countEuclideanDistance(Object object, Object target);
    double getMinValue(std::map<double, std::string> distanceResults);
    double countDistance(Object object, Object target, int noFeatures);

    int properlyClassified = 0, misclassified = 0;

public:
        NNClassifier(){};
        int execute(std::vector<Object> trainingSet, std::vector<Object> testingSet);


};
#endif // NNCLASSIFIER_H
