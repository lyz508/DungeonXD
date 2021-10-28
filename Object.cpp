#include "Object.h"

Object::Object(){
    this->tag = "Object";
    this->name = rand_name_generator(this->tag);
}

Object::Object(string tag, string name){
    this->name = name;
    this->tag = tag;
}

void Object::setName(string name){
    this->name = name;
}

void Object::setTag(string tag){
    this->tag = tag;
}

string Object::getName() const{
    return this->name;
}

string Object::getTag() const{
    return this->tag;
}


ostream& operator << (ostream& out, const Object& obj){

    out << "\n=======" << obj.name << "=======\n"
        << "Type: " << obj.tag << "\n\n";
    for(int i=0; i<14+obj.name.length(); i++){
        out << "=";
    }

    return out;
}
