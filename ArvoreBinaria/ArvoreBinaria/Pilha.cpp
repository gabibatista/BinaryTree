#include "stdafx.h"
#include "Pilha.h"
#include "NoPilha.h"

Pilha::Pilha()
{
}


Pilha::~Pilha()
{
}

NoPilha * Pilha::getTopo()
{
	return this->topo;
}

void Pilha::setTopo(NoPilha * topo)
{
	this->topo = topo;
}

void Pilha::empilha(NoPilha* no)
{
	if (!this->estaVazia())
		no->setAnterior(this->topo);

	this->topo = no;
	qtdNos++;
}

NoPilha* Pilha::desempilha()
{
	NoPilha* retorno;
	
	if (!this->estaVazia()) {
		retorno = this->topo;
		this->topo = this->topo->getAnterior();
		qtdNos--;
	}

	return retorno;
}

bool Pilha::estaVazia()
{
	if (this->topo == nullptr)
		return true;

	return false;
}

std::string Pilha::toString()
{
	NoPilha* atual = topo;
	char pontChar[6];
	pilhaString = "";

	while (atual != nullptr) {
		_itoa_s(atual->getValor(), pontChar, 10);
		pilhaString += pontChar;
		atual = atual->getAnterior();
		if (atual != nullptr)
			pilhaString += " | ";
	}

	return pilhaString;
}
