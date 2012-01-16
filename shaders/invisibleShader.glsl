// lightingShader.glsl
// Template for OpenGL 3.*
// N. Dommanget dommange@univ-mlv.fr


#ifdef _VERTEX_

//uniform vec4 filledData;

// Attributes : per vertex data
 in vec4 vertexPosition;
 in vec3 vertexNormal;
 in vec2 vertexUvs;
 in vec4 vertexColor;

// Varyings : data to transmit to fragments
 smooth out vec4 position;
 smooth out vec4 normal;
 smooth out vec2 uvs;
 smooth out vec4 localColor;

void main()
{
    if (filledData[0]) position = model * vertexPosition;
    if (filledData[1]) normal = model * vec4(vertexNormal, 0.0);
    if (filledData[2]) uvs = vertexUvs;
    if (filledData[3]) localColor = vertexColor;

    gl_Position = projection * view * model * vertexPosition;
}

#endif




#ifdef _FRAGMENT_


// Varyings : data receved and interpolated from the vertex shaders
 in vec4 position;
 in vec4 normal;
 in vec2 uvs;
 in vec4 localColor;

// Final output
 out vec4 fragColor;

void main()
{

	fragColor = vec4( 1., 0., 0., 0.2); 

}

#endif
