#include "lcd_boolean_table.h"
#include <iostream>


ConwayAlg::ConwayAlg()//konstruktor
{
    Rows = 0;//obowiązująca liczba wierszy dla tablicy algorytmu
    Columns = 0;//obowiązująca liczba kolumn dla tablicy algorytmu
    Feeds = 0;//ilość pól żywych
    Iterations = 0;//ilość wykonanych iteracji
    Torus = false;//zmienna odpowiedzialna za zapętlanie
    //connect(parent,)
}

//*******Sloty*********


void ConwayAlg::ClearValues()//zerowanie wartości pól w tablicy roboczej algorytmu
{
    for (int i = 0; i < Rows; ++i)
    {
        for(int j = 0; j < Columns; ++j)//przejście przez całą tablicę roboczą
        {
            Field[i][j] = false;//przypisanie każdemu elementowi wartości "false"
        }
    }
    Feeds = 0;//ilość pól żywych
    Iterations = 0;//ilość wykonanych iteracji
}


void ConwayAlg::ScreenAns()//metoda przkazująca do mainwindow wszystkie wartości logiczne w tablicy roboczej
{
    for (int i = 0; i < Rows; ++i)
    {
        for(int j = 0; j < Columns; ++j)//przejście przez całą tablicę
        {
            emit(ChangeItem(i, j, Field[i][j]));//przesłanie wszystkich wartości logicznych algorytmu
        }
    }
}

void ConwayAlg::ToggleCell(int x, int y)//zmiana logiczna w tablicy roboczej algortymu.
{
    bool set = Field[x][y];//przypisanie faktycznej wartości logicznej

    if(set)
    {
       Field[x][y] = false;//zmiana tej wartości na przeciwną
       --Feeds;//o jedno żywe pole mniej
    }
    else
    {
        Field[x][y] = true;//zmiana tej wartości na przeciwną
        ++Feeds;//o jedno żywe pole więcej
    }
    emit( ChangeItem(x, y, !set));//sygnał nakazujący zmienić pole w mainwindow na zgodne z wartością logiczną zanegowaną
}



void ConwayAlg::NewRows(int newRow)//funkcja ustawiająca nową ilość rzędów w algorytmie
{
    //jeśli nowa liczba wierszy jest mniejsza, trzeba zliczyć ilość utraconych żywych elementów
    for(int i = newRow; i < Rows; ++i)//wiersze od mniejszej zadanej ilości do starej ilości (większej)
    {
        for(int j = 0; j < Columns; ++j)//wszystkie kolumny istniejące w tabeli (ich wartość się nie zmieniła)
        {
            if(Field[i][j]) --Feeds;//zmniejszenie ilości żywych elementów, jeśli napotkano na takie
        }
    }

    Field.resize(newRow);//aktualizacja liczby wierszy

    for(int i = Rows; i < newRow; ++i)//jeśli nowa liczba wierszy jest większa
    {
        Field[i].resize(Columns); //aktualizacja liczby wierszy w algorytmie
    }

    Rows = newRow; //zapis nowej wartości ilości wierszy do swojego pola

    emit(NewRowsInf(newRow));//emisja sygnału do mainwindow informująca o zmianie rozmiaru obszaru działania (kolumny)
}

void ConwayAlg::NewColumns(int newCol)//funkcja ustawiająca nową ilość kolumn w algorytmie
{
    //jeśli nowa liczba kolumn jest mniejsza, trzeba zliczyć ilość utraconych żywych elementów
    for(int i = newCol; i < Columns; ++i)//kolumny od mniejszej zadanej ilości do starej ilości (większej)
    {
        for(int j = 0; j < Rows; ++j)//wszystkie wiersze (ich wartość się nie zmieniła)
        {
            if(Field[j][i]) --Feeds;//zmniejszenie ilości żywych elementów, jeśli napotkano na takie
        }
    }

    for(int i = 0; i < Rows; ++i)//dla każdego wiersza aktualizacja liczby kolumn
    {
        Field[i].resize(newCol); //każdy wiersz jest aktualizowany o liczbę przyjętych kolumn
    }

    Columns = newCol; //zapis nowej wartości ilości kolumn do swojego pola
    emit(NewColumnsInf(newCol));//emisja sygnału do mainwindow informująca o zmianie rozmiaru obszaru działania (wiersze)
}
