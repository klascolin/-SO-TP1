#include <vector>
#include <queue>
#include "sched_no_mistery.h"
#include "basesched.h"
#include <iostream>
using namespace std;

SchedNoMistery::SchedNoMistery(vector<int> argn) {
	
	actual=-1;  //Al principio no hay ninguna corriendo
	quantum.resize(argn.size());
	quantum[0]=1;      //Siempre el primer quantum es de 1
	unsigned int i=1;
	while(i<argn.size()){
		quantum[i]=argn[i]; //Inicializo el resto
		i++;
	}
}

void SchedNoMistery::load(int pid) {
    lista.push_back(pid);   //Lo agrego al final de la lista
    nuevos.push(pid);
    tupla *t= new tupla(pid,0);
    tareas.insert(tareas.begin()+pid,*t);   //Al principio la tarea tiene quantum 0
    tupla *n= new tupla(pid,0);
    contador.insert(contador.begin()+pid,*n);   //Al principio se corrio 0 veces
}

void SchedNoMistery::unblock(int pid) {
	colaBloq.push(pid);
	lista.push_back(pid);
	actual=actual%lista.size();
}

int SchedNoMistery::tick(int cpu, const enum Motivo m) {
	if (m == EXIT ){
		int j=0;
		while(j<lista.size()){
			j++;
		}
		int i=0;
		while(i<lista.size()){
			if(current_pid(cpu)==lista[i]){
				break;
			}
			i++;
		}
		
		lista.erase(lista.begin()+i);
		
		if(lista.size() != 0){
			actual=actual%lista.size();
		}	
		// Si el pid actual terminó, sigue el próximo.
		if(!nuevos.empty()){
            int sig = nuevos.front();
			nuevos.pop();
			tareas[sig].momento=0;
			return sig;
		}
		else if(!colaBloq.empty()){
            int sig = colaBloq.front();
			colaBloq.pop();
			contador[sig].momento --;
			if(contador[sig].momento > 0){
				contador[sig].momento --;
			}
			unsigned int j=contador[sig].momento;
			tareas[sig].momento=quantum[j]-1;
			return sig;
		}
		else {
			if(lista.empty()){
				return IDLE_TASK;
			}
			else{
				int sig=lista[actual];
			//	cerr<<lista.size()<<endl;
				tareas[sig].momento=0;
				return sig;
			}
		}
	}
	else if(m == TICK){
		//Si no hay ninguna corriendo pero hay en la cola corro la primera
        if (nuevos.empty()&& colaBloq.empty() && lista.empty()) return IDLE_TASK;
        else if (current_pid(cpu) == IDLE_TASK && !nuevos.empty()){
            int sig = nuevos.front();
            nuevos.pop();
            tareas[sig].momento=0;
            return sig;
		}
        else if (current_pid(cpu) == IDLE_TASK && !colaBloq.empty()){
            int sig = colaBloq.front();
            colaBloq.pop();
            contador[sig].momento --;
            if(contador[sig].momento > 0){
				contador[sig].momento --;
			}
			unsigned int j=contador[sig].momento;
			tareas[sig].momento=quantum[j]-1;
            return sig;
		}
		else if(current_pid(cpu) == IDLE_TASK && !lista.empty()){
            actual=(actual+1)%lista.size();
			int sig=lista[actual];
			tareas[sig].momento=0;
			return sig;
		}
		//Aumento el quantum actual
		tareas[current_pid(cpu)].momento=tareas[current_pid(cpu)].momento+1;
		unsigned int j=contador[current_pid(cpu)].momento;
		if (tareas[current_pid(cpu)].momento==quantum[j]) {
			if(j<quantum.size()-1){
            contador[current_pid(cpu)].momento=contador[current_pid(cpu)].momento+1;
			}
			if(!nuevos.empty()){
				int sig = nuevos.front();
				nuevos.pop();
				tareas[sig].momento=0;
				return sig;
			}
			if(!colaBloq.empty()){
				int sig = colaBloq.front();
				colaBloq.pop();
				contador[sig].momento --;
				if(contador[sig].momento > 0){
				
				contador[sig].momento --;
				}
				unsigned int j=contador[sig].momento;
				tareas[sig].momento=quantum[j]-1;
			
				return sig;
			}
			else if(!lista.empty()){
                actual=(actual+1)%lista.size();
                int sig=lista[actual];
                tareas[sig].momento=0;
                return sig;
            }
			else{
				tareas[current_pid(cpu)].momento=0;
				return current_pid(cpu);
			}
		}
		else{
			return current_pid(cpu);
		}
	}
    else if(m== BLOCK){
		unsigned int j=contador[current_pid(cpu)].momento;
		if(j<quantum.size()-1){
            contador[current_pid(cpu)].momento=contador[current_pid(cpu)].momento+1;
		}
        lista.erase(lista.begin()+actual);
        if(lista.size() != 0){
			actual=actual%lista.size();
		}
        if(!nuevos.empty()){
				int sig = nuevos.front();
				nuevos.pop();
				tareas[sig].momento=0;
				return sig;	
		}
        else if(!colaBloq.empty()){
				int sig = colaBloq.front();
				colaBloq.pop();
				tareas[sig].momento=0;
				return sig;
			}
        else if(!lista.empty()){
            
            int sig=lista[actual];
            tareas[sig].momento=0;
            return sig;
        }
    }
    else{
        return current_pid(cpu);
    }
    return IDLE_TASK;
}


