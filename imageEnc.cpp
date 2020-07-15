/* 
    AES 128 Bit Project 
    implementation by Abdullah1428
    CS Project
*/
// this file contains the image encryption 

#include "AES.hpp"

void image_encryption(Mat block,Mat key,int x,int y,Mat encrypt);

void imageEnc ()
{
    // 16 bytes of key or 128 bits of key
    uint8_t key[NumberofBlocks][NumberofBlocks] = 
    {
        0x2b, 0x28, 0xab, 0x09,
        0x7e, 0xae, 0xf7, 0xcf,
        0x15, 0xd2, 0x15, 0x4f,
        0x16, 0xa6, 0x88, 0x3c
    };

    // copying our key to Mat
    Mat keyBlock(NumberofBlocks, NumberofBlocks, CV_8UC1);
    dataCopytoMatrix(keyBlock,key);

    // reading input image which must be named InputFile.jpg
    // our input image is 316 x 316

    Mat InputImage = imread("InputFile.jpg",IMREAD_COLOR);
    
    Mat splitChannels[3];
    Mat encrypted_splitChannels[3]

    split(InputImage, splitChannels);

    // calculating total pixels in the image
    int totalPixels = InputImage.rows * InputImage.cols;

    /*
    int adjustedPixels = totalPixels;

    if (adjustedPixels % 16 != 0)
    {
        adjustedPixels = (adjustedPixels/NumberofBytes+1)*NumberofBytes;
    }
    */



    // now reading 4x4 blocs from the image 
    for (int k=0; k<3; k++){
        for (int row=0;row<InputImage.rows;row+=NumberofBlocks)
        {
            for (int col=0;col<InputImage.cols;col+=NumberofBlocks)
            {
                // selecting 4x4 block now
                Mat tile(NumberofBlocks,NumberofBlocks,CV_8UC1);
                tile = splitChannels[k](cv::Range(row,min(row+NumberofBlocks,InputImage.rows)),cv::Range(col,min(col+NumberofBlocks,InputImage.cols)));
                
            image_encryption(tile,keyBlock,row,col,&encrypted_splitChannels[k]);
            }        
        }
    }
    
    Mat encrypted_image;

    merge(encrypted_splitChannels, 3, encrypted_image);

    imshow("EncryptedImage",encrypted_image);
    
    waitKey();
}

void image_encryption(Mat block,Mat key,int x,int y,Mat * encrypt)
{

    block = block_encryption(block,key);

    for(int r=x;r<x+NumberofBlocks;r++)
    {
        for(int c=y;c<y+NumberofBlocks;c++)
        {
            encrypt->at<uint8_t>(r,c) = block.at<uint8_t>(r,c);
        }
    }
}









