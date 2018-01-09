#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

// Base class
class Sensor {
   public:
      float sensorValue(float pv) {
          shiftRight();
          cout << "Deleted Value: " << processvalue[0] << endl;
          processvalue[0] = pv;
          return (processvalue[0]);
      }
   protected:
      int arraysize = 10;
      float* processvalue = new float[arraysize-1];

      void shiftRight(){
          int temp = processvalue[arraysize-1];
            for (int i=arraysize-1; i>0; i--)
                {
                processvalue[i] = processvalue[i-1] ;
                }
            processvalue[0] = temp;
          }
};

// Derived class
class Temprature: public Sensor {
   public:
      float sensorCV() {
          float temppv;
          srand (time(NULL));
          temppv = rand() % 20 + 21;
          return (temppv);
      }
};

// Derived class
class Humidity: public Sensor {
   public:
      float sensorCV() {
          float humidpv;
          srand (time(NULL));
          humidpv = rand() % 10 + 1;
          return (humidpv);
      }
};

class Node {
   public:
       Temprature temp1; // We can create type of sensor during runtime for example i created static objects.
       Humidity humid1; // We can create type of sensor during runtime for example i created static objects.

       void poolValue(int i){
           if (i == 1){temp1.sensorValue(temp1.sensorCV());}
           else if (i == 2){humid1.sensorValue(humid1.sensorCV());}
       }

       float readValue(int i){
           if (i == 3){return(temp1.sensorValue(temp1.sensorCV()));}
           else if (i == 4){return(humid1.sensorValue(humid1.sensorCV()));}
       }

};


int main(void) {
   Node home1; // We can create type of node during runtime for example i created static objects. (And number of sensor)
   int i;
   float j;
   while(1){
        cout << "Enter you option 1 Pool temp, 2 Read temp value, 3 Pool humid, 4 Read humid value: ";
        cin >> i;
        if (i == 1){home1.poolValue(i);}
        else if (i == 2){home1.poolValue(i);}
        else if (i == 3){cout << "Current Temperature Value: " << home1.readValue(i) << endl;}
        else if (i == 4){cout << "Current Humidity Value: " << home1.readValue(i) << endl;}
   }

   // Print the area of the object.
   //cout << "Total area: " << Rect.getArea() << endl;

   return 0;
}
