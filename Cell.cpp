#include "Cell.hpp"

#include "Field.hpp"

Cell::Cell(int x, int y):
    QObject()
{
    m_x = x;
    m_y = y;

    m_haveMine = false;
    m_open = false;

    m_marked = false;

    m_exploded = false;
}

int Cell::minesAround() const
{
    int mines = 0;
    for (Cell *cell : getNeighbors()) {
        if (cell->haveMine()) {
            ++mines;
        }
    }
    return mines;

}

void Cell::setHaveMine(bool haveMine)
{
    m_haveMine = haveMine;
}

void Cell::toggleMark()
{
    switch (m_mark) {
    case MarkNothing:
        m_mark = MarkFlagged;
        m_marked = true;
        emit markChanged(m_mark);
        break;
    case MarkFlagged:
        m_mark = MarkQuestioned;
        m_marked = false;
        emit markChanged(m_mark);
        break;
    case MarkQuestioned:
        m_mark = MarkNothing;
        emit markChanged(m_mark);
        break;
    }
}

void Cell::tryToOpenAround()
{
    int mark = 0;
    for (Cell *cell : getNeighbors()) {
        if (cell->isMarked()) {
            ++mark;
        }
    }

    if (mark == minesAround()){
        for (Cell *cell : getNeighbors()) {
            if (cell->isMarked() == false && cell->mark() != MarkQuestioned){
                cell->open();
            }
        }
    }
}

void Cell::open()
{
    if (m_open == true){
            return;
    }

    m_open = true;
    emit opened(x(), y());
    emit isOpenChanged(isOpen());
    if (minesAround() == 0 && m_haveMine == false){
        for (Cell *cell : getNeighbors()) {
                cell->open();
        }
    }
    if (haveMine() == true){
        m_exploded = true;
        emit isExplodedChanged(isExploded());
    }
    emit minesAroundChanged(minesAround());
}


void Cell::reset()
{
    m_haveMine = false;
    m_open = false;

    m_marked = false;

    m_mark = MarkNothing;

    m_exploded = false;

    emit isExplodedChanged(isExploded());

    emit minesAroundChanged(minesAround());

    emit isOpenChanged(isOpen());

}

void Cell::setNeighbors(const QVector<Cell*> &neighbors)
{
    m_neighbors = neighbors;
}

QVector<Cell *> Cell::getNeighbors() const
{
    return m_neighbors;
}

void Cell::reveal()
{
    m_open = true;

    emit minesAroundChanged(minesAround());

    emit isOpenChanged(isOpen());
}
