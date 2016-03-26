#ifndef CELL_HPP
#define CELL_HPP

#include <QVector>

//class Field;

#include <QObject>

class Cell : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool haveMine READ haveMine NOTIFY haveMineChanged)
    Q_PROPERTY(bool isOpen READ isOpen NOTIFY opened)
    Q_PROPERTY(bool exploded READ isExploded NOTIFY isExplodedChanged)
    Q_PROPERTY(int minesAround READ minesAround NOTIFY minesAroundChanged)
    Q_PROPERTY(Mark mark READ mark NOTIFY markChanged)

public:
    enum Mark {
        MarkNothing,
        MarkFlagged,
        MarkQuestioned
    };

    Q_ENUM(Mark)

    //Cell(/*Field *field, */int x, int y);

    Cell(int x = 0, int y = 0);

    int x() const { return m_x; }
    int y() const { return m_y; }

    int minesAround() const;

    Mark mark() const { return m_mark; }

    void toggleMark();


    bool haveMine() const { return m_haveMine; }

    void setHaveMine(bool haveMine);

    bool isOpen() const { return m_open; }

    bool isMarked() const { return m_marked; }

    void reset();

    QVector<Cell*> getNeighbors() const;

    void tryToOpenAround();

    void setNeighbors(const QVector<Cell*> &neighbors);

    void reveal();

    bool isExploded()const { return m_exploded; }

public slots:
    void open();

signals:
    void opened(int x, int y);

    void markChanged(Mark newMark);

    void haveMineChanged(bool newHaveMine);

    void isOpenChanged(bool newIsOpen);

    void isExplodedChanged(bool newIsExploded);

    void minesAroundChanged(int newMinesAround);

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
