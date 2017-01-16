#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

/*
##########  ##########  ##########
#        #  #        #  #        #
#   00   ----   01   ----   02   #
#   m3   #  #        #  #        #
###| |####  ##########  ###| |####
   | |                     | |
###| |####  ##########  ###| |####
#        #  #        #  #        #
#   10   ----   11   ----   12   #
#   m2   #  #   m1   #  #        #
###| |####  ###| |####  ###| |####
   | |                     | |
###| |####  ###| |####  ###| |####
#        #  #        #  #        #
#   20   ----   21   ----   22   #
#        #  #        #  # p1, p2 #
##########  ##########  ##########
*/


    initializeAll();


    ui->PreviewLabel->setScaledContents( true );
    ui->PreviewLabel->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );


    charachters[0]->CurrentPositon->container->setEnabled(true);
    charachters[0]->CurrentPositon->container->setVisible(true);

    ui->textBrowser->setText(charachters[turn]->sayIntro());


    QMediaPlaylist *playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl(QCoreApplication::applicationDirPath()+"/mystic.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    QMediaPlayer *music = new QMediaPlayer();
    music->setPlaylist(playlist);
    music->play();

    //cast
    dynamic_cast<SmartMonster*>(charachters[4])->setAll(charachters[0],charachters[1], rooms);

    ui->centralWidget->setStyleSheet(QString::fromUtf8("QWidget#centralWidget\n"
    "{\n"
    "    border-image: url(:/Agents/pattern_background_dark_shadow_35092_1920x1200.jpg);\n"
    "}\n"
    ""));


}
MainWindow::~MainWindow()
{
    deleteAll();
    delete ui;
}
void MainWindow::ButtonClicked(QString dir)
{
    if(dir == "QUIT") exit(1);
    else if(charachters[turn]->act(dir))
    {
        if( charachters[turn]->hasWon() )
        {
            win.show();
            win.setName(charachters[turn]->getName() + "Has Won!\nCongratulations :)");
            this->hide();
        }
        for(int i = 2; i < 5; i++){ if(charachters[i]->Life())charachters[i]->act(dirs[rand()%4]);}
        turn = (turn == 1 ? 0:1);
        if(! charachters[0]->Life() && !charachters[1]->Life())
        {
            over.show();
            this->hide();
        }
        else if(!charachters[turn]->Life()) //if dead dont let him play
            turn = (turn == 1 ? 0:1);

        charachters[turn]->CurrentPositon->container->setEnabled(true);
        charachters[turn]->CurrentPositon->container->setVisible(true);

        ui->Fight->setEnabled(true);
        ui->Grab->setEnabled(true);

    }
    ui->textBrowser->setText(charachters[turn]->sayIntro());
    ui->leftText->setText(  charachters[turn]->getName() + "\n" + charachters[turn]->getDiscription() );
    ui->rightText->setText( dynamic_cast<Player*>(charachters[turn])->PrintItems() );
    ui->Image->setPixmap( charachters[turn]->image );

}

void MainWindow::on_north_clicked()
{
    ButtonClicked("NORTH");
}
void MainWindow::on_south_clicked()
{
    ButtonClicked("SOUTH");
}
void MainWindow::on_east_clicked()
{
    ButtonClicked("EAST");
}
void MainWindow::on_west_clicked()
{
    ButtonClicked("WEST");
}
void MainWindow::on_exit_clicked()
{
    ButtonClicked("QUIT");
}
void MainWindow::on_Drop_clicked()
{
    dynamic_cast<Player*>(charachters[turn])->remItem(ui->Input->text());
    ui->textBrowser->append( charachters[turn]->getMessage() );

}
void MainWindow::on_Fight_clicked()
{
    if(charachters[turn]->Fight( ui->Input->text())){
        ui->Input->setText("");
        ui->Fight->setEnabled(false);
        ui->textBrowser->append( charachters[turn]->getMessage() );
    }
}

void MainWindow::on_Grab_clicked()
{
    if(charachters[turn]->Grab( ui->Input->text()) ){
        ui->Input->setText("");
        ui->Grab->setEnabled(false);
        ui->textBrowser->append( charachters[turn]->getMessage() );
    }
}

void MainWindow::MousePressed( QString x )
{
    if( charachters[turn]->CurrentPositon->InnerChars[x] != NULL ){
        ui->PreviewLabel->setPixmap( charachters[turn]->CurrentPositon->InnerChars[x]->image );
        ui->previewText->setText( charachters[turn]->CurrentPositon->InnerChars[x]->getName() + "\n" +
                                  charachters[turn]->CurrentPositon->InnerChars[x]->getDiscription());
    }
}

