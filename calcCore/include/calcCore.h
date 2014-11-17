#pragma once
#include "auxMayBe.h"
#include "auxCalcCore.h"
#include <functional>

namespace core
{
	namespace stub
	{
		struct auxThread
		{
			static int getOptimumThreadCount()
			{
				static const int stubValue=10;
				//
				return stubValue;
			}
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
		//double getResult();
	private:
	   auxCalcCore::pdoParam pdoParam_;
	   int countThread_; 
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
	private:
		monad::MayBe<auxCalcCore::pdoParam> pdoParam_;
		monad::MayBe<int> countThread_;
		
		void doAfterStop();
	};
}