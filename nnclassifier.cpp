#include "nnclassifier.h"

int NNClassifier::execute(std::vector<Object> trainingSet, std::vector<Object> testingSet) {

    for (Object testingObject : testingSet)
        if (classify(trainingSet, testingObject).compare(testingObject.getClassName()) == 0)
            properlyClassified++;
        else
            misclassified++;

    return ((double)properlyClassified/((double)properlyClassified + (double)misclassified))*100;
}


std::string NNClassifier::classify(std::vector<Object> trainingSet, Object testingObject) {

    std::map<double, std::string> distanceResults;

    for (Object trainingObject: trainingSet)
        distanceResults[countEuclideanDistance(testingObject, trainingObject)] = trainingObject.getClassName();

    return distanceResults.find(getMinValue(distanceResults))->second;
}

double NNClassifier::countEuclideanDistance(Object object, Object target) {
    double sum = 0.0;
    for (int i = 0; i < object.getFeaturesNumber(); i++)
        sum += countDistance(object, target, i);
    return sum;
}

double NNClassifier::getMinValue(std::map<double, std::string> distanceResults) {
    double min = distanceResults.begin()->first;

    for(std::map<double, std::string>::iterator iter = distanceResults.begin(); iter != distanceResults.end(); ++iter)
        if (iter->first < min)
        min = iter->first;

    return min;
}

double NNClassifier::countDistance(Object object, Object target, int noFeatures) {
    return pow(object.getFeatures().at(noFeatures) - target.getFeatures().at(noFeatures), 2);
}
