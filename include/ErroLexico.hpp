#ifndef _ERRO_LEXICO_HPP_
#define _ERRO_LEXICO_HPP_

#include <string>
#include <ostream>
#include "Erro.hpp"

class ErroLexico : public Erro
{
private:
  char caractere;
  unsigned nLinha;

public:
  ErroLexico(std::string msg, char caractere, unsigned nLinha);
  std::string comoString() const override;
};


#endif