#include "classifierCalc.h"

    int ClassifierCalc::calculatePercentageRightClassificationOfTestObjects()
    {
        int calcRightClassification = 0;
        for(Object oTest : testObjects){
            if(compareTestObjectWithTrainVector(oTest))
                calcRightClassification++;
        }

        return (calcRightClassification*100)/noOfTestObjects;
    }

    bool ClassifierCalc::compareTestObjectWithTrainVector(Object testObject)
    {
        std::vector<float> testFeatures = testObject.getFeatures();
        int numberOfFeatures = testObject.getFeaturesNumber();

        double lowestValue = -1.0;
        std::string trainClassName = "";
        for(Object oTrain : trainObjects){

            double computeRet = computeComparation(oTrain.getFeatures(), testFeatures, numberOfFeatures);

            if((computeRet < lowestValue) || (lowestValue == -1.0))
            {
                lowestValue = computeRet;
                trainClassName = oTrain.getClassName();
            }

        }

        return trainClassName.compare(testObject.getClassName()) == 0;
    }

    double ClassifierCalc::computeComparation(std::vector<float> trainFeatures, std::vector<float> testFeatures, int numberOfFeatures)
    {
        double sum = 0.0;
        for(int i = 0; i < numberOfFeatures; i++){
            sum += pow(testFeatures[i] - trainFeatures[i], 2.0);
        }

        return sqrt(sum);
    }
