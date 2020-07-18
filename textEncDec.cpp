/* 
    AES 128 Bit Project 
    implementation by Abdullah1428
    CS Project
*/

#include "AES.hpp"

// encryption methods

uint8_t * file_Encryption_ECB(Mat keyBlock,int length,uint8_t * data,uint8_t * encryptedData)
{
    
    // now calling the encryption function to encrypt our text
    for(int i=0;i<length;i+=NumberofBytes)
    {
        file_encryption(data + i , keyBlock , encryptedData + i);
    }

    return encryptedData;
}

uint8_t * file_Encryption_CBC(Mat keyBlock,Mat ivBlock,int length,uint8_t * data,uint8_t * encryptedData)
{
    
    Mat newivBlock(NumberofBlocks,NumberofBlocks,CV_8UC1);
    uint8_t encrypted[NumberofBytes];

    // now calling the encryption function to encrypt our text
    for(int i=0;i<length;i+=NumberofBytes)
    {
        newivBlock = XOR_CBC(ivBlock,data+i);
        matrixCopytoArray(newivBlock,encrypted);
        ivBlock = file_encryption(encrypted , keyBlock , encryptedData + i);
    }
    return encryptedData;
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

// decryption methods

uint8_t * file_Decryption_ECB(Mat keyBlock,int length,uint8_t * cipheredData,uint8_t * decryptedData)
{
    // now calling the decryption function to decrypt our ciphered data
    for(int i=0;i<length;i+=NumberofBytes)
    {
        file_decryption(cipheredData + i , keyBlock , decryptedData + i);
    }

    return decryptedData;
}

uint8_t * file_Decryption_CBC(Mat keyBlock,Mat ivBlock,int length,uint8_t * cipheredData,uint8_t * decryptedData)
{
    Mat newdataBlock(NumberofBlocks,NumberofBlocks,CV_8UC1);
    uint8_t decrypted[NumberofBytes];

    // now calling the decryption function to decrypt our ciphered data
    for(int i=0;i<length;i+=NumberofBytes)
    {
        newdataBlock = file_decryption(cipheredData + i , keyBlock , decryptedData + i);
        matrixCopytoArray(newdataBlock,decrypted);
        ivBlock = XOR_CBC(ivBlock,decrypted);
        matrixCopytoArray(ivBlock,decryptedData+i);
        oneDcopytoMatrix(ivBlock,cipheredData+i);
        // dase block rawala che cipheredData+i block (Mat) ta copy ke)
    }

    //PrintArrayWithRange(decryptedData,"The orignal data is : ",length);
    return decryptedData;
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