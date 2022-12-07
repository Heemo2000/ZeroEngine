#type vertex
#version 460 core
layout(location = 0) in vec3 a_Position;

uniform mat4 u_ViewProjection;
uniform mat4 u_TransformationMatrix;
uniform vec3 offsets[30*30];			

vec4 cachedPos = vec4(0.0,0.0,0.0,1.0);

void calculatePosition(in mat4 viewProjection,in mat4 transformationMatrix,in vec3 vertexPosition,in vec3 offset,out vec4 result)
{
	result = viewProjection * transformationMatrix * vec4(vertexPosition + offset,1.0);
}

   void main()
{	
	calculatePosition(u_ViewProjection,u_TransformationMatrix,a_Position,offsets[gl_InstanceID],cachedPos);
	gl_Position = cachedPos;
}

#type fragment
#version 460 core
			
uniform vec4 u_Color;
out vec4 outColor;
void main()
{
	outColor = u_Color;
}