#include "stdafx.h"
#include "NoPilha.h"

NoPilha::NoPilha()
{
}

NoPilha::NoPilha(No* valor, int indicacao, char* funcao)
{
	this->valor = valor;
	this->indicacao = indicacao;
	this->funcao = funcao;
}

No* NoPilha::getValor()
{
	return this->valor;
}

char * NoPilha::getFuncao()
{
	return funcao;
}

void NoPilha::setValor(No* valor)
{
	this->valor = valor;
}

void NoPilha::setFuncao(char * funcao)
{
	this->funcao = funcao;
}

NoPilha * NoPilha::getAnterior()
{
	return this->anterior;
}

void NoPilha::setAnterior(NoPilha * anterior)
{
	this->anterior = anterior;
}

NoPilha::~NoPilha()
{
}
