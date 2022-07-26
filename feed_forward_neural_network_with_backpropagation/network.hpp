#ifndef _NETWORK_HPP_
#define _NETWORK_HPP_

#include <iostream>//for work in console
#include <fstream>//for work with files
#include <cmath>//mathematical library from C (for pow() using)
#include <vector>//dynamic array from STL    
#include "neuron.hpp"
#include <chrono>   

using namespace std;

/////////////////////////////////////////////////////
class Network
{
private:
    int layers;//amout of layers in a neural netwrok
    Neuron **neurons;//2D array for neurons keeping
    double ***weights;//3D aray to keep of bound weights
    double **b_shift_weights;//2D array for b_shift keeping
public:
    //Network();
    Network(vector<int> &each_layers);
    ~Network();
    double GetNeuronsElement(int layers, int position);//function for getting of value of neuron from private area
    double GetNeuronError(int layers, int position);//function for getting of error of neuron from private area  
    void SetFirstLayer(vector<double> &array);//initial data for neuron wetwork (for first layer)
    int MaximumIndex(double *value, int size);//search maximum value in output layer
    void NeuronsLayerActivization(vector<int> &each_layers, int LayerNumber);//each neuron in one layer of the network executes function act()
    int ForwardFeed(vector<int> &each_layers);//all neurons in the network executes function act()
    void BackPropogation(vector<int> &each_layers, int right_answer);//errors calculation
    int CycleOfTrain(vector<int> &neurons_in_each_layer, vector<double> &input_data, int right_answer, double learning_rate);
    int RepeatCycleOfTrain(vector<int> &neurons_in_each_layer, vector<vector<double>> &data, double learning_rate, int examples);
    void WeightsUpdater(vector<int> &each_layers, double learning_rate);//recalculation of weights for bounds
    
    void PrintOutputValues(vector<int> &each_layers, int order);//for printing of final result
    void SaveWeights(vector<int> &each_layers);//to save weight for the future   
};

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
                    b_shift_weights[i][j] = (rand() % 50) *0.07 / each_layers[i];
                    weights[i][j] = new double [each_layers[i + 1]];
                    for (int k = 0; k < each_layers[i + 1]; k++)
                    {
                        //we generate random weights
                        weights[i][j][k] = (rand() % 100) *0.01 / each_layers[i];
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

void Network::SetFirstLayer(vector<double> &array)
   {
        for (int i = 0; i < array.size(); i++)
        {
            neurons[0][i].SetValue(array[i]);
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
    double *tmp = new double;
    for (int i = 0; i < each_layers[layers - 1]; i++)
    {
        tmp[i] = neurons[layers - 1][i].GetValue();
    }  
    int prediction = MaximumIndex(tmp, each_layers[layers - 1]);
    delete tmp;

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

int Network::CycleOfTrain(vector<int> &neurons_in_each_layer, vector<double> &input_data, int right_answer, double learning_rate)
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

int Network::RepeatCycleOfTrain(vector<int> &neurons_in_each_layer, vector<vector<double>> &data, double learning_rate, int examples)
{
    vector<double> input;
    int add_i = 0;
    double right = 0.0, right_answers = 0.0;
    int count = 0;
    while(add_i < examples)
    {
        for (size_t i = 0; i < data[0].size()-1; i++)
        { 
            input.push_back(data[add_i][i]);   
        }

        right = data[add_i][data[0].size()-1];
        count = CycleOfTrain(neurons_in_each_layer, input, right, learning_rate);
        right_answers += count;
        cout << right  << "  "<< right_answers << endl;

        add_i++;
        input.clear();
    }
    return right_answers;
}


void Network::WeightsUpdater(vector<int> &each_layers, double learning_rate) 
{
    for (int i = 0; i < layers - 1; i++)
    {
        for (int j = 0; j < each_layers[i]; j++)
        {
            for (int k = 0; k < each_layers[i + 1]; k++)
            {
                //weights[i][j][k] += neurons[i][k].GetValue() * neurons[i + 1][j].GetError() * learning_rate;
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

void Network::PrintOutputValues(vector<int> &each_layers, int order)
{
    
    for (int i = 0; i < each_layers[order]; i++)
    {
        cout << i << " " << neurons[order][i].GetValue();
    }
    
}

void Network::SaveWeights(vector<int> &each_layers)
{
    ofstream fout;
    fout.open("weights.txt");
    for (int i = 0; i < layers; i++)
    {
        if(i < layers - 1)
        {
            for (int j = 0; j < each_layers[i]; j++)
            {
                for (int k = 0; k < each_layers[i + 1]; k++)
                {
                    fout << weights[i][j][k] << endl;
                }
                
            }
            
        }
    }
    fout.close();       
}

/*void reading (string filename)
{
    //vector<double> temp;
    ifstream fin;
    fin.open(filename);//It's a file opening
    if (!fin.is_open())//This is the checking that file was opened
    {
        cout << "Error to open your file" << endl;
    }
    else{
        cout << "The file with name " << filename << " was opened." << endl;
    }

    for (size_t i = 0; i < pixel_amount; i++)
    {
        double tt;
        cout << tt << " " ;
        //fin >> tt; 
        //temp.push_back(tt);
    }

    fin.close();
}*/



#endif