#ifndef FIELD_HPP
#define FIELD_HPP

#include <QVector>


class Cell;

#include <QObject>


class Field : public QObject
{
    Q_OBJECT
public:
    enum State{
        StateIdle,
        StateStarted,
        StateEnded
    };

    Field();

    void prepare();

    void setSize(int width, int height);
    void setNumberOfMines(int number);

    void generate(int x, int y);


    void lose();

    bool isGenerated() const { return m_generated; }

    int width() const { return m_width; }
    int height() const { return m_height; }

    Cell *cellAt(int x, int y) const;

    int numberOfMines() const { return m_numberOfMines; }

    int numberOfFlags() const { return m_numberOfFlags; }

    State state() const {return m_state;}

protected slots:
    void onCellOpened(int x, int y);

    void onCellMarkChanged();


signals:
    void numberOfMinesChanged();

    void numberOfFlagsChanged(int numberOfFlags);

    void stateChanged(State newState);
private:
    QVector<Cell*> m_cells;

    void win();
    void setState(State newState);
    int m_width;
    int m_height;
    bool m_generated;
    int m_numberOfMines;
    int m_numberOfFlags;
    int m_numberOfOpenedCells;
    State m_state;
};

#endif // FIELD_HPP
