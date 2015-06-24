// AbstractState.hpp

#ifndef ABSTRACTSTATE_HPP_INCLUDED
#define ABSTRACTSTATE_HPP_INCLUDED

namespace spaceshooter
{
	class AbstractState
	{
	public:
		virtual ~AbstractState();
		virtual bool Enter() = 0;
		virtual void Exit() = 0;
		virtual bool Update(float deltatime) = 0;
		virtual void Draw() = 0;
		virtual std::string GetNextState() = 0;
	};
} // namespace spaceshooter

#endif // ABSTRACTSTATE_HPP_INCLUDED
