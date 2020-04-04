#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)//konstruktor MainWindow
{
    HelpWindow = new Help(this);//utworzenie elementu klasy help (okna z pomocą), parent jako mainwindow

    SettingsWindow = new SettingWindow(this);//utworzenie elementu klasy "SettingWindow" (okna z ustawieniami reguł algorytmu), parentem jest mainwindow (to okno)

    Algorithm = new ConwayAlg(SettingsWindow);//utworzenie nowego obiektu z klasy ConwayAlg

    ui->setupUi(this);
    Timer.stop();//zatrzymanie timera
    Timer.setTimerType(Qt::PreciseTimer);
    Timer.setSingleShot(true);//jednorazowy sygnał przepełnienia
//    TimerController.stop();//zatrzymanie timera kontrolnego
//    TimerController.setInterval(1);//ustawienie interwału na jedną milisekundę
//    TimerController.setTimerType(Qt::PreciseTimer);
//    TimerController.setSingleShot(false);
//    MilisecondsPerFrame = 0;
    IsRunning = false;//zmienna wyznaczająca, czy symulacja trwa, czy nie
    MinSizeSquare = 3;//przypisanie wartości do zmiennej przechowującej najmniejszą dopuszczalną wartość rozmiaru pojedynczego kwadracika w tabeli w pikselach

    TitleProj = "Gra w życie - Dariusz Makarewicz";
    UnsavePath = QDir::currentPath() + "/UNSAVED.life";//przyporządkowanie ścieżki zapisywania niezapisanego projektu (tylko tutaj jest to ustalone)
    MainPath = "";//główna ścieżka dostępu do pliku przechowywana w programie

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

    connect(ui->Move, SIGNAL(clicked()), this, SLOT(WindowStep()));//jeśli kliknie się na przycisk "krok" następuje weryfikacja, czy symulacja jest aktywna, jeśli tak, to później nastąpi naciśnięci przycisku "symulacja"
    connect(this, SIGNAL(DoStep()), Algorithm, SLOT(Step()));//jeśli kliknie się na przycisk "krok" następuje pojedyncza iteracja algorytmu

    connect(ui->SizeFieldSlider, SIGNAL(valueChanged(int)), this, SLOT(ResizeField(int)));//gdy zostanie przesunięty suwak z wartością
    connect(this, SIGNAL(TidyUp()), this, SLOT(TidyUpScreen()));//porządkowanie właściowści programu w celu uzyskania maksymalnej spójności
    connect(ui->SetWholeScreen, SIGNAL(toggled(bool)), this, SLOT(SettingSize(bool)));//jeśli zmieniono wartość opcji dostępu do zmiany rozmiaru elementów w tabeli
    connect(ui->Generator, SIGNAL(clicked()), this, SLOT(Generate()));//gdy został naciśnięty przycisk generowania, wywoła się funkcja generująca elementy na ekranie
    connect(ui->Starter, SIGNAL(clicked()), this, SLOT(SimulationToggle()));//gdy został naciśnięty przycisk "symulacja", rozpoczyna się symulacja
    connect(ui->MultiStarter, SIGNAL(clicked()), this, SLOT(MultiStep()));//gdy zosatał naciśnięty przycisk "wiele kroków", wywołany zostaje odpowiedni slot
    connect(&Timer, SIGNAL(timeout()), this, SLOT(SimulationStep()));//połączenie przekroczenia wartości timera wywołuje następny krok
    //connect(&TimerController, SIGNAL(timeout()), this, SLOT(TimerControllerTimeout()));//połączenie przekroczenia wartości timera kontrolującego, wywołuje jego slot
    connect(ui->SpeedDial, SIGNAL(valueChanged(int)), ui->SpeedLcd, SLOT(display(int)));//jeśli wartość pokrętła zosatnie zmieniona, wyświetli się ona na wyświetlaczu
    connect(ui->ProjWidth, SIGNAL(valueChanged(int)), this, SLOT(TidyUpScreen()));//jeśli zmieni się wartość dostępnej przestrzeni rozdzielczości, trzeba to uwzględnić na ekranie
    connect(ui->ProjHeight, SIGNAL(valueChanged(int)), this, SLOT(TidyUpScreen()));//jeśli zmieni się wartość dostępnej przestrzeni rozdzielczości, trzeba to uwzględnić na ekranie
    connect(ui->MaxSize, SIGNAL(toggled(bool)), this, SLOT(TidyUpScreen()));//gdy zostanie zaznaczona opcja maksymalnego rozmiaru, trzeba to uwzględnić na ekranie

    connect(ui->Torus, SIGNAL(toggled(bool)), Algorithm, SLOT(TorusState(bool)));//gdy zostanie zaznaczona opcja "zapętlanie", wywoła się funkcja w algorytmie zminiająca zmienną logiczną
    connect(Algorithm, SIGNAL(TorusStateInf(bool)), this, SLOT(TorusChange(bool)));//gdy zostanie zaznaczona opcja "zapętlanie", wywoła się funkcja w algorytmie zminiająca zmienną logiczną

    qsrand(QTime::currentTime().msecsTo(QTime(0, 0, 0, 0)));//konfiguracja losowości

    SetInitialValues();//ustawienie wartości początkowych

    Changed = false;//zmienna przechowująca informację, czy coś się na ekranie zmieniło
    setWindowTitle(TitleProj);// ustawienie początkowego tytułu programu
    //Load();//otwarcie domyślnej ścieżki pliku
}

