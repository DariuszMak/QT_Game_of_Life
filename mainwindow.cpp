#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "conwayalg.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)//konstruktor MainWindow
{
    Algorithm = new ConwayAlg();//utworzenie nowego obiektu z klasy ConwayAlg
    ui->setupUi(this);

    MinSizeSquare = 3;//przypisanie wartości do zmiennej przechowującej najmniejszą dopuszczalną wartość rozmiaru pojedynczego kwadracika w tabeli w pikselach

    //ustawienia komunikatu błędu zapisu
    SaveError.setWindowFlags(Qt::WindowStaysOnTopHint);//okno zawsze na wierzchu
    SaveError.setWindowTitle("Błąd zapisu!");
    SaveError.setIcon(QMessageBox::Critical);

    //ustawienia komunikatu błędu odczytu
    LoadError.setWindowFlags(Qt::WindowStaysOnTopHint);//okno zawsze na wierzchu
    LoadError.setWindowTitle("Błąd odczytu!");
    LoadError.setIcon(QMessageBox::Critical);

    //ustawienia komunikatu z zapytaniem, czy zachować niezapisane dane
    SaveWhenClosed.setWindowFlags(Qt::WindowStaysOnTopHint);//okno zawsze na wierzchu
    SaveWhenClosed.setIcon(QMessageBox::Question);
    SaveWhenClosed.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    SaveWhenClosed.setDefaultButton(QMessageBox::Yes);

    //ustawienia komunikat informujący o zapisaniu w domyślnej lokalizacji zapisu
    WillBeSaved.setWindowFlags(Qt::WindowStaysOnTopHint);//okno zawsze na wierzchu
    WillBeSaved.setWindowTitle("Nastąpi zapisanie danych...");
    WillBeSaved.setIcon(QMessageBox::Information);
    WillBeSaved.setText("Dane zostaną zapisane do pliku o ścieżce: " + UnsavePath);


    connect(ui->ColumnChanger, SIGNAL(valueChanged(int)), Algorithm, SLOT(NewColumns(int)));//jeśli wartość z pola do wprowadzania ilości kolumn zmieniła się, to należy zaktualizować ilośc kolumn na ekranie (później też w algortymie przez sygnał NewCols())
    connect(ui->RowChanger, SIGNAL(valueChanged(int)), Algorithm, SLOT(NewRows(int)));//jeśli wartość z pola do wprowadzania ilości wierszy zmieniła się, to należy zaktualizować ilośc wierszy na ekranie (później też w algortymie przez sygnał NewRows())
    connect(Algorithm, SIGNAL(NewColumnsInf(int)), this, SLOT(ColumnsChanged(int)));//utworzenie odpowiedniej wielkości kolumn tabeli na podstawie przyjętej wartości z algorytmu
    connect(Algorithm, SIGNAL(NewRowsInf(int)), this, SLOT(RowsChanged(int)));//utworzenie odpowiedniej wielkości wierszy tabeli na podstawie przyjętej wartości z algorytmu
    connect(this, SIGNAL(StatusAsk()), Algorithm, SLOT(StatusAns()));//wysłanie zapytania o ilość żywych elementów oraz wykonanych iteracji
    connect(Algorithm, SIGNAL(ActualStatusInf(int,int)), this, SLOT(StatusUpdate(int,int)));//aktualny stan ilości żywych komórek oraz iteracji przekazany do mainwindow
    connect(ui->LifeField, SIGNAL(cellEntered(int,int)), Algorithm, SLOT(ToggleCell(int,int)));//jeśli nastąpi kliknięcie na tabelę, to zostanie podjęta akcja ożywienia lub umartwienia komórek
    connect(Algorithm, SIGNAL(ChangeItem(int,int,bool)), this, SLOT(SwitchField(int,int,bool)));//jeśli zmienił się stan logiczny pla w algorytmie, trzeba to również zaznaczyć na ekranie
    connect(ui->Cleaner, SIGNAL(clicked()), this, SLOT(ClearScreen()));//jeśli kliknięto na przycisk "wyczyść", to nastąpi wyczyszczenie ekranu
    connect(this, SIGNAL(ClearAlg()), Algorithm, SLOT(ClearValues()));//czyszczenie wszystkich wartości w tablicy roboczej algorytmu
    connect(this,SIGNAL(ScreenAsk()), Algorithm, SLOT(ScreenAns()));//po zapytaniu algorytmu na ekran zostaną przesłane wszystkie wartości logiczne prawdziwe

    connect(this, SIGNAL(DoStep()), Algorithm, SLOT(Step()));//jeśli kliknie się na przycisk "krok" następuje pojedyncza iteracja algorytmu

    connect(ui->SizeFieldSlider, SIGNAL(valueChanged(int)), this, SLOT(ResizeField(int)));//gdy zostanie przesunięty suwak z wartością
    connect(this, SIGNAL(TidyUp()), this, SLOT(TidyUpScreen()));//porządkowanie właściowści programu w celu uzyskania maksymalnej spójności
    connect(ui->SetWholeScreen, SIGNAL(toggled(bool)), this, SLOT(SettingSize(bool)));//jeśli zmieniono wartość opcji dostępu do zmiany rozmiaru elementów w tabeli



    //connect(&TimerController, SIGNAL(timeout()), this, SLOT(TimerControllerTimeout()));//połączenie przekroczenia wartości timera kontrolującego, wywołuje jego slot
    connect(ui->ProjWidth, SIGNAL(valueChanged(int)), this, SLOT(TidyUpScreen()));//jeśli zmieni się wartość dostępnej przestrzeni rozdzielczości, trzeba to uwzględnić na ekranie
    connect(ui->ProjHeight, SIGNAL(valueChanged(int)), this, SLOT(TidyUpScreen()));//jeśli zmieni się wartość dostępnej przestrzeni rozdzielczości, trzeba to uwzględnić na ekranie
    connect(ui->MaxSize, SIGNAL(toggled(bool)), this, SLOT(TidyUpScreen()));//gdy zostanie zaznaczona opcja maksymalnego rozmiaru, trzeba to uwzględnić na ekranie

    connect(Algorithm, SIGNAL(TorusStateInf(bool)), this, SLOT(TorusChange(bool)));//gdy zostanie zaznaczona opcja "zapętlanie", wywoła się funkcja w algorytmie zminiająca zmienną logiczną

    srand(QTime::currentTime().msecsTo(QTime(0, 0, 0, 0)));//konfiguracja losowości

    SetInitialValues();//ustawienie wartości początkowych

    Changed = false;//zmienna przechowująca informację, czy coś się na ekranie zmieniło
//    setWindowTitle(TitleProj);// ustawienie początkowego tytułu programu
    //Load();//otwarcie domyślnej ścieżki pliku
}

