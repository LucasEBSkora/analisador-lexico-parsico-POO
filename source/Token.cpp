#include "Token.hpp"

Token::Token(std::string lex, TipoToken tipo, unsigned int n) : lexema{lex}, nLinha{n}, tipo{tipo}
{
}

const std::string &Token::getLexema() const
{
  return lexema;
}

unsigned int Token::getNLinha() const
{
  return nLinha;
}

TipoToken Token::getTipo() const
{
  return tipo;
}

const char *tipoComoStr(TipoToken t);

std::ostream &operator<<(std::ostream &out, const Token &v)
{
  out << '(' << tipoComoStr(v.getTipo()) << ',' << v.getLexema() << ", linha: " << v.getNLinha() << ')';
  return out;
}

const char *tipoComoStr(TipoToken t)
{
  switch (t)
  {
  case identificador:
    return "identificador";
  case literalNumerico:
    return "literalNumerico";
  case literalTexto:
    return "literalTexto";
  case se:
    return "se";
  case senao:
    return "senao";
  case funcao:
    return "funcao";
  case seja:
    return "seja";
  case retornar:
    return "retornar";
  case enquanto:
    return "enquanto";
  case verdadeiro:
    return "verdadeiro";
  case falso:
    return "falso";
  case nulo:
    return "nulo";
  case classe:
    return "classe";
  case eu:
    return "eu";
  case super:
    return "super";
  case igual:
    return "igual";
  case diferente:
    return "diferente";
  case menorIgual:
    return "menorIgual";
  case maiorIgual:
    return "maiorIgual";
  case menor:
    return "menor";
  case maior:
    return "maior";
  case atrib:
    return "atrib";
  case parenEsq:
    return "parenEsq";
  case parenDir:
    return "parenDir";
  case pontoEVirgula:
    return "pontoEVirgula";
  case chaveEsq:
    return "chaveEsq";
  case chaveDir:
    return "chaveDir";
  case mais:
    return "mais";
  case menos:
    return "menos";
  case asterisco:
    return "asterisco";
  case barra:
    return "barra";
  case exclamacao:
    return "exclamacao";
  case eComercial:
    return "eComercial";
  case barraVertical:
    return "barraVertical";
  case circunflexo:
    return "circunflexo";
  case doisPontos:
    return "doisPontos";
  case ponto:
    return "ponto";
  case virgula:
    return "virgula";
  case eof:
    return "eof";
  }
  return "tipo desconhecido";
}