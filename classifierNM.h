#ifndef NMCLASSIFIER_H
#define NMCLASSIFIER_H

#include <string>
#include <vector>
#include <math.h>
#include <map>
#include "Object.h"

class NMClassifier : Classifier
{

    public:
        NMClassifier(){}
        int execute(std::vector<Object> trainingSet, std::vector<Object> testingSet);

    private:
        std::vector<Object> buildMatrix(std::vector<Object> trainingSet, std::string className);
        std::vector<double> calculateAvarage(std::vector<Object> matrix);
        double calculateDistance(std::vector<double> object, Object target);

};

#endif // NMCLASSIFIER_H
