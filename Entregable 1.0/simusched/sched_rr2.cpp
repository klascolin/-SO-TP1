#include <vector>
#include <queue>
#include "sched_rr2.h"
#include "basesched.h"
#include <iostream>

using namespace std;

SchedRR2::SchedRR2(vector<int> argn) {
	// Round robin recibe la cantidad de cores y sus cpu_quantum por parámetro
	cola = new std::queue<int>[argn[0]]; 
	contadores=new int[argn[0]];
	quantum= new int [argn[0]];
	CantBloq= new int [argn[0]];
	cores=argn[0];
	int i=0;
	while(i<argn[0]){
		quantum[i]=argn[i+1];
		CantBloq[i]=0;
		i++;
	}
}

SchedRR2::~SchedRR2() {
	delete[] contadores;
	delete[] quantum;
	delete[] CantBloq;
	delete[] cola;
}


void SchedRR2::load(int pid) {
	int i =1; 
	int run=  (current_pid(0)==IDLE_TASK ? 0:1);
	unsigned int min=cola[0].size()+run+CantBloq[0];
	int pos=0;  
	while(i<cores){
		int run= (current_pid(i)==IDLE_TASK ? 0:1);
		if ((cola[i].size()+run+CantBloq[i])<min){
			min= cola[i].size();
			pos=i;
		}
		i++;
	}
	cola[pos].push(pid);
}

void SchedRR2::unblock(int pid) {
	unsigned int i=0;
	int core;
	while(i<bloqueados.size()){
		if(bloqueados[i].pid == pid){
			core=bloqueados[i].cpu;
			bloqueados.erase(bloqueados.begin()+i);
			break;
		}
		i++;
	}
	cola[core].push(pid);
	CantBloq[core]--;
}


int SchedRR2::tick(int cpu, const enum Motivo m) {
	if (m == EXIT) {
		// Si el pid actual terminó, sigue el próximo.
		if (cola[cpu].empty()) return IDLE_TASK;
		else {
			contadores[cpu]=0;
			int sig = cola[cpu].front(); 
			cola[cpu].pop();
			return sig;
		}
	} else if(m == TICK){
		if (current_pid(cpu) == IDLE_TASK && !cola[cpu].empty()) {
			int sig = cola[cpu].front(); 
			cola[cpu].pop();
			contadores[cpu]=0;
			return sig;
		}
		contadores[cpu]=contadores[cpu]+1;
		if (contadores[cpu]== quantum[cpu]) {
			if(!cola[cpu].empty()){
				int sig = cola[cpu].front(); 
				cola[cpu].pop();
				cola[cpu].push(current_pid(cpu));
				contadores[cpu]=0;
				return sig;
			}
			else{
				contadores[cpu]=0;
				return current_pid(cpu);
			}
		} else {
			return current_pid(cpu);
		}
	}
	else if(m == BLOCK){
		CantBloq[cpu]=CantBloq[cpu]+1;
		tupla *t= new tupla(current_pid(cpu),cpu);
		bloqueados.push_back(*t);
		if (cola[cpu].empty()) return IDLE_TASK;
			else {
				contadores[cpu]=0;
				int sig = cola[cpu].front(); 
				cola[cpu].pop();
				return sig;
			}
	}
	else
		return 0;
}
