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

#include <QCloseEvent>

#include "conwayalg.h"
#include "ui_mainwindow.h"

#include "help.h"
#include "ui_help.h"

#include "settingwindow.h"
#include "ui_settingwindow.h"

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
    ConwayAlg * Algorithm;//wskaźnik na obiekt klasy ConwayAlg
    Help * HelpWindow;//utworzenie wskaźnika klasy help (okna z pomocą)
    SettingWindow * SettingsWindow;//utworzenie wskaźnika klasy help (okna z ustawieniami zasad algrotytmu)

    bool IsRunning;//zmienna wyznaczająca, czy symulacja trwa, czy nie
    bool Changed;//zmienna przechowująca informację, czy coś się na ekranie zmieniło
    QTimer Timer;//timer wykorzystany do animacji
//    QTimer TimerController;//timer wykorzystany do kontroli szybkości odświeżania się algorytmu

//    int MilisecondsPerFrame;//zmienna przechowująca ilość klatek

    int MinSizeSquare;//zmienna przechowująca najmniejszą dopuszczalną wartość rozmiaru pojedynczego kwadracika w tabeli w pikselach

    QString TitleProj;//zmienna typu string przechowująca tytuł całego projektu
    QString MainPath;//główna ścieżka dostępu do pliku przechowywana w programie
    QString UnsavePath;//zmienna typu string przechowująca ścieżkę do niezapisanego pliku

    QColorDialog ChooseAliveColor;//okno dialogowe wyboru koloru dla żywych kwadracików
    QColorDialog ChooseDeadColor;//okno dialogowe wyboru koloru dla martwych kwadracików
    QColor AliveColor;//zmienna przechowująca kolor żywych kwadracików
    QColor DeadColor;//zmienna przechowująca kolor martwych kwadracików

    QMessageBox SaveError;//komunikat błędu zapisu
    QMessageBox LoadError;//komunikat błędu odczytu
    QMessageBox SaveWhenClosed;//komunikat z zapytaniem, czy zapisać plik przed wyjściem z programu
    QMessageBox WillBeSaved;//komunikat informujący o zapisaniu w domyślnej lokalizacji zapisu
    QMessageBox CloseWindow;//komunikat py

    void SaveScreen(char*);//metoda zapisująca do pliku całą zawartość wartości logicznych zawartych w tabeli
    void LoadScreen(char*);//metoda wczytująca z pliku całą zawartość wartości logicznych zawartych w tabeli

    void SaveUnsaved();//metoda pytająca, czy zapisać niezapisany plik
    void SetInitialValues();//metoda ustawiająca wszystkie niezbędne wartości początkowe (rozmiar, ilość kolumn i wierszy na interfejsie, domyślne kolory)

    void Load();//reagująca na przycisk "wczytaj"
    void LoadAs();//metoda ragująca na przycik wczytaj jako
    void Save();//metoda reagująca na przycisk "zapisz"
    void SaveAs();//metoda reagująca na przycisk "zapisz jako..."
    void New();//metoda reagująca na przycisk "nowy"

    void ChangeSet();//metoda zmieniająca tytuł okna oraz wartość zmiennej changed

    void closeEvent(QCloseEvent * event);//specjalna metoda do przedefiniwania działań przy zamykaniu programu

private slots:
    void RowsChanged(int);//utworzenie odpowiedniej wielkości wierszy tabeli na podstawie przyjętej wartości
    void ColumnsChanged(int);//utworzenie odpowiedniej wielkości kolumn tabeli na podstawie przyjętej
    void StatusUpdate(int feeds, int iterations);//funkcja aktualizująca stan ile obiektów żyje oraz ile iteracji wystąpiło
    void SwitchField(int, int, bool);//funkcja ustawiająca w tabeli odpowiedni kwadracik w zależności od przyjętej wartości logicznej
    //void UpadeScreen();//funkcja aktualizująca stan ekranu z algorytmem
    void ClearScreen();//funkcja czyszcząca ekran i dane w algorytmie i na ekranie jednocześnie zatrzymuje symulację, ponieważ nie ma żywych pól w tabeli
    void ResizeField(int);//funkcja przyjmująca rozmiar pojedynczego pola na ekranie
    void TidyUpScreen();//funkcja dobierająca właściwości w oknie tak, aby kompozycja była spójna
    void SettingSize(bool);//Slot włączający lub wyłączający dostęp do elementów zmiany rozmiaru
    void Generate();//metoda generująca losowe elementy na ekranie
    void SimulationToggle();//metoda włączająca, bądź wyłączająca symulację
    void SimulationStep();//pojedynczy krok, wywołany przez przepełnienie timera
    //void TimerControllerTimeout();//akcja reagująca na przepełnienie się timera kontrolującego przebieg animacji
    void WindowStep();//slot wnikający, czy jest uruchomiona symulacja, reagujący na działanie przycisku "Krok"
    void MultiStep();//slot wykonujący wiele kroków algorytmu bez wyświetlania go
    void TorusChange(bool);//slot przyjmujący stan zapętlania z algorytmu do mainwindow
    void on_action_Zapisz_triggered();//slot wywoływany przez akcję "zapisz"
    void on_actionWczytaj_jako_triggered();//slot wywoływany przez akcję "wczytaj jako..."
    void on_actionZapisz_jako_triggered();//slot wywoływany przez akcję "zapisz jako..."
    void on_actionWczytaj_triggered();//slot wywoływany przez akcję "wczytaj"

    void on_action_Nowy_triggered();

    void on_actionOd_wie_triggered();

    void on_actionKolor_ywych_kom_rek_triggered();

    void on_actionKo_lor_martwych_kom_rek_triggered();

    void on_actionO_programie_triggered();

    void on_action_Ustawienia_zasad_triggered();

signals:

    void StatusAsk();//zapytanie algorytmu o ilość żywych kokórek i iteracji
    void ScreenAsk();//zapytanie o wszystkie wartości prawdziwe w tablicy roboczej algorytmu
    void ClearAlg(); //zerowanie zawartości tablicy roboczej algorytmu
    void TidyUp();//sygnał porządkujący właściowści ona programu w celu uzyskania maksymalnej spójności
    void DoStep();//sygnał wykonania kroku w algorytmie
    void CloseOtherWindows();//sygnał zamknięcia innych okien
};

#endif // MAINWINDOW_H
