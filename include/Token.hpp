#ifndef _TOKEN_HPP_
#define _TOKEN_HPP_

#include <string>
#include <ostream>

enum TipoToken
{
  identificador,
  literalNumerico,
  literalTexto,
  se,
  senao,
  funcao,
  seja,
  retornar,
  enquanto,
  verdadeiro,
  falso,
  nulo,
  classe,
  eu,
  super,
  igual,         // ==
  diferente,     // !=
  menorIgual,    // <=
  maiorIgual,    // >=
  menor,         // <
  maior,         // >
  atrib,         //=
  parenEsq,      // (
  parenDir,      // )
  pontoEVirgula, // ;
  chaveEsq,      // {
  chaveDir,      // }
  mais,          // +
  menos,         // -
  asterisco,     // *
  barra,         // /
  exclamacao,    // !
  eComercial,    // &
  barraVertical, // |
  circunflexo,   // ^
  doisPontos,    // :
  ponto,         //.
  virgula,       //,
  eof
};

class Token
{

private:
  std::string lexema;
  unsigned int nLinha;
  TipoToken tipo;

public:
  Token() = delete;
  Token(std::string lex, TipoToken tipo, unsigned int n);
  const std::string &getLexema() const;
  unsigned int getNLinha() const;
  TipoToken getTipo() const;
};

std::ostream &operator<<(std::ostream &out, const Token &v);

#endif