#ifndef _DATASET_HPP_
#define _DATASET_HPP_

#include <iostream>//for work in console
#include <fstream>//for work with files
#include <cmath>//mathematical library from C (for pow() using)
#include <vector>//dynamic array from STL    
#include <string>

using namespace std;

/////////////////////////////////////////////////////
class Dataset
{
private:
    vector<vector<double>> pixels;
    size_t str, element;
public:
    Dataset(string filename, string database);
    ~Dataset();
    size_t GetStr();
    size_t GetElement();
    vector<vector<double>> GetPixels();
    vector<vector<double>> GetPixelsLink();
    //void ShowData();
};

Dataset::Dataset(string filename, string database)
{
    if(database == "MNIST")
    {
        str = 785;
        //size_t initial_neurons_layer = 784;
        ifstream fin;//entry flow in file

        fin.open(filename);//It's a file opening
        if (!fin.is_open())//This is the checking that file was opened
        {
            cout << "Error to open your file" << endl;
        }
        else{
            cout << "The file with name \"" << filename << "\" was opened." << endl;
        }

        double predict;
        double pixel;
        string temp;//temporary parameter for the reading text from the file

            fin >> temp;
            /*if(line == 1) 
            {
               //cout << str << endl;
               int init_size = stoi(str2);
               this->element = size_t(init_size);
               pixels.resize(element, vector<double>(str));
            }*/
            if(temp == "Examples")
            {
                fin >> element;
                //cout << temp << endl;
                pixels.resize(element, vector<double>(str));
                fin >> predict;
                //cout << "predict = " << predict << endl;
                for (size_t i = 0; i < element; i++)
                {
                    for (size_t j = 0; j < str-1; j++)
                    {
                        fin >> pixel;
                        pixels[i][j] = pixel;
                        //cout << "[" << i << "][" << j << "] = " << pixels[i][j] << endl;
                        //fin.close();
                    }
                    //pixels[i].push_back(predict);
                    pixels[i][str-1] = predict;
                    fin.close();
                    //cout << "[" << i << "][" << str-1 << "] = " << pixels[i][str-1] << endl;
                    if(i == 1) break;
                    
                }
            }

    }
    else
    {
        cout << "Error to open database." << endl;
        cout << "Please check the name of your database. " << endl;
        cout << "If the name is correct, it means that your database is not supported by this program." << endl;
    }


}

Dataset::~Dataset()
{
}

size_t Dataset::GetStr()
{
    return str;
}

size_t Dataset::GetElement()
{
    return element;
}

vector<vector<double>> Dataset::GetPixels()
{
    return pixels;
}

vector<vector<double>> Dataset::GetPixelsLink()
{
    //return this->pixels;
    //Dataset
    //vector<vector<double>> *objects = &pixels;
    //vector<vector<double>> & tmp_arr = pixels;
    //return tmp_arr;
    return pixels;
}

/*void Dataset::ShowData()
{
    for (size_t i = 0; i < element; i++)
    {
        for (size_t j = 0; j < str-1; j++)
        {
            cout << "[" << i << "][" << j << "] = " << pixels[i][j] << endl;
        }       
    }
    
}*/


#endif