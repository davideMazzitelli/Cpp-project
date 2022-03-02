#ifndef PROGETTO_H
#define PROGETTO_H

#include <iostream>
#include <ostream>
#include "my_exceptions.h"
#include <cstddef>


/**
  @brief classe Set di elementi generici di tipo T

  La classe imlementa un Set di elementi T.
  In particolare un Set è una collezione di elementi che
  non può contenere duplicati

*/
template<typename T>
class Set{

	/**
    @brief struttura element

    Struttura dati element interna che viene usata per creare
    il Set.  
  */
	struct  element{
	
	T value; ///< Valore dell'elemento 
	element *left; ///< Puntatore all'elemento precedente
	element *right; ///< Puntatore all'elemento successivo

	/**
      Costruttore di default
      @post left == nullptr
      @post right == nullptr
  */
	element() : left(nullptr), right(nullptr) {}
	

	/**
      Costruttore secondario

      @param value valore da copiare

      @post value == value
      @post left == nullptr
      @post right == nullptr
    */
	explicit element(const T &v) : value(v), left(nullptr), right(nullptr) {}

	/**
      Copy constructor. 
      Copiamo i dati membro a membro.

      @param other elemento da copiare
    */
	element(const element &other) : value(other.value), left(other.left), right(other.right) {}

	/**
      Distruttore. 
    */
	~element() {}

	/**
      Operatore di assegnamento. 

      @param other elemento da copiare
      @return reference al nodo this
    */
	element& operator=(const element &other){
		value=other.value;
		left=other.left;
		right=other.right;

		return *this;
	}

}; // fine struct element

	element *head; ///< puntatore al primo elemento del Set
	unsigned int size; ///< numero di elementi nel Set

public:

	/**
    Costruttore di default.

    @post head == nullptr
    @post size == 0
  */
	Set() : head(nullptr), size(0) {}


	/**
      Costruttore secondario

      Verrà creato un Set di un elemento il cui valore è passato 
      come parametro

      @param val valore da aggiungere al Set    
    */
	explicit Set(const T &val) : head(nullptr), size(0) {
		try{
			add(val);
		}
		catch(...){
			clear();
    	throw;
		}
		size = 1;
	} 
	

	 /**
    Copy constructor

    @param other Set da copiare
  */
	Set(const Set &other) : head(nullptr), size(0) {
		element *curr = other.head;
		try{
			while(curr != nullptr){
				add(curr->value);
				curr = curr->right;
			}
		}
		catch(...){
			clear();
    	throw;
		}
	}


	/**
    Distruttore 

    @post head == nullptr
    @post size == 0
  */
	~Set() {
		clear();
	}	


	/**
    Operatore di assegnamento

    @param other Set da copiare

    @return reference al Set this

    @post size = other.size
  */
	Set& operator=(const Set &other){
		Set tmp(other);
		std::swap(this->head, tmp.head);
    std::swap(this->size, tmp.size);
    return *this;
	}


	// get size
	unsigned int get_size() const {
		return size;
	}


	/**
    Aggiunge un elemento nel Set verificando che tale
    non sia già presente tramite funzione checkSet

    @param value valore da inserire nel Set

    @post size = size+1
  */
	void add(const T &val){
		element *tmp = new element(val);

		if(size==0){ //Set vuoto
			head = tmp;
			size=1;
			return;
		}

		if(checkSet(val) == false){
			element *curr = head;
			element *prev = head;
			while(curr!=nullptr){
				prev = curr;
				curr = curr->right;
			}
			prev->right=tmp;
			tmp->left = prev;
			tmp->right = nullptr;
			size++;
		}
		else{
			delete tmp;
		}
	}

	/**
    Verifica che il valore passato come parametro non
    sia già presente nel Set

    @param value valore da verificare

    @return true se l'elemento è presente nel Set
    @return false altrimenti
  */
	bool checkSet(const T &val) const{
		element *curr = this->head;
		while(curr != nullptr){
			if(val == curr->value)
				return true;
			else
				curr = curr->right;
		}
		return false;
	}