MainWindow::~MainWindow()//destruktor okna MainWindow
{
    delete ui;
}



//********Prywatne metody*********


void MainWindow::resizeEvent(QResizeEvent *event)
{
    event->accept();
}

void MainWindow::closeEvent(QCloseEvent *event)//specjalna metoda do przedefiniwania działań przy zamykaniu programu
{
    event->accept();
    emit CloseOtherWindows();
}

void MainWindow::SetInitialValues()//metoda ustawiająca wszystkie niezbędne wartości początkowe (rozmiar, ilość kolumn i wierszy na interfejsie, domyślne kolory)
{
    AliveColor = QColor("yellow");//przypisanie kwadracikom żywym koloru żółtego
    DeadColor = QColor("black");//przypisanie kwadracikom martwym koloru czarnego

    ui->ProjWidth->setValue(1280);
    ui->ProjHeight->setValue(640);
    ui->ColumnChanger->setValue(128);
    ui->RowChanger->setValue(64);
}


//********Sloty*********


/*void MainWindow::TimerControllerTimeout()//akcja reagująca na przepełnienie się timera kontrolującego przebieg animacji
{
    //++MilisecondsPerFrame;
}*/


void MainWindow::SettingSize(bool val)//slot włączający lub wyłączający dostęp do elementów zmiany rozmiaru
{
    ui->ColumnChanger->setEnabled(val);//ilość kolumn aktywna/nieaktywna
    ui->RowChanger->setEnabled(val);//ilość wierszy aktywna/nieaktywna
    ui->SizeFieldLcd->setEnabled(val);//wyświetlacz z rozmiarem aktywny/nieaktywny
    if(ui->MaxSize->checkState())//jeśli utrzymywanie maksymalnego rozmiaru jest aktywne, należy
    {
        ui->SizeFieldSlider->setEnabled(false);//wyłączenie aktywności suwaka rozmiaru
    }
    else ui->SizeFieldSlider->setEnabled(val);//suwak rozmiaru aktywny/nieaktywny
}

