#ifndef _ANALISADOR_LEXICO_HPP_
#define _ANALISADOR_LEXICO_HPP_

#include <vector>
#include "Token.hpp"
#include <fstream>
#include <sstream>

class AnalisadorLexico
{
private:
  std::ifstream &fonte;
  unsigned int nLinha;
  std::stringstream lexema;
  char atual;

public:
  AnalisadorLexico(std::ifstream &arquivoFonte);
  const Token getProximo();

private:
  //utilidades
  bool avancar();
  bool noFim() const;
  const Token gerarComTipo(TipoToken tipo);
  const Token tentar(const std::string padrao, TipoToken tipo);
  std::string retornarLexema();
  //[0-9]
  bool numerico(char c) const;
  //([a-z]|[A-Z]|_)
  bool alfabetico(char c) const;
  //([a-z]|[A-Z]|_[0-9])
  bool alfanumerico(char c) const;
  
  //"estados"
  const Token inicio();
  const Token literal_texto();
  const Token prefixo_s();
  const Token prefixo_se();
  const Token prefixo_f();
  const Token prefixo_e();
  const Token prefixo_nao();
  const Token prefixo_menor();
  const Token prefixo_maior();
  const Token prefixo_igual();
  const Token literal_numerico();
  const Token id();
};

#endif