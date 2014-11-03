#ifndef THREADS_H_93AC6A3A_6098_11E4_B320_10FEED04CD1C
#define THREADS_H_93AC6A3A_6098_11E4_B320_10FEED04CD1C

#include <pthread.h>
#include <signal.h>
#include <sys/time.h>

class ThreadBase {
public:
	ThreadBase() : mpThread(NULL) {
	}

	virtual ~ThreadBase() {
	}

	bool start() {
		if (NULL == mpThread) { // create a new thread
			mpThread = new pthread_t;
			int ok = pthread_create(mpThread, NULL, ThreadBase::Dispatcher, this);
			if (ok != 0) {
				return false;
			}
		} else {
			return false;
		}
		return true;
	}

	bool join() {
		if (NULL != mpThread) { // join with a terminated thread
			int ok = pthread_join(*mpThread, NULL);
			if (ok != 0) {
				return false;
			}
			delete mpThread;
			mpThread = NULL;
		}
		return true;
	}

	bool detach() { // detach a thread
		if (NULL != mpThread) {
			int ok = pthread_detach(*mpThread);
			if (ok != 0) {
				return false;
			}
		}
		return true;
	}

	bool cancel() { // send a cancellation request to a thread
		if (NULL != mpThread) {
			int ok = pthread_cancel(*mpThread);
			if (ok != 0) {
				return false;
			}
		}
		return true;
	}

	bool kill(int sig) { // send a signal to a thread
		if (NULL != mpThread) {
			int ok = pthread_kill(*mpThread, sig);
			if (ok != 0) {
				return false;
			}
		}
		return true;
	}

	virtual void run() = 0;

private:
	pthread_t *mpThread;

	static void * Dispatcher(void *arg) {
		ThreadBase *tb(static_cast<ThreadBase *>(arg));
		tb->run();
		return NULL;
	}
};

class Mutex {
friend class Condition;
public:
	class MutexAttr {
	friend class Mutex;
	public:
		MutexAttr(int kind) {
			pthread_mutexattr_init(&mPthrMutexAttr); settype(kind);
		}

		MutexAttr() {
			pthread_mutexattr_init(&mPthrMutexAttr);
		}

		~MutexAttr() {
			pthread_mutexattr_destroy(&mPthrMutexAttr);
		}
		int settype(int kind) {
			return pthread_mutexattr_settype(&mPthrMutexAttr, kind);
		}

		int gettype(int *kind) {
			return pthread_mutexattr_gettype(&mPthrMutexAttr, kind);
		}

	private:
		pthread_mutexattr_t mPthrMutexAttr;
	};

	class MutexHolder {
	public:
		MutexHolder(Mutex *m): m(m) {
			m->lock();
		}

		~MutexHolder() { m->unlock(); }

	private:
		Mutex *m;
	};

	class MutexHolderTry {
	public:
		MutexHolderTry(Mutex *m): m(m), locked(false) {
			if (!(m->trylock())) locked = true;
		}

		~MutexHolderTry() {
			if (locked) m->unlock();
		}

		bool havelock() const {
			return locked;
		}

	private:
		Mutex *m;
		bool locked;
	};

	Mutex(const pthread_mutex_t initializer = Mutex::Initializer): mPthrMutex(initializer) {
	}

	Mutex(const MutexAttr *attr) {
		pthread_mutex_init(&mPthrMutex, &attr->mPthrMutexAttr);
	}

	~Mutex() {
		pthread_mutex_destroy(&mPthrMutex);
	}

	int lock() {
		return pthread_mutex_lock(&mPthrMutex);
	}

	int trylock() {
		return pthread_mutex_trylock(&mPthrMutex);
	}

	int unlock() {
		return pthread_mutex_unlock(&mPthrMutex);
	}

protected:
	static const pthread_mutex_t Initializer;

private:
	pthread_mutex_t mPthrMutex;
};

class RecursiveMutex: public Mutex {
public:
	RecursiveMutex(): Mutex(RecursiveMutex::Initializer) {}

protected:
	static const pthread_mutex_t Initializer;
};

class Condition {
public:
	Condition(const pthread_cond_t initialiser = Condition::Initializer): mPthrCond(initialiser) {
	}

	Condition(pthread_condattr_t *cond_attr) {
		pthread_cond_init(&mPthrCond, cond_attr);
	}

	~Condition() {
		pthread_cond_destroy(&mPthrCond);
	}

	int signal() {
		return pthread_cond_signal(&mPthrCond);
	}

	int broadcast() {
		return pthread_cond_broadcast(&mPthrCond);
	}

	int wait(Mutex &mutex) {
		return pthread_cond_wait(&mPthrCond, &mutex.mPthrMutex);
	}

	int timedWait(Mutex &mutex, const struct timespec *abstime) {
		return pthread_cond_timedwait(&mPthrCond, &mutex.mPthrMutex, abstime);
	}

	int timedWait(Mutex &mutex, long usec) {
		struct timeval now;
		struct timespec timeout;
		gettimeofday(&now, 0);
		timeout.tv_sec = now.tv_sec + usec / 1000000;
		timeout.tv_nsec = (now.tv_usec + usec % 1000000) * 1000;
		if(timeout.tv_nsec >= 1000000000) {
			timeout.tv_nsec -= 1000000000;
			timeout.tv_sec++;
		}
		return pthread_cond_timedwait(&mPthrCond, &mutex.mPthrMutex, &timeout);
	}

protected:
	static const pthread_cond_t Initializer;

private:
	pthread_cond_t mPthrCond;
};

class RWLock {
public:
	RWLock(const pthread_rwlock_t initialiser = RWLock::Initializer): mPthrRWLock(initialiser) {
	}

	RWLock(pthread_rwlockattr_t *rwlock_attr) {
		pthread_rwlock_init(&mPthrRWLock, rwlock_attr);
	}

	~RWLock() {
		pthread_rwlock_destroy(&mPthrRWLock);
	}

	int lockRead() {
		return pthread_rwlock_rdlock(&mPthrRWLock);
	}

	int tryReadLock() {
		return pthread_rwlock_tryrdlock(&mPthrRWLock);
	}

	int lockWrite() {
		return pthread_rwlock_wrlock(&mPthrRWLock);
	}

	int unlock() {
		return pthread_rwlock_unlock(&mPthrRWLock);
	}

	class ReadLockHolder {
	public:
		ReadLockHolder(RWLock *l): l(l) {
			l->lockRead();
		}
		~ReadLockHolder() {
			l->unlock();
		}

	private:
		RWLock *l;
	};

	class WriteLockHolder {
	public:
		WriteLockHolder(RWLock *l): l(l) {
			l->lockWrite();
		}

		~WriteLockHolder() {
			l->unlock();
		}

	private:
		RWLock *l;
	};

protected:
	static const pthread_rwlock_t Initializer;

private:
	pthread_rwlock_t mPthrRWLock;
};

#endif // THREADS_H_93AC6A3A_6098_11E4_B320_10FEED04CD1C
