#include <iostream>//for work in console
#include <fstream>//for work with files
#include <vector>//dynamic array from STL
//#include <array>//static array from STL
#include <chrono>//for time calculation
#include <cmath>    
#include "reluneuron.hpp"//sturcture of neuron
#include "structnet.hpp"//sturctures of different images
#include "dataset.hpp"//structure of dataset 
#include "network.hpp"

using namespace std;


/////////////////////////////////////////////////////

/*Network::Network()
{
    layers = 0;
    int size = 0;
    //neurons->SetValue(0.0);
    neurons = new Neuron * [size];
    neurons[0] = new Neuron [size];
    neurons[0]->SetValue(0.0);
    neurons[0]->SetError(0.0);
    //neurons[size][size] = 0;
    weights[size][size][size] = 0;
}*/

Network::Network(vector<int> &each_layers)
{
    layers = each_layers.size();

    //srand(time(0));//random generation number
        neurons = new Neuron * [layers];
        weights = new double ** [layers - 1];
        b_shift_weights = new double * [layers - 1];
        for (int i = 0; i < layers; i++)
        {
            neurons[i] = new Neuron [each_layers[i]];
            b_shift_weights[i] = new double [each_layers[i]];
            if (i < (layers - 1))
            {
                weights[i] = new double *[each_layers[i]];
                for (int j = 0; j < each_layers[i]; j++)
                {

                   b_shift_weights[i][j] = (rand() % 50) *0.06 / (each_layers[i] + 20);
                    weights[i][j] = new double [each_layers[i + 1]];
                    for (int k = 0; k < each_layers[i + 1]; k++)
                    {

                         weights[i][j][k] = ((rand() % 100)) * 0.03 / (each_layers[i + 1] + 20);

                    } 
                
                }            
            }         
        }    

}

Network::~Network()
{}

double Network::GetNeuronsElement(int layers, int position)
{
    return neurons[layers][position].GetValue();
}

double Network::GetNeuronError(int layers, int position)
{
    return neurons[layers][position].GetError();
}

//void Network::SetFirstLayer(vector<double> &array)
void Network::SetFirstLayer(double *array)
   {
        for (int i = 0; i < 784; i++)
        {
            neurons[0][i].SetValue(array[i]);
            //cout << neurons[0][i].GetValue() << endl;
        }
   }

int Network::MaximumIndex(double *value, int size)
{
    double maxi = value[0];
    int p = 0;
    double tmp2;
    for (int i = 0; i < size; i++)
    {
        tmp2 = value[i];
        if(tmp2 > maxi)
        {
            p = i;
            maxi = tmp2;
        }
    }
    return p;
}

void Network::NeuronsLayerActivization(vector<int> &each_layers, int LayerNumber)
{
    if(LayerNumber == 0)
    {
        for (int j = 0; j < each_layers[LayerNumber]; j++)
        {
            neurons[LayerNumber][j].act();
        }
    }
    else
    {
        for (int j = 0; j < each_layers[LayerNumber]; j++)//neuron number in current layer (amouht of weights)
        {
            double tmp = 0.0;
            for (int k = 0; k < each_layers[LayerNumber - 1]; k++)//neuron number in previous layer
            {
                //double tmp = 0.0;
                tmp += neurons[LayerNumber - 1][k].GetValue() * weights[LayerNumber - 1][k][j];
                //neurons[LayerNumber][j].SetValue(tmp);
            }
            neurons[LayerNumber][j].SetValue(tmp);
            tmp = b_shift_weights[LayerNumber - 1][j] + neurons[LayerNumber][j].GetValue();
            neurons[LayerNumber][j].SetValue(tmp);
            neurons[LayerNumber][j].act();            
        }  
    }
}

int Network::ForwardFeed(vector<int> &each_layers)
{
    //layers = each_layers.size();
    for (int i = 0; i < layers; i++)
    {
        NeuronsLayerActivization(each_layers, i);
    }
    //double *tmp = new double;
    double tmp[each_layers[layers - 1]];
    for (int i = 0; i < each_layers[layers - 1]; i++)
    {
        tmp[i] = neurons[layers - 1][i].GetValue();
    }  
    int prediction = MaximumIndex(tmp, each_layers[layers - 1]);
    //delete tmp;

    return prediction;
}

void Network::BackPropogation(vector<int> &each_layers, int right_answer) {
	for (int i = 0; i < each_layers[layers - 1]; i++) {
		if (i != right_answer)
        {
            double tmp = - (neurons[layers - 1][i].GetValue() * act_dev(neurons[layers - 1][i].GetValue()));
            neurons[layers - 1][i].SetError(tmp);
        }
		else
        {
            double tmp = (1.0 - neurons[layers - 1][i].GetValue()) * act_dev(neurons[layers - 1][i].GetValue());
            neurons[layers - 1][i].SetError(tmp);
        }
	}
	for (int i = layers - 2; i >= 0; i--) 
    {
        //double tmp2 = 0.0;
		for (int j = 0; j < each_layers[i]; j++)
        {
            double tmp = 0.0;
            for (int k = 0; k < each_layers[i + 1]; k++)
            {
                tmp += (weights[i][j][k] * neurons[i + 1][j].GetError());
                //neurons[i][j].SetError(tmp);
            }
            neurons[i][j].SetError(tmp);
            //tmp2 = neurons[i][j].GetError();
            for (int j = 0; j < each_layers[i]; j++)
            {
                
                tmp *= act_dev(neurons[i][j].GetValue());
                neurons[i][j].SetError(tmp);
            }
        }
	}
}


