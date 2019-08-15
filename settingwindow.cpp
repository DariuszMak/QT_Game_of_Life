#include "settingwindow.h"
#include "ui_settingwindow.h"

SettingWindow::SettingWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::settingWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Ustawienia zasad");
    connect(parent, SIGNAL(CloseOtherWindows()), this, SLOT(close()));//jeśli z klasy rodzica zostało wysłane polecenie zamknięcia wszystkich okien, to i to okno zostaje zamknięte
    connect(ui->checkBox0, SIGNAL(clicked(bool)), this, SLOT(actualizeTableAlive()));//połączenie checkBoxa z działaniem na tablicy z zasadami gry dla żywych komórek
    connect(ui->checkBox1, SIGNAL(clicked(bool)), this, SLOT(actualizeTableAlive()));//połączenie checkBoxa z działaniem na tablicy z zasadami gry dla żywych komórek
    connect(ui->checkBox2, SIGNAL(clicked(bool)), this, SLOT(actualizeTableAlive()));//połączenie checkBoxa z działaniem na tablicy z zasadami gry dla żywych komórek
    connect(ui->checkBox3, SIGNAL(clicked(bool)), this, SLOT(actualizeTableAlive()));//połączenie checkBoxa z działaniem na tablicy z zasadami gry dla żywych komórek
    connect(ui->checkBox4, SIGNAL(clicked(bool)), this, SLOT(actualizeTableAlive()));//połączenie checkBoxa z działaniem na tablicy z zasadami gry dla żywych komórek
    connect(ui->checkBox5, SIGNAL(clicked(bool)), this, SLOT(actualizeTableAlive()));//połączenie checkBoxa z działaniem na tablicy z zasadami gry dla żywych komórek
    connect(ui->checkBox6, SIGNAL(clicked(bool)), this, SLOT(actualizeTableAlive()));//połączenie checkBoxa z działaniem na tablicy z zasadami gry dla żywych komórek
    connect(ui->checkBox7, SIGNAL(clicked(bool)), this, SLOT(actualizeTableAlive()));//połączenie checkBoxa z działaniem na tablicy z zasadami gry dla żywych komórek
    connect(ui->checkBox8, SIGNAL(clicked(bool)), this, SLOT(actualizeTableAlive()));//połączenie checkBoxa z działaniem na tablicy z zasadami gry dla żywych komórek

    connect(ui->checkBox_0, SIGNAL(clicked(bool)), this, SLOT(actualizeTableDead()));//połączenie checkBoxa z działaniem na tablicy z zasadami gry dla martwych komórek
    connect(ui->checkBox_1, SIGNAL(clicked(bool)), this, SLOT(actualizeTableDead()));//połączenie checkBoxa z działaniem na tablicy z zasadami gry dla martwych komórek
    connect(ui->checkBox_2, SIGNAL(clicked(bool)), this, SLOT(actualizeTableDead()));//połączenie checkBoxa z działaniem na tablicy z zasadami gry dla martwych komórek
    connect(ui->checkBox_3, SIGNAL(clicked(bool)), this, SLOT(actualizeTableDead()));//połączenie checkBoxa z działaniem na tablicy z zasadami gry dla martwych komórek
    connect(ui->checkBox_4, SIGNAL(clicked(bool)), this, SLOT(actualizeTableDead()));//połączenie checkBoxa z działaniem na tablicy z zasadami gry dla martwych komórek
    connect(ui->checkBox_5, SIGNAL(clicked(bool)), this, SLOT(actualizeTableDead()));//połączenie checkBoxa z działaniem na tablicy z zasadami gry dla martwych komórek
    connect(ui->checkBox_6, SIGNAL(clicked(bool)), this, SLOT(actualizeTableDead()));//połączenie checkBoxa z działaniem na tablicy z zasadami gry dla martwych komórek
    connect(ui->checkBox_7, SIGNAL(clicked(bool)), this, SLOT(actualizeTableDead()));//połączenie checkBoxa z działaniem na tablicy z zasadami gry dla martwych komórek
    connect(ui->checkBox_8, SIGNAL(clicked(bool)), this, SLOT(actualizeTableDead()));//połączenie checkBoxa z działaniem na tablicy z zasadami gry dla martwych komórek

    connect(ui->pushButton_selAllAlive, SIGNAL(clicked(bool)), this, SLOT(checkAllAlive()));//zaznaczenie wszystkich opcji dla żywych komórek
    connect(ui->pushButton_deselAllAlive, SIGNAL(clicked(bool)), this, SLOT(uncheckAllAlive()));//odznaczenie wszystkich opcji dla żywych komórek

    connect(ui->pushButton_selAllDead, SIGNAL(clicked(bool)), this, SLOT(checkAllDead()));//zaznaczenie wszystkich opcji dla żywych komórek
    connect(ui->pushButton_deselAllDead, SIGNAL(clicked(bool)), this, SLOT(uncheckAllDead()));//odznaczenie wszystkich opcji dla żywych komórek



    for(int i = 0; i < 9; ++i)
    {
        tableOfRulesAlive[i] = 0;
        tableOfRulesAlive[i] = 0;
    }

    this->actualizeTableAlive();
    this->actualizeTableDead();

}

