#include "help.h"
#include "ui_help.h"

Help::Help(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Help)
{
    ui->setupUi(this);
    this->setWindowTitle("O programie");
    connect(parent, SIGNAL(CloseOtherWindows()), this, SLOT(close()));//jeśli z klasy rodzica zostało wysłane polecenie zamknięcia wszystkich okien, to i to okno zostaje zamknięte
}

Help::~Help()
{
    delete ui;
}
