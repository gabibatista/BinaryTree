#include "stdafx.h"
#include "Arvore.h"
#include "No.h"
#include "Pilha.h"
#include <stdexcept>
#include <math.h> 

Arvore::Arvore()
{

}

int qtdNosMenor = 0, qtdNosMaior = 0;
Pilha p = *(new Pilha());
//char* arvoreString = (char*)malloc(sizeof(char)*100);

void Arvore::inclusaoOrdenada(int valor) {
		// ver se está vazio
	bool novoEhRaiz = false;
	this->atual = this->raiz;

	No* novo = new No();
	novo->setValor(valor);
	novo->setFilhoMaior(nullptr);
	novo->setFilhoMenor(nullptr);

	if (estaVazia()){
		novo->setNivel(0);
		novoEhRaiz = true;
		niveis++;
		quantidadeNos++;
	}
	else if (!procurarNo(valor)) { // se ainda não existe o valor procurado => atual == onde deve ser inserido
		// verificar se isso não desbalanceará a árvore
		// caso desbalanceie, rebalanceie a árvore

		bool maior;

		No* pai = atual;

		while (atual != nullptr) {
			if (atual->getValor() > novo->getValor()) { // se o novo é menor que o atual
				pai = atual;
				maior = false;
				atual = atual->getFilhoMenor();
			}
			else { // se o novo é maior que o atual
				pai = atual;
				maior = true;
				atual = atual->getFilhoMaior();
			}
		}

		novo->setPai(pai);
		novo->setNivel(pai->getNivel() + 1);

		if (atual == nullptr && !maior) // se novo é menor que o pai
			pai->setFilhoMenor(novo);
		else if (atual == nullptr && maior) // se novo é maior que o pai
			pai->setFilhoMaior(novo);

		quantidadeNos++; //a quantidade de nos é incrementada
		toString(); // calcula a quantidade de niveis
		balanceada(raiz);
	}

	if (novoEhRaiz)
		raiz = novo;
}

