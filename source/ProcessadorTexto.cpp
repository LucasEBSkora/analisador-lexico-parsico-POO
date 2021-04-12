#include "ProcessadorTexto.hpp"

#include <iostream>
#include <fstream>

#include "AnalisadorLexico.hpp"
#include "AnalisadorSintatico.hpp"

#include "Token.hpp"

#include "Erro.hpp"
#include "ErroLexico.hpp"

ProcessadorTexto::ProcessadorTexto(const char *caminho) : fonte{caminho} {}

int ProcessadorTexto::executar()
{
  if (!fonte.is_open())
  {
    std::cout << "erro! Arquivo não encontrado." << std::endl;
  }

  try
  {
    //Quando o analisador léxico é instanciado, ele tenta ler o primeiro token
    //por isso essa parte também precisa estar no try-catch
    AnalisadorLexico lex = AnalisadorLexico(fonte);
    // do
    // {
    //   Token atual = lex.getProximo();
    //   std::cout << atual << std::endl;
    // } while (lex.lookahead().getTipo() != eof);

    AnalisadorSintatico sin = AnalisadorSintatico(lex);
    sin.analisar();
  }
  catch (Erro &e)
  {
    std::cout << '\n'
              << e << std::endl;
  }
  fonte.close();
  return 0;
}
