#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QString>
#include <QObject>
#include <QDebug>
#include "room.h"
#include "agent.h"
#include "monster.h"
#include "player.h"
#include "Object.h"
#include "Prop.h"
#include "FixedProp.h"
#include "Treasure.h"
#include <QLabel>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QSignalMapper>
#include "myclickableqlabel.h"
#include "winningdialog.h"
#include "smartmonster.h"
#include <typeinfo>
#include <QDir>
#include "gameover.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void ButtonClicked(QString dir);
    //when any button clicked, this fun is called,
    //it's responseable for moving all characters
    //exchange turns between characters

    ~MainWindow();      //couldnt care less

private slots:
    /*  seems obvious  */
    void on_north_clicked();
    void on_south_clicked();
    void on_east_clicked();
    void on_west_clicked();
    void on_exit_clicked();
    void on_Fight_clicked();

    void on_Grab_clicked();

    void MousePressed(QString x);


    void on_Drop_clicked();

private:
    //makeing form
    Ui::MainWindow *ui;
    //the Rooms
    Room *r00, *r01, *r02, *r10, *r11, *r12, *r20, *r21, *r22;
    map<QString, map<QString, QLabel*> > myMap;
    QSignalMapper* signalMapper;
    WinningDialog win;
    GameOver over;
    //Array of characters
    //{player1, player2, monster1, monster2, monster3};
    Agent* *charachters;
    //The current position for any character
    //that its turn to move
    QString dirs[4] = {"WEST", "NORTH", "EAST", "SOUTH"};
    int turn = 0;
    map<QString, Room*> rooms;
    //initialization methods
    void initializeRooms();
    void initializeLinks();
    void initializeAgents();
    void initializeLabels();
    void initializeAll();
    void initializeLast();
    void AddItems();
    void deleteAll();
    void addFirst();
    void initializeSignals();
};

#endif // MAINWINDOW_H
