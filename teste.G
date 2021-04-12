funcao _consolidateNegatives(operands) {
  seja _negative = falso;

  funcao mapear (f, d) {
    seja _op = extractFromNegative(f);
    se (_op.second) _negative = !_negative;
    retornar _op.first;
  }

  seja newOperands = operands.map(mapear).toList();

  operands.clear();
  operands.insertAll(0, newOperands);

  retornar _negative;
}