#include "classifierNN.h"
#include <map>
double ClassifierNN::Execute(std::vector<Object> trainingSet, std::vector<Object> testingSet,int k)
{
    int countOfCorrectClassifiedObjects = 0;
    for(Object obj : testingSet)
    {
        std::string classifiedClassName = Classify(obj, trainingSet, k);
        if(classifiedClassName.compare(obj.getClassName()) == 0)
            countOfCorrectClassifiedObjects++;
    }

    return (countOfCorrectClassifiedObjects*100)/testingSet.size();
}

std::string ClassifierNN::Classify(Object testObject, std::vector<Object> trainingSet, int k)
{
    std::vector<float> testFeatures = testObject.getFeatures();
    int numberOfFeatures = testObject.getFeaturesNumber();

    double lowestValue = -1.0;
    std::string trainClassName = "";
    std::vector<Object> neighbours = std::vector<Object>();

    for(unsigned int i=0; i<k; i++)
    {
        Object nearestNeighbour;
        for(Object trainingObject : trainingSet)
        {
            double distance = CalculateDistance(trainingObject.getFeatures(), testFeatures, numberOfFeatures);
            bool neighbourAlreadyFound = std::find(neighbours.begin(), neighbours.end(), trainingObject) != neighbours.end();
            if(!neighbourAlreadyFound && ((distance < lowestValue) || (lowestValue == -1.0)))
            {
                lowestValue = distance;
                nearestNeighbour = trainingObject;
            }
        }
        neighbours.insert(0,nearestNeighbour);
    }

    std::map<std::string,int> classesWithCounts = GetNeighboursClasses();

    return trainClassName;
}

double ClassifierNN::CalculateDistance(std::vector<float> trainFeatures, std::vector<float> testFeatures, int numberOfFeatures)
{
    double sum = 0.0;
    for(int i = 0; i < numberOfFeatures; i++){
        sum += pow(testFeatures[i] - trainFeatures[i], 2.0);
    }

    return sqrt(sum);
}
