#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <fstream>

using namespace std;

#include <QTime>
#include <QMainWindow>
#include <string>
#include <QMessageBox>
#include <QColorDialog>
#include <QFileDialog>
#include <QString>
#include <QDialog>
#include <QTimer>

#include <QCloseEvent>
#include "ui_mainwindow.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    int Table_widget_cell_size;
    int LCDDataBufferSize;

    uint8_t LCDDataBuffer[1024] { 0 };


    int LCDNubmberOfXCoord;
    int LCDNubmberOfYCoord;

    int NumberOfColumnsInWidget;
    int NumberOfRowsInWidget;

    int MinSizeSquare;

    QString TitleProj;

    QColorDialog ChooseAliveColor;
    QColorDialog ChooseDeadColor;
    QColor AliveColor;
    QColor DeadColor;

    void SetInitialValues();

    void ChangeSet();

    void resizeEvent(QResizeEvent *event);

    void closeEvent(QCloseEvent * event);

private slots:
    void RowsChanged(int);
    void ColumnsChanged(int);
    void SwitchField(int, int, bool);
    
    void ClearScreen();
    void ResizeField(int);
    void DisplayAccordingToBuffer(uint8_t * const);

    void printBuffer(uint8_t * const);

signals:
    void ClearAlg(); 
    void CloseOtherWindows();
    void LcdBufferModified();
};

#endif 
