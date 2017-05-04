#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include <string>
#include <vector>
#include <math.h>
#include <map>
#include <algorithm>
#include "object.h"

class Classifier
{
public:
    void Train();
    double Execute(std::vector<Object> trainingSet, std::vector<Object> testingSet, int k = 1);
};

#endif // CLASSIFIER_H
