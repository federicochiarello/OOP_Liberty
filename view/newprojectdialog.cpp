#include "newprojectdialog.h"

void NewProjectDialog::setup() {

	setModal(true);

	_layout->addWidget(_description);
	_layout->addWidget(_projectName);
	_layout->addWidget(_buttons);

	setLayout(_layout);
}

void NewProjectDialog::connects() {

	connect(_buttons, SIGNAL(rejected()),
			this, SLOT(reject()));

	connect(_buttons, SIGNAL(accepted()),
			this, SLOT(onOkClicked()));

	connect(this, SIGNAL(sendProjectName(const QString&)),
			_controller, SLOT(onNewProject(const QString&)));

	connect(_controller, SIGNAL(projectNameValid()),
			this, SLOT(accept()));

	connect(_controller, SIGNAL(projectNameNotValid()),
			this, SLOT(onProjectNameNotValid()));

}

NewProjectDialog::NewProjectDialog(const Controller* controller, QWidget* parent) :
	QDialog(parent),
	_controller(controller),
	_layout(new QVBoxLayout()),
	_description(new QLabel("Inserire il nome del nuovo progetto", this)),
	_projectName(new QLineEdit(this)),
	_buttons(new QDialogButtonBox(QDialogButtonBox::Cancel | QDialogButtonBox::Ok)) {

	setup();
	connects();
}

void NewProjectDialog::onOkClicked() {
	emit sendProjectName(_projectName->text());
}

void NewProjectDialog::onProjectNameNotValid() {
	QMessageBox* error = new QMessageBox(this);
	error->setIcon(QMessageBox::Critical);
	error->setText(tr("Nome non valido"));
	error->setInformativeText(tr("Per favore inserire un nome senza . , < > : / \\ \" | ? *"));
	error->show();
}
