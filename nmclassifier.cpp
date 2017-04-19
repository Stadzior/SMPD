#include "nmclassifier.h"
#include <QDebug>

int NMClassifier::execute(std::vector<Object> trainingSet, std::vector<Object> testingSet) {

    std::vector<Object> acerClass(buildMatrix(trainingSet, "Acer"));
    std::vector<Object> quercusClass(buildMatrix(trainingSet, "Quercus"));

    std::vector<double> acerAvarage(calculateAvarage(acerClass));
    std::vector<double> quercusAvarage(calculateAvarage(quercusClass));

    int classifiedA = 0;
    int classifiedB = 0;
    int failed = 0;
    //double min = -1;


    for (Object testingObject : testingSet) {
        double valueA = calculateDistance(acerAvarage, testingObject);
        double valueB = calculateDistance(quercusAvarage, testingObject);

        if (valueA < valueB) {
                classifiedA++;
                //min = valueA;
        }
        else if (valueB < valueA) {
                classifiedB++;
                //min = valueB;
        }
    }
    return ((double)classifiedA/(double)(classifiedA+classifiedB))*100;
}

std::vector<Object> NMClassifier::buildMatrix(std::vector<Object> trainingSet, std::string className) {
    std::vector<Object> matrix;

    for (Object value : trainingSet)
        if (value.getClassName().compare(className) == 0)
            matrix.push_back(value);

    return matrix;
}

std::vector<double> NMClassifier::calculateAvarage(std::vector<Object> matrix) {

    std::vector<double> avarage;

    for (int i = 0; i < matrix.at(0).getFeatures().size(); i++) {
        double sum = 0.0;  

        for (int j = 0; j < matrix.size(); j++)
            sum += matrix.at(j).getFeatures().at(i);

        avarage.push_back(sum/matrix.size());
    }

    return avarage;
}

double NMClassifier::calculateDistance(std::vector<double> object, Object target) {
    double result = 0.0;
    for (int i = 0; i < object.size(); i++)
        result += pow(object.at(i) - target.getFeatures().at(i), 2);
    return sqrt(result);
}
