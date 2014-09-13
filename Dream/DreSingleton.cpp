#include "DreSingleton.h"

namespace dream
{
	template<class T>
	T* Singleton<T>::mInstance = nullptr;
}