#include "AnalisadorSintatico.hpp"

#include "ErroLexico.hpp"
#include "ErroSintatico.hpp"

#include <iostream>

AnalisadorSintatico::AnalisadorSintatico(AnalisadorLexico &lex) : lx{lex}, atual{lx.getProximo()} {}

void AnalisadorSintatico::analisar()
{
  while (!noFim())
  {
    declaracao();
    std::cout << std::endl;
  }
}

void AnalisadorSintatico::declaracao()
{
  switch (atual.getTipo())
  {
  case classe:
    decl_classe();
    break;
  case funcao:
    decl_funcao();
    break;
  case seja:
    decl_var();
    break;
  default:
    statement();
    break;
  }
}

void AnalisadorSintatico::decl_classe()
{
  std::cout << "[decl_classe: ";
  atual = lx.getProximo(); //consome o "classe"
  if (atual.getTipo() != identificador)
    throw ErroSintatico("esperado nome da classe", atual);
  std::cout << atual.getLexema();
  atual = lx.getProximo();
  if (atual.getTipo() == doisPontos)
  {
    std::cout << "deriva de ";
    atual = lx.getProximo();
    parametros();
  }
  consumir(chaveEsq, "abre chaves necessária após declaração de classe");
  std::cout << " com corpo: [\n";
  while (atual.getTipo() == identificador)
  {
    TipoToken tipo_lookahead = lx.lookahead().getTipo();
    if (tipo_lookahead == parenEsq)
    {
      std::cout << " [metodo ";
      corpo_funcao(); //método
      std::cout << "]\n";
    }
    else if (tipo_lookahead == pontoEVirgula || tipo_lookahead == atrib)
    {
      std::cout << "atributo ";
      corpo_var();
      std::cout << "]\n";
    }
    else
      throw ErroSintatico("Token inesperado!", lx.lookahead());
  }
  std::cout << "]]";
  consumir(chaveDir, "fecha chaves necessária no fim de declaração de classe");
}

void AnalisadorSintatico::parametros()
{
  while (true)
  {
    if (atual.getTipo() != identificador)
      throw ErroSintatico("identificador esperado!", atual);
    std::cout << atual.getLexema();
    atual = lx.getProximo();
    if (atual.getTipo() != virgula)
      break;
    else
    {
      atual = lx.getProximo();
      std::cout << ", ";
    }
  }
}

void AnalisadorSintatico::decl_funcao()
{
  atual = lx.getProximo();
  std::cout << "[funcao ";
  corpo_funcao();
  std::cout << "]";
}
void AnalisadorSintatico::corpo_funcao()
{
  std::cout << atual.getLexema() << ' ';
  consumir(identificador, "Esperava nome da funcao!");
  consumir(parenEsq, "esperava abre parenteses apos nome da funcao");
  if (atual.getTipo() != parenDir)
  {
    std::cout << "parametros: [";
    parametros();
    std::cout << "] ";
  }
  consumir(parenDir, "esperava fecha parenteses apos nome da funcao");
  std::cout << "corpo: [";
  bloco();
}

void AnalisadorSintatico::bloco()
{
  consumir(chaveEsq, "Blocos precisam ser abertos com chaves!");
  std::cout << std::endl;
  while (atual.getTipo() != chaveDir)
  {
    declaracao();
    std::cout << std::endl;
  }
  consumir(chaveDir, "Blocos precisam ser fechados com chaves!");
}

void AnalisadorSintatico::decl_var()
{
  consumir(seja, "declaracao de variáveis sempre começa com a palavra chave 'seja' ");
  std::cout << "variavel: [";
  corpo_var();
  std::cout << ']';
}
void AnalisadorSintatico::corpo_var()
{
  std::cout << "nome: " << atual.getLexema();
  consumir(identificador, "Esperava nome!");
  if (atual.getTipo() == atrib)
  {
    std::cout << " valor inicial: ";
    atual = lx.getProximo();
    expressao();
  }
  consumir(pontoEVirgula, "esperava ; após declaração de variável!");
}
void AnalisadorSintatico::statement()
{
  switch (atual.getTipo())
  {
  case enquanto:
    enquanto_stmt();
    break;
  case se:
    se_stmt();
    break;
  case retornar:
    retornar_stmt();
    break;
  case chaveEsq:
    std::cout << "bloco: [";
    bloco();
    std::cout << ']';
    break;
  default:
    expr_stmt();
    break;
  }
}

void AnalisadorSintatico::expr_stmt()
{
  expressao();
  consumir(pontoEVirgula, "';' faltando!");
}

void AnalisadorSintatico::enquanto_stmt()
{
  consumir(enquanto, "Esperava palavra chave 'enquanto'");
  std::cout << "enquanto [ condicao : ";
  consumir(parenEsq, "Esperava abre parenteses após palavra chave 'enquanto'");
  expressao();
  consumir(parenDir, "Esperava fecha parenteses após condição da iteração");
  std::cout << " repeticao: ";
  statement();
  std::cout << ']';
}

void AnalisadorSintatico::se_stmt()
{
  consumir(se, "Esperava palavra chave 'se'");
  std::cout << "[se ";
  consumir(parenEsq, "Esperava abre parenteses após palavra chave 'enquanto'");
  expressao();
  consumir(parenDir, "Esperava fecha parenteses após condição");
  std::cout << " entao ";
  statement();
  if (atual.getTipo() == senao)
  {
    atual = lx.getProximo();
    std::cout << " senao ";
    statement();
  }
  std::cout << "]";
}

