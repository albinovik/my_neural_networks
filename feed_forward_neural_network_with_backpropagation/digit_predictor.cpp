#include <iostream>//for work in console
#include <fstream>//for work with files
#include <cmath>//mathematical library from C (for pow() using)
#include <vector>//dynamic array from STL    
#include "neuron.hpp" 
#include "network.hpp" 
#include <chrono>


int main(){

    vector<int> init = {6, 4, 3, 3};
    //size_t tp = init.size();
    /*
    first layer contains 6 neurons
    second layer contains 4 neurons
    third layer contains 3 neurons
    fourth layer contains 3 neurons
    */

    Network n(init);

    cout.precision(10);

    vector<double> data = {0, 1, 2, 3};

    /*for (auto var : data)//for each 
    {
        cout << var << endl;
    }*/

    vector<double> input;
    //cout << init.capacity() << endl;

    vector<vector<double>> ss;
    ss.resize(50, vector<double>(4));
    
    int g = 0;
    for (size_t i = 0; i < 50; i++)
    {
        //cout << "["<< i << "] " ;
        for (size_t j = 0; j < 4; j++)
        {
            if (j <= 2)
            {
                 ss[i][j] = ((rand() * 0.05) / 10000.0);
            }
            else
            {
                if (g < 10)
                {
                    ss[i][j] = 0;
                }
                if( g >= 10 && g < 20)
                {
                    ss[i][j] = 1;
                }
                if( g >= 20 && g < 30)
                {
                    ss[i][j] = 2;
                }
                if( g >= 30)
                {
                    ss[i][j] = 3;
                }
            }
            
            //cout << "\t   [" << j << "] =  " << ss[i][j] << endl;
        }
        g++;
    }

    //vector<double> data = {0, 1, 2};

    //int ppp = ss[0].size();
    //cout << ppp << endl << endl;

    double right_answers = 0, right, predict, maxra = 0;
    int epoch = 0, count = 0;
    chrono::duration<double> time;
    //double learning_rate = 0.15 * exp(-epoch / 20.);
    double lr = 0.15 * exp(-epoch / 20.);
    int examples = 101;
    int repeat = 0, tail = 0;
    //vector<int> re_examples;

    auto begin = chrono::steady_clock::now();
    //while (((right_answers / examples) * 100 ) < 100) {
        int right_answers_number = 0;
        auto t1 = chrono::steady_clock::now();

        //calculation of steps of training
        repeat = examples / ss.size();
        //cout << "repeat = " << repeat << endl;
        if(repeat == 0) 
        {
            right_answers_number = n.RepeatCycleOfTrain(init, ss, lr, examples);
            cout << " right_answers_number = "<< right_answers_number << endl;
        }
        else
        {
            vector<int> re_examples(repeat, ss.size());
            tail = (examples - (repeat * ss.size()));
            re_examples.push_back(tail);

            int add_j = 0;
            while(add_j < re_examples.size())
            {
                cout << re_examples[add_j] << endl;
                right_answers_number = n.RepeatCycleOfTrain(init, ss, lr, re_examples[add_j]);
                add_j++;
            }
        }
        


        //re_examples.clear();
       /* cout << endl;
        for (size_t i = 0; i < re_examples.size(); i++)
        {
            cout << re_examples[i];
        }*/

        /*for (auto var : re_examples)//for each 
        {
            cout << var << endl;
        }*/

        //training of network 
       /* for (size_t k = 0; k < re_examples.size(); k++) 
        {
            for(size_t j = 0; j < re_examples[k]; j++)
            {
                for (size_t i = 0; i < 3; i++)
                {
                    input.push_back(ss[j][i]);
                    right = data[i];
                    count = n.CycleOfTrain(init, input, right, lr);
                    right_answers += count;
                    //cout << right_answers << endl;
                }
                cout << "j = " << endl;
            }
        }*/

        //reference information
        auto t2 = chrono::steady_clock::now();
        time = t2 - t1;
        if (right_answers > maxra) maxra = right_answers;
        //cout << "right_answers: " << right_answers / examples * 100 << "\t" << "maxra: " << maxra / examples * 100 << "\t" << "epoch: " << epoch << "\tTIME: " << time.count() << endl;
        epoch++;
       // if (epoch == 20) 
           // break;
    //}
    auto end = chrono::steady_clock::now();
    time = end - begin;
    //cout << "TIME: " << time.count() / 60. << " min" << endl;

    //cout << endl << endl << examples / ss.size() << endl;
    
    

   /*
   First layer cantains 3 neurons.
   Therefore, we can input data for 3 neurons only.
   This data for first layer only.
   */


   

    

    /*vector<int> input;
    for (size_t i = 0; i < init.size(); i++)
    {
        for (size_t j = 0; j < init[i]; j++)
        {
            input [i] = dataset[i][j] ;
        }
        cout << endl;
    }*/

    /* vector<int> input;
     for (size_t i = 0; i < count; i++)
     {
        input[i];
     }*/
     //int data[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    // int data[3] = {0, 1, 2};
  
    //double right_answers = 0, right, predict, maxra = 0;
    //int epoch = 0, count = 0;
    //chrono::duration<double> time;
    //double learning_rate = 0.15 * exp(-epoch / 20.);
    //double lr = 0.15 * exp(-epoch / 20.);
    //int examples = 4;
    //data = ReadData("lib_MNIST_edit.txt", NW_config, examples);

     /*   for (int i = 0; i < 3; ++i) 
        {
            //n2.SetFirstLayer(input);
            right = data[i];//правильный ответ берем из data[] по индексу i
            count = n2.CycleOfTrain(init, input, right, lr);
            //CycleOfTrain(Network &n, vector<int> &neurons_in_each_layer, vector<double> &input_data, int right_answer, double learning_rate)
            right_answers += count;
            cout << right_answers << endl;
        }*/


   /* auto begin = chrono::steady_clock::now();
    while (((right_answers / examples) * 100 ) < 100) {
        right_answers = 0;
        auto t1 = chrono::steady_clock::now();
        for (int i = 0; i < examples; ++i) 
        {
            //n2.SetFirstLayer(input);
            right = data[i];//правильный ответ берем из data[] по индексу i
            count = n2.CycleOfTrain(init, input, right, lr);
            //CycleOfTrain(Network &n, vector<int> &neurons_in_each_layer, vector<double> &input_data, int right_answer, double learning_rate)
            right_answers += count;
        }
        auto t2 = chrono::steady_clock::now();
        time = t2 - t1;
        if (right_answers > maxra) maxra = right_answers;
        cout << "right_answers: " << right_answers / examples * 100 << "\t" << "maxra: " << maxra / examples * 100 << "\t" << "epoch: " << epoch << "\tTIME: " << time.count() << endl;
        epoch++;
        if (epoch == 20) 
            break;
    }
    auto end = chrono::steady_clock::now();
    time = end - begin;
    cout << "TIME: " << time.count() / 60. << " min" << endl;*/
    //NW.SaveWeights();

    return 0;
}