#include <vector>
#include <queue>
#include "sched_no_mistery.h"
#include "basesched.h"
#include <iostream>
using namespace std;

SchedNoMistery::SchedNoMistery(vector<int> argn) {

	//Resizeamos el tamaño de cada vector()
	quantum.resize(argn.size());
	colas.resize(argn.size());
	colaXtarea.resize(argn.size());

	
	//Inicializamos el vector de quantum:
	quantum[0]=1;      //Siempre el primer quantum es de 1
	unsigned int i=1;
	while(i<argn.size()){
		quantum[i]=argn[i]; //Inicializo el resto
		i++;
	}

}

void SchedNoMistery::load(int pid) {
   
   
    colaXtarea.push_back(0);   //Al principio esta en la cola 0
    colas[0].push(pid);			//Siempre que llega una tarea, va a la cola de maxima prioridad(q = 1)
}

void SchedNoMistery::unblock(int pid) {
		if(colaXtarea[pid] > 0)
			colaXtarea[pid]--;
		else
			colaXtarea[pid] = 0;

		colas[colaXtarea[pid]].push(pid);
		
}

 	int SchedNoMistery::tick(int cpu, const enum Motivo m) {
	//cout<< cola.front() <<endl;
	if (m == EXIT || m== BLOCK) {
		// Si el pid actual terminó, sigue el próximo.
		for(int i = 0;i<colas.size();i++){	
			if (!colas[i].empty()){
				int sig = colas[i].front(); 
				colas[i].pop();
				corrio=0;
				return sig;
			}
		}
		
		//Devolvemos la idle si todas vacias

		return IDLE_TASK;	
	} 
	else if(m == TICK){
		if(current_pid(cpu) == IDLE_TASK){
			for(int i = 0;i<colas.size();i++){	
				if(!colas[i].empty()){
					int sig = colas[i].front(); 
					colas[i].pop();
					corrio=0;
					return sig;
				}			
			}
			return IDLE_TASK;
		}
		//Recorremos todas las colas en orden	
		corrio++;
		if (corrio == quantum[colaXtarea[current_pid(cpu)]]) {	
				if(colaXtarea[current_pid(cpu)] == colas.size()-1)
					colas[colaXtarea[current_pid(cpu)]].push(current_pid(cpu));
				else{
					colas[colaXtarea[current_pid(cpu)]+1].push(current_pid(cpu));
					colaXtarea[current_pid(cpu)]=colaXtarea[current_pid(cpu)]+1;
				}
				
				for(int j = 0; j<colas.size();j++){
					if(!colas[j].empty()){
						int sig = colas[j].front();
						colas[j].pop();
						corrio=0;
						return sig;
					}
				}
				
		}	
		else{
			return current_pid(cpu);
	
		}
		
	}
	
	return IDLE_TASK;
}
