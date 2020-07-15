/* 
    AES 128 Bit Project 
    implementation by Abdullah1428
    CS Project
*/
// this file contains the image encryption 

#include "AES.hpp"

Mat image_channel_encryption(Mat,Mat);
Mat image_channel_decryption(Mat,Mat);
Mat image_block_getter(Mat,int,int);
void image_block_setter(Mat *,Mat,int,int);

void image_Encryption_Decryption()
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
        encryptedColorChannels[channel] = image_channel_encryption(imageColorChannels[channel],keyBlock); 
    }

    // Mat which will contain the final encrypted image after merging
    Mat encryptedImage;

    merge(encryptedColorChannels,3,encryptedImage);

    //imwrite("EncryptedImage.jpg",encryptedImage);

    imshow("EncryptedImage",encryptedImage);

    for(int channel = 0 ; channel < 3 ; channel++)
    {
        decryptedColorChannels[channel] = image_channel_decryption(encryptedColorChannels[channel],keyBlock); 
    }

    // Mat which will contain the final encrypted image after merging
    Mat decryptedImage;

    merge(decryptedColorChannels,3,decryptedImage);

    //imwrite("EncryptedImage",encryptedImage);

    imshow("decryptedImage",decryptedImage);

    waitKey();

}


Mat image_channel_encryption(Mat block,Mat key)
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

Mat image_channel_decryption(Mat block,Mat key)
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
            // encrypting the block
            fourCrossfourBlock =  block_decryption(fourCrossfourBlock,key);
            // copy the resultant block to encrypted block
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




/*
    // dubugging for picking 4x4 blocks of images and large sets of data

    uint8_t test_block[8][8] = {
        {0x32, 0x88, 0x31, 0xe0, 0x31, 0x31, 0x88, 0x07},
        {0x43, 0x5a, 0x31, 0x37, 0x31, 0x31, 0x88, 0x07},
        {0xf6, 0x30, 0x98, 0x07, 0x31, 0x31, 0x88, 0x07},
        {0xa8, 0x8d, 0xa2, 0x34, 0x31, 0x31, 0x88, 0x07},
        {0xf6, 0x30, 0x98, 0x07, 0x31, 0x31, 0x88, 0x07},
        {0xf6, 0x30, 0x98, 0x07, 0x31, 0x31, 0x88, 0x07},
        {0xf6, 0x30, 0x98, 0x07, 0x31, 0x31, 0x88, 0x07},
        {0xf6, 0x30, 0x98, 0x07, 0x31, 0x31, 0x88, 0x07}
    };

    // creating a test data
    Mat test_data(8, 8, CV_8UC1);
    dataCopytoMatrix8(test_data,test_block);


// now reading 4x4 blocs from the image 
    for (int row=0;row<8;row+=NumberofBlocks)
    {
        for (int col=0;col<8;col+=NumberofBlocks)
        {
            // selecting 4x4 block now
            Mat tile(NumberofBlocks,NumberofBlocks,CV_8UC1);
            //tile = slice_of_data(InputImage,col,row);   //this should extract 4x4 block from inputimage
            tile = test_data(cv::Range(row,min(row+NumberofBlocks,8)),cv::Range(col,min(col+NumberofBlocks,8)));
            
            //    print tile to console to make sure you are getting the right values
            
            //PrintMatrix(tile,"Tile value");
            //image_encryption(tile,keyBlock,row,col,EncodedImage);
            //tile = slice_of_data(test_data,col,row);   //this should extract 4x4 block from inputimage
            //cout<<"tile :"<<endl;
            //log_block(tile);
           //image_encryption(tile,keyBlock,row,col,EncodedImage);

        }        
    }

Mat slice_of_data(Mat data, int x, int y){
    Mat block(4,4,CV_8UC1);
    block = Mat::zeros(4,4,CV_8UC1);
    for (int i=y; i<(y+NumberofBlocks); i++){
        for (int j=x; j<(x+NumberofBlocks); j++){
            if (i<data.rows && j<data.cols){
                block.at<uint8_t>(i-y,j-x) = data.at<uint8_t>(i,j);
            }
        }
    }
    return block;
}

void log_block(Mat block){
    for (int i=0; i<block.rows; i++){
        for (int j=0; j<block.cols; j++){
            cout<<std::hex<<(int)block.at<uint8_t>(i,j)<<' ';
        }
        cout<<endl;
    } 

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

*/



