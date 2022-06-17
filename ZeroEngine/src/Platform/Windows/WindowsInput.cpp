#include "zeropch.h"
#include "WindowsInput.h"

namespace Zero
{
	Input* Input::s_Instance = new WindowsInput();
	bool WindowsInput::IsKeyPressedImpl(int keyCode) const
	{
		
		GLFWwindow* nativeWindow = static_cast<GLFWwindow*>(Application::GetInstance().GetWindow()->GetNativeWindow());
		auto state = glfwGetKey(nativeWindow, keyCode);

		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsKeyReleasedImpl(int keyCode) const
	{
		GLFWwindow* nativeWindow = static_cast<GLFWwindow*>(Application::GetInstance().GetWindow()->GetNativeWindow());
		auto state = glfwGetKey(nativeWindow, keyCode);

		return state == GLFW_RELEASE;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int button) const
	{
		GLFWwindow* nativeWindow = static_cast<GLFWwindow*>(Application::GetInstance().GetWindow()->GetNativeWindow());

		auto state = glfwGetMouseButton(nativeWindow, button);
		return state == GLFW_PRESS;
	}

	bool WindowsInput::IsMouseButtonReleasedImpl(int button) const
	{
		GLFWwindow* nativeWindow = static_cast<GLFWwindow*>(Application::GetInstance().GetWindow()->GetNativeWindow());

		auto state = glfwGetMouseButton(nativeWindow, button);
		return state == GLFW_RELEASE;
	}

	std::pair<float, float> WindowsInput::GetMousePosImpl() const
	{
		GLFWwindow* nativeWindow = static_cast<GLFWwindow*>(Application::GetInstance().GetWindow()->GetNativeWindow());

		std::pair<float, float> cursorPosition;
		double mouseX, mouseY;
		glfwGetCursorPos(nativeWindow, &mouseX, &mouseY);

		cursorPosition.first = (float)mouseX;
		cursorPosition.second = (float)mouseY;

		return cursorPosition;
	}

	float WindowsInput::GetMouseXImpl() const
	{
		auto [x, y] = GetMousePosImpl();
		return x;
	}

	float WindowsInput::GetMouseYImpl() const
	{
		auto [x, y] = GetMousePosImpl();
		return y;
	}
}