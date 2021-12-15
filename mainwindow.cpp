#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qtsimulator_lcd.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    Table_widget_cell_size = 1;

    ui->setupUi(this);

    MinSizeSquare = 1;

    srand(QTime::currentTime().msecsTo(QTime(0, 0, 0, 0)));
    SetInitialValues();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::resizeEvent(QResizeEvent *event)
{
    event->accept();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    event->accept();
    emit CloseOtherWindows();
}

void MainWindow::SetInitialValues()
{
    QFont font = ui->LifeField->font();
    font.setPointSize(1);
    ui->LifeField->setFont(font);

    this->setMinimumSize(QSize(1800, 700));


    AliveColor = QColor("yellow");
    DeadColor = QColor("black");

    this->RowsChanged(DISPLAY_ROWS);
    this->ColumnsChanged(DISPLAY_COLUMNS);
}

void MainWindow::DisplayAccordingToBuffer(uint8_t * const displayBuffer)
{
    std::printf("Display According To Buffer invoked. \n");

    for (int y = 0; y < DISPLAY_PAGES; ++y)
    {
        for(int x = 0; x < DISPLAY_COLUMNS; ++x)
        {
            int buffer_index = (y * DISPLAY_COLUMNS)+ x;
            int byte_from_buffer = displayBuffer[buffer_index];

            for(int byte_number = 0; byte_number < 8; ++byte_number) {
                bool logical_value = ((byte_from_buffer >> byte_number)  & 0x01);
                int y_coordinate_for_widget = (y * DISPLAY_PAGES) + byte_number;

                cout << "y: " << y << ", x: " << x << ", buffer_index: " << buffer_index << ", byte_from_buffer: " << byte_from_buffer << ", y_coordinate_for_widget: " << y_coordinate_for_widget << ", boolean_value: " << logical_value<< endl;

                emit(this->SwitchField(y_coordinate_for_widget, x, logical_value));
            }
        }
    }
}


void MainWindow::ResizeField(int NewSize)
{
    for(int i = 0; i < ui->LifeField->rowCount(); ++i)
    {
        if(ui->LifeField->rowHeight(i) != NewSize) ui->LifeField->setRowHeight(i, Table_widget_cell_size);
    }

    for(int i = 0; i < ui->LifeField->columnCount(); ++i)
    {
        if(ui->LifeField->columnWidth(i) != NewSize) ui->LifeField->setColumnWidth(i, Table_widget_cell_size);
    }
}

void MainWindow::SwitchField(int x, int y, bool value)
{
    QTableWidgetItem * item = ui->LifeField->item(x, y);

    if(item == 0)
    {
        item = new QTableWidgetItem;
        ui->LifeField->setItem(x, y, item);
    }

    if(value)
    {

        if(item->data(Qt::UserRole) != true)
        {
            item->setData(Qt::UserRole, QVariant(true));
        }

        if(item->background() != AliveColor)
        {
            item->setBackground(AliveColor);
        }
    }
    else
    {
        if(item->data(Qt::UserRole) != false)
        {
            item->setData(Qt::UserRole, QVariant(false));
        }

        if(item->background() != DeadColor)
        {
            item->setBackground(DeadColor);
        }
    }
}

void MainWindow::RowsChanged(int newRow)
{
    if(ui->LifeField->rowCount() == newRow) return;
    int oldRows = ui->LifeField->rowCount();

    ui->LifeField->setRowCount(newRow);


    for(int i = oldRows; i < newRow; ++i)
    {
        for(int j = 0; j < ui->LifeField->columnCount(); ++j)
        {
            SwitchField(i, j, false);
        }
        ui->LifeField->setRowHeight(i, Table_widget_cell_size);
    }
}

void MainWindow::ColumnsChanged(int newCol)
{
    if(ui->LifeField->columnCount() == newCol) return;
    int oldColumns = ui->LifeField->columnCount();

    ui->LifeField->setColumnCount(newCol);


    for(int i = oldColumns; i < newCol; ++i)
    {
        for(int j = 0; j < ui->LifeField->rowCount(); ++j)
        {
            SwitchField(j, i, false);
        }
        ui->LifeField->setColumnWidth(i, Table_widget_cell_size);
    }
}
