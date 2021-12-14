#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)//konstruktor MainWindow
{
    Table_widget_cell_size = 1;

    NumberOfColumns = 128;
    NumberOfRows = 64;

    ui->setupUi(this);

    MinSizeSquare = 1;//przypisanie wartości do zmiennej przechowującej najmniejszą dopuszczalną wartość rozmiaru pojedynczego kwadracika w tabeli w pikselach

    connect(ui->Cleaner, SIGNAL(clicked()), this, SLOT(ClearScreen()));//jeśli kliknięto na przycisk "wyczyść", to nastąpi wyczyszczenie ekranu


//    connect(, SIGNAL(), ,SLOT());
//    connect(this, SIGNAL(LCDBufferModified()), this, SLOT());

    connect(this, SIGNAL(Refresh_fields_state()), this, SLOT(TidyUpScreen()));//porządkowanie właściowści programu w celu uzyskania maksymalnej spójności
    srand(QTime::currentTime().msecsTo(QTime(0, 0, 0, 0)));//konfiguracja losowości
    SetInitialValues();//ustawienie wartości początkowych
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
    QFont font = ui->LifeField->font();
    font.setPointSize(1);
    ui->LifeField->setFont(font);

    this->setMinimumSize(QSize(1800, 700));


    AliveColor = QColor("yellow");//przypisanie kwadracikom żywym koloru żółtego
    DeadColor = QColor("black");//przypisanie kwadracikom martwym koloru czarnego

    this->RowsChanged(this->NumberOfRows);
    this->ColumnsChanged(this->NumberOfColumns);

}


//********Sloty*********


void MainWindow::printBuffer(uint8_t * const displayBuffer)
{
    this->DisplayAccordingToBuffer(displayBuffer);
}


void MainWindow::DisplayAccordingToBuffer(uint8_t * const displayBuffer)
{
    std::printf("DisplayAccordingToBuffer invoked");
}


void MainWindow::TidyUpScreen()
{
    std::printf("Tidy up screen invoked. \n");
}

void MainWindow::ResizeField(int NewSize)//funkcja przyjmująca rozmiar pojedynczego pola na ekranie skalująca całą tabelę
{
    for(int i = 0; i < ui->LifeField->rowCount(); ++i)//przez wszystkie wiersze
    {
        if(ui->LifeField->rowHeight(i) != NewSize) ui->LifeField->setRowHeight(i, Table_widget_cell_size);//aktualizowany rozmiar mowo tworzonych wierszy (jeśli inny od starego)
    }

    for(int i = 0; i < ui->LifeField->columnCount(); ++i)//przez wszystkie kolumny
    {
        if(ui->LifeField->columnWidth(i) != NewSize) ui->LifeField->setColumnWidth(i, Table_widget_cell_size);//aktualizowany rozmiar mowo tworzonych kolumn (jeśli inny od starego)
    }
    emit(Refresh_fields_state());//sygnał porządkujący właściowści ona programu w celu uzyskania maksymalnej spójności
}

void MainWindow::ClearScreen()//funkcja czyszcząca ekran i dane w algorytmie i na ekranie jednocześnie zatrzymuje symulację, ponieważ nie ma żywych pól w tabeli
{
    emit(ClearAlg());//wyzerowanie stanu całej tablicy w algorytmie
    emit(ScreenAsk());//sygnał aktualizacji stanu wartośi logicznych umieszczonych w tabeli roboczej na ekranie
}

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
        ui->LifeField->setRowHeight(i, Table_widget_cell_size);//jeśli było więcej wierszy, to te powstałe "zbyt szerokie" zostaną ustawione do właśwej szerokości
    }
    emit(Refresh_fields_state());//sygnał porządkujący właściowści ona programu w celu uzyskania maksymalnej spójności
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
        ui->LifeField->setColumnWidth(i, Table_widget_cell_size);//jeśli było więcej kolumn, to te powstałe "zbyt szerokie" zostaną ustawione do właśwej szerokości
    }    
    emit (Refresh_fields_state());//sygnał porządkujący właściowści programu w celu uzyskania maksymalnej spójności
    emit StatusAsk();//zapytanie algorytmu o ilość żywych kokórek i iteracji
}


void MainWindow::on_actionOd_wie_triggered()
{
    Refresh_fields_state();
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
