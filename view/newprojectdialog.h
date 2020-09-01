#ifndef NEWPROJECTDIALOG_H
#define NEWPROJECTDIALOG_H

#include <QLayout>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QMessageBox>

#include "controller/controller.h"

class NewProjectDialog : public QDialog{
	Q_OBJECT
	const Controller* _controller;

	QVBoxLayout* _layout;

	QLabel* _description;
	QLineEdit* _projectName;
	QDialogButtonBox* _buttons;

	void setup();
	void connects();
	bool isValid();
public:

	explicit NewProjectDialog(const Controller* controller, QWidget* parent =nullptr);

signals:
	void sendProjectName(const QString&);

public slots:
	void onOkClicked();
	void onProjectNameNotValid();
};

#endif // NEWPROJECTDIALOG_H
