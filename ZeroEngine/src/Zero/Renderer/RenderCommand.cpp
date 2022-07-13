#include "zeropch.h"
#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRenderAPI.h"

namespace Zero
{
	RenderAPI* RenderCommand::s_RenderAPI = new OpenGLRenderAPI();
}