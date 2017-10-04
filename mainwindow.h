// huddlers-qt/mainwindow.h -- GUI top level declaration header file
// This code is copyright 2017 inhabited.systems

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QTimer>
#include <QWidget>
#include <creature.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    // enums

    // initialized in constructor
    QGraphicsView *mGraphicsView;
    QGraphicsScene *mGraphicsScene;
    QGraphicsEllipseItem *mEllipseItem;
    long mAnimationUpdateInterval;
    long mGameLogicUpdateInterval;
    int mWindowOriginX;
    int mWindowOriginY;
    int mWindowWidth;
    int mWindowHeight;
    int mSceneWidth;
    int mSceneHeight;
    int mWindowSceneXOffset;
    int mWindowSceneYOffset;
    int mWindowViewOffset;
    int mCreatureCount;

    // initialized after constructor
    QTimer mAnimationTimer;
    QTimer mGameLogicTimer;
    Creature *mPrimeCreature;
    QVector<Creature *> mCreatures;


    // methods
    void setupGUI();
    void setupGame();
    void startAnimationTimer();
    void startGameLogicTimer();

private slots:

    void animationTick();
    void gameLogicTick();
    void doNothing();
};

#endif // MAINWINDOW_H
