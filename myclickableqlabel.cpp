#include "myclickableqlabel.h"

myClickableQlabel::myClickableQlabel(QWidget *parent):QLabel(parent)
{

}
void myClickableQlabel::mousePressEvent(QMouseEvent *ev)
{
    emit Mouse_pressed();
}

