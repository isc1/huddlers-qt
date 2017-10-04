// huddlers-qt/creature.cpp
// This code is copyright 2017 inhabited.systems

#include "creature.h"
#include <QWidget>
#include <QGraphicsItem>
#include <QDebug>
#include <QPen>

Creature::Creature()
    : mId(0)
    , mName("Clerd")
    , mPosX(0)
    , mPosY(0)
    , mLastPosX(0)
    , mLastPosY(0)
    , mDestinationX(0)
    , mDestinationY(0)
    , mTarget1(NULL)
    , mTarget2(NULL)
    , mWidth(0)
    , mHeight(0)
    , mSize(0)
    , mType(0)
    , mSpeed(0.2)
    , mOriginalSpeed(0.2)
    , mHaltForAnimTickCount(0)
    , mCreatureGraphicsObject(NULL)
{
    // Creature constructor
}

Creature::~Creature()
{

}

void Creature::setGraphicsObject(QAbstractGraphicsShapeItem *graphicsObjectPtr)
{
    if (graphicsObjectPtr != NULL)
    {
        mCreatureGraphicsObject = graphicsObjectPtr;
        mWidth = mCreatureGraphicsObject->boundingRect().width();
        mHeight = mCreatureGraphicsObject->boundingRect().height();
        mSize = mWidth * mHeight;
        mCreatureGraphicsObject->setPos(mPosX, mPosY);
    }
    else
    {
        qDebug("graphicsObjectPtr is Null!");
    }
}

void Creature::setid(int id)
{
    mId = id;
}

void Creature::setname(QString name)
{
    mName = name;
}

void Creature::setPosX(qreal x)
{
    if(mCreatureGraphicsObject != NULL)
    {
        mPosX = x;
        mCreatureGraphicsObject->setPos(mPosX, mPosY);
    }
    else
    {
        qDebug() << __FUNCTION__ << ":" << "Creature graphics object is NULL!";
    }
}

void Creature::setPosY(qreal y)
{
    if(mCreatureGraphicsObject != NULL)
    {
        mPosY = y;
        mCreatureGraphicsObject->setPos(mPosX, mPosY);
    }
    else
    {
        qDebug() << __FUNCTION__ << ":" << "Creature graphics object is NULL!";
    }
}

void Creature::setLastPosX(qreal x)
{
    if(mCreatureGraphicsObject != NULL)
    {
        mLastPosX = x;
    }
    else
    {
        qDebug() << __FUNCTION__ << ":" << "Creature graphics object is NULL!";
    }
}

void Creature::setLastPosY(qreal y)
{
    if(mCreatureGraphicsObject != NULL)
    {
        mLastPosY = y;
    }
    else
    {
        qDebug() << __FUNCTION__ << ":" << "Creature graphics object is NULL!";
    }
}


void Creature::setWidth(qreal w)
{
    mWidth = w;
    mSize = mWidth * mHeight;
}

void Creature::setHeight(qreal h)
{
    mHeight= h;
    mSize = mWidth * mHeight;
}

void Creature::setoutlinecolor(QColor linecolor)
{
    if(mCreatureGraphicsObject != NULL)
    {
        QPen pen = mCreatureGraphicsObject->pen();
        pen.setColor(linecolor); // TODO: Need to test this. Not sure setColor is the right thing.
        mCreatureGraphicsObject->setPen(pen);
    }
    else
    {
        qDebug() << __FUNCTION__ << ":" << "Creature graphics object is NULL!";
    }
}

void Creature::setoutlinewidth(int linewidth)
{
    if(mCreatureGraphicsObject != NULL)
    {
        QPen pen = mCreatureGraphicsObject->pen();
        pen.setWidth(linewidth); // TODO: Need to test this. Not sure setWidth is the right thing.
        mCreatureGraphicsObject->setPen(pen);
    }
    else
    {
        qDebug() << __FUNCTION__ << ":" << "Creature graphics object is NULL!";
    }
}

