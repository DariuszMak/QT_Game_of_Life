#ifndef CONWAYALG_H
#define CONWAYALG_H

#include <QVector>
#include <QInputDialog>
#include <QObject>
#include <QTimer>


class ConwayAlg : public QObject
{
    Q_OBJECT
public:
    ConwayAlg();
private:
    int Rows;//obowiązująca liczba wierszy dla tablicy algorytmu
    int Columns;//obowiązująca liczba kolumn dla tablicy algorytmu
    int Feeds;//ilość pól żywych
    int Iterations;//ilość wykonanych iteracji
    bool Torus;//zmienna odpowiedzialna za zapętlanie

    QVector< QVector<bool> > Field;//wektor w wektorze, tablica dwuwymiarowa na której działamy w algorytmie

public slots:
    void NewRows(int);//funkcja ustawiająca nową ilość rzędów w algorytmie
    void NewColumns(int);//funkcja ustawiająca nową ilość kolumn w algorytmie
    void ToggleCell(int, int);//zmiana logiczna w tablicy roboczej algortymu.
    void ScreenAns();//metoda przkazująca do mainwindow wszystkie wartości logiczne w tablicy roboczej
    void ClearValues();//zerowanie wartości pól w tablicy roboczej algorytmu

signals:
    void NewRowsInf(int);//sygnał przekazujący do mainwindow informację o zmienionej liczbie wierszy w algorytmie
    void NewColumnsInf(int);//sygnał przekazujący do mainwindow informację o zmienionej liczbie kolumn w algorytmie
    void ActualStatusInf(int, int);//sygnał przekazujący do mainwindow informację o ilośći żywych obiektów oraz wykonanych iteracji
    void ChangeItem(int, int, bool);//sygnał nakazujący zmienić pole w mainwindow na zgodne z wartością logiczną
};

#endif // CONWAYALG_H
