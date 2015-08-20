#ifndef QFRAME_H
#define QFRAME_H

#include <QWidget>

namespace Ui {
class QFrame;
}

class QFrame : public QWidget
{
    Q_OBJECT

public:
    explicit QFrame(QWidget *parent = 0);
    ~QFrame();

private:
    Ui::QFrame *ui;
};

#endif // QFRAME_H
