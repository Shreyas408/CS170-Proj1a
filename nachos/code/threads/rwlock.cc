#include <semaphore.h>
#include <pthread.h>
#include "rwlock.h"

#ifndef P1_RWLOCK
#ifdef P1_SEMAPHORE
//Task 1 code (using semaphore in place of mutex)
RWLock::RWLock() { 
	sem = new Semaphore("Semaphore Lock", 1);
}
RWLock::~RWLock() {
	delete sem;
}
//NOTE that for Task 1, startRead should be the same as startWrite
void RWLock::startRead() { 
	sem->P();
} 
void RWLock::startWrite() { 
	sem->P();
}
//NOTE that for Task 1, doneRead should be the same as doneWrite
void RWLock::doneRead() { 
	sem->V();
} 
void RWLock::doneWrite() { 
	sem->V();
}
#else
//Task 2 code (using NACHOS Lock)
RWLock::RWLock() { 
	lock = new Lock("NACHOS Lock");
}
RWLock::~RWLock() { 
	delete lock;
}
//NOTE that for Task 2, startRead should be the same as startWrite
void RWLock::startRead() { 
	lock->Acquire();
} 
void RWLock::startWrite() { 
	lock->Acquire();
}
//NOTE that for Task 2, doneRead should be the same as doneWrite
void RWLock::doneRead() { 
	lock->Release();
} 
void RWLock::doneWrite() { 
	lock->Release();
}
#endif
#else
//Task 3 code (full rwlock)
RWLock::RWLock() {
	readCV = new Condition("Read CV");
	writeCV = new Condition("Write CV");
	lock = new Lock("RW Lock");
	AW = 0; WW = 0; AR = 0; WR = 0;
}
RWLock::~RWLock() { 
	delete readCV;
	delete writeCV;
	delete lock;
}
void RWLock::startRead() { 
	lock->Acquire();
	while ( (AW + WW) > 0 ){
		WR++;
		readCV->Wait(lock);
		WR--;
	}
	AR++;
	lock->Release();
}
void RWLock::doneRead() { 
	lock->Acquire();
	AR--;
	if( AR == 0 && WW > 0 )
		writeCV->Signal(lock);
	lock->Release();
}
void RWLock::startWrite() { 
	lock->Acquire();
	while(  (AW + AR) > 0){
		WW++;
		writeCV->Wait(lock);
		WW--;	
	}
	AW++;
	lock->Release();
}
void RWLock::doneWrite() { 
	lock->Acquire();
	AW--;
	if ( WW > 0 ){
		writeCV->Signal(lock);
	} else if ( WR > 0 ){
		readCV->Broadcast(lock);
	}
	lock->Release();
}
#endif