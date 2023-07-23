#type vertex
#version 460 core
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;

uniform mat4 u_ViewProjection;
uniform mat4 u_TransformationMatrix;
			
out vec4 v_Color;

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
}

#type fragment
#version 460 core
		
in vec4 v_Color;
out vec4 outColor;
void main()
{
	outColor = v_Color;
}