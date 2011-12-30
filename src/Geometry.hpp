#ifndef _GEOMETRY_HPP_
#define _GEOMETRY_HPP_

#include <stein/math/Vector3f.hpp>
#include <stein/Object.hpp>

struct Triangle {
	stein::Vector3f a;
	stein::Vector3f b;
	stein::Vector3f c;
	stein::Object * pObject;
	Triangle(stein::Vector3f & aSource, stein::Vector3f & bSource, stein::Vector3f & cSource, stein::Object * pObjectSource) :
		a(aSource), b(bSource), c(cSource), pObject(pObjectSource)
	{}
	~Triangle() {}
};

struct Ray {
	stein::Vector3f pos;
	stein::Vector3f dir;
	Ray(stein::Vector3f & p, stein::Vector3f & d) :
		pos(p), dir(d) 
	{}
	~Ray() {}
};

struct Intersection {
	Ray ray;
	Triangle triangle;
	stein::Vector3f point;
	Intersection(Ray r, Triangle t, stein::Vector3f p) : ray(r), triangle(t), point(p)
	{}
	~Intersection() {}
	float computeDepth(const Camera & camera) {
		// return distance between position of camera and the intersection
		return (point - camera.getPosition()).norm();
	}
};


bool checkIntersection(const Ray & ray, const Triangle & triangle, stein::Vector3f & result) {
    GLfloat t = (normal.dotP(triangle.a) - normal.dotP(ray.pos)) / normal.dotP(ray.dir);
    if (t<0.0) return false;

    Vector3f pa(triangle.a.x - ray.pos.x, triangle.a.y - ray.pos.y, triangle.a.z - ray.pos.z);
    Vector3f pb(triangle.b.x - ray.pos.x, triangle.b.y - ray.pos.y, triangle.b.z - ray.pos.z);
    Vector3f pc(triangle.c.x - ray.pos.x, triangle.c.y - ray.pos.y, triangle.c.z - ray.pos.z);
    
    // Test intersection against triangle ABC
    GLfloat u = dir.scalarTriple(pc, pb);
	if (u<0.0) return false;
    
    GLfloat v = dir.scalarTriple(pa, pc);
    if (v<0.0) return false;
    
    GLfloat w = dir.scalarTriple(pb, pa);
    if (w<0.0) return false;

    // Compute r, r=u*a+v*b+w*c, from barycentric coordinates (u, v, w)
    GLfloat denom=1.0/(u+v+w);
    u*=denom;
    v*=denom;
    w*=denom;
    
    result.x = u * triangle.a.x + v * triangle.b.x + w * triangle.c.x;
	result.y = u * triangle.a.y + v * triangle.b.y + w * triangle.c.y;
	result.z = u * triangle.a.z + v * triangle.b.z + w * triangle.c.z;
    
    return true;
}

#endif // _GEOMETRY_HPP_
