/* 
    AES 128 Bit Project 
    implementation by Abdullah1428
    CS Project
*/
// this file contains the image encryption decryption for CBC mode

#include "AES.hpp"

Mat image_channel_encryption(Mat,Mat,Mat);
Mat image_channel_decryption(Mat,Mat,Mat);
Mat image_block_getter(Mat,int,int);
void image_block_setter(Mat *,Mat,int,int);
Mat XOR_CBC_Image(Mat,Mat);

void image_Encryption_Decryption_CBC()
{
    // 16 bytes of key or 128 bits of key
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
        0x0f, 0x0f, 0x0f, 0x0f,
        0x0f, 0x0f, 0x0f, 0x0f,
        0x0f, 0x0f, 0x0f, 0x0f,
        0x0f, 0x0f, 0x0f, 0x0f,
    };
    
    // copying our key to Mat
    Mat keyBlock(NumberofBlocks, NumberofBlocks, CV_8UC1);
    Mat ivBlock(NumberofBlocks,NumberofBlocks,CV_8UC1);
    dataCopytoMatrix(keyBlock,key);
    dataCopytoMatrix(ivBlock,iv);

    // reading input image which must be named InputFile.jpg
    // our input image is 316 x 316
    Mat InputImage = imread("InputFile.jpg",IMREAD_COLOR);

    // now as we know color image has 3 colors in it R G B
    // so we will be needing to split each color from the image and then
    // encrypt it and after that we will decrypt each color and then again merge to form orignal image
    // so fot that purpose we will use open CV split and merge functions

    Mat imageColorChannels[3]; // r g b
    Mat encryptedColorChannels[3];
    Mat decryptedColorChannels[3];

    // now spliting 
    split(InputImage,imageColorChannels);

    // now encrypting each channel
    for(int channel = 0 ; channel < 3 ; channel++)
    {
        encryptedColorChannels[channel] = image_channel_encryption(imageColorChannels[channel],keyBlock,ivBlock); 
    }

    // Mat which will contain the final encrypted image after merging
    Mat encryptedImage;

    merge(encryptedColorChannels,3,encryptedImage);

    //imwrite("EncryptedImage.jpg",encryptedImage);

    imshow("EncryptedImage",encryptedImage);

    for(int channel = 0 ; channel < 3 ; channel++)
    {
        decryptedColorChannels[channel] = image_channel_decryption(encryptedColorChannels[channel],keyBlock,ivBlock); 
    }

    // Mat which will contain the final encrypted image after merging
    Mat decryptedImage;

    merge(decryptedColorChannels,3,decryptedImage);

    //imwrite("decryptedImage",decryptedImage);

    imshow("decryptedImage",decryptedImage);

    waitKey();

}


Mat image_channel_encryption(Mat block,Mat key,Mat iv)
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
            // xor data with iv block
            fourCrossfourBlock = XOR_CBC_Image(iv,fourCrossfourBlock);
            // encrypting the block
            fourCrossfourBlock =  block_encryption(fourCrossfourBlock,key);
            // update iv block for next iteration
            iv = fourCrossfourBlock;
            // copy the resultant block to encrypted block
            image_block_setter(&encryptedBlock,fourCrossfourBlock,j,i);
        } 
    } 
    return encryptedBlock;
}

Mat image_channel_decryption(Mat block,Mat key,Mat iv)
{
    int rows = block.rows;
    int cols = block.cols;
    Mat fourCrossfourBlock;
    Mat decryptedBlockiv;
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
            decryptedBlockiv =  block_decryption(fourCrossfourBlock,key);
            // xor decrypted block with iv
            decryptedBlockiv = XOR_CBC_Image(iv,decryptedBlockiv);
            // updating iv
            iv = fourCrossfourBlock;
            // updating data block
            fourCrossfourBlock = decryptedBlockiv;
            // copy the resultant block to decrypted block
            image_block_setter(&decryptedBlock,fourCrossfourBlock,j,i);
        }
    } 
    return decryptedBlock;
}

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




