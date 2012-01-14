#ifndef _GEOMETRY_HPP_
#define _GEOMETRY_HPP_

#include <stein/math/Vector3f.hpp>
#include <stein/Camera.hpp>
#include <stein/Object.hpp>

struct Triangle {
	const stein::Vector3f a;
	const stein::Vector3f b;
	const stein::Vector3f c;
	const stein::Vector3f normal;
	const stein::Object * pObject;
	Triangle(const stein::Vector3f & aSource, const stein::Vector3f & bSource, const stein::Vector3f & cSource, const stein::Vector3f & normalSource, const stein::Object * pObjectSource) :
		a(aSource), b(bSource), c(cSource), normal(normalSource), pObject(pObjectSource)
	{}
	Triangle(const Triangle & b) :
		a(b.a), b(b.b), c(b.c), normal(b.normal), pObject(b.pObject)
	{}
	~Triangle() {}
};

struct Ray {
	const stein::Vector3f pos;
	const stein::Vector3f dir;
	Ray(const stein::Vector3f & p, stein::Vector3f d) :
		pos(p), dir(d.normalize()) 
	{
		glBegin(GL_LINE);
			glVertex3f(pos[0], pos[1], pos[2]);
			glVertex3f(pos[0]+dir[0], pos[1]+dir[1], pos[2]+dir[2]);
		glEnd();
	}
	Ray(const Ray & b) :
		pos(b.pos), dir(b.dir)
	{}
	~Ray() {}
};

struct Intersection {
	const Ray ray;
	const Triangle triangle;
	stein::Vector3f point;
	Intersection(const Ray & r, const Triangle & t, bool & intersect) :
		ray(r), triangle(t), point()
	{
		if(!checkIntersection()) {
			throw "No intersection";
			intersect = false;
		} else
			intersect = true;
	}
	Intersection(const Intersection & b) :
		ray(b.ray), triangle(b.triangle)
	{}
	~Intersection() {}
	
	float computeDepth(const stein::Camera & camera) {
		// return distance between position of camera and the intersection
		return (point - camera.getPosition()).norm();
	}
	
	bool checkIntersection() {
		GLfloat t = (triangle.normal.dotP(triangle.a) - triangle.normal.dotP(ray.pos)) / triangle.normal.dotP(ray.dir);
		if (t<0.0) return false;
	
		stein::Vector3f pa(triangle.a.x - ray.pos.x, triangle.a.y - ray.pos.y, triangle.a.z - ray.pos.z);
		stein::Vector3f pb(triangle.b.x - ray.pos.x, triangle.b.y - ray.pos.y, triangle.b.z - ray.pos.z);
		stein::Vector3f pc(triangle.c.x - ray.pos.x, triangle.c.y - ray.pos.y, triangle.c.z - ray.pos.z);
		
		// Test intersection against triangle ABC
		float u = ray.dir.scalarTriple(pc, pb);
		if (u<0.0) return false;
		
		float v = ray.dir.scalarTriple(pa, pc);
		if (v<0.0) return false;
		
		float w = ray.dir.scalarTriple(pb, pa);
		if (w<0.0) return false;

		// @TODO : since we are using float, we need to test value using epsilon
		if(u+v+w == 0.)
			return false;
			
		// Compute r, r=u*a+v*b+w*c, from barycentric coordinates (u, v, w)
		float denom = 1.0/(u+v+w);
		u*=denom;
		v*=denom;
		w*=denom;
		
		point.x = u * triangle.a.x + v * triangle.b.x + w * triangle.c.x;
		point.y = u * triangle.a.y + v * triangle.b.y + w * triangle.c.y;
		point.z = u * triangle.a.z + v * triangle.b.z + w * triangle.c.z;
		
		return true;
	}
};


#endif // _GEOMETRY_HPP_