	/**
    Rimuove l'elemento il cui valore è passato come
    parametro dal Set

    @param value valore da rimuovere
  */
	void remove(const T &val){
		if(checkSet(val) == true){
			element *curr = head;
			element *next = head;
			element *prev = head;

			while(curr!=nullptr){
				if(curr->value==val){ 	//trovato l'elemento nel set
					if(size==1){	//set di 1 solo elemento
						delete curr;
						size = 0;
						this->head = nullptr;
						return;
					}
					else
						if(curr->left == nullptr){ 	//l'elemento da rimuovere è l'head
							next = curr->right;
							this->head = next;
							delete curr;
							size--;
							return;
						}
						else	
							if(curr->right == nullptr){	//l'elemento da rimuovere è l'ultimo del set
								prev = curr->left;
								prev->right = nullptr;
								delete curr;
								size--;
								return;
							}
						else{	//elemento è interno al set
							prev = curr->left;
							next = curr->right;
							prev->right = next;
							next->left = prev;
							delete curr;
							size--;
							return;
						}
				}
				curr = curr->right;
			}
		}	
		else
			throw wrong_argument("elemento non presente nel Set");
	}


	/**
    Accesso in lettura dell'elemento alla posizione
    index (parametro) del Set.
    Le posizioni partono dall'indice 1

    @param index indice dell'elemento nel Set

    @return reference al valore dell'elemento all'indice
    index nel Set
  */
	T& operator[](unsigned int index) const {
		element *curr = head;

		if(index == 0 || index > size){
			throw wrong_argument("wrong index");
		}
		while(index > 1){
			curr = curr->right;
			index--;
		}
		return curr->value;;
	}


	/**
    Funzione globale che implementa l'operatore di stream per un oggetto Set.
    La funzione messa friend perchè accediamo ai dati privati di Set.

    @param os stream di output
    @param set Set da spedire sullo stream

    @return lo stream di output
  */
	friend std::ostream& operator<<(std::ostream &os, const Set &set) {
		os<< "Size: " <<set.size <<std::endl;
		element *curr = set.head;
		while(curr != nullptr){
			os<< curr->value << " ";
			curr = curr->right;
		}
		return os;
	}


	/**
    Verifica se due Set sono uguali.
    Due Set sono uguali se contengono gli stessi elementi,
    anche se in ordine diverso.
    Utilizzo della funzione checkSet.

    @param other Set di cui verificare l'uguaglianza

    @return true se i due Set sono uguali
    @return false altrimenti
  */
	bool operator==(const Set &other) const{
		if(size != other.size)
			return false;
		element *curr = other.head;
		while(curr != nullptr){
			if(checkSet(curr->value)==false)
				return false;
			curr = curr->right;
		}
		return true;
	}


	/**
    Costruttore che crea un Set composto da dati
    presi da una sequenza identificata da uniteratore di 
    inizio e uno di fine. 
    Gli iteratori possono essere di qualunque tipo Q. 

    @param b iteratore di inizio sequenza
    @param e iteratore di fine sequenza
  */
	template <typename Q>
  Set(Q b, Q e) : head(nullptr), size(0){
  	try{
   		for( ; b!=e; ++b)
      	add(static_cast<T>(*b));
   	}
   	catch(...){
   		clear();
   		throw;
    }
  }

  /**
   Svuota il Set

   @post head == nullptr
   @post size == 0
  */
  void clear() {
   element *curr = head;
   while (curr!=nullptr) {
   	element *next = curr->right;
     	delete curr;
     	curr = next;
  	}
   	size = 0;
   	head = nullptr;
  }
  


  /**
    Gli iteratori devono iterare sui dati inseriti nella classe
    principale. 
    Nel Set mettiamo dei dati di tipo T, l'iteratore deve quindi
    iterare sui dati di tipo T. 
    NON sui nodi della lista che sono un dettaglio implementativo interno.
  */
	class const_iterator {

  public:
    typedef std::bidirectional_iterator_tag iterator_category;
    typedef T                         tipo_value;
    typedef ptrdiff_t                 difference_type;
    typedef const T*                  pointer;
    typedef const T&                  reference;
  
