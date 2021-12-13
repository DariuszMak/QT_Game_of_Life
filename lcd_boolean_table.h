#ifndef LCD_BOOLEAN_TABLE_H
#define LCD_BOOLEAN_TABLE_H

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
    int Rows;//obowiÄ…zujÄ…ca liczba wierszy dla tablicy algorytmu
    int Columns;//obowiÄ…zujÄ…ca liczba kolumn dla tablicy algorytmu
    int Feeds;//iloĹ›Ä‡ pĂłl ĹĽywych
    int Iterations;//iloĹ›Ä‡ wykonanych iteracji
    bool Torus;//zmienna odpowiedzialna za zapÄ™tlanie

    QVector< QVector<bool> > Field;//wektor w wektorze, tablica dwuwymiarowa na ktĂłrej dziaĹ‚amy w algorytmie

public slots:
    void NewRows(int);//funkcja ustawiajÄ…ca nowÄ… iloĹ›Ä‡ rzÄ™dĂłw w algorytmie
    void NewColumns(int);//funkcja ustawiajÄ…ca nowÄ… iloĹ›Ä‡ kolumn w algorytmie
    void ToggleCell(int, int);//zmiana logiczna w tablicy roboczej algortymu.
    void ScreenAns();//metoda przkazujÄ…ca do mainwindow wszystkie wartoĹ›ci logiczne w tablicy roboczej
    void ClearValues();//zerowanie wartoĹ›ci pĂłl w tablicy roboczej algorytmu

signals:
    void NewRowsInf(int);//sygnaĹ‚ przekazujÄ…cy do mainwindow informacjÄ™ o zmienionej liczbie wierszy w algorytmie
    void NewColumnsInf(int);//sygnaĹ‚ przekazujÄ…cy do mainwindow informacjÄ™ o zmienionej liczbie kolumn w algorytmie
    void ActualStatusInf(int, int);//sygnaĹ‚ przekazujÄ…cy do mainwindow informacjÄ™ o iloĹ›Ä‡i ĹĽywych obiektĂłw oraz wykonanych iteracji
    void ChangeItem(int, int, bool);//sygnaĹ‚ nakazujÄ…cy zmieniÄ‡ pole w mainwindow na zgodne z wartoĹ›ciÄ… logicznÄ…
};

#endif // LCD_BOOLEAN_TABLE_H
