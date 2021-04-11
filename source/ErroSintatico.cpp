#include "ErroSintatico.hpp"

#include <sstream>

ErroSintatico::ErroSintatico(std::string msg, Token token) : Erro(msg), token{token} {}

std::string ErroSintatico::comoString() const
{
  std::stringstream ss;
  ss << "[Linha " << token.getNLinha() << "] Erro em '"
      << token.getLexema() << "': " << mensagem;
  return ss.str();
}