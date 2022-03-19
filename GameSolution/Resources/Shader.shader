#defaultVertexShader
#version 330 core
layout(location = 0) in vec4 aPos;
layout(location = 1) in vec2 aTextCoords;

out vec2 textCoords;

//uniform mat4 scale;
//uniform vec2 move;
//uniform mat4 rotation;
uniform vec2 shift;

void main()
{
	textCoords = vec2(aTextCoords.x + shift.x, aTextCoords.y + shift.y);
	//vec4 varTest = scale * rotation * vec4(aPos.x, aPos.y, 0.0, 1.0);
	gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);
	//gl_Position = scale * vec4(aPos.x + move.x, aPos.y + move.y, 0.0f, 1.0f);

};
#Ende

#defaultFragmentShader
#version 330 core
out vec4 FragColor;
in vec2 textCoords;
uniform sampler2D ourTexture;

void main()
{
	vec4 texColor = texture(ourTexture, textCoords);
	if (texColor.a < 0.1) {
		discard;
	}

	FragColor = texColor;

}
#Ende