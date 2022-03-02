#include "progetto.h"
#include <iostream>
#include "my_exceptions.h"
#include <string>



/**
    @brief tipo custom point

    Tipo custom utilizzato per il testing
  */
struct point {									// tipo custom point
  	int x; ///< coordinata x del punto
  	int y; ///< coordinata y del punto

  	/**
      Costruttore di default
      @post x == xx
      @post y == yy
  */
  	point(int xx, int yy) : x(xx), y(yy) {}
};

/**
    operatore di stream per un oggetto point.

    @param os stream di output
    @param p point da spedire sullo stream

    @return lo stream di output
  */
std::ostream &operator<<(std::ostream &os, const point &p) {
	std::cout<<"("<<p.x<<","<<p.y<<")";
	return os;
}

/**
    @brief predicato per tipi point per il testing della funzione filter_out.

    Ritorna true se p.x==p.y
  */
struct pred_point {								//predicato point
	bool operator()(const point &p) const {
		return (p.x == p.y);
	}
};

/**
    Verifica se point sono uguali.
    
    @param p1 point a sinistra dell'operatore
    @param p2 point a destra dell'operatore

    @return true se i due point sono uguali
    @return false altrimenti
  */
bool operator==(const point &p1, const point &p2){ // uguaglianza point
	if(p1.x==p2.x && p1.y==p2.y)
		return true; 
	else 
		return false;
}


/**
    @brief predicato per tipi int per il testing della funzione filter_out

    Ritorna true se il valore intero passato è uguale a 3
  */
struct is_three {								// predicato
  	bool operator()(int a) const {
    return (a == 3);
  	}
};

/**
    @brief predicato per tipi int per il testing della funzione filter_out

    Ritorna true se il valore intero passato è divisibile per 2
  */
struct is_even {								// predicato
  	bool operator()(int a) const {
    return (a%2 == 0);
  	}
};

/**
    @brief predicato per tipi int per il testing della funzione filter_out

    Ritorna true se il valore intero passato è minore di 5
  */
struct is_lessfive {							// predicato
  	bool operator()(int a) const {
    return (a < 5);
  	}
};



int prova_int(){								// test Set<int>

	std::cout<<"******** Test su set int ********"<<std::endl;


	Set<int> set1; // test costruttore primario

	set1.add(10); //test add
  	set1.add(1);
  	set1.add(20);
 	set1.add(8);
  	set1.add(12);
   	set1.add(12);
   	set1.add(1);
	set1.add(0);

	std::cout<<"\ntest costruttore primario"<<std::endl;
	std::cout<< set1 <<"\n"<< std::endl; // test operatore <<


	Set<int> setscnd(1);// test costruttore secondario
	std::cout<<"test costruttore secondario"<<std::endl;
	std::cout<< setscnd << std::endl;


	Set<int> set1c(set1); // test copy constr
	std::cout<< "\ntest copy constructor" << std::endl;
	std::cout<< set1c <<"\n"<< std::endl;

	std::cout<< "test operatore ==" << std::endl; // test operatore ==
	bool eql = (set1==set1c); 
	std::cout<< "set1 == set1c (true):" << eql <<std::endl;

	Set<int> setx;
	eql = (set1==setx);
	std::cout<< "set1 == setx (false):" << eql <<std::endl;



	Set<int> set2 = set1; // test assegnamento
	std::cout<< "\ntest assegnamento" << std::endl;
	std::cout<< set2 <<"\n"<< std::endl;

	set1.remove(20); // test remove
	set1.remove(8);
	std::cout<< "test remove" << std::endl;
	std::cout<< set1 <<"\n"<< std::endl;


	int dati[6] = {5,8,4,9,2,4}; // test costruttore iteratori
	Set<int> set3(dati, dati+6);
	std::cout<< "test costruttore iteratori" << std::endl;
	std::cout<< set3 <<"\n"<< std::endl;

	Set<int> set4(set1.begin(), set1.end());
	std::cout<< "test costruttore iteratori" << std::endl;
	std::cout<< set4 <<"\n"<< std::endl;


	std::cout<< "test operatore [] -> set3[3]" << std::endl; // test operatore []
	std::cout<< set3[3] <<"\n" << std::endl;


	is_even ie;  // test filter_out
	Set<int> setIe = filter_out(set3, ie);
	std::cout<< "test filter_out" << std::endl;
	std::cout<< setIe <<"\n"<< std::endl;


	Set<int> setConcat = set3 + set4; // test concatenazione
	std::cout<< "test concatenazione set3 e set4" << std::endl;
	std::cout<< setConcat << std::endl;


	Set<int> setIntersect = set1c - set1; // test intersezione
	std::cout<< "\ntest intersezione set1 e set1c" << std::endl; // 10 1 12 0
	std::cout<< setIntersect << std::endl;

	return 0;
}




