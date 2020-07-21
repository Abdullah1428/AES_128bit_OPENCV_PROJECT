/* 
    AES 128 Bit Project 
    implementation by Abdullah1428
    CS Project
*/

// here all main libraries and different methods will be added that will be used in the project
#include <opencv2/opencv.hpp> // open cv library
#include <stdint.h> // for uint8_t types library
#include <iostream> // input output stream library
#include <sstream> // providing string stream classes library
#include <fstream> // for file handling library
#include <string> // for string operations
#include <math.h> // for math operations
#include <sys/time.h> // for calculating encoding and decoding time

using namespace std;
using namespace cv;

const int NumberofBlocks = 4;
const int NumberofRounds = 10;
const int NumberofBytes = NumberofBlocks * NumberofBlocks;

// Print functions methods
void PrintMatrix(Mat, const char *);
void PrintArray(uint8_t *, const char *);
void PrintArrayWithRange(uint8_t *, const char *,int);
void PrintExpandedKey(uint8_t *, const char *);
void horizontalBlocks(Mat,int,const char *);
void verticalBlocks(Mat,int,const char *);
// data copy methods
void dataCopytoMatrix(Mat, uint8_t array[4][4]);
void matrixCopytoArray(Mat,uint8_t []);
void dataCopyTo2dArray(uint8_t dest[4][4],uint8_t []);
void oneDcopytoMatrix (Mat,uint8_t []);
void dataCopytoMatrix8(Mat mat, uint8_t array[8][8]);

// first step key Schedule
void key_Schedule(Mat, uint8_t[]);

// method to be used for both encryption and decryption
Mat addRoundKey(Mat, uint8_t *);

// AES Encryption Rounds methods
Mat subByte(Mat);
Mat shiftRows(Mat);
Mat mixColumns(Mat);

// encryption method
Mat block_encryption(Mat,Mat);

// AES Decryption Rounds methods
Mat inverseSubByte(Mat);
Mat inverseShiftRows(Mat);
Mat inverseMixColumns(Mat);

// decryption method
Mat block_decryption(Mat,Mat);

// file encryption methods
Mat file_encryption(uint8_t [],Mat ,uint8_t []);
// ECB Mode
uint8_t * file_Encryption_ECB(Mat,int,uint8_t *,uint8_t *);
// CBC Mode
uint8_t * file_Encryption_CBC(Mat,Mat,int,uint8_t *,uint8_t *);

// for CBC mode XOR of IV and Plain Text
Mat XOR_CBC(Mat ,uint8_t []);

// file decryption methods
Mat file_decryption(uint8_t [],Mat ,uint8_t []);
// ECB Mode
uint8_t * file_Decryption_ECB(Mat,int,uint8_t *,uint8_t *);
// CBC Mode
uint8_t * file_Decryption_CBC(Mat,Mat,int,uint8_t *,uint8_t *);

// for image encryption and decryption in ECB and CBC mode
Mat XOR_CBC_Image(Mat,Mat); // iv and data block
Mat image_channel_encryption_ecb(Mat,Mat);
Mat image_channel_decryption_ecb(Mat,Mat);
Mat image_channel_encryption_cbc(Mat block,Mat key,Mat iv);
Mat image_channel_decryption_cbc(Mat block,Mat key,Mat iv);
// picking and placing 4x4 blocks
Mat image_block_getter(Mat,int,int);
void image_block_setter(Mat *,Mat,int,int);


// for arguments passed when running files
int program_args(int,char **,const char *);
// to get key in hex from the key file
Mat getKeyFile(const char *);

// to get text length and text from the ciphered file
int cipheredFileLength (const char *);
uint8_t * getTextFromCipheredFile(const char *, uint8_t *);

// to get text length and text from the input file
int getTextFileLength (const char *);
uint8_t * getTextFromInputFile(const char *, uint8_t *);