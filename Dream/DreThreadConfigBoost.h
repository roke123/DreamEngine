/////////////////////////////////////
// date:2014/9/12 16:09
// author: zou lei
/////////////////////////////////////

#ifndef __DRE_THREAD_CONFIG_BOOST_H__
#define __DRE_THREAD_CONFIG_BOOST_H__

#include "3rdParty\boost\boost\thread.hpp"

namespace dream
{

#define DRE_MUTEX_NAME_MODIFY(name, operation)					__dream_mutex_boost_##name##_##operation##__		

#define DRE_MUTEX(name)											mutable boost::recursive_mutex DRE_MUTEX_NAME_MODIFY(name, _);
#define DRE_STATIC_MUTEX(name)									static boost::recursive_mutex DRE_MUTEX_NAME_MODIFY(name, _);
#define DRE_STATIC_MUTEX_INSTANCE(name)							boost::recursive_mutex DRE_MUTEX_NAME_MODIFY(name, _);
#define DRE_SCOPED_LOCK_MUTEX(name)								boost::recursive_mutex::scoped_lock DRE_MUTEX_NAME_MODIFY(name, lock)(DRE_MUTEX_NAME_MODIFY(name, _));
#define DRE_LOCK_MUTEX_NAMED(name)								DRE_MUTEX_NAME_MODIFY(name, _).lock;
#define DRE_UNLOCK_MUTEX_NAMED(name)							DRE_MUTEX_NAME_MODIFY(name, _).unlock;

#define DRE_MUTEX_CONDITIONAL(mutex)							if (mutex)
#define DRE_THREAD_SYNCHRONISER(sync)							boost::condition_variable DRE_MUTEX_NAME_MODIFY(sync, _);
#define DRE_THREAD_WAIT(sync, mutex, lock)						DRE_MUTEX_NAME_MODIFY(sync, _).wait(lock);
#define DRE_THREAD_NOTIFY_ONE(sync)								DRE_MUTEX_NAME_MODIFY(sync, _).notify_one(); 
#define DRE_THREAD_NOTIFY_ALL(sync)								DRE_MUTEX_NAME_MODIFY(sync, _).notify_all(); 

#define DRE_RW_MUTEX(name)										mutable boost::shared_mutex DRE_MUTEX_NAME_MODIFY(sync, _);
#define DRE_LOCK_RW_MUTEX_READ(name)							boost::shared_lock<boost::shared_mutex> DRE_MUTEX_NAME_MODIFY(sync, read)(DRE_MUTEX_NAME_MODIFY(sync, _))
#define DRE_LOCK_RW_MUTEX_WRITE(name)							boost::unique_lock<boost::shared_mutex> DRE_MUTEX_NAME_MODIFY(sync, write)(DRE_MUTEX_NAME_MODIFY(sync, _))

#define DRE_THREAD_POINTER(T, var)								boost::thread_specific_ptr<T> DRE_MUTEX_NAME_MODIFY(var, _)
#define DRE_THREAD_POINTER_INIT(var)							DRE_MUTEX_NAME_MODIFY(var, _)(&deletePtr)
#define DRE_THREAD_POINTER_VAR(T, var)							boost::thread_specific_ptr<T> DRE_MUTEX_NAME_MODIFY(var, _)(&deletePtr<T>)
#define DRE_THREAD_POINTER_SET(var, expr)						DRE_MUTEX_NAME_MODIFY(var, _).reset(expr)
#define DRE_THREAD_POINTER_GET(var)								DRE_MUTEX_NAME_MODIFY(var, _).get()
#define DRE_THREAD_POINTER_DELETE(var)							DRE_MUTEX_NAME_MODIFY(var, _).reset(0)

#define DRE_THREAD_TYPE											boost::thread
#define DRE_THREAD_CREATE(name, worker) boost::thread* name = OGRE_NEW_T(boost::thread, MEMCATEGORY_GENERAL)(worker);
#define DRE_THREAD_DESTROY(name) OGRE_DELETE_T(name, thread, MEMCATEGORY_GENERAL)
#define DRE_THREAD_HARDWARE_CONCURRENCY boost::thread::hardware_concurrency()
#define DRE_THREAD_CURRENT_ID boost::this_thread::get_id()
#define DRE_THREAD_WORKER_INHERIT
	// Utility
#define OGRE_THREAD_SLEEP(ms) boost::this_thread::sleep(boost::posix_time::millisec(ms));

}

#endif	// end of __DRE_THREAD_CONFIG_BOOST_H__