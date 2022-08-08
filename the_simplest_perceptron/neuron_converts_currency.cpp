#include <iostream>

using namespace std;

/////////////////////////////////////////////////////////
/*

THIS IS ONE NEURON MODEL.

The neuron has one INPUT with WEIGHT (W) and one OUTPUT.


          W     ___
INPUT -------->|___|-------> OUTPUT

*/
/////////////////////////////////////////////////////////

/*We are going to give to the neuron information about ruble exchange rate.
And we expect to get on the way out dollar exchange rate.
*/

class Neuron{
    private:
        double weight = 0.4;//We don't know initial value of weight. It's random value.
        double error;//error calculates as RIGHT VALUE minus CURRENT VALUE of program
        double reducing = 0.0001;//additional constant for a deviation reducing

    public:
        double GetError()//function for getting of error value from private area
        {
            return error;
        }

        double GetReducing()//function for getting of reducing value from private area
        {
            return reducing;
        }

        //function for the loading of initial value in the neuron
        //This is a model of INPUT of tne neuron
        double InputData(double init)
        {
            return init * weight;//OUTPUT of tne neuron
        }

        /*The function OutputData(..) is not important!
        It returns the input value according output data only
        The function makes sence in the context of the task of the currency converting*/
        double OutputData(double out)
        {
            return (out / weight);
        }

        /*The function Train() is teaching neuron.
        Tne neuron is learning here.*/
        void Train(double init, double right_result)
        {
            double current_result = init * weight;
            error = right_result - current_result;
            double correction = (error / current_result) * reducing;
            weight += correction;
        }
};

int main(){
    
    double dollar = 1;
    double ruble = 60;

    Neuron n1;//We create an object with Neuron type
    
    int i = 0;
    do// The cycle is for training of the neuron and errors calculation
    {
        i++;
        n1.Train(ruble, dollar);
        cout << i << " epoch, error: " << n1.GetError() << endl;
    } while (n1.GetError() > n1.GetReducing() || n1.GetError() < -n1.GetReducing());

    cout << "The learning has done!" << endl;

    cout << "100" << " RUB is "<< n1.InputData(100) << " USD" << endl;

    cout << "1200" << " RUB is "<< n1.InputData(1200) << " USD" << endl;

    cout << n1.OutputData(1) << " RUB is "<< dollar << " USD" << endl;

    return 0;
}