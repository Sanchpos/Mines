#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsItem>

namespace Ui {
class MainWindow;
}

class QGraphicsScene;
class Field;
class QGraphicsSimpleTextItem;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    void newGame();

    void resizeField(int width, int height);

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent *event);

protected slots:
    void updateSceneScale();

    void onFieldNumberOfFlagsChanged(int number);

private slots:
    void on_actionNewGame_triggered();

    void onFieldStateChanged();

    void difficultyBeginner();
    void difficultyIntermediate();
    void difficultyExpert();

    void on_actionBeginner_triggered();

    void on_actionIntermediate_triggered();

    void on_actionExpert_triggered();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *m_scene;
    Field *m_field;
    QGraphicsSimpleTextItem *m_gameStateText;
    QGraphicsRectItem *m_fieldItem;
    QGraphicsRectItem *m_gameStateRect;
};

#endif // MAINWINDOW_H
