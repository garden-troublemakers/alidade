#ifndef __BUILDERS_HPP__
#define __BUILDERS_HPP__

#include "MeshBuilder.h"

namespace stein {

class Object; //Forward declaration

// Building functions
void buildTriangle(Object &object, MeshBuilder & builder);
void buildSquare(Object &object, const float side, MeshBuilder & builder);
bool buildObjectGeometryFromOBJ(Object &object, const char* fileName, bool smoothObject, bool normalize, MeshBuilder & builder);

} // namespace stein

#endif
