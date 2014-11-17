#include "auxQt.h"
#include <QApplication>
#include <QTextCodec>
#include <QLocale>


bool auxQt::isGuiAvailable()
{
	QApplication::Type type = QApplication::type();
	//
	return (QApplication::GuiClient == type);
}

void auxQt::initCodec()
{
	QTextCodec *codec = QTextCodec::codecForName("UTF-8");
	QTextCodec::setCodecForCStrings(codec);
	QTextCodec::setCodecForLocale(codec);
	//
	QTextCodec *codecTr = QTextCodec::codecForName("CP1251");
	QTextCodec::setCodecForTr(codecTr);
}

const QLocale& auxQt::getProperLocale()
{
	static QLocale loc( QLocale::C );
	//
	return loc;
}

void auxQt::initQt(int argc, char **argv, bool needInitcodec)
{
	if (!qApp)
	{
		//std::cout << "Init Qt Core" << std::endl;
		new QApplication(argc, argv);
	}

	if (needInitcodec)
	{
		initCodec();
	}
}

void auxQt::initQtDefault(bool guiAllowed, bool needInitcodec)
{
	if (!qApp)
	{
		static int defArgc = 1;
		static char** defArgv = NULL;

		if (guiAllowed)
		{
			//std::cout << "Init Qt GUI Core" << std::endl;
			new QApplication(defArgc, defArgv);
		} 
		else
		{
			//std::cout << "Init Qt Core" << std::endl;
			new QCoreApplication(defArgc, defArgv);
		}
	}
	//
	if (needInitcodec)
	{
		initCodec();
	}
}


monad::MayBe<double> auxQt::convert::toDouble(const QString& str)
{
	monad::MayBe<double> result;
	//
	{
		bool flag(false);
		//
		double d = str.toDouble(&flag);
		if (flag)
		{
			result = d;
		}
	}
	//
	return result;
}

monad::MayBe<int> auxQt::convert::toInt(const QString& str)
{
	monad::MayBe<int> result;
	//
	{
		bool flag(false);
		//
		int d = str.toInt(&flag);
		if (flag)
		{
			result = d;
		}
	}
	//
	return result;
}
