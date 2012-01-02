#ifndef _OBJ_HPP_
#define _OBJ_HPP_

#include <stein/Object.hpp>
#include <stein/Scene.hpp>
#include <string>

struct Obj {
	enum ObjectType {
		PLAYER, VISIBLE_WALL, INVISIBLE_WALL, PORTALABLE_ZONE, ACTION_ZONE, MIRROR, DECOR
	};
	stein::Object object;
	ObjectType type;
	int block;
	std::string path;
	double posX, posY, posZ;
	Obj(stein::Scene * pScene, const std::string & p, const ObjectType & t) :
		object(pScene->createObject(GL_TRIANGLES)), type(t), path(p)
	{
		pScene->addObjectToDraw(object.id);
	}
};

#endif // _OBJ_HPP_
