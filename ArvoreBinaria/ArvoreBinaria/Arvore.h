#pragma once
#include <iostream>
#include "No.h"

class Arvore
{
public:
	Arvore();
	~Arvore();
	
	void inclusaoOrdenada(int);

	// para exclus�o
	void exclusaoOrdenada(int);
	void exclusaoOrdenada(No*);

	// to String => para printar na tela
	//friend ostream& operator<< (ostream& saida, const Arvore a);
	std::string toString();
	void adicionarAString(No*);
	
	// getters
	No* getRaiz();
	No* getAtual();

	// setters
	void setRaiz(No*);
	void setAtual(No*);
	
	// coisinhas �teis
	bool estaVazia();
	void reordenar(No*);
	void posicionarNoPrimeiro();
	No* procurarNo(int);
	void balanceada(No*);
	//No* balanceadaRecursao(No*, int);
	No* contQtdNosMaior(No*);
	No* contQtdNosMenor(No*);
	void rotacionarParaEsq(No*);
	void rotacionarMenorDosMaioresPai(No*);
	void rotacionarParaDir(No*);
	void rotacionarMaiorDosMenoresPai(No*);

	// N�o uso para nada mas pode ser que algum dia seja �til
	No* maiorDeTodos();
	No* menorDeTodos();

protected:
	No* raiz;
	No* atual;
	int niveis;
	int quantidadeNos;
	std::string arvoreString;
	No* indesejado;

};

