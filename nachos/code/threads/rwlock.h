//#include<stdio.h>
//#include<pthread.h>
#include <synch.h>

#ifndef _RWLOCK_H_
#define _RWLOCK_H_

class RWLock{
private:
#ifdef RWLOCK
	//pthread_cond_t readCV;
	//pthread_cond_t writeCV;
	//Semaphore readSem("Read", 1);
	//Semaphore writeSem("Write", 1);
	//int AW;
	//int WW;
	//int AR;
	//int WR;
#endif
	Semaphore lock("Lock", 1); 

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