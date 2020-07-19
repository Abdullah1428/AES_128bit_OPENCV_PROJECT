/* 
    AES 128 Bit Project 
    implementation by Abdullah1428
    CS Project
*/
#include "AES.hpp"

int main(int argc, char ** argv)
{

    if (!program_args(argc,argv,"-file") 
    || (!program_args(argc,argv,"-ecb") && !program_args(argc,argv,"-cbc")) 
    || !program_args(argc,argv,"-key") 
    || (program_args(argc,argv,"-cbc") && !program_args(argc,argv,"-iv")) )
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
        int fileLength = cipheredFileLength(file);

        if(fileLength == 0)
        {
            // file could not be read
            return 1;
        }

        // getting the key from the text file
        Mat keyBlock = getKeyFile(keyFile);

        // data will hold the orignal text
        uint8_t * data = new uint8_t[fileLength];
        // encrypted data will hold the ciphered text
        uint8_t * decryptedData = new uint8_t[fileLength];

        // reading data from input file
        data = getTextFromCipheredFile(file,data);

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

        long seconds = (stopTime.tv_sec - startTime.tv_sec);
        long microSeconds = ((seconds*1000000) + stopTime.tv_usec) - (startTime.tv_usec);

        cout<<endl<<"The decryption of text file took "<<seconds<<" in seconds and took "<<microSeconds<<" in micro seconds"<<endl;
        // freeing memory from pointers
        delete []data;
        delete []decryptedData;
        delete file;
        delete keyFile;
        delete ivFile;
        
    }
    else if (strstr(file,".png")!=NULL || strstr(file,".png")!=NULL)
    {
        // here image decryption will be done
        // getting the key from the text file
        Mat keyBlock = getKeyFile(keyFile);
        // here image encryption will be done
        string imageDir = "files/";

        string imageName = imageDir + file;

        Mat EncryptedImage = imread(imageName,IMREAD_COLOR);
        // now as we know color image has 3 colors in it R G B
        // so we will be needing to split each color from the image and then
        // encrypt it and after that we will decrypt each color and then again merge to form orignal image
        // so fot that purpose we will use open CV split and merge functions
        Mat imageColorChannels[3]; // r g b
        Mat decryptedColorChannels[3];

        // now spliting 
        split(EncryptedImage,imageColorChannels);

        struct timeval startTime , stopTime;

        if(program_args(argc,argv,"-ecb"))
        {
            // ecb mode
            // starting time
            gettimeofday(&startTime, NULL);
            // encrypting data using ecb mode
            // now encrypting each channel
            for(int channel = 0 ; channel < 3 ; channel++)
            {
                decryptedColorChannels[channel] = image_channel_decryption_ecb(imageColorChannels[channel],keyBlock); 
            }
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
            for(int channel = 0 ; channel < 3 ; channel++)
            {
                decryptedColorChannels[channel] = image_channel_decryption_cbc(imageColorChannels[channel],keyBlock,ivBlock); 
            }
            // end time
            gettimeofday(&stopTime, NULL);
        }

        Mat decryptedImage;

        merge(decryptedColorChannels,3,decryptedImage);

        imwrite("files/DecryptedImage.jpg",decryptedImage);

        cout<<endl<<"Decrypted image stored in files folder with name DecryptedImage"<<endl;

        long seconds = (stopTime.tv_sec - startTime.tv_sec);
        long microSeconds = ((seconds*1000000) + stopTime.tv_usec) - (startTime.tv_usec);

        cout<<endl<<"The decryption of image file took "<<seconds<<" in seconds and took "<<microSeconds<<" in micro seconds"<<endl;
    }
    
    return 0;
}

