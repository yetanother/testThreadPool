#include <QApplication>

#include "tstDlg.h"
#include "auxQt.h"

int main()
{
	{
		static const bool needGui(true);
		static const bool needInitCodec(true);
		auxQt::initQtDefault(needGui, needInitCodec);
	}
	//
	dlgTest dlg(nullptr);
	dlg.show();
	//
	return qApp->exec();
}