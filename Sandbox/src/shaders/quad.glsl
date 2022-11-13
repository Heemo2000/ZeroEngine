#type vertex
#version 460 core
layout(location = 0) in vec3 a_Position;

uniform mat4 u_ViewProjection;
uniform mat4 u_TransformationMatrix;
			
vec4 cachedPos = vec4(0.0,0.0,0.0,1.0);
			
void calculatePosition(in mat4 viewProjection,in mat4 transformationMatrix,in vec3 vertexPosition,out vec4 result)
{
	result = viewProjection * transformationMatrix * vec4(vertexPosition,1.0);
}

void main()
{	
	calculatePosition(u_ViewProjection,u_TransformationMatrix,a_Position,cachedPos);
	gl_Position = cachedPos;
}

#type fragment
#version 460 core
			
out vec4 outColor;
void main()
{
	outColor = vec4(1.0f,1.0f,1.0,1.0f);
}