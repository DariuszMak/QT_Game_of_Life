#include "conwayalg.h"
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

void ConwayAlg::Step()//metoda wykonująca wszystkie niezbędne obliczenia dla pojedynczego kroku algorytmu
{
//    bool ** tmp;//utworzenie tablicy tymczasowej

//    tmp = new bool * [Rows];//ilość rzędów tablicy tymczasowej taka jak w tablicy roboczej

//    for(int row = 0; row < Rows; ++row)//przejście przez wszytkie rzędy
//    {
//        tmp[row] = new bool[Columns];//ilość kolumn tablicy tymczasowej taka jak w tablicy roboczej

//        for(int col = 0; col < Columns; ++col)//przejście przez wszystkie kolumny
//        {
//            int count = 0;//zmienna przechowująca ilość sąsiadów

//            //int tmpr_torus = 0;//zmienna pomocnicza przechowująca pozycję rzędu aktualnie sprawdzanej komórki
//            //int tmpc_torus = 0;//zmienna pomocnicza przechowująca pozycję kolumny aktualnie sprawdzanej komórki


//            for(int tmpr = row - 1; tmpr < row + 2; ++tmpr)//sąsiedzi po rzędach
//            {
//                for(int tmpc = col - 1; tmpc < col + 2; ++tmpc)//sąsiedzi po kolumnach
//                {
//                    //if( (tmpr == row) && (tmpc == col) ) continue;//jeśli jest to takie samo pole jak w przyjętych parametrach, należy wykonać następna iterację

//                    int tmpr_torus = tmpr;//zmienna pomocnicza przechowująca pozycję rzędu aktualnie sprawdzanej komórki
//                    int tmpc_torus = tmpc;//zmienna pomocnicza przechowująca pozycję kolumny aktualnie sprawdzanej komórki

//                    if(tmpr < 0)
//                    {
//                        if(Torus) tmpr_torus = Rows - 1;//jeśli pozycja rzędu jest mniejsza niż najniższa pozycja, to ustawia się największą z możliwych
//                        else continue;
//                    }
//                    if(tmpc < 0){
//                        if(Torus) tmpc_torus = Columns - 1;//jeśli pozycja kolumny jest mniejsza niż najniższa pozycja, to ustawia się największą z możliwych
//                        else continue;
//                    }
//                    if(tmpr >= Rows)
//                    {
//                        if (Torus) tmpr_torus = 0;//jeśli pozycja rzędu jest większa niż największa możliwa pozycja, to ustawia się najmniejszą z możliwych
//                        else continue;
//                    }
//                    if(tmpc >= Columns)
//                    {
//                        if (Torus) tmpc_torus = 0;//jeśli pozycja kolumny jest większa niż największa możliwa pozycja, to ustawia się najmniejszą z możliwych
//                        else continue;
//                    }
//                    //if( (tmpr < 0) || (tmpr >= Rows) ) continue;//jeśli pole mieści się poza zakresem tablicy,należy wykonać następna iterację
//                    //if( (tmpc < 0) || (tmpc >= Columns) || ( (tmpr == row) && (tmpc == col) ) ) continue;//jeśli pole mieści się poza zakresem tablicy lub jest to takie samo pole jak w przyjętych parametrach, należy wykonać następna iterację
//                    if(Field[tmpr_torus][tmpc_torus] == true) ++count;//jeśli wartość w tablicy roboczej jest prawdziwa, to należy zwiększyć ilość sąsiadów interesującej nas komórki
//                }
//            }

//            if(Field[row][col] == true) --count;//jeśli komórka była żywa, to zostaje odjęta liczba żywych komórek (bo zostałaby niepotrzebnie policzona - dana komórka nie jest sąsiednia sama z sobą)

//            //zliczona ilość sąsiadów dla pojedynczego pola w zmiennej count

//            if(Field[row][col])//jeśli interesująca nas komórka jest żywa
//            {
//                bool temp_bool_alive = false;
//                for(int t = 0; t < 9; ++t)
//                {
//                    if(SettingsWindowRules->getTableAlive(t) && count == t) temp_bool_alive = true;
//                }
//                if( temp_bool_alive ) tmp[row][col] = true;//pozostanie bez zmian, czyli będzie żywa przy liczbie sąsiadów 2 lub 3
//                else
//                {
//                    tmp[row][col] = false;//jeśli nie, to umiera
//                    --Feeds;//zmniejszona liczba żwywych elementów
//                }
//            }
//            else//jeśli interesująca nas komórka jest martwa
//            {
//                bool temp_bool_dead = false;
//                for(int t = 0; t < 9; ++t)
//                {
//                    if(SettingsWindowRules->getTableDead(t) && count == t) temp_bool_dead = true;
//                }
//                if(temp_bool_dead) {
//                    tmp[row][col] = true;//ożyje tylko, gdy ma dokładnie trzech sąsiadów
//                    ++Feeds;//zwiększona liczba żwywych elementów
//                }
//                else tmp[row][col] = false;//jeśli nie, to pozostaje bez zmian
//            }
//        }
//    }

//    //wypełniona jest już cała tablica tymczasowa

//    for(int row = 0; row < Rows; ++row)//przejście przez wszytkie rzędy
//    {
//        for(int col = 0; col < Columns; ++col)//przejście przez wszystkie kolumny
//        {
//            bool NewVal = tmp[row][col];//przypisanie nowej wartości z tymczasowej tabeli do NewVal
//            if(Field[row][col] != NewVal)//jeśli stara wartość jest różna od wartości
//            {
//                Field[row][col] = tmp[row][col];//przepisanie z tablicy tymczasowej wartości do tablicy roboczej
//                emit(ChangeItem(row, col, NewVal));//wysłanie sygnału zmiany wartości na ekranie
//            }
//        }
//    }
//    ++Iterations;//zwiększenie liczby iteracji


//    for(int row = 0; row < Rows; ++row)//przejście przez wszytkie rzędy
//    {
//        delete[] tmp[row];//usuwanie
//    }

//    delete[] tmp;


    StatusAns();//wywołanie metody przekazująca do mainwindow informację o ilości żywych pól i iteracjach

}

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
    StatusAns();//przesłanie informacji do mainwindow o ilości żwywych elementów oraz iteracji

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
    StatusAns();//metoda przekazująca do mainwindow informację o ilości żywych pól i iteracjach
    emit( ChangeItem(x, y, !set));//sygnał nakazujący zmienić pole w mainwindow na zgodne z wartością logiczną zanegowaną
}


void ConwayAlg::StatusAns()//metoda przekazująca do mainwindow informację o ilości żywych pól i iteracjach
{
    emit(ActualStatusInf(Feeds, Iterations));
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