int Network::CycleOfTrain(vector<int> &neurons_in_each_layer, double *input_data, int right_answer, double learning_rate)
{
    SetFirstLayer(input_data);
    int predict = ForwardFeed(neurons_in_each_layer);
    if (predict != right_answer) {
        BackPropogation(neurons_in_each_layer, right_answer);
        WeightsUpdater(neurons_in_each_layer, learning_rate);
        return 0;
    }
    else return 1;
}

void Network::RepeatCyclesOfTrain(vector<int> &neurons_in_each_layer, Dataset data, int examples, double learning_rate)
{
    double right_answers_number = 0.0;
    double maxra = 0;
    int epoch = 0;
    chrono::duration<double> time;
    int count = 0;
    
    ////////////////////////////////////////////////////////////////////////////////////
    ofstream fout1, fout2;//element of ofstream class is creating                    ///
    fout1.open("b_shifts.txt");//file "b_shifts.txt" for b_shifts writing is opening ///
    fout2.open("weights.txt");//file "weights.txt" for weights writing is opening    ///
    ////////////////////////////////////////////////////////////////////////////////////

    auto begin = chrono::steady_clock::now();
    while((right_answers_number / examples * 100 ) < 100)
    {
        auto t1 = chrono::steady_clock::now();
        for (size_t i = 0; i < examples; i++)
        {
            count = CycleOfTrain(neurons_in_each_layer, data.GetPixelLayer(i), data.GetElement(i), learning_rate);
        }
        epoch++;
        right_answers_number += count;
        //ra = 
        auto t2 = chrono::steady_clock::now();
        time = t2 - t1;
        if (right_answers_number > maxra) maxra = right_answers_number;
            cout << "right answers (%): " << (right_answers_number / examples) * 100 << "\t" << "maximum of right answers (%): " << maxra / examples * 100 << "\t" << "epoch: " << epoch << "\tTIME: " << time.count() << endl;

        if (epoch == 500) break;
    }

    auto end = chrono::steady_clock::now();
    time = end - begin;
    cout << "TIME: " << time.count() / 60. << " min" << endl;

    /////////////////////////////////////////////////////////////////////////////////
    SaveWeights(neurons_in_each_layer, fout1, fout2);                             ///
    fout1.close();                                                                ///
    fout2.close();                                                                ///
    /////////////////////////////////////////////////////////////////////////////////
}



void Network::RepeatCyclesOfTrain(vector<int> &neurons_in_each_layer, Dataset data, int examples)
//void Network::RepeatCyclesOfTrain(vector<int> &neurons_in_each_layer, MNIST data, int examples, double koef)
{
    double right_answers_number = 0.0;
    double maxra = 0;
    int epoch = 0;
    double learning_rate;
    chrono::duration<double> time;
    int count = 0;
    //cout << "1:       I AM WORKING UNTIL HERE!!!" << endl;

    ////////////////////////////////////////////////////////////////////////////////////
    ofstream fout1, fout2;//element of ofstream class is creating                    ///
    fout1.open("b_shifts.txt");//file "b_shifts.txt" for b_shifts writing is opening ///
    fout2.open("weights.txt");//file "weights.txt" for weights writing is opening    ///
    ////////////////////////////////////////////////////////////////////////////////////

    //cout << "2:       I AM WORKING UNTIL HERE!!!" << endl;

    auto begin = chrono::steady_clock::now();
    while((right_answers_number / examples * 100 ) < 100)
    {
        //cout << "1:       I AM WORKING UNTIL HERE!!!" << endl;       
        learning_rate =  0.15 * exp(-epoch / 20.);//leaning rate default function

        auto t1 = chrono::steady_clock::now();
        for (size_t i = 0; i < examples; i++)
        {
            //cout << "2:       I AM WORKING UNTIL HERE!!!" << endl;
            count = CycleOfTrain(neurons_in_each_layer, data.GetPixelLayer(i), data.GetElement(i), learning_rate);
        }
        epoch++;
        right_answers_number += count;
        //ra = 
        auto t2 = chrono::steady_clock::now();
        time = t2 - t1;
        
        if (right_answers_number > maxra) maxra = right_answers_number;
            cout << "right answers (%): " << (right_answers_number / examples) * 100 <<  "\tmaximum of right answers (%): " << maxra / examples * 100 << "\t" << "epoch: " << epoch << "\tTIME: " << time.count() << endl;

        if (epoch == 500)
        {
            //SaveWeights(neurons_in_each_layer);
            break;
        } //break;
    }

    auto end = chrono::steady_clock::now();
    time = end - begin;
    cout << "TIME: " << time.count() / 60. << " min" << endl;

    /////////////////////////////////////////////////////////////////////////////////
    SaveWeights(neurons_in_each_layer, fout1, fout2);                             ///
    fout1.close();                                                                ///
    fout2.close();                                                                ///
    /////////////////////////////////////////////////////////////////////////////////
}


