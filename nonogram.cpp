#include "nonogram.h"
#include "QPainter"
#include "QDebug"
#include "QColor"
#include "QMouseEvent"
#include <QFileDialog>

Nonogram::Nonogram(QWidget *parent, int gridSize) : QWidget(parent)
{
    //init grid size from config, before create class
    this->gridSize = gridSize;
    this->grid.fill(false, gridSize*gridSize);
    offset = ((gridSize / 2)+2) *12;
    setLeftNums();
    setTopNums();
    //clicked on widget ->
    //  check which grid place
    //  color grid place configured color
    //  have export button -> exports to json or image?

    // shows numbers on top and side when exported to image they stays
}

Nonogram::Nonogram(QFile* file, QWidget *parent): QWidget(parent){
    qDebug() << "loading data" ;
    QTextStream stream(file);
    //grid size
    QString data =  stream.readLine();
    this->gridSize = data.toInt();

    //grid
    data = stream.readLine();
    auto splitData = data.split(" ");
    for (auto item : splitData ) {
        this->grid.append(item.toInt());
    }
    if(grid.size() > gridSize* gridSize){
        grid.resize(gridSize* gridSize);
    }
    if(grid.size() == gridSize* gridSize){
        qDebug() << "size equals grid size";
    }

    file->close();
    qDebug() << splitData.size();
    qDebug() << this->grid.size() << this->gridSize;
    offset = ((gridSize / 2)+2) *12;
    setTopNums();
    setLeftNums();
}

void Nonogram::exportSelf(){
    QString dir;
    auto filename = QFileDialog::getSaveFileName(this, "select", dir,"*.nono");
    QFile file(filename, this);
    file.open(QIODevice::WriteOnly);
     QTextStream data(&file);

     data << gridSize << Qt::endl;
     for(auto gridLoc : this->grid){
        data << gridLoc << " ";
     }
     Qt::endl(data);
     file.close();
     qDebug() << "the file has been saved" + dir;
}

void Nonogram::paintEvent(QPaintEvent *event) {
    paintGrid(this->gridSize);
    paintNumbers();
    fillGrid();
}

void Nonogram::paintNumbers(){

    //qDebug() << "paintNumbers";
    QPainter paint(this);
    int index = this->top.length() -1;
    for (int i =gridSize;i >= 0;i--) {
        int localIndex= 0;
        while (top.value(index) != -1) {

            //qDebug() << index << top.value(index);
            int xCoord = offset + (i*squareSize) + (squareSize/2);

            if(top.value(index) > 9)
                paint.setPen(Qt::red);
            else
                paint.setPen(Qt::black);
            paint.drawText(xCoord, offset-(numSize*localIndex) - numSize - 5, numSize, numSize, 0 ,QString::number(top.value(index)) );
            localIndex++;
            index--;
        }
        //qDebug() << index;
        index--;
    }

    index = this->left.length() -1;
    for (int i =gridSize;i >= 0;i--) {
        int localIndex= 0;
        while (left.value(index) != -1) {

            //qDebug() << index << left.value(index);
            int yCoord = offset + i*squareSize;
            left.value(index);
            if(left.value(index) > 9)
                paint.setPen(Qt::red);
            else
                paint.setPen(Qt::black);
            paint.drawText(offset-((numSize)*localIndex) - (numSize), yCoord, numSize, numSize, 0 ,QString::number(left.value(index)) );
            localIndex++;
            index--;
        }
        //qDebug() << index;
        index--;
    }
}

void Nonogram::paintGrid(int grid){
    QPainter paint(this);
    //paint.drawLine(10,10, 50, 50);
    QSize size = QWidget::size();
    int minSize = size.height() > size.width() ? size.width(): size.height();
    minSize -= (offset);
    this->gridLength = minSize;
    this->squareSize = minSize / gridSize;
    for (int i = 0;i <= grid ;i++ ) {
        paint.drawLine(i*squareSize+ offset, offset ,i*squareSize+ offset, squareSize*grid + offset);
    }
    for (int i = 0;i <= grid ;i++ ) {
        paint.drawLine(offset,i*squareSize + offset,squareSize*grid+ offset,i*squareSize + offset);
    }
}

void Nonogram::fillGrid(){
    QPainter paint(this);
    paint.setBrush(QBrush(Qt::black));
    //qDebug() << "filling grid";
    for (int i = 0;i<gridSize ;i++ ) {
        //horizontal (x)
        for (int j = 0;j<gridSize ;j++ ) {
            if(grid.value((i*gridSize)+ j)){
                int starty = i*squareSize + offset,
                        startx = j*squareSize + offset;
                paint.drawRect(startx, starty, squareSize, squareSize);
            }
        }
    }
}

void Nonogram::mousePressEvent(QMouseEvent *ev){

    int xIndex = (ev->x() - offset)/squareSize;
    if(xIndex >= gridSize || xIndex <0){
        return;
    }
    int yIndex = (ev->y() - offset)/squareSize;
    if(yIndex >= gridSize || yIndex <0){
        return;
    }
    //qDebug() << xIndex << yIndex << yIndex*gridSize + xIndex << this->grid.size();
    int index = (yIndex*gridSize) + xIndex;
    //qDebug() << index;
    bool replace = !grid.value(index);
    this->grid.replace(index, replace);
    //qDebug() << this->grid;
    maxNums = 1;
    setTopNums();
    setLeftNums();
    update();

};

void Nonogram::setLeftNums(){
    bool bStart = true;
    int startIndex;
    QVector<int> list;
    list.append(-1);
    for (int j = 0;j < gridSize ;j++ ) {
        bool bAny= false;
        int numCount = 0;
        for (int i = 0;i<gridSize ;i++ ) {
            //qDebug() << bStart;
            int currIndex=i+(j*gridSize);
            if(bStart){
                if(this->grid[currIndex] == 1){
                    startIndex = i;
                    bStart = false;
                    bAny = true;
                    numCount++;
                }
            } else{
                if(this->grid[currIndex] == 0){
                    //qDebug() << "i - startIndex" << i - startIndex;
                    list.append(i-startIndex);
                    bStart = true;
                }
            }
            //qDebug() << i+(j*gridSize) <<  i;
        }
        //qDebug() << bStart;
        if(!bStart){
            bStart = true;
            list.append(gridSize-startIndex);
        }
        if(!bAny){
            list << 0;
        }
        if(numCount > maxNums){
            maxNums = numCount;
        }
        list.append(-1);

    }
    qDebug()<<list;
    this->left = list;
}

void Nonogram::setTopNums(){
    bool bStart = true;
    int startIndex;
    QVector<int> list;
    list.append(-1);
    for (int j = 0;j < gridSize ;j++ ) {
        int numCount = 0;
        bool bAny= false;
        for (int i = 0;i<gridSize ;i++ ) {
            //qDebug() << bStart;
            int currIndex=j+(i*gridSize);
            if(bStart){
                if(this->grid[currIndex] == 1){
                    startIndex = i;
                    bStart = false;
                    bAny = true;
                    numCount++;
                }
            } else{
                if(this->grid[currIndex] == 0){
                    //qDebug() << "i - startIndex" << i - startIndex;
                    list.append(i-startIndex);
                    bStart = true;
                }
            }
            //qDebug() << i+(j*gridSize) <<  i;
        }
        //qDebug() << bStart;
        if(!bStart){
            bStart = true;
            list.append(gridSize-startIndex);
        }
        if(!bAny){
            list << 0;
        }
        if(numCount > maxNums){
            maxNums = numCount;
        }
        list.append(-1);

    }
    //qDebug()<<"top"<<list;
    this->top = list;
}


