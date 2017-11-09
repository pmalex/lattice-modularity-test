#include "header.h"

bool one(int a)//true if count(a) <= 1
{
	if(a == 0 || a == 1)return true;
	if(a % 2 != 0)return false;
	int res = 0;
	while(a > 0){
		res += a%2;
		if(res > 1)return false;
		a /= 2;
	}
	return true;
}
void g_eq(int d)
{
	Hyperhope tt(MAX_HOPES/100);
	int a = (1 << d);
	//prepare
	for(int i = 3;i < a;++i){
		Hope* H = new Hope;
		H -> insert(i);
		if(!one(i))
			Eq.insert(H);
	}

	for(int i = 3;i < a/2 - 1;++i){
		if(one(i))continue;
		Hope* H = new Hope;
		H -> insert(i);
		for(int j = i + 1;j < a;++j)
			if((i & j) == 0 && !one(j))
				H -> insert(j);
		tt.insert(H);
	}
	//start generating
	clog<<tt.hm_c<<endl;
	Hyperhope hopebuf;
	Hope	  numbuf;
	Hope 	  *hp, *base;
	int	  j,s;

	base = new Hope;
	j = 0;
	for(int i = 0;i < tt.hm_c;){
		if(j == 0 && hopebuf.empty()){
			hp = tt.hm[i];
			i++;
			j = 1;
			base -> insert(hp -> m[0]);
		}
		if(j == 0 && !hopebuf.empty()){
			hp = tt.find(s);
			j = 1;
		}
		for(;j < hp -> m_c;++j){
			s = hp -> m[0] + hp -> m[j];
			if(s >= a/2 - 1){
				Hope* H = new Hope(base);
				H -> insert(hp -> m[j]);
				Eq.insert(H);
			}else{
				hopebuf.insert(hp);
				numbuf.insert(j);
				base -> insert(hp -> m[j]);
				Hope* H = new Hope(base);
				Eq.insert(H);
				j = 0;
				break;
			}
		}
		if(j == hp -> m_c && hopebuf.empty()){
			j = 0;
			base -> m_c--;
		}
		if(j == hp -> m_c && !hopebuf.empty()){
			hp = hopebuf.pop();
			j = numbuf.pop() + 1;
			base -> m_c--;
		}
	}
	delete base;
}
int get(Hope* Hp, int z)
{
	int d = 0;
	int dim = Hp -> m_c;
	for(int i = 0;i < dim;++i){
		(z%2)?(d |= (1 << (dim - Hp -> m[dim - i - 1]))):1;
		z /= 2;
	}
	return d;
}
void make_con()
{
	for(int i = 0;i < Eq.hm_c;++i){
		Hope *hp = Eq.hm[i];
		bool flag = true;
		for(int j = 0;j < hp -> m_c;++j){			//for any hope element
			for(int l = 1;l < A.hm_c;++l){			//for any letter
				int t = get(A.hm[l], hp -> m[j]);
				//hp -> out();cout<<(hp -> m[j])<<" "<<t<<" "<<l<<endl;
				if(!one(t) && !(hp -> find(t))){
					flag = false;
					break;
				}
			}
			if(!flag)break;
		}
		if(flag){
			Hope *p = new Hope(hp);
			Con.insert(p);
		}
	}
}
void make_lattice()
{
	for(int i = 0;i < Con.hm_c;++i){
		Node* np = new Node(Con.hm[i]);
		L.insert(np);
	}
	Hope* hp = new Hope;
	hp -> insert(0);
	Node* np = new Node(hp);
	np -> insert_up(hp);
	np -> insert_down(hp);
	for(int i = 0;i < L.nm_c;++i){
		np -> insert_up(L.nm[i] -> V);
		L.nm[i] -> insert_down(hp);
	}
	L.insert(np);

	for(int i = 0;i < Con.hm_c;++i){
		Node* np = L.find(Con.hm[i]);
		for(int j = 0;j < Con.hm_c;++j)
			if(Con.hm[i] -> operator<=(Con.hm[j]))
			{
				np -> insert_up(Con.hm[j]);
				L.nm[j] -> insert_down(Con.hm[i]);
			}
	}
	Con.insert(hp);
}
bool check()
{
	if(L.nm_c < 330){
		for(int i = 0;i < L.nm_c;++i)
			for(int j = 0;j < L.nm_c;++j)
				for(int k = 0;k < L.nm_c;++k)
					if(!func(i, j, k))
						return false;
		if(func == go1)
			cout<<"This lattice is modular."<<endl;
		if(func == go2)
			cout<<"This lattice is distributive."<<endl;
		return true;
	}else{
		srand(time(NULL));
		int count = 0;
		while(count < 1000000){
			count++;
			if(!func(rand()%L.nm_c, rand()%L.nm_c, rand()%L.nm_c)){
				cout<<"Answer on "<<count<<" iteration."<<endl;
				return false;
			}
		}
		if(func == go1)
			cout<<"This Lattice is probably modular, iteration count:"<<count<<endl;
		if(func == go2)
			cout<<"This Lattice is probably distributive, iteration count:"<<count<<endl;		
		return true;
	}
}
bool go1(int i, int j, int k)
{
	x = L.nm[i];
	y = L.nm[j];
	z = L.nm[k];	
	if(x -> V -> operator<=(z -> V))
		if(inf(sup(x, y), z) != sup(x, inf(y, z))){
			cout<<"Lattice is not modular:"<<endl;
			cout<<"x = ";x -> V -> out();cout<<endl;
			cout<<"y = ";y -> V -> out();cout<<endl;
			cout<<"z = ";z -> V -> out();cout<<endl<<endl;
			Node *p = sup(x, y);
			cout<<"sup {";x -> V -> out();cout<<",";y -> V -> out();cout<<"} = ";p -> V -> out();cout<<endl;
			cout<<"inf {";p -> V -> out();cout<<",";z -> V -> out();cout<<"} = ";inf(p, z) -> V -> out();cout<<" <-"<<endl;
			p = inf(y, z);
			cout<<">"<<endl;
			cout<<"inf {";y -> V -> out();cout<<",";z -> V -> out();cout<<"} = ";p -> V -> out();cout<<endl;
			cout<<"sup {";x -> V -> out();cout<<",";p -> V -> out();cout<<"} = ";sup(x, p) -> V -> out();cout<<" <-"<<endl;
			
			return false;
		}
	return true;
}
bool go2(int i, int j, int k)
{
	x = L.nm[i];
	y = L.nm[j];
	z = L.nm[k];	
	if(inf(sup(x, y), z) != sup(inf(x, z), inf(y, z))){
		cout<<"Lattice is not distributive:"<<endl;
		cout<<"x = ";x -> V -> out();cout<<endl;
		cout<<"y = ";y -> V -> out();cout<<endl;
		cout<<"z = ";z -> V -> out();cout<<endl;
		
		return false;
	}
	return true;
}
bool lattice_print(bool flag)
{
	list<Hope*> l;
	list<Hope*>::iterator it1,it2;
	ofstream ff("out.dot");
	ff<<"graph lattice {"<<endl;
	ff<<"rankdir = BT;"<<endl;
	if(Con.hm_c > 20)
		ff<<"ratio = \"0.75\";"<<endl;
	//if(Con.hm_c > 92)
	//	ff<<"rotate = 90;"<<endl;
	ff<<"node[shape = \"none\"];"<<endl;
	if(!flag){
		ff<<"\"";
		ff<<*(x -> V);
		ff<<"\"[shape = \"rectangle\"];"<<endl;

		ff<<"\"";
		ff<<*(y -> V);
		ff<<"\"[shape = \"rectangle\"];"<<endl;

		ff<<"\"";
		ff<<*(z -> V);
		ff<<"\"[shape = \"rectangle\"];"<<endl;
	}

	for(int i = 0;i < L.nm_c;++i){
		for(int j = 0;j < L.nm[i] -> up_c;++j)
			if(L.nm[i] -> up[j] != L.nm[i] -> V)
				l.push_back(L.nm[i] -> up[j]);
		
		for(it1 = l.begin();it1 != l.end();++it1)
			for(it2 = l.begin();it2 != l.end();++it2){
				if(it2 == it1)continue;
				if((*it1) -> operator<=(*it2)){
					l.remove(*it2);
					it1 = l.begin();
					break;
				}else if((*it2) -> operator<=(*it1)){
					l.remove(*it1);
					it1 = l.begin();
					break;
				}
			}

		for(it1 = l.begin();it1 != l.end();++it1){
			ff<<"\"";
			ff<<*(L.nm[i] -> V);
			ff<<"\"";
			ff<<" -- ";
			ff<<"\"";
			ff<<*(*it1);
			ff<<"\"";
			ff<<";"<<endl;
		}
		l.clear();
	}
	ff<<"}"<<endl;
	ff.close();
	system("dot -Tpdf out.dot -o lattice.pdf");
// 	system("dot -Tsvg out.dot -o lattice.svg");
}

