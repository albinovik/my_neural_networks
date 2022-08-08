<<<<<<< HEAD
#include <dirent.h>//for work with directory
=======
>>>>>>> cecdbdf57ff9bb8e4621578ed7e44b327c7b98f6
#include <iostream>//for work in console
#include <fstream>//for work with files
#include "structnet.hpp"//sturctures of different images
#include "dataset.hpp"
#include <map>//container
<<<<<<< HEAD
//#include <string>
//#include <cstdio>
=======
>>>>>>> cecdbdf57ff9bb8e4621578ed7e44b327c7b98f6

using namespace std;


<<<<<<< HEAD
/////////////////////////////////////////////////////////////////////////////////////////
//                               Dataset from lybrary                                  //
/////////////////////////////////////////////////////////////////////////////////////////

Dataset::Dataset(string filename)
{

    //MNIST data
    if ( filename == "MNIST.txt")
    {

        DIR *dir;
        struct dirent *ent;
        if ((dir = opendir("./lib/")) != NULL) 
            while ((ent = readdir(dir)) != NULL) 
            {

                if (ent->d_name == filename)
                {
                    string con_str = "./lib/" + filename;
                    //cout << con_str << endl;

                    ifstream fin;//entry flow in file

                    fin.open(con_str);//It's a file opening
                    if (!fin.is_open())//This is the checking that file was opened
                    {
                        cout << "Error to open your file" << endl;
                    }
                    else{
                        cout << "The file with name \"" << filename << "\" was opened." << endl;
                    }

                    string temp;//temporary parameter for the reading text from the file as a string

                    fin >> temp;

                    if(temp == "Examples")
                    {
                        fin >> size;
                        cout << "The number of examples for training in the file: " << size << endl;

                        data = new Image [size];
                        for (int i = 0; i < size; i++)
                        {
                            data[i].pixels = new double[784];
                        }

                        for (int i = 0; i < size; i++) 
                        {
                            fin >> data[i].element;
                            for (int j = 0; j < 784; j++) 
                            {
                                fin >> data[i].pixels[j];
                            }
                        }

                        fin.close();
                    }

                }


            }

        closedir(dir);

    }

    //my own data of letters
    if (filename == "letters.txt" )
    {
        map<char,int> latin_alphabet{
        {'A', 0},{'B', 1},{'C', 2},{'D', 3},{'E', 4},{'F', 5},
        {'G', 6},{'H', 7},{'I', 8},{'J', 9},{'K', 10},{'L', 11},
        {'M',12},{'N', 13},{'O', 14},{'P', 15},{'Q', 16},{'R', 17},
        {'S', 18},{'T', 19},{'U', 20},{'V', 21},{'W', 22},{'X', 23},
        {'Y', 24},{'Z', 25}
        };

        DIR *dir;
        struct dirent *ent;
        if ((dir = opendir("./lib/")) != NULL) 
            while ((ent = readdir(dir)) != NULL) 
            {
                if (ent->d_name == filename)
                {
                    string con_str = "./lib/" + filename;
                    //cout << con_str << endl;
       
       
                            ifstream fin;//entry flow in file

                            fin.open(con_str);//It's a file opening
                            if (!fin.is_open())//This is the checking that file was opened
                            {
                                cout << "Error to open your file" << endl;
                            }
                            else{
                                cout << "The file with name \"" << filename << "\" was opened." << endl;
                            }

                            string temp;//temporary parameter for the reading text from the file as a string

                            char temp2;//temporary parameter for the reading text from the file as a syblom

                            fin >> temp;

                            if(temp == "Examples")
                            {
                                fin >> size;
                                cout << "The number of examples for training in the file: " << size << endl;

                                data = new Image [size];
                                for (int i = 0; i < size; i++)
                                {
                                    data[i].pixels = new double[784];
                                }

                                for (int i = 0; i < size; i++) 
                                {
                                    fin >> temp2;

                                    //get number of letter from latin alphabet
                                    data[i].element = latin_alphabet[temp2];
                                    
                                    //fin >> data[i].element;

                                    for (int j = 0; j < 784; j++) 
                                    {
                                        fin >> data[i].pixels[j];
                                    }
                                }

                                fin.close();
                            }
                }
            }

        closedir(dir);
    }    


    //my own data of letters
    if (filename == "shapes.txt" ) 
    {
        map<char,int> shps{
        {'C', 0},{'S', 1},{'T', 2}
        };
        /*
        C - circle
        S - square
        T - triangle
        */
               
        DIR *dir;
        struct dirent *ent;
        if ((dir = opendir("./lib/")) != NULL) 
            while ((ent = readdir(dir)) != NULL) 
            {

                if (ent->d_name == filename)
                {
                    string con_str = "./lib/" + filename;
                    //cout << con_str << endl;
       
       
                            ifstream fin;//entry flow in file

                            fin.open(con_str);//It's a file opening
                            if (!fin.is_open())//This is the checking that file was opened
                            {
                                cout << "Error to open your file" << endl;
                            }
                            else{
                                cout << "The file with name \"" << filename << "\" was opened." << endl;
                            }

                            string temp;//temporary parameter for the reading text from the file as a string

                            char temp2;//temporary parameter for the reading text from the file as a syblom

                            fin >> temp;

                            if(temp == "Examples")
                            {
                                fin >> size;
                                cout << "The number of examples for training in the file: " << size << endl;

                                data = new Image [size];
                                for (int i = 0; i < size; i++)
                                {
                                    data[i].pixels = new double[784];
                                }

                                for (int i = 0; i < size; i++) 
                                {
                                    fin >> temp2;

                                    //get number of letter from latin alphabet
                                    data[i].element = shps[temp2];
                                    
                                    //fin >> data[i].element;

                                    for (int j = 0; j < 784; j++) 
                                    {
                                        fin >> data[i].pixels[j];
                                    }
                                }

                                fin.close();
                            }
                }
            }
        closedir(dir);

    }   
}

