#include<iostream>
#include<fstream>
#include<sstream>
#include<Windows.h>
using namespace std;
class Airline{
private: 
string Flight,Dept,Dest;
int Seats;



public:
Airline(string flight,string dept,string dest,int seat){
  Flight=flight;
  Dept=dept;
  Dest=dest;
  Seats=seat;
}
string getFlight(){
    return Flight;
}
string getDept(){
    return Dept;
}
string getDest(){
    return Dest;
}

int getSeat(){
    return Seats;
}

};
int main(){
Airline Flight1( "F101","thursday","tokyo",17);
Airline Flight2("F102","Monday","paris",19);

ofstream out("flight.txt");
if(!out){
    cout<<"file can't be found"<<endl;
}
else{
    out<<Flight1.getFlight()<<":"<<Flight1.getDest()<<":"<<Flight1.getDept()<<":"<<Flight1.getSeat()<<endl;
    out<<Flight2.getFlight()<<":"<<Flight2.getDest()<<":"<<Flight2.getDept()<<":"<<Flight2.getSeat()<<endl;
    cout<<"data saved successfully"<<endl;
    out.close();
}
}