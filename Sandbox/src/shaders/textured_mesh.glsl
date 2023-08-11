#type vertex
#version 460 core
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TexCoord;
layout(location = 3) in float a_TexIndex;

uniform mat4 u_ViewProjection;
uniform mat4 u_TransformationMatrix;
			
out vec4 v_Color;
out vec2 v_TexCoord;
out float v_TexIndex;
vec4 cachedPos = vec4(0.0,0.0,0.0,1.0);
			

void calculatePosition(in mat4 viewProjection,in mat4 transformationMatrix,in vec3 vertexPosition,out vec4 result)
{
	result = viewProjection * transformationMatrix * vec4(vertexPosition,1.0);
}

void main()
{	
	calculatePosition(u_ViewProjection,u_TransformationMatrix,a_Position,cachedPos);
	gl_Position = cachedPos;
	v_Color = a_Color;
	v_TexCoord = a_TexCoord;
	v_TexIndex = a_TexIndex;
}

#type fragment
#version 460 core

layout(location = 0)out vec4 outColor;

in vec4 v_Color;
in vec2 v_TexCoord;
in float v_TexIndex;

uniform sampler2D u_TexUnits[32];


void main()
{
	int texIndex = int(v_TexIndex);
	vec4 requiredColor = texture(u_TexUnits[texIndex], v_TexCoord) * v_Color;
	if(requiredColor.a < 0.1)
	{
	  discard;
	}
	outColor = requiredColor;
}