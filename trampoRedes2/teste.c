#include "version_s.h" 

void initfs_test ()
{
	puts ("Testes com a initfs");

	puts ("Quando o numero de blocos for insuficiente");
	puts ("a funcao deve retornar FALHA");

	if ( initfs ("very_small_fs", 10) == FALHA)
		puts ("OK!");
	else
		puts ("DEU RUIM!");

	puts ("Quando eu tento criar um SAs com 500 blocos");
        puts ("a funcao deve retornar SUCESSO");

	if ( initfs ("some_fs", 500) == SUCESSO)
	       	puts ("OK!");
        else
	        puts ("DEU RUIM!");
        
}

void vopenfs_test ()
{

}

void vopen_test ()
{

}

int main ()
{
        puts ("Testes do Sistema de Arquivos Versionado");
        
        initfs_test ();
        // vopenfs_test ();
	// vopen_test ();

	return 0;
}

