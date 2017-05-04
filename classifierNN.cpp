#include "classifierNN.h"

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

std::map<std::string,int> GetNeighboursClassesWithCounts(std::vector<Object> neighbours)
{
    std::map<std::string,int> resultMap = std::map<std::string,int>();
    for(unsigned int i = 0; i< neighbours.size(); i++)
    {
        if(resultMap.count(neighbours[i].getClassName())>0)
        {
            resultMap[neighbours[i].getClassName()]++;
        }
        else
        {
            //resultMap.insert(0,new std::pair(neighbours[i].getClassName(),1));
        }
    }
    return resultMap;
}


std::string ClassifierNN::Classify(Object testObject, std::vector<Object> trainingSet, int k)
{
    std::vector<float> testFeatures = testObject.getFeatures();
    int numberOfFeatures = testObject.getFeaturesNumber();

    double lowestValue = -1.0;
    std::string trainClassName = "";
    std::vector<Object> neighbours = std::vector<Object>();

    for(int i=0; i<k; i++)
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
        neighbours.push_back(nearestNeighbour);
    }

    //std::map<std::string,int> classesWithCounts = GetNeighboursClassesWithCounts(neighbours);
    int largestValue = -1;
    //for (std::map<std::string, int>::iterator it = classesWithCounts.begin(); it != classesWithCounts.end(); ++it)
    //{
      //  it->
      //  if(>largestValue)
      //  {
      //      trainClassName = classesWithCounts[i]
       // }
    //}
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
