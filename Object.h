#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <string>
#include <vector>
#include "Functions.h"

using namespace std;

class Object
{
private:
    string name;
    string tag;
public:
    Object();
    Object(string tag, string name);

    /* pure virtual function */
    virtual bool triggerEvent(Object*) = 0;

    /* Set & Get function*/
    void setName(string);
    void setTag(string);
    string getName() const;
    string getTag() const;

    friend ostream& operator << (ostream& out, const Object& obj);
};


#endif // OBJECT_H
