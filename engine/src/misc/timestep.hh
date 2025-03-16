#ifndef TRIANGL_MISC_TIMESTEP_HH
#define TRIANGL_MISC_TIMESTEP_HH

namespace triangl {

	struct timestep
	{
		float time = 0.0f;

		timestep() = default;
		timestep(const timestep&) = default;
		timestep& operator=(const timestep&) = default;

		timestep(float t)
			: time(t) {}

		timestep& operator=(float t)
		{
			time = t;
			return *this;
		}

		float get_time() const { return time; }
		float operator()() const { return time; }
		operator float() const { return time; }
	};

	template <typename O>
	inline O& operator<<(O& stream, const timestep& ts)
	{
		return stream << ts.time;
	}

}

#endif
