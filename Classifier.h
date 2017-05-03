#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include <string>
#include <vector>
#include <math.h>

#include "object.h"

class Classifier
{
public:
    void Train();
    double Execute(std::vector<Object> trainingSet, std::vector<Object> testingSet);
};

#endif // CLASSIFIER_H
