#include <iostream>//for work in console
#include <array>//array from STL
#include <fstream>//for work with files
#include <string>//for getline() using in this program
#include <sstream>//flows of strings
#include <vector>//dynamic array from STL
#include <chrono>
#include <thread>

using namespace std;

/*
A MODEL OF THE NEURON:

           W1     ___
1 INPUT -------->|   |
           W2    |   |
2 INPUT -------->|   |------> 1 OUTPUT
           W3    |   |
3 INPUT -------->|___|

The neuron can answer the question: 
"Can this student pass the exam?"

Neuron has 3 inputs:

First input:    a student remembers the name of the professor          1
                a student doesnt't remember the name of the professor  0
Second input:   a student always visited lectures of the professor     1
                a student didn't visit any lectures of the professor   0
Third:          a student good knows disciplince                       1
                a student does't know disciplince at all               0

Each inputs has its own weights.

We can initialize random values, for example:
First input has weight = 0.2
Second input has weight = 0.8
Third input has weight = 0.1

We assume also that a function of activation for the neuron has such form:

value = First input * Fist weight + Second input * Second weight + \
        Third input * Third weight

if(value>=0.5) return 1;   - the student will pass the exam
else return  0;            - the student won't pass the exam

In the end, we have one value only.

!!!!! Weights is changing in a learning process of the neuron.
*/

class Neuron{
    private:
        array<double,3> weights = {0.2, 0.8, 0.1};//Setting random values for weights
        double error = 1.0;
        double reducing = 0.00001;//additional constant for a deviation reducing
        const int size = 3;//All arrays in this program have size is 3
        

    public:
        double GetError();//function for getting of error value from private area
        double GetReducing();//function for getting of reducing value from private area
        double GetSize();//function for getting of size value from private area
        double GetWeight(int i);//function for getting of size value from private area

        double InputData(array<double,3> &init);//function for the loading of initial value in the neuron

        /*The function Train() is teaching the neuron.
        Tne neuron is learning here.
        That means that its weights are changing every epoch.*/
        void Train(array<double,3> &init, double &right_result);
};

double Neuron::GetError()
{
    return error;
}

double Neuron::GetReducing()
        {
            return reducing;
        }

double Neuron::GetSize()
{
    return reducing;
}

double Neuron::InputData(array<double,3> &init)
{
    double value;
    for (int i = 0; i < size; i++)
    {
        value += init[i] * weights[i];
    } 
    return value;   
}

void Neuron::Train(array<double,3> &init, double &right_result)
{
    double current_result =InputData(init);
    error = right_result - current_result;
    double correction = (error / current_result) * reducing;

    for (int i = 0; i < size; i++)
    {

        weights[i] += correction;
    }
}

double Neuron::GetWeight(int i)
{
    return weights[i];
}

//////////////////////////////////////////////////////////////////////////////////////
//                         function beyond any classes                              //
//////////////////////////////////////////////////////////////////////////////////////
//double * read_file_for_leaning(string filename)
vector<vector<double>> read_file_for_leaning(string filename)
{

    /*Data for the neuron training are keeping in file "right_answers.txt"
    This is a database of a last exam for many students, their progresses and results.
    Progresses consist 3 numbers. They are inputs parameters for neuron (INPUT).
    Results are numbers in the end of each string (OUTPUT).
    */
    ifstream fin;//entry flow in file
    //string path = "right_answers.txt";//the name of a file are keeping as a string
    ofstream fout;//exit flow from file

    fin.open(filename);//It's a file opening
    if (!fin.is_open())//This is the checking that file was opened
    {
        cout << "Error to open your file" << endl;
    }
    else{
        cout << "The file with name \"" << filename << "\" was opened." << endl;
    }

    //tuple<string,double,double,double,double> temp;

    string str;//temporary parameter for the reading text from the file
    int line = 1;//for the counting of strings into the file

    vector<string> names;
    vector<vector<double>> init_progresses;
    init_progresses.resize(4, vector<double>(0));
    //vector<double> out_results;

    string name;
    double a, b, c, results;
    int count = 0;

    while (!fin.eof())
    {
        getline(fin, str);
        if(line > 2)
        { 
            istringstream ss(str);
            ss >> name >> a >> b >> c >> results;
            //cout << a << "  " << b << "  " << c << "  " << results << endl;
                names.push_back(name);
                init_progresses[0].push_back(a);
                init_progresses[1].push_back(b);
                init_progresses[2].push_back(c);
                init_progresses[3].push_back(results);
                //out_results.push_back(results); 
        }
        else line++;

    }

    fin.close();

    return init_progresses;

}


//////////////////////////////////////////////////////////////////////////////////////////

