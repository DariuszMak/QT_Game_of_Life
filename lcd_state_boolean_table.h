#ifndef LCD_STATE_BOOLEAN_TABLE_H
#define LCD_STATE_BOOLEAN_TABLE_H

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
    int Rows;//obowiĂ„â€¦zujĂ„â€¦ca liczba wierszy dla tablicy algorytmu
    int Columns;//obowiĂ„â€¦zujĂ„â€¦ca liczba kolumn dla tablicy algorytmu
    int Feeds;//iloÄąâ€şĂ„â€ˇ pÄ‚Ĺ‚l ÄąÄ˝ywych
    int Iterations;//iloÄąâ€şĂ„â€ˇ wykonanych iteracji
    bool Torus;//zmienna odpowiedzialna za zapĂ„â„˘tlanie

    QVector< QVector<bool> > Field;//wektor w wektorze, tablica dwuwymiarowa na ktÄ‚Ĺ‚rej dziaÄąâ€šamy w algorytmie

public slots:
    void NewRows(int);//funkcja ustawiajĂ„â€¦ca nowĂ„â€¦ iloÄąâ€şĂ„â€ˇ rzĂ„â„˘dÄ‚Ĺ‚w w algorytmie
    void NewColumns(int);//funkcja ustawiajĂ„â€¦ca nowĂ„â€¦ iloÄąâ€şĂ„â€ˇ kolumn w algorytmie
    void ToggleCell(int, int);//zmiana logiczna w tablicy roboczej algortymu.
    void ScreenAns();//metoda przkazujĂ„â€¦ca do mainwindow wszystkie wartoÄąâ€şci logiczne w tablicy roboczej
    void ClearValues();//zerowanie wartoÄąâ€şci pÄ‚Ĺ‚l w tablicy roboczej algorytmu

signals:
    void NewRowsInf(int);//sygnaÄąâ€š przekazujĂ„â€¦cy do mainwindow informacjĂ„â„˘ o zmienionej liczbie wierszy w algorytmie
    void NewColumnsInf(int);//sygnaÄąâ€š przekazujĂ„â€¦cy do mainwindow informacjĂ„â„˘ o zmienionej liczbie kolumn w algorytmie
    void ActualStatusInf(int, int);//sygnaÄąâ€š przekazujĂ„â€¦cy do mainwindow informacjĂ„â„˘ o iloÄąâ€şĂ„â€ˇi ÄąÄ˝ywych obiektÄ‚Ĺ‚w oraz wykonanych iteracji
    void ChangeItem(int, int, bool);//sygnaÄąâ€š nakazujĂ„â€¦cy zmieniĂ„â€ˇ pole w mainwindow na zgodne z wartoÄąâ€şciĂ„â€¦ logicznĂ„â€¦
};

#endif // LCD_STATE_BOOLEAN_TABLE_H
