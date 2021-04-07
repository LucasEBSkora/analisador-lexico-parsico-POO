#include "ErroLexico.hpp"

ErroLexico::ErroLexico(std::string msg, char caractere, unsigned nLinha) : mensagem{msg}, caractere{caractere}, nLinha{nLinha} {}

std::ostream &operator<<(std::ostream &out, const ErroLexico &e)
{
  out << "[Linha " << e.nLinha << "] Erro no caractere '"
      << e.caractere << "': " << e.mensagem;
  return out;
}