#include <rde_common/lib.h>
#include "stopwatch.h"


namespace win{
	LARGE_INTEGER	counterFrequency;
	LARGE_INTEGER	lastCount;

	StopWatch::StopWatch() :
		lastdeltaElapse(0),
		currentElapse(0),
		deltaElapse(0),
		cycleCount(0) {

		memset(&timerStep[0], 0, sizeof(float32) * 10);
		QueryPerformanceFrequency(&counterFrequency);
		QueryPerformanceCounter(&lastCount);
	}

	void StopWatch::reset1() {
		QueryPerformanceCounter(&lastCount);
	}

	float32 StopWatch::getElapsedSeconds(void) {
		// Get the current count
		LARGE_INTEGER lCurrent;
		QueryPerformanceCounter(&lCurrent);

		currentElapse = float(((lCurrent.QuadPart - lastCount.QuadPart) /
			double(counterFrequency.QuadPart)));
		return currentElapse;

	}

	float32 StopWatch::getDiffElapsedSeconds() {
		float32 flookup[2];
		deltaElapse = (this->getElapsedSeconds() - lastdeltaElapse);
		flookup[0] = deltaElapse;
		flookup[1] = 0.0f;
		//_deltaElapse<0.0f? 0.0f: _deltaElapse;
		deltaElapse = flookup[deltaElapse < 0.0f];
		lastdeltaElapse = currentElapse;

		return deltaElapse;

	}

	float32 StopWatch::lastElapseTime() const {
		return deltaElapse;
	}

	void	StopWatch::startTimer1() {
		cycleCount++;
		stepsCount = 0;
		laststepElapse = this->getElapsedSeconds();
	}

	void	StopWatch::addTimerStep() {
		timerStep[stepsCount++] += this->getElapsedSeconds() - laststepElapse;
		laststepElapse = this->getElapsedSeconds();
	}

	bool8 StopWatch::endtimerTimer() {
		bool8 reach = false;
		timerStep[stepsCount] = this->getElapsedSeconds() - laststepElapse;
		stepsCount++;

		if (cycleCount == 60) {
			cycleCount = 0;
			reach = true;
			for (int i = 0; i < stepsCount; i++) {
				timerAvarage[i] = (timerStep[i] / 60) * 1000;
			}
			memset(&timerStep[0], 0, sizeof(float32) * 10);
		}
		return reach;
	}

}