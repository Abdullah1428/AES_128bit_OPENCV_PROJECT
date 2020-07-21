/* 
    AES 128 Bit Project 
    implementation by Abdullah1428
    CS Project
*/

#include "AES.hpp"
#include "lookup_tables.hpp"

void rotateLastFourBytes(uint8_t *);
void SboxValues(uint8_t *);

void key_Schedule(Mat keyState, uint8_t expandedKeys[NumberofBlocks * NumberofBlocks * (NumberofRounds + 1)])
{

    uint8_t lastFourBytes[NumberofBlocks];
    uint8_t RCON = 1;

    // here we have the key in Matrix so
    // now converting the Matrix key to one d array where key will
    // be arranged according to column wise so that we can pick it easily for key expansion porcess
    int index = 0;
    uint8_t singleArrayKey[NumberofBytes];

    matrixCopytoArray(keyState,singleArrayKey);

    // now the first 16 bytes in the expanded key will be orignal key so copy the orignal key to expanded key
    for (int i = 0; i < NumberofBlocks * NumberofBlocks; i++)
    {
        expandedKeys[i] = singleArrayKey[i];
    }

    /* printing the orignal key in the expanded key
    for (int i=0;i<16;i++) 
    {
        cout<<std::hex<<(int)expandedKeys[i]<<" ";
    }
    */

    // now 16 bytes are already filled so we will start from 17 byte or 16 location
    int doneBytes = NumberofBytes;
    int numberofBytes = NumberofBlocks * NumberofBlocks * (NumberofRounds + 1);
    while (doneBytes < numberofBytes)
    {

        /*
            for key generation few steps are required
            1) pick last 4 bytes and give a left rotation to the bytes
            2) now for the rotated bytes find SBOX values from the lookup table for SBOX
            3) now pick first 4 bytes from the key, then pick first column from RCON table 
            4) now XOR the first 4 bytes, RCON column value and the SBOX value column
            5) result generated from these 4 bytes will be the first column of the new 4 bytes for round 1 key
            6) now for rest 3 bytes of the round 1 key 
                for 2 byte => take the new column generated in round 1 key and 2 column from first 16 bytes and XOR it
                for 3 byte => take the 2 column generated in round 1 key and 3 column from first 16 bytes and XOR it
                for 4 byte => take the 3 column generated in round 1 key and 4 column from first 16 bytes and XOR it

            and tadahhhh!! key generated
            could it be any easier??

            repeat these steps to generate keys for all rounds so a total 176 bytes of expanded key will be generated
            which will be then added with each round in the addRoundKey step of encyption  

        */

        // picking last 4 bytes
        for (int x = 0; x < NumberofBlocks; x++)
        {
            lastFourBytes[x] = expandedKeys[x + doneBytes - NumberofBlocks];
        }

        // we know that this step has to be only repeated at the start of new round key
        // so we can generate a condition here that only repeat these steps when we are the start of new
        // round key generation

        if (doneBytes % NumberofBytes == 0)
        {
            rotateLastFourBytes(lastFourBytes);
            /* printing last four bytes after rotation
            cout<<endl<<"Last four bytes or last column after rotaation "<<endl;
    	    for (int i=0;i<4;i++) 
    	    {
        	    cout<<std::hex<<(int)lastFourBytes[i]<<" ";
    	    }
            */
            SboxValues(lastFourBytes);
            /* printing last four bytes after SBOX values
            cout<<endl<<"Last four bytes or last column after sbox"<<endl;
    	    for (int i=0;i<4;i++) 
    	    {
        	    cout<<std::hex<<(int)lastFourBytes[i]<<" ";
    	    }
            */

            // picking the RCON value
            lastFourBytes[0] = lastFourBytes[0] ^ rcon[RCON];
            RCON++;
            /* printing newly generated first column of the round key
            cout<<endl<<"Last four bytes or last column after rcon"<<endl;
    	    for (int i=0;i<4;i++) 
    	    {
        	    cout<<std::hex<<(int)lastFourBytes[i]<<" ";
    	    }
            */
        }

        // now generating last 3 bytes
        for (uint8_t z = 0; z < NumberofBlocks; z++)
        {
            expandedKeys[doneBytes] = expandedKeys[doneBytes - NumberofBytes] ^ lastFourBytes[z];
            doneBytes++;
        }
        /* prining the 176 bytes of keys generated at each step
        cout<<endl<<"Expanded Keys after generating new row"<<endl;
        for (int i=0;i<176;i++) 
        {
            cout<<std::hex<<(int)expandedKeys[i]<<" ";
        }
        */

        // now this process will repeat and all keys for all the rounds will be generated
    }
}

// method for roatation of the last four bytes picked
void rotateLastFourBytes(uint8_t *bytes)
{
    uint8_t temp = bytes[0];
    bytes[0] = bytes[1];
    bytes[1] = bytes[2];
    bytes[2] = bytes[3];
    bytes[3] = temp;
}

// method for Sbox values
void SboxValues(uint8_t *bytes)
{
    for (int i = 0; i < NumberofBlocks; i++)
    {
        bytes[i] = sbox[bytes[i] / 16][bytes[i] % 16];
    }
}
