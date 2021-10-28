#include "Exceptions.h"

/*For The Exception Handle*/
CantFindTheLoadFile::CantFindTheLoadFile(){

}

CantFindTheLoadFile::CantFindTheLoadFile(string type){
    this->type = type;
}

string CantFindTheLoadFile::getType(){
    return this->type;
}

