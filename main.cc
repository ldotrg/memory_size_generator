#include <iostream>
using namespace std;
#include "e_list.h"
#include "event.h"
#include "random.h"
#include <iomanip>
#include <fstream>
#define     ARRIVAL              1
#define     MAX_ARRIVAL_COUNT    10000
#define     SERVE_RATE           1
#define     GAMMA_VAR            1

fstream file ;

void outputDataFormat(){
    
    file.open("list_of_random_number.txt" , ios ::out | ios::trunc) ;
    file<<" "<<endl;
    file.close() ;
}


void outputDataMessage(double value){
    
    file.open("list_of_random_number.txt" , ios ::out | ios::app) ;
    file<<"random number: "<<value<<endl;
    file.close() ;
}
/*main*/
int main(int argc, char **argv) {

    /* ARRIVAL generator & DEPARTURE generator  */
    double  mean_size = 0;
    unsigned int  event_count = 0;
    double  result = 0;
    double  each_result;
    int seed2=(int)time(0) ;
    int total_num = 0;
    outputDataFormat();
    cout << "Exponential distribution random number generator \n";
    cout << "What's your allocate mean_size: ";
    cin >> mean_size;
    cout << "How many random number: ";
    cin >> total_num;
    //double  arrimean = 1 / arrival_Rate;

    Expon   arrigen(seed2,mean_size);

    
    //double    servmean = 1/SERVE_RATE;
    //Erlang t_a1(seed1, n/lambda_MTC, n/(lambda_MTC)^2) ;
    //Gamma servgen(servmean, GAMMA_VAR);


    E_List* eventptr;
    Event*  event_In;
    Event*  event_Out;


    eventptr = new E_List();
    /*Generate the first event*/
    event_In = new Event();

    event_In->set_allocate_size(arrigen++);
    event_In->setEventType(ARRIVAL);
    *eventptr << *event_In;

    while( event_count < total_num)
    {

        *eventptr >> event_Out;
        each_result = event_Out->get_allocate_size();
        result += event_Out->get_allocate_size();
        cout <<"Random number: "<<setprecision(5)<<each_result<<endl;

        event_In = new Event();
        event_In->set_allocate_size(arrigen++);
        event_In->setEventType(ARRIVAL);
        *eventptr << *event_In;
        event_count++;
        outputDataMessage(each_result);
    }
    cout << "total number of random numbers = "<<total_num<<endl;
    cout << "Allocate Mean Size = "<<result/total_num<<endl;

    
    file.open("list_of_random_number.txt" , ios ::out | ios::app) ;
    file<<"total number of random numbers = "<<total_num<<endl;
    file<<"Allocate Mean Size = "<<result/total_num<<endl;
    file.close() ;


    return 0;
}


