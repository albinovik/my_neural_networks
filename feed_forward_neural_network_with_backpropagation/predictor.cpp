#include <iostream>//for work in console
#include <fstream>//for work with files
#include <cmath>//mathematical library from C (for pow() using)
#include <vector>//dynamic array from STL 
#include <chrono>//for time calculation 
#include <thread>//for work with threads
#include "reluneuron.hpp"//neuron with ReLU function
#include "structnet.hpp"//sturctures of different images 
#include "dataset.hpp"//class for reading data files
#include "network.hpp" //neural network

//int main(int argc, char *argv[2]){
int main(){

   /* int middle_layer = atoi(argv[1]);
    int volume = atoi(argv[2]);*/


    int user_choice1 = 0, user_choice2 = 0;

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
    cin >> user_choice1;

    /////////////////////////////////////////////////////////////////////////////////
    //                              work with digits                               //
    /////////////////////////////////////////////////////////////////////////////////
    if(user_choice1 == 1)
    {    
        cout << "____________________________________________________________________________________________" << endl;
        cout << "|                                                                                           |" << endl;
        cout << "|                               THE OPERATING MODE SETTING                                  |" << endl;
        cout << "|___________________________________________________________________________________________|" << endl;  
        cout << "TESTING MODE (with default settings)."  << endl;
        cout << "You can use results of a previous training for your images testing. Enter 1 for choosing of this mode." << endl;
        cout << endl;
        cout << "TRAINING MODE (with default settings)." << endl;
        cout << "If you want to train the network using default settings and to test after that, enter 2 for choosing of this mode." << endl;
        cout << endl;
        cout << "DESIGN MODE. "<< endl;
        cout << "If you want to construct your own network design, enter 3." << endl;
        cout << "Please enter one of the numbers ( 1 / 2 / 3 )  for choosing mode of work for network:" << endl; 
        cin >> user_choice2;

        if(user_choice2 == 1)
        { 

            cout << "____________________________________________________________________________________________" << endl;
            cout << "|                                                                                           |" << endl;
            cout << "|                                       TESTING MODE                                        |" << endl;
            cout << "|___________________________________________________________________________________________|" << endl;

            vector<int> init = {784, 256, 10};
            /*
            first layer contains 784 neurons
            second layer contains 256 neurons
            third layer contains 10 neurons
            */
            Network n(init);


            string user_text;
            while(1)
            {
                cout << endl << "Enter name of your file with image for network testing: " << endl;
                cin >> user_text;

                Dataset one_digit(user_text, 'd');

                n.TestLib(init, one_digit, 'd');//weights and b_shifts data are form library (lib)

                cout << "Do you want to continue? (Yes / No)" << endl;
                cin >> user_text;
                if(user_text == "No" || user_text == "no") break;
            }

        }


        if(user_choice2 == 2)
        { 
            cout << "____________________________________________________________________________________________" << endl;
            cout << "|                                                                                           |" << endl;
            cout << "|                                       TRAINIG MODE                                        |" << endl;
            cout << "|___________________________________________________________________________________________|" << endl;

            Dataset dataset("MNIST.txt");

            vector<int> init = {784, 256, 10};
            /*
            first layer contains 784 neurons
            second layer contains 256 neurons
            third layer contains 10 neurons
            */

            Network n(init);
            n.Train(init,dataset, 400);
            
            string user_text;
            while(1)
            {
                cout << endl << "Enter name of your file with image for network testing: " << endl;
                cin >> user_text;

                Dataset one_digit(user_text, 'd');

                n.Test(init, one_digit, 'd');

                cout << "Do you want to continue? (Yes / No)" << endl;
                cin >> user_text;
                if(user_text == "No" || user_text == "no") break;
            }

            
        }

        if(user_choice2 == 3)
        { 
            cout << "____________________________________________________________________________________________" << endl;
            cout << "|                                                                                           |" << endl;
            cout << "|                                       DESIGN MODE                                         |" << endl;
            cout << "|___________________________________________________________________________________________|" << endl;

            int net_construct, net_construct2;
            double lr;
            vector<int> init;

            cout << "The neural network works with image format 28 by 28 pixels." << endl;
            cout << "Therefore, first layer of network contains 784 neurons." << endl;
            cout << "Last layer contains 10 neurons according amount of digits." << endl;
            cout << "You can change middle layers only. Let's get started!" << endl;
            cout << "How much middle layers do you want to set? " << endl;
            cin >> net_construct;

            //init.resize(net_construct + 2);
            init.push_back(784);

            for (size_t i = 0; i < size_t(net_construct); i++)
            {
                cout << "Enter number of neuron on "<< i + 2 << " layer: " << endl;
                cin >> net_construct2;
                init.push_back(net_construct2);
            }

            init.push_back(10);

            cout << "The network construction is finished: " << endl;
            for (size_t i = 0; i < init.size(); i++)
            {
                cout << init[i] << "  ";
            }
            cout << endl;
            
            //initialization of network
            Network n(init);
            cout << "The neural network will training on library data for digits. " << endl;
            cout << "You can control the learning rate of training. " << endl;
            cout << "Do you want to control the learning rate? (1 - Yes, 0 - No ) " << endl;
            cin >> net_construct2;

            if(net_construct2 == 1) 
            {
                cout << "Enter learning rate (from 0 to 1) in double format: " << endl;
                cin >> lr;
                cout << "Library data for digits contains 400 images. " << endl;
                cout << "How much images do you want to set for trainig? " << endl;
                cin >> net_construct;

                cout << "TRAINIG PROCESS IS STARTING." << endl;
                this_thread::sleep_for(chrono::seconds(2));
                Dataset dataset("MNIST.txt");
                n.Train(init, dataset, net_construct, lr);

                string user_text;
                while(1)
                {
                    cout << endl << "Enter name of your file with image for network testing: " << endl;
                    cin >> user_text;

                    Dataset one_digit(user_text, 'd');

                    n.Test(init, one_digit, 'd');

                    cout << "Do you want to continue? (Yes / No)" << endl;
                    cin >> user_text;
                    if(user_text == "No" || user_text == "no") break;
                }


            }


            if(net_construct2 == 0) 
            {
                cout << "Lerning rate will set default." << endl;
                cout << "Library data for digits contains 400 images. " << endl;
                cout << "How much images do you want to set for trainig? " << endl;
                cin >> net_construct;

                cout << "TRAINIG PROCESS IS STARTING." << endl;
                this_thread::sleep_for(chrono::seconds(2));
                Dataset dataset("MNIST.txt");
                n.Train(init, dataset, net_construct);

                string user_text;
                while(1)
                {
                    cout << endl << "Enter name of your file with image for network testing: " << endl;
                    cin >> user_text;

                    Dataset one_digit(user_text, 'd');

                    n.Test(init, one_digit, 'd');

                    cout << "Do you want to continue? (Yes / No)" << endl;
                    cin >> user_text;
                    if(user_text == "No" || user_text == "no") break;
                }
                
            }
            
        }
    }

    /////////////////////////////////////////////////////////////////////////////////
    //                              work with letters                              //
    /////////////////////////////////////////////////////////////////////////////////
    if (user_choice1 == 2)
    {
        cout << "____________________________________________________________________________________________" << endl;
        cout << "|                                                                                           |" << endl;
        cout << "|                               THE OPERATING MODE SETTING                                  |" << endl;
        cout << "|___________________________________________________________________________________________|" << endl; 
        cout << "TESTING MODE (with default settings)."  << endl;
        cout << "You can use results of a previous training for your images testing. Enter 1 for choosing of this mode." << endl;
        cout << endl;
        cout << "TRAINING MODE (with default settings)." << endl;
        cout << "If you want to training the network using default settings and testing after that, enter 2 for choosing of this mode." << endl;
        cout << endl;
        cout << "DESIGN MODE. "<< endl;
        cout << "If you want to construct your own network design, enter 3." << endl;
        cout << "Please enter one of the numbers ( 1 / 2 / 3 )  for choosing mode of work for network:" << endl; 
        cin >> user_choice2;

        
        if(user_choice2 == 1)
        { 
            cout << "____________________________________________________________________________________________" << endl;
            cout << "|                                                                                           |" << endl;
            cout << "|                                       TESTING MODE                                        |" << endl;
            cout << "|___________________________________________________________________________________________|" << endl;

            vector<int> init = {784, 130, 26};
            /*
            first layer contains 784 neurons
            second layer contains 130 neurons
            third layer contains 26 neurons
            */
            Network n(init);


            string user_text;
            while(1)
            {
                cout << endl << "Enter name of your file with image for network testing: " << endl;
                cin >> user_text;

                Dataset sdf(user_text, 'l');

                n.TestLib(init, sdf, 'l');//weights and b_shifts data are form library (lib)

                cout << "Do you want to continue? (Yes / No)" << endl;
                cin >> user_text;
                if(user_text == "No" || user_text == "no") break;
            }

        }

        if(user_choice2 == 2)
        { 

            cout << "____________________________________________________________________________________________" << endl;
            cout << "|                                                                                           |" << endl;
            cout << "|                                       TRAINIG MODE                                        |" << endl;
            cout << "|___________________________________________________________________________________________|" << endl;

            Dataset dataset("letters.txt");
            
            vector<int> init = {784, 130, 26};
            /*
            first layer contains 784 neurons
            second layer contains 130 neurons
            third layer contains 26 neurons
            */

            Network n(init);

            n.Train(init, dataset, 200, 1);

         
            string user_text;
            while(1)
            {
                cout << endl << "Enter name of your file with image for network testing: " << endl;
                cin >> user_text;

                Dataset lll(user_text, 'l');

                n.Test(init, lll, 'l');

                cout << "Do you want to continue? (Yes / No)" << endl;
                cin >> user_text;
                if(user_text == "No" || user_text == "no") break;
            }

        }

        if(user_choice2 == 3)
        { 
            cout << "____________________________________________________________________________________________" << endl;
            cout << "|                                                                                           |" << endl;
            cout << "|                                       DESIGN MODE                                         |" << endl;
            cout << "|___________________________________________________________________________________________|" << endl;

            int net_construct, net_construct2;
            double lr;
            vector<int> init;

            cout << "The neural network works with image format 28 by 28 pixels." << endl;
            cout << "Therefore, first layer of network contains 784 neurons." << endl;
            cout << "Last layer contains 10 neurons according amount of digits." << endl;
            cout << "You can change middle layers only. Let's get started!" << endl;
            cout << "How much middle layers do you want to set? " << endl;
            cin >> net_construct;

            //init.resize(net_construct + 2);
            init.push_back(784);

            for (size_t i = 0; i < size_t(net_construct); i++)
            {
                cout << "Enter number of neuron on "<< i + 2 << " layer: " << endl;
                cin >> net_construct2;
                init.push_back(net_construct2);
            }

            init.push_back(26);

            cout << "The network construction is finished: " << endl;
            for (size_t i = 0; i < init.size(); i++)
            {
                cout << init[i] << "  ";
            }
            cout << endl;
            
            //initialization of network
            Network n(init);
            cout << "The neural network will training on library data for digits. " << endl;
            cout << "You can control the learning rate of training. " << endl;
            cout << "Do you want to control the learning rate? (1 - Yes, 0 - No ) " << endl;
            cin >> net_construct2;

            if(net_construct2 == 1) 
            {
                cout << "Enter learning rate (from 0 to 1) in double format: " << endl;
                cin >> lr;
                cout << "Library data for digits contains 200 images. " << endl;
                cout << "How much images do you want to set for trainig? " << endl;
                cin >> net_construct;

                cout << "TRAINIG PROCESS IS STARTING." << endl;
                this_thread::sleep_for(chrono::seconds(2));
                Dataset dataset("letters.txt");
                n.Train(init, dataset, net_construct, lr);

                string user_text;
                while(1)
                {
                    cout << endl << "Enter name of your file with image for network testing: " << endl;
                    cin >> user_text;

                    Dataset one_digit(user_text, 'l');

                    n.Test(init, one_digit, 'l');

                    cout << "Do you want to continue? (Yes / No)" << endl;
                    cin >> user_text;
                    if(user_text == "No" || user_text == "no") break;
                }


            }


            if(net_construct2 == 0) 
            {
                cout << "Lerning rate will set default." << endl;
                cout << "Library data for digits contains 200 images. " << endl;
                cout << "How much images do you want to set for trainig? " << endl;
                cin >> net_construct;

                cout << "TRAINIG PROCESS IS STARTING." << endl;
                this_thread::sleep_for(chrono::seconds(2));
                Dataset dataset("letters.txt");
                n.Train(init, dataset, net_construct);

                string user_text;
                while(1)
                {
                    cout << endl << "Enter name of your file with image for network testing: " << endl;
                    cin >> user_text;

                    Dataset one_digit(user_text, 'l');

                    n.Test(init, one_digit, 'l');

                    cout << "Do you want to continue? (Yes / No)" << endl;
                    cin >> user_text;
                    if(user_text == "No" || user_text == "no") break;
                }
                
            }
            
        }

    }

    /////////////////////////////////////////////////////////////////////////////////
    //                              work with shapes                               //
    /////////////////////////////////////////////////////////////////////////////////
    if (user_choice1 == 3)
    {
        cout << "____________________________________________________________________________________________" << endl;
        cout << "|                                                                                           |" << endl;
        cout << "|                               THE OPERATING MODE SETTING                                  |" << endl;
        cout << "|___________________________________________________________________________________________|" << endl; 
        cout << "TESTING MODE (with default settings)."  << endl;
        cout << "You can use results of a previous training for your images testing. Enter 1 for choosing of this mode." << endl;
        cout << endl;
        cout << "TRAINING MODE (with default settings)." << endl;
        cout << "If you want to training the network using default settings and testing after that, enter 2 for choosing of this mode." << endl;
        cout << endl;
        cout << "DESIGN MODE. "<< endl;
        cout << "If you want to construct your own network design, enter 3." << endl;
        cout << "Please enter one of the numbers ( 1 / 2 / 3 )  for choosing mode of work for network:" << endl; 
        cin >> user_choice2;

        if(user_choice2 == 1)
        { 

            cout << "____________________________________________________________________________________________" << endl;
            cout << "|                                                                                           |" << endl;
            cout << "|                                       TESTING MODE                                        |" << endl;
            cout << "|___________________________________________________________________________________________|" << endl;

            vector<int> init = {784, 33, 3};
            /*
            first layer contains 784 neurons
            second layer contains 33 neurons
            third layer contains 3 neurons
            */
            Network n(init);


            string user_text;
            while(1)
            {
                cout << endl << "Enter name of your file with image for network testing: " << endl;
                cin >> user_text;

                Dataset sdf(user_text, 's');

                n.TestLib(init, sdf, 's');//weights and b_shifts data are form library (lib)

                cout << "Do you want to continue? (Yes / No)" << endl;
                cin >> user_text;
                if(user_text == "No" || user_text == "no") break;
            }

        }

        if(user_choice2 == 2)
        { 

            cout << "____________________________________________________________________________________________" << endl;
            cout << "|                                                                                           |" << endl;
            cout << "|                                       TRAINIG MODE                                        |" << endl;
            cout << "|___________________________________________________________________________________________|" << endl;

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


        
            string user_text;
            while(1)
            {
                cout << endl << "Enter name of your file with image for network testing: " << endl;
                cin >> user_text;

                Dataset sdf(user_text, 's');

                n.Test(init, sdf, 's');

                cout << "Do you want to continue? (Yes / No)" << endl;
                cin >> user_text;
                if(user_text == "No" || user_text == "no") break;
            }
        }

        if(user_choice2 == 3)
        { 
            cout << "____________________________________________________________________________________________" << endl;
            cout << "|                                                                                           |" << endl;
            cout << "|                                       DESIGN MODE                                         |" << endl;
            cout << "|___________________________________________________________________________________________|" << endl;

            int net_construct, net_construct2;
            double lr;
            vector<int> init;

            cout << "The neural network works with image format 28 by 28 pixels." << endl;
            cout << "Therefore, first layer of network contains 784 neurons." << endl;
            cout << "Last layer contains 10 neurons according amount of digits." << endl;
            cout << "You can change middle layers only. Let's get started!" << endl;
            cout << "How much middle layers do you want to set? " << endl;
            cin >> net_construct;

            //init.resize(net_construct + 2);
            init.push_back(784);

            for (size_t i = 0; i < size_t(net_construct); i++)
            {
                cout << "Enter number of neuron on "<< i + 2 << " layer: " << endl;
                cin >> net_construct2;
                init.push_back(net_construct2);
            }

            init.push_back(3);

            cout << "The network construction is finished: " << endl;
            for (size_t i = 0; i < init.size(); i++)
            {
                cout << init[i] << "  ";
            }
            cout << endl;
            
            //initialization of network
            Network n(init);
            cout << "The neural network will training on library data for digits. " << endl;
            cout << "You can control the learning rate of training. " << endl;
            cout << "Do you want to control the learning rate? (1 - Yes, 0 - No ) " << endl;
            cin >> net_construct2;

            if(net_construct2 == 1) 
            {
                cout << "Enter learning rate (from 0 to 1) in double format: " << endl;
                cin >> lr;
                cout << "Library data for digits contains 30 images. " << endl;
                cout << "How much images do you want to set for trainig? " << endl;
                cin >> net_construct;

                cout << "TRAINIG PROCESS IS STARTING." << endl;
                this_thread::sleep_for(chrono::seconds(2));
                Dataset dataset("shapes.txt");
                n.Train(init, dataset, net_construct, lr);

                string user_text;
                while(1)
                {
                    cout << endl << "Enter name of your file with image for network testing: " << endl;
                    cin >> user_text;

                    Dataset one_digit(user_text, 's');

                    n.Test(init, one_digit, 's');

                    cout << "Do you want to continue? (Yes / No)" << endl;
                    cin >> user_text;
                    if(user_text == "No" || user_text == "no") break;
                }


            }


            if(net_construct2 == 0) 
            {
                cout << "Lerning rate will set default." << endl;
                cout << "Library data for digits contains 30 images. " << endl;
                cout << "How much images do you want to set for trainig? " << endl;
                cin >> net_construct;

                cout << "TRAINIG PROCESS IS STARTING." << endl;
                this_thread::sleep_for(chrono::seconds(2));
                Dataset dataset("letters.txt");
                n.Train(init, dataset, net_construct);

                string user_text;
                while(1)
                {
                    cout << endl << "Enter name of your file with image for network testing: " << endl;
                    cin >> user_text;

                    Dataset one_digit(user_text, 's');

                    n.Test(init, one_digit, 's');

                    cout << "Do you want to continue? (Yes / No)" << endl;
                    cin >> user_text;
                    if(user_text == "No" || user_text == "no") break;
                }
                
            }
            
        }
    }






    /////////////////////////////////////////////////////////////////////////////////
    //                    message about  an input error of user                    //
    /////////////////////////////////////////////////////////////////////////////////
    if(user_choice1 != 1 && user_choice1 != 2 && user_choice1 != 3)
    {
        cout << "Invalid input: " << user_choice1 << endl;
    }


    return 0;
}