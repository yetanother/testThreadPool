#include "calcCore.h"
#include "threadpool.h"
#include <iostream>

void core::Calculator::doAfterStop()
{
	 pdoParam_.reset();
}

bool core::Calculator::isReadyToCalc() const
{
	const bool pred1 = 	checkCorrectInputData();
	const bool pred2 = 	checkCountThread();
	return 	(pred1&&pred2);
}

bool core::Calculator::checkCorrectInputData() const
{
	const bool pred1 = pdoParam_.hasValue();
	//
	bool pred2 = false;
	//
	if (pred1)
	{
		pred2 = pdoParam_.get().isCorrect();
	}
	//
	return (pred1 && pred2);
}

bool core::Calculator::checkCountThread() const
{
   bool result = true;
   //
   if (countThread_.hasValue())
   {
	   const int& count = countThread_.get();
	   result = (count>=1);
   }
   //
   return result;
}

bool core::Calculator::checkComplex() const
{
	const bool pred1 = checkCorrectInputData();
	const bool pred2 = checkCountThread();
	return (pred1&&pred2);
}

void core::Calculator::doCalc(core::callbackFunctor pFunc)
{
	using namespace monad;
	//
   if (!checkComplex())
   {
	   return;// result;
   }
   // do
   {
	   const auxCalcCore::pdoParam& param = pdoParam_.get();
	   int countThread(1);
	   {
		   if (countThread_.hasValue())
		   {
			   countThread = countThread_.get();
		   } 
		   else
		   {
			   countThread_ = core::stub::auxThread::getOptimumThreadCount();
		   }
	   }
	   //
	   pIntegrator_ = std::make_unique<core::Integrator>(param, countThread);
	   //
	   //core::Integrator Integr(param, countThread);
	   double res = pIntegrator_->start();
		   //
	   pFunc(res);
   }
   //
   return ;
}

void core::Calculator::doStop()
{
	//
	{
		if (pIntegrator_)
		{
			pIntegrator_->stop();
		}

	}
	//
	doAfterStop();
}



double core::Integrator::start()
{
	double stubResult = pdoParam_.interval_.end_;
	//
	{
		pThreadPool_ = std::make_unique<ThreadPool>(countThread_);
		  //ThreadPool pool(countThread_);
		  //
		  std::vector< std::future<double> > results;
		  //map
		  std::vector<double> args;
		  {
			  const double& dx = pdoParam_.delta_;
			  int countIntervals = static_cast<int>(pdoParam_.interval_.length() / dx);
			  const double& begin = pdoParam_.interval_.begin_;
			  const double& end = pdoParam_.interval_.end_;
			  //
			  {
				  double curPos = begin;
				  args.push_back(curPos);
				  //
				  for (int i = 0; i < countIntervals; ++i)
				  {
					  curPos += dx;
					  args.push_back(curPos);
				  }
				  //
				  if (curPos < end)
				  {
					  args.push_back(end);
				  }
			  }
			  //
			  const int& size = args.size() - 1;
			  for (int i = 0; i < size; ++i)
			  {
				  results.emplace_back(
					  pThreadPool_->enqueue([i, &args] {
					  std::this_thread::sleep_for(std::chrono::seconds(10));
					  double tmp = args[i + 1] - args[i];
					  return tmp;
				  })
					  );
			  }
		  }
		  //reduce
		  {
			  double sum = 0;
			  //
			  for (auto && result : results)
			  {
				  sum += result.get();
			  }
			  stubResult = sum;
		  }

	}
	return stubResult;
}

void core::Integrator::stop()
{
	if (pThreadPool_)
	{
		pThreadPool_->stop();
	}
}

int core::stub::auxThread::getOptimumThreadCount()
{
	static const int defValue = 10;
	//
	int hw = std::thread::hardware_concurrency();
	if (hw <= 0)
	{
		return defValue;
	}
	else
	{
		return hw;
	}
}