void MainWindow::TidyUpScreen()//funkcja dobierająca właściwości w oknie tak, aby kompozycja była spójna
{
    int Size;//zmienna pomocnicza wykorzystywana wielokrotnie w tej funkcji

    int MinSizeColumn;//wartość najmniejszego rozmiaru kwadracika dla kolumn

    int MinSizeRow;//wartość najmniejszego rozmiaru kwadracika dla wierszy

    MinSizeColumn = ui->ProjWidth->value() / ui->ColumnChanger->value();//obliczenie wartości najmniejszego rozmiaru kwadracika dla kolumn
    MinSizeRow = ui->ProjHeight->value() / ui->RowChanger->value();//obliczenie wartości najmniejszego rozmiaru kwadracika dla wierszy

    if(MinSizeColumn < MinSizeRow) Size = MinSizeColumn;//brana jest pod uwagę najmniejsza wartość
    else Size = MinSizeRow;//brana jest pod uwagę najmniejsza wartość


    if(Size < MinSizeSquare) Size = MinSizeSquare;//rozmiar MinSizeSquare jest najmniejszym dopuszczalnym rozmiarem kwadracikiem

    ui->SizeFieldSlider->setMaximum(Size);//ustawienie wartości maksymalnej suwaka z rozmiarem


    if(ui->MaxSize->checkState())//jeśli zaznaczona jest opcja dopasowania największego rozmiaru
    {
         ui->SizeFieldSlider->setValue(Size);//ustawiana jest taka właśnie wartość
    }

    Size = ui->SizeFieldLcd->value();//wartość w wyświetlaczu rozmiaru (ta, która obowiązuje, może się nie zmieniać, gdzy nie jest zaznaczona opcja dopasowywania rozmiaru)

    int tempWidth = Size * ui->ColumnChanger->value();//tymczasowa obliczona szerokość tabeli z polami
    int tempHeight = Size * ui->RowChanger->value();//tymczasowa obliczona wysokość tabeli z polami


    //Uwaga!!! w poniższym skalowaniu niezbędne jest ustawienie zarówno wartości minimanych, jak i maksymalnych (funkcja resize nie działa zgodnie z oczekiwaniami)

    ui->Page->setMinimumSize(ui->ProjWidth->value(), ui->ProjHeight->value());//skalowanie obszaru z ramką jako pole dostępne w pikselach - wartości minimalne
    ui->Page->setMaximumSize(ui->ProjWidth->value(), ui->ProjHeight->value());//skalowanie obszaru z ramką jako pole dostępne w pikselach - wartości maksymalne
    ui->Page->setMinimumHeight(ui->ProjHeight->value());
    ui->Page->setMinimumWidth(ui->ProjWidth->value());
    ui->Page->setMaximumHeight(ui->ProjHeight->value());
    ui->Page->setMaximumWidth(ui->ProjWidth->value());

    if(tempWidth < 300) tempWidth = 300;


    ui->LifeField->setMinimumSize(tempWidth, tempHeight);//skalowanie tabeli - wartości minimalne
    ui->LifeField->setMaximumSize(tempWidth, tempHeight);//skalowanie tabeli - wartości maksymalne

    ui->LifeField->move((ui->Page->width() - tempWidth)/2, (ui->Page->height() - tempHeight)/2);//obliczana na bieżąco pozycja tabeli w stackedboxie

    emit(ui->SetWholeScreen->toggled(ui->SetWholeScreen->checkState()));//uaktualnienie panelu bocznego do zmian parametrów rozmiaru tabeli i rozmiaru w pikselach, aby suwak był aktywny, bądź nie
}