No* maisBaixo;

 void Arvore::balanceada(No* esseNo) {
 balanceada_inicio: if (esseNo->getNivel() < niveis - 1) { // se o nivel do atual é menor que o último nível -> até o penúltimo
		if (esseNo->getFilhoMenor() != nullptr) { // se não for nulo, atual recebe o seu filho menor
			//balanceada(esseNo->getFilhoMenor()); // recursão-> um nível abaixo na árvore
			p.empilha(new NoPilha(esseNo, 1, "balanceada"));
			esseNo = esseNo->getFilhoMenor();
			goto balanceada_inicio;
		local1:
			esseNo = p.desempilha()->getValor();

			if (esseNo->getFilhoMaior() != nullptr) { // se não for nulo, atual recebe o seu filho maior
					//balanceada(esseNo->getFilhoMaior()); // recursão-> um nível abaixo na árvore
					p.empilha(new NoPilha(esseNo, 2, "balanceada"));
					esseNo = esseNo->getFilhoMaior();
					goto balanceada_inicio;
				local2:
					esseNo = p.desempilha()->getValor();
			}

			if (esseNo->getFilhoMenor() != nullptr && esseNo->getFilhoMenor()->getFilhoMenor() != nullptr && esseNo->getFilhoMaior() == nullptr) { // se o filho menor tem um filho menor
				rotacionarParaDir(esseNo->getFilhoMenor());
			}

			else if (esseNo->getFilhoMenor() != nullptr && esseNo->getFilhoMenor()->getFilhoMaior() != nullptr && esseNo->getFilhoMaior() == nullptr){ // se o filho menor não tem um filho menor, mas tem um maior
				rotacionarMaiorDosMenoresPai(esseNo);
			}

			else if (esseNo->getFilhoMaior() == nullptr && esseNo->getFilhoMenor() == nullptr){ // se é folha => menor dos maiores com o pai deste
				if (esseNo->getPai() != nullptr) {
					if (esseNo->getValor() < esseNo->getPai()->getValor()) // se esseNo é filhoMenor
						rotacionarMaiorDosMenoresPai(esseNo->getPai()); ////////////////////AQUI ESTÁ O PROBLEMA
					else // se esseNo é filhoMaior
						rotacionarMenorDosMaioresPai(esseNo->getPai());
				}
			}
		}
		else if (esseNo->getFilhoMaior() != nullptr) { // se não tiver o filho menor -> desbalanceado
				// se tem o filho maior
				if (esseNo->getFilhoMaior()->getFilhoMaior() != nullptr && esseNo->getFilhoMaior()->getFilhoMenor() == nullptr) { // se o filho maior tem um filho maior
					rotacionarParaEsq(esseNo->getFilhoMaior()); //rotaciona para a esquerda
				}
				else if (esseNo->getFilhoMaior()->getFilhoMenor() != nullptr) { // se o filho maior não tem um filho maior, mas tem um menor
					rotacionarMenorDosMaioresPai(esseNo);
				}
				else if (esseNo->getFilhoMaior()->getNivel() < niveis - 2){ // se é folha => menor dos maiores com o pai deste e se se o nivel do atual é menor que o último nível -> até o penúltimo
					if (esseNo->getValor() < esseNo->getPai()->getValor()) // se esseNo é filhoMenor
						rotacionarMenorDosMaioresPai(esseNo->getPai());
					else // se esseNo é filhoMaior
						rotacionarMaiorDosMenoresPai(esseNo->getPai());
				}
		}

		qtdNosMaior = 0;
		qtdNosMenor = 0;
		maisBaixo = esseNo;
		No* maisBaixoMaior = contQtdNosMaior(esseNo->getFilhoMaior());
		maisBaixo = esseNo;
		No* maisBaixoMenor = contQtdNosMenor(esseNo->getFilhoMenor());
		
		int cont = 0;
		for (int i = niveis - 2; i >= 0; i--)
			cont = cont + (pow( 2, i));

		if (qtdNosMaior > qtdNosMenor + 1 && maisBaixoMaior->getNivel() > maisBaixoMenor->getNivel() && quantidadeNos - 1 < cont) //&& maisBaixoMaior->getNivel() > niveis - 1 //&& quantidadeNos < cont
			rotacionarMenorDosMaioresPai(esseNo);
		else if (qtdNosMaior + 1 < qtdNosMenor && maisBaixoMaior->getNivel() < maisBaixoMenor->getNivel() && quantidadeNos - 1 < cont)//maior dos menores-> raiz // && maisBaixoMenor->getNivel() > niveis - 1  // 
			rotacionarMaiorDosMenoresPai(esseNo);

		if (!p.estaVazia()) {
			if (p.getTopo()->indicacao == 1)
				goto local1;
			else if (p.getTopo()->indicacao == 2)
				goto local2;
		}

		if (!p.estaVazia() && (p.getTopo()->getFuncao() == "balanceada")) {
			esseNo = p.desempilha()->getValor();
			goto balanceada_inicio;
		}
	}
}

No* Arvore::contQtdNosMaior(No* raizAtual) {
contQtdNosMaior_inicio: 
	if (raizAtual != nullptr) {
		qtdNosMaior++;

		if (raizAtual->getFilhoMenor() != nullptr) {
			//contQtdNosMaior(raizAtual->getFilhoMenor());
			p.empilha(new NoPilha(raizAtual, 3, "contQtdNosMaior"));
			raizAtual = raizAtual->getFilhoMenor();
			goto contQtdNosMaior_inicio;

		local3:
			raizAtual = p.desempilha()->getValor();
		}

		if (raizAtual->getFilhoMaior() != nullptr) {
			//contQtdNosMaior(raizAtual->getFilhoMaior());
			p.empilha(new NoPilha(raizAtual, 4, "contQtdNosMaior"));
			raizAtual = raizAtual->getFilhoMaior();
			goto contQtdNosMaior_inicio;

		local4:
			raizAtual = p.desempilha()->getValor();
		}

		if (raizAtual->getNivel() > maisBaixo->getNivel()) 
			maisBaixo = raizAtual;
	}

	if (!p.estaVazia()) {
		if (p.getTopo()->indicacao == 3)
			goto local3;
		else if (p.getTopo()->indicacao == 4)
			goto local4;
	}

	if (!p.estaVazia() && (p.getTopo()->getFuncao() == "contQtdNosMaior")) {
		raizAtual = p.desempilha()->getValor();
		goto contQtdNosMaior_inicio;
	}

	return maisBaixo;
}

