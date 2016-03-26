#ifndef CELL_HPP
#define CELL_HPP

#include <QVector>

//class Field;

#include <QObject>

class Cell : public QObject
{
    Q_OBJECT
public:
    enum Mark {
        MarkNothing,
        MarkFlagged,
        MarkQuestioned
    };

    Cell(/*Field *field, */int x, int y);

    int x() const { return m_x; }
    int y() const { return m_y; }

    int minesAround() const;

    Mark mark() const { return m_mark; }

    void toggleMark();


    bool haveMine() const { return m_haveMine; }
    void setHaveMine(bool haveMine);

    bool isOpen() const { return m_open; }

    bool isMarked() const { return m_marked; }

    void open();

    void reset();

    QVector<Cell*> getNeighbors() const;

    void tryToOpenAround();

    void setNeighbors(const QVector<Cell*> &neighbors);

    void reveal();

    bool isExploded()const { return m_exploded; }

signals:
    void opened(int x, int y);

    void markChanged(Mark newMark);

private:
    //Field *m_field;

    int m_x;
    int m_y;

    bool m_haveMine;
    bool m_open;

    bool m_marked;

    Mark m_mark;

    QVector <Cell*> m_neighbors;

    bool m_exploded;
};

#endif // CELL_HPP