/////////////////////////////////////////////////////////////////////////////////////////
//                     Dataset from current directory (with mode)                      //
/////////////////////////////////////////////////////////////////////////////////////////
Dataset::Dataset(string filename, char mode)
{
    //MNIST data
    if (mode == 'd')
=======
Dataset::Dataset(string filename)
{
    //MNIST data
    if (filename == "digits.txt")
>>>>>>> cecdbdf57ff9bb8e4621578ed7e44b327c7b98f6
    {
        ifstream fin;//entry flow in file

        fin.open(filename);//It's a file opening
        if (!fin.is_open())//This is the checking that file was opened
        {
            cout << "Error to open your file" << endl;
        }
        else{
            cout << "The file with name \"" << filename << "\" was opened." << endl;
        }

        string temp;//temporary parameter for the reading text from the file as a string

        fin >> temp;

        if(temp == "Examples")
        {
            fin >> size;
            cout << "The number of examples for training in the file: " << size << endl;

            data = new Image [size];
            for (int i = 0; i < size; i++)
            {
                data[i].pixels = new double[784];
            }

            for (int i = 0; i < size; i++) 
            {
                fin >> data[i].element;
                for (int j = 0; j < 784; j++) 
                {
                    fin >> data[i].pixels[j];
                }
            }

            fin.close();
        }
    }

    //my own data of letters
<<<<<<< HEAD
    if (mode == 'l')
=======
    if (filename == "letters.txt")
>>>>>>> cecdbdf57ff9bb8e4621578ed7e44b327c7b98f6
    {
        map<char,int> latin_alphabet{
        {'A', 0},{'B', 1},{'C', 2},{'D', 3},{'E', 4},{'F', 5},
        {'G', 6},{'H', 7},{'I', 8},{'J', 9},{'K', 10},{'L', 11},
        {'M',12},{'N', 13},{'O', 14},{'P', 15},{'Q', 16},{'R', 17},
        {'S', 18},{'T', 19},{'U', 20},{'V', 21},{'W', 22},{'X', 23},
        {'Y', 24},{'Z', 25}
        };
       
       
        ifstream fin;//entry flow in file

        fin.open(filename);//It's a file opening
        if (!fin.is_open())//This is the checking that file was opened
        {
            cout << "Error to open your file" << endl;
        }
        else{
            cout << "The file with name \"" << filename << "\" was opened." << endl;
        }

        string temp;//temporary parameter for the reading text from the file as a string

        char temp2;//temporary parameter for the reading text from the file as a syblom

        fin >> temp;

        if(temp == "Examples")
        {
            fin >> size;
            cout << "The number of examples for training in the file: " << size << endl;

            data = new Image [size];
            for (int i = 0; i < size; i++)
            {
                data[i].pixels = new double[784];
            }

            for (int i = 0; i < size; i++) 
            {
                fin >> temp2;

                //get number of letter from latin alphabet
                data[i].element = latin_alphabet[temp2];
                
                //fin >> data[i].element;

                for (int j = 0; j < 784; j++) 
                {
                    fin >> data[i].pixels[j];
                }
            }

            fin.close();
        }


    }    


<<<<<<< HEAD
    //my own data of letters
    if (mode == 's')
=======
    //my own data of shapes
    if (filename == "shapes.txt")
>>>>>>> cecdbdf57ff9bb8e4621578ed7e44b327c7b98f6
    {
        map<char,int> shps{
        {'C', 0},{'S', 1},{'T', 2}
        };
        /*
        C - circle
        S - square
        T - triangle
        */
       
       
        ifstream fin;//entry flow in file

        fin.open(filename);//It's a file opening
        if (!fin.is_open())//This is the checking that file was opened
        {
            cout << "Error to open your file" << endl;
        }
        else{
            cout << "The file with name \"" << filename << "\" was opened." << endl;
        }

        string temp;//temporary parameter for the reading text from the file as a string

        char temp2;//temporary parameter for the reading text from the file as a syblom

        fin >> temp;

        if(temp == "Examples")
        {
            fin >> size;
            cout << "The number of examples for training in the file: " << size << endl;

            data = new Image [size];
            for (int i = 0; i < size; i++)
            {
                data[i].pixels = new double[784];
            }

            for (int i = 0; i < size; i++) 
            {
                fin >> temp2;

                //get number of letter from latin alphabet
                data[i].element = shps[temp2];
                
                //fin >> data[i].element;

                for (int j = 0; j < 784; j++) 
                {
                    fin >> data[i].pixels[j];
                }
            }

            fin.close();
        }


    }   
}

<<<<<<< HEAD
/////////////////////////////////////////////////////////////////////////////////////////////////////

=======
>>>>>>> cecdbdf57ff9bb8e4621578ed7e44b327c7b98f6
Dataset::~Dataset()
{}

int Dataset::GetSize()
{
    return size;
}

double Dataset::GetElement(int i)
{
    return data[i].element;
}

double Dataset::GetPixel(int i, int j)
{
    return data[i].pixels[j];
}

double *Dataset::GetPixelLayer(int i)
{
    return data[i].pixels;
}