#ifndef _PROCESSADOR_TEXTO_HPP_
#define _PROCESSADOR_TEXTO_HPP_

#include <fstream>


class ProcessadorTexto
{
private:
  std::ifstream fonte;

public:
  ProcessadorTexto(const char *caminho);
  int executar();
};

#endif