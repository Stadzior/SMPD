#ifndef CLASSIFIERNM_H
#define CLASSIFIERNM_H

#include <map>
#include "Object.h"
#include "classifier.h"

class ClassifierNM : public Classifier
{

    public:
        ClassifierNM(){}
        double Execute(std::vector<Object> trainingSet, std::vector<Object> testingSet, int k = 1);
    private:
        std::vector<Object> BuildMatrix(std::vector<Object> trainingSet, std::string className);
        std::vector<double> CalculateAvarage(std::vector<Object> matrix);
        double CalculateDistance(std::vector<double> object, Object target);

};

#endif // CLASSIFIERNM_H
