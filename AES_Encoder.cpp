/* 
    AES 128 Bit Project 
    implementation by Abdullah1428
    CS Project
*/

#include "AES.hpp"

// testing purpose
Mat encryptor(Mat data,Mat key,Mat iv);
Mat decryptor(Mat data,Mat key,Mat iv);

int main(int argc, char **argv)
{
    //file_Encryption_ECB();
    
    //file_Encryption_CBC();

    //image_Encryption_Decryption_ECB();

    image_Encryption_Decryption_CBC();

    return 0;
}

// testing XOR function here

/*
    Mat tile = EncodedImage(cv::Range(row,min(row+NumberofBlocks,EncodedImage.rows)),cv::Range(col,min(col+NumberofBlocks,EncodedImage.cols)));

    // 16 bytes of key or 128 bits of key
    /*
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

    uint8_t keyarray[NumberofBytes];

    matrixCopytoArray(keyBlock,keyarray);

    Mat result1 = XOR_CBC_Image(ivBlock,keyBlock);

    Mat result2 = XOR_CBC(ivBlock,keyarray);

    PrintMatrix(result1,"This is result 1");
    PrintMatrix(result2,"This is result 2");
    */


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


/*
Mat encryptor(Mat data,Mat key,Mat iv)
{
    Mat FourCrossFourBlock;

    Mat encryptedBlock = Mat::zeros(8,8,CV_8UC1);

    for(int i=0;i<8;i+=NumberofBlocks)
    {
        for(int j=0;j<8;j+=NumberofBlocks)
        {
            FourCrossFourBlock = data(cv::Range(i,min(i+NumberofBlocks,8)),cv::Range(j,min(j+NumberofBlocks,8)));
            //FourCrossFourBlock = image_block_getter(data,j,i);
            PrintMatrix(FourCrossFourBlock,"This is 4x4 block picker");
              
            FourCrossFourBlock = XOR_CBC_Image(iv,FourCrossFourBlock);
            //PrintMatrix(FourCrossFourBlock,"This is after CBC with iv");
            FourCrossFourBlock =  block_encryption(FourCrossFourBlock,key);
            //PrintMatrix(FourCrossFourBlock,"This is after encryption"); 
            iv = FourCrossFourBlock;
            //PrintMatrix(iv,"This is new iv");
            image_block_setter(&encryptedBlock,FourCrossFourBlock,j,i);
        }
    }

    return encryptedBlock;

}
*/
/*

Mat decryptor(Mat data,Mat key,Mat iv)
{
    Mat FourCrossFourBlock;
    Mat decryptedBlockiv;
    Mat temp;

    Mat decryptedBlock = Mat::zeros(8,8,CV_8UC1);

    for(int i=0;i<8;i+=NumberofBlocks)
    {
        for(int j=0;j<8;j+=NumberofBlocks)
        {
            FourCrossFourBlock = data(cv::Range(i,min(i+NumberofBlocks,8)),cv::Range(j,min(j+NumberofBlocks,8)));
            //temp = image_block_getter(data,j,i);
            //FourCrossFourBlock = image_block_getter(data,j,i);
            //PrintMatrix(FourCrossFourBlock,"This is 4x4 block picker of enc data"); 
            decryptedBlockiv = block_decryption(FourCrossFourBlock,key);
            //PrintMatrix(decryptedBlockiv,"This is after decryption function");
            decryptedBlockiv = XOR_CBC_Image(iv,decryptedBlockiv);
            //PrintMatrix(decryptedBlockiv,"This is after XOR");
            iv = temp;
            //PrintMatrix(iv,"Updated iv");
            FourCrossFourBlock = decryptedBlockiv; 
            //PrintMatrix(FourCrossFourBlock,"Updated this should be orignal text now");
            image_block_setter(&decryptedBlock,FourCrossFourBlock,j,i);
        }
    }
    return decryptedBlock;
}

*/