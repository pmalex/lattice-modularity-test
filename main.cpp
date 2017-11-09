#include "header.cpp"

int main(int argc, char **argv)
{
	ifstream f(argv[1], ios::in);
	if(!f){
		cerr<<"No filename"<<endl;
		return 1;
	}
	int lc, sc, buf;
	char ch;
	f>>lc>>sc;
	Hope *hp = new Hope(sc);
	for(int i = 0;i < sc;++i){
		f>>ch;
		hp -> insert(ch);
	}
	A.insert(hp);
	for(int i = 0;i < lc;++i){
		hp = new Hope(sc);
		for(int j = 0;j < sc;++j){
			f>>ch;
			for(int k = 0;k < sc;++k)
				if(ch == (A.hm[0] -> m[k])){
					hp -> insert(k + 1);
					break;
				}
		}
		A.insert(hp);
	}
	g_eq(sc);
	cout<<"Equivalence created... ";
	cout<<(Eq.hm_c + 1)<<endl;

	//Eq.out();cout<<endl;

	make_con();
	cout<<"Congruence ready... ";
	cout<<(Con.hm_c + 1)<<endl;

	make_lattice();
	clog<<"Lattice created..."<<endl;

	if(argc >= 3 && argv[2][0] == 'd'){
		cout<<"Congruence's:"<<endl;
		Con.out();cout<<endl;
		cout<<"Lattice:"<<endl;
		L.out();
	}
	clog<<"Starting search..."<<endl;
	cout<<"--------------------------"<<endl;
	clog<<"What check?(m or d):";
	cin>>ch;
	func = (ch == 'm')?go1:go2;
	bool flag = check();
	cout<<"--------------------------"<<endl;
	clog<<"Printing lattice and automaton..."<<endl;
	lattice_print(flag);
// 	automaton_print();

	f.close();
	return 0;
}

