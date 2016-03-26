#include "CellItem.hpp"

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSimpleTextItem>
#include <QPainter>

#include "Cell.hpp"

const int CellItem::cellSize = 32;

CellItem::CellItem(Cell *cell, QGraphicsItem *parent) :
    QGraphicsItem(parent)
{
    m_cell = cell;
    m_text = new QGraphicsSimpleTextItem(this);

    QFont f = m_text->font();
    f.setPixelSize(cellSize - 4);
    m_text->setFont(f);


    //setPos(m_cell->x() * cellSize, m_cell->y() * cellSize);

    //setAcceptedMouseButtons(Qt::LeftButton);

    //setAcceptedMouseButtons(Qt::RightButton);
}

QRectF CellItem::boundingRect() const
{
    return QRectF(0, 0, cellSize, cellSize);
}

void CellItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::HighQualityAntialiasing);

    painter->drawRect(0, 0, cellSize, cellSize);


    if (m_cell->isOpen()) {
        if (m_cell->haveMine()) {
            //painter->fillRect(2, 2, cellSize - 4, cellSize - 4, Qt::red);
            if (m_cell->isExploded() == true){
                painter->fillRect(2, 2, cellSize - 4, cellSize - 4, Qt::red);
            }
            else{
                painter->fillRect(2, 2, cellSize - 4, cellSize - 4, Qt::green);
            }
            m_text->setText("+");
            m_text->setPos((cellSize - m_text->boundingRect().width())/2, (cellSize - m_text->boundingRect().height())/2);
        }
        else if(m_cell->minesAround() != 0){
            m_text->setText(QString::number(m_cell->minesAround()));
            m_text->setPos((cellSize - m_text->boundingRect().width())/2, (cellSize - m_text->boundingRect().height())/2);
        }
    }
    else {
        painter->fillRect(2, 2, cellSize - 4, cellSize - 4, Qt::gray);
        switch (m_cell->mark()) {
            case Cell::MarkFlagged:
                m_text->setText("!");
                m_text->setPos((cellSize - m_text->boundingRect().width())/2, (cellSize - m_text->boundingRect().height())/2);
                break;
            case Cell::MarkQuestioned:
                m_text->setText("?");
                m_text->setPos((cellSize - m_text->boundingRect().width())/2, (cellSize - m_text->boundingRect().height())/2);
                break;
            case Cell::MarkNothing:
                m_text->setText("");
                m_text->setPos((cellSize - m_text->boundingRect().width())/2, (cellSize - m_text->boundingRect().height())/2);
                break;
        }
    }
}


void CellItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    event->accept();
}

void CellItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
       if (m_cell->isOpen()){
            m_cell->tryToOpenAround();
       }
       else{
           m_cell->open();
       }
    }
    if (event->button() == Qt::RightButton) {
        m_cell->toggleMark();
    }
    update();
}
