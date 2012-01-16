#include "Scene.hpp"
#include "Tools.hpp"
#include "Camera.hpp"
#include "Object.hpp"

#include <stdexcept>
#include <exception>
#include <iostream>

namespace stein {

GLuint Scene::defaultShaderID = 0;

// Default constructor
Scene::Scene() :
    defaultColor(Color::WHITE), defaultTransformation(Matrix4f::identity()), pCamera(NULL) {
    // Light creation
    GLfloat lightPosition[] = { 0.0, 5.0, 0.0, 1.0 };
    GLfloat lightPower = 1.0;
    setLight(lightPosition, lightPower);
    try {
		drawnObjectsTexture0IDs = new GLuint[maxDrawnObjects]();
		drawnObjectsTexture1IDs = new GLuint[maxDrawnObjects]();
		for (size_t i = 0; i < maxDrawnObjects; i++) {
			drawnObjectsTexture0IDs[i] = 0;
			drawnObjectsTexture1IDs[i] = 0;
		}
	} catch(...) {
		// @TODO : Find better exception
		std::cerr << "BUFFER OVERFLOW !!" << std::endl;
	}
	glEnable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_ALPHA_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
   
}

Scene::~Scene() {
    for (size_t i = 0; i < storedObjects.size(); ++i)
        delete storedObjects[i];
	delete [] drawnObjectsTexture0IDs;
	delete [] drawnObjectsTexture1IDs;
}

// Adds the object in the Objects library array, 
// after the last added object, and only if the array is not full, returns the index
Object& Scene::createObject(GLenum primitiveType) {
    std::cout << "Create object in Scene" << std::endl;
	const size_t size = storedObjects.size();
    if (size >= maxStoredObjects)
        throw std::runtime_error("maximum number of stored objects reached");
    storedObjects.push_back(new Object(size, primitiveType));
    return *storedObjects.back();
}

// Adds the index of stored object to draw in the drawnObjects array, 
// after the last added, and only if the array is not full
GLuint Scene::addObjectToDraw(GLuint indexStoredObject, GLuint shaderID) {
    const size_t size = drawnObjects.size();
    if (size >= maxDrawnObjects)
        throw std::runtime_error("maximum number of drawn objects reached");
    drawnObjects.push_back(ObjectInstance(indexStoredObject, shaderID, defaultTransformation, defaultColor));
    return size;
}

// Sets the color for the drawn object of index indexDrawObject
void Scene::setDrawnObjectColor(GLuint indexDrawnObject, const Color &color) {
    assert(indexDrawnObject<drawnObjects.size());
    drawnObjects[indexDrawnObject].color = color;
}

// Sets the transformation matrix for the drawn object of index indexDrawObject
void Scene::setDrawnObjectModel(GLuint indexDrawnObject, const Matrix4f &model) {
    assert(indexDrawnObject<drawnObjects.size());
    drawnObjects[indexDrawnObject].transformation = model;
}

// Sets the if of the shader to use on the drawn object of index indexDrawObject
void Scene::setDrawnObjectShaderID(GLuint indexDrawnObject, GLuint shaderID) {
    assert(indexDrawnObject<drawnObjects.size());
    drawnObjects[indexDrawnObject].shaderId = shaderID;
}

//Sets the ID of the texture to use on the drawn object of index indexDrawnObject
void Scene::setDrawnObjectTextureID(GLuint indexDrawnObject, GLuint textureUnit, GLuint textureID) {
	if (textureUnit == 0) drawnObjectsTexture0IDs[indexDrawnObject] = textureID;
	if (textureUnit == 1) drawnObjectsTexture1IDs[indexDrawnObject] = textureID;
}

// Sets the light
void Scene::setDefaultColor(const Color &color) {
    defaultColor = color;
    for (size_t i = 0; i < drawnObjects.size(); ++i)
        drawnObjects[i].color = defaultColor;
}

// Sets default transformation matrix
void Scene::setDefaultModel(const Matrix4f &_defaultModel) {
    defaultTransformation = _defaultModel;
    for (size_t i = 0; i < drawnObjects.size(); ++i)
        drawnObjects[i].transformation = defaultTransformation;
}

// Sets default shader ID
void Scene::setDefaultShaderID(GLuint id) {
    defaultShaderID = id;
}

// Sets light data to use in shader
void Scene::setLight(GLfloat * position, GLfloat power) {
    for (GLuint iCoord = 0; iCoord < 4; iCoord++)
        lightPosition[iCoord] = position[iCoord];
    lightPower = power;
}

// Decides what will elements drawn after this call will look like
void Scene::setAppearance(const ObjectInstance &instance) {
    const size_t shaderId = instance.shaderId;

    // We use the specific values of model per object
    setMatricesInShader(shaderId, instance.transformation, pCamera->getView(), pCamera->getPosition(), pCamera->getProjection());
    glUniform4fv(glGetUniformLocation(shaderId, "color"), 1, instance.color);

    // Specifies which VBO were filled
    const Object * pObject = storedObjects[instance.objectId];
    assert(pObject);
    setFilledDataInShader(shaderId, pObject->hasPrimitives(), pObject->hasNormals(), pObject->hasUvs(), pObject->hasColors());
    
    // Sets the light in the current shader
    setLightInShader(shaderId, lightPosition, lightPower);
    
    //Selects our current texture for unit 0
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, drawnObjectsTexture0IDs[instance.objectId]);
    
    //Selects our current texture for unit 1
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, drawnObjectsTexture1IDs[instance.objectId]);
    
    //std::cout << "Texture Id 0 : " << drawnObjectsTexture0IDs[instance.objectId] << std::endl;
    //std::cout << "Texture Id 1 : " << drawnObjectsTexture1IDs[instance.objectId] << std::endl;
    
	setTextureUnitsInShader(shaderId);
    
    glCullFace(GL_BACK);
}

// Draw all Objects
	void Scene::drawObjectsOfScene() {
		for (size_t i = 0; i < drawnObjects.size(); ++i) {
			const ObjectInstance &instance = drawnObjects[i];
			setAppearance(instance);
			storedObjects[instance.objectId]->drawObject();
		}
	}

} // namespace stein
