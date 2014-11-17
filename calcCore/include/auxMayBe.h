#pragma once

namespace monad
{
	template<typename T>
	class MayBe
	{
		private:
			bool settled_;
			T	 value_;
		public:
			typedef T type;

			MayBe():settled_(false){}

			MayBe(const MayBe<T>& rv)
			{
				settled_ = rv.settled_;
				if (settled_)
				{
					value_ = rv.value_;
				}
			}

			MayBe& operator=(const MayBe<T>& rv)
			{
				if( this != &rv )
				{
					settled_ = rv.settled_;
					if (settled_)
					{
						value_ = rv.value_;
					}
				}
				//
				return *this;
			}

			MayBe(const T& t)
			{
				settled_ = true;
				value_ = t;
			}

			MayBe& operator=(const T& t)
			{
				settled_ = true;
				value_ = t;
				return *this;
			}

			bool operator< (const MayBe<T> &other) const
			{
				bool pred1 = this->hasValue();
				bool pred2 = other.hasValue();
				//
				if (!pred1 && !pred2)
				{
					return false;
				}
				if (pred1 && pred2)
				{
					return (this->get() < other.get());
				}
				if(pred1 && !pred2)
				{
					false;
				}
				//
				return true;
			}

			bool operator== (const MayBe<T> &other) const
			{
				bool pred1 = this->hasValue();
				bool pred2 = other.hasValue();
				//
				if (pred1 != pred2)
				{
					return false;
				}
				if (!pred1 && !pred2)
				{
					return true;
				}
				if(pred1 && pred2)
				{
					return this->get() && other.get();
				}
				//
				return false;
			}

			bool isSettled()const{return settled_;}
			bool hasValue()const{return isSettled();}

			const T& get()const
			{
				if (settled_)
				{
					return value_;
				}
				else
				{
					throw;
				}
			}
			const T& get(const T& defValue)const
			{
				if (settled_)
				{
					return value_;
				}
				//
				return defValue;
			}

			T& get()
			{
				if (settled_)
				{
					return value_;
				}
				else
				{
					throw;
				}
			}

			void set(const T& rv)
			{
				settled_ = true;
				value_ = rv;
			}

			void reset(){settled_ = false;}
	};
	typedef MayBe<double> opDouble;
	typedef MayBe<int> opInt;
}