#ifndef __SCHED_RR2__
#define __SCHED_RR2__

#include <vector>
#include <queue>
#include "basesched.h"

class SchedRR2 : public SchedBase {
	public:
		SchedRR2(std::vector<int> argn);
        ~SchedRR2();
		virtual void load(int pid);
		virtual void unblock(int pid);
		virtual int tick(int cpu, const enum Motivo m);

	private:
		std::queue<int> *cola;
		int *contadores;
		int *quantum;
		int cores;
		typedef struct tuplaa{
			int pid;
			int cpu;
			tuplaa(int x,int y){
				pid=x;
				cpu=y;
			}
		}tupla;
		std::vector<tupla> bloqueados;
		int *CantBloq;
};
#endif
