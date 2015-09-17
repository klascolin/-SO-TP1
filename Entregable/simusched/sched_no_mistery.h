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
    std::vector<int> quantum;   //Tiene todos los quantum que nos pasan por parametro
    std::vector<int> lista;     //Va a tener todas las tareas que estan corriendo y no estan bloqueadas
    std::queue<int> colaBloq;   //Va a tener a las tareas que se fueron desbloqueando
    int actual;                 //Es la posicion en la lista de la tarea que se esta corriendo en el momento
    std::vector<tupla> tareas; //Tiene el pid y el quantum actual
    std::vector<tupla> contador;    //Tiene el pid y un contador de cuantas veces se corrio
	std::queue<int> nuevos;
};

#endif
