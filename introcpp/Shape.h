#pragma once
class Shape{
private:
    float _size = 0;
    int* _color = 0;

public:
    /// Constructor
    Shape(int r=0, int g=0, int b=0);
    
    /// Destructor
    ~Shape();
      
    /// Copy constructor
    Shape(const Shape& shape);

    /// Assignment operator
    Shape& operator=(const Shape& shape);
    
    /// Member function
    int size() const { return _size; }
    
    /// Operator
    void operator*(const float scale);
};
