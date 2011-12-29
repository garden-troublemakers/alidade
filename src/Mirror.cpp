#include "Mirror.hpp"

using namespace stein;
using namespace std;

Mirror::Mirror(const Scene * const pScene) :
	Camera(), m_pScene(pScene),
	m_frame(m_pScene->createObject(GL_TRIANGLES)), m_surface(m_pScene->createObject(GL_TRIANGLES))
{
    buildSquare(m_frame, .6);
    buildSquare(m_surface);
    m_pScene->addObjectToDraw(m_frame.id);
    m_pScene->addObjectToDraw(m_surface.id);
    m_pScene->setDrawnObjectColor(m_frame.id, Color(WHITE));
    m_pScene->setDrawnObjectColor(m_surface.id, Color(GRAY));
}

virtual Mirror::~Mirror() {

}