void automaton_print()
{
	ofstream ff("out.dot");
	ff<<"digraph automaton {"<<endl;
	ff<<"rankdir = LR;"<<endl;
	ff<<"ratio = \"0.75\";"<<endl;
	for(int i = 1;i < A.hm_c;++i)
		for(int j = 0;j < A.hm[0] -> m_c;++j){
			ff<<(char)(A.hm[0] -> m[j])<<" -> ";
			ff<<(char)(A.hm[0] -> m[A.hm[i] -> m[j] - 1]);
			//ff<<"[label = "<<'t'<<(i - 1)<<"];"<<endl;
			ff<<"[label = "<<(char)('k' + i - 1)<<"];"<<endl;
		}
	ff<<"}"<<endl;
	ff.close();
	system("dot -Tsvg out.dot -o automaton.svg");
}

Node* sup(Node* np1, Node* np2)
{
	if(np1 -> up_c == 1)
		return np1;
	else if(np2 -> up_c == 1)
		return np2;

	if(np1 -> down_c == 1)
		return np2;
	else if(np2 -> down_c == 1)
		return np1;

	set<Hope*, Hope> su;
	for(int i = 0;i < np1 -> up_c;++i){
		if(np2 -> find_up(np1 -> up[i]))
			su.insert(np1 -> up[i]);
	}
	return L.find(*su.begin());
}
Node* inf(Node* np1, Node* np2)
{
	if(np1 -> down_c == 1)
		return np1;
	else if(np2 -> down_c == 1)
		return np2;

	if(np1 -> up_c == 1)
		return np2;
	else if(np2 -> up_c == 1)
		return np1;

	set<Hope*, Hope> su;
	for(int i = 0;i < np1 -> down_c;++i){
		if(np2 -> find_down(np1 -> down[i]))
			su.insert(np1 -> down[i]);
	}
	return L.find(*(--su.end()));
}
//---------------- class Hope ------------------------
ofstream& operator<<(ofstream& out, Hope& H)
{
	char t[H.m_c];
	for(int i = H.m_c - 1;i >= 0;--i){
		int p = H.m[i];
		int dim = A.hm[0] -> m_c;
		int j = 0, k = 0;
		while(p > 0){
			if(p%2)t[k++] = (A.hm[0] -> m[dim - j - 1]);
			p /= 2;
			++j;
		}
		out<<"(";
		for(int l = k - 1;l >= 0;--l)
			out<<t[l];
		out<<")";
	}
}
Hope::Hope()
{
	max = 15;
	m = new int[max];
	m_c = 0;
}
Hope::Hope(int k)
{
	max = k;
	m = new int[max];
	m_c = 0;
}
Hope::Hope(Hope* hp)
{
	max = hp -> max;
	m = new int[max];
	m_c = hp -> m_c;
	for(int i = 0;i < m_c;++i)
		m[i] = hp -> m[i];
}
Hope::~Hope()
{
	delete[] m;
}
void Hope::insert(int x)
{
	if(m_c == max){
		max *= 100;
		int* t = new int[max];
		for(int i = 0;i < m_c;++i)
			t[i] = m[i];
		delete[] m;
		m = t;
	}
	m[m_c++] = x;
}
int Hope::pop()
{
	m_c--;
	return m[m_c];
}
bool Hope::find(int z) const
{
	for(int i = 0;i < m_c;++i)
		if(m[i] == z || (m[i] | z) == m[i])
			return true;
	return false;
}
void Hope::clear()
{
	m_c = 0;
}
bool Hope::operator<=(Hope *hp) const
{
	for(int i = 0;i < m_c;++i)
		if(!(hp -> find(m[i])))
			return false;
	return true;
}
bool Hope::operator()(Hope* H1, Hope* H2) const
{
	if(H1 == H2)return false;
	return (H1 -> operator<=(H2));
}
void Hope::fout() const
{
	for(int i = 0;i < m_c;++i)
		cout<<"("<<m[i]<<")";
}
void Hope::out() const
{
	char t[m_c];
	for(int i = m_c - 1;i >= 0;--i){
		int p = m[i];
		int dim = A.hm[0] -> m_c;
		int j = 0, k = 0;
		while(p > 0){
			if(p%2)t[k++] = (A.hm[0] -> m[dim - j - 1]);
			p /= 2;
			++j;
		}
		cout<<"(";
		for(int l = k - 1;l >= 0;--l)
			cout<<t[l];
		cout<<")";
	}
}
//----------------- class Hyperhope ----------------------------

