#include <exception>
#include <iomanip>
#include <iostream>
#include <set>
#include <string>

using namespace std;

class Erro_op_Conjunto : public exception
{
public:
	virtual const char* what() const throw()
	{
		return "Conjunto: Operacao Invalida ou Nao implementada ainda";
	}
};	// end Erro_op_Conjunto()


class Conjunto
{
private:
	set<int>			elementos;
	string				nome;
	unsigned short		tamanho;

public:
	Conjunto() : tamanho{ 0 }, nome("conjunto"){}		// sem parametros
	Conjunto(string str) : tamanho{ 0 }, nome(str){}	// define nome
	Conjunto(string str, short primeiro, short limite, short incremento) : tamanho{ 0 }, nome(str)
	{
		for (int i = primeiro; i <= limite; i += incremento)
		{
			insere(i);
		}	// end for
	}	// construtor de exemplo, tipo um for: insere os caras

	Conjunto(const Conjunto& original)	// construtor de copia
	{
		for (auto i : original.elementos)
		{
			elementos.insert(i);
		};	// copia todos
		nome = "copiado de " + original.nome;
		tamanho = original.tamanho;
	}

	void 			aborta() const;
	void			define_nome(string);
	void			insere(int);
	string const	ve_nome() const;
	int const		ve_tamanho() const;

	const Conjunto& operator=(const Conjunto&);
	bool            operator==(const Conjunto&);
	bool            operator!=(const Conjunto&);

	friend ostream& operator<<(ostream&, const Conjunto&);
	friend Conjunto operator^(const Conjunto&, const Conjunto&);

	friend Conjunto operator+(const Conjunto&, const Conjunto&);
	friend Conjunto operator+(const Conjunto&, const int);
	friend Conjunto operator+(const int, const Conjunto&);

	friend Conjunto operator-(const Conjunto&, const Conjunto&);
	friend Conjunto operator-(const Conjunto&, const int);

	friend Conjunto operator*(const Conjunto&, const Conjunto&);
	friend Conjunto operator/(const Conjunto&, const Conjunto&);

};	// end class Conjunto


int teste_trata_excecao()
{
	try
	{
		Conjunto	c;
		Conjunto	d("D");
		Conjunto	e("2 pares", 2, 4, 2);
		Conjunto	f("teste", 10, 30, 1);
		cout << f << endl << "teste " << endl;;

		cout << c.ve_nome() << " tem agora " << c.ve_tamanho() << " elemetos" << endl;
		c.define_nome("outro");
		cout << c.ve_nome() << " tem agora " << c.ve_tamanho() << " elementos" << endl;

		cout << c << endl;
		cout << c << d << endl;
		cout << e << endl;

		Conjunto a("a", 2, 4, 2);
		Conjunto b("b", 1, 3, 2);
		Conjunto produto;
		Conjunto soma;
		cout << a << endl;
		cout << "calculando a = a + 6" << endl;
		a = a + 6;
		cout << a << endl;
		cout << b << endl;
		cout << "calculando b = 5 + b" << endl;
		b = 5 + b;
		cout << b << endl;
		cout << "somando soma = a + b" << endl;
		soma = a + b;
		cout << soma << endl;
		cout << "multiplicando  produto = a + b" << endl;
		produto = a * b;
		cout << produto << endl;
		cout << "dividindo  b = a / b vai abortar porque nao foi implementado ainda" << endl;
		b = a / b;
	}
	catch (Erro_op_Conjunto& excecao)
	{
		cout << excecao.what() << endl;
		cout << "Erro de operacao em Conjunto foi capturado: retorna normalmente" << endl;
	}	// end try
	return 0;
}


int teste_nao_trata_excecao()
{
	Conjunto a, b;
	cout << "dividindo  b = a / b vai abortar porque nao foi implementado ainda" << endl;
	b = a / b;
	return 0;
}


