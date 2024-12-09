#include "BaseMainWidget.h"

#include "MainWindow.h"


BaseMainWidget::BaseMainWidget(MainWindow* parent)
	: QWidget(parent)
	, m_uiParentWindow(parent)
{
	setAttribute(Qt::WA_DeleteOnClose);
}

MainWindow* BaseMainWidget::GetParentWindow() const
{
	return m_uiParentWindow;
}
