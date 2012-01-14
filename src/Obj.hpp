#ifndef _OBJ_HPP_
#define _OBJ_HPP_

#include <stein/Object.hpp>
#include <stein/Scene.hpp>
#include <stein/Tools.hpp>
#include <string>

enum ObjectType {
	PLAYER, VISIBLE_WALL, INVISIBLE_WALL, PORTALABLE_ZONE, ACTION_ZONE, MIRROR, DECOR
};
	
struct Obj {

	stein::Object &object;
	std::string path;
	ObjectType type;
	int block;
	double posX, posY, posZ;
	std::string texturePath;
	Obj(stein::Scene * pScene, const std::string & p, const ObjectType &t, const std::string &tp = "../res/textures/sand.ppm") :
		object(pScene->createObject(GL_TRIANGLES)), path(p), type(t), texturePath(tp)
	{
		object.setTextureId(stein::loadTexture(texturePath.c_str()));
		pScene->addObjectToDraw(object.id);
	}
	
};

#endif // _OBJ_HPP_
