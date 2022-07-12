#pragma once


namespace Zero
{
	class ZERO_API RenderingContext
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};
}