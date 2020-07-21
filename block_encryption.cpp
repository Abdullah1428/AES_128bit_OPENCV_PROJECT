/* 
    AES 128 Bit Project 
    implementation by Abdullah1428
    CS Project
*/

// This file will contain the whole algorithm and steps for encryption of data

#include "AES.hpp"

Mat block_encryption(Mat data,Mat key)
{
    // for 10 rounds and one initial round we will need different keys for encryption
    // so we will use AES keyExpansion concept to expand the key upto 176 bytes
    // 11 rounds  = 16 bytes for each round but first 16 bytes will be orignal key which will
    // be used in the inital Round
    // here we declare expandedKey array which will contain the expanded key of 176 bytes
    uint8_t expandedKey[NumberofBlocks * NumberofBlocks * (NumberofRounds + 1)];

    // passsing the key to be expanded by 176 bytes for all rounds and storing in expandedKey array
    // keyExpansion method wiil return a expanded key for all rounds consisting of 176 bytes
    
    key_Schedule(key, expandedKey);
    
    //PrintMatrix(keyBlock,"The orignal key is");
    //PrintExpandedKey(expandedKey, "The expanded key is");

    // now from here we will call AES encryption rounds to encrypt our data
    // first will be inital round where data and orignal cipher key will be XORED
    Mat state = addRoundKey(data,expandedKey); 
    //PrintMatrix(state,"after Initial Round");

    // total rounds = 10 by in one round Mix Column will not be called
    for (int i=1; i <= NumberofRounds-1; i++)
    {
        state = subByte(state);
        //PrintMatrix(state,"After Sub Byte");
        state = shiftRows(state);
        //PrintMatrix(state,"After Shift Rows");
        state = mixColumns(state);
        //PrintMatrix(state,"After Mix Column");
        state = addRoundKey(state, expandedKey + i * 16 );
        //PrintMatrix(state,"After add round key");
    }
    
    // final round without mix column
    state = subByte(state);
    state = shiftRows(state);
    state = addRoundKey(state, expandedKey + 160);

    return state;
}


