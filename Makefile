all:
	c++ -o lattice-modularity-test -O2 main.cpp

clean: 
	if test -f lattice-modularity-test; then rm lattice-modularity-test; fi
	if test -f lattice.pdf; then rm lattice.pdf; fi
	if test -f out.dot; then rm out.dot; fi
