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
	contador.resize(argn.size());
	last = -1;
	
	//Inicializamos el vector de quantum:
	quantum[0]=1;      //Siempre el primer quantum es de 1
	unsigned int i=1;
	while(i<argn.size()){
		quantum[i]=argn[i]; //Inicializo el resto
		i++;
	}

}

void SchedNoMistery::load(int pid) {
   
   
    contador.insert(contador.begin()+pid,0);   //Al principio se corrio 0 veces
    colas[0].push(pid);						//Siempre que llega una tarea, va a la cola de maxima prioridad(q = 1)
}

void SchedNoMistery::unblock(int pid) {
	colaBloq.push(pid);
	
	//~ int i=0;
	//~ cout<<"lista des ";
	//~ while(i<lista.size()){
	//~ cout<<lista[i]<<" ";
	//~ i++;
	//~ }
	//~ cout<<""<<endl;
	//actual=actual%lista.size();
}

 	int SchedNoMistery::tick(int cpu, const enum Motivo m) {
	//cout<< cola.front() <<endl;
	if (m == EXIT || m== BLOCK) {
		// Si el pid actual terminó, sigue el próximo.
		for(int i = 0;i<colas.size();i++){	
			if (!colas[i].empty()){
				contador[cpu]=0;
				int sig = colas[i].front(); 
				colas[i].pop();
				return sig;
			}
		}
		
		//Devolvemos la idle si todas vacias

		return IDLE_TASK;	
	} 
	else if(m == TICK){

		//Recorremos todas las colas en orden	
		for(int i = 0;i<colas.size();i++){	
			if(colas[i].empty() && !last == current_pid(cpu))
				continue;

			contador[i]=contador[i]+1;
			if (contador[i] == quantum[i]) {	
					cout<< "asd";
					if(current_pid(cpu) != IDLE_TASK){
						if(i == colas.size()-1)
							colas[i].push(current_pid(cpu));
						else
							colas[i+1].push(current_pid(cpu));
					}
					if(!colas[i].size() >= 1){
						int sig = colas[i].front(); 
						last = sig;
						colas[i].pop();
						contador[i]=0;
						return sig;
					}	
					else{
						contador[i]=0;
						return colas[i+1].front();
					}		
					
			}
				/*else{		
						contador[i]=0;
						return current_pid(cpu);
					}*/
				
			else
				return current_pid(cpu);
		}
		return 0;
	}
}
