#ifndef TEXTHOLDER_H
#define TEXTHOLDER_H


#include <QTextEdit>
#include <QMouseEvent>

class TextHolder : public QTextEdit {
	Q_OBJECT

public:
	TextHolder(QWidget* parent =nullptr);
	TextHolder(const QString& text, QWidget* parent =nullptr);

	void setup();
protected:
	//void mousePressEvent(QMouseEvent *e) override;

private:

};

#endif // TEXTHOLDER_H
