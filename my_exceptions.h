#ifndef MY_EXCEPTIONS_H
#define MY_EXCEPTIONS_H

#include <stdexcept>
#include <string>

/**
  @brief classe wrong_argument

  Eccezione di tipo custom utilizzata lanciata quando
  un indice passato come parametro per la lettura di 
  un elemento del Set non è valido o quando l’elemento 
  da rimuovere non è presente nel Set
*/
class wrong_argument : public std::invalid_argument {
public:

	/**
      Costruttore di default.
      Prende come parametro una stringa message; 
      lancia l’eccezione della classe standard std::invalid_argument(message).
    */
	wrong_argument(const std::string &message);

};

#endif