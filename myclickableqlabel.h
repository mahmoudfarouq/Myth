#ifndef MYCLICKABLEQLABLE_H
#define MYCLICKABLEQLABLE_H

#include <QLabel>
#include <QMouseEvent>
#include <QDebug>
#include <QEvent>

class myClickableQlabel : public QLabel
{
    Q_OBJECT
public:
    explicit myClickableQlabel(QWidget *parent = 0);
    void mousePressEvent(QMouseEvent *ev);
signals:
    void Mouse_pressed();

public slots:


};

#endif // MYCLICKABLEQLABLE_H
