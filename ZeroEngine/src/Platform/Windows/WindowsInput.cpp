#include "zeropch.h"
#include "WindowsInput.h"
#include "Zero/Application.h"
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

	std::pair<float, float> WindowsInput::GetMousePosNormalizedImpl() const
	{
		auto mousePos = GetMousePosImpl();
		auto resolution = GetResolutionImpl();

		float x = -1.0f + 2.0f * (mousePos.first / (float)resolution.first);
		float y = 1.0f - 2.0f * (mousePos.second / (float)resolution.second);

		std::pair<float, float> normalizedPosition;
		normalizedPosition.first = x;
		normalizedPosition.second = y;

		return normalizedPosition;
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
	std::pair<int, int> WindowsInput::GetResolutionImpl() const
	{
		GLFWwindow* nativeWindow = static_cast<GLFWwindow*>(Application::GetInstance().GetWindow()->GetNativeWindow());

		int width, height;

		glfwGetWindowSize(nativeWindow, &width, &height);

		return std::pair<int, int>(width, height);
	}
}