void AnalisadorSintatico::retornar_stmt()
{
  consumir(retornar, "Esperava palavra chave 'retornar'");
  std::cout << "[retornar";
  if (atual.getTipo() != pontoEVirgula)
  {
    std::cout << ' ';
    expressao();
  }
  consumir(pontoEVirgula, "';' faltando após valor de retorno!");
  std::cout << ']';
}

void AnalisadorSintatico::expressao()
{
  atribuicao();
}

void AnalisadorSintatico::atribuicao()
{
  ou_logico();
  if (atual.getTipo() == atrib)
  {
    atual = lx.getProximo();
    std::cout << " recebe ";
    atribuicao();
  }
}

void AnalisadorSintatico::ou_logico()
{
  e_logico();
  if (atual.getTipo() == barraVertical)
  {
    atual = lx.getProximo();
    std::cout << " ou ";
    ou_logico();
  }
}

void AnalisadorSintatico::e_logico()
{
  igualdade();
  if (atual.getTipo() == eComercial)
  {
    atual = lx.getProximo();
    std::cout << " e ";
    e_logico();
  }
}

void AnalisadorSintatico::igualdade()
{
  comparacao();
  if (atual.getTipo() == igual)
  {
    atual = lx.getProximo();
    std::cout << " igual a ";
    igualdade();
  }
  else if (atual.getTipo() == diferente)
  {
    atual = lx.getProximo();
    std::cout << " diferente de ";
    igualdade();
  }
}

void AnalisadorSintatico::comparacao()
{
  adicao();
  if (atual.getTipo() == menorIgual)
  {
    atual = lx.getProximo();
    std::cout << " menor ou igual a ";
    comparacao();
  }
  else if (atual.getTipo() == maiorIgual)
  {
    atual = lx.getProximo();
    std::cout << " maior ou igual a ";
    comparacao();
  }
  else if (atual.getTipo() == menor)
  {
    atual = lx.getProximo();
    std::cout << " menor que ";
    comparacao();
  }
  else if (atual.getTipo() == maior)
  {
    atual = lx.getProximo();
    std::cout << " maior que ";
    comparacao();
  }
}

void AnalisadorSintatico::adicao()
{
  multiplicacao();
  if (atual.getTipo() == mais)
  {
    atual = lx.getProximo();
    std::cout << " mais ";
    adicao();
  }
  else if (atual.getTipo() == menos)
  {
    atual = lx.getProximo();
    std::cout << " menos ";
    adicao();
  }
}

void AnalisadorSintatico::multiplicacao()
{
  unario();
  if (atual.getTipo() == asterisco)
  {
    atual = lx.getProximo();
    std::cout << " vezes ";
    multiplicacao();
  }
  else if (atual.getTipo() == barra)
  {
    atual = lx.getProximo();
    std::cout << " dividido por ";
    multiplicacao();
  }
}

void AnalisadorSintatico::unario()
{
  if (atual.getTipo() == exclamacao)
  {
    atual = lx.getProximo();
    std::cout << "não ";
    unario();
  }
  else if (atual.getTipo() == menos)
  {
    atual = lx.getProximo();
    std::cout << "menos ";
    unario();
  }
  else
    chamada();
}
void AnalisadorSintatico::chamada()
{
  primario();
  funcao_ou_atributo();
}
void AnalisadorSintatico::funcao_ou_atributo()
{
  if (atual.getTipo() == parenEsq)
  {
    atual = lx.getProximo();
    if (atual.getTipo() != parenDir)
    {
      std::cout << " args: [";
      argumentos();
      std::cout << "] ";
    }
    consumir(parenDir, "Esperava fecha parenteses apos argumentos da chamada!");
    funcao_ou_atributo();
  }
  else if (atual.getTipo() == ponto)
  {
    atual = lx.getProximo();
    std::cout << " campo " << atual.getLexema();
    consumir(identificador, "Esperava identificador após ponto!");
    funcao_ou_atributo();
  }
}
void AnalisadorSintatico::argumentos()
{
  do
  {
    expressao();
    if (atual.getTipo() != virgula)
      break;
    else
    {
      atual = lx.getProximo();
      std::cout << ", ";
    }
  } while (true);
}
void AnalisadorSintatico::primario()
{
  switch (atual.getTipo())
  {
  case literalNumerico:
  case literalTexto:
  case verdadeiro:
  case falso:
  case nulo:
  case identificador:
  case eu:
    std::cout << atual.getLexema();
    atual = lx.getProximo();
    break;
  case super:
    atual = lx.getProximo();
    consumir(ponto, "Espera ponto após 'super'.");
    std::cout << "super metodo " << atual.getLexema();
    consumir(identificador, "Espera identificador após ponto");
    break;
  case parenEsq:
    atual = lx.getProximo();
    expressao();
    consumir(parenDir, "Fecha parenteses faltando!");
    break;
  default:
    throw ErroSintatico("Token inesperado!", atual);
  }
}

bool AnalisadorSintatico::noFim() const
{
  return atual.getTipo() == eof;
}

void AnalisadorSintatico::consumir(TipoToken tipo, std::string mensagem)
{
  if (atual.getTipo() != tipo)
    throw ErroSintatico(mensagem, atual);
  atual = lx.getProximo();
}