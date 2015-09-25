#include <vector>
#include <queue>
#include "sched_rr.h"
#include "basesched.h"
#include <iostream>

using namespace std;

SchedRR::SchedRR(vector<int> argn) {
	contadores=new int[argn[0]];
	quantum= new int [argn[0]];
	int i=0;
	while(i<argn[0]){
		quantum[i]=argn[i+1];
		i++;
	}
	// Round robin recibe la cantidad de cores y sus cpu_quantum por parámetro
}

SchedRR::~SchedRR() {
	delete[] contadores;
	delete[] quantum;
}


void SchedRR::load(int pid) {
	
	cola.push(pid);
}

void SchedRR::unblock(int pid) {
	cola.push(pid);
}

int SchedRR::tick(int cpu, const enum Motivo m) {
	//cout<< cola.front() <<endl;
	if (m == EXIT || m== BLOCK) {
		// Si el pid actual terminó, sigue el próximo.
		if (cola.empty()) return IDLE_TASK;
		else {
			contadores[cpu]=0;
			int sig = cola.front(); 
			cola.pop();
			return sig;
		}
	} else if(m == TICK){
		if (current_pid(cpu) == IDLE_TASK && !cola.empty()) {
			int sig = cola.front(); cola.pop();
			contadores[cpu]=0;
			return sig;
		}
		contadores[cpu]=contadores[cpu]+1;
		if (contadores[cpu]== quantum[cpu]) {
			if(!cola.empty()){
				int sig = cola.front(); 
				cola.pop();
				cola.push(current_pid(cpu));
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
	else
		return 0;
}
