#pragma once

namespace win {

	class StopWatch {
	protected:
		float32			lastdeltaElapse;
		float32			currentElapse;
		float32			deltaElapse;

		/// TIMER
		float32			timerStep[10];

		float32			laststepElapse;
		int32			stepsCount;
		int32			cycleCount;
	public:
		float32			timerAvarage[10];

		StopWatch();

		void reset1(void);
		float32 getElapsedSeconds(void);
		float32 getDiffElapsedSeconds(void);
		float32 lastElapseTime() const;


		void	startTimer1();
		void	addTimerStep();
		bool8	endtimerTimer();
	};
}
