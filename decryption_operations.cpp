/* 
    AES 128 Bit Project 
    implementation by Abdullah1428
    CS Project
*/

// This file contains all decryption operations
// Inverse SubBytes Inverse ShiftRows Inverse Mix Columns and Add Round Key

#include "AES.hpp"
#include "lookup_tables.hpp"

// method to shift row
void inverseshiftRow(Mat, int, int);

// inverse Sub Byte method
Mat inverseSubByte(Mat state)
{

    Mat temp(NumberofBlocks, NumberofBlocks, CV_8UC1);
    uint8_t x;
    for (int i = 0; i < NumberofBlocks; i++)
    {
        for (int j = 0; j < NumberofBlocks; j++)
        {
            x = state.at<uint8_t>(i, j);
            temp.at<uint8_t>(i, j) = inverse_sbox[x / 16][x % 16];
        }
    }
    return temp;
}

// inverse Shift Rows method
Mat inverseShiftRows(Mat state)
{

    inverseshiftRow(state, 1, NumberofBlocks-1);
    inverseshiftRow(state, 2, NumberofBlocks-2);
    inverseshiftRow(state, 3, NumberofBlocks-3);

    return state;
}

// method to shift each row of the mat
 
void inverseshiftRow(Mat state, int row, int shifts)
{

    uint8_t x;
    for (int i = 0; i < shifts; i++)
    {
        x = state.at<uint8_t>(row, 0);
        for (int j = 0; j < NumberofBlocks - 1; j++)
        {
            state.at<uint8_t>(row, j) = state.at<uint8_t>(row, j + 1);
        }
        state.at<uint8_t>(row, NumberofBlocks - 1) = x;
    }
}


// inverse Mix Columns method 
Mat inverseMixColumns(Mat state)
{

    Mat temp(NumberofBlocks, NumberofBlocks, CV_8UC1);

    temp = state;

    /*

        for inverse mix columns we have to dot product each column of our state
        or data with the matrix shown below to get the each column which will be reult of mix columns
        {
            14 , 11 , 13 , 9
            9 , 14 , 11 , 13
            13 , 9 , 14 , 11
            11 , 13 , 9 , 14
        }

    */

    uint8_t column_picker[NumberofBlocks];
    uint8_t mix_column_value[NumberofBlocks];

    // first step is to pick all rows data from a single column like 0,0 1,0 2,0 3,0 etc
    // and then looking for lookup tables for that value

    for (int col = 0; col < NumberofBlocks; col++)
    {
        for (int row = 0; row < NumberofBlocks; row++)
        {
            // picking each column data
            column_picker[row] = state.at<uint8_t>(row, col);
        }
        // calculating values from lookup tables
        mix_column_value[0] = multiplier14[column_picker[0] / 16][column_picker[0] % 16] ^ multiplier11[column_picker[1] / 16][column_picker[1] % 16] ^ multiplier13[column_picker[2] / 16][column_picker[2] % 16] ^ multiplier9[column_picker[3] / 16][column_picker[3] % 16];
        mix_column_value[1] = multiplier9[column_picker[0] / 16][column_picker[0] % 16] ^ multiplier14[column_picker[1] / 16][column_picker[1] % 16] ^ multiplier11[column_picker[2] / 16][column_picker[2] % 16] ^ multiplier13[column_picker[3] / 16][column_picker[3] % 16];
        mix_column_value[2] = multiplier13[column_picker[0] / 16][column_picker[0] % 16] ^ multiplier9[column_picker[1] / 16][column_picker[1] % 16] ^ multiplier14[column_picker[2] / 16][column_picker[2] % 16] ^ multiplier11[column_picker[3] / 16][column_picker[3] % 16];
        mix_column_value[3] = multiplier11[column_picker[0] / 16][column_picker[0] % 16] ^ multiplier13[column_picker[1] / 16][column_picker[1] % 16] ^ multiplier9[column_picker[2] / 16][column_picker[2] % 16] ^ multiplier14[column_picker[3] / 16][column_picker[3] % 16];

        // storing the mix column results column wise
        for (int rows = 0; rows < NumberofBlocks; rows++)
        {
            temp.at<uint8_t>(rows, col) = mix_column_value[rows];
        }
    }

    // returning the newly Mat
    return temp;
}

// add round key method same as encryption
/*
Mat addRoundKey(Mat state, uint8_t * key)
{
    /*
    cout<<endl<<endl<<"Key Round Picking 16 bytes"<<endl;
    for(int i=0;i<16;i++)
    {
       cout<<std::hex<<(int)key[i]<<" ";
    }
    
    // simply XOR each key element with the state mat
    Mat temp(NumberofBlocks, NumberofBlocks, CV_8UC1);
    temp = state;
    for (int row = 0; row < NumberofBlocks; row++)
    {
        for (int col = 0; col < NumberofBlocks; col++)
        {
            temp.at<uint8_t>(row, col) = state.at<uint8_t>(row, col) ^ key[row + 4 * col];
        }
    }

    return temp;
}
*/