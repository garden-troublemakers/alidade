#ifndef _MIRROR_HPP_
#define _MIRROR_HPP_

#include <stein/Builders.hpp>
#include <stein/Camera.hpp>
#include <cstdlib>

enum MirrorType {
	GRAY = 0, BLUE = 1, RED = 2
};

class Mirror : stein::Camera {
	private :
		Scene* m_pScene;
		Object m_frame;
		Object m_surface;
		
		Object _buildFrame();
		Object _buildSurface();
	public:
		Mirror(Scene* scene);
		~Mirror();
		//void updateSurface(); // called at each frame
};

#endif // _MIRROR_HPP_
