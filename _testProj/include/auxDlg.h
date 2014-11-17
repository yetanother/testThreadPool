#pragma once

class QString;
class QWidget;

namespace auxDlg
{
	void MsgBox(QWidget* parent, const QString& caption, const QString& text);
}