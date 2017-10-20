#include "stdafx.h"
#include "No.h"

No::No()
{	

}

No* No::getPai()
{
	return pai;
}

No* No::getFilhoMenor()
{
	return filhoMenor;
}

int No::getValor()
{
	return valor;
}

int No::getNivel()
{
	return nivel;
}

No* No::getFilhoMaior()
{
	return filhoMaior;
}

void No::setPai(No* novoPai)
{
	pai = novoPai;
}

void No::setValor(int novoValor)
{
	valor = novoValor;
}

void No::setNivel(int novoNivel)
{
	nivel = novoNivel;
}

void No::setFilhoMenor(No* novoMenor) 
{
	filhoMenor = novoMenor;
}

void No::setFilhoMaior(No* novoMaior)
{
	filhoMaior = novoMaior;
}

void No::deleteFilhoMenor()
{
	filhoMenor = nullptr;
}

void No::deleteFilhoMaior()
{
	filhoMaior = nullptr;
}

No::~No()
{
}
