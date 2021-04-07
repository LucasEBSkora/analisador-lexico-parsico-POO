funcao multiplicar(operandos) {
  se (operandos == nulo) retornar (n(0));

  _openOtherMultiplications(operandos);

  seja divisionNegatives = falso;

  seja i = 0;
  enquanto (i < operandos.length) {
    seja divisions = Lista();

    {
      seja i = 0;
      enquanto(i < operandos.length) {
        
      seja _op = extractFromNegative(operandos.pos(i));
      se (Tipo(_op.first) == Division) {
        operandos.removeAt(i);

        se (_op.second) divisionNegatives = !divisionNegatives;

        divisions.add(Divisao.de(_op.first));
      } senao
        i = i + 1;
      }
    }
    

    seja (divisions.isNotEmpty) {
      seja nums = Lista();
      seja dens = Lista();

      {
        seja i = 0;
        enquanto (i < divisions.length()) {
          seja f = divisions.em(i)
          seja numerator = f.numerator;
          se (Tipo(numerator) == Multiplication) {
            nums.addAll(numerator.operands);
          } senao nums.add(numerator);

          seja denominator = f.denominator;
          se (Tipo(denominator) == Multiplication) {
            dens.addAll(denominator.operands);
          } senao {
            dens.add(denominator);
          }

          i = i + 1;
        }
      }

      retornar divide(nums, dens);
    }
    i = i + 1;
  }

  seja negativeForNumbers = _multiplyNumbers(operands);
  seja negativeOthers = _consolidateNegatives(operands);

  seja _negative = xor(negativeForNumbers, negativeOthers);
  _negative = xor(_negative, divisionNegatives);

  _createExponents(operands);

  seja _mul;

  se (operands.isEmpty) {
    retornar n(0);
  } senao se (operands.length == 1) {
    _mul = operands.at(0);
  } senao {
    _mul = Multiplication(operands);
  }

  se (_negative) retornar negative(_mul);
  senao retornar _mul; 
}

classe Multiplication : BSFunction {
  operands;

  Multiplication(operands, params) {
    eu.operands = operands;
    params = params;
  }

  evaluate(p) {
    retornar multiply(f.evaluate(p));
  }

  copy(params) {
    retornar Multiplication(operands, params);
  }

  getdefaultParameters() {
    retornar SplayTreeSet.from(operands.parameters);
  }  

  getApprox() 
  {
    retornar multiply(operands.approx]);
  }

  accept(FunctionVisitor visitor) {
    retornar visitor.visitMultiplication(this);
  } 
}

funcao _openOtherMultiplications(operands) {
  seja i = 0;
  enquanto (i < operands.length) {
    seja _op = extractFromNegative(operands.em(i));

    se (Tipo(_op.first) == Multiplication) {
      operands.removeAt(i);
      seja m = Multiplication(_op.first);
      operands.insertAll(i, m.operands);
      se (_op.second) operands.add(n(-1));
    } senao
      i = i + 1;
  }
}

funcao _multiplyNumbers(operands) {
  seja number = 1.0;
  seja negative = falso;

  seja namedNumbers = HashMap();

  seja i = 0;
  enquanto (i < operands.length) {

    seja _op = extractFromNegative(operands.em(i));

    se (_op.first != nulo) {
      operands.removeAt(i);
      seja n = Number(_op.first);
      se (!n.isNamed) {
        se (_op.second == -1) 
          number = -number * n.value;
        senao 
          number = number * n.value;
      } senao {

        se (!namedNumbers.containsKey(n.name)) {
          namedNumbers.em(n.name) = Pair(n.absvalue, 0);
        }
        namedNumbe.em(n.name).second = namedNumbe.em(n.name).second + 1;

        se (_op.second) number = -number;
      }
    } senao
      i = i + 1;
  }

  se (number == 0)
    operands.clear();
  senao {
    seja numbers = List();
    se (number < 0) negative = verdadeiro;
    se (number.abs() != 1) numbers.add(n(number.abs()));
    
    {
      seja i = 0;
      enquanto(i < namedNumbers.keys.length) {
        seja key = namedNumbers.keys.em(i);
        seja pair = namedNumbers.em(key);
        se (pair.second != 0) {
          numbers.add(xor(namedNumber(pair.first, key), n(pair.second)));
        }
        i = i + 1;
      }
    }

    operands.insertAll(0, numbers);

    se (number.abs() == 1 & operands.isEmpty) operands.add(n(1));
  }

  retornar negative;
}

funcao _consolidateNegatives(operands) {
  seja _negative = falso;

  funcao mapear(BSFunction f) {
    seja _op = extractFromNegative(f);
    se (_op.second) _negative = !_negative;
    retornar _op.first;
  }

  seja newOperands = operands.map(mapear).toList();

  operands.clear();
  operands.insertAll(0, newOperands);

  retornar _negative;
}

funcao _createExponents(operands) {
  seja i = 0;
  enquanto(i < operands.length) {
    seja f = operands.em();

    seja base;
    seja exponent;

    se (Tipo(f) == Exponentiation) {
      base = f.base;
      exponent = f.exponent;
    } senao {
      base = f;
      exponent = n(1);
    }

    seja j =  i + 1;
    enquanto(j < operands.length) {
      seja g = operands.em(j);

      se (Tipo(g) == Exponentiation) {
        se (g.base == base) {
          operands.removeAt(j);
          exponent = exponent + g.exponent;
        }
      } senao {
        se (g == base) {
          operands.removeAt(j);
          exponent = exponent + n(1);
        }
      }

      j = j + 1;
    }

  
    se (exponent != n(1)) {
      operands.removeAt(i);
      operands.insert(i, xor(base, exponent));
    }
    
    i = i + 1;
  }
}
