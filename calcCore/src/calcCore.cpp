#include "calcCore.h"
#include "threadpool.h"

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
	   core::Integrator Integr(param, countThread);
	   double res = Integr.start();
		   //
	   pFunc(res);
   }
   //
   return ;
}



double core::Integrator::start()
{
	double stubResult = pdoParam_.interval_.end_;
	//
	{
		  ThreadPool pool(countThread_);
		  //
		  std::vector< std::future<int> > results;

		  for(int i = 0; i < 8; ++i)
		  {
			  results.emplace_back(
				  pool.enqueue([i] {
					  std::cout << "hello " << i << std::endl;
					  std::this_thread::sleep_for(std::chrono::seconds(1));
					  std::cout << "world " << i << std::endl;
					  return i*i;
			  })
				  );
		  }
		  for(auto && result: results)
			  std::cout << result.get() << ' ';
		  std::cout << std::endl;
	}
	return stubResult;
}
