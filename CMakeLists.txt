cmake_minimum_required(VERSION 3.24)
project(trabalho_final C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(trabalho_final
        main.c rubro_negra/rubro_negra.c rubro_negra/rubro_negra.h rubro_negra_teste/rubro_negra_teste.c rubro_negra_teste/rubro_negra_teste.h rubro_negra_teste/transformacao_teste.c rubro_negra_teste/util.c rubro_negra_teste/util.h rubro_negra_teste/criacao_teste.c)
