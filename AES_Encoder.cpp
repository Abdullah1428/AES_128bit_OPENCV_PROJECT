/* 
    AES 128 Bit Project 
    implementation by Abdullah1428
    CS Project
*/

#include "AES.hpp"

int main(int argc, char **argv)
{

    if (!program_args(argc,argv,"-file") 
    || (!program_args(argc,argv,"-ecb") && !program_args(argc,argv,"-cbc")) 
    || !program_args(argc,argv,"-key") 
    || (program_args(argc,argv,"-cbc") && !program_args(argc,argv,"-iv")) )
    {
        cout<<"Please provide correct arguments"<<endl;
        cout<<"The correct format to pass arguments are"<<endl;
        cout<<"AES_Encoder.exe -file InputFile.txt/InputFile.jpg -ecb/cbc -key keyFile.txt (for cbc) -iv ivFile.txt"<<endl;
        
        // exit
        return 1;
    }

    const char * file = argv[program_args(argc,argv,"-file")+1];
    const char * keyFile = argv[program_args(argc,argv,"-key")+1];
    const char * ivFile = argv[program_args(argc,argv,"-iv")+1]; 
    
    if (strstr(file,".txt")==NULL && strstr(file,".png")==NULL && strstr(file,".jpg")==NULL)
    {
        cout<<"Please provide a txt, jpg or png file"<<endl;
        return 1;
    }

    if(strstr(file,".txt")!=NULL)
    {
        // here text file encryption will be done
        int fileLength = getTextFileLength(file);

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
        uint8_t * encryptedData = new uint8_t[fileLength];

        // reading data from input file
        data = getTextFromInputFile(file,data);

        struct timeval startTime , stopTime;

        if(program_args(argc,argv,"-ecb"))
        {
            // ecb mode
            // starting time
            gettimeofday(&startTime, NULL);
            // encrypting data using ecb mode
            encryptedData = file_Encryption_ECB(keyBlock,fileLength,data,encryptedData);
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
            encryptedData = file_Encryption_CBC(keyBlock,ivBlock,fileLength,data,encryptedData);
            // end time
            gettimeofday(&stopTime, NULL);
        }
        
        ofstream outfile;
	    outfile.open("files/EncodedFile.txt", ios::out | ios::binary);
	    if (outfile.is_open())
	    {
		    outfile.write((char *)encryptedData,fileLength);
		    outfile.close();
		    cout << endl << "Wrote encrypted message to file EncodedFile in files folder" << endl;
	    }   
	    else
        {
            cout << "Unable to open file";
        }

        long seconds = (stopTime.tv_sec - startTime.tv_sec);
        long microSeconds = ((seconds*1000000) + stopTime.tv_usec) - (startTime.tv_usec);

        cout<<endl<<"The encryption of text file took "<<seconds<<" in seconds and took "<<microSeconds<<" in micro seconds"<<endl;

        // freeing memory from pointers
        delete []data;
        delete []encryptedData;
        delete file;
        delete keyFile;
        delete ivFile;
        
    }
    else if (strstr(file,".jpg")!=NULL || strstr(file,".png")!=NULL)
    {
        // getting the key from the text file
        Mat keyBlock = getKeyFile(keyFile);
        // here image encryption will be done
        string imageDir = "files/";

        string imageName = imageDir + file;

        Mat InputImage = imread(imageName,IMREAD_COLOR);
        // now as we know color image has 3 colors in it R G B
        // so we will be needing to split each color from the image and then
        // encrypt it and after that we will decrypt each color and then again merge to form orignal image
        // so fot that purpose we will use open CV split and merge functions
        Mat imageColorChannels[3]; // r g b
        Mat encryptedColorChannels[3];

        // now spliting 
        split(InputImage,imageColorChannels);

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
                encryptedColorChannels[channel] = image_channel_encryption_ecb(imageColorChannels[channel],keyBlock); 
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
                encryptedColorChannels[channel] = image_channel_encryption_cbc(imageColorChannels[channel],keyBlock,ivBlock); 
            }
            // end time
            gettimeofday(&stopTime, NULL);
        }

        Mat encryptedImage;

        merge(encryptedColorChannels,3,encryptedImage);

        imwrite("files/EncryptedImage.png",encryptedImage);

        cout<<endl<<"Encrypted image stored in files folder with name EncryptedImage"<<endl;

        long seconds = (stopTime.tv_sec - startTime.tv_sec);
        long microSeconds = ((seconds*1000000) + stopTime.tv_usec) - (startTime.tv_usec);

        cout<<endl<<"The encryption of image file took "<<seconds<<" in seconds and took "<<microSeconds<<" in micro seconds"<<endl;
                
    }

    return 0;
}

































