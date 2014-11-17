#include "auxDlg.h"

#include <QWidget>
#include <QString>
#include <QMessageBox>
#include "QApplication"
#include "auxQt.h"
#include <QDebug>

void auxDlg::MsgBox(QWidget* parent, const QString& caption, const QString& text)
{
	if (!qApp)
	{
		static const bool initCodec=true;
		auxQt::initQt(1, NULL, initCodec);
	}
	//
	bool pred = auxQt::isGuiAvailable();
	if (pred)
	{
		int ret = QMessageBox::warning(parent, caption, text, QMessageBox::Ok);
		Q_UNUSED(ret);
	} 
	else
	{
		qWarning() << text << "(" << caption << ")";
		qWarning() << endl;
	}
}