No* Arvore::contQtdNosMenor(No* raizAtual) {
 contQtdNosMenor_inicio:
	if (raizAtual != nullptr) {
		qtdNosMenor++;

		if (raizAtual->getFilhoMenor() != nullptr) {
			//contQtdNosMenor(raizAtual->getFilhoMenor());
			p.empilha(new NoPilha(raizAtual, 5, "contQtdNosMenor"));
			raizAtual = raizAtual->getFilhoMenor();
			goto contQtdNosMenor_inicio;

		local5:
			raizAtual = p.desempilha()->getValor();
		}

		if (raizAtual->getFilhoMaior() != nullptr) {
			//contQtdNosMenor(raizAtual->getFilhoMaior());
			p.empilha(new NoPilha(raizAtual, 6, "contQtdNosMenor"));
			raizAtual = raizAtual->getFilhoMaior();
			goto contQtdNosMenor_inicio;

		local6:
			raizAtual = p.desempilha()->getValor();
		}

		if (raizAtual->getNivel() > maisBaixo->getNivel())
			maisBaixo = raizAtual;
	}

	if (!p.estaVazia()) {
		if (p.getTopo()->indicacao == 5)
			goto local5;
		else if (p.getTopo()->indicacao == 6)
			goto local6;
	}

	if (!p.estaVazia() && (p.getTopo()->getFuncao() == "contQtdNosMenor")) {
		raizAtual = p.desempilha()->getValor();
		goto contQtdNosMenor_inicio;
	}

	return maisBaixo;
}

/*No* Arvore::balanceadaRecursao(No* raizAtual, int niveisArvoreAtual) {
	for (int i = 0; i < niveisArvoreAtual - 2; i++) { // enquanto estiver abaixo do penúltimo
		if (contQtdNosMaior(raizAtual) > contQtdNosMenor(raizAtual)){ // menor dos maiores-> raiz
			rotacionarMenorDosMaioresPai(raizAtual);
		}
		else if (contQtdNosMenor(raizAtual) > contQtdNosMaior(raizAtual)) {//maior dos menores-> raiz
			rotacionarMaiorDosMenoresPai(raizAtual);
		}
		else if (raizAtual->getPai() != nullptr) {
			balanceadaRecursao(raizAtual->getPai(), niveisArvoreAtual + 1);
		}
	}

	return nullptr;
}*/

void Arvore::rotacionarMaiorDosMenoresPai(No* antigoPai) {
	No* paiCerto;
	No* auxi = antigoPai->getFilhoMenor();

	No* aux = new No();
	aux->setNivel(antigoPai->getNivel() + 1);
	aux->setPai(antigoPai);
	aux->setValor(antigoPai->getValor()); // aux terá o valor da raiz antiga
	aux->setFilhoMaior(nullptr);
	aux->setFilhoMenor(nullptr);

	if (antigoPai->getFilhoMaior() != nullptr) {
		paiCerto = antigoPai->getFilhoMaior();
		//if (aux->getValor() > antigoPai->getFilhoMaior()->getValor()) // se é maior que o filho maior -> filho maior vira filho menor deste
		//	aux->setFilhoMenor(antigoPai->getFilhoMaior());
		//else  // se é menor que o filho maior -> filho maior vira filho maior deste
		//	aux->setFilhoMaior(antigoPai->getFilhoMaior());

		//antigoPai->getFilhoMaior()->setNivel(aux->getNivel() + 1);
		//antigoPai->getFilhoMaior()->setPai(aux);
		//antigoPai->setFilhoMaior(aux);
		while (paiCerto->getFilhoMenor())
			paiCerto = paiCerto->getFilhoMenor();

		paiCerto->setFilhoMenor(aux);
		aux->setPai(paiCerto);
		aux->setNivel(paiCerto->getNivel() + 1);
	}
	else
		antigoPai->setFilhoMaior(aux);

	if (auxi != nullptr) {
		while (auxi->getFilhoMaior() != nullptr)
			auxi = auxi->getFilhoMaior();

		antigoPai->setValor(auxi->getValor()); // o pai fica com o valor do maior dos menores

		exclusaoOrdenada(auxi);
	}
	//antigoPai->getFilhoMaior()->deleteFilhoMenor();

/*	if (antigoPai->getValor() == raiz->getValor()) {
		antigoPai->getPai()->setPai(nullptr);
		raiz = antigoPai->getPai();
	}*/
}

