/* 
    AES 128 Bit Project 
    implementation by Abdullah1428
    CS Project
*/
// this file contains the image encryption decryption for ECB mode

#include "AES.hpp"

Mat image_channel_encryption_ecb(Mat block,Mat key)
{
    int rows = block.rows;
    int cols = block.cols;

    if(rows % 4 != 0)
    {
        rows = (rows/NumberofBlocks + 1)*NumberofBlocks;
    }

    if(cols % 4 != 0)
    {
        cols = (cols/NumberofBlocks + 1)*NumberofBlocks;
    }

    Mat fourCrossfourBlock;
    // here each channel of image will be encrypted 
    
    // we are recieving whole channel for image and key as arguments
    // first step is to pick 4x4 block from our image so that we can pass it to AES encryption block
    
    Mat encryptedBlock = Mat::zeros(rows,cols,CV_8UC1);

    for(int i=0;i<rows;i+=NumberofBlocks)
    {
        for(int j=0;j<cols;j+=NumberofBlocks)
        {
            // picking 4x4 block here
            fourCrossfourBlock = image_block_getter(block,j,i);
            // encrypting the block
            fourCrossfourBlock =  block_encryption(fourCrossfourBlock,key);
            // copy the resultant block to encrypted block
            image_block_setter(&encryptedBlock,fourCrossfourBlock,j,i);
        }
    } 
    return encryptedBlock;
}

Mat image_channel_decryption_ecb(Mat block,Mat key)
{
    int rows = block.rows;
    int cols = block.cols;
    Mat fourCrossfourBlock;
    // here each channel of image will be encrypted 
    
    // we are recieving whole channel for image and key as arguments
    // first step is to pick 4x4 block from our image so that we can pass it to AES encryption block

    Mat decryptedBlock = Mat::zeros(rows,cols,CV_8UC1);

    for(int i=0;i<rows;i+=NumberofBlocks)
    {
        for(int j=0;j<cols;j+=NumberofBlocks)
        {
            // picking 4x4 block here
            fourCrossfourBlock = image_block_getter(block,j,i);
            // decrypting the block
            fourCrossfourBlock =  block_decryption(fourCrossfourBlock,key);
            // copy the resultant block to decrypted block
            image_block_setter(&decryptedBlock,fourCrossfourBlock,j,i);
        }
    } 
    return decryptedBlock;
}

Mat image_channel_encryption_cbc(Mat block,Mat key,Mat iv)
{
    int rows = block.rows;
    int cols = block.cols;

    if(rows % 4 != 0)
    {
        rows = (rows/NumberofBlocks + 1)*NumberofBlocks;
    }

    if(cols % 4 != 0)
    {
        cols = (cols/NumberofBlocks + 1)*NumberofBlocks;
    }

    //cout<<"Rows are : "<<rows<<" and Cols are : "<<cols;

    //cout<<"The rows and cols for enc "<<rows<<cols<<endl;

    Mat fourCrossfourBlock;
    // here each channel of image will be encrypted 
    
    // we are recieving whole channel for image and key as arguments
    // first step is to pick 4x4 block from our image so that we can pass it to AES encryption block

    Mat encryptedBlock = Mat::zeros(rows,cols,CV_8UC1);
    
    for(int i = 0; i < rows; i+=NumberofBlocks)
    {
        for(int j = 0; j < cols; j+=NumberofBlocks)
        {
            // picking 4x4 block here
            fourCrossfourBlock = image_block_getter(block,j,i);

            /*         
            //orignal data block picking
            if(i == 4 && j == 4)
            {
                PrintMatrix(fourCrossfourBlock,"The orignal data");
            }
            */            
            // xor data with iv block
            fourCrossfourBlock = XOR_CBC_Image(iv,fourCrossfourBlock);
            // encrypting the block
            fourCrossfourBlock =  block_encryption(fourCrossfourBlock,key);

            /*
            //encrypted block checking with picked block in decrypting 
            if(i == 64 && j == 64)
            {
                PrintMatrix(fourCrossfourBlock,"The encrypted block");
            }
            */

            // update iv block for next iteration
            iv = fourCrossfourBlock;
            // copy the resultant block to encrypted block
            image_block_setter(&encryptedBlock,fourCrossfourBlock,j,i);  
        } 
    } 
    return encryptedBlock;
}

Mat image_channel_decryption_cbc(Mat block,Mat key,Mat iv)
{

    //PrintMatrix(key,"This is key block");
    //PrintMatrix(iv,"This is iv block");

    int rows = block.rows;
    int cols = block.cols;

    //cout<<"The rows and cols for dec "<<rows<<cols<<endl;
    
    Mat fourCrossfourBlock;
    Mat temp;
    Mat decryptedBlockiv;
    // here each channel of image will be encrypted 
    
    // we are recieving whole channel for image and key as arguments
    // first step is to pick 4x4 block from our image so that we can pass it to AES encryption block

    Mat decryptedBlock = Mat::zeros(rows,cols,CV_8UC1);

    for(int i = 0; i < rows; i+=NumberofBlocks)
    {
        for(int j = 0; j < cols; j+=NumberofBlocks)
        {
            temp = image_block_getter(block,j,i);
            // picking 4x4 block here
            fourCrossfourBlock = image_block_getter(block,j,i);

            /*
            // picking right data
            if(i == 64 && j == 64)
            {
                PrintMatrix(fourCrossfourBlock,"The picked block");
            }
            */
            // decrypting the block using cbc mode
            decryptedBlockiv =  block_decryption(fourCrossfourBlock,key);
            // xor decrypted block with iv

            /*
            if(i == 4 && j == 4)
            {
                PrintMatrix(iv,"This is iv Matrix");
                PrintMatrix(decryptedBlockiv,"This is decrypted block");
            }
            */

            decryptedBlockiv = XOR_CBC_Image(iv,decryptedBlockiv);

            /*
                // here orignal data back should display

            if(i == 4 && j == 4)
            {
                PrintMatrix(decryptedBlockiv,"is this orignal data back?");
            }

            */
            

            // updating iv
            iv = temp;
            // copy decrypted block to fourcrossfour for storing
            fourCrossfourBlock = decryptedBlockiv;
            
            /*
            //decrypted block matches with first picked block for encryption
            if(i == 0 && j == 0)
            {
                PrintMatrix(fourCrossfourBlock,"The first decrypted block of image");
            }
            */

            // copy the resultant block to decrypted block
            image_block_setter(&decryptedBlock,fourCrossfourBlock,j,i);

            /*
            // storing correctly in decrypted block
            if(i == 0 && j == 0)
            {
                PrintMatrix(decryptedBlock,"The first decrypted block of image");
            }
            */
        }
    } 
    return decryptedBlock;
}