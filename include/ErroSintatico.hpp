#ifndef _ERRO_SINTATICO_HPP_
#define _ERRO_SINTATICO_HPP_

#include <string>
#include <ostream>

#include "Token.hpp"
#include "Erro.hpp"

class Token; 

class ErroSintatico : public Erro
{
private:
  Token token;

public:
  ErroSintatico(std::string msg, Token token);
  std::string comoString() const override;
};


#endif