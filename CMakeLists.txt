cmake_minimum_required(VERSION 3.22)
project(trabalho_final C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")

include_directories(.)

add_executable(trabalho_final
        main.c
        rubro_negra/rubro_negra.c
        rubro_negra/rubro_negra.h
        rubro_negra/testes/rubro_negra_teste.c
        rubro_negra/testes/rubro_negra_teste.h
        rubro_negra/testes/balanceamento_teste.c
        rubro_negra/testes/util.c
        rubro_negra/testes/util.h
        rubro_negra/testes/criacao_teste.c
        rubro_negra/balanceamento.c
        rubro_negra/fila/fila.h
        rubro_negra/fila/fila.c
        rubro_negra/testes/fila_teste.c
        rubro_negra/fila_rubro_negra.c
        rubro_negra/fila_rubro_negra.h)
