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
 cout <<" ����� " << data << " �����������";
 }
CreateAndDestroy::~CreateAndDestroy()
 {
	cout << "����� " << data << " ����������" << endl;
 }
void Create ();
CreateAndDestroy first (1);
int main ()
 {
	cout <<  "������ �������� �� main" << endl;
   CreateAndDestroy second (2);
   cout << " �������� ����������� � main" << endl;
   static CreateAndDestroy third (3);
   cout << " �������� �������� � main" << endl;
   Create ();
   CreateAndDestroy fourth (4);
   cout << " �������� ����������� � main" << endl;

   return 0;
 }
void Create ()
 {
	CreateAndDestroy fifth (5);
   cout << " �������� ����������� � Create" << endl;
   static CreateAndDestroy sixth (6);
   cout << " �������� �������� � Create" << endl;
   CreateAndDestroy seventh (7);
   cout << " �������� ����������� � Create" << endl;
 }
