#ifndef __BUILDERS_HPP__
#define __BUILDERS_HPP__

namespace stein {

class Object; //Forward declaration

// Building functions
void buildTriangle(Object &object);
void buildSquare(Object &object, const float side = 0.5);
bool buildObjectGeometryFromOBJ(Object &object, const char* fileName, bool smoothObject, bool normalize);

} // namespace stein

#endif
