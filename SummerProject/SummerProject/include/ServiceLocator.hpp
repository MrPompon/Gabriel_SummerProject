// ServiceLocator.hpp

#ifndef SERVICELOCATOR_HPP_INCLUDED
#define SERVICELOCATOR_HPP_INCLUDED

#include <cassert>

namespace spaceshooter
{
	template <class T>
	class ServiceLocator
	{
	public:
		static void SetService(T* service)
		{
			ms_service = service;
		}

		static T* GetService()
		{
			assert(ms_service);
			return ms_service;
		}

	private:
		static T* ms_service;
	};

	template <class T>
	T* ServiceLocator<T>::ms_service = nullptr;
} // namespace spaceshooter

#endif // SERVICELOCATOR_HPP_INCLUDED
