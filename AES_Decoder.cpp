/* 
    AES 128 Bit Project 
    implementation by Abdullah1428
    CS Project
*/
#include "AES.hpp"

int main(int argc, char ** argv)
{

    if(!program_args(argc,argv,"-file") || (!program_args(argc,argv,"-ecb")) && (!program_args(argc,argv,"-cbc")) || (!program_args(argc,argv,"-key")) || (!program_args(argc,argv,"-cbc")) && (!program_args(argc,argv,"-iv")) )
    {
        cout<<"Please provide correct arguments";
        cout<<"The correct format to pass arguments are"<<endl;
        cout<<"AES_Decoder.exe -file EncodedFile.txt/EncodedFile.jpg -ecb/cbc -key keyFile.txt (for cbc) -iv ivFile.txt"<<endl;
        
        // exit
        return 1;
    }

    const char * file = argv[program_args(argc,argv,"-file")+1];
    const char * keyFile = argv[program_args(argc,argv,"-key")+1];
    const char * ivFile = argv[program_args(argc,argv,"-iv")+1]; 
    
    if (strstr(file,".txt")==NULL && strstr(file,".png")==NULL && strstr(file,".jpg")==NULL)
    {
        cout<<"Please provide a txt, jpg or png file to decrypt"<<endl;
        return 1;
    }

    if(strstr(file,".txt")!=NULL)
    {
        // here Encoded file decryption will be done
        int fileLength = getTextFileLength(file);

        if(fileLength == 0)
        {
            // file could not be read
            return 1;
        }

        // getting the key from the text file
        Mat keyBlock = getKeyFile("keyFile.txt");

        // data will hold the orignal text
        uint8_t * data = new uint8_t[fileLength];
        // encrypted data will hold the ciphered text
        uint8_t * decryptedData = new uint8_t[fileLength];

        // reading data from input file
        data = getTextFromInputFile(file,data);

        struct timeval startTime , stopTime;

        if(program_args(argc,argv,"-ecb"))
        {
            // ecb mode
            // starting time
            gettimeofday(&startTime, NULL);
            // encrypting data using ecb mode
            decryptedData = file_Decryption_ECB(keyBlock,fileLength,data,decryptedData);
            // end time
            gettimeofday(&stopTime, NULL);
        }
        else
        {
            // cbc mode
            // starting time
            gettimeofday(&startTime, NULL);
            Mat ivBlock = getKeyFile(ivFile);
            // encrypting data using cbc mode
            decryptedData = file_Decryption_CBC(keyBlock,ivBlock,fileLength,data,decryptedData);
            // end time
            gettimeofday(&stopTime, NULL);
        }
        
        ofstream outfile;
	    outfile.open("files/DecodedFile.txt", ios::out | ios::binary);
	    if (outfile.is_open())
	    {
		    outfile.write((char *)decryptedData,fileLength);
		    outfile.close();
		    cout << endl << "Wrote decrypted message to file DecodedFile in files folder" << endl;
	    }   
	    else
        {
            cout << "Unable to open file";
        }

        // freeing memory from pointers
        delete []data;
        delete []decryptedData;
        delete file;
        delete keyFile;
        delete ivFile;
        
    }
    else if (strstr(file,".jpg")!=NULL)
    {
        // here image encryption will be done
    }
    
    return 0;
}

