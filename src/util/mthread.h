/*
 * mthread.h
 *
 * Provides functions for running pthreads on C++ member functions.
 */
#ifndef MTHREAD_H_
#define MTHREAD_H_

#include "pthread.h"

/*
 * Template class that stores pthread data and provides functions for relaying
 * the call to the original member function.
 */
template<typename T, typename R=void>
class mthread {
public:

	/*
	 * Create and run a new pthread on a member function that does not require
	 * arguments.
	 *
	 * Usage:
	 * Asynchronously call the following function:
	 *     T *p_ref = new T();
	 *     p_ref->f_start_routine();
	 *
	 * Params:
	 *     p_thread - the pthread to run through the function
	 *     p_attr - the pthread attributes
	 *     p_ref - reference to the calling object
	 *     f_start_routine - function pointer to the member function of type <T>
	 *
	 * Returns:
	 *     on success, returns 0; on error, it returns an error number and the
	 *     contents of <p_thread> are undefined
	 */
	static int create(pthread_t *p_thread, const pthread_attr_t *p_attr, T *p_ref, R (T::*f_start_routine)()) {
		return pthread_create(p_thread, p_attr, func_no_args, (void *) new mthread(p_ref, f_start_routine));
	}

	/*
	 * Create and run a new pthread on a member function that requires arguments.
	 *
	 * Usage:
	 * Asynchronously call the following function:
	 *     T *p_ref = new T();
	 *     void *data = (void *)(some_data);
	 *     p_ref->f_start_routine(data);
	 *
	 * Params:
	 *     p_thread - the pthread to run through the function
	 *     p_attr - the pthread attributes
	 *     p_ref - reference to the calling object
	 *     f_start_routine - function pointer to the member function of type <T>
	 *     p_arg - the argument to pass to the member function, of type (void *)
	 *
	 * Returns:
	 *     on success, returns 0; on error, it returns an error number and the
	 *     contents of <p_thread> are undefined
	 */
	static int create(pthread_t *p_thread, const pthread_attr_t *p_attr, T *p_ref, R (T::*f_start_routine)(void *), void *p_arg) {
		return pthread_create(p_thread, p_attr, func_args, (void *) new mthread(p_ref, f_start_routine, p_arg));
	}

private:

	/*
	 * Static function called by the pthread. The argument passed to the
	 * function is an mthread object containing the data of the original
	 * function call. The original call is performed in this function using
	 * the original object reference, member function pointer, and argument
	 * to be passed.
	 * This function is used if the original member function requires an
	 * argument to be passed.
	 *
	 * Parameters:
	 *     p_arg - pointer to mthread object containing the original call data.
	 */
	static void *func_args(void *p_arg) {
		mthread *p_wrap = (mthread *) p_arg;
		(p_wrap->mp_ref->*p_wrap->mf_arg)(p_wrap->mp_arg);

		delete p_wrap;
		return 0;
	}

	/*
	 * Static function called by the pthread. The argument passed to the
	 * function is an mthread object containing the data of the original
	 * function call. The original call is performed in this function using
	 * the original object reference and member function pointer.
	 * This function is used if the original member function does not require an
	 * argument to be passed.
	 *
	 * Parameters:
	 *     p_arg - pointer to mthread object containing the original call data.
	 */
	static void *func_no_args(void *p_arg) {
		mthread *p_wrap = (mthread *) p_arg;
		(p_wrap->mp_ref->*p_wrap->mf_no_arg)();

		delete p_wrap;
		return 0;
	}

	/*
	 * mp_ref - reference to the original calling object
	 * mp_arg - reference to the original argument to be passed, if one exists
	 * mf_no_arg - reference to the original member function; used if the
	 *             the function did not require an argument.
	 * mf_arg - reference to the original member function; used if the function
	 *          required an argument.
	 */
	T *mp_ref;
	void *mp_arg;
	R (T::*mf_no_arg)();
	R (T::*mf_arg)(void *);

	/*
	 * Create a new mthread object to wrap a function call with no argument.
	 *
	 * Params:
	 *     p_ref - pointer to the original calling object
	 *     f_func - pointer to the original member function
	 */
	mthread(T *p_ref, R (T::*f_func)()) {
		mp_ref = p_ref;
		mf_arg = NULL;
		mf_no_arg = f_func;
		mp_arg = NULL;
	}

	/*
	 * Create a new mthread object to wrap a function call with an argument.
	 *
	 * Params:
	 *     p_ref - pointer to the original calling object
	 *     f_func - pointer to the original member function
	 *     p_arg - pointer to the original function argument
	 */
	mthread(T *p_ref, R (T::*f_func)(void *), void *p_arg) {
		mp_ref = p_ref;
		mf_arg = f_func;
		mf_no_arg = NULL;
		mp_arg = p_arg;
	}

	/*
	 * Set the reference and argument pointers to NULL.
	 * Do not deallocate any data.
	 */
	virtual ~mthread() {
		mp_ref = NULL;
		mp_arg = NULL;
	}

};

/*
 * Create and run a new pthread on a member function that does not require
 * arguments.
 *
 * Usage:
 * Asynchronously call the following function:
 *     T *p_ref = new T();
 *     p_ref->f_start_routine();
 *
 * Params:
 *     p_thread - the pthread to run through the function
 *     p_attr - the pthread attributes
 *     p_ref - reference to the calling object
 *     f_start_routine - function pointer to the member function of type <T>
 *
 * Returns:
 *     on success, returns 0; on error, it returns an error number and the
 *     contents of <p_thread> are undefined
 */
template<typename T, typename R=void>
int mthread_create(pthread_t *p_thread, const pthread_attr_t *p_attr, T *p_ref, R (T::*f_start_routine)()) {
	return mthread<T,R>::create(p_thread, p_attr, p_ref, f_start_routine);
}

/*
 * Create and run a new pthread on a member function that requires arguments.
 *
 * Usage:
 * Asynchronously call the following function:
 *     T *p_ref = new T();
 *     void *data = (void *)(some_data);
 *     p_ref->f_start_routine(data);
 *
 * Params:
 *     p_thread - the pthread to run through the function
 *     p_attr - the pthread attributes
 *     p_ref - reference to the calling object
 *     f_start_routine - function pointer to the member function of type <T>
 *     p_arg - the argument to pass to the member function, of type (void *)
 *
 * Returns:
 *     on success, returns 0; on error, it returns an error number and the
 *     contents of <p_thread> are undefined
 */
template<typename T, typename R=void>
int mthread_create(pthread_t *p_thread, const pthread_attr_t *p_attr, T *p_ref, R (T::*f_start_routine)(void *), void *p_arg) {
	return mthread<T,R>::create(p_thread, p_attr, p_ref, f_start_routine, p_arg);
}

#endif
