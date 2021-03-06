#include "tasks.h"
#include "stdlib.h"

#include <sys/time.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
using namespace std;

void TaskCPU(int pid, vector<int> params) { // params: n
	uso_CPU(pid, params[0]); // Uso el CPU n milisegundos.
}

void TaskIO(int pid, vector<int> params) { // params: ms_pid, ms_io,
	uso_CPU(pid, params[0]); // Uso el CPU ms_pid milisegundos.
	uso_IO(pid, params[1]); // Uso IO ms_io milisegundos.
}

void TaskAlterno(int pid, vector<int> params) { // params: ms_pid, ms_io, ms_pid, ...
	for(int i = 0; i < (int)params.size(); i++) {
		if (i % 2 == 0) uso_CPU(pid, params[i]);
		else uso_IO(pid, params[i]);
	}
}
void TaskBatch(int pid, vector<int> params){ 
	//Los parametros son cant ciclos CPU , y cant llamadas Bloqueantes.
	//Nuevo:
	
	vector<int> lista;
	for(int i = 0; i < params[0];i++){
		lista.push_back(i);
	}
	std::random_shuffle(lista.begin(),lista.end());
	int listaArray[params[0]-1];
	for(int i=0;i<params[1];i++){
		listaArray[lista[i]] = 1;
	}
	for(int i=0;i<params[0];i++){		
		if(listaArray[i] == 1){
			uso_IO(pid,1);
		}else{
			uso_CPU(pid,1);
		}
	}
	/*
	 * TaskBatch 20 2
TaskBatch 60 9
TaskBatch 22 5

	 * 
	 * */

}
//Esta tarea genera n llamadas bloqueantes con duracion al azar(entre bmin y bmax)
void TaskConsola(int pid, vector<int> params){ //params: n,bmin,bmax
	//Obtenemos una semilla a partir de la hora
	//srand(time(NULL));

	int range =  params[2] - params[1] +1;
	int i,rnd;
	
	for(i=0;i<params[0];i++){
		rnd = (rand() % range ) + params[1];	
		uso_IO(pid, rnd); // Uso IO rnd ms
	}

	return ;
}


	

void tasks_init(void) {
	/* Todos los tipos de tareas se deben registrar acá para poder ser usadas.
	 * El segundo parámetro indica la cantidad de parámetros que recibe la tarea
	 * como un vector de enteros, o -1 para una cantidad de parámetros variable. */
	register_task(TaskCPU, 1);
	register_task(TaskIO, 2);
	register_task(TaskAlterno, -1);
	register_task(TaskConsola,3);
	register_task(TaskBatch,2);
	
}