MainWindow::~MainWindow()//destruktor okna MainWindow
{
    SaveUnsaved();//wywołanie metody pytającej, czy zapisać niezapisany plik
    delete ui;
    delete Algorithm;
    delete HelpWindow;
    delete SettingsWindow;
}



//********Prywatne metody*********



void MainWindow::closeEvent(QCloseEvent *event)//specjalna metoda do przedefiniwania działań przy zamykaniu programu
{
    QMessageBox msgBox;
    msgBox.setText("Czy napewno chcesz wyjść z programu?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    int result = msgBox.exec();
    switch (result) {
        case QMessageBox::Yes:
            event->accept();
            emit CloseOtherWindows();
            break;
        case QMessageBox::No:
            event->ignore();
            break;
    }
}

void MainWindow::SetInitialValues()//metoda ustawiająca wszystkie niezbędne wartości początkowe (rozmiar, ilość kolumn i wierszy na interfejsie, domyślne kolory)
{
    emit(ui->Torus->toggled(ui->Torus->checkState()));//emisja sygnału uaktualnienia stanu zapętlania lub nie
    emit(ui->RowChanger->valueChanged(ui->RowChanger->value()));//wartości początkowe wierszy
    emit(ui->ColumnChanger->valueChanged(ui->ColumnChanger->value()));//wartości początkowe ilości kolumn
    emit(ui->SizeFieldSlider->valueChanged(ui->SizeFieldSlider->value()));//uaktualnienie wartości początkowej suwaka

    AliveColor = QColor("yellow");//przypisanie kwadracikom żywym koloru żółtego
    DeadColor = QColor("black");//przypisanie kwadracikom martwym koloru czarnego

    emit(ui->SetWholeScreen->toggled(ui->SetWholeScreen->checkState()));//emisja sygnału w celu uaktualnienia stanu określanego przez checkboxa
    emit(ui->SpeedDial->valueChanged(ui->SpeedDial->value()));//uaktualnienie wartości początkowej wyświelacza prękości w pokrętle
    emit(ui->ProjHeight->valueChanged(0));//uaktualnienie wartości początkowej wysokości pola w pikselach
    emit(ui->ProjWidth->valueChanged(0));//uaktualnienie wartości początkowej szerokości pola w pikselach


    ui->NumberOfSteps->setValue(1000);
    ui->ProjWidth->setValue(900);
    ui->ProjHeight->setValue(450);
    ui->ColumnChanger->setValue(100);
    ui->RowChanger->setValue(50);
    ui->Torus->setChecked(true);

    bool tableAliveTemp[9] = {false, false, true, true, false, false, false, false, false};//początkowe ustawienia dla reguł algorytmu dla żywych komórek
    bool tableDeadTemp[9] = {false, false, false, true, false, false, false, false, false};//początkowe ustawienia dla reguł algorytmu dla martwych komórek

    for( int i = 0; i < 9; ++i )
    {
        SettingsWindow->setTableAlive( i, tableAliveTemp[i] );
        SettingsWindow->setTableDead( i, tableDeadTemp[i] );
    }

    emit(ScreenAsk());//aktualizacja wszystkich stanów kwadracików w tabeli z algorytmem
}

void MainWindow::SaveUnsaved()//metoda pytająca, czy zapisać niezapisany plik
{
    if(Changed)//zapisanie niezapisanego projektu, gdy nastąpiła zmiana w stosunku do oryginału
    {
        if(MainPath == "")//jeśli nie wybrano żadnego pliku
        {
            WillBeSaved.exec();//komunikat informujący o zapisaniu w domyślnej lokalizacji zapisu
            MainPath = UnsavePath;//ustawienie (tylko chwilowo) głównej ścieżki jako domyślnej lokalizacji
            char *path = UnsavePath.toLocal8Bit().data();//konwersja ścieżki do tablicy typu char (wskaźnik pierwszego elementu)
            SaveScreen(path);
        }

        while(Changed)//dopóki nie zostane zapisany poprawnie plik lub nie nastąpi anulowanie operacji
        {
            QString questionWindowText;//string z różnymi wersjami odpowiedzi do zapytań

            if(MainPath == "")//jeśli ścieżka jest pusta, to
            {
                questionWindowText = "Dane przepadną. Czy chcesz je zachować?";
            }
            else
            {
                questionWindowText = "Zachować zmiany w pliku: " + MainPath + " ?";
            }

            //wyświetlenie okna dialogowego z zapytaniami
            QMessageBox::StandardButton Reply;//w zmiennej Reply przechowywana jest odpowiedź z okna dialogowego
            Reply = SaveWhenClosed.question(this, "Zakończenie programu", questionWindowText);
            if (Reply == QMessageBox::Yes)//jeśli wybrano "tak", to nastąpi zapis
            {
                Save();
            }
            else if(Reply == QMessageBox::No)//jeśli wybrano "nie", to nakończy się pytanie o ścieżkę do zapisania
            {
                Changed = false;
            }
        }
    }
}

void MainWindow::Load()//reagująca na przycisk "wczytaj"
{
    if(MainPath == "")
    {
        LoadAs();
    }
    else
    {
        char *path = MainPath.toLocal8Bit().data();
        LoadScreen(path);//wysłanie ścieżki do pobrania
    }
}

void MainWindow::LoadAs()//metoda ragująca na przycik wczytaj jako
{
    QString TempPath;//tymczasowa pomocnicza ścieżka
    TempPath = QFileDialog::getOpenFileName(this, tr("Wybierz plik do wczytania"),"./","Pliki życia (*.life);; Wszystkie (*)");//podanie do zmiennej typu Qstring ścieżki z okna dialogowego
    if(TempPath != "")// jeśli podana ścieżka jest różna od pustej
    {
        MainPath = TempPath;//zapamiętanie głównej ścieżki
        char *path = MainPath.toLocal8Bit().data();//konwersja ścieżki do tablicy typu char (wskaźnik pierwszego elementu)
        LoadScreen(path);//wysłanie ścieżki
    }
}

void MainWindow::LoadScreen(char * path)//metoda wczytująca z pliku całą zawartość wartości logicznych zawartych w tabeli
{
    long int temp_val;//pomocnicza zmienna tymczasowa przechowująca wczytane wartości

    ifstream plik(path);//otwarcie pliku o podanej ścieżce

    if( plik.good() == true )//jeśli udało się otworzyć plik, to
    {
        plik >> temp_val;

        ui->Torus->setChecked(bool(temp_val));//ustawienie stanu zapętlenia


        for( int i = 0; i < 9; ++i )
        {
            plik >> temp_val;

            SettingsWindow->setTableAlive(i, bool(temp_val));
        }

        for( int i = 0; i < 9; ++i )
        {
            plik >> temp_val;

            SettingsWindow->setTableDead(i, bool(temp_val));
        }

        plik >> temp_val;

        ui->RowChanger->setValue(temp_val);//wartości początkowe ilości kolumn

        plik >> temp_val;

        ui->ColumnChanger->setValue(temp_val);//wartości początkowe wierszy

        plik >> temp_val;

        ui->SizeFieldSlider->setValue(temp_val);//rozmiar pola tabeli

        plik >> temp_val;

        AliveColor.setRgb(temp_val);//kolor żywych komórek

        plik >> temp_val;

        DeadColor.setRgb(temp_val);//kolor martwych komórek

        emit(ui->Cleaner->clicked());

        disconnect(Algorithm, SIGNAL(ChangeItem(int,int,bool)), this, SLOT(SwitchField(int,int,bool)));//jeśli zmienił się stan logiczny pla w algorytmie, trzeba to również zaznaczyć na ekranie

        for(int i = 0; i < ui->LifeField->rowCount(); ++i)//wczytywanie po kolei wszystkich wartości logicznych z pliku
        {

            for(int j = 0; j < ui->LifeField->columnCount(); ++j)//wczytywanie po kolei wszystkich wartości logicznych z pliku
            {
                plik >> temp_val;
                if(temp_val) emit(ui->LifeField->cellEntered(i, j));//emitowanie odpowiedniego sygnału, gdy okaże się, że wartość logiczna jest prawdziwa
            }
        }
        plik.close();//zampknięcie pliku po zakończeniu wczytywania danych

        connect(Algorithm, SIGNAL(ChangeItem(int,int,bool)), this, SLOT(SwitchField(int,int,bool)));//jeśli zmienił się stan logiczny pla w algorytmie, trzeba to również zaznaczyć na ekranie

        emit(ScreenAsk());//uaktualnianie wszystkich kwadracików na ekranie
        setWindowTitle(TitleProj + ", Otwarty plik: " + MainPath);//wyświetlenie ścieżki w tytule programu
        Changed = false;
    }
    else
    {
        LoadError.setText("Nie można odczytać pliku: " + MainPath + " - Spróbuj ponownie.");
        MainPath = "";
        if(Changed)
        {
            setWindowTitle("*" + TitleProj + ", Błąd odczytu!!!" );//zmiana tytułu okna gdy nastąpiła zmiana w stosunku do wcześniejszej wersji projektu
        }
        else
        {
            setWindowTitle(TitleProj + ", Błąd odczytu!!!" );//zmiana tytułu okna gdy nie nastąpiła zmiana w stosunku do wcześniejszej wersji projektu
        }
        LoadError.exec();//uruchomienie okienka z komunikatem o błędzie wczytania
        Load();
    }
}

void MainWindow::Save()//metoda reagująca na przycisk "zapisz"
{
    if(MainPath == "")
    {
        SaveAs();
    }
    else
    { 
        char *path = MainPath.toLocal8Bit().data();
        SaveScreen(path);//wysłanie ścieżki do pobrania
    }
}

void MainWindow::SaveAs()//metoda reagująca na przycisk "zapisz jako..."
{
    QString TempPath;//tymczasowa pomocnicza ścieżka
    TempPath = QFileDialog::getSaveFileName(this, tr("Wybierz plik do zapisania"),"./","Plik    i życia (*.life);; Wszystkie (*)");
    //sprawdzenie, czy rozszerzenie programu zgadza się

    if (TempPath.right(5) != ".life")
    {
        TempPath.append(".life");
    }

    if(TempPath != "")// jeśli podana ścieżka jest różna od pustej
    {
        MainPath = TempPath;//zapamiętanie głównej ścieżki
        char *path = MainPath.toLocal8Bit().data();
        SaveScreen(path);
    }
}

void MainWindow::SaveScreen(char * path)//metoda zapisująca do pliku całą zawartość wartości logicznych zawartych w tabeli
{
    ofstream plik(path, ios::out | ios::trunc);//całkowite czyszczenie pliku przed otwarciem

    if( plik.good() == true )
    {
        plik << noboolalpha << bool(ui->Torus->checkState()) << endl;

        for( int i = 0; i < 9; ++i )
        {
            plik << noboolalpha << bool(SettingsWindow->getTableAlive(i)) << " ";
        }
        plik << endl;

        for( int i = 0; i < 9; ++i )
        {
            plik << noboolalpha << bool(SettingsWindow->getTableDead(i)) << " ";
        }
        plik << endl;

        plik << ui->RowChanger->value() << endl;
        plik << ui->ColumnChanger->value() << endl;
        plik << ui->SizeFieldSlider->value() << endl;
        plik << AliveColor.rgb() << endl;
        plik << DeadColor.rgb() << endl;

        for(int i = 0; i < ui->LifeField->rowCount(); ++i)
        {
            plik << endl;//nowa linia
            for(int j = 0; j < ui->LifeField->columnCount(); ++j)
            {
                plik << ui->LifeField->item(i, j)->data(Qt::UserRole).toBool() << " ";//dostęp do wartości logicznych (konwersja do wartości logicznych) i zapisanie ich do pliku
            }
        }
        plik.close();
        setWindowTitle(TitleProj + ", Otwarty plik: " + MainPath);//wyświetlenie ścieżki w tytule programu
        Changed = false;
    }
    else
    {
        SaveError.setText("Nie można zapisać pliku: " + MainPath + " - Spróbuj ponownie.");
        MainPath = "";

        if(Changed)
        {
            setWindowTitle("*" + TitleProj + ", Błąd zapisu!!!" );//zmiana tytułu okna gdy nastąpiła zmiana w stosunku do wcześniejszej wersji projektu
        }
        else
        {
            setWindowTitle(TitleProj + ", Błąd zapisu!!!" );//zmiana tytułu okna gdy nie nastąpiła zmiana w stosunku do wcześniejszej wersji projektu
        }

        SaveError.exec();//wyświetlenie okienka z informacją o błędzie zapisu
        Save();
    }
}

void MainWindow::New()
{
    SaveUnsaved();//wywołanie metody wykonującej szereg czynności z niezapisanym plikiem

    MainPath = "";
    emit(ui->Cleaner->clicked());
    SetInitialValues();//ustawianie wartości początkowych
    Changed = false;
    setWindowTitle(TitleProj);// ustawienie początkowego tytułu programu
}


void MainWindow::ChangeSet()//metoda zmieniająca tytuł okna oraz wartość zmiennej changed
{
    if ( !Changed )//jeśli plansza jest zapisana i jeśli nowa ilość żywych elementów jest różna od poprzedniej
    {
        setWindowTitle("*" + windowTitle());//do tytułu dopisana jest gwiazdka na początku (tylko jedna gwiazdka, gwarantuje to zapis "jeśli stan planszy jest zapisany"
        Changed = true;//wartość zmiennej odpowiedzialnej za stan zmienionej konfiguracji tabeli jest ustawiona na prawdziwą
    }
}


//********Sloty*********


void MainWindow::MultiStep()//slot wykonujący wiele kroków algorytmu bez wyświetlania go
{
    bool tempState = IsRunning;//tymczasowa zmienna pamiętająca, stan włączonej symulacji
    //ui->NumberOfSteps->setEnabled(false);//wyłączenie spinboxa do wprowadzania ilości kroków
    disconnect(Algorithm, SIGNAL(ChangeItem(int,int,bool)), this, SLOT(SwitchField(int,int,bool)));//jeśli zmienił się stan logiczny pla w algorytmie, trzeba to również zaznaczyć na ekranie
    for(int i = 0; i < ui->NumberOfSteps->value(); ++i)
    {
        if(ui->LifeFeed->value()) emit(ui->Move->clicked());

    }
    //ui->NumberOfSteps->setEnabled(true);//włączenie spinboxa do wprowadzania ilości kroków
    connect(Algorithm, SIGNAL(ChangeItem(int,int,bool)), this, SLOT(SwitchField(int,int,bool)));//jeśli zmienił się stan logiczny pla w algorytmie, trzeba to również zaznaczyć na ekranie
    emit(ScreenAsk());
    if(!IsRunning && tempState) emit(ui->Starter->clicked());//jeśli symulacja jest zatrzymana, należy włączyć ją z powrotem

}


void MainWindow::WindowStep()//slot wnikający, czy jest uruchomiona symulacja, reagujący na działanie przycisku "Krok"
{
    if(IsRunning) emit(ui->Starter->clicked());//jeśli symulacja jest aktywna i zostal wciśnięty przycisk "krok", trzeba wcisnąć też przycisk "symulacja"
    emit(DoStep());//sygnał wykonania kroku w algorytmie
}

void MainWindow::SimulationToggle()//metoda włączająca, bądź wyłączająca symulację
{
    if(IsRunning) IsRunning = false;//zmiana wartości logicznej zmiennej odpowiedzialnej za uruchomioną symulację
    else IsRunning = true;

    if(IsRunning)//gdy symulacja trwa
    {
        //ui->Cleaner->setEnabled(false);//wyłączenie przycisku wyczyść
        //ui->Generator->setEnabled(false);//wyłączenie przycisku symulacja
        SimulationStep();//wykonanie kroku symulacji
        //TimerController.start();
    }
    else//gdy symulacja już jest zatrzymana
    {
        //ui->Cleaner->setEnabled(true);//włączenie przycisku wyczyść
        //ui->Generator->setEnabled(true);//włączenie przycisku symulacja

        Timer.stop();//zatrzymanie timera
        //TimerController.stop();//zatrzymanie timera kontrolnego
    }
    emit(ScreenAsk());//aktualizacja wszystkich stanów kwadracików w tabeli z algorytmem
}

void MainWindow::SimulationStep()//pojedynczy krok, wywołany przez przepełnienie timera
{
    if(IsRunning)//gdy uruchmiona jest symulacja
    {
        //cout << MilisecondsPerFrame << endl;
        //MilisecondsPerFrame = 0;
        Timer.start(ui->SpeedDial->value());//ustawienie odliczania timera od nowa

        disconnect(ui->LifeField, SIGNAL(cellEntered(int,int)), Algorithm, SLOT(ToggleCell(int, int)));//rozłączenie syngału i slotu jeśli nastąpi kliknięcie na tabelę, to zostanie podjęta akcja ożywienia lub umartwienia komórek
        emit(DoStep());//sygnał wykonania kroku w algorytmie
        connect(ui->LifeField, SIGNAL(cellEntered(int,int)), Algorithm, SLOT(ToggleCell(int, int)));//jeśli nastąpi kliknięcie na tabelę, to zostanie podjęta akcja ożywienia lub umartwienia komórek
    }
}

/*void MainWindow::TimerControllerTimeout()//akcja reagująca na przepełnienie się timera kontrolującego przebieg animacji
{
    //++MilisecondsPerFrame;
}*/

void MainWindow::Generate()//metoda generująca losowe elementy na ekranie
{
    bool tempState = IsRunning;//tymczasowa zmienna pamiętająca, stan włączonej symulacji
    if(IsRunning) emit(ui->Starter->clicked());//wewnętrzne "kliknięcie" przycisku symulacji, gdy symulacja jest aktywna
    bool done = false;//zmienna logiczna informująca, czy dana wartość została przyjęta
    int percent = 30;//zmienna odpowiedzialna za prawdopodobieństwo wystąpienia w procentach żywego kwadracika

    //okno do wprowadzania danych:
    percent = QInputDialog::getInt(0, "Generowanie życia", "Prawdopodobieństwo populacji\nkomórki w procentach [1 - 100]:", percent, 1, 100, 1, &done, Qt::WindowStaysOnTopHint);//wywołanie okienka do wprowadzania danych
    if(done)//jeśli nie przekazano wartości, wyjdź
    {
        emit(ui->Cleaner->clicked());//czyszczenie ekranu i wartości w algorytmie

        for(int i = 0; i < ui->LifeField->rowCount(); ++i)
        {
            for(int j = 0; j < ui->LifeField->columnCount(); ++j)//przejście przez wszystkie elementy tablicy roboczej algorytmu
            {
                if((qrand() % 100) + 1 <= percent) emit(ui->LifeField->cellEntered(i,j));//jeśli losowa wartość jest mniejsza lub równa do zmienne percet, ustaw kwadracik jako żywy
            }
        }
    }
    if(!IsRunning && tempState) emit(ui->Starter->clicked());//jeśli symulacja jest zatrzymana, należy włączyć ją z powrotem
}

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
    //ui->Page->setMinimumHeight(ui->ProjHeight->value());
    //ui->Page->setMinimumWidth(ui->ProjWidth->value());
    //ui->Page->setMaximumHeight(ui->ProjHeight->value());
    //ui->Page->setMaximumWidth(ui->ProjWidth->value());

    //if(tempWidth < 300) tempWidth = 300;


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
        if(ui->LifeField->columnWidth(i) != NewSize)ui->LifeField->setColumnWidth(i, ui->SizeFieldLcd->value());//aktualizowany rozmiar mowo tworzonych kolumn (jeśli inny od starego)
    }
    ChangeSet();//zmiana tytułu okna na tytuł z gwiazdką oraz stanu "niezapisangego" projektu
    emit (TidyUp());//sygnał porządkujący właściowści ona programu w celu uzyskania maksymalnej spójności
}

