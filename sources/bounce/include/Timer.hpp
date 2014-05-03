/*
 * Timer.h
 *
 *  Created on: 31 maj 2013
 *      Author: daniel
 */

#ifndef TIMER_H_
#define TIMER_H_


#include <iostream>
#if __unix__
#define systime
#endif
#ifdef __APPLE__
#define systime
#endif


#ifdef systime
#include <sys/time.h>
#endif
#ifdef _WIN32
#include <Windows.h>
#endif

namespace bounce {

class Timer {
private:
#ifdef systime
	timeval lastTime;
#endif
#ifdef _WIN32
    SYSTEMTIME lastTime;
#endif
public:
	void start();
	void stop();
	float getElapsedTime();
};

#ifdef _WIN32

inline void Timer::start() {
    GetSystemTime(&lastTime);
}

inline void Timer::stop() {

}

inline float Timer::getElapsedTime() {
    SYSTEMTIME now;
    float elapsedTime;
    GetSystemTime(&now);

    elapsedTime = (now.wSecond - lastTime.wSecond) * 1000.0f;
    elapsedTime += (now.wMilliseconds - lastTime.wMilliseconds) / 1000.0f;

    lastTime = now;

    return elapsedTime;
}

#endif

#ifdef systime

inline void Timer::start() {
	gettimeofday(&lastTime, NULL);
}

inline void Timer::stop() {

}

inline float Timer::getElapsedTime() {
	timeval now;
	float elapsedTime;
	gettimeofday(&now, NULL);

	elapsedTime = (now.tv_sec - lastTime.tv_sec) * 1000.0f;
	elapsedTime += (now.tv_usec - lastTime.tv_usec) / 1000.0f;

	lastTime = now;

	return elapsedTime;
}

#endif

}

#endif /* TIMER_H_ */
