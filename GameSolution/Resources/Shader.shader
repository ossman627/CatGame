#VertexShader
#version 330 core

layout(location = 0) in vec4 aPos;
//layout(location = 1) in vec2 aTextCoords;

//out vec2 textCoords;

//uniform mat4 scale;
//uniform vec2 move;
//uniform mat4 rotation;

void main()
{
	//textCoords = aTextCoords;
	//vec4 varTest = scale * rotation * vec4(aPos.x, aPos.y, 0.0, 1.0);
	gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);
	//gl_Position = scale * vec4(aPos.x + move.x, aPos.y + move.y, 0.0f, 1.0f);

};

#FragmentShader
#version 330 core

out vec4 FragColor;
//in vec2 textCoords;
//uniform sampler2D ourTexture;

void main()
{
	/*vec4 texColor = texture(ourTexture, textCoords);
	if (texColor.a < 0.1) {
		discard;
	}
	*/
	FragColor = vec4(1.0, 0.5, 0.5, 1.0);

}
#Ende