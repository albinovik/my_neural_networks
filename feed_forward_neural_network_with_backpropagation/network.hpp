#ifndef _NETWORK_HPP_
#define _NETWORK_HPP_

/*#include <iostream>//for work in console
#include <fstream>//for work with files
#include <vector>//dynamic array from STL
#include <chrono>//for time calculation    
#include "reluneuron.hpp"//sturcture of neuron
//#include "structnet.hpp"//sturctures of different images
#include "dataset.hpp"//structure of dataset */

/////////////////////////////////////////////////////
class Network
{
private:
    //int layers;//amout of layers in a neural netwrok
    Neuron **neurons;//2D array for neurons keeping
    double ***weights;//3D aray to keep of bound weights
    double **b_shift_weights;//2D array for b_shift keeping
    int layers;//amout of layers in a neural netwrok
public:
    //Network();
    Network(vector<int> &each_layers);//constructor of forwardfeed network
    ~Network();//destructor
    double GetNeuronsElement(int layers, int position);//function for getting of value of neuron from private area
    double GetNeuronError(int layers, int position);//function for getting of error of neuron from private area  

    //the loading data into the neural network and calculations:
    void SetFirstLayer(double *array);//initial data for neural network (for first layer)
    int MaximumIndex(double *value, int size);//search maximum value in output layer
    void NeuronsLayerActivization(vector<int> &each_layers, int LayerNumber);//each neuron in one layer of the network executes function act()
    int ForwardFeed(vector<int> &each_layers);//all neurons in the network executes function act()
    void BackPropogation(vector<int> &each_layers, int right_answer);//errors calculation
    void WeightsUpdater(vector<int> &each_layers, double learning_rate);//recalculation of weights for bounds
    int CycleOfTrain(vector<int> &neurons_in_each_layer, double *input_data, int right_answer, double learning_rate);//one complete calculation inside a neural network
    void RepeatCyclesOfTrain(vector<int> &neurons_in_each_layer, Dataset data, int examples, double learning_rate);//several complete calculations inside the neural network
    void RepeatCyclesOfTrain(vector<int> &neurons_in_each_layer, Dataset data, int examples);//several complete calculations inside the neural network with the default learning_rate
    void Train(vector<int> &neurons_in_each_layer, Dataset data, int examples, double learning_rate);//Full neural network training
    void Train(vector<int> &neurons_in_each_layer, Dataset data, int examples);//Full neural network training with the default learning_rate
    
    //the work with the final data
<<<<<<< HEAD
    //void SaveWeights(vector<int> &each_layers, std::ofstream &fout);
    void SaveWeights(vector<int> &each_layers, std::ofstream &fout1, std::ofstream &fout2);

    //for testing
    void ReadWeights(vector<int> &each_layers, std::ifstream &fin1, std::ifstream &fin2);
    void Test(vector<int> &each_layers, Dataset datatest);
=======
    void SaveWeights(vector<int> &each_layers, std::ofstream &fout);
>>>>>>> cecdbdf57ff9bb8e4621578ed7e44b327c7b98f6
};



#endif