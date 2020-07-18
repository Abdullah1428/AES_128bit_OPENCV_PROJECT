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

// 3 horizontal blocks
void horizontalBlocks(Mat matrix, int size, const char * sentence)
{
    cout << endl << sentence << endl;

    int coll = 0;
    int horizontal_Condition = 4;

    for(int k = 0; k < size; k++) 
    {
        for (int row = 0; row < NumberofBlocks; row++)
        {
            for (int col = coll; col < horizontal_Condition; col++)
            {
                cout << std::hex << (int)matrix.at<uint8_t>(row, col) << " ";
            }
            cout << endl;
        }
        cout<<endl;
        horizontal_Condition += 4;
        coll+=4;
    }
}

// 3 vertical blocks
void verticalBlocks(Mat matrix, int size, const char * sentence)
{
    cout << endl << sentence << endl;

    int roww = 0;
    int vertical_Condition = 4;

    for(int k = 0; k < size; k++) 
    {
        for (int row = roww; row < vertical_Condition; row++)
        {
            for (int col = 0; col < NumberofBlocks; col++)
            {
                cout << std::hex << (int)matrix.at<uint8_t>(row, col) << " ";
            }
            cout << endl;
        }
        cout<<endl;
        vertical_Condition += 4;
        roww+=4;
    }
}

// get text file length and text methods
int getTextFileLength (const char * file)
{
    stringstream fileString;
    
    string fileData;
	
    ifstream userData;

    string fileDir = "files/";

    string fileName = fileDir+file;

	userData.open(fileName, ios::in | ios::binary);
    if (userData.is_open()) 
    {
        fileString << userData.rdbuf();
    }
    else
    {
        cout<<"the input file could not be read,Please try again with a proper text file with the text to be encrypted";
        return 0;
    }

    userData.close();
    
    // displaying data stored in array
    fileData = fileString.str();

    // counting all characters in the file
    int length = 0;
    while(fileData[length] != '\0')
    {
        length++;
    }

    int adjustedLength = length;

    if((adjustedLength % 16) != 0)
    {
        adjustedLength = (adjustedLength/NumberofBytes+1)*NumberofBytes;
    }   

    return adjustedLength;

}

uint8_t * getTextFromInputFile(const char * file , uint8_t * data)
{
    stringstream fileString;
    
    string fileData;
	
    ifstream userData;

    string fileDir = "files/";

    string fileName = fileDir+file;

	userData.open(fileName, ios::in | ios::binary);
    if (userData.is_open()) 
    {
        fileString << userData.rdbuf();
    }

    userData.close();
    
    // displaying data stored in array
    fileData = fileString.str();

    // counting all characters in the file
    int length = 0;
    while(fileData[length] != '\0')
    {
        length++;
    }

    uint8_t textdata[length];
    
    for (int i=0;i<length;i++)
    {
        textdata[i] = fileData[i];
    }

    int adjustedLength = length;

    if((adjustedLength % 16) != 0)
    {
        adjustedLength = (adjustedLength/NumberofBytes+1)*NumberofBytes;
    }   

    for (int i=0;i<adjustedLength;i++)
    {
        // here we will add 0 in the adjusted length
        if(i >= length)
        {
            data[i] = 0;
        }
        else
        {
            data[i] = textdata[i];
        }
    }

    return data;
}

Mat getKeyFile(const char * key)
{

    Mat keyBlock = Mat::zeros(NumberofBlocks,NumberofBlocks,CV_8UC1);

    string KEY;
	ifstream infile;

    string keyDir = "files/";

    string keyFile = keyDir + key;

	infile.open(keyFile, ios::in | ios::binary);

    if (infile.is_open())
	{
        // The first line of file should be the key
		getline(infile, KEY); 
		infile.close();
	}
    else
    {
        cout<<"Key file could not be read";
    }

    istringstream hex_chars_stream(KEY);
    uint8_t keyData[16];
	int i = 0;
	unsigned int c;
	while (hex_chars_stream >> hex >> c)
	{
		keyData[i] = c;
		i++;
	}
    
    int index = 0;
    for(int i=0;i<NumberofBlocks;i++)
    {
        for(int j=0;j<NumberofBlocks;j++)
        {
            keyBlock.at<uint8_t>(i,j) = keyData[index];
            index++;
        }
    }

    return keyBlock;

}