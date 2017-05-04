#include "classifierNN.h"

double ClassifierNN::Execute(std::vector<Object> trainingSet, std::vector<Object> testingSet,int k)
{
    int countOfCorrectClassifiedObjects = 0;
    for(Object obj : testingSet)
    {
        std::string classifiedClassName = Classify(obj,trainingSet);
        if(classifiedClassName.compare(obj.getClassName()) == 0)
            countOfCorrectClassifiedObjects++;
    }

    return (countOfCorrectClassifiedObjects*100)/testingSet.size();
}

std::string ClassifierNN::Classify(Object testObject, std::vector<Object> trainingSet)
{
    std::vector<float> testFeatures = testObject.getFeatures();
    int numberOfFeatures = testObject.getFeaturesNumber();

    double lowestValue = -1.0;
    std::string trainClassName = "";
    for(Object trainingObject : trainingSet){

        double distance = CalculateDistance(trainingObject.getFeatures(), testFeatures, numberOfFeatures);

        if((distance < lowestValue) || (lowestValue == -1.0))
        {
            lowestValue = distance;
            trainClassName = trainingObject.getClassName();
        }
    }

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
