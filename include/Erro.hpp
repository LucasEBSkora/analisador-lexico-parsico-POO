#ifndef _ERRO__HPP_
#define _ERRO__HPP_

#include <string>
#include <ostream>

class Erro
{
protected:
  std::string mensagem;

public:
  Erro(std::string msg);
  virtual ~Erro();
  virtual std::string comoString() const = 0;
};

std::ostream &operator<<(std::ostream &out, const Erro &e);



#endif