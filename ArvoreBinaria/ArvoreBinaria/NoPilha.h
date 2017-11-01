#pragma once
#include "No.h"
class NoPilha
{
public:
	int indicacao;
	char* funcao;

	NoPilha();
	NoPilha(No*, int, char*);

	No* getValor();
	void setValor(No*);

	char* getFuncao();
	void setFuncao(char*);

	NoPilha* getAnterior();
	void setAnterior(NoPilha*);

	~NoPilha();

private:
	No* valor;
	NoPilha* anterior;

};