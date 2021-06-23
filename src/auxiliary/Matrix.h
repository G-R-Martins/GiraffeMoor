#pragma once
#include "mkl.h"

class Matrix
{
public:
	//Constructors and Destrutor
	Matrix(void);													//Construtor Padrão
	Matrix(long lines);												//Construtor de matriz coluna
	Matrix(long lines, long columns);								//Construtor Paramétrico
	Matrix(Matrix const &copied);									//Construtor de cópia
	//Matrix(Matrix&& copied) noexcept;								//Move semantics
	~Matrix(void);													//Destrutor Padrão

	//Gets and Sets
	long getLines();												//Retorna o número de linhas da matriz
	long getColumns();												//Retorna o número de colunas da matriz 

	void setLines(long value);										//Define o número de linhas da matriz 
	void setColumns(long value);									//Define o número de colunas da matriz 
	double* getMatrix();											//Retorna o endereço de uma matriz

	//General Functions
	void print();													//Imprime a matriz no console
	void fprint(const char* s);										//Imprime a matriz em um arquivo de texto, cujo nome está no char s
	bool alloc();													//Aloca a matriz 
	bool alloc(const long& lines);									//Aloca a matriz coluna com tamanho indicado
	bool alloc(const long& lines, const long& columns);				//Aloca a matriz com tamanho indicado
	bool flush();													//Libera a memória ocupada pela matriz
	void clear();													//Zera a matriz, mantando as dimensões atuais

	//Operators
	friend Matrix operator + (Matrix &matrix1, Matrix &matrix2);	//Operador Soma
	friend Matrix operator - (Matrix &matrix1, Matrix &matrix2);	//Operador Subtração
	friend Matrix operator * (Matrix &matrix1, Matrix &matrix2);	//Operador Multiplicacao de matrizes
	friend Matrix operator * (double escalar, Matrix &matrix1);		//Operador Multiplicacao por escalar
	friend Matrix operator * (Matrix &matrix1, double escalar);		//Operador Multiplicacao por escalar
	double &operator() (long line, long column);					//Retorno do valor na posição especificada
	Matrix& operator=(Matrix const &matrix1);						//Operador de Atribuição
	//Matrix& operator=(Matrix&& matrix1) noexcept;						//Operador de Atribuição

	friend bool operator == (Matrix &matrix1, Matrix &matrix2);		//Verificação de igualdade
	friend bool operator != (Matrix &matrix1, Matrix &matrix2);		//Verificação de inegualdade
	friend double dot(Matrix &matrix1, Matrix &matrix2);			//Produto escalar entre dois vetores
	friend Matrix cross(Matrix &matrix1, Matrix &matrix2);			//Operador produto vetorial entre duas matrizes
	friend Matrix dyadic(Matrix &matrix1, Matrix &matrix2);			//Operador produto vetorial entre duas matrizes
	friend Matrix skew(Matrix &matrix1);							//Operador skew de um vetor
	friend Matrix axial(Matrix &matrix1);							//Operador axial de um vetor
	friend Matrix fullsystem(Matrix &A, Matrix &b, int *flag_error);//Resolve o sistema linear da forma Ax=b
	friend double norm(Matrix &matrix1);							//Retorna a norma de um vetor
	friend double norm4(Matrix &matrix1);							//Retorna a norma de um vetor considerando somente os 4 primeiros graus de liberdade
	friend Matrix transp(Matrix &matrix1);							//Retorna a transposta de uma matriz
	friend void zeros(Matrix* matrix1);								//Zera a matriz
	friend Matrix invert3x3(Matrix &matrix);						//Inverte uma matriz 3x3	

	friend Matrix invert2x2(Matrix &matrix);						//Inverte uma matriz 2x2


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	friend double operator + (double a, Matrix &matrix2);			//Operador Soma de matriz com um elemento e um vetor	
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
protected:

	double*  m_matrix;												//Matriz unidimensional
	long     m_lines;												//Número de linhas
	long     m_columns;												//Número de colunas
	long	 m_alloced_lines;										//Número de linhas atualmente alocadas
	bool	 m_lines_deleted;										//Flag que indica se as linhas foram desalocadas				
};

//Operador Multiplicacao de matrizes
//template <typename Array>
//Matrix operator* (Matrix& matrix, Array& arr)
//{
//	//Verificação da possibilidade de multiplicação
//	if (arr.size() != matrix.m_columns)
//	{
//		printf("Nao e possivel multiplicar as matrizes. Dimensoes incompativeis!");
//		return NULL;
//	}
//	else
//	{
//		Matrix return_m(matrix.m_columns, 1);
//		//Se a segunda matriz for um vetor
//		//if (matrix.m_columns == 1)
//		{
//			for (long line = 0; line < matrix.m_lines; line++)
//			{
//				for (long column = 0; column < matrix_m_columns; column++)
//				{
//					return_m(line, 0) += matrix[line + column * matrix.m_lines] * arr[line];
//				}
//			}
//
//		}
//		//Se não
//		else
//		return_m.print();
//
//		return return_m;
//	}
//}
