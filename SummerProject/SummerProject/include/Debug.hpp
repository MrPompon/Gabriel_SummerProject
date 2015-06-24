// Debug.hpp

#ifndef DEBUG_HPP_INCLUDED
#define DEBUG_HPP_INCLUDED

namespace spaceshooter
{
	class Debug
	{
		// note(tommi): non-copyable
		Debug(const Debug&);
		Debug& operator=(const Debug&);

	public:
		Debug();
		~Debug();

		void Log(const std::string& format, ...);
	};
} // namespace spaceshooter

#endif // DEBUG_HPP_INCLUDED
