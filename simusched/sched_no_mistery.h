#ifndef __SCHED_NOMIS__
#define __SCHED_NOMIS__

#include <vector>
#include <queue>
#include "basesched.h"

class SchedNoMistery : public SchedBase {
  public:
    SchedNoMistery(std::vector<int> argn);
    virtual void load(int pid);
    virtual void unblock(int pid);
    virtual int tick(int cpu, const enum Motivo m);
  private:
    typedef struct tuplaa{
        int pid;
        int momento;
        tuplaa(int x,int y){
            pid=x;
            momento=y;
        }
    }tupla;
    std::vector<int> quantum;
    std::queue<int> cola;
    std::vector<tupla> tareas; //tiene el pid y el quantum actual
    std::vector<tupla> contador;    //tiene el pid y un contador de cuantas veces se corrio
};

#endif
