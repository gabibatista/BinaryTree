#pragma once
#include "No.h"
class NoPilha
{
public:
	int indicacao;
	NoPilha();
	NoPilha(No*, int);
	No* getValor();
	void setValor(No*);
	NoPilha* getAnterior();
	void setAnterior(NoPilha*);
	~NoPilha();

private:
	No* valor;
	NoPilha* anterior;

};