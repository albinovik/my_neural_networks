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
    double act_dev(double x);//the derivative of the sigmoid
};

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
    value = (1 /( 1 + pow(2.71828, -value)));//sigmoid
}

double act_dev(double x)//the derivative of the sigmoid
{
    if((fabs(x -1) < 1e-9) || (fabs(x) < 1e-9)) return 0.0;
    return (x * (1.0 - x));
}

#endif