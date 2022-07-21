#pragma once
#include "Zero/Core.h"


namespace Zero
{
	class ZERO_API Timestep
	{
	public:
		Timestep(float deltaTime = 0.0f, float fixedDeltaTime = 0.01667f) :
			m_DeltaTime(deltaTime), m_FixedDeltaTime(fixedDeltaTime) {}

		operator float() { return m_DeltaTime; }
		float GetFixedDeltaTimeInSec() { return m_FixedDeltaTime; }

		float GetDeltaTimeInSec() { return m_DeltaTime; }
		float GetDeltaTimeInMilliSec() { return m_DeltaTime * 1000.0f; }
	private:
		float m_DeltaTime;
		float m_FixedDeltaTime;
	};
}