Hyperhope::Hyperhope()
{
	hm = new Hope*[MAX_HOPES];
	hm_c = 0;
}
Hyperhope::Hyperhope(int k)
{
	hm = new Hope*[k];
	hm_c = 0;
}
Hyperhope::~Hyperhope()
{
	for(int i = 0;i < hm_c;++i)
		hm[i] -> ~Hope();
	delete[] hm;
}
void Hyperhope::insert(Hope* H)
{
	hm[hm_c++] = H;
}
Hope* Hyperhope::find(int n) const
{
	for(int i = 0;i < hm_c;++i)
		if(hm[i] -> m[0] == n)
			return hm[i];
	return NULL;
}
Hope* Hyperhope::pop()
{
	hm_c--;
	return hm[hm_c];
}
bool Hyperhope::empty() const
{
	return (hm_c == 0);
}
void Hyperhope::out() const
{
	for(int i = 0;i < hm_c;++i){
		hm[i] -> out();
		cout<<";";
	}
}
//------------- class Node -----------------------------
Node::Node(Hope* hp)
{
	V = hp;
	up = new Hope*[MAX_NODES];
	up_c = 0;

	down = new Hope*[MAX_NODES];
	down_c = 0;
}
Node::~Node()
{
	delete[] up;
	delete[] down; 
}
void Node::insert_up(Hope* hp)
{
	up[up_c++] = hp;
}
void Node::insert_down(Hope* hp)
{
	down[down_c++] = hp;
}
bool Node::find_up(Hope* hp) const
{
	for(int i = 0;i < up_c;++i)
		if(up[i] == hp)
			return true;
	return false;
}
bool Node::find_down(Hope* hp) const
{
	for(int i = 0;i < down_c;++i)
		if(down[i] == hp)
			return true;
	return false;
}
void Node::out() const
{
	for(int i = 0;i < down_c;++i){
		down[i] -> out();
		cout<<"<-";
	}
	cout<<"[";
	V -> out();
	cout<<"]->";
	for(int i = 0;i < up_c;++i){
		up[i] -> out();
		if(i + 1 < up_c)cout<<"->";
	}
}
//---------------- class Lattice -----------------
Lattice::Lattice()
{
	nm = new Node*[MAX_NODES];
	nm_c = 0;
}
Lattice::~Lattice()
{
	for(int i = 0;i < nm_c;++i)
		delete nm[i];
	delete[] nm;
}
void Lattice::insert(Node* np)
{
	nm[nm_c++] = np;
}
Node* Lattice::find(Hope* hp) const
{
	for(int i = 0;i < nm_c;++i)
		if(nm[i] -> V == hp)
			return nm[i];
	cerr<<"find in lattice returning NULL"<<endl;
	return NULL;
}
void Lattice::out() const
{
	for(int i = 0;i < nm_c;++i){
		nm[i] -> out();
		cout<<endl;
	}
}

