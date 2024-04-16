OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11

#
G++ = g++

#
program.exe: program.o Cluster.o AreaProcesosPendientes.o Procesador.o Proceso.o
	$(G++) -o program.exe program.o Cluster.o AreaProcesosPendientes.o Procesador.o Proceso.o

#
program.o: program.cc Cluster.hh AreaProcesosPendientes.hh Procesador.hh Proceso.hh
	$(G++) -c program.cc $(OPCIONS)
 
#
Cluster.o: Cluster.cc Cluster.hh Procesador.hh Proceso.hh 
	$(G++) -c Cluster.cc $(OPCIONS) 

#
Procesador.o: Procesador.cc Procesador.hh Proceso.hh
	$(G++) -c Procesador.cc $(OPCIONS)

#
Proceso.o: Proceso.cc Proceso.hh 
	$(G++) -c Proceso.cc $(OPCIONS)	

#
AreaProcesosPendientes.o: AreaProcesosPendientes.cc AreaProcesosPendientes.hh Proceso.hh Cluster.hh
	$(G++) -c AreaProcesosPendientes.cc $(OPCIONS)	

#
tar: program.cc AreaProcesosPendientes.cc AreaProcesosPendientes.hh Proceso.cc Proceso.hh Cluster.cc Cluster.hh Procesador.cc Procesador.hh html.zip
	tar -cvf practica.tar program.cc AreaProcesosPendientes.cc AreaProcesosPendientes.hh Proceso.cc Proceso.hh Cluster.cc Cluster.hh Procesador.cc Procesador.hh Makefile html.zip

#
clean:
	rm -f *.o
	rm -f *.exe
