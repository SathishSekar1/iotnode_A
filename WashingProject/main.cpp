#include <iostream>
#include <stdlib.h>
#include "windows.h"

using namespace std;

class Machine
{
  class State *current;

  public:
    int value, currentmode, rotarspeed;
    float tempraturepv;
    string modetype[8] = {"None", "Cotton 40 degC", "Cotton 60 degC", "Quick Wash", "Delicate", "Rinse", "Spin", "Drain"};
    string currentcycle;
    int rpmarray [8] = {0,1500,1400,1500,800,1000,3000,0};
    int temparray [8] = {25,40,60,35,35,35,25,25};
    bool doorlockstatus, detergentloadedstatus, fabricconditionerstatus, clothloadstatus, start_stop, waterinletValve, detergentflushvalve,drainValve,fabricconditionflushvalve,buzzer;
    Machine();
    void setCurrent(State *s)
    {
        current = s;
    }
    void loadCloth(){
        clothloadstatus = true;
    }
    void loaddetergentTray(){
        detergentloadedstatus = true;
    }
    void loadfabricTray(){
        fabricconditionerstatus = true;
    }
    void selectMode(int x){
        currentmode = x;
    }
    void buttonStart(){
        start_stop = true;
    }
    void fillWater(bool a){
        waterinletValve = a;
    }
    void drumSpeed(int b){
        rotarspeed = b;
    }
    void drainDrum(bool c){
        drainValve = c;
    }
    void flushdetergentTray(bool d){
        detergentflushvalve = d;
    }
    void flushfabricTray(bool e){
        fabricconditionflushvalve = e;
    }
    void beep(bool f){
        buzzer = f;
    }
    void doorLock(){
        doorlockstatus = true;
    }
    void doorOpen(){
        doorlockstatus = false;
    }
    void temperaturesetpoint(float g){
        tempraturepv = g;
    }
    void currentstareupdate(string h){
        currentcycle = h;
    }
    //void updateScreen();
    //void unloadCloth();
    void clearvalues()
    {
        doorlockstatus = false;
        detergentloadedstatus = false;
        fabricconditionerstatus = false;
        clothloadstatus = false;
        currentmode = 0;
        start_stop = false;
        waterinletValve = false;
        rotarspeed = 0;
        drainValve = false;
        detergentflushvalve = false;
        fabricconditionflushvalve = false;
        buzzer = false;
        tempraturepv = 25;
        value = 0;
    }
    void messageIdle()
    {
        system ("CLS");
        cout << "Current Washing Machine status: \n";
        cout << "Current Mode: " << modetype[currentmode] <<"\n";
        cout << "Detergent tray load status: " << boolalpha << detergentloadedstatus <<"\n";
        cout << "Fabric conditioner load status: " << fabricconditionerstatus << "\n";
        cout << "Loading door locked :" << doorlockstatus << "\n";
        if (currentmode > 0)
            {
                cout << "Enter any value in following 1: Load detergent tray, 2: Load Fabric conditioner, 3: load cloths, 4: select mode, 5: Start Sequence: ";
            }
        else{
            cout << "Enter any value in following 1: Load detergent tray, 2: Load Fabric conditioner, 3: load cloths, 4: select mode: ";
        }
    }
    void messageRunning(){
        system ("CLS");
        cout << "Loading door locked :" << boolalpha << doorlockstatus << "\n";
        cout << "Current Mode: " << modetype[currentmode] <<"\n";
        cout << "Current Cycle: " << currentcycle << "\n";
        cout << "Detergent tray flushing: " << boolalpha << detergentflushvalve << detergentloadedstatus <<"\n";
        cout << "Fabric conditioner flushing: " << boolalpha << fabricconditionflushvalve << "\n";
        cout << "Fabric conditioner flushing: " << boolalpha << fabricconditionflushvalve << "\n";
        cout << "Water Inlet valve Open: " << boolalpha << waterinletValve << "\n";
        cout << "Drain Outlet valve Open: " << boolalpha << drainValve << "\n";
        cout << "Drum speed RPM: " << rotarspeed << "\n";
        cout << "Temperature: " << tempraturepv << "\n";
        cout << "Buzzer On Status: " << buzzer << "\n";
    }
    void idle();
    int getvalueIdeal(){
        cin >> value;
        return value;
    }
    void running();
};

class State
{
  public:
    virtual void idle(Machine *m)
    {
        cout << "   already idle\n";
    }
    virtual void running(Machine *m)
    {
        cout << "   already running\n";
    }
};

void Machine::idle()
{
  current->idle(this);
}

void Machine::running()
{
  current->running(this);
}

class IDLE: public State
{
  public:
    IDLE()
    {
        cout << '\n' ;
    };
    ~IDLE()
    {
        //cout << "  sensing\n";
    };
    void running(Machine *m);
};

class RUNNING: public State
{
  public:
    RUNNING()
    {
        //cout << '\n';
    };
    ~RUNNING()
    {
        //cout << "   dtor-processing\n";
    };
    void idle(Machine *m);
};