void MainWindow::ResizeField(int NewSize)//funkcja przyjmująca rozmiar pojedynczego pola na ekranie skalująca całą tabelę
{
    ui->SizeFieldLcd->display(NewSize);//wprowadzenie do wyświetlacza z rozmiarem wartości

    for(int i = 0; i < ui->LifeField->rowCount(); ++i)//przez wszystkie wiersze
    {
        if(ui->LifeField->rowHeight(i) != NewSize) ui->LifeField->setRowHeight(i, ui->SizeFieldLcd->value());//aktualizowany rozmiar mowo tworzonych wierszy (jeśli inny od starego)
    }

    for(int i = 0; i < ui->LifeField->columnCount(); ++i)//przez wszystkie kolumny
    {
        if(ui->LifeField->columnWidth(i) != NewSize) ui->LifeField->setColumnWidth(i, ui->SizeFieldLcd->value());//aktualizowany rozmiar mowo tworzonych kolumn (jeśli inny od starego)
    }
    emit (TidyUp());//sygnał porządkujący właściowści ona programu w celu uzyskania maksymalnej spójności
}

void MainWindow::ClearScreen()//funkcja czyszcząca ekran i dane w algorytmie i na ekranie jednocześnie zatrzymuje symulację, ponieważ nie ma żywych pól w tabeli
{
    emit(ClearAlg());//wyzerowanie stanu całej tablicy w algorytmie
    //UpadeScreen();//aktualizacja danych na ekranie
    //RowsChanged(0);//wyskalowanie tabeli do rozmiaru 0
    //ColumnsChanged(0);//wyskalowanie tabeli do rozmiaru 0
    //ColumnsChanged(ui->ColumnChanger->value());//wyskalowanie tabeli do poprzedniego rozmiaru ze skasowanymi wartościami itemów (kolorów tła)
    //RowsChanged(ui->RowChanger->value());//wyskalowanie tabeli do poprzedniego rozmiaru ze skasowanymi wartościami itemów (kolorów tła)
    emit(ScreenAsk());//sygnał aktualizacji stanu wartośi logicznych umieszczonych w tabeli roboczej na ekranie
    //emit(StatusAsk());//aktualizacja liczby żywych pól i iteracji
}

/*void MainWindow::UpadeScreen()//funkcja aktualizująca stan ekranu z algorytmem
{
    emit(ScreenAsk());
}*/

void MainWindow::SwitchField(int x, int y, bool value)//funkcja ustawiająca w tabeli odpowiedni kwadracik w zależności od przyjętej wartości logicznej
{
    QTableWidgetItem *item = ui->LifeField->item(x, y);//przypisanie do wskaźnika "item" adresu pola z tabeli

    if(item == 0)//jeśli nie ma jeszcze itema, to należy go przypisać
    {
        item = new QTableWidgetItem;//utworzenie nowego elementu item i przypisanie jego adresu do wcześniej utworzonego wskaźnika
        ui->LifeField->setItem(x, y, item);//umieszczenie tego elementu w tabeli
    }

    if(value)
    {

        if(item->data(Qt::UserRole) != true)//jeśli wartość logiczna w itemie jest inna od prawdziwej (może nie być żadnej)
        {
            item->setData(Qt::UserRole, QVariant(true));//ustawienie wartości true
        }

        if(item->background() != AliveColor)//jeśli kolor się zmienił
        {
            item->setBackground(AliveColor);//zmiana koloru tła
        }
    }
    else
    {
        if(item->data(Qt::UserRole) != false)//jeśli wartość logiczna w itemie jest inna od fałszywej (może nie być żadnej) lub kolor się zmienił
        {
            item->setData(Qt::UserRole, QVariant(false));//ustawienie wartości false
        }

        if(item->background() != DeadColor)//jeśli kolor się zmienił
        {
            item->setBackground(DeadColor);//zmiana koloru tła item
        }
    }
}

