/* 
    AES 128 Bit Project 
    implementation by Abdullah1428
    CS Project
*/
// this file contains the image encryption 

#include "AES.hpp"

void image_encryption(Mat block,Mat key,int x,int y,Mat encrypt);

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

    // copying our key to Mat
    Mat keyBlock(NumberofBlocks, NumberofBlocks, CV_8UC1);
    dataCopytoMatrix(keyBlock,key);

    // reading input image which must be named InputFile.jpg
    // our input image is 316 x 316

    Mat InputImage = imread("InputFile.jpg",IMREAD_GRAYSCALE);
    Mat EncodedImage(InputImage.rows,InputImage.cols,CV_8UC1);

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
    for (int row=0;row<8;row+=NumberofBlocks)
    {
        for (int col=0;col<8;col+=NumberofBlocks)
        {
            // selecting 4x4 block now
            Mat tile(NumberofBlocks,NumberofBlocks,CV_8UC1);
            //tile = slice_of_data(InputImage,col,row);   //this should extract 4x4 block from inputimage
            tile = test_data(cv::Range(row,min(row+NumberofBlocks,8)),cv::Range(col,min(col+NumberofBlocks,8)));
            /*
                print tile to console to make sure you are getting the right values
            */
            //PrintMatrix(tile,"Tile value");
            //image_encryption(tile,keyBlock,row,col,EncodedImage);
            //tile = slice_of_data(test_data,col,row);   //this should extract 4x4 block from inputimage
            cout<<"tile :"<<endl;
            log_block(tile);
           //image_encryption(tile,keyBlock,row,col,EncodedImage);

        }        
    }

   // imshow("EncryptedImage",EncodedImage);
    
    waitKey();
}

void image_encryption(Mat block,Mat key,int x,int y,Mat encrypt)
{

    block = block_encryption(block,key);

    for(int r=x;r<x+NumberofBlocks;r++)
    {
        for(int c=y;c<y+NumberofBlocks;c++)
        {
            encrypt.at<uint8_t>(r,c) = block.at<uint8_t>(r,c);
        }
    }
}