void MainWindow::deleteAll()
{
    delete r00; delete r01; delete r02; delete r11; delete r10; delete r12;
    delete r20; delete r21; delete r22;
    delete[] charachters;
}
void MainWindow::initializeAll()
{
    initializeRooms();
    initializeLinks();
    initializeAgents();
    AddItems();
    initializeLabels();
    initializeLast();
    addFirst();
    initializeSignals();
}
void MainWindow::initializeSignals()
{
    signalMapper = new QSignalMapper (this) ;
    map<QString, map<QString, QLabel*> >::const_iterator it;
    for( it = myMap.begin(); it != myMap.end(); it++ )
    {
        map<QString, QLabel*>::const_iterator it2;
        for( it2 = it->second.begin(); it2 != it->second.end(); it2++ )
        {
            connect(it2->second, SIGNAL( Mouse_pressed() ), signalMapper, SLOT(map()) );
            signalMapper -> setMapping (it2->second, it2->first) ;
        }
    }
    connect (signalMapper, SIGNAL(mapped(QString)), this, SLOT(MousePressed(QString))) ;
}

void MainWindow::addFirst()
{
    for(int i = 0; i < 4; i++)
        charachters[i]->CurrentPositon->allLabels[charachters[i]->getName()]->setPixmap(charachters[i]->image);
}

