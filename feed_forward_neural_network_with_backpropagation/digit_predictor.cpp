#include <iostream>//for work in console
#include <fstream>//for work with files
#include <cmath>//mathematical library from C (for pow() using)
#include <vector>//dynamic array from STL    
#include "neuron.hpp" 
#include "network.hpp" 
#include <chrono>


int main(){

    //double r1, r2, r3;

    vector<int> init = {6, 4, 3, 3};
    size_t tp = init.size();
    /*
    first layer contains 6 neurons
    second layer contains 4 neurons
    third layer contains 3 neurons
    fourth layer contains 3 neurons
    */
    vector<vector<double>> dataset;

    for (size_t i = 0; i < init.size(); i++)
    {
        dataset.resize(tp, vector<double>(init[i]));
    }

    for (size_t i = 0; i < init.size(); i++)
    {
        for (size_t j = 0; j < init[i]; j++)
        {
            dataset[i][j] = (rand() * 0.5) / 100.0;
        }
    }

    for (size_t i = 0; i < init.size(); i++)
    {
        for (size_t j = 0; j < init[i]; j++)
        {
            cout << dataset[i][j] << " ";
        }
        cout << endl;
    }
    
    /*for (size_t j = 0; j < init[i]; j++)
    {
        for (size_t i = 0; i < init.size(); i++)
        {
            cout << dataset[i][j] << " ";
        }
        cout << endl;
    }*/

    //dataset.resize(tp, vector<int>(n));
    //dataset.resize(tp, vector<double>(0));

    for (size_t i = 0; i < dataset.size(); i++)
    {
        /* code */
    }
    

    /*for (auto var : dataset)//for each 
    {
        cout << var << endl;
    }*/



   //vector<double> input = {0.01, 0.21, 0.45, 0.01, 0.21, 0.45};
   /*
   First layer cantains 3 neurons.
   Therefore, we can input data for 3 neurons only.
   This data for first layer only.
   */


    Network n2(init);

    cout.precision(10);

     vector<int> input;
     for (size_t i = 0; i < count; i++)
     {
        input[i]
     }
     
  
    double right_answers = 0, right, predict, maxra = 0;
    int epoch = 0;
    chrono::duration<double> time;
    //double learning_rate = 0.15 * exp(-epoch / 20.);

    int data[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    int examples = 4;
    //data = ReadData("lib_MNIST_edit.txt", NW_config, examples);
    auto begin = chrono::steady_clock::now();
    while (((right_answers / examples) * 100 ) < 100) {
        right_answers = 0;
        auto t1 = chrono::steady_clock::now();
        for (int i = 0; i < examples; ++i) {
            //NW.SetInput(data[i].pixels);
    //??      input = pixels[i];//тут надо передать целую строку, она каждый раз разная
            n2.SetFirstLayer(input);
            right = data[i];//правильный ответ берем из data[] по индексу i
            predict = n2.ForwardFeed(init);
            if (predict != right) {
                n2.BackPropogation(init, right);
                n2.WeightsUpdater(init, 0.15 * exp(-epoch / 20.));
            }
            else 
                right_answers++;
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
    cout << "TIME: " << time.count() / 60. << " min" << endl;
    //NW.SaveWeights();

    return 0;
}