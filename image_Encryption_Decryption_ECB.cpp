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
    Mat fourCrossfourBlock;
    // here each channel of image will be encrypted 
    
    // we are recieving whole channel for image and key as arguments
    // first step is to pick 4x4 block from our image so that we can pass it to AES encryption block

    Mat encryptedBlock = Mat::zeros(rows - (rows % NumberofBlocks) + (rows % NumberofBlocks ? NumberofBlocks : 0),
    cols - (cols % NumberofBlocks) + (cols % NumberofBlocks ? NumberofBlocks : 0),CV_8UC1 );

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

    Mat decryptedBlock = Mat::zeros(rows - (rows % NumberofBlocks) + (rows % NumberofBlocks ? NumberofBlocks : 0),
    cols - (cols % NumberofBlocks) + (cols % NumberofBlocks ? NumberofBlocks : 0),CV_8UC1 );

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

    //cout<<"The rows and cols for enc "<<rows<<cols<<endl;

    Mat fourCrossfourBlock;
    // here each channel of image will be encrypted 
    
    // we are recieving whole channel for image and key as arguments
    // first step is to pick 4x4 block from our image so that we can pass it to AES encryption block

    Mat encryptedBlock = Mat::zeros(rows - (rows % NumberofBlocks) + (rows % NumberofBlocks ? NumberofBlocks : 0),
    cols - (cols % NumberofBlocks) + (cols % NumberofBlocks ? NumberofBlocks : 0),CV_8UC1 );

    //Mat encryptedBlock = Mat::zeros(rows,cols,CV_8UC1);
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

    //Mat decryptedBlock = Mat::zeros(rows - (rows % NumberofBlocks) + (rows % NumberofBlocks ? NumberofBlocks : 0),
    //cols - (cols % NumberofBlocks) + (cols % NumberofBlocks ? NumberofBlocks : 0),CV_8UC1 );

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




















// testing XOR function here

// testing purpose
//Mat encryptor(Mat data,Mat key,Mat iv);
//Mat decryptor(Mat data,Mat key,Mat iv);

/*
    Mat tile = EncodedImage(cv::Range(row,min(row+NumberofBlocks,EncodedImage.rows)),cv::Range(col,min(col+NumberofBlocks,EncodedImage.cols)));

    // 16 bytes of key or 128 bits of key

    // from here checking 8x8 block of data
    /*
    uint8_t test_block[8][8] = {
        {0x32, 0x88, 0x31, 0xe0, 0x31, 0x31, 0x88, 0x07},
        {0x43, 0x5a, 0x31, 0x37, 0x31, 0x31, 0x88, 0x07},
        {0xf6, 0x30, 0x98, 0x07, 0x31, 0x31, 0x88, 0x07},
        {0xa8, 0x8d, 0xa2, 0x34, 0x31, 0x31, 0x88, 0x07},
        {0xf6, 0x30, 0x98, 0x07, 0x35, 0x33, 0x88, 0x07},
        {0xf6, 0x30, 0x98, 0x07, 0x35, 0x33, 0x88, 0x07},
        {0xf6, 0x30, 0x98, 0x07, 0x35, 0x33, 0x88, 0x07},
        {0xf6, 0x30, 0x98, 0x07, 0x35, 0x33, 0x88, 0x07}
    };

    uint8_t key[NumberofBlocks][NumberofBlocks] = 
    {
        0x2b, 0x28, 0xab, 0x09,
        0x7e, 0xae, 0xf7, 0xcf,
        0x15, 0xd2, 0x15, 0x4f,
        0x16, 0xa6, 0x88, 0x3c
    };

    // for CBC Mode declaring IV matrix
    uint8_t iv[NumberofBlocks][NumberofBlocks] = 
    {
        {0xf4, 0x2f, 0xf3, 0xff},
        {0xdc, 0xdc, 0xdd, 0xdd},
        {0xab, 0x12, 0x34, 0x67},
        {0xa1, 0x45, 0x24, 0xc7}
    };

    Mat testData(8,8,CV_8UC1);
    Mat keyBlock(NumberofBlocks, NumberofBlocks, CV_8UC1);
    Mat ivBlock(NumberofBlocks,NumberofBlocks,CV_8UC1);
    dataCopytoMatrix8(testData,test_block);
    dataCopytoMatrix(keyBlock,key);
    dataCopytoMatrix(ivBlock,iv);
    */

/*
    Mat encryptedData = encryptor(testData,keyBlock,ivBlock);
    
    cout<<"The encrpyted data is"<<endl;
    for (int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            cout << std::hex << (int)encryptedData.at<uint8_t>(i, j) << " ";
        }
        cout<<endl;
    }
    cout<<endl<<endl;
    */
    /*
    Mat decryptedData = decryptor(encryptedData,keyBlock,ivBlock);

    cout<<"The decrpyted data is"<<endl;
    for (int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            cout << std::hex << (int)decryptedData.at<uint8_t>(i, j) << " ";
        }
        cout<<endl;
    }
    cout<<endl<<endl;
*/

