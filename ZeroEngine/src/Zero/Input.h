#pragma once
#include "Zero/Core.h"

namespace Zero
{
	class ZERO_API Input
	{
	 public:
		 inline static bool IsKeyPressed(int keyCode) { return s_Instance->IsKeyPressedImpl(keyCode); }
		 inline static bool IsKeyReleased(int keyCode) { return s_Instance->IsKeyReleasedImpl(keyCode); }
		 inline static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		 inline static bool IsMouseButtonReleased(int button) { return s_Instance->IsMouseButtonReleasedImpl(button); }
		 inline static std::pair<float,float> GetMousePos() { return s_Instance->GetMousePosImpl(); }
		 inline static std::pair<float, float> GetMousePosNormalized() {	 return s_Instance->GetMousePosNormalizedImpl();}
		 inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		 inline static float GetMouseY() { return s_Instance->GetMouseYImpl(); }
		 
	

	protected:
		virtual bool IsKeyPressedImpl(int keyCode) const = 0;
		virtual bool IsKeyReleasedImpl(int keyCode) const = 0;
		virtual bool IsMouseButtonPressedImpl(int button) const = 0;
		virtual bool IsMouseButtonReleasedImpl(int button) const = 0;

		virtual std::pair<float, float> GetMousePosImpl() const = 0;
		virtual std::pair<float, float> GetMousePosNormalizedImpl() const = 0;

		virtual float GetMouseXImpl() const = 0;
		virtual float GetMouseYImpl() const = 0;

		virtual std::pair<int, int> GetResolutionImpl() const = 0;
	
	private:
		static Input* s_Instance;
	};
}