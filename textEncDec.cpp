/* 
    AES 128 Bit Project 
    implementation by Abdullah1428
    CS Project
*/

#include "AES.hpp"

// text file encryption methods

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

// text file decryption methods

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

    dataCopyTo2dArray(cipherText,data);
    
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


