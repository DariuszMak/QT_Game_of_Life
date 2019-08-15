#ifndef SETTINGWINDOW_H
#define SETTINGWINDOW_H

#include <QDialog>
#include <iostream>
using namespace std;

namespace Ui {
class settingWindow;
}

class SettingWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SettingWindow(QWidget *parent = 0);
    ~SettingWindow();
    void setTableAlive(int, bool);//setter do tablicy z regułami dla żywych komórek, określa czy dalej mają być żywe (przyjmuje indeks i logiczną wartość)
    void setTableDead(int, bool);//setter do tablicy dla martywch komórek, określa czy komórki mają ożyć (przyjmuje indeks i logiczną wartość)
    bool getTableAlive(int);//getter do tablicy z regułami dla żywych komórek, określa czy dalej mają być żywe (zwraca logiczną wartość, przyjmuje indeks)
    bool getTableDead(int);//getter do tablicy dla martywch komórek, określa czy komórki mają ożyć (zwraca logiczną wartość, przyjmuje indeks)

private:
    Ui::settingWindow *ui;
    bool tableOfRulesAlive[9];//tablica z regułami dla żywych komórek, określa czy dalej mają być żywe
    bool tableOfRulesDead[9];//tablica z regułami dla martywch komórek, określa czy komórki mają ożyć
private slots:
    void actualizeTableAlive();//aktualizacja zawartości tablicy (dla żywych komórek, określa czy dalej mają być żywe) zgodnie z zaznaczoną zawartością
    void actualizeTableDead();//aktualizacja zawartości tablicy (dla martywch komórek, określa czy komórki mają ożyć) zgodnie z zaznaczoną zawartością
    void checkAllAlive();//zaznacza wszystkie opcje reguł dla żywych komórek
    void uncheckAllAlive();//odznacza wszystkie opcje reguł dla żywych komórek
    void checkAllDead();//zaznacza wszystkie opcje reguł dla żywych komórek
    void uncheckAllDead();//odznacza wszystkie opcje reguł dla żywych komórek

signals:
};



#endif // SETTINGWINDOW_H
