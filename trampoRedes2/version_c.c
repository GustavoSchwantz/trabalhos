#include <version_c.h>

int initfs (char * arquivo, int blocos)
{

}

indice_fs_t vopenfs (char * arquivo) 
{

}

indice_arquivo_t vopen (indice_fs_t fs, char * nome,  int acesso, int version)
{

}

int vclose (indice_arquivo_t arquivo)
{

}

uint32_t vread (indice_arquivo_t arquivo, uint32_t tamanho, char *buffer)
{

}

int vwrite (indice_arquivo_t arquivo, uint32_t tamanho, char *buffer)
{

}

int vdelete (indice_arquivo_t arquivo)
{

}

int vseek (indice_arquivo_t arquivo, uint32_t seek)
{

}

time_t vcreation (indice_arquivo_t arquivo, int versao)
{

}

time_t vaccessed (indice_arquivo_t arquivo, int versao)
{

}

time_t vlast_modified (indice_arquivo_t arquivo, int versao)
{

}

int vclosefs (indice_fs_t fs)
{

}

