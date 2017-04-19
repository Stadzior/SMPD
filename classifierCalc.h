#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include <string>
#include <vector>
#include <math.h>

#include "object.h"

class ClassifierCalc
{
private:
    std::vector<Object> trainObjects;
    std::vector<Object> testObjects;
    int noOfTrainObjects;
    int noOfTestObjects;

    bool compareTestObjectWithTrainVector(Object testObject);
    double computeComparation(std::vector<float> trainFeatures, std::vector<float> testFeatures, int numberOfFeatures);

public:

    ClassifierCalc(){}

    void setTrainObjects(std::vector<Object> trainObjects){this->trainObjects = trainObjects; noOfTrainObjects = trainObjects.size();}
    std::vector<Object> getTrainObjects(){return trainObjects;}
    void setTestObjects(std::vector<Object> testObjects){this->testObjects = testObjects; noOfTestObjects = testObjects.size();}
    std::vector<Object> getTestObjects(){return testObjects;}

    int calculatePercentageRightClassificationOfTestObjects();
    std::vector<double> getKNearestNeighbours(int k);
};


#endif // CLASSIFIER_H
