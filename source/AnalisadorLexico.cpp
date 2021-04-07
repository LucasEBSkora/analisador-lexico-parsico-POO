#include "AnalisadorLexico.hpp"

#include <iostream>

#include "ErroLexico.hpp"

AnalisadorLexico::AnalisadorLexico(std::ifstream &arquivoFonte) : fonte{arquivoFonte}, nLinha{1}
{
  avancar();
}

const Token AnalisadorLexico::getProximo()
{

  while (true)
  {
    if (atual == '\n')
    {
      ++nLinha;
      avancar();
    }
    else if (!(atual == ' ' || atual == '\t' || atual == '\r'))
      break;
    avancar();
  }

  if (!noFim())
    return inicio();
  else
    return Token("", TipoToken::eof, nLinha);
}

const Token AnalisadorLexico::inicio()
{
  lexema = std::stringstream();
  // std::cout << "primeiro caractere:" << atual << std::endl;
  switch (atual)
  {
  case '"':
    return literal_texto();
  case 's':
    return prefixo_s();
  case 'f':
    return prefixo_f();
  case 'r':
    return tentar("etornar", retornar);
  case 'e':
    return prefixo_e();
  case 'v':
    return tentar("erdadeiro", verdadeiro);
  case 'n':
    return tentar("ulo", nulo);
  case 'c':
    return tentar("lasse", classe);
  case '!':
    return prefixo_nao();
  case '<':
    return prefixo_menor();
  case '>':
    return prefixo_maior();
  case '=':
    return prefixo_igual();
  case '(':
    return gerarComTipo(parenEsq);
  case ')':
    return gerarComTipo(parenDir);
  case ';':
    return gerarComTipo(pontoEVirgula);
  case '{':
    return gerarComTipo(chaveEsq);
  case '}':
    return gerarComTipo(chaveDir);
  case '+':
    return gerarComTipo(mais);
  case '-':
    return gerarComTipo(menos);
  case '*':
    return gerarComTipo(asterisco);
  case '/':
    return gerarComTipo(barra);
  case '&':
    return gerarComTipo(eComercial);
  case '|':
    return gerarComTipo(barraVertical);
  case '^':
    return gerarComTipo(circunflexo);
  case ':':
    return gerarComTipo(doisPontos);
  case '.':
    return gerarComTipo(ponto);
  case ',':
    return gerarComTipo(virgula);
  }
  if (numerico(atual))
    return literal_numerico();
  if (alfabetico(atual))
    return id();
  throw ErroLexico("Caractere inesperado!", atual, nLinha);
}

const Token AnalisadorLexico::literal_texto()
{
  avancar();
  while (fonte.peek() != -1)
  {
    if (atual == '"')
      break;
    else if (atual == '\n')
      ++nLinha;
    avancar();
  }
  if (atual == '"')
    return gerarComTipo(literalTexto);
  else
    throw ErroLexico("String nao terminada!", atual, nLinha);
}
const Token AnalisadorLexico::prefixo_s()
{
  avancar();
  if (atual == 'e')
    return prefixo_se();
  if (atual == 'u')
    return tentar("uper", super);
  return id();
}

const Token AnalisadorLexico::prefixo_se()
{
  if (fonte.peek() == 'n')
    return tentar("nao", senao);
  if (fonte.peek() == 'j')
    return tentar("ja", seja);
  if (alfanumerico(fonte.peek()))
    return id();
  return gerarComTipo(se);
}

const Token AnalisadorLexico::prefixo_f()
{
  avancar();
  if (atual == 'u')
    return tentar("ncao", funcao);
  if (atual == 'a')
    return tentar("lso", falso);
  return id();
}

const Token AnalisadorLexico::prefixo_e()
{
  avancar();
  std::cout << "atual: " << atual << std::endl;
  if (atual == 'n')
    tentar("quanto", enquanto);
  if (atual == 'u' && !alfanumerico(fonte.peek()))
    return gerarComTipo(eu);
  return id();
}

const Token AnalisadorLexico::prefixo_nao()
{
  if (fonte.peek() == '=')
  {
    avancar();
    return gerarComTipo(diferente);
  }
  return gerarComTipo(exclamacao);
}
const Token AnalisadorLexico::prefixo_menor()
{
  if (fonte.peek() == '=')
  {
    avancar();
    return gerarComTipo(menorIgual);
  }
  return gerarComTipo(menor);
}
const Token AnalisadorLexico::prefixo_maior()
{
  if (fonte.peek() == '=')
  {
    avancar();
    return gerarComTipo(maiorIgual);
  }
  return gerarComTipo(maior);
}
const Token AnalisadorLexico::prefixo_igual()
{
  if (fonte.peek() == '=')
  {
    avancar();
    return gerarComTipo(igual);
  }
  return gerarComTipo(atrib);
}
const Token AnalisadorLexico::literal_numerico()
{
  
  while(numerico(fonte.peek())) avancar();
  
  if (fonte.peek() == '.') {
    avancar();
    while(numerico(fonte.peek())) avancar();
  } 

  return gerarComTipo(literalNumerico);
}
const Token AnalisadorLexico::id()
{
  while (alfanumerico(fonte.peek()))
    avancar();
  return gerarComTipo(identificador);
}

bool AnalisadorLexico::avancar()
{
  lexema << atual;
  atual = fonte.get();
  return atual == -1;
}

bool AnalisadorLexico::noFim() const
{
  return atual == -1;
}
const Token AnalisadorLexico::gerarComTipo(TipoToken tipo)
{
  avancar();
  return Token(retornarLexema(), tipo, nLinha);
}

const Token AnalisadorLexico::tentar(const std::string padrao, TipoToken tipo)
{
  for (char c : padrao)
  {
    if (fonte.peek() != c)
      return id();
    avancar();
  }
  return gerarComTipo(tipo);
}

std::string AnalisadorLexico::retornarLexema()
{
  return lexema.str();
}

bool AnalisadorLexico::numerico(char c) const
{
  return ('0' <= c && c <= '9');
}

bool AnalisadorLexico::alfabetico(char c) const
{
  return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') ||
         c == '_';
}

bool AnalisadorLexico::alfanumerico(char c) const
{
  return alfabetico(c) || numerico(c);
}