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

    
    int corrio; //El tiempo que lleva corriendo la tarea actual

    std::vector<std::queue<int> > colas;  //colas de prioridad
    
    std::vector<int> quantum;   //Tiene todos los quantum que nos pasan por parametro
    
  
    std::vector<int> colaXtarea; //En que cola esta cada tarea

	
};

#endif