void MainWindow::ClearScreen()//funkcja czyszcząca ekran i dane w algorytmie i na ekranie jednocześnie zatrzymuje symulację, ponieważ nie ma żywych pól w tabeli
{
    if(IsRunning) emit(ui->Starter->clicked());//wewnętrzne "kliknięcie" przycisku symulacji, gdy symulacja jest aktywna
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
    ChangeSet();//zmiana tytułu okna na tytuł z gwiazdką oraz stanu "niezapisangego" projektu
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
    ChangeSet();//zmiana tytułu okna na tytuł z gwiazdką oraz stanu "niezapisangego" projektu
    emit (TidyUp());//sygnał porządkujący właściowści ona programu w celu uzyskania maksymalnej spójności
    emit StatusAsk();//zapytanie algorytmu o ilość żywych kokórek i iteracji
}

void MainWindow::StatusUpdate(int life, int iterations)//funkcja aktualizująca stan ile obiektów żyje oraz ile iteracji wystąpiło
{
    static int life_temp;//zmienna statyczna przechowująca wcześniejszą ilość żywych elementów
    static int step_temp;
    if ( life != life_temp || (step_temp != iterations)) ChangeSet();//jeśli nowa ilość żywych elementów jest różna od poprzedniej

    life_temp = life;//przypisanie do zmiennej statycznej nowej wartości (do późniejszego ponownego wykorzystania)
    step_temp = iterations;

    ui->LifeFeed->display(life);//wyświetlanie na wyświetlaczu liczby żywych komórek
    ui->Iteration->display(iterations);//wyświetlanie na wyświetlaczu liczby iteracji
    if(ui->LifeFeed->value())//jeśli choć jeden kwadracik żyje, należy uruchomić odpowiednie przyciski
    {
        ui->Move->setEnabled(true);//ustawienie przycisku "krok" jako aktywnego
        ui->Starter->setEnabled(true);//ustawienie przycisku "symulacja" jako aktywnego
        ui->MultiStarter->setEnabled(true);//ustawienie przycisku "wiele kroków" jako aktywnego
    }
    else
    {
        ui->Move->setEnabled(false);//ustawienie przycisku "krok" jako nieaktywnego
        ui->Starter->setEnabled(false);//ustawienie przycisku "symulacja" jako nieaktywnego
        ui->MultiStarter->setEnabled(false);//ustawienie przycisku "wiele kroków" jako nieaktywnego
        if(IsRunning) emit(ui->Starter->clicked());//wewnętrzne "kliknięcie" przycisku symulacji, jeśli nie ma już żadnych pól żywych !!! BARDZO WAŻNY ELEMENT CAŁEGO PROGRAMU
    }

    QFont TempFont = ui->Starter->font();//przypisanie do zmiennej tymczasowej TempFont czcionki przycisku rozpoczynającego symulację

    if(IsRunning)//gdy symulacja trwa
    {
        TempFont.setBold(true);//ustawienie odpowiedniej wielkości czcionki
    }
    else
    {
        TempFont.setBold(false);//ustawienie odpowiedniej wielkości czcionki
    }

    ui->Starter->setFont(TempFont);//ustawienie czcionki
}

