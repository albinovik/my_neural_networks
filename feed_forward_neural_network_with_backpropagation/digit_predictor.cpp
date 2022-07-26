#include <iostream>//for work in console
#include <fstream>//for work with files
#include <cmath>//mathematical library from C (for pow() using)
#include <vector>//dynamic array from STL  
#include <chrono>//for time calculation 
#include "neuron.hpp" 
#include "network.hpp" 
#include "dataset.hpp"


int main(){


    Dataset p("test.txt", "MNIST");
    cout << p.GetStr() << "  " << p.GetElement() << endl;
   // p.ShowData();

    vector<int> init = {784, 256, 10};
    /*
    first layer contains 784 neurons
    second layer contains 256 neurons
    third layer contains 10 neurons
    */

   vector<vector<double>> data = p.GetPixels();

   cout << data[0].size() << "    " << data.size() << endl;

   cout << &data[0][3] << "  " <<  &data[1][3] << endl;

    cout << data[0][155] << "  " <<  data[1][158] << endl;

   /* for (size_t i = 0; i < data.size(); i++)
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
        
    }*/

    Network n(init);

    cout.precision(10);

    vector<double> input;

    //cout << p.GetPixels().size();

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
        repeat = examples / p.GetPixels().size();
        //cout << "repeat = " << repeat << endl;
        if(repeat == 0) 
        {
            right_answers_number = n.RepeatCycleOfTrain(init, data, lr, examples);
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
            vector<int> re_examples(repeat,  p.GetPixels().size());
            tail = (examples - (repeat *  p.GetPixels().size()));
            re_examples.push_back(tail);

            int add_j = 0;
            while(add_j < re_examples.size())
            {
                //cout << re_examples[add_j] << endl;
                right_answers_number = n.RepeatCycleOfTrain(init, data, lr, re_examples[add_j]);
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