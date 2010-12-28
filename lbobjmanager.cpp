#include "lbobjmanager.h"

lbObjManager::lbObjManager()
{

}

void 
vertex_callback(obj::float_type x, obj::float_type y, obj::float_type z)
{
  //  std::cout << "v " << x << " " << y << " " << z << "\n";
};

void 
tri_face_callbacks(obj::index_type a, obj::index_type b, obj::index_type c)
{
  //  std::cout << "f: " << a << " " << b << " " << c << "\n";  
};

void 
quad_face_callbacks(obj::index_type a, obj::index_type b, obj::index_type c, obj::index_type d)
{
  //  std::cout << "f: " << a << " " << b << " " << c << " " << d << "\n";  
};



void
lbObjManager::parseObj(const char* objName)
{
  obj::obj_parser obj_parser;
  obj_parser.geometric_vertex_callback(vertex_callback);
  obj_parser.face_callbacks(tri_face_callbacks, NULL, NULL, NULL, quad_face_callbacks,
  			    NULL, NULL, NULL, NULL,
  			    NULL, NULL, NULL, NULL,
  			    NULL, NULL, NULL, NULL,
  			    NULL, NULL, NULL);
  obj_parser.parse(objName);
}
