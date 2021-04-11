#ifndef _ANALISADOR_SINTATICO_HPP_
#define _ANALISADOR_SINTATICO_HPP_

#include <string>

#include "AnalisadorLexico.hpp"
#include "Token.hpp"

class AnalisadorSintatico
{
private:
  AnalisadorLexico &lx;
  Token atual;

public:
  AnalisadorSintatico(AnalisadorLexico &lex);
  void analisar(); //equivale à regra "programa"
private:
  void declaracao();
  void decl_classe();
  void parametros();
  void decl_funcao();
  void corpo_funcao();
  void bloco();
  void decl_var();
  void corpo_var();
  void statement();
  void expr_stmt();
  void enquanto_stmt();
  void se_stmt();
  void retornar_stmt();
  void expressao();
  void atribuicao();
  void ou_logico();
  void e_logico();
  void igualdade();
  void comparacao();
  void adicao();
  void multiplicacao();
  void unario();
  void chamada();
  void funcao_ou_atributo();
  void argumentos();
  void primario();


  bool noFim() const;
  //se o token atual não for desse tipo, joga uma exceção. Caso contrário, avança para o próximo.
  void consumir(TipoToken tipo, std::string mensagem);
};

#endif