void Arvore::rotacionarParaDir(No* novaRaiz) {
	No* aux = new No();
	aux->setNivel(novaRaiz->getNivel());
	aux->setPai(novaRaiz->getPai());
	aux->setValor(novaRaiz->getPai()->getValor()); // aux terá o valor da raiz antiga
	aux->setFilhoMaior(nullptr);
	aux->setFilhoMenor(nullptr);

	novaRaiz->getPai()->setFilhoMaior(aux); // o filho maior do pai é o aux -> antigo pai

	novaRaiz->getPai()->setValor(novaRaiz->getValor());
	novaRaiz->setValor(novaRaiz->getFilhoMenor()->getValor());
	
	if (novaRaiz->getFilhoMenor()->getFilhoMenor() != nullptr)
		novaRaiz->setFilhoMenor(novaRaiz->getFilhoMenor()->getFilhoMenor());
	else
		novaRaiz->setFilhoMenor(novaRaiz->getFilhoMenor()->getFilhoMaior());

	if (raiz->getValor() == novaRaiz->getValor()) {
		novaRaiz->setPai(nullptr);
		raiz = novaRaiz;
	}

	toString(); //recalcular niveis
}

void Arvore::rotacionarMenorDosMaioresPai(No* antigoPai) {
	No* paiCerto;
	No* auxiliar = antigoPai->getFilhoMaior();

	No* aux = new No();
	aux->setNivel(antigoPai->getNivel() + 1);
	aux->setPai(antigoPai);
	aux->setValor(antigoPai->getValor()); // aux terá o valor da raiz antiga
	aux->setFilhoMaior(nullptr);
	aux->setFilhoMenor(nullptr);

	if (antigoPai->getFilhoMenor() != nullptr) {
		paiCerto = antigoPai->getFilhoMenor();
		//antigoPai->getFilhoMenor()->setPai(aux);
		//antigoPai->getFilhoMenor()->setNivel(antigoPai->getFilhoMenor()->getNivel() + 1);

		//if (antigoPai->getFilhoMenor()->getValor() < aux->getValor())
		//	aux->setFilhoMenor(antigoPai->getFilhoMenor());
		//else if (antigoPai->getFilhoMenor()->getValor() > aux->getValor())
		//	aux->setFilhoMaior(antigoPai->getFilhoMenor());
		while (paiCerto->getFilhoMaior() != nullptr)
			paiCerto = paiCerto->getFilhoMaior();

		paiCerto->setFilhoMaior(aux);
		aux->setPai(paiCerto);
		aux->setNivel(paiCerto->getNivel() + 1);
	}
	else {
		antigoPai->setFilhoMenor(aux);
	}

	if (auxiliar != nullptr) {
		while (auxiliar->getFilhoMenor() != nullptr)
			auxiliar = auxiliar->getFilhoMenor();

		antigoPai->setValor(auxiliar->getValor()); // o pai fica com o valor do menor dos maiores
		posicionarNoPrimeiro();
		exclusaoOrdenada(auxiliar);
	}
	/*antigoPai->getFilhoMaior()->deleteFilhoMenor();

	if (antigoPai->getValor() == raiz->getValor()) {
		antigoPai->getPai()->setPai(nullptr);
		raiz = antigoPai->getPai();
	}*/
}