void IDLE::running(Machine *m)
{
  int x,y;
  m-> clearvalues();
  m->messageIdle();
  getnextvalue:
  x = m->getvalueIdeal();
  switch(x){
  case 1 :
    m->loaddetergentTray();
    m->messageIdle();
    Sleep(1000);
    goto getnextvalue;
    break;
  case 2:
    m->loadfabricTray();
    m->messageIdle();
    Sleep(1000);
    goto getnextvalue;
    break;
  case 3:
    m->loadCloth();
    m->messageIdle();
    Sleep(1000);
    goto getnextvalue;
    break;
  case 4:
    cout << "Enter you mode option 1:None 2:Cotton 40 degC 3:Cotton 60 degC 4:Quick Wash 5:Delicate 6:Rinse 7:Spin 8:Drain :";
    m->selectMode(m->getvalueIdeal()-1);
    m->messageIdle();
    Sleep(1000);
    goto getnextvalue;
    break;
  case 5:
    m->buttonStart();
    Sleep(1000);
    break;
  }
  Sleep(1000);
  system ("CLS");
  cout << "   going from idle to running \n";
  Sleep(1000);
  m->setCurrent(new RUNNING());
  delete this;
}

void RUNNING::idle(Machine *m)
{
  system ("CLS");
  m->doorLock();
  m->messageRunning();
  Sleep(1000);
  int x;
  x = m->currentmode;
  switch(x){
  case 1 :
    m->drumSpeed(m->rpmarray[x]);
    m->temperaturesetpoint(m->temparray [x]);
    m->currentstareupdate("Soaking");
    m->messageRunning();
    Sleep(1000);
    m->currentstareupdate("Washing");
    m->messageRunning();
    Sleep(1000);
    m->currentstareupdate("Rinsing");
    m->messageRunning();
    Sleep(1000);
    m->currentstareupdate("Spin");
    m->messageRunning();
    Sleep(1000);
    m->currentstareupdate("Drain");
    m->messageRunning();
    Sleep(1000);
    break;
  case 2:
    m->drumSpeed(m->rpmarray[x]);
    m->temperaturesetpoint(m->temparray [x]);
    m->currentstareupdate("Soaking");
    m->messageRunning();
    Sleep(1000);
    m->currentstareupdate("Washing");
    m->messageRunning();
    Sleep(1000);
    m->currentstareupdate("Rinsing");
    m->messageRunning();
    Sleep(1000);
    m->currentstareupdate("Spin");
    m->messageRunning();
    Sleep(1000);
    m->currentstareupdate("Drain");
    m->messageRunning();
    Sleep(1000);
    break;
  case 3:
    m->drumSpeed(m->rpmarray[x]);
    m->temperaturesetpoint(m->temparray [x]);
    m->currentstareupdate("Soaking");
    m->messageRunning();
    Sleep(1000);
    m->currentstareupdate("Washing");
    m->messageRunning();
    Sleep(1000);
    m->currentstareupdate("Rinsing");
    m->messageRunning();
    Sleep(1000);
    m->currentstareupdate("Spin");
    m->messageRunning();
    Sleep(1000);
    m->currentstareupdate("Drain");
    m->messageRunning();
    Sleep(1000);
    break;
  case 4:
    m->drumSpeed(m->rpmarray[x]);
    m->temperaturesetpoint(m->temparray [x]);
    m->currentstareupdate("Soaking");
    m->messageRunning();
    Sleep(1000);
    m->currentstareupdate("Washing");
    m->messageRunning();
    Sleep(1000);
    m->currentstareupdate("Rinsing");
    m->messageRunning();
    Sleep(1000);
    m->currentstareupdate("Spin");
    m->messageRunning();
    Sleep(1000);
    m->currentstareupdate("Drain");
    m->messageRunning();
    Sleep(1000);
    break;
  case 5:
    m->drumSpeed(m->rpmarray[x]);
    m->temperaturesetpoint(m->temparray [x]);
    m->currentstareupdate("Rinsing");
    m->messageRunning();
    Sleep(1000);
    m->currentstareupdate("Spin");
    m->messageRunning();
    Sleep(1000);
    m->currentstareupdate("Drain");
    m->messageRunning();
    Sleep(1000);
    break;
  case 6:
    m->drumSpeed(m->rpmarray[x]);
    m->temperaturesetpoint(m->temparray [x]);
    m->currentstareupdate("Spin");
    m->messageRunning();
    Sleep(1000);
    m->currentstareupdate("Drain");
    m->messageRunning();
    Sleep(1000);
    break;
  case 7:
    m->drumSpeed(m->rpmarray[x]);
    m->temperaturesetpoint(m->temparray [x]);
    m->currentstareupdate("Drain");
    m->messageRunning();
    Sleep(1000);
    break;
  }

  cout << "   going from running to idle \n";
  m-> clearvalues();
  Sleep(1000);
  m->setCurrent(new IDLE());
  delete this;
}

Machine::Machine()
{
  current = new IDLE();
  cout << '\n';
}

int main()
{
  void(Machine:: *ptrs[])() =
  {
    Machine::running,
    Machine::idle
  };
  Machine fsm;
  int msdelay = 1000;
  while(1){
    (fsm.*ptrs[0])();
    (fsm.*ptrs[1])();
  }

}
