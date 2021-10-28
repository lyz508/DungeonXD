#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <iostream>
#include <string>
using namespace std;


class CantFindTheLoadFile{
private:
    string type;
public:
    CantFindTheLoadFile();
    CantFindTheLoadFile(string type);
    string getType();
};


#endif // EXCEPTIONS_H
