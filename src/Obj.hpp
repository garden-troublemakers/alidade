#ifndef _OBJ_HPP_
#define _OBJ_HPP_

#include <stein/Object.hpp>
#include <stein/Scene.hpp>
#include <stein/Tools.hpp>
#include <string>

enum ObjectType {
	PLAYER, VISIBLE_WALL, INVISIBLE_WALL, PORTALABLE_ZONE, ACTION_ZONE, MIRROR, PORTAL, DECOR
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
			triangleNormal = (normals[i] + normals[i+1] + normals[i+2]).normalize();
			triangles.push_back(Triangle(vertices[indices[i]], vertices[indices[i+1]], vertices[i+2], triangleNormal, &object));
		}
		return triangles;
	}


#endif // _OBJ_HPP_
