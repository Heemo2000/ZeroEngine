#pragma once
#include "Zero/Core.h"

enum class RendererAPI
{
	None = 0,
	OpenGL = 1
};


class ZERO_API Renderer
{
public:
	static inline RendererAPI GetAPI() { return s_RendererAPI; }
private:
	static RendererAPI s_RendererAPI;
};

