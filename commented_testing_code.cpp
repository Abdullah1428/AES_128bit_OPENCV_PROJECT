/* 
    AES 128 Bit Project 
    implementation by Abdullah1428
    CS Project
*/
// this file contains the image encryption decryption for CBC mode

//#include "AES.hpp"

/*
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

    
    horizontalBlocks(encryptedColorChannels[0],3,"3 horizontal blocks for encrypted image channel 0");
    verticalBlocks(encryptedColorChannels[0],3,"3 vertical blocks for encrypted image channel 0");
    
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

*/

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

// 3 horizontal blocks
/*
void horizontalBlocks(Mat matrix, int size, const char * sentence)
{
    cout << endl << sentence << endl;

    int coll = 0;
    int horizontal_Condition = 4;

    for(int k = 0; k < size; k++) 
    {
        for (int row = 0; row < NumberofBlocks; row++)
        {
            for (int col = coll; col < horizontal_Condition; col++)
            {
                cout << std::hex << (int)matrix.at<uint8_t>(row, col) << " ";
            }
            cout << endl;
        }
        cout<<endl;
        horizontal_Condition += 4;
        coll+=4;
    }
}

// 3 vertical blocks
void verticalBlocks(Mat matrix, int size, const char * sentence)
{
    cout << endl << sentence << endl;

    int roww = 0;
    int vertical_Condition = 4;

    for(int k = 0; k < size; k++) 
    {
        for (int row = roww; row < vertical_Condition; row++)
        {
            for (int col = 0; col < NumberofBlocks; col++)
            {
                cout << std::hex << (int)matrix.at<uint8_t>(row, col) << " ";
            }
            cout << endl;
        }
        cout<<endl;
        vertical_Condition += 4;
        roww+=4;
    }
}
*/