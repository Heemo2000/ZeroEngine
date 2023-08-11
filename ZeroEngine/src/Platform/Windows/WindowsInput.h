#pragma once
#include "Zero/Input.h"
#include "Platform/Windows/WindowsWindow.h"

#include <GLFW/glfw3.h>
namespace Zero
{
	
	class WindowsInput : public Input
	{
	 protected:
		virtual bool IsKeyPressedImpl(int keyCode) const override;
		virtual bool IsKeyReleasedImpl(int keyCode) const override;
		virtual bool IsMouseButtonPressedImpl(int button) const override;
		virtual bool IsMouseButtonReleasedImpl(int button) const override;
		virtual std::pair<float,float> GetMousePosImpl() const override;
		virtual std::pair<float, float> GetMousePosNormalizedImpl() const override;
		virtual float GetMouseXImpl() const override;
		virtual float GetMouseYImpl() const override;
		virtual std::pair<int, int> GetResolutionImpl() const override;
	};
}