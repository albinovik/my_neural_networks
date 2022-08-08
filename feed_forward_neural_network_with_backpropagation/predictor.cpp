#include <iostream>//for work in console
#include <fstream>//for work with files
#include <cmath>//mathematical library from C (for pow() using)
#include <vector>//dynamic array from STL 
#include <chrono>//for time calculation 
#include "reluneuron.hpp"//neuron with ReLU function
#include "structnet.hpp"//sturctures of different images 
#include "dataset.hpp"//class for reading data files
#include "network.hpp" //neural network

//int main(int argc, char *argv[2]){
int main(){

   /* int middle_layer = atoi(argv[1]);
    int volume = atoi(argv[2]);*/


    int user_choice = 0;

    cout << "____________________________________________________________________________________________" << endl;
    cout << "|                                                                                           |" << endl;
    cout << "|                               WELCOME TO TERNARY PREDICTOR!                               |" << endl;
    cout << "|___________________________________________________________________________________________|" << endl;
    cout << endl;
    cout <<  "This program trains the feed forward neural network using the error backpropagation method. " << endl;
    cout <<  "The program implements work with black&white pictures which is represented only one object:" << endl;
    cout << "1) one of the digits (from 0 to 9);" << endl;
    cout << "2) one of the letters of the latin alphabet (from A to Z);" << endl;
    cout << "3) one of the shapes (circle, square, triangle)." << endl;
    cout << endl;
    cout << "What kind of images do you prefer to work with? ( Please enter one of the numbers:  1 / 2 / 3 )" << endl;    
    cin >> user_choice;

    /////////////////////////////////////////////////////////////////////////////////
    //                              work with digits                               //
    /////////////////////////////////////////////////////////////////////////////////
    if(user_choice == 1)
    {
        Dataset dataset("MNIST.txt");

        vector<int> init = {784, 256, 10};
        /*
        first layer contains 784 neurons
        second layer contains 256 neurons
        third layer contains 10 neurons
        */

        Network n(init);
        n.Train(init,dataset, 400);
        //testing process ///////////////////////////////////////////////////////////
        string user_text;
        while(1)
        {
            cout << endl << "Enter name of your file with image for network testing: " << endl;
            cin >> user_text;

            Dataset one_digit(user_text, 'd');

            n.Test(init, one_digit);

            cout << "Do you want to continue? (Yes / No)" << endl;
            cin >> user_text;
            if(user_text == "No" || user_text == "no") break;
        }



    }

    /////////////////////////////////////////////////////////////////////////////////
    //                              work with letters                              //
    /////////////////////////////////////////////////////////////////////////////////
    if (user_choice == 2)
    {

        
        Dataset dataset("letters.txt");
        
        vector<int> init = {784, 130, 26};
        /*
        first layer contains 784 neurons
        second layer contains 100 neurons
        third layer contains 26 neurons
        */

        Network n(init);

        n.Train(init, dataset, 200, 1);

        //testing process ///////////////////////////////////////////////////////////
        string user_text;
        while(1)
        {
            cout << endl << "Enter name of your file with image for network testing: " << endl;
            cin >> user_text;

            Dataset lll(user_text, 'l');

            n.Test(init, lll);

            cout << "Do you want to continue? (Yes / No)" << endl;
            cin >> user_text;
            if(user_text == "No" || user_text == "no") break;
        }

        //testing process ///////////////////////////////////////////////////////////
        //Dataset rtyu("test_letters.txt");

        //n.Test(init, rtyu);

    }

    /////////////////////////////////////////////////////////////////////////////////
    //                              work with shapes                               //
    /////////////////////////////////////////////////////////////////////////////////
    if (user_choice == 3)
    {
        //cout << "Sorry, this part of the code in the process of development.. " << endl;

        Dataset dataset("shapes.txt");
        
        vector<int> init = {784, 33, 3};
        /*
        first layer contains 784 neurons
        second layer contains 33 neurons
        third layer contains 3 neurons
        */

        Network n(init);

        n.Train(init, dataset, 30, 1);


        //testing process ///////////////////////////////////////////////////////////
        string user_text;
        while(1)
        {
            cout << endl << "Enter name of your file with image for network testing: " << endl;
            cin >> user_text;

            Dataset sdf(user_text, 's');

            n.Test(init, sdf);

            cout << "Do you want to continue? (Yes / No)" << endl;
            cin >> user_text;
            if(user_text == "No" || user_text == "no") break;
        }
    }






    /////////////////////////////////////////////////////////////////////////////////
    //                    message about  an input error of user                    //
    /////////////////////////////////////////////////////////////////////////////////
    if(user_choice != 1 && user_choice != 2 && user_choice != 3)
    {
        cout << "Invalid input: " << user_choice << endl;
    }


    return 0;
}