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

    //double ra = 0;//anount of right answers from neural netwrok
    int right_answers_number = 0;
    double ra = 0;
    double maxra = 0;
    int epoch = 0;
    chrono::duration<double> time;
    double lr = 0.15 * exp(-epoch / 20.);//function learning_rate (to control temp of training)
    //double lr = 0.87 ;
    int examples = 67;//amount of datasets for training
    int repeat = 0, tail = 0;//additional parameters to repate training
    auto begin = chrono::steady_clock::now();
    while ((ra / examples * 100 ) < 100) {
        //int right_answers_number = 0;
        auto t1 = chrono::steady_clock::now();

        //calculation of steps of training
        repeat = examples / ss.size();
        //cout << "repeat = " << repeat << endl;
        if(repeat == 0) 
        {
            right_answers_number = n.RepeatCycleOfTrain(init, ss, lr, examples);
            cout << " right_answers_number = "<< right_answers_number << endl;
            //ra += right_answers_number; 
            ra = right_answers_number;
            epoch++;
            auto t2 = chrono::steady_clock::now();
            time = t2 - t1;
            if (ra > maxra) maxra = ra;
            cout << "right answers (%): " << (ra / examples) * 100 << "\t" << "maximum of right answers (%): " << maxra / examples * 100 << "\t" << "epoch: " << epoch << "\tTIME: " << time.count() << endl;
        }
        else
        {
            vector<int> re_examples(repeat, ss.size());
            tail = (examples - (repeat * ss.size()));
            re_examples.push_back(tail);

            int add_j = 0;
            while(add_j < re_examples.size())
            {
                //cout << re_examples[add_j] << endl;
                right_answers_number = n.RepeatCycleOfTrain(init, ss, lr, re_examples[add_j]);
                //cout << " right_answers_number = "<< right_answers_number << endl;
                //ra += right_answers_number; 
                ra = right_answers_number;
                epoch++;
                auto t2 = chrono::steady_clock::now();
                time = t2 - t1;
                if (ra > maxra) maxra = ra;
                cout << "right answers (%): " << ra / examples * 100 << "\t" << "maximum of right answers (%): " << maxra / examples * 100 << "\t" << "epoch: " << epoch << "\tTIME: " << time.count() << endl;
                add_j++;
                //if (epoch == 100) 
                 //   break;
            }
        }
        //ra += right_answers_number; 
        //cout << ra << endl;
        //reference information
       /* auto t2 = chrono::steady_clock::now();
        time = t2 - t1;
        if (ra > maxra) maxra = ra;
        cout << "amount of right answers: " << ra / examples * 100 << "\t" << "maxra: " << maxra / examples * 100 << "\t" << "epoch: " << epoch << "\tTIME: " << time.count() << endl;*/
        //epoch++;
        if (epoch == 20) 
            break;
    }
    auto end = chrono::steady_clock::now();
    time = end - begin;
    cout << "TIME: " << time.count() / 60. << " min" << endl;

    //cout << endl << endl << examples / ss.size() << endl;
    
    

   /*
   First layer cantains 3 neurons.
   Therefore, we can input data for 3 neurons only.
   This data for first layer only.
   */

    //NW.SaveWeights();

    return 0;
}