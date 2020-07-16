/* 
    AES 128 Bit Project 
    implementation by Abdullah1428
    CS Project
*/

#include "AES.hpp"

void file_Encryption_ECB()
{
    stringstream fileString;
    string fileData;
	ifstream userData;
	userData.open("InputFile.txt", ios::in | ios::binary);
    if (userData.is_open()) 
    {
        fileString << userData.rdbuf();
    }

    userData.close();
    
    // displaying data stored in array
    fileData = fileString.str();

    // counting all characters in the file
    int x = 0;
    while(fileData[x] != '\0')
    {
        x++;
    }

    int limit = x;
    // declaring array for the data
    uint8_t data[limit];
    
    for (int i=0;i<limit;i++)
    {
        data[i] = fileData[i];
    }

    unsigned int orignalLength = limit;
    // cout<<endl<<"The length of data is "<<orignalLength<<endl;

    /* 
        // printing the hex of data 
        // da for new line

    for(int i=0;i<sizeof(data);i++)
    {
        cout<<std::hex<<(int)data[i];
    }
    */

    // in AES we encrypt or decrypt 16 bytes of block at one time so 
    // our data must be a multiplier of 16 and if not then we will add
    // dummy zero data at the end to make the data multiplier of 16

    int adjustedLength = orignalLength;

    if((adjustedLength % 16) != 0)
    {
        adjustedLength = (adjustedLength/NumberofBytes+1)*NumberofBytes;
    }

    //cout<<endl<<"The adjusted length is "<<adjustedLength<<endl;

    // now defining new array for the adjusted data so it can be encrypted correctly
    uint8_t adjustedData[adjustedLength];
    // encryptedData array will contain the ciphered or encrypted data
    uint8_t encryptedData[adjustedLength];

    for (int i=0;i<adjustedLength;i++)
    {
        // here we will add 0 in the adjusted length
        if(i >= orignalLength)
        {
            adjustedData[i] = 0;
        }
        else
        {
            adjustedData[i] = data[i];
        }
    }

    // displaying new data after adjusting and adding zeros
    /*
    for(int i=0;i<adjustedLength;i++)
    {
        cout<<std::hex<<(int)adjustedData[i];
    }
    */

    // declaring our key
    // 16 bytes of key or 128 bits of key
    uint8_t key[NumberofBlocks][NumberofBlocks] = 
    {
        0x2b, 0x28, 0xab, 0x09,
        0x7e, 0xae, 0xf7, 0xcf,
        0x15, 0xd2, 0x15, 0x4f,
        0x16, 0xa6, 0x88, 0x3c
    };

    Mat keyBlock(NumberofBlocks, NumberofBlocks, CV_8UC1);
    dataCopytoMatrix(keyBlock,key);


    // now calling the encryption function to encrypt our text
    for(int i=0;i<adjustedLength;i+=NumberofBytes)
    {
        file_encryption(adjustedData + i , keyBlock , encryptedData + i);
    }

    // now displaying the encrypted data 
    //PrintArrayWithRange(encryptedData,"The encrypted data is : ",adjustedLength);

    // Write the encrypted string out to file ""
	ofstream outfile;
	outfile.open("EncodedFile.txt", ios::out | ios::binary);
	if (outfile.is_open())
	{
		outfile.write((char *)encryptedData,adjustedLength);
		outfile.close();
		cout << endl << "Wrote encrypted message to file" << endl;
	}
	else
    {
        cout << "Unable to open file";
    }
}

void file_Encryption_CBC()
{
    stringstream fileString;
    string fileData;
	ifstream userData;
	userData.open("InputFile.txt", ios::in | ios::binary);
    if (userData.is_open()) 
    {
        fileString << userData.rdbuf();
    }

    userData.close();
    
    // displaying data stored in array
    fileData = fileString.str();

    // counting all characters in the file
    int x = 0;
    while(fileData[x] != '\0')
    {
        x++;
    }

    int limit = x;

    // declaring array for the data
    uint8_t data[limit];
    
    for (int i=0;i<limit;i++)
    {
        data[i] = fileData[i];
    }

    unsigned int orignalLength = limit;
    // cout<<endl<<"The length of data is "<<orignalLength<<endl;

    /* 
        // printing the hex of data 
        // da for new line

    for(int i=0;i<sizeof(data);i++)
    {
        cout<<std::hex<<(int)data[i];
    }
    */

    // in AES we encrypt or decrypt 16 bytes of block at one time so 
    // our data must be a multiplier of 16 and if not then we will add
    // dummy zero data at the end to make the data multiplier of 16

    int adjustedLength = orignalLength;

    if((adjustedLength % 16) != 0)
    {
        adjustedLength = (adjustedLength/NumberofBytes+1)*NumberofBytes;
    }

    //cout<<endl<<"The adjusted length is "<<adjustedLength<<endl;

    // now defining new array for the adjusted data so it can be encrypted correctly
    uint8_t adjustedData[adjustedLength];
    // encryptedData array will contain the ciphered or encrypted data
    uint8_t encryptedData[adjustedLength];

    for (int i=0;i<adjustedLength;i++)
    {
        // here we will add 0 in the adjusted length
        if(i >= orignalLength)
        {
            adjustedData[i] = 0;
        }
        else
        {
            adjustedData[i] = data[i];
        }
    }

    // displaying new data after adjusting and adding zeros
    /*
    for(int i=0;i<adjustedLength;i++)
    {
        cout<<std::hex<<(int)adjustedData[i];
    }
    */

    // Now this is CBC Mode so we will need a initialization vector which
    // will be XORed with the data
    // for CBC Mode declaing IV matrix
    uint8_t iv[NumberofBlocks][NumberofBlocks] = 
    {
        0x0f, 0x0f, 0x0f, 0x0f,
        0x0f, 0x0f, 0x0f, 0x0f,
        0x0f, 0x0f, 0x0f, 0x0f,
        0x0f, 0x0f, 0x0f, 0x0f,
    };

    // declaring our key
    // 16 bytes of key or 128 bits of key
    uint8_t key[NumberofBlocks][NumberofBlocks] = 
    {
        0x2b, 0x28, 0xab, 0x09,
        0x7e, 0xae, 0xf7, 0xcf,
        0x15, 0xd2, 0x15, 0x4f,
        0x16, 0xa6, 0x88, 0x3c
    };

    Mat keyBlock(NumberofBlocks, NumberofBlocks, CV_8UC1);
    Mat ivBlock(NumberofBlocks,NumberofBlocks,CV_8UC1);
    dataCopytoMatrix(keyBlock,key);
    dataCopytoMatrix(ivBlock,iv);

    Mat newivBlock(NumberofBlocks,NumberofBlocks,CV_8UC1);
    uint8_t encrypted[NumberofBytes];

    // now calling the encryption function to encrypt our text
    for(int i=0;i<adjustedLength;i+=NumberofBytes)
    {
        newivBlock = XOR_CBC(ivBlock,adjustedData+i);
        matrixCopytoArray(newivBlock,encrypted);
        ivBlock = file_encryption(encrypted , keyBlock , encryptedData + i);
    }

    // now displaying the encrypted data 
    //PrintArrayWithRange(encryptedData,"The encrypted data is : ",adjustedLength);

    // Write the encrypted string out to file ""
	ofstream outfile;
	outfile.open("EncodedFile_CBC.txt", ios::out | ios::binary);
	if (outfile.is_open())
	{
		outfile.write((char *)encryptedData,adjustedLength);
		outfile.close();
		cout << endl << "Wrote encrypted message to file" << endl;
	}
	else
    {
        cout << "Unable to open file";
    }
}

