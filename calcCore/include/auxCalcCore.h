#pragma once

namespace auxCalcCore
{
	typedef double tDig;

	struct interval
	{
		interval(){}
		interval(const tDig& begin, const tDig& end)
			:begin_(begin), end_(end){}
		//
		bool isCorrect()const{return (end_>=begin_);}
		tDig length()const{return (end_-begin_);}

		tDig begin_;
		tDig end_;
	};
	//
	struct pdoParam
	{
		pdoParam(){}

		pdoParam(const interval& interval, const tDig& delta)
			:interval_(interval), delta_(delta){}
		//
		bool isCorrect()const
		{
			const bool pred1 = 	interval_.isCorrect();
			const bool pred2 = (delta_>0)&&(delta_<=interval_.length());
			return (pred1&&pred2);
		}
		//
		interval interval_;
		tDig delta_;
	};
}