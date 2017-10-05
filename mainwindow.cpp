// huddlers-qt/mainwindow.cpp
// This code is copyright 2017 inhabited.systems

#include <QtWidgets>
#include <QDebug>
#include "mainwindow.h"
#include "creature.h"

MainWindow::MainWindow(QWidget *parent) // MainWindow object constructor code
    : QMainWindow(parent)
    //make sure the initializer list is in the same order as in .h file
    , mGraphicsView(NULL)
    , mGraphicsScene(NULL)
    , mEllipseItem(NULL)
    , mAnimationUpdateInterval(2)  // in milliseconds
    , mGameLogicUpdateInterval(50) // in milliseconds
    , mWindowOriginX(56)
    , mWindowOriginY(100)
    , mWindowWidth(1000)
    , mWindowHeight(800)
    , mSceneWidth(600)
    , mSceneHeight(600)
    , mWindowSceneXOffset(60)
    , mWindowSceneYOffset(100)
    , mWindowViewOffset(40)
    , mCreatureCount(200)
{
    qDebug() << "huddlers-qt " << __FUNCTION__ << "*** STARTED ***";

    setupGUI();
    if (mCreatureCount >= 5)
    {
        setupGame();
        startAnimationTimer(); // fires animationTick()
        startGameLogicTimer(); // fires gameLogicTick()
    }
    else
    {
        qDebug() << "huddlers-qt " << __FUNCTION__ << " ERROR: mCreatureCount (" << mCreatureCount << ") < 5";
    }

}

MainWindow::~MainWindow() // MainWindow object destructor code
{
    qDebug() << "huddlers-qt " << __FUNCTION__ << "*** DELETING SCENE ***";

    if (mGraphicsView != NULL)
    {
        delete mGraphicsView;
        mGraphicsView = NULL;
    }
    if (mGraphicsScene != NULL)
    {
        mGraphicsScene->clear();
        delete mGraphicsScene;
        mGraphicsScene = NULL;
    }
    qDebug() << "huddlers-qt " << __FUNCTION__ << "*** ENDED ***";
}

void MainWindow::setupGUI()
{
    setGeometry(mWindowOriginX, mWindowOriginY, mWindowWidth, mWindowHeight);
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // set up the scene
    mGraphicsScene = new QGraphicsScene(0, 0, mSceneWidth, mSceneHeight);

    // set up the view, centering it in the window
    mGraphicsView = new QGraphicsView(mGraphicsScene);
    mGraphicsView->setGeometry(0,0, mSceneWidth, mSceneHeight);
    mGraphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    mGraphicsView->setDragMode(QGraphicsView::ScrollHandDrag);

    QLayout *mylayout = new QHBoxLayout();
    centralWidget->setLayout(mylayout);
    mylayout->addWidget(mGraphicsView);
}

void MainWindow::setupGame()
{
    qsrand(QDateTime::currentMSecsSinceEpoch() / 1000);
    // qDebug() << "random = " << qrand();

    QPen pen;
    pen.setColor(QColor(Qt::black));
    pen.setWidth(1);

    mPrimeCreature = new Creature();
    mPrimeCreature->setGraphicsObject(new QGraphicsEllipseItem(0,0,10,10));
    mPrimeCreature->setPosX(10);
    mPrimeCreature->setPosY(10);
    mPrimeCreature->setSpeed(0.25);
    mPrimeCreature->setOriginalSpeed(mPrimeCreature->getSpeed());
    mPrimeCreature->setfillcolor(QColor(255,0,0));
    mGraphicsScene->addItem(mPrimeCreature->getGraphicsObject());

    mGraphicsScene->addRect(0,0,mSceneWidth, mSceneHeight);

    pen.setColor(QColor(Qt::black));
    pen.setWidth(1);

    for (int i=0; i<=mCreatureCount; i++)
    {
        Creature *mycreature = new Creature();
        int x = (qrand()%mWindowWidth)*0.9;
        int y = (qrand()%mWindowHeight)*0.9;
        qreal mysize = 6.0 + qrand()%10;
        mycreature->setGraphicsObject(new QGraphicsEllipseItem(0,0,mysize,mysize));
        mycreature->setSize(mysize);
        mycreature->setPosX(x);
        mycreature->setPosY(y);
        qreal minRandomSpeed = ((qrand()%10)/1000.0) + 0.02;
        mycreature->setSpeed(((qrand()%10)/100.0) + minRandomSpeed);
        mycreature->setOriginalSpeed(mycreature->getSpeed());

        //mycreature->setPen(pen);
        mycreature->getGraphicsObject()->setPen(pen);
        //mycreature->getGraphicsObject()->setBrush(QBrush(QColor(100,100,100), Qt::SolidPattern));
        mycreature->getGraphicsObject()->setBrush(QBrush(QColor(qrand()%255,qrand()%255,qrand()%255), Qt::SolidPattern));
        mGraphicsScene->addItem(mycreature->getGraphicsObject());
        mCreatures.push_back(mycreature);
    }

    for (int i=0; i<=mCreatureCount; i++)
    {
        mCreatures.at(i)->setTarget1(mCreatures.at(qrand()%mCreatureCount));
        mCreatures.at(i)->setTarget2(mCreatures.at(qrand()%mCreatureCount));
    }

    // Change colors of one of the creatures just to see if it works
    mCreatures.at(0)->setoutlinecolor(Qt::green);
    mCreatures.at(1)->setfillcolor(Qt::blue);
    mCreatures.at(2)->setoutlinewidth(3);

    //qDebug() << "huddlers-qt " << __FUNCTION__ << "*** ENDED ***";
}

