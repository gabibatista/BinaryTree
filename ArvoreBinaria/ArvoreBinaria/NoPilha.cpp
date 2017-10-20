#include "stdafx.h"
#include "NoPilha.h"

NoPilha::NoPilha()
{
}

NoPilha::NoPilha(No* valor, int indicacao)
{
	this->valor = valor;
	this->indicacao = indicacao;
}

No* NoPilha::getValor()
{
	return this->valor;
}

void NoPilha::setValor(No* valor)
{
	this->valor = valor;
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
