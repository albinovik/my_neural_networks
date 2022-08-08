#ifndef _NEURON_HPP_
#define _NEURON_HPP_



class Neuron{
private:
    double value;
    double error;
public:
    Neuron();//constructor
    Neuron(double value, double error);//constructor with parameters
    Neuron operator=(const Neuron &another);//operator= reloading
    double GetValue();//function for getting of value from private area
    double GetError();//function for getting of error from private area
    void SetValue(double value);//function for setting of value in private area
    void SetError(double value);//function for setting of error in private area
    void act();//activation function
    
};

double act_dev(double x);//the derivative of the sigmoid


#endif