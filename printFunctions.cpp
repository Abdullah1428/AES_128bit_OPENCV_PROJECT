#include "AES.hpp"

// different print functions

void PrintMatrix(Mat matrix, const char *sentence)
{
    cout << endl << sentence << endl;
    for (int row = 0; row < NumberofBlocks; row++)
    {
        for (int col = 0; col < NumberofBlocks; col++)
        {
            cout << std::hex << (int)matrix.at<uint8_t>(row, col) << " ";
        }
        cout << endl;
    }
}

void PrintArray(uint8_t *array, const char *sentence)
{
    cout << endl << sentence << endl;
    for (int i = 0; i < NumberofBytes; i++)
    {
        cout << std::hex << (int)array[i] << " ";
    }
}

void PrintArrayWithRange(uint8_t *array, const char *sentence,int range)
{
    cout << endl << sentence << endl;
    for (int i = 0; i < range; i++)
    {
        cout << std::hex << (int)array[i] << " ";
    }
}

void PrintExpandedKey(uint8_t *array, const char *sentence)
{
    int index = 0;
    cout << endl << sentence << endl;
    for (int i = 0; i < 176; i++)
    {
        cout << std::hex << (int)array[i] << " ";
        index++;
        if (index % 16 == 0 && index != 0)
        {
            cout << endl;
        }
    }
}

// different copy data methods

void dataCopytoMatrix(Mat mat, uint8_t array[4][4])
{
    for (int i = 0; i < NumberofBlocks; i++)
    {
        for (int j = 0; j < NumberofBlocks; j++)
        {
            mat.at<uint8_t>(i, j) = array[i][j];
        }
    }
}

void matrixCopytoArray(Mat ciphered,uint8_t cipher[])
{
    int ind = 0;
    for (int row=0;row<NumberofBlocks;row++)
    {
        for(int col=0;col<NumberofBlocks;col++)
        {
            cipher[ind] = ciphered.at<uint8_t>(row,col);
            ind++;
        }
    } 
}

void dataCopyTo2dArray(uint8_t dest[4][4],uint8_t source[])
{
    int index = 0;
    for (int row=0;row<NumberofBlocks;row++)
    {
        for(int col=0;col<NumberofBlocks;col++)
        {
            dest[row][col] = source[index];
            index++;
        }
    } 
}

void oneDcopytoMatrix (Mat dest,uint8_t source[])
{
    int index = 0;
    for (int i = 0; i < NumberofBlocks; i++)
    {
        for (int j = 0; j < NumberofBlocks; j++)
        {
            dest.at<uint8_t>(i, j) = source[index];
            index++;
        }
    }   
}

void dataCopytoMatrix8(Mat mat, uint8_t array[8][8])
{
    for (int i = 0; i < NumberofBlocks+NumberofBlocks; i++)
    {
        for (int j = 0; j < NumberofBlocks+NumberofBlocks; j++)
        {
            mat.at<uint8_t>(i, j) = array[i][j];
        }
    }
}