int prova_point(){

		std::cout<<"\n******** Test su set di tipi custom point ********"<<std::endl;


	Set<point> setp;					// test tipi custom

	std::cout<<"test costruttore primario"<<std::endl;
	std::cout<< setp << std::endl;

	point p1(1,1);
	point p2(3,7);
	point p3(1,1);
	point p4(6,4);
	point p5(10,3);


	setp.add(p1);
	setp.add(p2);
	setp.add(p3);


	std::cout<<"\ntest dopo add"<<std::endl;
	std::cout<< setp << std::endl;

	std::cout<<"\ntest operatore: setp[2]"<<std::endl; 
	std::cout<< setp[2] << std::endl;


	std::cout<<"\ntest costruttore secondario"<<std::endl;
	Set<point> setpscnd(p2);
	std::cout<< setpscnd <<std::endl; 


	std::cout<<"\ntest copy constructor"<<std::endl;
	Set<point> setpc(setp);
	std::cout<< setpc << std::endl;


	std::cout<<"\ntest operatore ="<<std::endl;
	Set<point> setp2 = setp;
	std::cout<< setp2 << std::endl;


	std::cout<<"\ntest remove"<<std::endl;
	setp2.remove(p1);
	std::cout<< setp2 << std::endl;


	std::cout<<"\ntest costruttore iteratori"<<std::endl;
	point datip[5] = {p1,p2,p3,p4,p5};
	Set<point> setpIter(datip, datip+5);
	std::cout<< setpIter << std::endl;


	std::cout<<"\ntest operatore =="<<std::endl;
	bool eqlp = (setp == setpIter);
	std::cout<< eqlp << std::endl; //false
	Set<point> setp3;
	setp3.add(p2);
	setp3.add(p1);
	setp3.add(p3);
	eqlp = (setp == setp3); //true
	std::cout<< eqlp << std::endl;


	std::cout<<"\ntest filter_out"<<std::endl;
	pred_point pp;
	std::cout<< filter_out(setp3, pp) <<std::endl; //(1,1)


	std::cout<<"\ntest concatenazione"<<std::endl;
	Set<point> setp4(p5);
	Set<point> setp5(p4);
	std::cout<< setp4 + setp5  <<std::endl; // (10,3) (6,4)


	std::cout<<"\ntest intersezione"<<std::endl; // (1,1) (3,7)
	std::cout<< setp - setpIter  <<std::endl;



	return 0;
}


/**
    @brief predicato per tipi std::string per il testing della funzione filter_out

    Ritorna true se la lunghezza della stringa passata è minore di 4
  */
struct pred_str {
	bool operator() (const std::string &str){
		return (str.length()<4);
	}
};


void prova_stringhe(void) {

	std::cout<<"\n******** Test su set di stringhe ********"<<std::endl;

	Set<std::string> setst;

	std::cout<<"\ntest costruttore primario"<<std::endl;
	std::cout<< setst <<std::endl;

	setst.add("uno");
	setst.add("cane");
	setst.add("gatto");
	setst.add("uno");
	setst.add("boh");

	std::cout<<"\ntest add"<<std::endl;
	std::cout<< setst <<std::endl;

	std::cout<<"\ntest operatore []: setst[3]"<<std::endl;
	std::cout<< setst[3] <<std::endl;

	std::cout<<"\ntest costruttore secondario"<<std::endl;
	Set<std::string> setst2("secondario");
	std::cout<< setst2 <<std::endl;


	std::cout<<"\ntest copy constructor"<<std::endl;
	Set<std::string> setCopy(setst);
	std::cout<<setCopy<<std::endl;


	std::cout<<"\ntest operatore ="<<std::endl;
	setCopy = setst2;
	std::cout<<setCopy<<std::endl;


	std::cout<<"\ntest remove"<<std::endl;
	setCopy.remove("secondario");
	std::cout<<setCopy<<std::endl;


	std::cout<<"\ntest costruttore iteratori"<<std::endl;
	std::string datip[5] = {"uno", "due", "tre", "quattro", "cinque"};
	Set<std::string> setstIter(datip, datip+5);
	std::cout<< setstIter << std::endl;


	std::cout<<"\ntest operatore =="<<std::endl;
	bool eqlst = (setstIter==setst); //false
	std::cout<< eqlst << std::endl;

	Set<std::string> setst3;
	setst3.add("cinque");
	setst3.add("tre");
	setst3.add("quattro");
	setst3.add("uno");
	setst3.add("due");

	eqlst = (setst3==setstIter); //true
	std::cout<< eqlst << std::endl;


	std::cout<<"\ntest filter_out"<<std::endl;
	pred_str ps;
	std::cout<< filter_out(setst3, ps) << std::endl;

	std::cout<<"\ntest concatenazione"<<std::endl;
	std::cout<< setst3 + setst <<std::endl;


	std::cout<<"\ntest intersezione"<<std::endl;
	std::cout<< setst3 - setst <<std::endl;


}




int main(){

	prova_int();

	prova_point();

	prova_stringhe();

	return 0;
}