void MainWindow::TorusChange(bool state)//slot przyjmujący stan zapętlania z algorytmu do mainwindow
{
    QFont TempFont = ui->Torus->font();//przypisanie do zmiennej tymczasowej TempFont czcionki checkboksa od ustawienia zapętlania
    if(state) TempFont.setBold(true);//jeśli zmieniono na prawdzią, to ma być wytłuszczenia
    else TempFont.setBold(false);//jeśli zapętlanie jest wyłączone, to nie ma być wytłuszczenia
    ui->Torus->setFont(TempFont);//ustawienie czcionki
    ChangeSet();//zmiana tytułu okna na tytuł z gwiazdką oraz stanu "niezapisangego" projektu
}

void MainWindow::on_action_Zapisz_triggered()
{
    bool tempState = IsRunning;//tymczasowa zmienna pamiętająca, stan włączonej symulacji
    if(IsRunning) emit(ui->Starter->clicked());//wewnętrzne "kliknięcie" przycisku symulacji, gdy symulacja jest aktywna
    Save();//funkcja zapisująca cały stan ekranu (wartości logicznych w tabeli)
    if(!IsRunning && tempState) emit(ui->Starter->clicked());//jeśli symulacja jest zatrzymana, należy włączyć ją z powrotem
}

void MainWindow::on_actionWczytaj_jako_triggered()
{
    bool tempState = IsRunning;//tymczasowa zmienna pamiętająca, stan włączonej symulacji
    if(IsRunning) emit(ui->Starter->clicked());//wewnętrzne "kliknięcie" przycisku symulacji, gdy symulacja jest aktywna
    LoadAs();
    if(!IsRunning && tempState) emit(ui->Starter->clicked());//jeśli symulacja jest zatrzymana, należy włączyć ją z powrotem
}

