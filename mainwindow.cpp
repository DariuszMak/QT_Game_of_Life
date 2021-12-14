#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    Table_widget_cell_size = 1;

    for (unsigned int i = 0; i < 1024; i++)
    {
        if (i == 0){
            LCDDataBuffer[i] = 0x03;
        }

        if (i == 128){
            LCDDataBuffer[i] = 0xff;
        }

        if (i == 1023){
            LCDDataBuffer[i] = 0xf0;
        }

        std::cout << i << ": " << LCDDataBuffer[i] << std::endl;
    }

    LCDNubmberOfXCoord = 128;
    LCDNubmberOfYCoord = 8;

    NumberOfColumnsInWidget = 128;
    NumberOfRowsInWidget = 64;

    ui->setupUi(this);

    MinSizeSquare = 1;

    connect(ui->Cleaner, SIGNAL(clicked()), this, SLOT(ClearScreen()));





    connect(this, SIGNAL(Refresh_fields_state()), this, SLOT(TidyUpScreen()));
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

    this->RowsChanged(this->NumberOfRowsInWidget);
    this->ColumnsChanged(this->NumberOfColumnsInWidget);

    this->printBuffer(this->LCDDataBuffer);
}





void MainWindow::printBuffer(uint8_t * const displayBuffer)
{
    this->DisplayAccordingToBuffer(displayBuffer);
}

void MainWindow::DisplayAccordingToBuffer(uint8_t * const displayBuffer)
{
    std::printf("Display According To Buffer invoked. \n");

    for (int y = 0; y < this->LCDNubmberOfYCoord; ++y)
    {
        for(int x = 0; x < this->LCDNubmberOfXCoord; ++x)
        {
            int buffer_index = (y * 128)+ x;
            int byte_from_buffer = displayBuffer[buffer_index];

            for(int byte_number = 0; byte_number < 8; ++byte_number) {
                bool logical_value = ((byte_from_buffer >> byte_number)  & 0x01);
                int y_coordinate_for_widget = (y * 8) + byte_number;

                cout << "y: " << y << ", x: " << x << ", buffer_index: " << buffer_index << ", byte_from_buffer: " << byte_from_buffer << ", y_coordinate_for_widget: " << y_coordinate_for_widget << ", boolean_value: " << logical_value<< endl;

                emit(this->SwitchField(y_coordinate_for_widget, x, logical_value));
            }
        }
    }
}

void MainWindow::TidyUpScreen()
{
    std::printf("Tidy up screen invoked. \n");
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
    emit(Refresh_fields_state());
}

void MainWindow::ClearScreen()
{
    emit(ClearAlg());
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
    emit(Refresh_fields_state());
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
    emit (Refresh_fields_state());
}