void Arvore::rotacionarParaEsq(No* novaRaiz) {
	No* aux = new No();
	aux->setNivel(novaRaiz->getNivel()); 
	aux->setPai(novaRaiz->getPai());
	aux->setValor(novaRaiz->getPai()->getValor()); // aux terá o valor da raiz antiga
	aux->setFilhoMaior(nullptr);
	aux->setFilhoMenor(nullptr);


	if (novaRaiz->getPai()->getFilhoMenor() != nullptr) {
		if (novaRaiz->getPai()->getFilhoMenor() < aux) // o filho menor é maior do que aux
			aux->setFilhoMaior(novaRaiz->getPai()->getFilhoMenor());
		else // o filho menor é menor do que aux
			aux->setFilhoMenor(novaRaiz->getPai()->getFilhoMenor());

		novaRaiz->getPai()->setFilhoMenor(aux); // o filho menor do pai é o aux -> antigo pai
	}
	else
		novaRaiz->getPai()->setFilhoMenor(aux); // o filho menor do pai é o aux -> antigo pai

	novaRaiz->getPai()->setValor(novaRaiz->getValor());
	novaRaiz->setValor(novaRaiz->getFilhoMaior()->getValor());
	
	if (novaRaiz->getFilhoMaior()->getFilhoMaior() != nullptr)
		novaRaiz->setFilhoMaior(novaRaiz->getFilhoMaior()->getFilhoMaior());
	else
		novaRaiz->setFilhoMaior(novaRaiz->getFilhoMaior()->getFilhoMenor());

	if (raiz->getValor() == novaRaiz->getValor()) {
		novaRaiz->setPai(nullptr);
		raiz = novaRaiz;
	}

	toString(); //recalcular niveis
}


void Arvore::exclusaoOrdenada(int valor){
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////ver se não está vazio//////////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	No* indesejado;
	if (!estaVazia()) {
		
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////ver se existe o valor a ser inserido///////////////////////////////////// 
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////

		posicionarNoPrimeiro();
		procurarNo(valor); // posiciona o atual
		
		if (atual->getValor() == raiz->getValor() && quantidadeNos == 1) {
			raiz = nullptr;
			quantidadeNos--;
		}
 		else if (atual->getValor() == valor) {
			indesejado = atual; // indesejado é o que se deseja excluir
			reordenar(indesejado);
			quantidadeNos--;
		}
	}
}

void Arvore::exclusaoOrdenada(No* indesejado) {
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////ver se não está vazio//////////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if (!estaVazia()) {
		if (procurarNo(indesejado->getValor()))
			reordenar(indesejado);
	}
}

std::string Arvore::toString()
{
	arvoreString = "";
	if (!estaVazia()) {
		posicionarNoPrimeiro();
		adicionarAString(raiz);
	}
	else
		arvoreString = "()";

	return arvoreString;
}

void Arvore::adicionarAString(No* noAtual){
 adicionarAString_inicio:
	//strcat_s(arvoreString, 1, "(");
	//strcat(arvoreString, "(");
	arvoreString += "(";					  //// inicia sempre com um parênteses

	if (noAtual->getFilhoMenor() != nullptr) { //// se tem o filho menor
		//adicionarAString(noAtual->getFilhoMenor()); //// recursão => avança para o próximo maior
		p.empilha(new NoPilha(noAtual, 7, "adicionarAString"));
		noAtual = noAtual->getFilhoMenor();
		goto adicionarAString_inicio;

		local7:
			noAtual = p.desempilha()->getValor();
	}
	
	char pontChar[6];
	_itoa_s(noAtual->getValor(), pontChar, 10);
	arvoreString += pontChar;
	if (noAtual->getNivel() > niveis - 1) // se o nível do noAtual é maior que último nível => incrementa niveis
		niveis += 1;

	if (noAtual->getFilhoMaior() != nullptr) { //// se tem o filho maior
		//adicionarAString((*noAtual).getFilhoMaior()); //// recursão => avança para o próximo maior
		p.empilha(new NoPilha(noAtual, 8, "adicionarAString"));
		noAtual = noAtual->getFilhoMaior();
		goto adicionarAString_inicio;

		local8:
			noAtual = p.desempilha()->getValor();
	}

		arvoreString += ")";					  //// finaliza sempre com um parênteses

		if (!p.estaVazia()) {
			if (p.getTopo()->indicacao == 7)
				goto local7;
			else if (p.getTopo()->indicacao == 8)
				goto local8;
		}
	
		if (!p.estaVazia() && (p.getTopo()->getFuncao() == "adicionarAString")) {
		noAtual = p.desempilha()->getValor();
		goto adicionarAString_inicio;
	}
}



