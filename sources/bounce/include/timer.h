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
        void Reset();
        float GetElapsedTime() const;
    };
    
#ifdef _WIN32
    
    inline void SystemTimer::Reset() {
        last_time_ = GetTickCount64();
    }
    
    inline float SystemTimer::GetElapsedTime() const {
        ULONGLONG now = GetTickCount64();
        
        float elapsedTime = now - last_time_;
        
        return elapsedTime;
    }
    
#endif
    
#ifdef systime
    
    inline void SystemTimer::Reset() {
        gettimeofday(&last_time_, NULL);
    }
    
    inline float SystemTimer::GetElapsedTime() const {
        timeval now;
        float elapsed_time;
        gettimeofday(&now, NULL);
        
        elapsed_time = (now.tv_sec - last_time_.tv_sec) * 1000.0f;
        elapsed_time += (now.tv_usec - last_time_.tv_usec) / 1000.0f;
        
        return elapsed_time;
    }
    
#endif
    
    class Timer {
    private:
        SystemTimer system_timer_;
        
    public:
        void Start();
        void Stop();
        float GetElapsedTime() const;
        void Reset();
    };
    
    inline void Timer::Start() {
        system_timer_.Reset();
    }
    
    inline void Timer::Stop() {
        
    }
    
    inline float Timer::GetElapsedTime() const {
        return system_timer_.GetElapsedTime();
    }
    
    inline void Timer::Reset() {
        system_timer_.Reset();
    }
    
}

#endif /* TIMER_H_ */
