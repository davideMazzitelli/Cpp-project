#include "my_exceptions.h"

wrong_argument::wrong_argument(const std::string &message) 
: std::invalid_argument(message){ }