void MainWindow::RowsChanged(int newRow)//utworzenie odpowiedniej wielkości wierszy tabeli na podstawie przyjętej wartości
{
    if(ui->LifeField->rowCount() == newRow) return;//gdy faktyczna ilość wierszy w tabeli jest równa z ilością zadaną, należy wyjść z metody
    int oldRows = ui->LifeField->rowCount();//przypisanie do oldRows wartości obecnej ilości wierszy w tabeli

    ui->LifeField->setRowCount(newRow);//ustawienie ilości wierszy w tabeli zgodnie z ilością wprowadzoną do funcji

    //Gdy wierszy jest więcej
    for(int i = oldRows; i < newRow; ++i)//od starej (mniejszej) ilości wierszy do nowo wprowadzonej ilości wierszy
    {
        for(int j = 0; j < ui->LifeField->columnCount(); ++j)//dla każdego wiersza poruszanie się po kolumnach, aby wypełnić brakujące pola
        {
            SwitchField(i, j, false);//domyślne ustawienie jako itema na kolor wyłączonego itema
        }
        ui->LifeField->setRowHeight(i, ui->SizeFieldLcd->value());//jeśli było więcej wierszy, to te powstałe "zbyt szerokie" zostaną ustawione do właśwej szerokości
    }
    ui->ProjHeight->setMinimum(MinSizeSquare * ui->RowChanger->value());//ustawienie minimalnej wartości do rozdzielczości
    emit (TidyUp());//sygnał porządkujący właściowści ona programu w celu uzyskania maksymalnej spójności
    emit StatusAsk();//zapytanie algorytmu o ilość żywych kokórek i iteracji
}

void MainWindow::ColumnsChanged(int newCol)//utworzenie odpowiedniej wielkości kolumn tabeli na podstawie przyjętej wartości
{
    if(ui->LifeField->columnCount() == newCol) return;//gdy faktyczna ilość kolumn w tabeli jest równa z ilością zadaną, należy wyjść z metody
    int oldColumns = ui->LifeField->columnCount();//przypisanie do oldColumns wartości obecnej ilości kolumn w tabeli

    ui->LifeField->setColumnCount(newCol);//ustawienie ilości kolumn w tabeli zgodnie z ilością wprowadzoną do funcji

    //Gdy kolumn jest więcej
    for(int i = oldColumns; i < newCol; ++i)//od starej (mniejszej) ilości kolumn do nowo wprowadzonej ilości kolumn
    {
        for(int j = 0; j < ui->LifeField->rowCount(); ++j)//dla każdej kolumny poruszanie się po wierszach, aby wypełnić brakujące pola
        {
            SwitchField(j, i, false);//domyślne ustawienie jako itema na kolor wyłączonego itema
        }
        ui->LifeField->setColumnWidth(i, ui->SizeFieldLcd->value());//jeśli było więcej kolumn, to te powstałe "zbyt szerokie" zostaną ustawione do właśwej szerokości
    }    
    ui->ProjWidth->setMinimum(MinSizeSquare * ui->ColumnChanger->value());//ustawienie minimalnej wartości do rozdzielczości
    emit (TidyUp());//sygnał porządkujący właściowści ona programu w celu uzyskania maksymalnej spójności
    emit StatusAsk();//zapytanie algorytmu o ilość żywych kokórek i iteracji
}


void MainWindow::on_actionOd_wie_triggered()
{
    TidyUp();
    emit(ScreenAsk());
}

void MainWindow::on_actionKolor_ywych_kom_rek_triggered()
{
    QColor TempAliveColor = ChooseAliveColor.getColor(AliveColor, 0, "Wybierz kolor dla żywych komórek");
    if(TempAliveColor != "" && TempAliveColor != AliveColor)//jeśli kolor został wybrany i jest różny od tego w globalnej zmiennej, należy go ustawić
    {
        AliveColor = TempAliveColor;//ualtualnianie koloru w zmiennej globalnej
        emit(ScreenAsk());//uaktualnianie koloru na ekranie
    }
}

void MainWindow::on_actionKo_lor_martwych_kom_rek_triggered()
{
    QColor TempDeadColor = ChooseDeadColor.getColor(DeadColor, 0, "Wybierz kolor dla martwych komórek");
    if(TempDeadColor != "" && TempDeadColor != DeadColor)//jeśli kolor został wybrany i jest różny od tego w globalnej zmiennej, należy go ustawić
    {
        DeadColor = TempDeadColor;//ualtualnianie koloru w zmiennej globalnej
        emit(ScreenAsk());//uaktualnianie koloru na ekranie
    }
}
