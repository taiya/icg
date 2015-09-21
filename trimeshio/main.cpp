#include "icg_common.h"
#include <iomanip>
#include "MLogger.h" 
#include <OpenGP/Surface_mesh.h>
using namespace opengp;

int main(int, char**){
    std::cout << std::setprecision(2) << std::setw(2) << std::fixed;
    
    Surface_mesh mesh;
//    mesh.read("bunny.obj");
//    mesh.read("sphere.obj");
    mesh.read("triangle.obj");
    mesh.triangulate();
    mesh.update_face_normals();
    mesh.update_vertex_normals();
     
    auto f_normal = mesh.get_face_property<vec3>("f:normal");
    auto v_point = mesh.get_vertex_property<vec3>("v:point");
    auto v_normal = mesh.get_vertex_property<vec3>("v:normal");

    for(auto f: mesh.faces()){
        mLogger() << "Face: [" << f.idx() << "]";
        mLogger() << "  n: " << f_normal[f];
        for(auto v: mesh.vertices(f)){
            vec3 p = v_point[v];
            vec3 n = v_normal[v];
            mLogger() << "  Vertex[" << v.idx() << "]"; 
            mLogger() << "    p:" << p; 
            mLogger() << "    n:" << n; 
        }
    }
    
    return 0;
}
