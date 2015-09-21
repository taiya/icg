#if 0
#include "Shape.h"
using namespace std;

int main(){
    Shape a(1,0,0); ///< Constructor
    Shape b;        ///< Constructor 
    Shape c(a);     ///< Copy constructor
    Shape d=a;      ///< Copy constructor
    a = b;          ///< Assignment operator
    return 0;
} ///< Destructor for a, b, c and d
#endif

#if 0
#include <iostream> ///< defines std::cout
using namespace std;

void foo1(int  var){ var++; }    ///< by value
void foo2(int* var){ (*var)++; } ///< by pointer
void foo3(int& var){ var++; }    ///< by reference
        
int main(int, char**){
    int var1=0, var2=0, var3=0;
    foo1(var1);  cout << var1 << endl; ///< output: "0"
    foo2(&var2); cout << var2 << endl; ///< output: "1"
    foo3(var3);  cout << var3 << endl; ///< output: "1"
    return 0;
}
#endif

#if 0
#include <iostream>

template <class T>
T multiply(T a, T b){ return a*b; }

int main(int, char**){
    using namespace std;
    float a=0.5f, b=3.0f;
    cout << multiply(a,b) << endl; ///< automatic
    cout << multiply<float>(a,b) << endl;
    cout << multiply<int>(a,b) << endl;
}
#endif

#if 0
template <class T>
class Shape{
private:
    float _size = 0;
    T _color[3];
public:
    // ...
    
};

int main(int, char**){
    Shape<unsigned char> shape1;
    Shape<float> shape2;
}
#endif

#if 0
#include <iostream>
#include <vector>

int main(int, char**){
    std::vector<float> v(3, 0.0f);
    v.resize(4, 1.0f);
    
    ///--- Using C like operator[ ]
    std::cout << "v: ";
    for (int i = 0; i < v.size(); ++i)
        std::cout << v[i] << " ";
    std::cout << std::endl;
    
    ///--- Using C++11
    std::cout << "v: ";
    for (auto item : v)
        std::cout << item << " ";
    std::cout << std::endl;
    
    return 0;
}
#endif
    
#if 0
#include <iostream>
#include <map>
#include <string>

int main(int, char**){
    using namespace std; ///< namespace of STL 
    map<string, int> m;
    m["#shapes"] = 2;
    m["#materials"] = 3;   
    /// map::operator[]
    cout << m["#shapes"] << endl;
    
    /// foreach in C++11 
    cout << "map content: \n";
    for(const auto& pair: m)
        cout << pair.first << " " << pair.second << endl;
    
    return 0;
}
#endif


#if 0
#include <iostream>
#include <Eigen/Dense>
using namespace std; 

int main(int, char**){
    typedef Eigen::Vector3f vec3;
    typedef Eigen::Matrix3f mat3x3;

    vec3 x(1,0,0);
    mat3x3 M = mat3x3::Random();
    vec3 out = M*x; ///< operator*
    
    cout << "x: " << x.transpose() << endl;
    cout << "M: \n" << M << endl;
    cout << "M*x: " << out.transpose() << endl;
    
    return 0;
}
#endif

#if 1
#include <iostream>
#include <Eigen/Dense>
#include <Eigen/Geometry>
using namespace std;

int main(int, char**){
    typedef Eigen::ParametrizedLine<float, 3> ray3;
    typedef Eigen::Vector3f vec3;
    
    /// Let’s build a ray
    vec3 o = vec3(0,0,0);
    vec3 d = vec3(1,1,0).normalized();
    ray3 r(o,d);

    /// p = r(t) = o + t*d
    vec3 p = r.pointAt(2);
    cout << p.transpose() << endl;
    
    return 0;
}
#endif
