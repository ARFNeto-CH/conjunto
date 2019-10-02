#include <exception>
#include <iomanip>
#include <iostream>
#include <set>
#include <string>

using namespace std;

class Erro_Operacao_Conjunto : public exception
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

	Conjunto(const Conjunto&& original)	noexcept// construtor de copia
	{
		for (auto i : original.elementos)
		{
			elementos.insert(i);
		};	// copia todos
		nome = "movido de " + original.nome;
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


int teste_nao_trata_excecao()
{
	Conjunto a, b;
	cout << "dividindo  b = a / b vai abortar porque nao foi implementado ainda" << endl;
	b = a / b;
	return 0;
}


int teste_operacoes()
{
	// testa os operadores e construtores 
	try
	{
		{	// atribuicao na declaracao
			cout << "criando A = 1..5" << endl;
			Conjunto A("A", 1, 5, 1);
			cout << A;

			cout << "declarando B = A" << endl;
			Conjunto B = A;
			cout << B;
		}

		{	// atribuicao
			cout << "atribuindo  B = A" << endl;
			cout << "criando A = 5..10" << endl;
			Conjunto A("A", 5, 10, 1);
			Conjunto B;
			B = A;
			cout << B;
		}

		{	// ^ interseccao
			Conjunto A("A", 1,  5, 1);
			Conjunto B("B", 3, 10, 1);
			cout << "criando A^B" << endl;
			Conjunto C = A ^ B;
			cout << A << B << C;
		}

		{	// diferenca Conjunto - Conjunto
			Conjunto A("A", 1, 10, 1);
			Conjunto B("B", 4, 8, 1);
			cout << "criando A - B" << endl;
			Conjunto C = A - B;
			cout << A << B << C;
		}
		 
		{	// desigualdade !=
			Conjunto A("A", 1, 10, 1);
			Conjunto B("B", 4, 8, 1);
			cout << "testando desigualdade A != B" << endl;
			cout << A << B;
			if (A != B)
			{
				cout << "diferentes" << endl;
			}
			else
			{
				cout << "iguais" << endl;
			};	// end if
		}

		{	// igualdade ==
			Conjunto A("idem", 1, 10, 1);
			Conjunto B("idem", 1, 10, 1);
			cout << A << B;
			cout << "testando igualdade A == B" << endl;
			if (A == B)
			{
				cout << "iguais" << endl;
			}
			else
			{
				cout << "diferentes" << endl;
			};	// end if
		}

		{	// diferenca Conjunto B = A - (int)
			cout << endl;
			cout << " diferenca com (int)" << endl;
			Conjunto A("A", 1, 5, 1);
			int i = 1;
			Conjunto B = A - i;
			cout << " Conjunto B = A - (i=1)";
			cout << A << B;
		}

		{	// diferenca B = A - (int)
			cout << endl;
			cout << " diferenca com (int)" << endl;
			Conjunto A("A", 1, 5, 1);
			int i = 5;
			Conjunto B;
			B = A - i;
			cout << "B = A - (i=5)";
			cout << A << B;
		}


		{	// soma Conjunto + (int)
			cout << endl;
			cout << " soma com (int)" << endl;
			cout << " soma com (int)" << endl;
			cout << " soma com (int)" << endl;

			Conjunto A("A+int", 1, 5, 1);
			int i = 0;
			cout << endl;
			cout << " Conjunto + (int) = 0" << endl;
			cout << A;
			cout << " Conjunto B = A + 0";
			Conjunto B = A + i;
			cout << B;
			cout << " C = A + 0";
			Conjunto C;
			C = A + i;
			cout << C;
		}

		{	// soma (int) + Conjunto
			cout << endl;
			cout << "(int) + Conjunto" << endl;
			cout << "(int) + Conjunto" << endl;
			cout << "(int) + Conjunto" << endl;

			Conjunto A("int+A", 1, 5, 1);
			int i = 0;
			cout << endl;
			cout << "(int) + Conjunto" << endl;
			cout << A;
			cout << " Conjunto B = 0 + A";
			Conjunto B = i + A;
			cout << B;
			cout << " C = 0 + A";
			Conjunto C;
			C = i + A;
			cout << C;
		}

		{
			cout << endl << "testa excecao tentando dividir C = A / B" << endl;
			Conjunto A("int+A", 1, 5, 1);
			Conjunto B("int+A", 1, 5, 1);
			B = B / A;
		}
	}
	catch (Erro_Operacao_Conjunto& excecao)
	{
		cout << excecao.what() << endl;
		cout << "Erro de operacao em Conjunto foi capturado: retorna normalmente" << endl;
	}	// end try
	return 0;
}	// end teste_operacoes()


int main(int argc, char** argv)
{
	teste_operacoes();
	cout << "em main() depois dos testes. Encerrando" << endl;
	//teste_nao_trata_excecao();
	return 0;
}	// end main()


void  Conjunto::aborta() const
{
	throw Erro_Operacao_Conjunto();
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
	cout << " Conjunto - int" << endl;

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
