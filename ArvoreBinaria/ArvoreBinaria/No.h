#pragma once
class No
{
public:
	No();
	~No();
	void setPai(No*);
	void setValor(int);
	void setNivel(int);
	void setFilhoMenor(No*);
	void setFilhoMaior(No*);
	void deleteFilhoMenor();
	void deleteFilhoMaior();
	No* getPai();
	No* getFilhoMaior();
	No* getFilhoMenor();
	int getValor();
	int getNivel();

private:
	No* pai;
	No* filhoMenor;
	No* filhoMaior;
	int valor;
	int nivel;
};