void Creature::setfillcolor(QColor fillcolor)
{
    if(mCreatureGraphicsObject != NULL)
    {
        QPen pen = mCreatureGraphicsObject->pen();
        pen.setColor(fillcolor); // TODO: Need to test this, it's probably not right.
        mCreatureGraphicsObject->setPen(pen);
    }
    else
    {
        qDebug() << __FUNCTION__ << ":" << "Creature graphics object is NULL!";
    }
}

void Creature::settype(int type)
{
    mType = type;
}


int Creature::getid()
{
    return mId;
}

QString Creature::getname()
{
    return mName;
}

qreal Creature::getPosX()
{
    return mPosX;

}

qreal Creature::getPosY()
{
    return mPosY;
}

qreal Creature::getLastPosX()
{
    return mLastPosX;

}

qreal Creature::getLastPosY()
{
    return mLastPosY;
}

qreal Creature::getWidth()
{
    return mWidth;
}

qreal Creature::getHeight()
{
    return mHeight;
}

void Creature::setSize(qreal s)
{
    if(mCreatureGraphicsObject != NULL)
    {
        mSize = s;
    }
    else
    {
        qDebug() << __FUNCTION__ << ":" << "Creature graphics object is NULL!";
    }
}

qreal Creature::getSize()
{
    return mSize;
}

qreal Creature::distanceTo(QPointF pos)
{
    //good ol' pythagoras
    //return sqrt((pos.x()-mPos.x())*(pos.x()-mPos.x()) + (pos.y()-mPos.y())*(pos.y()-mPos.y()));
    return sqrt((pos.x()-mPosX)*(pos.x()-mPosX) + (pos.y()-mPosY)*(pos.y()-mPosY));
}

void Creature::setSpeed(qreal s)
{
    if(mCreatureGraphicsObject != NULL)
    {
        mSpeed = s;
    }
    else
    {
        qDebug() << __FUNCTION__ << ":" << "Creature graphics object is NULL!";
    }
}

qreal Creature::getSpeed()
{
    if(mCreatureGraphicsObject != NULL)
    {
        return mSpeed;
    }
    else
    {
        qDebug() << __FUNCTION__ << ":" << "Creature graphics object is NULL!";
    }
    return 0.0;
}

void Creature::setOriginalSpeed(qreal s)
{
    if(mCreatureGraphicsObject != NULL)
    {
        mOriginalSpeed = s;
    }
    else
    {
        qDebug() << __FUNCTION__ << ":" << "Creature graphics object is NULL!";
    }
}

qreal Creature::getOriginalSpeed()
{
    if(mCreatureGraphicsObject != NULL)
    {
        return mOriginalSpeed;
    }
    else
    {
        qDebug() << __FUNCTION__ << ":" << "Creature graphics object is NULL!";
    }
    return 0.0;
}

void Creature::setTarget1(Creature *target1)
{
    if(mCreatureGraphicsObject != NULL && target1 != NULL)
    {
        mTarget1 = target1;
    }
    else
    {
        qDebug() << __FUNCTION__ << ":" << "Creature graphics object is NULL!";
    }
}

void Creature::setTarget2(Creature *target2)
{
    if(mCreatureGraphicsObject != NULL && target2 != NULL)
    {
        mTarget2 = target2;
    }
    else
    {
        qDebug() << __FUNCTION__ << ":" << "Creature graphics object is NULL!";
    }
}

Creature *Creature::getTarget1() //FIX
{
    if(mCreatureGraphicsObject != NULL)
    {
        return mTarget1;
    }
    else
    {
        qDebug() << __FUNCTION__ << ":" << "Creature graphics object is NULL!";
    }
    return NULL;
}

Creature *Creature::getTarget2() //FIX
{
    if(mCreatureGraphicsObject != NULL)
    {
        return mTarget2;
    }
    else
    {
        qDebug() << __FUNCTION__ << ":" << "Creature graphics object is NULL!";
    }
    return NULL;
}

QAbstractGraphicsShapeItem *Creature::getGraphicsObject()
{
    return mCreatureGraphicsObject;
}
