#pragma once
#include "auxMayBe.h"
#include "auxCalcCore.h"
#include <functional>
#include <memory>
#include "threadpool.h"

namespace core
{
	namespace stub
	{
		struct auxThread
		{
			static int getOptimumThreadCount();
		};
	}
	//
	typedef std::function<void(double)> callbackFunctor;
	//
	struct Integrator
	{
		Integrator(const auxCalcCore::pdoParam& paramn, const int& count)
			:pdoParam_(paramn), countThread_(count)
		{
		}

		double start();
		void stop();
		//double getResult();
	private:
	   auxCalcCore::pdoParam pdoParam_;
	   int countThread_;
	   std::unique_ptr<ThreadPool> pThreadPool_;
	};
	//
	struct Calculator
	{
		bool isReadyToCalc()const;
		bool checkCorrectInputData()const;
		bool checkCountThread()const;

		bool checkComplex()const;

		void setParam(const monad::MayBe<auxCalcCore::pdoParam> val)
		{
			pdoParam_ = val;
		}
		void setCountThread(const monad::MayBe<int>& val)
		{
			countThread_ = 	val;
		}
		//
		void doCalc(core::callbackFunctor pFunc);
		void doStop();
	private:
		monad::MayBe<auxCalcCore::pdoParam> pdoParam_;
		monad::MayBe<int> countThread_;
		std::unique_ptr<core::Integrator> pIntegrator_;
		
		void doAfterStop();
	};
}