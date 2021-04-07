#include "ProcessadorTexto.hpp"

#include <iostream>
#include <fstream>

#include "AnalisadorLexico.hpp"
#include "ErroLexico.hpp"

ProcessadorTexto::ProcessadorTexto(const char *caminho) : fonte{caminho} {}

int ProcessadorTexto::executar()
{
  if (!fonte.is_open())
  {
    std::cout << "erro! Arquivo não encontrado." << std::endl;
  }

  AnalisadorLexico lex = AnalisadorLexico(fonte);
  
  Token token = lex.getProximo();
  while (token.getTipo() != TipoToken::eof)
  {
    std::cout << token << std::endl;
    try {

    token = lex.getProximo();
    } catch(ErroLexico e) {
      std::cout << e << std::endl;
      token = lex.getProximo();
    }
  }

  return 0;
}
