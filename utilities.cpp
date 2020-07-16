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

/////////////////////////////////////////////////////////////////////////////
// Similar Methods used for all types of encryptions and decryptions
Mat image_block_getter(Mat data, int x, int y)
{
    Mat block(4,4,CV_8UC1);
    block = Mat::zeros(4,4,CV_8UC1);
    for (int i=y; i<(y+NumberofBlocks); i++)
    {
        for (int j=x; j<(x+NumberofBlocks); j++)
        {
            if (i<data.rows && j<data.cols)
            {
                block.at<uint8_t>(i-y,j-x) = data.at<uint8_t>(i,j);
            }
        }
    }
    return block;
}

void image_block_setter(Mat * setter ,Mat block,int x,int y)
{
    for (int i=y; i<(y+NumberofBlocks); i++)
    {
        for (int j=x; j<(x+NumberofBlocks); j++)
        {
            setter->at<uint8_t>(i,j) = block.at<uint8_t>(i-y,j-x);
        }
    }
}

// add round key method
Mat addRoundKey(Mat state, uint8_t * key)
{
    /*
    cout<<endl<<endl<<"Key Round Picking 16 bytes"<<endl;
    for(int i=0;i<16;i++)
    {
       cout<<std::hex<<(int)key[i]<<" ";
    }
    */
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

// Mat XOR CBC 
Mat XOR_CBC(Mat iv, uint8_t data[])
{
    Mat plainText(NumberofBlocks, NumberofBlocks, CV_8UC1);

    oneDcopytoMatrix(plainText,data);    

    Mat temp(NumberofBlocks, NumberofBlocks, CV_8UC1);

    for (int row = 0; row < NumberofBlocks; row++)
    {
        for (int col = 0; col < NumberofBlocks; col++)
        {
            temp.at<uint8_t>(row, col) = plainText.at<uint8_t>(row, col) ^ iv.at<uint8_t>(row, col);
        }
    }

    return temp;
}

// Mat XOR CBC image
Mat XOR_CBC_Image(Mat iv, Mat data)
{
    Mat temp(NumberofBlocks, NumberofBlocks, CV_8UC1);

    for (int row = 0; row < NumberofBlocks; row++)
    {
        for (int col = 0; col < NumberofBlocks; col++)
        {
            temp.at<uint8_t>(row, col) = data.at<uint8_t>(row, col) ^ iv.at<uint8_t>(row, col);
        }
    }

    return temp;
}