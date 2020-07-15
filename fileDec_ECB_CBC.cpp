/* 
    AES 128 Bit Project 
    implementation by Abdullah1428
    CS Project
*/

#include "AES.hpp"

void file_Decryption_ECB()
{
    stringstream cipherString;
    string cipherData;
	ifstream cipherfile;
	cipherfile.open("EncodedFile.txt", ios::in | ios::binary);
    if (cipherfile.is_open()) 
    {
        cipherString << cipherfile.rdbuf();
        cipherfile.close();
    }

    // displaying data stored in array
    cipherData = cipherString.str();

    // counting all characters in the file
    int x = 0;
    while(cipherData[x] != '\0')
    {
        x++;
    }
    //cout<<"The x value is "<<x<<endl;

    int limit = x;
    // declaring array for the data
    uint8_t cipheredData[limit];
    
    for (int i=0;i<limit;i++)
    {
        cipheredData[i] = cipherData[i];
    }

    int cipherLength = limit;
    //cout<<endl<<"The cipher length is "<<cipherLength<<endl;
    //cipherLength = cipherLength - 1;

    uint8_t decryptedData[cipherLength];

    /* 
        // printing the hex of data 
        // da for new line
    
    for(int i=0;i<sizeof(cipheredData);i++)
    {
        cout<<std::hex<<(int)cipheredData[i];
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

    // now calling the decryption function to decrypt our ciphered data
    for(int i=0;i<cipherLength;i+=NumberofBytes)
    {
        file_decryption(cipheredData + i , keyBlock , decryptedData + i);
    }

    //PrintArrayWithRange(decryptedData,"The orignal data is : ",cipherLength);

    ofstream outfile;
	outfile.open("DecodedFile.txt", ios::out | ios::binary);
	if (outfile.is_open())
	{
		outfile.write((char *)decryptedData,cipherLength);
		outfile.close();
		cout << endl << "Wrote decrypted message to file" << endl;
	}
	else
    {
        cout << "Unable to open file";
    }
}

void file_Decryption_CBC()
{
    stringstream cipherString;
    string cipherData;
	ifstream cipherfile;
	cipherfile.open("EncodedFile_CBC.txt", ios::in | ios::binary);
    if (cipherfile.is_open()) 
    {
        cipherString << cipherfile.rdbuf();
        cipherfile.close();
    }

    // displaying data stored in array
    cipherData = cipherString.str();

    // counting all characters in the file
    int x = 0;
    while(cipherData[x] != '\0')
    {
        x++;
    }

    int limit = x;

    //cout<<"The length value is "<<limit<<endl;

    // declaring array for the data
    uint8_t cipheredData[limit];
    
    for (int i=0;i<limit;i++)
    {
        cipheredData[i] = cipherData[i];
    }

    int cipherLength = limit;

    uint8_t decryptedData[cipherLength];

    /* 
        // printing the hex of data 
        // da for new line
    
    for(int i=0;i<sizeof(cipheredData);i++)
    {
        cout<<std::hex<<(int)cipheredData[i];
    }

    */
    
    // Now this is CBC Mode so we will need a initialization vector which
    // will be XORed with the data
    // for CBC Mode declaring IV matrix
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

    Mat newdataBlock(NumberofBlocks,NumberofBlocks,CV_8UC1);
    uint8_t decrypted[NumberofBytes];

    // now calling the decryption function to decrypt our ciphered data
    for(int i=0;i<cipherLength;i+=NumberofBytes)
    {
        newdataBlock = file_decryption(cipheredData + i , keyBlock , decryptedData + i);
        matrixCopytoArray(newdataBlock,decrypted);
        ivBlock = XOR_CBC(ivBlock,decrypted);
        matrixCopytoArray(ivBlock,decryptedData+i);
        oneDcopytoMatrix(ivBlock,cipheredData+i);
        // dase block rawala che cipheredData+i block (Mat) ta copy ke)
    }

    //PrintArrayWithRange(decryptedData,"The orignal data is : ",cipherLength);

    ofstream outfile;
	outfile.open("DecodedFile_CBC.txt", ios::out | ios::binary);
	if (outfile.is_open())
	{
		outfile.write((char *)decryptedData,cipherLength);
		outfile.close();
		cout << endl << "Wrote decrypted message to file" << endl;
	}
	else
    {
        cout << "Unable to open file";
    }
}

Mat file_decryption(uint8_t data[],Mat key,uint8_t plain[])
{
    // declaring 2d array to store 16 bytes of ciphered data recieved to be decrypted
    uint8_t cipherText[NumberofBlocks][NumberofBlocks];

    int index = 0;
    for (int row=0;row<NumberofBlocks;row++)
    {
        for(int col=0;col<NumberofBlocks;col++)
        {
            cipherText[row][col] = data[index];
            index++;
        }
    }

    // declaring Mat to copy the 16 bytes of data
    Mat cipherBlock(NumberofBlocks, NumberofBlocks, CV_8UC1);
    
    // copying data
    dataCopytoMatrix(cipherBlock,cipherText);

    // encrypting data
    Mat decrypted_data = block_decryption(cipherBlock,key);
    // PrintMatrix(decrypted_data,"The orignal text is : ");

    matrixCopytoArray(decrypted_data,plain);

    return decrypted_data;   
}

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


/*

// ciphered practice data 
    uint8_t cipherData[NumberofBlocks][NumberofBlocks] = 
    {
        0x39, 0x02, 0xdc, 0x19,
        0x25, 0xdc, 0x11, 0x6a,
        0x84, 0x09, 0x85, 0x0b,
        0x1d, 0xfb, 0x97, 0x32
    };
    
    // 16 bytes of key or 128 bits of key
    uint8_t key[NumberofBlocks][NumberofBlocks] = 
    {
        0x2b, 0x28, 0xab, 0x09,
        0x7e, 0xae, 0xf7, 0xcf,
        0x15, 0xd2, 0x15, 0x4f,
        0x16, 0xa6, 0x88, 0x3c
    };

    // creating 2 open CV matrix of 4x4 size
    Mat cipherBlock(NumberofBlocks, NumberofBlocks, CV_8UC1);
    Mat keyBlock(NumberofBlocks, NumberofBlocks, CV_8UC1);

    // copying the data from 2d arrays to matrix
    dataCopytoMatrix(cipherBlock, cipherData);
    dataCopytoMatrix(keyBlock, key);


    Mat decrypted_data = block_decryption(cipherBlock,keyBlock);

    PrintMatrix(decrypted_data,"The decrypted value is");
*/