void MainWindow::on_actionZapisz_jako_triggered()
{
    bool tempState = IsRunning;//tymczasowa zmienna pamiętająca, stan włączonej symulacji
    if(IsRunning) emit(ui->Starter->clicked());//wewnętrzne "kliknięcie" przycisku symulacji, gdy symulacja jest aktywna
    SaveAs();
    if(!IsRunning && tempState) emit(ui->Starter->clicked());//jeśli symulacja jest zatrzymana, należy włączyć ją z powrotem
}

void MainWindow::on_actionWczytaj_triggered()
{
    bool tempState = IsRunning;//tymczasowa zmienna pamiętająca, stan włączonej symulacji
    if(IsRunning) emit(ui->Starter->clicked());//wewnętrzne "kliknięcie" przycisku symulacji, gdy symulacja jest aktywna
    Load();
    if(!IsRunning && tempState) emit(ui->Starter->clicked());//jeśli symulacja jest zatrzymana, należy włączyć ją z powrotem
}

void MainWindow::on_action_Nowy_triggered()
{
    if(IsRunning) emit(ui->Starter->clicked());//wewnętrzne "kliknięcie" przycisku symulacji, gdy symulacja jest aktywna
    New();
}

void MainWindow::on_actionOd_wie_triggered()
{
    TidyUp();
    emit(ScreenAsk());
}

