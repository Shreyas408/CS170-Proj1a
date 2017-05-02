//#include<stdio.h>
//#include<pthread.h>
#include <synch.h>

#ifndef _RWLOCK_H_
#define _RWLOCK_H_

class RWLock{
private:
	#ifndef P1_RWLOCK
	#ifdef P1_SEMAPHORE
	//Task 1 code (using semaphore in place of mutex)
	Semaphore* sem;
	#else
	//Task 2 code (using NACHOS Lock)
	Lock* lock;
	#endif
	#else
	//Task 3 code (full rwlock)
	Condition* readCV;
	Condition* writeCV;
	Lock* lock;
	int AW;
	int WW;
	int AR;
	int WR;
	#endif
public:
		RWLock();
    	~RWLock();
    //Reader
    	void startRead();
    	void doneRead();
    // Writer
    	void startWrite();
    	void doneWrite();
};

#endif