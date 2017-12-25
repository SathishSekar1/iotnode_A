#include <iostream>
#include <stdlib.h>
#include "windows.h"

using namespace std;

class Machine
{
  class State *current;

  public:
    int value;
    Machine();
    void setCurrent(State *s)
    {
        current = s;
    }
    void returnVlaue()
    {
        cout << value;
    }
    void updateValue()
    {
        cin >> value;
    }
    void idle();
    void sensing();
    void processing();
};

class State
{
  public:
    virtual void idle(Machine *m)
    {
        cout << "   already idle\n";
    }
    virtual void sensing(Machine *m)
    {
        cout << "   already sensing\n";
    }
    virtual void processing(Machine *m)
    {
        cout << "   already processing\n";
    }
};

void Machine::idle()
{
  current->idle(this);
}

void Machine::sensing()
{
  current->sensing(this);
}

void Machine::processing()
{
  current->processing(this);
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
    void sensing(Machine *m);
};

class SENSING: public State
{
  public:
    SENSING()
    {
        //cout << '\n';
    };
    ~SENSING()
    {
        //cout << "   dtor-processing\n";
    };
    void processing(Machine *m);
};

class PROCESSING: public State
{
  public:
    PROCESSING()
    {
        cout << '\n';
    };
    ~PROCESSING()
    {
        //cout << "   dtor-idle\n";
    };
    void idle(Machine *m)
    {
        cout << "   going from processing to idle";
        m->setCurrent(new IDLE());
        delete this;
    }
};

void IDLE::sensing(Machine *m)
{
  cout << "   going from idle to sensing \n";
  cout << "   Enter Sensor Value: ";
  m->updateValue();
  m->setCurrent(new SENSING());
  delete this;
}

void SENSING::processing(Machine *m)
{
  cout << "   going from sensing to processing \n";
  cout << "   Value read from sensor: ";
  m->returnVlaue();
  m->setCurrent(new PROCESSING());
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
    Machine::idle,
    Machine::sensing,
    Machine::processing
  };
  Machine fsm;
  int msdelay = 1000;
  while (1)
  {
    (fsm.*ptrs[1])();
    (fsm.*ptrs[2])();
    Sleep(msdelay);
    (fsm.*ptrs[0])();
  }
}