void Network::Train(vector<int> &neurons_in_each_layer, Dataset data, int examples, double learning_rate)
{
    cout << "You have selected " << examples << " for training." << endl;

    if(examples <= data.GetSize()) 
    {
        RepeatCyclesOfTrain(neurons_in_each_layer, data, examples, learning_rate);
    }
    else
    {
        cout << "The number of examples that you wnat to set is larger than the number of examples in file with dataset." << endl; 
    }
}

void Network::Train(vector<int> &neurons_in_each_layer, Dataset data, int examples)
{
    cout << "You have selected " << examples << " for training." << endl;

    if(examples <= data.GetSize()) 
    {
        RepeatCyclesOfTrain(neurons_in_each_layer, data, examples);
    }
    else
    {
        cout << "The number of examples that you wnat to set is larger than the number of examples in file with dataset." << endl; 
    }
}




void Network::WeightsUpdater(vector<int> &each_layers, double learning_rate) 
{
    for (int i = 0; i < layers - 1; i++)
    {
        for (int j = 0; j < each_layers[i]; j++)
        {
            for (int k = 0; k < each_layers[i + 1]; k++)
            {
                weights[i][j][k] += neurons[i][j].GetValue() * neurons[i + 1][k].GetError() * learning_rate;
            }                   
        }                   
    }
    for (int i = 0; i < layers - 1; i++) {
		for (int j = 0; j < each_layers[i + 1]; j++) {
			b_shift_weights[i][j] += neurons[i + 1][j].GetError() * learning_rate;
		}
	}
}


//void Network::SaveWeights(vector<int> &each_layers, std::ofstream &fout)
void Network::SaveWeights(vector<int> &each_layers, std::ofstream &fout1, std::ofstream &fout2)
{
    /* if (fout.is_open())
    {
        cout << "File for writing of final weights is opened." << endl;
    }
    else
    {
        cout << "Error to open file for writing of final weights." << endl;
    }*/

    if (fout1.is_open() && fout2.is_open())
    {
        cout << "Files for writing of final weights and b_shifts are opened." << endl;
    }
    else
    {
        cout << "Error to open files for writing of final weights and b_shifts." << endl;
    }


    for (int i = 0; i < layers - 1; i++)
    {
        for (int j = 0; j < each_layers[i]; j++)
        {
            fout1 << b_shift_weights[i][j] << endl;

            for (int k = 0; k < each_layers[i + 1]; k++)
            {
                fout2 << weights[i][j][k] << endl;
            }    
              
        }  
        if(i == 1) 
        {
            cout << "The writing of weights and b_shifts has been completed successfully." << endl << endl;
        }                 
    }
}

void Network::ReadWeights(vector<int> &each_layers, std::ifstream &fin1, std::ifstream &fin2)
{
    if (fin1.is_open() && fin2.is_open())
    {
        cout << "Files for reading of right weights and b_shifts are opened." << endl;
    }
    else
    {
        cout << "Error to open files for reading of right weights and b_shifts." << endl;
    }


    for (int i = 0; i < layers - 1; i++)
    {
        for (int j = 0; j < each_layers[i]; j++)
        {
            fin1 >> b_shift_weights[i][j];
           // cout << b_shift_weights[i][j] << endl;

            for (int k = 0; k < each_layers[i + 1]; k++)
            {
                fin2 >> weights[i][j][k];
                //cout << weights[i][j][k] << endl;
            }    
            
        }  
        if(i == 1) 
        {
            cout << "Right weights and b_shifts has been loaded successfully." << endl << endl;
        }                 
    }
}


/////////////////////////////////////////////////////////////////////////////////////////////////////

void Network::Test(vector<int> &each_layers, Dataset datatest)
{
    cout << "TESTING OF NEURAL NETWORK IS STARTING. " << endl;

    double right_answer_for_test = datatest.GetElement(0);
    //cout << "right_answer for test: " << right_answer << endl;

    /////////////////////////////////////////////////////////
    //loading in the network rights weights and b_shifts   //
    /////////////////////////////////////////////////////////
    ifstream fin1;                                        ///
    fin1.open("b_shifts.txt");                            ///
    ifstream fin2;                                        ///
    fin2.open("weights.txt");                             ///
                                                          ///
    ReadWeights(each_layers, fin1, fin2);       ///
                                                          ///
    fin1.close();                                         ///
    fin2.close();                                         ///
    /////////////////////////////////////////////////////////

    SetFirstLayer(datatest.GetPixelLayer(0));
    int prediction_for_test = ForwardFeed(each_layers);

    cout << "Result of testing: " << endl;
    cout << "right answer = " << right_answer_for_test << endl;
    cout << "network answer: " << prediction_for_test << endl;

}