int main(){

    Neuron n1;//the creating of the neuron

    array<double,3> progress_iii;//input data for learning (array for 3 INPUT)
    double result_i;//input data for learning (it is the right answer( 1 OUTPUT))
    int epoch = 0;//the sequence number of epoch in the learning of the neuron

    vector<vector<double>> data = read_file_for_leaning("right_answers.txt");//reading file with data for leaning process

    cout << "Please wait for the finish of the neuron training. " << endl;
    cout << "It can take a few minutes " ;//<< endl;

    /*for(int i = 0; i < 10; i++)
    {
        this_thread::sleep_for(chrono::seconds(2));
        cout << ". " ;
    }*/

    int rang = int(data[0].size()); 
 
    int control = 1;

    while(n1.GetError()*0.001 > n1.GetReducing() || n1.GetError()*0.001 < -n1.GetReducing())
    {
        for (size_t j = 0; j < rang; j++)
        {
            progress_iii[0] = data[0][j]; 
            progress_iii[1] = data[1][j];
            progress_iii[2] = data[2][j];
            result_i = data[3][j];

            n1.Train(progress_iii, result_i);

        }
        //cout << ".";
        epoch++;
        if(epoch % 125 == 0) 
        {
            this_thread::sleep_for(chrono::seconds(1));
            cout << ". " ;
        }
        //cout << "   epoch: " << epoch << "   errors: " << n1.GetError()  << "   weights: " << n1.GetWeight(1) << " | " << n1.GetWeight(2) << " | " << n1.GetWeight(3) << endl;
        if(epoch == 2000) break;
    }

    //do
    //{


    /*while(n1.GetError()*0.001 > n1.GetReducing() || n1.GetError()*0.001 < -n1.GetReducing())
    {
        for (size_t j = 0; j < rang; j++)
        {
            //cout << "[ " << j << " ]     " << endl;
            for (size_t i = 0; i < 4; i++)
            {
                if (i <= 2)
                {
                    progress_iii[i] = data[i][j];
                    //cout <<  " progress_iii[ " << i << " ] = " << progress_iii[i] << " " ;
                }
                else
                {
                    result_i = data[i][j];
                    //cout << "  result_i = " << result_i << endl;
                }
            }
            n1.Train(progress_iii, result_i);
            if(size_t(j) == data[0].size()-1) epoch++;
            //cout << ".";// << endl;
            cout << " j: " << j  << "   epoch: " << epoch << "   errors: " << n1.GetError()  << "   weights: " << n1.GetWeight(1) << " | " << n1.GetWeight(2) << " | " << n1.GetWeight(3) << endl;
            //cout << endl;
       }
    }*/
 

    //} while (n1.GetError()*0.01 > n1.GetReducing() || n1.GetError()*0.01 < -n1.GetReducing());

    cout << endl << "The training of the neuron has done!" << endl;

    //cout << " weights: " << n1.GetWeight(1) << " | " << n1.GetWeight(2) << " | " << n1.GetWeight(3) << endl;
    
    ///////////////////////////////

    //test of out neuron:
    array<double,3> student_progress;
    

    string name_student;
    string user_text;
    double temp;

    this_thread::sleep_for(chrono::seconds(2));

    cout << "____________________________________________" << endl;
    cout << "|                                          |" << endl;
    cout << "|   WELCOME TO OUR ACADEMICAL PREDICTOR!   |" << endl;
    cout << "|__________________________________________|" << endl;
    cout << endl;
    cout <<  "You are the professor of a prestigious university." << endl;
    cout << "You are teaching the course \"Neuron Networks\"." << endl;
    cout <<  "Now it has already happened the end of the semester." << endl;
    cout << "You have to take exams with your students." << endl;
    cout << endl;
    cout << "        OUR NEURON CAN HELP YOU!!!        " << endl;
    cout << endl;

    while(1)
    {

        cout << "Enter name of your student (one word only): " << endl;
        cin >> name_student;
        //if(name_student == "exit") break;
        cout << "Does the student remember your name? (Enter 1, if Yes / Enter 0, if No) :" << endl;
        cin >> temp;
        student_progress[0] = temp;
        //cout << "If he(she) does, enter 1. If he(she) doesn't, enter 0: " << endl;
        cout << "Did the student visit all your lectures? (Enter 1, if Yes / Enter 0, if No) :" << endl;
        cin >> temp;
        student_progress[1] = temp;
        cout << "Does the student know the discipline \"Neuron Networks\"? (Enter 1, if Yes / Enter 0, if No) :" << endl;
        cin >> temp;
        student_progress[2] = temp;

        //cout << endl;

        double tmp = n1.InputData(student_progress);

        if(tmp >=0.5)
        {
            cout << "RESULT:   The student "<< name_student << " will pass the exam." << endl;
        }
        else
        {
            cout << "RESULT:   The student " << name_student << " won't pass the exam." << endl;
        }
        cout << endl << endl;
        //cout << "Enter \"exit\" as a name of student for exit from program!" << endl;
        //cout << endl << endl;
        cout << "Do you want to continue? (Yes / No)" << endl;
        cin >> user_text;
        if(user_text == "No" || user_text == "no") break;
    }
    
    return 0;//the end of the program
}