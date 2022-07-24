#include <iostream>//for work in console
#include <fstream>//for work with files
#include <cmath>//mathematical library from C (for pow() using)
#include <vector>//dynamic array from STL    
#include "neuron.hpp" 
#include "network.hpp" 
#include <chrono>


int main(){

    double r1, r2, r3;

    vector<int> init = {10, 6, 4, 2};
    /*
    first layer contains 3 neurons
    second layer contains 2 neurons
    third layer contains 2 neurons
    fourth layer contains 1 neuron
    */

   vector<double> input = {0.01, 0.21, 0.45, 0.01, 0.21, 0.45, 0.84, 0.90, 0.05, 0.18};
   /*
   First layer cantains 3 neurons.
   Therefore, we can input data for 3 neurons only.
   This data for first layer only.
   */


    Network n2(init);

    cout.precision(50);

    n2.SetFirstLayer(input);//loading data into first layaer of the neural network 
    cout << "data of netwroks after first layer setting (1 itteration): " << endl;
    for (int i = 0; i < init.size(); i++)
    {
        for (int j = 0; j < init[i]; j++)
        {
            cout << "neurons["<< i << "][" << j << "] = " << n2.GetNeuronsElement(i, j) << "   error["<< i << "][" << j << "] = " << n2.GetNeuronError(i, j) << endl;
        }
    }
    cout << endl;

    int temp = n2.ForwardFeed(init);//activization of all neurons and output data calculation
    cout << "data of networks after ForwardFeed()  (1 itteration): " << endl;
    for (int i = 0; i < init.size(); i++)
    {
        for (int j = 0; j < init[i]; j++)
        {
            cout << "neurons["<< i << "][" << j << "] = " << n2.GetNeuronsElement(i, j) << "   error["<< i << "][" << j << "] = " << n2.GetNeuronError(i, j) << endl;
        }
    }
    cout << endl;

    cout << "data of networks after BackPropagation()  (1 itteration): " << endl;
    n2.BackPropogation(init, temp);
    
    for (int i = 0; i < init.size(); i++)
    {
        for (int j = 0; j < init[i]; j++)
        {
            cout << "neurons["<< i << "][" << j << "] = " << n2.GetNeuronsElement(i, j) << "   error["<< i << "][" << j << "] = " << n2.GetNeuronError(i, j) << endl;
        }
    }
    cout << endl;

    n2.WeightsUpdater(init, 0.5);

    vector<double> input2 = {0.31, 0.24, 0.08, 011, 0.11, 0.15};
    n2.SetFirstLayer(input2);
    cout << "data of netwroks after first layer setting (2 itteration): " << endl;
    for (int i = 0; i < init.size(); i++)
    {
        for (int j = 0; j < init[i]; j++)
        {
            cout << "neurons["<< i << "][" << j << "] = " << n2.GetNeuronsElement(i, j) << "   error["<< i << "][" << j << "] = " << n2.GetNeuronError(i, j) << endl;
        }
    }
    cout << endl;



    int temp2 = n2.ForwardFeed(init);//activization of all neurons and output data calculation
    cout << "datat of networks after ForwardFeed()  (2 itteration): " << endl;
    for (int i = 0; i < init.size(); i++)
    {
        for (int j = 0; j < init[i]; j++)
        {
            cout << "neurons["<< i << "][" << j << "] = " << n2.GetNeuronsElement(i, j) << "   error["<< i << "][" << j << "] = " << n2.GetNeuronError(i, j) << endl;
        }
    }
    cout << endl;

    cout << "datat of networks after BackPropagation()  (2 itteration): " << endl;
    n2.BackPropogation(init, temp2);
    
    for (int i = 0; i < init.size(); i++)
    {
        for (int j = 0; j < init[i]; j++)
        {
            cout << "neurons["<< i << "][" << j << "] = " << n2.GetNeuronsElement(i, j) << "   error["<< i << "][" << j << "] = " << n2.GetNeuronError(i, j) << endl;
        }
    }

    cout << endl << endl << endl;

  
  
  
  /*  double right_answers = 0, right, predict, maxra = 0;
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
*/
    return 0;
}