void MainWindow::startAnimationTimer()
{
    // associate the signal timeout() to the slot gameTick(), and start our update timer
    // SHOULD timeout() HAVE A UNIQUE NAME HERE?
    QObject::connect(&mAnimationTimer, SIGNAL(timeout()), this, SLOT(animationTick()));
    mAnimationTimer.start(mAnimationUpdateInterval);
}

void MainWindow::startGameLogicTimer()
{
    // associate the signal timeout() to the slot gameTick(), and start our update timer
    // SHOULD timeout() HAVE A UNIQUE NAME HERE?
    QObject::connect(&mGameLogicTimer, SIGNAL(timeout()), this, SLOT(gameLogicTick()));
    mGameLogicTimer.start(mGameLogicUpdateInterval);
}

void MainWindow::animationTick()
{

    mPrimeCreature->setPosX(mPrimeCreature->getPosX() + mPrimeCreature->getSpeed());
    mPrimeCreature->setPosY(mPrimeCreature->getPosY() + mPrimeCreature->getSpeed());

    for (int i=0; i<=mCreatureCount; i++)
    {

        // I don't think targetting or movement stuff really belong in animationTick()
        // they should be called from gameLogicTick() I think.

        qreal tx = mCreatures.at(i)->getTarget1()->getPosX();
        qreal ty = mCreatures.at(i)->getTarget1()->getPosY();
        QPointF tpf(tx, ty);
        qreal myX = mCreatures.at(i)->getPosX();
        qreal myY = mCreatures.at(i)->getPosY();
        qreal targetX = mCreatures.at(i)->getTarget1()->getPosX();
        qreal targetY = mCreatures.at(i)->getTarget1()->getPosY();
        qreal mySpeed = mCreatures.at(i)->getSpeed();

        if (mCreatures.at(i)->distanceTo(tpf) > mCreatures.at(i)->getTarget1()->getSize()*10.0)
        {
            if (targetX > myX)
                mCreatures.at(i)->setPosX(myX + mySpeed);
            if (targetX < myX)
                mCreatures.at(i)->setPosX(myX - mySpeed);
            if (targetY > myY)
                mCreatures.at(i)->setPosY(myY + mySpeed);
            if (targetY < myY)
                mCreatures.at(i)->setPosY(myY - mySpeed);
        }

        if (mPrimeCreature->getPosX() < 0) mPrimeCreature->setPosX(mSceneWidth);
        if (mPrimeCreature->getPosX() > mSceneWidth) mPrimeCreature->setPosX(0);
        if (mPrimeCreature->getPosY() < 0) mPrimeCreature->setPosY(mSceneHeight);
        if (mPrimeCreature->getPosY() > mSceneHeight) mPrimeCreature->setPosY(0);

        if (myX < 0) mCreatures.at(i)->setPosX(mSceneWidth);
        if (myX > mSceneWidth) mCreatures.at(i)->setPosX(0);
        if (myY < 0) mCreatures.at(i)->setPosY(mSceneHeight);
        if (myY > mSceneHeight) mCreatures.at(i)->setPosY(0);

    }

    mGraphicsScene->advance();
}

void MainWindow::gameLogicTick()
{
    for (int i=0; i<=mCreatureCount; i++)
    {
        int changeTargetFactor = 50;
        int randomCreature = qrand()%mCreatureCount;

        if (qrand()%changeTargetFactor == 0) mCreatures.at(i)->setTarget1(mCreatures.at(randomCreature));

    }

}

void MainWindow::doNothing() {}
