#include "ErroLexico.hpp"

#include <sstream>

ErroLexico::ErroLexico(std::string msg, char caractere, unsigned nLinha) : Erro(msg), caractere{caractere}, nLinha{nLinha} {}

std::string ErroLexico::comoString() const
{
  std::stringstream ss;
  ss << "[Linha " << nLinha << "] Erro no caractere '"
     << caractere << "': " << mensagem;
  return ss.str();
}
