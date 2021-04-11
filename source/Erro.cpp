#include "Erro.hpp"

Erro::Erro(std::string msg) : mensagem{msg} {}

Erro::~Erro() {}

std::ostream &operator<<(std::ostream &out, const Erro &e)
{
  out << e.comoString();
  return out;
}