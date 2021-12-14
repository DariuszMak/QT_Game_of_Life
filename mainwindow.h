#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <fstream>
//#include <iostream>
using namespace std;

#include <QTime>//potrzebne do określenia losowości
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

    int NumberOfColumns;
    int NumberOfRows;

    int MinSizeSquare;//zmienna przechowująca najmniejszą dopuszczalną wartość rozmiaru pojedynczego kwadracika w tabeli w pikselach

    QString TitleProj;//zmienna typu string przechowująca tytuł całego projektu

    QColorDialog ChooseAliveColor;//okno dialogowe wyboru koloru dla żywych kwadracików
    QColorDialog ChooseDeadColor;//okno dialogowe wyboru koloru dla martwych kwadracików
    QColor AliveColor;//zmienna przechowująca kolor żywych kwadracików
    QColor DeadColor;//zmienna przechowująca kolor martwych kwadracików

    void SetInitialValues();//metoda ustawiająca wszystkie niezbędne wartości początkowe (rozmiar, ilość kolumn i wierszy na interfejsie, domyślne kolory)

    void ChangeSet();//metoda zmieniająca tytuł okna oraz wartość zmiennej changed

    void resizeEvent(QResizeEvent *event);

    void closeEvent(QCloseEvent * event);//specjalna metoda do przedefiniwania działań przy zamykaniu programu

private slots:
    void RowsChanged(int);//utworzenie odpowiedniej wielkości wierszy tabeli na podstawie przyjętej wartości
    void ColumnsChanged(int);//utworzenie odpowiedniej wielkości kolumn tabeli na podstawie przyjętej
    void SwitchField(int, int, bool);//funkcja ustawiająca w tabeli odpowiedni kwadracik w zależności od przyjętej wartości logicznej
    //void UpadeScreen();//funkcja aktualizująca stan ekranu z algorytmem
    void ClearScreen();//funkcja czyszcząca ekran i dane w algorytmie i na ekranie jednocześnie zatrzymuje symulację, ponieważ nie ma żywych pól w tabeli
    void ResizeField(int);//funkcja przyjmująca rozmiar pojedynczego pola na ekranie
    void TidyUpScreen();//funkcja dobierająca właściwości w oknie tak, aby kompozycja była spójna
    void DisplayAccordingToBuffer(uint8_t * const);

    void printBuffer(uint8_t * const);

signals:
    void StatusAsk();//zapytanie algorytmu o ilość żywych kokórek i iteracji
    void ScreenAsk();//zapytanie o wszystkie wartości prawdziwe w tablicy roboczej algorytmu
    void ClearAlg(); //zerowanie zawartości tablicy roboczej algorytmu
    void Refresh_fields_state();//sygnał porządkujący właściowści ona programu w celu uzyskania maksymalnej spójności
    void CloseOtherWindows();//sygnał zamknięcia innych okien
    void LcdBufferModified();
};

#endif // MAINWINDOW_H