    const_iterator() : c_pointer(nullptr) {
    }
    
    const_iterator(const const_iterator &other) : c_pointer(other.c_pointer) {
    }

    const_iterator& operator=(const const_iterator &other) {
      c_pointer = other.c_pointer;
      return *this;
    }

    ~const_iterator() { }

    // Ritorna il dato riferito dall'iteratore (dereferenziamento)
    reference operator*() const {
      return c_pointer->value;
    }

    // Ritorna il puntatore al dato riferito dall'iteratore
    pointer operator->() const {
      return &(c_pointer->value);
    }
    
    // Operatore di iterazione post-incremento
    const_iterator operator++(int) {
      const_iterator tmp(*this);
      c_pointer = c_pointer->right;
      return tmp;
    }

    // Operatore di iterazione pre-incremento
    const_iterator& operator++() {
      	c_pointer = c_pointer->right;
      	return *this;
    }

    // post-decremento
    const_iterator operator--(int) {
			const_iterator tmp(*this);
      c_pointer = c_pointer->left;
      return tmp;	
		}

		// Operatore di iterazione pre-decremento
		const_iterator &operator--() {
			c_pointer = c_pointer->left;
      return *this;
		}

    // Uguaglianza
    bool operator==(const const_iterator &other) const {
    	return (c_pointer == other.c_pointer);
    }
    
    // Diversita'
    bool operator!=(const const_iterator &other) const {
     	return !(other == *this);
    }


  private:
    friend class Set; 
    const_iterator(const element *el) : c_pointer(el) { }
    const element *c_pointer;

  }; // fine const_iterator

 
  	// begin: Ritorna l'iteratore all'inizio della sequenza dati
  const_iterator begin() const {
   	return const_iterator(head);
	}
  
 	//end: Ritorna l'iteratore alla fine della sequenza dati
  const_iterator end() const {
  	return const_iterator(nullptr);
  }


};// fine classe Set

/**
  Funzione globale che, dato un Set generico S su tipi T 
  e un predicato booleano generico P, ritorna un 
	nuovo set di tipi T ottenuto prendendo da S tutti gli 
	elementi che soddisfano il predicato P

  @param set Set sorgente
  @param predicato predicato

*/
template<typename T, typename P>
Set<T> filter_out(const Set<T> &set, P predicato) {
	typename Set<T>::const_iterator b, e;

	Set<T> tmp;
	
	try{
		for(b = set.begin(), e=set.end(); b!=e; ++b){
			if (predicato(*b))
				tmp.add(*b);
		}
	}
	catch(...){
		tmp.clear();
		throw;
	}
	
	return tmp;
}

/**
  Funzione globale che,  dati in input due Set
  generici su tipi T, ritorna un Set di tipi T 
  che contiene gli elementi di entrambi i set (“concatenazione” di set)

  @param set1 Set sorgente 1
  @param set2 Set sorgente 2
*/
template<typename T>
Set<T> operator+(const Set<T> &set1, const Set<T> &set2) {
	typename Set<T>::const_iterator b, e;

	Set<T> tmp;
	try{
		for(b = set1.begin(), e=set1.end(); b!=e; ++b)	{
			tmp.add(*b);
		}
		for(b = set2.begin(), e=set2.end(); b!=e; ++b)	{
			tmp.add(*b);
		}
	}
	catch(...){
		tmp.clear();
		throw;
	}

	return tmp;
}

/**
  Funzione globale che, dati in input due Set
	generici su tipi T, ritorna un Set di tipi T 
	che contiene gli elementi comuni a entrambi i set 
	(“intersezione” di set)

  @param set1 Set sorgente 1
  @param set2 Set sorgente 2
*/
template<typename T>
Set<T> operator-(const Set<T> &set1, const Set<T> &set2) {
	typename Set<T>::const_iterator b, e;

	Set<T> tmp;
	
	try{
		for(b = set1.begin(), e=set1.end(); b!=e; ++b){
			if(set2.checkSet(*b)==true)
				tmp.add(*b);
		}
	}
	catch(...){
		tmp.clear();
		throw;
	}

	return tmp;
}


#endif