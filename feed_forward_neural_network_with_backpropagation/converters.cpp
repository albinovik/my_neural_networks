#include <iostream>//for work in console
#include <map>//container
#include "converters.hpp"

using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////
//                                       Converters                                    //
/////////////////////////////////////////////////////////////////////////////////////////

void ConverterToLDigits(double *arr, double sum){

    cout << "RESULTS: " << endl;
    for (int i = 0; i < 10; i++)
    {
        //cout << "RESULTS: " << endl;
        arr[i] = abs(arr[i] / sum) * 100;
        if(arr[i] < 0.001) arr[0];
        cout << i << " : " << arr[i] << "%" << endl;
    } 

}

void ConverterToLetters(double *arr, double sum){

    map<int,char> latin_alphabet_inverse_key{
    {0, 'A'},{1, 'B'},{2, 'C'},{3, 'D'},{4, 'E'},{5, 'F'},
    {6, 'G'},{7, 'H'},{8, 'I'},{9, 'J'},{10, 'K'},{11, 'L'},
    {12, 'M'},{13, 'N'},{14, 'O'},{15, 'P'},{16, 'Q'},{17, 'R'},
    {18, 'S'},{19, 'T'},{20, 'U'},{21, 'V'},{22, 'W'},{23, 'X'},
    {24, 'Y'},{25, 'Z'}
    };

    cout << "RESULTS: " << endl;
    for (int i = 0; i < 26; i++)
    {
        //cout << "RESULTS: " << endl;
        arr[i] = abs(arr[i] / sum) * 100;
        if(arr[i] < 0.001) arr[0];
        //if(arr[i] < 0.001) arr[0]; 
        cout << latin_alphabet_inverse_key[i] << " : " << arr[i] << "%" << endl;
    } 

}

void ConverterToShapes(double *arr, double sum){

    map<int,string> shps_inverse_key{
        {0, "Circle"},{1, "Square"},{2, "Triangle"}
        };
        /*
        C - circle
        S - square
        T - triangle
        */

    cout << "RESULTS: " << endl;
    for (int i = 0; i < 3; i++)
    {
        //cout << "RESULTS: " << endl;
        arr[i] = abs(arr[i] / sum) * 100;
        if(arr[i] < 0.001) arr[0]; 
        cout << shps_inverse_key[i] << " : " << arr[i] << "%" << endl;
    } 

}