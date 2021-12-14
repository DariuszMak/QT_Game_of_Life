#include "lcd_state_boolean_table.h"
#include <iostream>


LCDStateBooleanTable::LCDStateBooleanTable()
{
    Rows = 0;
    Columns = 0;
}


void LCDStateBooleanTable::ClearValues()
{
    for (int i = 0; i < Rows; ++i)
    {
        for(int j = 0; j < Columns; ++j)
        {
            Field[i][j] = false;
        }
    }
}


void LCDStateBooleanTable::ScreenAns()
{
    for (int i = 0; i < Rows; ++i)
    {
        for(int j = 0; j < Columns; ++j)
        {
            emit(ChangeCellFromVectorTable(i, j, Field[i][j]));
        }
    }
}


void LCDStateBooleanTable::NewRows(int newRow)
{
    Field.resize(newRow);

    for(int i = Rows; i < newRow; ++i)
    {
        Field[i].resize(Columns); 
    }

    Rows = newRow; 
    emit(NewRowsInf(newRow));
}


void LCDStateBooleanTable::NewColumns(int newCol)
{
    for(int i = 0; i < Rows; ++i)
    {
        Field[i].resize(newCol); 
    }

    Columns = newCol; 
    emit(NewColumnsInf(newCol));
}