void MainWindow::initializeRooms()
{
    r00 = new Room("Jurassic World", "A world full of ancient monsters", "r00", ui->groupBox, Point(0, 0));
    rooms["00"] = r00;
    r01 = new Room("Dark World", "Don't expect anything good for you here", "r01", ui->groupBox_2, Point(0, 1));
    rooms["01"] = r01;
    r02 = new Room("Volcanic World", "Only two ways to stay alive \"Fire bending\" or \"Water bending\"", "r02", ui->groupBox_3, Point(0, 2));
    rooms["02"] = r02;
    r10 = new Room("Zombie World", "A place for Zombies to enjoy their time and you are not invited at all", "r10", ui->groupBox_4, Point(1, 0));
    rooms["10"] = r10;
    r11 = new Room("Dragon hills", "Hills full of Chaos caused by the thousands of dragons living there", "r11", ui->groupBox_5, Point(1, 1));
    rooms["11"] = r11;
    r12 = new Room("The Iron Fortress", "A massive high Fortress was built to protect Humans from the other worlds ", "r12", ui->groupBox_6, Point(1, 2));
    rooms["12"] = r12;
    r20 = new Room("Devil lands", "In these Lands be one of them, or be Dead ", "r20", ui->groupBox_7, Point(2, 0));
    rooms["20"] = r20;
    r21 = new Room("UnderWorld", "only few people were able to get out alive", "r21", ui->groupBox_8, Point(2, 1));
    rooms["21"] = r21;
    r22 = new Room("Parallel World", "Hateful Souls and Sealed Ghosts stuck forever", "r22", ui->groupBox_9, Point(2, 2));
    rooms["22"] = r22;
}
void MainWindow::initializeLinks()
{
    r00->link(r01, "EAST" );
    r00->link(r10, "SOUTH");
    r01->link(r02, "EAST" );
    r02->link(r12, "SOUTH");
    r10->link(r20, "SOUTH");
    r11->link(r12, "EAST" );
    r11->link(r21, "SOUTH");
    r12->link(r22, "SOUTH");
    r20->link(r21, "EAST" );
    r21->link(r22, "EAST" );
}
void MainWindow::initializeAgents()
{
    charachters = new Agent*[5];
    charachters[0] = new Player ("FountainHero","A Masked Hero who mastered all the \"Water bending\" skills." ,  r22, 4000, 2000, 1500
                                 , QPixmap( ":/Agents/masked_hero_fountain_by_liavcol-d7lrduf.jpg" ));   //player1
    charachters[1] = new Player ("InfernoHero","A Masked Hero who mastered all the \"Fire bending\" skills. " ,  r22, 4000, 2000, 1500
                                 , QPixmap( ":/Agents/masked_hero_inferno_by_liavcol-d7k39cr.jpg" ));  //player2
    charachters[2] = new Monster("ZombieWarrior","A skull monster and a zombie servant for the Tormentor.",  r11, 2000,  1001,  800
                                 , QPixmap( ":/Agents/Zombie.jpg" ));        //monster1
    charachters[3] = new Monster("FlameGhost","A flame monster and a ghost servant for the Tormentor.",  r10, 2000,  1001,  800
                                 , QPixmap( ":/Agents/Flame.jpg" ));        //monster2
    charachters[4] = new SmartMonster("OBELISKtheTormentor","The descent of this mighty creature shall be heralded by burning winds and twisted lands. And with the coming of this horror, those who draw breath shall know the meaning of eternal slumber." ,r00, 3000,  2001,  400
                                 , QPixmap( ":/Agents/obelisk.jpg" ));        //monster3
}
void MainWindow::AddItems()
{
    Object* MillenniumShield  = new Prop( "MillenniumShield", "this shield is rumored to block any strong attack", 0, 1000 );
    Object* AxeofFools = new Prop( "AxeofFools", "holder of this Axe will have the best luck ever.", 2000, 0 );
    Object* SwordofDestruction = new Prop( "SwordofDestruction", "a Sword that can destroy all the dark creatures and vanish \
                                           them from existence.", 1500, 0 );
    Object* LightningBlade = new Prop( "LightningBlade", "a blade which can turn your enemies to ashes in a second.", 1500, 500);
    Object* LegendarySword = new Prop( "LegendarySword", "an ancient sword was used by a Brave king to make his legacy.", 1500, 1000 );
    Object* treasure = new Treasure( "The Pharaoh Treasue", "a treasure made only from Gold, Platinum, Diamonds, Rhodium, Painite, Jadeite and Rubies\
                                     the abstract value is in the range of \"3 Billion Dollars\". adding it's an ancient 7000 year-old\
                                     treasure, multiply that by at least 100 times." );
    Object* rightKey = new FixedProp("Old Steel Key", "The Key Of Light AND Dark", 0);
    Object* wrongKey = new FixedProp("Golden Shine Key", "Amazing And Adorable Key", 0);
    Object* hpHealer = new FixedProp("Health Angle", "Increases You Health", 1000);
    Object* trick = new FixedProp("MystryBox", "Increases You Health", -1000);
    Object* trick2= new FixedProp("MystryBox", "Increases You Health", -500);

    r00->addItem(treasure);
    r01->addItem(SwordofDestruction);
    r01->addItem(trick);
    r02->addItem(rightKey);
    r10->addItem(wrongKey);
    r11->addItem(LegendarySword);
    r11->addItem(hpHealer);
    r12->addItem(MillenniumShield);
    r20->addItem(LightningBlade);
    r21->addItem(hpHealer);
    r22->addItem(AxeofFools);
    r22->addItem(trick2);
}
void MainWindow::initializeLabels()
{
    myMap["r00"]["OBELISKtheTormentor"] = ui->label_1;
    myMap["r00"]["FlameGhost"] = ui->label_2;
    myMap["r00"]["FountainHero"]  = ui->label_3;
    myMap["r00"]["InfernoHero"]  = ui->label_4;

    myMap["r01"]["ZombieWarrior"] = ui->label_5;
    myMap["r01"]["FlameGhost"] = ui->label_6;
    myMap["r01"]["FountainHero"]  = ui->label_7;
    myMap["r01"]["InfernoHero"]  = ui->label_8;

    myMap["r02"]["OBELISKtheTormentor"] = ui->label_9;
    myMap["r02"]["FlameGhost"] = ui->label_10;
    myMap["r02"]["FountainHero"]  = ui->label_11;
    myMap["r02"]["InfernoHero"]  = ui->label_12;

    myMap["r10"]["OBELISKtheTormentor"] = ui->label_13;
    myMap["r10"]["FlameGhost"] = ui->label_14;
    myMap["r10"]["FountainHero"]  = ui->label_15;
    myMap["r10"]["InfernoHero"]  = ui->label_16;

    myMap["r11"]["ZombieWarrior"] = ui->label_17;
    myMap["r11"]["OBELISKtheTormentor"] = ui->label_18;
    myMap["r11"]["FountainHero"]  = ui->label_19;
    myMap["r11"]["InfernoHero"]  = ui->label_20;

    myMap["r12"]["ZombieWarrior"] = ui->label_21;
    myMap["r12"]["FlameGhost"] = ui->label_22;
    myMap["r12"]["FountainHero"]  = ui->label_23;
    myMap["r12"]["InfernoHero"]  = ui->label_24;

    myMap["r20"]["ZombieWarrior"] = ui->label_25;
    myMap["r20"]["FlameGhost"] = ui->label_26;
    myMap["r20"]["FountainHero"]  = ui->label_27;
    myMap["r20"]["InfernoHero"]  = ui->label_28;

    myMap["r21"]["ZombieWarrior"] = ui->label_29;
    myMap["r21"]["OBELISKtheTormentor"] = ui->label_30;
    myMap["r21"]["FountainHero"]  = ui->label_31;
    myMap["r21"]["InfernoHero"]  = ui->label_32;

    myMap["r22"]["OBELISKtheTormentor"] = ui->label_33;
    myMap["r22"]["FlameGhost"] = ui->label_34;
    myMap["r22"]["FountainHero"]  = ui->label_35;
    myMap["r22"]["InfernoHero"]  = ui->label_36;

}

void MainWindow::initializeLast()
{
    ui->Image->setScaledContents( true );
    ui->Image->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    ui->Image->setPixmap( charachters[0]->image );

    ui->leftText->setText(  charachters[0]->getName() + "\n" + charachters[0]->getDiscription() );
    ui->rightText->setText( dynamic_cast<Player*>(charachters[0])->PrintItems() );


    map<QString, map<QString, QLabel*> >::const_iterator it;
    for( it = myMap.begin(); it != myMap.end(); it++ )
    {
        map<QString, QLabel*>::const_iterator it2;
        for( it2 = it->second.begin(); it2 != it->second.end(); it2++ )
        {
            it2->second->setScaledContents( true );
            it2->second->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
        }
    }

    r00->setAllLabels( myMap["r00"] );
    r01->setAllLabels( myMap["r01"] );
    r02->setAllLabels( myMap["r02"] );
    r10->setAllLabels( myMap["r10"] );
    r11->setAllLabels( myMap["r11"] );
    r12->setAllLabels( myMap["r12"] );
    r20->setAllLabels( myMap["r20"] );
    r21->setAllLabels( myMap["r21"] );
    r22->setAllLabels( myMap["r22"] );
}


