#include "lcd_state_boolean_table.h"
#include <iostream>


LCD_state_boolean_table::LCD_state_boolean_table()//konstruktor
{
    Rows = 0;//obowiązująca liczba wierszy dla tablicy algorytmu
    Columns = 0;//obowiązująca liczba kolumn dla tablicy algorytmu
}


void LCD_state_boolean_table::ClearValues()//zerowanie wartości pól w tablicy roboczej algorytmu
{
    for (int i = 0; i < Rows; ++i)
    {
        for(int j = 0; j < Columns; ++j)//przejście przez całą tablicę roboczą
        {
            Field[i][j] = false;//przypisanie każdemu elementowi wartości "false"
        }
    }
}


void LCD_state_boolean_table::ScreenAns()//metoda przkazująca do mainwindow wszystkie wartości logiczne w tablicy roboczej
{
    for (int i = 0; i < Rows; ++i)
    {
        for(int j = 0; j < Columns; ++j)//przejście przez całą tablicę
        {
            emit(ChangeItem(i, j, Field[i][j]));//przesłanie wszystkich wartości logicznych algorytmu
        }
    }
}


void LCD_state_boolean_table::NewRows(int newRow)//funkcja ustawiająca nową ilość rzędów w algorytmie
{
    Field.resize(newRow);//aktualizacja liczby wierszy

    for(int i = Rows; i < newRow; ++i)//jeśli nowa liczba wierszy jest większa
    {
        Field[i].resize(Columns); //aktualizacja liczby wierszy w algorytmie
    }

    Rows = newRow; //zapis nowej wartości ilości wierszy do swojego pola
    emit(NewRowsInf(newRow));//emisja sygnału do mainwindow informująca o zmianie rozmiaru obszaru działania (kolumny)
}


void LCD_state_boolean_table::NewColumns(int newCol)//funkcja ustawiająca nową ilość kolumn w algorytmie
{
    for(int i = 0; i < Rows; ++i)//dla każdego wiersza aktualizacja liczby kolumn
    {
        Field[i].resize(newCol); //każdy wiersz jest aktualizowany o liczbę przyjętych kolumn
    }

    Columns = newCol; //zapis nowej wartości ilości kolumn do swojego pola
    emit(NewColumnsInf(newCol));//emisja sygnału do mainwindow informująca o zmianie rozmiaru obszaru działania (wiersze)
}
