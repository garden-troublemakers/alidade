#ifndef _GEOMETRY_HPP_
#define _GEOMETRY_HPP_

#include <stein/GLHeaders.hpp>
#include <stein/math/Vector3f.hpp>
#include <stein/Camera.hpp>
#include <stein/Object.hpp>
#include <stein/Tools.hpp>
#include <list>

// Computing is done outside the camera's projection matrix
// You need to multiply view's inverse matrix by your projected points' vector

class Obj;
struct Box;

struct Triangle {
	const stein::Vector3f a;
	const stein::Vector3f b;
	const stein::Vector3f c;
	const stein::Vector3f normal;
	const stein::Object * pObject;
	Triangle(const stein::Vector3f & aSource, const stein::Vector3f & bSource, const stein::Vector3f & cSource, const stein::Vector3f & normalSource, const stein::Object * pObjectSource) :
		a(aSource), b(bSource), c(cSource), normal(normalSource), pObject(pObjectSource)
	{}
	~Triangle() {}
};

struct Ray {
	const stein::Vector3f pos;
	const stein::Vector3f dir;
	Ray(const stein::Vector3f & p, stein::Vector3f d) :
		pos(p), dir(-d.normalize())
	{}
	Ray(const Ray & b) :
		pos(b.pos), dir(b.dir) {
	}
	~Ray() {}
};

struct Intersection {
	const Ray ray;
	const Triangle triangle;
	stein::Vector3f point;
	Intersection(const Ray & r, const Triangle & t) :
		ray(r), triangle(t), point()
	{}
	
	Intersection(const Intersection & b) :
		ray(b.ray), triangle(b.triangle), point(b.point)
	{}
	
	~Intersection() {}
	
	float computeDepth(const stein::Camera & camera) {
		// return distance between position of camera and the intersection
		return (point - camera.getPosition()).norm();
	}
};



bool intersectRayTriangle(const Ray & ray, const Triangle & triangle, Intersection * pIntersection);
bool intersectRayBox(const Ray & ray, const Box & box, stein::Camera * refCam);
bool intersectRayObject(const Ray & ray, Obj * pObject, stein::Camera * refCam, Intersection * pIntersection);



#endif // _GEOMETRY_HPP_