int teste_outro()
{
	try
	{
		Conjunto a("teste", 1, 4, 1);
		cout << a;
		a = 300 + a + 300;
		cout << a;
		a = a + 300;
		cout << a;
		a = 400 + 400 + a;
		cout << a;
		a = 401 + (400 + a);
		cout << a;

		//Conjunto	c("3", 1, 3, 1);
		//Conjunto	d("2", 1, 2, 1);
		//Conjunto expressao = (d + d) * c + 300;
		//cout << c;
		//cout << d;
		//cout << expressao << endl;
		//cout << c / d;		// vai cancelar aqui
	}
	catch (Erro_op_Conjunto& excecao)
	{
		cout << excecao.what() << endl;
		cout << "Erro de operacao em Conjunto foi capturado: retorna normalmente" << endl;
	}	// end try
	return 0;
}


int teste_operacoes()
{
	// testa os operadores e construtores 
	try
	{
		cout << "criando A = 1..5" << endl;
		Conjunto A("A", 1, 5, 1);
		cout << A;

		cout << "declarando B = A" << endl;
		Conjunto B = A;
		cout << B;

		cout << "atribuindo  C = B" << endl;
		Conjunto C;
		C = B;
		cout << C;

		cout << "criando D = 3..7" << endl;
		Conjunto D("D", 3, 7, 1);
		cout << D;

		cout << "mostrando A^D" << endl;
		cout << (A ^ D);

		cout << "mostrando A-D" << endl;
		cout << (A - D);

		cout << endl << "testando A != D: ";
		if (A != D)
		{
			cout << "diferentes" << endl;
		}
		else
		{
			cout << "iguais" << endl;
		};	// end if

		Conjunto F("A", 1, 5, 1);	// iguazinho a A
		cout << endl << "testando A == F: ";
		if (A == F)
		{
			cout << "iguais" << endl;
		}
		else
		{
			cout << "diferentes" << endl;
		};	// end if

		cout << "tirando 3 de F" << endl;
		F = (F - 3);
		cout << F;

		cout << "F + 6" << endl;
		cout << F + 6;

		cout << "G = F - 2" << endl;
		Conjunto G = F - 2;
		cout << G;

		cout << "G - 1" << endl;
		cout << G - 1;

		cout << "A, F, A - F" << endl;
		cout << A << F << A - F;

	}
	catch (Erro_op_Conjunto& excecao)
	{
		cout << excecao.what() << endl;
		cout << "Erro de operacao em Conjunto foi capturado: retorna normalmente" << endl;
	}	// end try
	return 0;
}


int main(int argc, char** argv)
{
	teste_operacoes();
	//teste_outro();
	//teste_trata_excecao();
	//cout << "***** voltou do teste *****" << endl;
	//cout << "***** agora testa sem tratar erro em Conjunto *****" << endl;
	//teste_nao_trata_excecao();
	//cout << "***** voltou do teste *****" << endl;
	return 0;
}	// end main()


void  Conjunto::aborta() const
{
	throw Erro_op_Conjunto();
}


void Conjunto::define_nome(string n)
{
	nome = n;
	//throw Erro_op_Conjunto();
}


void Conjunto::insere(int i)
{
	if (elementos.find(i) == elementos.end())
	{
		elementos.insert(i);
		tamanho += 1;
	}
	return;
}


string const Conjunto::ve_nome() const
{
	return nome;
}


int const Conjunto::ve_tamanho() const
{
	return tamanho;
};


const Conjunto& Conjunto::operator=(const Conjunto& original)
{
	nome = "= " + original.nome;
	tamanho = original.tamanho;
	for (auto i : original.elementos)
	{
		elementos.insert(i);
	};	// copia todos
	nome = "= a '" + original.nome + "'";
	tamanho = original.tamanho;
	return *this;
}


bool Conjunto::operator==(const Conjunto& original)
{
	if (nome != original.nome) return false;
	if (tamanho != original.tamanho) return false;
	if (elementos != original.elementos) return false;
	return true;
}


bool Conjunto::operator!=(const Conjunto& original)
{
	if (nome != original.nome) return true;
	if (tamanho != original.tamanho) return true;
	if (elementos != original.elementos) return true;
	return false;
}