No* Arvore::maiorDeTodos() {
	///////// posiciona no primeiro
	posicionarNoPrimeiro();
	
	///////// se o atual tiver um filho maior
	while (atual->getFilhoMaior() != nullptr) {
		////// o filho maior é maior que o atual
		atual = atual->getFilhoMaior();
	}

	///// retorna o maior
	return atual;
}

No* Arvore::menorDeTodos() {
	///////// posiciona no primeiro
	posicionarNoPrimeiro();

	///////// se o atual tiver um filho menor
	while (atual->getFilhoMenor() != nullptr) {
		////// o filho menor é menor que o atual
		atual = atual->getFilhoMenor();
	}

	///// retorna o menor
	return atual;
}

void Arvore::reordenar(No* problema) { // no caso de exclusão => problema === indesejado // colocar o menor dos maiores ou o maior dos menores no lugar do pai
	No* irmaoDoProblema;
	No* irmaoCerto;
	No* paiCerto;
	No* menorMaiores;
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////se o problema não é folha e tem um filho maior//////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
  
	if (problema->getFilhoMaior() != nullptr) { // se o problema tem um filho maior, esse deve ir no lugar do problema
		paiCerto = problema->getFilhoMaior();

		while (paiCerto->getFilhoMenor() != nullptr)
			paiCerto = paiCerto->getFilhoMenor();

		//problema->setFilhoMaior(paiCerto->getFilhoMaior());
		if (paiCerto->getValor() > paiCerto->getPai()->getValor())
			paiCerto->getPai()->setFilhoMaior(paiCerto->getFilhoMaior());
		else
			paiCerto->getPai()->setFilhoMenor(paiCerto->getFilhoMaior());

		problema->setValor(paiCerto->getValor());

		if (paiCerto->getFilhoMaior() != nullptr)
			paiCerto->getFilhoMaior()->setPai(paiCerto->getPai());
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////se o problema não é folha e tem um filho menor//////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////

	else if (problema->getFilhoMenor() != nullptr) { // se o problema tem um filho menor, esse deve ir no lugar do problema
		paiCerto = problema->getFilhoMenor();

		while (paiCerto->getFilhoMaior() != nullptr)
			paiCerto = paiCerto->getFilhoMaior();

		if (paiCerto->getValor() > paiCerto->getPai()->getValor())
			paiCerto->getPai()->setFilhoMaior(paiCerto->getFilhoMaior());
		else
			paiCerto->getPai()->setFilhoMenor(paiCerto->getFilhoMaior());

		problema->setValor(paiCerto->getValor());

		if (paiCerto->getFilhoMenor() != nullptr)
			paiCerto->getFilhoMenor()->setPai(paiCerto->getPai());
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////se o problema é folha e é filho maior////////////////////////////////////// => quando é folha não terei que chamar a recursão novamente
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	else if (problema->getPai() != nullptr) {
		if ((problema->getPai()->getFilhoMaior() != nullptr) && (problema->getValor() == problema->getPai()->getFilhoMaior()->getValor())) {
			// se o problema é maior que o pai, tenho que procurar o maior dos menores OU se o problema é igual ao pai, o pai já foi o problema
			irmaoDoProblema = problema->getPai()->getFilhoMenor();  // o irmaoDoProblema é menor que o problema

			if (irmaoDoProblema == nullptr) { // o problema é folha e não tem irmãos
				problema->getPai()->deleteFilhoMaior();
				problema->setPai(nullptr);
			}

			///////////////////////// se o irmao do problema não é folha e tem um filho maior
			else if (irmaoDoProblema->getFilhoMaior() != nullptr) { // se o irmaoDoProblema tem um filho maior, ele que deverá ir no lugar do pai
				/////// maior dos menores pai
				irmaoCerto = irmaoDoProblema->getFilhoMaior();

				while (irmaoCerto->getFilhoMaior() != nullptr)
					irmaoCerto = irmaoCerto->getFilhoMaior();

				problema->setValor(problema->getPai()->getValor());
				problema->getPai()->setValor(irmaoCerto->getValor());
				irmaoCerto->getPai()->deleteFilhoMaior();
			}

			///////////////////////// se o irmao do problema não é folha e tem um filho menor
			else if (irmaoDoProblema->getFilhoMenor() != nullptr) { // se o irmaoDoProblema tem um filho menor, mas não tem um filho maior,
				/////// rotacionar para dir
				problema->setValor(problema->getPai()->getValor());
				problema->getPai()->setValor(irmaoDoProblema->getValor());
				problema->getPai()->setFilhoMenor(irmaoDoProblema->getFilhoMenor());
				problema->getPai()->getFilhoMenor()->setPai(problema->getPai());
				
				//acertar nivel dos filhos menores do irmao do problema
			    irmaoCerto = irmaoDoProblema->getFilhoMenor();
				
				do {
					irmaoCerto->setNivel(irmaoCerto->getPai()->getNivel() + 1);
					irmaoCerto = irmaoCerto->getFilhoMenor();
				} while (irmaoCerto != nullptr);

				//acertar nivel dos filhos maiores do filho menor do irmao do problema
				if (irmaoDoProblema->getFilhoMenor()->getFilhoMaior() != nullptr) {
					irmaoCerto = irmaoDoProblema->getFilhoMenor()->getFilhoMaior();

					do {
						irmaoCerto->setNivel(irmaoCerto->getPai()->getNivel() + 1);
						irmaoCerto = irmaoCerto->getFilhoMaior();
					} while (irmaoCerto != nullptr);
				}

			}

			else if (irmaoDoProblema != nullptr)
				problema->getPai()->setFilhoMaior(nullptr);
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////se o problema é folha e é filho menor////////////////////////////////////// => quando é folha não terei que chamar a recursão novamente
		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		else if (problema->getPai()->getFilhoMenor() != nullptr && ((problema->getValor() < problema->getPai()->getValor()) || problema->getValor() == problema->getPai()->getFilhoMenor()->getValor())) {
			// se o problema é menor que o pai, tenho que procurar o menor dos maiores OU se o problema é igual ao pai, o pai já foi problema
			irmaoDoProblema = problema->getPai()->getFilhoMaior();

			if (irmaoDoProblema == nullptr) { // o problema é folha e não tem irmãos
				problema->getPai()->deleteFilhoMenor();
				problema->setPai(nullptr);
			}

			///////////////////////// se o irmao do problema não é folha e tem um filho menor
			else if (irmaoDoProblema->getFilhoMenor() != nullptr) { // se o irmaoDoProblema tem um filho menor, ele que deverá ir no lugar do pai
				/////// menor dos maiores pai
				irmaoCerto = irmaoDoProblema->getFilhoMenor();

				while (irmaoCerto->getFilhoMenor() != nullptr)
					irmaoCerto = irmaoCerto->getFilhoMenor();

				problema->setValor(problema->getPai()->getValor());
				problema->getPai()->setValor(irmaoCerto->getValor());
				irmaoCerto->getPai()->setFilhoMenor(irmaoCerto->getFilhoMaior());

				// acertar niveis dos filhos maiores de irmaoCerto
				if (irmaoCerto->getFilhoMaior() != nullptr) {
					do {
						irmaoCerto->getFilhoMaior()->setNivel(irmaoCerto->getNivel() + 1);
						irmaoCerto = irmaoCerto->getFilhoMaior();
					} while (irmaoCerto != nullptr);
				}
			}

			///////////////////////// se o irmao do problema não é folha e tem um filho maior
			else if (irmaoDoProblema->getFilhoMaior() != nullptr) { 
				// rotacionar para esq
				problema->setValor(problema->getPai()->getValor());
				problema->getPai()->setValor(irmaoDoProblema->getValor());
				problema->getPai()->setFilhoMaior(irmaoDoProblema->getFilhoMaior());
				problema->getPai()->getFilhoMaior()->setPai(problema->getPai());

				//acertar nivel dos filhos maiores do irmao do problema
				irmaoCerto = irmaoDoProblema->getFilhoMaior();

				do {
					irmaoCerto->setNivel(irmaoCerto->getPai()->getNivel() + 1);
					irmaoCerto = irmaoCerto->getFilhoMaior();
				} while (irmaoCerto != nullptr);

				irmaoCerto = irmaoDoProblema->getFilhoMaior()->getFilhoMenor();
				//acertar nivel dos filhos menores do filho maior do irmao do problema
				if (irmaoCerto != nullptr) {
					do {
						irmaoCerto->setNivel(irmaoCerto->getPai()->getNivel() + 1);
						irmaoCerto = irmaoCerto->getFilhoMenor();
					} while (irmaoCerto != nullptr);
				}
			}

			else if (irmaoDoProblema != nullptr)
				problema->getPai()->setFilhoMenor(nullptr);
		}
	}
	else
		this->raiz = nullptr;

	balanceada(raiz);
	balanceada(raiz);
	balanceada(raiz);
}

No* Arvore::getRaiz()
{
	return raiz;
}

No* Arvore::getAtual() {
	int teste = atual->getValor();
	return atual;
}

bool Arvore::estaVazia()
{
	if (raiz == nullptr) {				// se atual for nulo
		return true;					// retorna um nó vazio
	}
	return false;
}

void Arvore::setRaiz(No* novaRaiz)
{
	raiz = novaRaiz;
}

void Arvore::setAtual(No* no)
{
	atual = no;
}

void Arvore::posicionarNoPrimeiro()
{
	int teste = raiz->getValor();
	atual = raiz;
	teste = atual->getValor();
}

/*
No* procurarNo(int)
verifica em toda a árvore se há algum nó com o valor 
*/
No* Arvore::procurarNo(int valorProcurado)
{	
	procurarNo_inicio:
	if (this->getAtual()->getValor() == valorProcurado)	// se o valor do nó atual é igual ao valorProcurado
		return atual;								// retorna atual

	if (getAtual()->getValor() > valorProcurado) {	// se o valor do nó atual é maior que o valorProcurado
		if (getAtual()->getFilhoMenor() == nullptr) // se o filho menor do atual é nulo
			return getAtual()->getFilhoMenor();							// retorno o atual

		atual = getAtual()->getFilhoMenor();		// atual aponta para o filho menor
		//return procurarNo(valorProcurado);			// recursão => procura novamente, sendo o filho menor o atual
		goto procurarNo_inicio;
	}

	if (getAtual()->getValor() < valorProcurado) {   // se o valor do nó atual é menor que o valorProcurado
		if (getAtual()->getFilhoMaior() == nullptr) // se o filho maior do atual é nulo
			return getAtual()->getFilhoMaior();							// retorno o atual

		atual = getAtual()->getFilhoMaior();		// atual aponta para o filho maior
		//return procurarNo(valorProcurado);			// recursão => procura novamente, sendo o filho maior o atual
		goto procurarNo_inicio;
	}

	return atual; // retorna o atual
}

Arvore::~Arvore()
{
}

/*ostream& operator<<(ostream& saida, const Arvore a)
{
	// TODO: insert return statement here
	adicionarAString(raiz);
	return arvoreString;
}*/
