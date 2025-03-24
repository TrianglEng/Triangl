#pragma once

namespace Triangl
{
	struct Timestep
	{
		float Time = 0.0f;

		Timestep() = default;
		Timestep(const Timestep&) = default;
		Timestep& operator=(const Timestep&) = default;

		Timestep(float time)
			: Time(time) {}

		Timestep& operator=(float time)
		{
			Time = time;
			return *this;
		}

		float GetTime() const { return Time; }
		float operator()() const { return Time; }
		operator float() const { return Time; }
	};

	template <typename OStream>
	inline OStream& operator<<(OStream& stream, const Timestep& ts)
	{
		return stream << ts.Time;
	}
}