void SettingWindow::setTableAlive(int index, bool value)//setter do tablicy z regułami dla żywych komórek, określa czy dalej mają być żywe (przyjmuje indeks i logiczną wartość)
{
    tableOfRulesAlive[index] = value;
    if( index == 0 ) ui->checkBox0->setChecked(tableOfRulesAlive[index]);
    else if ( index == 1 ) ui->checkBox1->setChecked(tableOfRulesAlive[index]);
    else if ( index == 2 ) ui->checkBox2->setChecked(tableOfRulesAlive[index]);
    else if ( index == 3 ) ui->checkBox3->setChecked(tableOfRulesAlive[index]);
    else if ( index == 4 ) ui->checkBox4->setChecked(tableOfRulesAlive[index]);
    else if ( index == 5 ) ui->checkBox5->setChecked(tableOfRulesAlive[index]);
    else if ( index == 6 ) ui->checkBox6->setChecked(tableOfRulesAlive[index]);
    else if ( index == 7 ) ui->checkBox7->setChecked(tableOfRulesAlive[index]);
    else if ( index == 8 ) ui->checkBox8->setChecked(tableOfRulesAlive[index]);
    actualizeTableAlive();
}

void SettingWindow::setTableDead(int index, bool value)//setter do tablicy dla martywch komórek, określa czy komórki mają ożyć (przyjmuje indeks i logiczną wartość)
{
    tableOfRulesDead[index] = value;
    if( index == 0 ) ui->checkBox_0->setChecked(tableOfRulesDead[index]);
    else if ( index == 1 ) ui->checkBox_1->setChecked(tableOfRulesDead[index]);
    else if ( index == 2 ) ui->checkBox_2->setChecked(tableOfRulesDead[index]);
    else if ( index == 3 ) ui->checkBox_3->setChecked(tableOfRulesDead[index]);
    else if ( index == 4 ) ui->checkBox_4->setChecked(tableOfRulesDead[index]);
    else if ( index == 5 ) ui->checkBox_5->setChecked(tableOfRulesDead[index]);
    else if ( index == 6 ) ui->checkBox_6->setChecked(tableOfRulesDead[index]);
    else if ( index == 7 ) ui->checkBox_7->setChecked(tableOfRulesDead[index]);
    else if ( index == 8 ) ui->checkBox_8->setChecked(tableOfRulesDead[index]);
    actualizeTableDead();
}

bool SettingWindow::getTableAlive(int index)//getter do tablicy z regułami dla żywych komórek, określa czy dalej mają być żywe (zwraca logiczną wartość, przyjmuje indeks)
{
    return tableOfRulesAlive[index];
}

bool SettingWindow::getTableDead(int index)//getter do tablicy dla martywch komórek, określa czy komórki mają ożyć (zwraca logiczną wartość, przyjmuje indeks)
{
    return tableOfRulesDead[index];
}


void SettingWindow::actualizeTableAlive()//aktualizacja zawartości tablicy (dla żywych komórek, określa czy dalej mają być żywe) zgodnie z zaznaczoną zawartością
{
    bool temp;
    QString temp_text = "";
    for(int i = 0; i < 9; ++i)
    {
        if( i == 0 ) temp = ui->checkBox0->checkState();
        else if ( i == 1 ) temp = ui->checkBox1->checkState();
        else if ( i == 2 ) temp = ui->checkBox2->checkState();
        else if ( i == 3 ) temp = ui->checkBox3->checkState();
        else if ( i == 4 ) temp = ui->checkBox4->checkState();
        else if ( i == 5 ) temp = ui->checkBox5->checkState();
        else if ( i == 6 ) temp = ui->checkBox6->checkState();
        else if ( i == 7 ) temp = ui->checkBox7->checkState();
        else if ( i == 8 ) temp = ui->checkBox8->checkState();
        tableOfRulesAlive[i] = temp;
        if (tableOfRulesAlive[i]) temp_text.append(QString::number(i));
    }
    if (temp_text == "") temp_text = "-";
    ui->label_alive->setText(temp_text);
}

void SettingWindow::actualizeTableDead()//aktualizacja zawartości tablicy (dla martywch komórek, określa czy komórki mają ożyć) zgodnie z zaznaczoną zawartością
{
    bool temp;
    QString temp_text = "";
    for(int i = 0; i < 9; ++i)
    {
        if( i == 0 ) temp = ui->checkBox_0->checkState();
        else if ( i == 1 ) temp = ui->checkBox_1->checkState();
        else if ( i == 2 ) temp = ui->checkBox_2->checkState();
        else if ( i == 3 ) temp = ui->checkBox_3->checkState();
        else if ( i == 4 ) temp = ui->checkBox_4->checkState();
        else if ( i == 5 ) temp = ui->checkBox_5->checkState();
        else if ( i == 6 ) temp = ui->checkBox_6->checkState();
        else if ( i == 7 ) temp = ui->checkBox_7->checkState();
        else if ( i == 8 ) temp = ui->checkBox_8->checkState();
        tableOfRulesDead[i] = temp;
        if (tableOfRulesDead[i]) temp_text.append(QString::number(i));
    }
    if (temp_text == "") temp_text = "-";
    ui->label_dead->setText(temp_text);
}

void SettingWindow::checkAllAlive()//zaznacza wszystkie opcje reguł dla żywych komórek
{
    for( int i = 0; i < 9; ++i )
    {
        this->setTableAlive( i, true );
    }
}

void SettingWindow::uncheckAllAlive()//odznacza wszystkie opcje reguł dla żywych komórek
{
    for( int i = 0; i < 9; ++i )
    {
        this->setTableAlive( i, false );
    }
}

void SettingWindow::checkAllDead()//zaznacza wszystkie opcje reguł dla żywych komórek
{
    for( int i = 0; i < 9; ++i )
    {
        this->setTableDead( i, true );
    }
}

void SettingWindow::uncheckAllDead()//odznacza wszystkie opcje reguł dla żywych komórek
{
    for( int i = 0; i < 9; ++i )
    {
        this->setTableDead( i, false );
    }
}


SettingWindow::~SettingWindow()
{
    delete ui;
}
