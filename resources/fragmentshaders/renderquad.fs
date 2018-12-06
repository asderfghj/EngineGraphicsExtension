#version 330 core
in vec2 TexCoord;

uniform sampler2D texture;

void main()
{
	//gl_FragColor = vec4(1.0, 0.0, 1.0, 1.0);
	//float averageColor = (texture2D(texture, TexCoord).x + texture2D(texture, TexCoord).y + texture2D(texture, TexCoord).z) / 3;
	
	gl_FragColor = texture2D(texture, TexCoord);
}