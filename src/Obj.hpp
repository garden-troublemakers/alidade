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
	std::string texturePath;
	const GLuint shaderId;
	Obj(stein::Scene * pScene,
		const GLuint& sId,
		const std::string& p,
		const ObjectType &t,
		const std::string &tp = "../res/textures/sand.ppm") :
		object(pScene->createObject(GL_TRIANGLES)), path(p), type(t), texturePath(tp), shaderId(sId)
	{
		// need to 	write this in a better c++ syntax. let's go.
		if(texturePath != "") {
			std::cout << "path : " << texturePath << std::endl;
			object.setTextureId(stein::loadTexture(texturePath.c_str()));
			std::cout << "après" << std::endl;
		}
		pScene->addObjectToDraw(object.id);
	}
	
};

#endif // _OBJ_HPP_
