#include "Shape.h"

#include <iostream>
using namespace std;

Shape::Shape(int r, int g, int b){
    cout << "Shape()" << endl;
    _color = new int[3]; ///< RGB          
    _color[0]=r; _color[1]=g; _color[2]=b;
}

Shape::~Shape(){ 
    cout << "~Shape()" << endl;
    delete[] _color; 
}

Shape::Shape(const Shape &shape){
    cout << "Shape(Shape& )" << endl;
    this->_size = shape._size;
    _color = new int[3]; ///< CAREFUL!
    for (int i = 0; i < 3; ++i) 
        this->_color[i] = shape._color[i];
}

Shape &Shape::operator=(const Shape &shape){
    cout << "Shape::operator=" << endl;
    this->_size = shape._size;
    for (int i = 0; i < 3; ++i) 
        this->_color[i] = shape._color[i];
    return *this;
}

void Shape::operator*(const float scale){
    cout << "Shape::operator*" << endl;
    this->_size *= scale;
}
