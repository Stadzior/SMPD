#ifndef CLASSIFIER_H
#define CLASSIFIER_H

class ClassifierNN : Classifier
{
private:
    std::vector<Object> trainObjects;
    std::vector<Object> testObjects;

    bool compareTestObjectWithTrainVector(Object testObject);
    double computeComparation(std::vector<float> trainFeatures, std::vector<float> testFeatures, int numberOfFeatures);

public:

    ClassifierNN(){}

    void setTrainObjects(std::vector<Object> trainObjects){this->trainObjects = trainObjects; noOfTrainObjects = trainObjects.size();}
    std::vector<Object> getTrainObjects(){return trainObjects;}
    void setTestObjects(std::vector<Object> testObjects){this->testObjects = testObjects; noOfTestObjects = testObjects.size();}
    std::vector<Object> getTestObjects(){return testObjects;}

    int calculatePercentageOfCorrectClassification();
    std::vector<double> getKNearestNeighbours(int k);
};


#endif // CLASSIFIER_H
