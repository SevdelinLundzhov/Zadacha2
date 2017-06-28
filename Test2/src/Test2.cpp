//============================================================================
// Name        : Test2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

using namespace std;
/*
class Time
 { public:
     Time (int = 0, int = 0, int = 0);
     void setTime (int, int, int);
     void printMilitary ();
     void printStandard ();
   private:
     int hour;
     int minute;
     int second;
  };
Time::Time (int hr, int min, int sec)
 {
	setTime (hr, min, sec);
 }
*/
class CreateAndDestroy
 { public:
    CreateAndDestroy (int);
    ~CreateAndDestroy ();
 private:
     int data;
 } ;
CreateAndDestroy::CreateAndDestroy (int value)
 {
	data = value;
 cout <<" Обект " << data << " конструктор";
 }
CreateAndDestroy::~CreateAndDestroy()
 {
	cout << "Обект " << data << " деструктор" << endl;
 }
void Create ();
CreateAndDestroy first (1);
int main ()
 {
	cout <<  "външен създаден до main" << endl;
   CreateAndDestroy second (2);
   cout << " вътрешен автоматичен в main" << endl;
   static CreateAndDestroy third (3);
   cout << " вътрешен статичен в main" << endl;
   Create ();
   CreateAndDestroy fourth (4);
   cout << " вътрешен автоматичен в main" << endl;

   return 0;
 }
void Create ()
 {
	CreateAndDestroy fifth (5);
   cout << " вътрешен автоматичен в Create" << endl;
   static CreateAndDestroy sixth (6);
   cout << " вътрешен статичен в Create" << endl;
   CreateAndDestroy seventh (7);
   cout << " вътрешен автоматичен в Create" << endl;
 }
