#include <iostream>//for work in console
#include <array>//array from STL
#include <fstream>//for work with files
#include <string>//for getline() using in this program
#include <sstream>//flows of strings
#include <vector>//dynamic array from STL

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
Second input has weight = 0.3
Third input has weight = 0.6

We assume also that a function of activation for the neuron has such form:

value = First input * Fist weight + Second input * Second weight + \
        Third input * Third weight

if(value>=0.5) return 1;   - the student passed the exam
else return  0;            - the student didn't pass the exam

In the end, we have one value only.

!!!!! Weights can change in a learning process of the neuron.
*/

class Neuron{
    private:
        array<double,3> weights = {0.2, 0.3, 0.6};//Setting random values for weights
        //array<double,3> motivation = {1.0, 1.5 , 2.0};
        //array<double,3> error = {0.0, 0.0, 0.0};//Errors for each weights
        double error;
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
    //double correction = (error / current_result);
    //cout << "correction = " << correction << endl;

    for (int i = 0; i < size; i++)
    {

        weights[i] += correction;
    }
}

double Neuron::GetWeight(int i)
{
    return weights[i];
}

//////////////////////////////////////////////////////////////////////////////////////////

int main(){
    
    /*Data for the neuron training are keeping in file "right_answers.txt"
    This is a database of a last exam for many students, their progresses and results.
    Progresses consist 3 numbers. They are inputs parameters for neuron (INPUT).
    Results are numbers in the end of each string (OUTPUT).
    */
    ifstream fin;//entry flow in file
    string path = "right_answers.txt";//the name of a file are keeping as a string
    ofstream fout;//exit flow from file

    fin.open(path);//It's a file opening
    if (!fin.is_open())//This is the checking that file was opened
    {
        cout << "Error to open your file" << endl;
    }
    else{
        cout << "The file with name " << path << " was opened." << endl;
    }

    //tuple<string,double,double,double,double> temp;

    string str;//temporary parameter for the reading text from the file
    int line = 1;//for the counting of strings into the file

    vector<string> names;
    vector<vector<double>> init_progresses;
    init_progresses.resize(3, vector<double>(0));
    vector<double> out_results;

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
                out_results.push_back(results); 
        }
        else line++;

    }

    fin.close();

    ////////////////////////////////////////////////////////////////////////////

    Neuron n1;//the creating of the neuron

    array<double,3> progress_iii;//input data for learning (array for 3 INPUT)
    double result_i;//input data for learning (it is the right answer( 1 OUTPUT))

    int epoch = 0;//the sequence number of epoch in the learning of the neuron
    
    do
    {  
        for (size_t j = 0; j < init_progresses[0].size(); j++)
        {
            for (size_t i = 0; i < 3; i++)
            {
                progress_iii[i] = init_progresses[i][j];
                result_i = out_results[j];
                //cout << "progress_iii[ " << i << " ] = " << progress_iii[i] << "  result_i = " << result_i << endl;
            }
            n1.Train(progress_iii, result_i);

            if(size_t(j) == init_progresses[0].size()-1) epoch++;
            cout << j << " j,  " << epoch << " epoch, errors:  " << n1.GetError()  << ", weights: " << n1.GetWeight(1) << " | " << n1.GetWeight(2) << " | " << n1.GetWeight(3) << endl;
        } 
    } while (n1.GetError()*0.0001 > n1.GetReducing() || n1.GetError()*0.0001 < -n1.GetReducing());

    cout << "The learning is has done!" << endl;
    
      


    ///////////////////////////////

    //test of out neuron:
    array<double,3> student_progress;
    /*Konstantin remembers of the professor name (1)
      Konstantin didn't visit any lectures of the professor (0)
      Konstantin doesn't knows disciplince at all (0)

      We want to know result of Konstantin*/

    

    string name_student;
    string user_text;
    double temp;

    cout << "____________________________________________" << endl;
    cout << "|                                          |" << endl;
    cout << "|   WELCOME TO OUR ACADENICAL PREDICTOR!   |" << endl;
    cout << "____________________________________________" << endl;
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

        cout << endl;

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