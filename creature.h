// huddlers-qt/creature.h
// This code is copyright 2017 inhabited.systems

#ifndef CREATURE_H
#define CREATURE_H

#include <QObject>
#include <QWidget>
#include <QString>
#include <QGraphicsItem>

class Creature
{
public:
    Creature();
    ~Creature();

    void setGraphicsObject(QAbstractGraphicsShapeItem *graphicsObjectPtr);
    void setid(int id);
    void setname(QString name);
    void setPosX(qreal x);
    void setPosY(qreal y);
    void setLastPosX(qreal x);
    void setLastPosY(qreal y);
    void setWidth(qreal w);
    void setHeight(qreal h);
    void setSize(qreal s);
    void setoutlinecolor(QColor linecolor);
    void setoutlinewidth(int linewidth);
    void setfillcolor(QColor fillcolor);
    void settype(int type);
    void setSpeed(qreal x);
    void setOriginalSpeed(qreal s);
    void setTarget1(Creature *target1);
    void setTarget2(Creature *target2);

    int getid();
    QString getname();
    qreal getPosX();
    qreal getPosY();
    qreal getLastPosX();
    qreal getLastPosY();
    qreal distanceTo(QPointF pos);

    qreal getWidth();
    qreal getHeight();
    qreal getSize();
    qreal getSpeed();
    qreal getOriginalSpeed();

    Creature *getTarget1();
    Creature *getTarget2();
    QAbstractGraphicsShapeItem *getGraphicsObject();

private:
    int         mId;
    QString     mName;
    qreal       mPosX;
    qreal       mPosY;
    qreal       mLastPosX;
    qreal       mLastPosY;
    qreal       mDestinationX;
    qreal       mDestinationY;
    QPointF     mDestination;
    Creature    *mTarget1;
    Creature    *mTarget2;
    QPointF     mTargetPos1;
    QPointF     mTargetPos2;
    qreal       mWidth;
    qreal       mHeight;
    int         mSize;
    int         mType;
    qreal       mSpeed;
    qreal       mOriginalSpeed;
    qreal       mHaltForAnimTickCount;
    QAbstractGraphicsShapeItem *mCreatureGraphicsObject;
};

#endif // CREATURE_H
