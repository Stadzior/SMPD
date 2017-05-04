#include "classifierNM.h"

double ClassifierNM::Execute(std::vector<Object> trainingSet, std::vector<Object> testingSet, int k)
{

    std::vector<Object> acerClass(BuildMatrix(trainingSet, "Acer"));
    std::vector<Object> quercusClass(BuildMatrix(trainingSet, "Quercus"));

    std::vector<double> acerAvarage(CalculateAvarage(acerClass));
    std::vector<double> quercusAvarage(CalculateAvarage(quercusClass));

    int classifiedA = 0;
    int classifiedB = 0;

    for (Object testingObject : testingSet) {
        double valueA = CalculateDistance(acerAvarage, testingObject);
        double valueB = CalculateDistance(quercusAvarage, testingObject);

        if (valueA < valueB) {
                classifiedA++;
        }
        else if (valueB < valueA) {
                classifiedB++;
        }
    }
    return ((double)classifiedA/(double)(classifiedA+classifiedB))*100;
}

std::vector<Object> ClassifierNM::BuildMatrix(std::vector<Object> trainingSet, std::string className)
{
    std::vector<Object> matrix;

    for (Object value : trainingSet)
        if (value.getClassName().compare(className) == 0)
            matrix.push_back(value);

    return matrix;
}

std::vector<double> ClassifierNM::CalculateAvarage(std::vector<Object> matrix)
{

    std::vector<double> avarage;

    for (unsigned int i = 0; i < matrix.at(0).getFeatures().size(); i++) {
        double sum = 0.0;  

        for (unsigned int j = 0; j < matrix.size(); j++)
            sum += matrix.at(j).getFeatures().at(i);

        avarage.push_back(sum/matrix.size());
    }

    return avarage;
}

double ClassifierNM::CalculateDistance(std::vector<double> object, Object target)
{
    double result = 0.0;
    for (unsigned int i = 0; i < object.size(); i++)
        result += pow(object.at(i) - target.getFeatures().at(i), 2);
    return sqrt(result);
}
