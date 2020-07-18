/* 
    AES 128 Bit Project 
    implementation by Abdullah1428
    CS Project
*/
// this file contains the image encryption decryption for CBC mode

#include "AES.hpp"

Mat image_channel_encryption(Mat,Mat,Mat);
Mat image_channel_decryption(Mat,Mat,Mat);

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
        {0x32, 0x88, 0x31, 0xe0},
        {0x43, 0x5a, 0x31, 0x37},
        {0xf6, 0x30, 0x98, 0x07},
        {0xa8, 0x8d, 0xa2, 0x34}
    };
    
    // copying our key to Mat
    Mat keyBlock(NumberofBlocks, NumberofBlocks, CV_8UC1);
    Mat ivBlock(NumberofBlocks,NumberofBlocks,CV_8UC1);
    dataCopytoMatrix(keyBlock,key);
    dataCopytoMatrix(ivBlock,iv);

    // reading input image which must be named InputFile.jpg
    // our input image is 316 x 316
    Mat InputImage = imread("files/linux.jpg",IMREAD_COLOR);

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

    /*
    horizontalBlocks(encryptedColorChannels[0],3,"3 horizontal blocks for encrypted image channel 0");
    verticalBlocks(encryptedColorChannels[0],3,"3 vertical blocks for encrypted image channel 0");
    */
    //PrintMatrix(imageColorChannels[0],"The imageColorChannel 0");
    //PrintMatrix(imageColorChannels[1],"The imageColorChannel 1");
    //PrintMatrix(imageColorChannels[2],"The imageColorChannel 2");
    // Mat which will contain the final encrypted image after merging
    Mat encryptedImage;

    merge(encryptedColorChannels,3,encryptedImage);

    imwrite("files/EncryptedImage_CBC.jpg",encryptedImage);

    imshow("EncryptedImage",encryptedImage);

    for(int channel = 0 ; channel < 3 ; channel++)
    {
        decryptedColorChannels[channel] = image_channel_decryption(encryptedColorChannels[channel],keyBlock,ivBlock); 
    }

    /*
        // debugging the values to see the correct output values

    horizontalBlocks(imageColorChannels[0],3,"3 horizontal blocks for orignal image channel 0");
    horizontalBlocks(decryptedColorChannels[0],3,"3 horizontal blocks for decrypted image channel 0");
    verticalBlocks(imageColorChannels[0],3,"3 vertical blocks for orignal image channel 0");
    verticalBlocks(decryptedColorChannels[0],3,"3 vertical blocks for decrypted image channel 0");

    horizontalBlocks(imageColorChannels[1],3,"3 horizontal blocks for orignal image channel 1");
    horizontalBlocks(decryptedColorChannels[1],3,"3 horizontal blocks for decrypted image channel 1");
    verticalBlocks(imageColorChannels[1],3,"3 vertical blocks for orignal image channel 1");
    verticalBlocks(decryptedColorChannels[1],3,"3 vertical blocks for decrypted image channel 1");

    horizontalBlocks(imageColorChannels[1],3,"3 horizontal blocks for orignal image channel 2");
    horizontalBlocks(decryptedColorChannels[1],3,"3 horizontal blocks for decrypted image channel 2");
    verticalBlocks(imageColorChannels[1],3,"3 vertical blocks for orignal image channel 2");
    verticalBlocks(decryptedColorChannels[1],3,"3 vertical blocks for decrypted image channel 2");

    */
    //PrintMatrix(decryptedColorChannels[0],"The decryptedColorChannel 0");
    //PrintMatrix(decryptedColorChannels[1],"The decryptedColorChannel 1");
    //PrintMatrix(decryptedColorChannels[2],"The decryptedColorChannel 2");
    // Mat which will contain the final encrypted image after merging
    Mat decryptedImage;

    merge(decryptedColorChannels,3,decryptedImage);

    imwrite("files/decryptedImage_CBC.jpg",decryptedImage);

    //Mat decrypt = imread("decryptedImage.jpg",IMREAD_COLOR);

    imshow("decrypted image",decryptedImage);

    waitKey();

}

