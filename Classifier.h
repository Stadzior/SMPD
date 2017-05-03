#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#endif // CLASSIFIER_H

#include <string>
#include <vector>
#include <math.h>

#include "object.h"

class Classifier
{
public:
    void Train();
    double Execute();
    int trainObjectsCount;
    int objectsCount;
};
