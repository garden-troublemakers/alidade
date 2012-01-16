#ifndef _OBJ_HPP_
#define _OBJ_HPP_

#include "Geometry.hpp"
#include <stein/Object.hpp>
#include <stein/Scene.hpp>
#include <stein/MeshBuilder.h>
#include <stein/Tools.hpp>
#include <stein/math/Vector3f.hpp>
#include <string>
#include <list>

enum ObjectType {
	PLAYER, VISIBLE_WALL, INVISIBLE_WALL, PORTALABLE_ZONE, ACTION_ZONE, MIRROR, DECOR, PORTAL
};

struct Obj {
	stein::Object &object;
	std::string path;
	ObjectType type;
	int block;
	double posX, posY, posZ;
	stein::MeshBuilder builder;
	std::string texturePath;
	
	Obj(stein::Scene * pScene, const std::string & p, const ObjectType &t, const std::string &tp = "../res/textures/sand.ppm") :
		object(pScene->createObject(GL_TRIANGLES)), path(p), type(t), texturePath(tp)
	{
		//object.setTextureId(stein::loadTexture(texturePath.c_str()));
		pScene->addObjectToDraw(object.id);
	}
	
	std::list<Triangle> getTrianglesList() const
	{
		std::list<Triangle> triangles;
		std::vector<unsigned int> indices;
		std::vector<stein::Vector3f> vertices;
		std::vector<stein::Vector3f> normals;
		std::vector<stein::UV> uvs;
		stein::Vector3f triangleNormal;
		builder.unpack(indices, vertices, normals, uvs);
		for(size_t i = 0; i < indices.size() ; i+=3) {
			const unsigned int & i0 = indices[i];
			const unsigned int & i1 = indices[i+1];
			const unsigned int & i2 = indices[i+2];
			triangleNormal = (normals[i0] + normals[i1] + normals[i2]).normalize();
			triangles.push_back(Triangle(vertices[i0], vertices[i1], vertices[i2], triangleNormal, &object));
		}
		return triangles;
	}
};

struct Collision {
	const Obj* obj;
	Collision(const Obj* o) : obj(o)
	{}
	
	Collision(const Collision & other) : obj(other.obj)
	{}
	
	~Collision() {}
	
	ObjectType type() const {
		return obj->type;
	}
};

static inline ObjectType getObjectTypeFromInt(int type) {
	switch(type) {
		case 0 : return PLAYER;
		case 1 : return VISIBLE_WALL;
		case 3 : return PORTALABLE_ZONE;
		case 4 : return ACTION_ZONE;
		case 5 : return MIRROR;
		case 6 : return DECOR;
		default : return INVISIBLE_WALL;
	}
}

#endif // _OBJ_HPP_
