#include "cab202_timer.h"
#include <assert.h>


#ifdef WIN32
#include <windows.h>
#else
#include <time.h>
#include <unistd.h>
#endif

#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#endif

/* A list of timers which are allocated to particular purposes via create_timer. */
cab202_timer_t timers[TIMER_MAX];

/* the current number of allocated timers. */
int timer_count = 0;


timer_id create_timer( long milliseconds ) {
	if ( milliseconds <= 0 || timer_count > TIMER_MAX ){
		return TIMER_ERROR;
	}

	timers[timer_count].milliseconds = milliseconds;
	reset_timer( timer_count );

	return timer_count++;
}


void reset_timer( timer_id id ) {
	if ( id < 0 || id >= timer_count ) {
		return;
	}

	timers[id].reset_time = get_current_time();
}


int timer_expired( timer_id id ) {
	double current_time = get_current_time();
	double time_diff = current_time - timers[id].reset_time;
	int expired = time_diff * MILLISECONDS >= timers[id].milliseconds;

	if ( expired ) {
		reset_timer( id );
	}

	return expired;
}

void timer_pause( long milliseconds ) {
#ifdef WIN32
	Sleep( milliseconds );
#else
	/* usleep requires input in microseconds rather than milliseconds. */
	usleep( milliseconds * MILLISECONDS );
#endif
}

#ifdef WIN32
/*
	Implementation of clock_gettime sourced from StackOverflow:
	http://stackoverflow.com/questions/5404277/porting-clock-gettime-to-windows
	*/

LARGE_INTEGER getFILETIMEoffset() {
	SYSTEMTIME s;
	FILETIME f;
	LARGE_INTEGER t;

	s.wYear = 1970;
	s.wMonth = 1;
	s.wDay = 1;
	s.wHour = 0;
	s.wMinute = 0;
	s.wSecond = 0;
	s.wMilliseconds = 0;
	SystemTimeToFileTime( &s, &f );
	t.QuadPart = f.dwHighDateTime;
	t.QuadPart <<= 32;
	t.QuadPart |= f.dwLowDateTime;
	return ( t );
}

#pragma warning( disable: 4100 )

int clock_gettime( int X, struct timeval *tv ) {
	LARGE_INTEGER           t;
	FILETIME            f;
	double                  microseconds;
	static LARGE_INTEGER    offset;
	static double           frequencyToMicroseconds;
	static int              initialized = 0;
	static BOOL             usePerformanceCounter = 0;

	if ( !initialized ) {
		LARGE_INTEGER performanceFrequency;
		initialized = 1;
		usePerformanceCounter = QueryPerformanceFrequency( &performanceFrequency );
		if ( usePerformanceCounter ) {
			QueryPerformanceCounter( &offset );
			frequencyToMicroseconds = (double) performanceFrequency.QuadPart / 1000000.;
		}
		else {
			offset = getFILETIMEoffset();
			frequencyToMicroseconds = 10.;
		}
	}
	if ( usePerformanceCounter ) QueryPerformanceCounter( &t );
	else {
		GetSystemTimeAsFileTime( &f );
		t.QuadPart = f.dwHighDateTime;
		t.QuadPart <<= 32;
		t.QuadPart |= f.dwLowDateTime;
	}

	t.QuadPart -= offset.QuadPart;
	microseconds = (double) t.QuadPart / frequencyToMicroseconds;
	t.QuadPart = (LONGLONG) microseconds;
	tv->tv_sec = (long) ( t.QuadPart / 1000000 );
	tv->tv_usec = t.QuadPart % 1000000;
	return ( 0 );
}

double get_current_time() {
	struct timeval timeval;
	clock_gettime( 0, &timeval );
	return timeval.tv_sec + timeval.tv_usec / 1.0e+6;
}
#else 
double get_current_time () {
	struct timespec timeval;

#ifdef __MACH__ // OS X does not have clock_gettime, use clock_get_time
	clock_serv_t cclock;
	mach_timespec_t mts;
	host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
	clock_get_time(cclock, &mts);
	mach_port_deallocate(mach_task_self(), cclock);
	timeval.tv_sec = mts.tv_sec;
	timeval.tv_nsec = mts.tv_nsec;
#else
	/* http://linux.die.net/man/3/clock_gettime */
	clock_gettime( CLOCK_REALTIME, &timeval );
#endif

	return timeval.tv_sec + timeval.tv_nsec / 1.0e+9;
}
#endif
