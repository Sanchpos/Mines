#ifndef FIELD_HPP
#define FIELD_HPP

#include <QVector>


class Cell;

#include <QObject>


class Field : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int width READ width NOTIFY widthChanged)
    Q_PROPERTY(int height READ height NOTIFY heightChanged)
    Q_PROPERTY(State state READ state NOTIFY stateChanged)
    Q_PROPERTY(bool resetInProgress READ resetInProgress NOTIFY progressChanged)

public:
    enum State{
        StateIdle,
        StateStarted,
        StateEnded
    };
    Q_ENUM(State)

    Field();

    void prepare();

    void setSize(int width, int height);
    void setNumberOfMines(int number);

    void generate(int x, int y);


    void lose();

    bool isGenerated() const { return m_generated; }

    int width() const { return m_width; }
    int height() const { return m_height; }

    //Cell *cellAt(int x, int y) const;
    Q_INVOKABLE Cell *cellAt(int x, int y) const;

    int numberOfMines() const { return m_numberOfMines; }

    int numberOfFlags() const { return m_numberOfFlags; }

    State state() const {return m_state;}

    bool resetInProgress() const {return m_resetInProgress; }

protected slots:
    void onCellOpened(int x, int y);

    void onCellMarkChanged();

public slots:

    void startNewGame();

signals:
    void numberOfMinesChanged();

    void numberOfFlagsChanged(int numberOfFlags);

    void stateChanged(State newState);

    void widthChanged(int newWidth);
    void heightChanged(int newHeight);

    void progressChanged(bool newProgress);

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

    bool m_resetInProgress;

};

#endif // FIELD_HPP
