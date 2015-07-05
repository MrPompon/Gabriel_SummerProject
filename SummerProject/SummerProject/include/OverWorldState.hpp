// OverWorldState.hpp

#ifndef OverWorldState_HPP_INCLUDED
#define OverWorldState_HPP_INCLUDED

#include "AbstractState.hpp"

namespace spaceshooter
{
	class OverWorldState : public AbstractState
	{
	public:
		virtual bool Enter();
		virtual void Exit();
		virtual bool Update(float deltatime);
		virtual void Draw();
		virtual std::string GetNextState();
	private:

	};
}
// namespace spaceshooter

#endif // OverWorldState_HPP_INCLUDED