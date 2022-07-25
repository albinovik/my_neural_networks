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


    Network n(init);

    cout.precision(10);
    //vector<vector<double>> dataset;

   /* for (size_t i = 0; i < init.size(); i++)
    {
        dataset.resize(tp, vector<double>(init[i]));
    }

    for (size_t i = 0; i < init.size(); i++)
    {
        for (size_t j = 0; j < init[i]; j++)
        {
            dataset[i][j] = (rand() * 0.5) / 100.0;
        }
    }*/

   /* for (size_t i = 0; i < init.size(); i++)
    {
        for (size_t j = 0; j < init[i]; j++)
        {
            cout << dataset[i][j] << " ";
        }
        cout << endl;
    }*/
    
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

   /* for (size_t i = 0; i < dataset.size(); i++)
    {
        
    }*/
    

    /*for (auto var : dataset)//for each 
    {
        cout << var << endl;
    }*/



   // vector<double> input = {0.01, 0.21, 0.45, 0.01, 0.21, 0.45};

    vector<double> input;
    //cout << init.capacity() << endl;

    vector<vector<double>> ss;
    ss.resize(50, vector<double>(3));
    

    for (size_t i = 0; i < 50; i++)
    {
        //cout << "["<< i << "] " ;
        for (size_t j = 0; j < 3; j++)
        {
            ss[i][j] =  ((rand() * 0.05) / 10000.0);
            //cout << "\t   [" << j << "] =  " << ss[i][j] << endl;
        }
    }

    vector<double> data = {0, 1, 2};

    //int ppp = ss[0].size();
    //cout << ppp << endl << endl;

    double right_answers = 0, right, predict, maxra = 0;
    int epoch = 0, count = 0;
    chrono::duration<double> time;
    //double learning_rate = 0.15 * exp(-epoch / 20.);
    double lr = 0.15 * exp(-epoch / 20.);
    int examples = 100;
    int repeat = 0, tail = 0;
    //vector<int> re_examples;

    auto begin = chrono::steady_clock::now();
    //while (((right_answers / examples) * 100 ) < 100) {
        right_answers = 0;
        auto t1 = chrono::steady_clock::now();

        //calculation of steps of training
        repeat = examples / ss.size();
        //cout << "repeat = " << repeat << endl;
        if(repeat == 0) 
        {
            int add_i = 0;
            while(add_i < examples)
            {
                for (size_t i = 0; i < ss[0].size(); i++)
                { 
                    input.push_back(ss[add_i][i]);   
                }

                right = data[add_i];
                count = n.CycleOfTrain(init, input, right, lr);
                right_answers += count;
                cout << right_answers << endl;

                add_i++;
                input.clear();
            }
        }
        else
        {
            vector<int> re_examples(repeat, ss.size());
            tail = ((repeat * ss.size()) -examples);
            re_examples.push_back(tail);
            //re_examples.shrink_to_fit();

            int add_j = 0;
            while(add_j < re_examples.size()-1)
            {
           // for (size_t k = 0; k < re_examples.size()-1; k++)
           // {
                //cout << re_examples[k] << endl;
                int add_i = 0;
                while(add_i < re_examples[add_j])
                {
                    for (size_t k = 0; k < ss[0].size(); k++)
                    { 
                        double gg = ss[add_i][k];
                        input.push_back(gg);   
                    }

                    right = data[add_i];
                    count = n.CycleOfTrain(init, input, right, lr);
                    right_answers += count;
                    cout << right_answers << endl;

                    add_i++;
                    input.clear();
                }
           // }
            add_j++;
            }



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