// ArvoreBinaria.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Arvore.h"
#include "No.h"

Arvore a;

void opcao_Inserir() {
	char* resposta = "";
	int valor;
	printf("\n Valor que deseja inserir: ");
	std::cin >> valor;
	
	No* este;
	bool naArvore = false;

	if (!a.estaVazia()) {
		a.posicionarNoPrimeiro();
		este = a.procurarNo(valor);
		if (este != nullptr && este->getValor() == valor) { // encontrou o nó => foi incluído
			std::cout << "\n Valor ja presente na arvore \n\n\n";
			naArvore = true;
		}
	}

	if (!naArvore) {
		a.inclusaoOrdenada(valor); 
		a.balanceada(a.getRaiz());
		a.balanceada(a.getRaiz());
		a.posicionarNoPrimeiro();
		este = a.procurarNo(valor);
		if (este->getValor() == valor) // encontrou o nó => foi incluído
			std::cout << "\n No incluido com sucesso \n\n\n";
	}
}

void opcao_Excluir() {
	char* resposta = "";
	int valor;
	printf("\n Valor que deseja excluir: ");
	std::cin >> valor;

	No* este;
	bool naArvore = true;

	if (!a.estaVazia()) {
		a.posicionarNoPrimeiro();
		este = a.procurarNo(valor);
		if (este == nullptr) { // não encontrou o nó =~> não existe na árvore
			std::cout << "\n Valor nao presente na arvore \n\n\n";
			naArvore = false;
		}
	}
	else if (a.estaVazia()) {
		std::cout << "\n Valor nao presente na arvore \n\n\n";
		naArvore = false;
	}

	if (naArvore) {
		a.exclusaoOrdenada(valor);
		if (!a.estaVazia()) {
			a.balanceada(a.getRaiz());
			a.balanceada(a.getRaiz());
			a.balanceada(a.getRaiz());
			a.posicionarNoPrimeiro();
			este = a.procurarNo(valor);
			if (este == nullptr) // encontrou o nó => foi incluído
				std::cout << "\n No excluido com sucesso \n\n\n";
		}
		else if (a.estaVazia())
			std::cout << "\n No excluido com sucesso \n\n\n";
	}
}

void opcao_Visualizar() {
	std::cout << "\n Sua arvore: " << a.toString().c_str() << "\n\n\n" << std::endl;
}

int main()
{
	a = *(new Arvore());
	int opcao = 0;
	char* resposta = (char*)malloc(sizeof(char)*2);
	while (1) {
		printf("Selecione uma opcao: \n");
		printf("1 - Inserir na arvore\n");
		printf("2 - Excluir da arvore\n");
		printf("3 - Visualizar arvore\n");

		std::cin >> resposta;

		if (!strcmp(resposta, "1"))
			opcao_Inserir();
		else if (!strcmp(resposta, "2"))
			opcao_Excluir();
		else if (!strcmp(resposta, "3"))
			opcao_Visualizar();
 	}

    return 0;
}

