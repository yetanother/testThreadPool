#include "tstDlg.h"

#include <QMessageBox>

#include "auxTemplate.h"
#include "auxDlg.h"
#include "auxMayBe.h"
#include "auxQt.h"
#include <functional>

dlgTest::dlgTest(QWidget * parent, Qt::WindowFlags f /*= 0*/)
	:QWidget(parent)
{
	Q_UNUSED(f);
	//
	qthread_ = new QThread(this);
	//
	init();
}

void dlgTest::init()
{
	ui.setupUi(this);
	initConnection();
	//
	{
		static const int defCountThread(1);
		ui.sbThread->setValue(defCountThread);
	}
	{
		solver_ = auxT::make_unique<core::Calculator>();
	}
	{
		validator_ = new QDoubleValidator(this);
		static const int decs(11);
		validator_->setDecimals(decs);
	}
	//
	//dlgTest::setValidator(validator_, ui.wgtBegin);
	//dlgTest::setValidator(validator_, ui.wgtEnd);
	//dlgTest::setValidator(validator_, ui.wgtStep);
	//
	dlgTest::setValue(0, ui.wgtBegin);
	dlgTest::setValue(1/*3.1415926*/, ui.wgtEnd);
	dlgTest::setValue(1, ui.wgtStep);
}

void dlgTest::setValidator(QValidator *validator, QLineEdit* wgt)
{
		 wgt->setValidator(validator);
}

void dlgTest::setValue(const auxCalcCore::tDig& val, QLineEdit* wgt)
{
   QString str = QString("%1").arg(val);
   //
   wgt->setText(str);
}

void dlgTest::slStart()
{
	using namespace monad;
	//
	clearOutputWgt();
	{
		MayBe<auxCalcCore::pdoParam> mb = getCalcParam();
		solver_->setParam(mb);
	}
	{
		MayBe<int> mbCount = dlgTest::getCountThread();
		solver_->setCountThread(mbCount);
	}
	{
		bool isCorrectInputData = solver_->checkCorrectInputData();
		bool isCorrectCountThread = solver_->checkCountThread();
		//
		if (!isCorrectInputData)
		{
			auxDlg::MsgBox(this, "caption", tr("Некорректные ИД"));
			return;
		} 
		else
		{
			if (!isCorrectCountThread)
			{
				auxDlg::MsgBox(this, "caption", tr("ошибка в количестве потоков"));
				return;
			} 
		}
	}
	//
	{//start calculation
		{
			QString outStr("~in process~");
			ui.wgtOutput->setText(outStr);
		}
		std::function<void(double)> pf0 = [this](double val)
		{
			emit sigHasResult(val);
		};
		//
		std::function<void(double)> pf = [this, pf0](double val)
		{
			solver_->doCalc(pf0);
			//this->hasAResult(val);
		};
		//qt
		//
		//solver_->doCalc(pf);
		//qApp->processEvents(QEventLoop::AllEvents, 0)
		auxDlg::MsgBox(this, "doCalc", "doCalc");
	}
}

void dlgTest::initConnection()
{
	{
		bool res = QObject::connect(
							ui.btnStart, 
							SIGNAL(released()),
							this,
							SIGNAL(sigStart())
							);
		Q_ASSERT_X(res, "dlgTest::initConnection", "issue connection with");
	}
	{
		bool res = QObject::connect(
			this, 
			SIGNAL(sigStart()),
			this,
			SLOT(slStart())
			);
		Q_ASSERT_X(res, "dlgTest::initConnection", "issue connection with");
	}
	{
		bool res = QObject::connect(
			this, 
			SIGNAL(sigHasResult(double)),
			this,
			SLOT(slHasResult(double))
			);
		Q_ASSERT_X(res, "dlgTest::initConnection", "issue connection with");
	}
	{
		bool res = QObject::connect(
			ui.btnStop,
			SIGNAL(released()),
			this,
			SLOT(slStop())
			);
		Q_ASSERT_X(res, "dlgTest::initConnection", "issue connection with");
	}
}

monad::MayBe<auxCalcCore::pdoParam> dlgTest::getCalcParam() const
{
	monad::MayBe<auxCalcCore::pdoParam> result;
	//
	{
		using namespace auxQt;
		using namespace monad;
		//
		opDouble mbStart = auxQt::wgt::getData<double>(ui.wgtBegin);
		opDouble mbFinish = auxQt::wgt::getData<double>(ui.wgtEnd);
		opDouble mbStep = auxQt::wgt::getData<double>(ui.wgtStep);
		//
		{
			const bool pred1 = mbStart.hasValue();
			const bool pred2 = mbFinish.hasValue();
			const bool pred3 = mbStep.hasValue();
			//
			const bool Pred = (pred1&&pred2&&pred3);
			//
			if (!Pred)
			{
				return result;
			}
		}
		//
		const double& start = mbStart.get();
		const double& finish = mbFinish.get();
		const double& step = mbStep.get();
		//
		auxCalcCore::pdoParam param(auxCalcCore::interval(start, finish), step);
		result = param;
	}
	//
	return result;
}

monad::MayBe<int> dlgTest::getCountThread() const
{
	monad::MayBe<int> result;
	//
	{
		using namespace auxQt;
		//
		QGroupBox *p = ui.gboxThread;
		if (p)
		{
			if (p->isChecked())
			{
				QSpinBox *wgt = ui.sbThread;
				if (wgt)
				{
					result = wgt->value();
				}
			}
		}
	}
	//
	return result;
}

void dlgTest::clearOutputWgt()
{
	ui.wgtOutput->clear();
}

void dlgTest::hasAResult(double val)
{
	emit sigHasResult(val);
}

void dlgTest::slHasResult(double val)
{
	auxDlg::MsgBox(this, "caption", "dlgTest::slHasResult");
	//
	QString str = QString("%1").arg(val);
	QLineEdit *wgt = ui.wgtOutput;
	wgt->setText(str);
}

void dlgTest::slStop()
{
	//auxDlg::MsgBox(this, "caption", "dlgTest::slStop");
	//
	if (solver_)
	{
		//
		solver_->doStop();
	}
}

void dlgTest::slStub()
{
	auxDlg::MsgBox(this, "slStub", "dlgTest::slStub");
}

