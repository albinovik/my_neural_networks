#include <cmath>//mathematical library from C (for pow() using)
#include "reluneuron.hpp"

Neuron::Neuron()
{
    error = value = 0.0;
}

Neuron::Neuron(double value, double error)
{
    this->value = value;
    this->error = error;
}

Neuron Neuron::operator=(const Neuron &another)
{
    value = another.value;
    error = another.error;
    return *this;
}

double Neuron::GetValue()//function for getting of error value from private area
{
    return value;
}

double Neuron::GetError()//function for getting of error error from private area
{
    return error;
}

void Neuron::SetValue(double value)//function for getting of error value from private area
{
    this->value = value;
}

void Neuron::SetError(double error)//function for getting of error value from private area
{
    this->error = error;
}

void Neuron::act()//activation function
{
    //ReLU function
    if (value < 0)  0.01 * value;
    else if (value > 1) value = 1. + 0.01 * (value - 1.);
        else value = value;

}

double act_dev(double x)//the derivative of the sigmoid
{
    //the derivative of the ReLU function
    if (x < 0 || x > 1) x = 0.01;
    else x = 1;

    return x;
}