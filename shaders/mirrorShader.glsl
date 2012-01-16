#ifdef VERTEX

// Attributes : per vertex data
in vec4 vertexPosition;
in vec3 vertexNormal;
in vec2 vertexUvs;
in vec4 vertexColor;

// Varyings : data to transmit to fragments
smooth out vec4 posNorm;

void main()
{
	posNorm=projection ∗ view ∗ model ∗ vertexPosition;
	gl Position = posNorm;
}

#endif


#ifdef FRAGMENT

// Varyings : data receved and interpolated from the vertex shaders
smooth in vec4 posNorm;

// Final output
out vec4 fragColor;

void main()
{
	vec2 uvs=posNorm.xy/posNorm.w;
	uvs=(uvs+1.0)/2.0;
	fragColor=vec4(texture2D(textureUnitDiffuse, uvs).rgb, 1.0);
	//fragColor=mix(vec4(texture2D(textureUnitDiffuse, uvs).rgb, 1.0), vec4(1.0), 0.5);
}

#endif
