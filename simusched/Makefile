export LC_ALL=C
CXXFLAGS= -Wall -pedantic -g -ggdb
LDFLAGS= -lpthread

OBJS=main.o simu.o basesched.o basetask.o tasks.o sched_rr.o sched_fcfs.o sched_rr2.o sched_no_mistery.o
MAIN=simusched


.PHONY: all clean new
all: $(MAIN)

ejercicio1:
	mkdir ejercicio1
	./simusched taskConsola.tsk 1 1 1 SchedFCFS | ./graphsched.py  > ./ejercicio1/ej1.png	

ejercicio2:
	mkdir ejercicio2
	./simusched taskRolando.tsk 1 4 1 SchedFCFS  | ./graphsched.py > ./ejercicio2/Rolando1Core.png
	./simusched taskRolando.tsk 2 4 1 SchedFCFS  | ./graphsched.py > ./ejercicio2/Rolando2Core.png

ejercicio5:
	mkdir ejercicio5
	./simusched taskEj5.tsk 1 4 1 SchedRR  2  | ./graphsched.py > ./ejercicio5/quantum2.png
	./simusched taskEj5.tsk 1 4 1 SchedRR 10 | ./graphsched.py > ./ejercicio5/quantum10.png
	./simusched taskEj5.tsk 1 4 1 SchedRR 50| ./graphsched.py > ./ejercicio5/quantum50.png

$(MAIN): $(OBJS) sched_mistery.o 
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp %.h basesched.h
basesched.o: basesched.cpp basesched.h
basetask.o: basetask.cpp basetask.h
main.o: main.cpp simu.h basetask.h basesched.h tasks.h sched_fcfs.h \
 sched_rr.h sched_rr2.h
simu.o: simu.cpp simu.h basetask.h basesched.h
simusched.o: simusched.cpp basetask.h basesched.h tasks.h
tasks.o: tasks.cpp tasks.h basetask.h

clean:
	rm -f $(OBJS) $(MAIN)

new: clean all

