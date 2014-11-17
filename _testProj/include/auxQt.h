#pragma once
#include "auxMayBe.h"

class QLocale;
class QString;
class QLineEdit;

namespace auxQt
{
	 bool isGuiAvailable();

	 void initCodec();

	 const QLocale& getProperLocale();

	 void initQt(int argc, char **argv, bool needInitcodec);
 	 void initQtDefault(bool guiAllowed, bool needInitcodec);

	 namespace convert
	 {
		 monad::MayBe<double> toDouble(const QString& str);
		 monad::MayBe<int> toInt(const QString& str);

		 template<typename T>
		 monad::MayBe<T> toData(const QString& str);

		 template<>
		 inline
		 monad::MayBe<double> toData(const QString& str)
		 {
			 return toDouble(str); 
		 }
		 template<>
		 inline
		 monad::MayBe<int> toData(const QString& str)
		 {
			 return toInt(str); 
		 }

	 }

	 namespace wgt
	 {
		template<typename T>
		inline
		monad::MayBe<T> getData(QLineEdit* wgt)
		{
			monad::MayBe<T> result;
			//
			const QString& str = wgt->text();
			result = convert::toData<T>(str);
			//
			return result;
		}
	 }
}