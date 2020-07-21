/* 
    AES 128 Bit Project 
    implementation by Abdullah1428
    CS Project
*/

// This file will contain the whole algorithm and steps for decryption of ciphered data

#include "AES.hpp"

Mat block_decryption(Mat data,Mat key) 
{
    // expanded key concept is just like explained in encryption
    // we will need 176 bytes of expanded key 
    uint8_t expandedKey[NumberofBlocks * NumberofBlocks * (NumberofRounds + 1)];

    //PrintMatrix(keyBlock,"The orignal key is");
    //PrintExpandedKey(expandedKey, "The expanded key is");

    // passsing the key to be expanded by 176 bytes for all rounds and storing in expandedKey array
    // keyExpansion method wiil return a expanded key for all rounds consisting of 176 bytes
    key_Schedule(key, expandedKey);

    // for here we will decypt the ciphered data back to orignal data
    // for decryption the expanded key will start from last
    Mat state = addRoundKey(data,expandedKey+160);
    //PrintMatrix(state,"after Initial Round");

    for (int i=NumberofRounds-1;i>=1;i--)
    {
        state = inverseSubByte(state);
        //PrintMatrix(state,"After Inverse Sub Byte");
        state = inverseShiftRows(state);
        //PrintMatrix(state,"After Inverse Shift Rows");
        state = addRoundKey(state,expandedKey + i * 16);
        //PrintMatrix(state,"After add round key");
        state = inverseMixColumns(state);
        //PrintMatrix(state,"After Inverse Mix Columns");
    }  

    state = inverseSubByte(state);
    state = inverseShiftRows(state);
    state = addRoundKey(state,expandedKey);

    return state;
}

