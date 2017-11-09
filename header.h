#include <cstdlib>
#include <iostream>
#include <fstream>
#include <set>
#include <list>
using namespace std;

struct Hope;
struct Hyperhope;
struct Node;

const int 	MAX_HOPES = 1000000;
const int 	MAX_NODES = 400000;

Node *x,*y,*z;

bool 	one(int);			//true if count(a) <= 1
void 	g_eq(int);			//generate equivalence
int	get(Hope*, int);		//for correct out state's name
void	make_con();
void	make_lattice();
bool	check();
bool	go1(int, int, int);		//for check modular (retrying parts)
bool	go2(int, int, int);		//for check distributive (retrying parts)
bool	lattice_print(bool);		//out to file
void	automaton_print();

Node*	sup(Node*, Node*);
Node*	inf(Node*, Node*);

bool 	(*func)(int, int, int);

struct Hope
{
	int* 		m;
	int 		m_c;
	int 		max;

	friend ofstream& operator<<(ofstream&, Hope&);
	Hope();
	Hope(int);
	Hope(Hope*);
	~Hope();
	void insert(int);
	int pop();
	bool find(int) const;
	void clear();
	bool operator<=(Hope*) const;
	bool operator()(Hope*, Hope*) const;

	void fout() const;
	void out() const;
};
struct Hyperhope
{
	Hope**		hm;
	int 		hm_c;

	Hyperhope();
	Hyperhope(int);
	~Hyperhope();
	void insert(Hope*);
	Hope* find(int) const;
	Hope* pop();
	bool empty() const;

	void out() const;
} Eq, A(40), Con(MAX_HOPES/100);

struct Node
{
	Hope**		up;
	int		up_c;
	Hope*		V;
	Hope**		down;
	int		down_c;

	Node(Hope*);
	~Node();
	void insert_up(Hope*);
	void insert_down(Hope*);
	bool find_up(Hope*) const;
	bool find_down(Hope*) const;

	void out() const;
};
struct Lattice
{
	Node**		nm;
	int		nm_c;

	Lattice();
	~Lattice();
	void insert(Node*);
	Node* find(Hope*) const;

	void out() const;
} L;