void MainWindow::on_actionKolor_ywych_kom_rek_triggered()
{
    bool tempState = IsRunning;//tymczasowa zmienna pamiętająca, stan włączonej symulacji
    if(IsRunning) emit(ui->Starter->clicked());//wewnętrzne "kliknięcie" przycisku symwulacji, gdy symulacja jest aktywna
    QColor TempAliveColor = ChooseAliveColor.getColor(AliveColor, 0, "Wybierz kolor dla żywych komórek");
    if(TempAliveColor != "" && TempAliveColor != AliveColor)//jeśli kolor został wybrany i jest różny od tego w globalnej zmiennej, należy go ustawić
    {
        AliveColor = TempAliveColor;//ualtualnianie koloru w zmiennej globalnej
        ChangeSet();//zmiana tytułu okna na tytuł z gwiazdką oraz stanu "niezapisangego" projektu
        emit(ScreenAsk());//uaktualnianie koloru na ekranie
    }
    if(!IsRunning && tempState) emit(ui->Starter->clicked());//jeśli symulacja jest zatrzymana, należy włączyć ją z powrotem
}

void MainWindow::on_actionKo_lor_martwych_kom_rek_triggered()
{
    bool tempState = IsRunning;//tymczasowa zmienna pamiętająca, stan włączonej symulacji
    if(IsRunning) emit(ui->Starter->clicked());//wewnętrzne "kliknięcie" przycisku symulacji, gdy symulacja jest aktywna
    QColor TempDeadColor = ChooseDeadColor.getColor(DeadColor, 0, "Wybierz kolor dla martwych komórek");
    if(TempDeadColor != "" && TempDeadColor != DeadColor)//jeśli kolor został wybrany i jest różny od tego w globalnej zmiennej, należy go ustawić
    {
        DeadColor = TempDeadColor;//ualtualnianie koloru w zmiennej globalnej
        ChangeSet();//zmiana tytułu okna na tytuł z gwiazdką oraz stanu "niezapisangego" projektu
        emit(ScreenAsk());//uaktualnianie koloru na ekranie
    }
    if(!IsRunning && tempState) emit(ui->Starter->clicked());//jeśli symulacja jest zatrzymana, należy włączyć ją z powrotem
}

void MainWindow::on_actionO_programie_triggered()
{
    HelpWindow->show();
}

void MainWindow::on_action_Ustawienia_zasad_triggered()
{
    SettingsWindow->show();
}