ostream& operator<<(ostream& o, const Conjunto& conjunto)
{
	o << endl;
	o << "Conjunto: '" << conjunto.nome << "'" << endl << endl;
	o << "     Elementos:...." << conjunto.tamanho << endl;
	// estara vazio?
	if (conjunto.elementos.size() == 0)	return o;

	o << endl << "{" << endl;
	int n = 0;

	for (auto i : conjunto.elementos)
	{
		o << setw(6) << i;
		n = n + 1;
		if (n % 5 == 0) cout << endl;
	}
	o << endl << "}" << endl;
	o << endl << "Fim do conjunto '" << conjunto.nome << "'" << endl << endl;
	return o;
};	// end operator<<


Conjunto operator^(const Conjunto& a, const Conjunto& b)
{
	// retorna a interseccao de A e B, conjunto com 
	// apenas os valores comuns
	Conjunto inter(a.nome + "^" + b.nome);
	for (auto i : a.elementos)
		if (b.elementos.find(i) != b.elementos.end())
			inter.elementos.insert(i);
	inter.tamanho = (unsigned short) inter.elementos.size();
	return inter;
};


Conjunto operator*(const Conjunto& a, const Conjunto& b)
{
	Conjunto produto(a.nome + "*" + b.nome);
	for (auto x : a.elementos)
	{
		for (auto y : b.elementos)
		{
			produto.elementos.insert(x * y);
		}
	}	// produto cartesiano
	produto.tamanho = (unsigned short)produto.elementos.size();
	return produto;
};	// end operator*


Conjunto operator/(const Conjunto& a, const Conjunto& b)
{
	a.aborta();
	return a;
};	// end operator/


Conjunto operator+(const Conjunto& conjunto, const int valor)
{
	Conjunto soma(conjunto.nome);
	for (auto i : conjunto.elementos)
	{
		soma.elementos.insert(i);
	};	// copia todos
	soma.tamanho = conjunto.tamanho;	// claro
	if (conjunto.elementos.find(valor) == conjunto.elementos.end())
		soma.elementos.insert(valor);
	soma.tamanho = (unsigned short) soma.elementos.size();
	return soma;
}	// end operator+


Conjunto operator+(const int valor, const Conjunto& conjunto)
{
	return operator+(conjunto, valor);
}	// end operator+


Conjunto operator+(const Conjunto& a, const Conjunto& b)
{
	Conjunto soma("'" + a.nome + "' + '" + b.nome + "'");
	for (auto i : a.elementos)
	{
		soma.elementos.insert(i);
	}	// copia todos de a
	soma.tamanho = a.tamanho;	// claro
	for (auto i : b.elementos)
	{	// se nao tinha em a entao insere
		if (a.elementos.find(i) == a.elementos.end())
			soma.elementos.insert(i);
		soma.tamanho += 1;
	}	// copia todos de b que nao estavam em a 
	return soma;
}	// end operator+


Conjunto operator-(const Conjunto& conjunto, const int valor)
{
	Conjunto menosInt("'" + conjunto.nome + "' - int");
	for (auto i : conjunto.elementos)
	{
		menosInt.elementos.insert(i);
	};	// copia todos
	// agora se tem o int apaga
	auto esse = menosInt.elementos.find(valor);
	if (esse == menosInt.elementos.end())
		return menosInt;
	// tem o cara
	menosInt.elementos.erase(esse);
	menosInt.tamanho = (unsigned short) menosInt.elementos.size();
	return menosInt;
};	// end operator-


Conjunto operator-(const Conjunto& a, const Conjunto& b)
{
	Conjunto diferenca("'" + a.nome + "' - '" + b.nome + "'");
	// retorna a diferenca de A e B, conjunto com 
	// apenas os valores de A que nao estao em B
	for (auto i : a.elementos)
		if (b.elementos.find(i) == b.elementos.end())
			diferenca.elementos.insert(i);
	diferenca.tamanho = (unsigned short) diferenca.elementos.size();
	return diferenca;
};	// end operator-
