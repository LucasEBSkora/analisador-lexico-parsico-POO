project('analisador-lexico-sintatico', 'cpp',)

src = [
  'source/main.cpp',
  'source/ProcessadorTexto.cpp',
  'source/Token.cpp',
  'source/AnalisadorLexico.cpp',
  'source/ErroLexico.cpp',
  'source/Erro.cpp',
  'source/AnalisadorSintatico.cpp',
  'source/ErroSintatico.cpp',
]

incdir = include_directories('include')

executable('lxpr', src, include_directories: incdir)