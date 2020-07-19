# AES 128 bit (CBC and ECB mode) Implementation using C++ and Open CV

## Open CV setup and tutorials
I have setup openCV for c++ in vs code.
A detailed medium article to follow the setup is given
#### https://medium.com/analytics-vidhya/vs-code-with-opencv-c-on-windows-10-explained-256418442c52

Some of the OpenCV methods used in this program are from reference
#### https://www.youtube.com/watch?v=l_4fNNyk1aw&list=PLAp0ZhYvW6XbEveYeefGSuLhaPlFML9gP

## Program info
All the function/methods used in the implementation of algoirthm are defined in AES.hpp header file.
All the lookup tables used for encryption and decryption are defined in lookup_tables.hpp header file.
The main method to encode the given text or image file is in AES_Encoder.cpp.
The main method to decode the given text or image file is in AES_Decoder.hpp.
keyFile.txt is in files folder which must be in hex and of length 16.
ivFile.txt is in files folder which is an initialization vector for cbc mode. It should also be in hex and of length 16.
To encrypt a text file or image file place your file in the files folder.
Text encryption will generate a EncodedFile.txt and Text decryption will generate a DecodedFile.txt.
Image encryption will generate EncryptedImage.png and Image decrpytion will generate DecryptedImage.png/jpg.

## Program Compilation
To compile the project there are two bat files.
encrypt.bat generates encoder.exe. 
decrypt.bat generates decoder.exe.

## Program running

#### ECB Mode for text file and image
To run the encoder exe for text encryption in ECB mode pass arguments like this ->
.\encoder.exe -file [yourinputFileName.txt] -ecb -key [keyFile.txt]

To run the decoder exe for text decryption in ECB mode pass arguments like this ->
.\decoder.exe -file [EncodedFileName.txt] -ecb -key [keyFile.txt]

To run the encoder exe for image encryption in ECB mode pass arguments like this ->
.\encoder.exe -file [yourinputFileName.jpg/png] -ecb -key [keyFile.txt]

To run the decoder exe for image decryption in ECB mode pass arguments like this ->
.\decoder.exe -file [EncodedFileName.png] -ecb -key [keyFile.txt]

#### CBC Mode for text file and image
To run the encoder exe for text encryption in CBC mode pass arguments like this ->
.\encoder.exe -file [yourinputFileName.txt] -cbc -key [keyFile.txt] -iv [ivFile.txt]

To run the decoder exe for text decryption in CBC mode pass arguments like this ->
.\decoder.exe -file [EncodedFileName.txt] -cbc -key [keyFile.txt] -iv [ivFile.txt]

To run the encoder exe for image encryption in CBC mode pass arguments like this -> 
.\encoder.exe -file [yourinputFileName.jpg/png] -cbc -key [keyFile.txt] -iv [ivFile.txt]

To run the decoder exe for image decryption in CBC mode pass arguments like this -> 
.\decoder.exe -file [EncodedFileName.png] -cbc -key [keyFile.txt] -iv [ivFile.txt]


## Program Execution Timings
To calculate program execution timings reference
https://www.techiedelight.com/find-execution-time-c-program/

#### ECB Image Encoding 
42 kb image file took 0.97 seconds or 973227 micro seconds so 
ECB image encoding is done 0.042 mb/0.97 seconds = 0.043 mb per second

#### ECB Image Decoding 
515 kb image file took 0.99 seconds or 991208 micro seconds so 
ECB image decoding is done 0.515 mb/0.99 seconds = 0.52 mb per second

#### CBC Image Encoding 
42 kb image file took 0.98 seconds or 986351 micro seconds so 
CBC image encoding is done 0.042 mb/0.98 seconds = 0.042 mb per second

#### CBC Image Decoding 
622 kb image file took 1.06 seconds or 1063494 micro seconds so 
CBC image decoding is done 0.622 mb/1.06 seconds = 0.57 mb per second

#### ECB Text file Encoding
84 kb text file took 0.126 seconds or 126319 mirco seconds so 
ECB Text file encoding is done 0.084 mb/0.126 seconds = 0.66 mb per second

#### ECB Text file Decoding
84 kb text file took 0.124 seconds or 124967 micro seconds so
ECB text file decoding is done 0.084 mb/0.124 seconds = 0.67 mb per second

#### CBC Text file Encoding
84 kb text file took 0.132 seconds or 132587 mirco seconds so 
CBC Text file encoding is done 0.084 mb/0.132 seconds = 0.63 mb per second

#### CBC Text file Decoding
84 kb text file took 0.147 seconds or 147268 micro seconds so
ECB text file decoding is done 0.084 mb/0.147 seconds = 0.57 mb per second
