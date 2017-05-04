#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <vector>

class Object
{
private:
	int classID;
    std::string className;
    std::vector<float> features;


public:

    Object(){}
    Object(const std::string &className, const std::vector<float> &features) :classID(-1), className(className), features(features)
    {
    }

    std::string getClassName() const;
    size_t getFeaturesNumber() const;
    const std::vector<float> &getFeatures() const;
    bool operator==(const Object &obj) const {
        return obj.classID == classID && obj.className == className && obj.features == features;
    }
};



#endif // OBJECT_H
