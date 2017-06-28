//============================================================================
// Name        : Test1.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

class Time
{
  public:
    Time();
    void setTime(int, int, int);
    void printMilitary();
    void printStandard();
  private:
    int hour;
    int minute;
    int second;
};
Time::Time()
{
  hour = minute = second = 0;
}

void Time::setTime(int h, int m, int s)
{
  hour = (h >= 0 && h < 24) ? h : 0;
  minute = (m >= 0 && m < 60) ? m : 0;
  second = (s >= 0 && s < 60) ? s : 0;
}

void Time::printMilitary()
{
  cout << (hour < 10 ? "0 ": " ") << hour << ": " << (minute < 10 ? "0 ": " ")

    << minute << ": " << (second < 10 ? "0 ": " ") << second << endl;
}

void Time::printStandard()
{
  cout << ((hour == 0 || hour == 12) ? 12 : hour % 12) << ": " << (minute < 10
    ? "0 ": " ") << minute << ": " << (second < 10 ? "0 ": " ") << second << ((hour < 12) ? " AM ": " PM ") << endl;
}

int main()
{
  Time t;
  //при това дефиниране автоматично се извиква
    //конструктора на класа Time



  t.printMilitary();//резултат 00:00:00
  t.printStandard();//резултат 12:00:00 AM
  t.setTime (13, 27, 6);
  t.printMilitary();//резултат 13:27:06
  t.printStandard();//резултат 1:27:06 PM
  t.setTime (99, 99, 99);
  t.printMilitary();//резултат 00:00:00
  t.printStandard();//резултат 12:00:00 AM


  return 0;
}

