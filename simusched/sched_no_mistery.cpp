#include <vector>
#include <queue>
#include "sched_no_mistery.h"
#include "basesched.h"
#include <iostream>
using namespace std;

SchedNoMistery::SchedNoMistery(vector<int> argn) {
	quantum.resize(argn.size()-1);
	int i=0;
	quantum[0]=1;
	while(i<argn.size()){
		quantum[i]=argn[i+1];
		i++;
	}
}

void SchedNoMistery::load(int pid) {
    cola.push(pid);
    tupla *t= new tupla(pid,0);
    tareas.insert(tareas.begin()+pid,*t);
    tupla *n= new tupla(pid,0);
    contador.insert(contador.begin()+pid,*n);

}

void SchedNoMistery::unblock(int pid) {

	cola.push(pid);
}

int SchedNoMistery::tick(int cpu, const enum Motivo m) {
    if (m == EXIT || m== BLOCK) {
		// Si el pid actual terminó, sigue el próximo.
		if (cola.empty()) return IDLE_TASK;
		else {
			int sig = cola.front();
			cola.pop();
			tareas[sig].momento=0;
			return sig;
		}
	} else if(m == TICK){
		//Si no hay ninguna corriendo pero hay en la cola corro la primera
		if (current_pid(cpu) == IDLE_TASK && !cola.empty()) {
			int sig = cola.front();
			cola.pop();
			tareas[sig].momento=0;
			return sig;
		}
		//Aumento el quantum actual
		tareas[current_pid(cpu)].momento=tareas[current_pid(cpu)].momento+1;
		//
		int j=contador[current_pid(cpu)].momento;
		if (tareas[current_pid(cpu)].momento==quantum[j]) {
			if(j<quantum.size()-1){
            contador[current_pid(cpu)].momento=contador[current_pid(cpu)].momento+1;
			}
			if(!cola.empty()){
				int sig = cola.front();
				cola.pop();
				cola.push(current_pid(cpu));
				tareas[sig].momento=0;
				return sig;
			}
			else{
				tareas[current_pid(cpu)].momento=0;
				return current_pid(cpu);
			}
		}
		else {
			return current_pid(cpu);
		}
	}
	else
		return 0;
}