Mat file_encryption(uint8_t data[],Mat key,uint8_t cipher[])
{
    // declaring 2d array to store 16 bytes of data recieved to be encrypted
    uint8_t plainText[NumberofBlocks][NumberofBlocks];

    dataCopyTo2dArray(plainText,data);

    // declaring Mat to copy the 16 bytes of data
    Mat block(NumberofBlocks, NumberofBlocks, CV_8UC1);
    
    // copying data
    dataCopytoMatrix(block,plainText);

    // encrypting data
    Mat encrypted_data = block_encryption(block,key);
    //PrintMatrix(encrypted_data,"The cipher text is : ");

    matrixCopytoArray(encrypted_data,cipher);

    return encrypted_data;
}


// for AES one block of data will be 16 bytes or 4x4 2d array
    
    /*
        practice data

        0x19, 0xa0, 0x9a, 0xe9,
        0x3d, 0xf4, 0xc6, 0xf8,
        0xe3, 0xe2, 0x8d, 0x48,
        0xbe, 0x2b, 0x2a, 0x08

        0x32, 0x88, 0x31, 0xe0,
        0x43, 0x5a, 0x31, 0x37,
        0xf6, 0x30, 0x98, 0x07,
        0xa8, 0x8d, 0xa2, 0x34
    

    uint8_t data[NumberofBlocks][NumberofBlocks] = 
    {
        0x32, 0x88, 0x31, 0xe0,
        0x43, 0x5a, 0x31, 0x37,
        0xf6, 0x30, 0x98, 0x07,
        0xa8, 0x8d, 0xa2, 0x34
    };

    /*
        practice keys

        0xa0, 0x88, 0x23, 0x2a,
        0xfa, 0x54, 0xa3, 0x6c,
        0xfe, 0x2c, 0x39, 0x76,
        0x17, 0xb1, 0x39, 0x05

        0x2b, 0x28, 0xab, 0x09,
        0x7e, 0xae, 0xf7, 0xcf,
        0x15, 0xd2, 0x15, 0x4f,
        0x16, 0xa6, 0x88, 0x3c

        0x00, 0x01, 0x02, 0x03,
        0x04, 0x05, 0x06, 0x07, 
        0x08, 0x09, 0x0a, 0x0b, 
        0x0c, 0x0d, 0x0e, 0x0f

        

    // 16 bytes of key or 128 bits of key
    uint8_t key[NumberofBlocks][NumberofBlocks] = 
    {
        0x2b, 0x28, 0xab, 0x09,
        0x7e, 0xae, 0xf7, 0xcf,
        0x15, 0xd2, 0x15, 0x4f,
        0x16, 0xa6, 0x88, 0x3c
    };

    // for CBC Mode declaing IV matrix
    uint8_t iv[NumberofBlocks][NumberofBlocks] = 
    {
        0x0f, 0x0f, 0x0f, 0x0f,
        0x0f, 0x0f, 0x0f, 0x0f,
        0x0f, 0x0f, 0x0f, 0x0f,
        0x0f, 0x0f, 0x0f, 0x0f,
    };

    Mat block(NumberofBlocks, NumberofBlocks, CV_8UC1);
    Mat keyBlock(NumberofBlocks, NumberofBlocks, CV_8UC1);
    Mat ivBlock(NumberofBlocks,NumberofBlocks,CV_8UC1);

    dataCopytoMatrix(block,data);
    dataCopytoMatrix(keyBlock,key);
    dataCopytoMatrix(ivBlock,iv);
    
    Mat encrypted_data = block_encryption(block,keyBlock);

    PrintMatrix(encrypted_data,"The ciphered value is");
*/