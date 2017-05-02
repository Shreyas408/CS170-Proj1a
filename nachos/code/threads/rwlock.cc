#include <semaphore.h>
#include <pthread.h>
#include "rwlock.h"

#ifndef P1_RWLOCK
#ifdef P1_SEMAPHORE
//Task 1 code (using semaphore in place of mutex)
RWLock::RWLock() { }
RWLock::~RWLock() { }
void RWLock::startRead() { } //NOTE that for Task 1, startRead should be the same as startWrite
void RWLock::startWrite() { }
void RWLock::doneRead() { } //NOTE that for Task 1, doneRead should be the same as doneWrite
void RWLock::doneWrite() { }
#else
//Task 2 code (using NACHOS Lock)
RWLock::RWLock() { }
RWLock::~RWLock() { }
void RWLock::startRead() { } //NOTE that for Task 2, startRead should be the same as startWrite
void RWLock::startWrite() { }
void RWLock::doneRead() { } //NOTE that for Task 2, doneRead should be the same as doneWrite
void RWLock::doneWrite() { }
#endif
#else
//Task 3 code (full rwlock)
RWLock::RWLock() {}
RWLock::~RWLock() { }
void RWLock::startRead() { }
void RWLock::doneRead() { }
void RWLock::startWrite() { }
void RWLock::doneWrite() { }
#endif

// RWLock::RWLock(){
// 	#ifdef RWLOCK
// 	pthread_cond_init(&this->writeCV, NULL);;
// 	pthread_cond_init(&this->readCV, NULL);
// 	this->AW = 0;
// 	this->WW = 0;
// 	this->AR = 0;
// 	this->WR = 0;
// 	#endif
// 	pthread_mutex_init ( &this->lock, NULL);
// }

// RWLock::~RWLock(){
// 	#ifdef RWLOCK
// 		pthread_cond_destroy(&this->readCV);
// 		pthread_cond_destroy(&this->writeCV);
// 	#endif
// 	pthread_mutex_destroy(&this->lock);
// }

// void RWLock::startRead(){
// 	pthread_mutex_lock(&this->lock);
// 	#ifdef RWLOCK
// 		while ((this->AW + this->WW) > 0){
// 			this->WR++;
// 			pthread_cond_wait(&this->readCV, &this->lock);
// 			this->WR--;			
// 		}
// 		this->AR++;
// 		pthread_mutex_unlock(&this->lock);
// 	#endif
// }

// void RWLock::doneRead(){
// 	#ifdef RWLOCK
// 		pthread_mutex_lock(&this->lock);
// 		this->AR--;
// 		if(this->AR == 0 && this->WW > 0)
// 			pthread_cond_signal(&this->writeCV);
// 		pthread_mutex_unlock(&this->lock);
// 	#else
// 		pthread_mutex_unlock(&this->lock);
// 	#endif
// }

// void RWLock::startWrite(){
// 	pthread_mutex_lock(&this->lock);
// 	#ifdef RWLOCK
// 		while(  (this->AW + this->AR) > 0){
// 			this->WW++;
// 			pthread_cond_wait(&this->writeCV, &this->lock);
// 			this->WW--;
// 		}
// 		this->AW++;
// 		pthread_mutex_unlock(&this->lock);
// 	#endif
// }

// void RWLock::doneWrite(){
// 	#ifdef RWLOCK
// 		pthread_mutex_lock(&this->lock);
// 		this->AW--;
// 		if (this->WW > 0){
// 			pthread_cond_signal(&this->writeCV);
// 		} else if (this->WR > 0){
// 			pthread_cond_broadcast(&this->readCV);
// 		}
// 		pthread_mutex_unlock(&this->lock);
// 	#else
// 		pthread_mutex_unlock(&this->lock);
// 	#endif
// }