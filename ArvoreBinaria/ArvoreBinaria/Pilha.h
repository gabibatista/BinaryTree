#pragma once
#include <iostream>
#include "NoPilha.h"

class Pilha
{
public:
	Pilha();
	NoPilha* getTopo();
	void setTopo(NoPilha*);
	void empilha(NoPilha*);
	NoPilha* desempilha();
	bool estaVazia();
	std::string toString();
	~Pilha();

private:
	NoPilha* topo;
	std::string pilhaString;
	int qtdNos;

};