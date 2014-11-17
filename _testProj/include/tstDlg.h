#pragma once

#include "ui_tstDlg.h"
//
#include <QWidget>
#include <QLineEdit>
#include <QDoubleValidator>
#include "auxCalcCore.h"
#include "calcCore.h"

class  dlgTest : public QWidget
{
	Q_OBJECT

public:
	dlgTest(QWidget * parent, Qt::WindowFlags f = 0);

	void hasAResult(double val);

signals:
	void sigStart();
	void sigHasResult(double val);

private:
	Ui::tstDlg ui;
	QDoubleValidator *validator_;
	//
	std::unique_ptr<core::Calculator> solver_;

	static void setValidator(QValidator *validator, QLineEdit* wgt);
	static void setValue(const auxCalcCore::tDig& val, QLineEdit* wgt);

	void init();
	void initConnection();

	monad::MayBe<auxCalcCore::pdoParam> getCalcParam()const;
	monad::MayBe<int> getCountThread()const;

	void clearOutputWgt();

	

private slots:
	void slStart();
	void slHasResult(double val);
};