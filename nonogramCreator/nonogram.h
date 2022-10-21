#ifndef NONOGRAM_H
#define NONOGRAM_H

#include <QWidget>
#include <QVector2D>
#include <QFile>

class Nonogram : public QWidget
{
    Q_OBJECT
public:
    explicit Nonogram(QWidget *parent = nullptr,int gridSize = 10);
    explicit Nonogram( QFile* file,QWidget *parent);

    void paintEvent(QPaintEvent *event) override;
    void paintGrid(int gridSize);
    void fillGrid();
    //the numbers on the left side of the grid
    void setLeftNums();
    //numbers on top of the grid
    void setTopNums();
    void paintNumbers();

    void exportSelf();
    //void importFile();

    int gridLength = 0;
    int offset;
    int gridSize;
    int squareSize = 0;
    int maxNums = 1;
    int numSize = 15;
    QVector<bool> grid;
    QVector<int> top;
    QVector<int> left;

    void mousePressEvent(QMouseEvent *ev) override;
signals:

};

#endif // Nonogram_H
