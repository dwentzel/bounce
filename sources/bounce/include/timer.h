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
    
    class SystemTimer {
    private:
#ifdef systime
        timeval last_time_;
#endif
#ifdef _WIN32
        ULONGLONG last_time_;
#endif
    public:
        void reset();
        float getElapsedTime();
    };
    
#ifdef _WIN32
    
    inline void SystemTimer::reset() {
        last_time_ = GetTickCount64();
    }
    
    inline float SystemTimer::getElapsedTime() {
        ULONGLONG now = GetTickCount64();
        
        float elapsedTime = now - last_time_;
        
        last_time_ = now;
        
        return elapsedTime;
    }
    
#endif
    
#ifdef systime
    
    inline void SystemTimer::reset() {
        gettimeofday(&last_time_, NULL);
    }
    
    inline float SystemTimer::getElapsedTime() {
        timeval now;
        float elapsed_time;
        gettimeofday(&now, NULL);
        
        elapsed_time = (now.tv_sec - last_time_.tv_sec) * 1000.0f;
        elapsed_time += (now.tv_usec - last_time_.tv_usec) / 1000.0f;
        
        last_time_ = now;
        
        return elapsed_time;
    }
    
#endif
    
    
    class Timer {
    private:
        SystemTimer system_timer_;
        
    public:
        void start();
        void stop();
        float getElapsedTime();
    };
    
    inline void Timer::start() {
        system_timer_.reset();
    }
    
    inline void Timer::stop() {
        
    }
    
    inline float Timer::getElapsedTime() {
        return system_timer_.getElapsedTime();
    }
    
}

#endif /* TIMER_H_ */
