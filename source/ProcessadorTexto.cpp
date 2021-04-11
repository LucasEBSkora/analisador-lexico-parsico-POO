#include "ProcessadorTexto.hpp"

#include <iostream>
#include <fstream>

#include "AnalisadorLexico.hpp"
#include "AnalisadorSintatico.hpp"

#include "Erro.hpp"

ProcessadorTexto::ProcessadorTexto(const char *caminho) : fonte{caminho} {}

int ProcessadorTexto::executar()
{
  if (!fonte.is_open())
  {
    std::cout << "erro! Arquivo não encontrado." << std::endl;
  }

  AnalisadorLexico lex = AnalisadorLexico(fonte);

  AnalisadorSintatico sin = AnalisadorSintatico(lex);
  try
  {
    sin.analisar();
  }
  catch (Erro* e)
  {
    std::cout << *e << std::endl;
  }
  return 0;
}
