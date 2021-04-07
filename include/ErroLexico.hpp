#ifndef _ERRO_LEXICO_HPP_
#define _ERRO_LEXICO_HPP_

#include <string>
#include <ostream>

class ErroLexico
{
private:
  std::string mensagem;
  char caractere;
  unsigned nLinha;

public:
  ErroLexico(std::string msg, char caractere, unsigned nLinha);
  friend std::ostream &operator<<(std::ostream &out, const ErroLexico &e);
};


#endif