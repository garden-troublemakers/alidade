#include "Obj.hpp"
#include "Geometry.hpp"

bool intersectRayTriangle(const Ray & ray, const Triangle & triangle, Intersection * pIntersection) {
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

	pIntersection = new Intersection(ray, triangle);

	pIntersection->point.x = u * triangle.a.x + v * triangle.b.x + w * triangle.c.x;
	pIntersection->point.y = u * triangle.a.y + v * triangle.b.y + w * triangle.c.y;
	pIntersection->point.z = u * triangle.a.z + v * triangle.b.z + w * triangle.c.z;
	
	return true;
}

bool intersectRayBox(const Ray & ray, const Box & box, stein::Camera * pRefCam) {
	return true;
}

bool intersectRayObject(const Ray & ray, Obj * pObject, stein::Camera * pRefCam, Intersection * pIntersection) {
	Intersection * pTriangleIntersection = NULL;
	/*
	 *	Not needed because we only have basic objects, but may speed up the loop for complex objects.
	 *
	if(!!pObject->pBoundingBox)
		if(!intersectRayBox(ray, pObject->pBoundingBox, refCam))
			return false;
	*/

	// loop on primitives
	std::list<Triangle> triangles = pObject->getTrianglesList();
	for(std::list<Triangle>::iterator t = triangles.begin(); t != triangles.end(); ++t) { // get & test intersection
		if(intersectRayTriangle(ray, *t, pTriangleIntersection)) {
			std::cout << "intersection" << std::endl;
			if(!pIntersection || (pTriangleIntersection->computeDepth(*pRefCam) < pIntersection->computeDepth(*pRefCam))) {  // test its depth
				delete pIntersection;
				pIntersection = pTriangleIntersection;
			} else {
				delete pTriangleIntersection;
				pTriangleIntersection = NULL;
			}
		} else {
			delete pTriangleIntersection;
			pTriangleIntersection = NULL;
		}
	}
	return !!pTriangleIntersection;
}
