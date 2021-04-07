#include "ProcessadorTexto.hpp"

#include <iostream>

int main(int argc, char *argv[]) {
  if (argc == 2) {
    return ProcessadorTexto(argv[1]).executar();
  } else return -1;
}