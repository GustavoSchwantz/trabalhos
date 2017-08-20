#include <stdio.h>
#include <stdint.h>
#include "roteador.h"
#include "simpletest.h"
#include <assert.h>

uint32_t iptoint (int a, int b, int c, int d);

/* testa o caso em que ha varios pacotes que nao dao match com nenhum endereco */
void azarados ();
/* verifica se o resultado permanece igual msm alterando a ordem da tabela */
void prefixo_em_comum ();
/* testa a situacao de enviar um pacote para um mesmo endereco */
void pensador_profundo ();


int main (int argc, char const *argv[])
{
	DESCRIBE("Testes adicionais do simulador de roteador CIDR");


	azarados ();
	prefixo_em_comum ();
	pensador_profundo ();
	GRADEME(); 

	if (grade==maxgrade)	
		return 0;
	else return grade;

	return 0;
}

uint32_t iptoint (int a, int b, int c, int d){
	return (uint32_t) (a<<24)+(b<<16)+(c<<8)+d;
}

void azarados ()
{
	entrada rotas[5] = { iptoint(192,168,100,42), 8, 1,
						 iptoint (193,169,100,42), 16, 2,
						 iptoint(99,100,1,1), 23, 3,
						 iptoint (50,0,0,2), 31, 4,
						 iptoint(193,168,100,41), 31, 5 };

	uint32_t pacs[5] = { iptoint(255,0,0,0), iptoint(193,255,255,255), iptoint(193,168,100,42),
	    iptoint(99,100,2,1), iptoint(50,0,0,1) };
	uint32_t * result;

	WHEN("Tenho cinco rotas diferentes");
	IF("Envio cinco pacotes que nao batem com elas");

	result = roteamento(rotas, 5, pacs, 5, 5);
	assert(result);
	THEN("Todos os pacotes devem ser descartados");
	isEqual(result[0], 5, 1); 

	THEN("Nao deve haver pacote algum em nenhum enlace");
	for(int i=1; i<=5; i++){
		isEqual(result[i], 0, 1);
	}
}

void prefixo_em_comum () 
{
	entrada rotas0[4] = { iptoint(192,168,100,0), 8, 1,
						 iptoint (192,168,100,2), 16, 2,
						 iptoint(192,168,100,4), 24, 3,
						 iptoint(192,168,100,8), 27, 4 };


    /* msm tabela q a anterior, so q com a ordem dos prefixos trocadas */
	entrada rotas1[4] = { iptoint(192,168,100,0), 24, 1,
						 iptoint (192,168,100,2), 27, 2,
						 iptoint(192,168,100,4), 8, 3,
						 iptoint(192,168,100,8), 16, 4 };					 

	uint32_t pacs[5] = { iptoint(192,168,100,2), iptoint(192,168,100,3), iptoint(192,168,100,7),
	    iptoint(192,168,100,11), iptoint(192,168,100,13) };
	uint32_t *result0, *result1;

	WHEN("Tenho duas tabelas com enderecos iguais de direntes prefixos");
	IF("Envio cinco pacotes para a rota de maior prefixo");

	result0 = roteamento (rotas0, 4, pacs, 5, 4);
	result1 = roteamento (rotas1, 4, pacs, 5, 4);
	assert(result0);
	assert(result1);
	THEN("Nenhum pacote deve ser descartado em ambos os casos");
	isEqual(result0[0], 0, 1);
	isEqual(result1[0], 0, 1); 

	THEN("No primeiro caso, todos os pacotes vao para o enlace 4");
	isEqual(result0[4], 5, 1);

	THEN("No segundo caso, todos os pacotes vao para o enlace 2");
	isEqual(result1[2], 5, 1);
}

void pensador_profundo ()
{
	entrada rotas[3] = { iptoint(19,5,0,0), 8, 1,
						 iptoint (192,168,101,0), 22, 2,
						 iptoint(192,168,100,0), 23, 3 };

	uint32_t pacotes[42];

	for (int i=0; i<21; i++){
		pacotes[i] = iptoint(192,168,100,235 + i);
	}		

    for (int i=21; i<42; i++){
		pacotes[i] = iptoint(192,168,101,214 + i);
	}

    WHEN("Envio 42 pacotes");
	IF("Se eu enviar todos para um mesmo destino");
	THEN("Eu devo ter 42 pacotes em um enlace");

	uint32_t * result;	

	result = roteamento(rotas, 3, pacotes, 42, 3);
	assert(result);

	isEqual(result[3], 42, 1);		 
}