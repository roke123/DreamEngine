/////////////////////////////////////////
// date: 2014/9/12 15:54
// author: zou lei
/////////////////////////////////////////

#ifndef __DRE_THREAD_CONFIG_NONE_H__
#define __DRE_THREAD_CONFIG_NONE_H__

namespace dream
{

#define OGRE_AUTO_MUTEX
#define OGRE_LOCK_AUTO_MUTEX
#define OGRE_MUTEX(name)
#define OGRE_STATIC_MUTEX(name)
#define OGRE_STATIC_MUTEX_INSTANCE(name)
#define OGRE_LOCK_MUTEX(name)
#define OGRE_LOCK_MUTEX_NAMED(mutexName, lockName)
#define OGRE_AUTO_SHARED_MUTEX
#define OGRE_LOCK_AUTO_SHARED_MUTEX
#define OGRE_NEW_AUTO_SHARED_MUTEX
#define OGRE_DELETE_AUTO_SHARED_MUTEX
#define OGRE_COPY_AUTO_SHARED_MUTEX(from)
#define OGRE_SET_AUTO_SHARED_MUTEX_NULL
#define OGRE_MUTEX_CONDITIONAL(name) if(true)
#define OGRE_RW_MUTEX(name)
#define OGRE_LOCK_RW_MUTEX_READ(name)
#define OGRE_LOCK_RW_MUTEX_WRITE(name)
#define OGRE_THREAD_SYNCHRONISER(sync) 
#define OGRE_THREAD_WAIT(sync, lock) 
#define OGRE_THREAD_NOTIFY_ONE(sync) 
#define OGRE_THREAD_NOTIFY_ALL(sync) 
#define OGRE_THREAD_POINTER(T, var) T* var
#define OGRE_THREAD_POINTER_INIT(var) var(0)
#define OGRE_THREAD_POINTER_VAR(T, var) T* var = 0
#define OGRE_THREAD_POINTER_SET(var, expr) var = expr
#define OGRE_THREAD_POINTER_GET(var) var
#define OGRE_THREAD_POINTER_DELETE(var) { OGRE_DELETE var; var = 0; }
#define OGRE_THREAD_SLEEP(ms)
#define OGRE_THREAD_WORKER_INHERIT

}

#endif	// end of __DRE_THREAD_CONFIG_NONE_H__