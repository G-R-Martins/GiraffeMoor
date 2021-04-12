#include "PCH.h"


//Construtor Padrão
Matrix::Matrix(void)
{
	m_lines_deleted = true;
	m_alloced_lines = 0;
	m_lines = 1;
	m_columns = 1;
	//Inicializa a matriz como null e tenta alocá-la
	m_matrix = NULL;
	if (!alloc())
		printf("Nao foi possivel alocar matriz! \n");
}
//Construtor de matriz quadrada
Matrix::Matrix(long lines)
{
	m_lines_deleted = true;
	m_alloced_lines = 0;
	m_lines = lines;
	m_columns = 1;
	//Inicializa a matriz como null e tenta alocá-la
	m_matrix = NULL;
	if (!alloc())
		printf("Nao foi possivel alocar matriz! \n");
}
//Construtor Paramétrico
Matrix::Matrix(long lines, long columns)
{
	m_lines_deleted = true;
	m_alloced_lines = 0;
	m_lines = lines;
	m_columns = columns;
	//Inicializa a matriz como null e tenta alocá-la
	m_matrix = NULL;
	if (!alloc())
		printf("Nao foi possivel alocar matriz! \n");
}
//Construtor de cópia
Matrix::Matrix(Matrix const &copied)
{
	//Verifica dimensões da matriz - se necessário, faz re-alocação
	//if (copied.m_alloced_lines != m_alloced_lines)
	//{
	m_alloced_lines = 0;
	m_lines = copied.m_lines;
	m_columns = copied.m_columns;
	m_lines_deleted = true;
	//Inicializa a matriz como null e tenta alocá-la
	m_matrix = NULL;
	if (!alloc())
		printf("Nao foi possivel alocar matriz! \n");
	//}
	//Copia os valores na nova matriz
	for (long i = 0; i < copied.m_alloced_lines; i++)
		m_matrix[i] = copied.m_matrix[i];
}
////Move semantics
//Matrix::Matrix(Matrix&& copied) noexcept
//	: m_matrix(std::move(copied.m_matrix)), m_lines(std::move(copied.m_lines)), m_columns(std::move(copied.m_columns)),
//	m_alloced_lines(std::move(copied.m_alloced_lines)), m_lines_deleted(std::move(copied.m_lines_deleted))
//{
//	copied.m_matrix = nullptr;
//}
//Destrutor Padrão
Matrix::~Matrix(void)
{
	flush();
}

//Retorna o número de linhas da matriz
long Matrix::getLines()
{
	return this->m_lines;
}
//Retorna o número de colunas da matriz 
long Matrix::getColumns()
{
	return this->m_columns;
}
//Define o número de linhas da matriz
void Matrix::setLines(long value)
{
	m_lines = value;
}
//Define o número de colunas da matriz
void Matrix::setColumns(long value)
{
	m_columns = value;
}

//Imprime a matriz na tela
void Matrix::print()
{
	printf("\n");
	for (long i = 0; i < this->getLines(); i++)
	{
		printf("|");
		for (long j = 0; j < this->getColumns(); j++)
		{
			if (m_matrix[i + j * m_lines] >= 0.0)
				printf(" %.4e ", m_matrix[i + j * m_lines]);
			else
				printf(" %.4e ", m_matrix[i + j * m_lines]);
		}
		printf("|\n");
	}
	printf("\n");
}
//Imprime a matriz em um arquivo de texto, cujo nome está no char s
void Matrix::fprint(const char* s)
{
	FILE *file1 = fopen(s, "a");
	fprintf(file1, "\n");
	for (long i = 0; i < this->getLines(); i++)
	{
		fprintf(file1, "| ");
		for (long j = 0; j < this->getColumns(); j++)
		{
			if (m_matrix[i + j * m_lines] > 1 || m_matrix[i + j * m_lines] < -1)
				fprintf(file1, " %.5e\t", m_matrix[i + j * m_lines]);
			else
				fprintf(file1, "      0     \t");// , m_matrix[i + j * m_lines]);
		}
		fprintf(file1, "|\n");
	}
	fprintf(file1, "\n");
	fclose(file1);
}

//Aloca a matriz
bool Matrix::alloc()
{
	flush();

	//Tenta alocar a matriz
	if (!(m_matrix = new double[( size_t )m_lines* ( size_t )m_columns]))
		//Falha
		return false;
	//Caso consiga
	else
	{
		m_alloced_lines = m_lines * m_columns;
		this->m_lines_deleted = false;

		for (long i = 0; i < m_alloced_lines; i++)
			m_matrix[i] = 0.0;
		return true;
	}
}
bool Matrix::alloc(const long& lines)
{
	flush();
	m_lines = lines;
	m_columns = 1;

	//Tenta alocar a matriz
	if (!(m_matrix = new double[lines]))
		//Falha
		return false;
	//Caso consiga
	else
	{
		m_alloced_lines = lines;
		this->m_lines_deleted = false;

		for (long i = 0; i < m_alloced_lines; i++)
			m_matrix[i] = 0.0;
		return true;
	}
}
bool Matrix::alloc(const long& lines, const long& columns)
{
	flush();
	m_lines = lines;
	m_columns = columns;

	//Tenta alocar a matriz
	if (!(m_matrix = new double[( size_t )m_lines* ( size_t )m_columns]))
		//Falha
		return false;
	//Caso consiga
	else
	{
		m_alloced_lines = m_lines * m_columns;
		this->m_lines_deleted = false;

		for (long i = 0; i < m_alloced_lines; i++)
			m_matrix[i] = 0.0;
		return true;
	}
}

//Libera a memória ocupada pela matriz
bool Matrix::flush()
{
	//Percorre as linhas
	//Se há linhas para desalocar
	if (this->m_lines_deleted == false)
	{
		if (m_matrix)
			delete[] m_matrix;
		//Desalocada com sucesso
		m_lines_deleted = true;	//para evitar desalocação novamente
		m_matrix = NULL;
		m_alloced_lines = 0;
	}
	return true;
}
//Zera a matriz, mantendo as dimensões atuais
void Matrix::clear()
{
	for (int i = 0; i < m_alloced_lines; i++)
		m_matrix[i] = 0.0;
}

//Operador Soma
Matrix operator + (Matrix& matrix1, Matrix& matrix2)
{
	//Verifica se as dimensões das matrizes são compatíveis
	if (( matrix1.getLines() != matrix2.getLines() ) || ( matrix1.getColumns() != matrix2.getColumns() ))
	{
		//Mensagem de erro - Dimensões Incompatíveis
		printf("Matrizes devem possuir a mesma dimensao! \n");
		//Retorna vazio
		return NULL;
	}
	//Caso as dimensões sejam compatíveis
	else
	{
		//Cria uma matriz de retorno
		Matrix return_matrix(matrix1.getLines(), matrix1.getColumns());

		//Subtrai elemento a elemento da matriz
		for (long i = 0; i < matrix1.m_alloced_lines; i++)
			return_matrix.m_matrix[i] = matrix1.m_matrix[i] + matrix2.m_matrix[i];

		//Retorna a matriz subtração
		return return_matrix;
	}
}
//Operador Subtração
Matrix operator - (Matrix &matrix1, Matrix &matrix2)
{
	//Verifica se as dimensões das matrizes são compatíveis
	if ((matrix1.getLines() != matrix2.getLines()) || (matrix1.getColumns() != matrix2.getColumns()))
	{
		//Mensagem de erro - Dimensões Incompatíveis
		printf("Matrizes devem possuir a mesma dimensao! \n");
		//Retorna vazio
		return NULL;
	}
	//Caso as dimensões sejam compatíveis
	else
	{
		//Cria uma matriz de retorno
		Matrix return_matrix(matrix1.getLines(), matrix1.getColumns());

		//Subtrai elemento a elemento da matriz
		for (long i = 0; i < matrix1.m_alloced_lines; i++)
			return_matrix.m_matrix[i] = matrix1.m_matrix[i] - matrix2.m_matrix[i];

		//Retorna a matriz subtração
		return return_matrix;
		//return std::move(return_matrix);
	}
}


//Operador Multiplicacao de matrizes
Matrix operator * (Matrix &matrix1, Matrix &matrix2)
{
	//Verificação da possibilidade de multiplicação
	if (matrix1.m_columns != matrix2.m_lines)
	{
		//Produto escalar
		if (matrix1.m_lines == matrix2.m_lines)
		{
			Matrix ret(1, 1);
			for (int i = 0; i < matrix1.m_lines; i++)
				ret(0, 0) += matrix1(i, 0)*matrix2(i, 0);
			return ret;
		}
		else
		{
			printf("Nao e possivel multiplicar as matrizes. Dimensoes incompativeis!");
			return NULL;
		}
	}
	else
	{

		Matrix return_m(matrix1.m_lines, matrix2.m_columns);
		//Se a segunda matriz for um vetor
		if (matrix2.m_columns == 1)
			cblas_dgemv(CblasColMajor, CblasNoTrans, matrix1.m_lines, matrix1.m_columns, 1.0, matrix1.m_matrix, matrix1.m_lines, matrix2.m_matrix, 1, 0.0, return_m.m_matrix, 1);
		//Se não
		else
			cblas_dgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, matrix1.m_lines, matrix2.m_columns, matrix2.m_lines, 1.0, matrix1.m_matrix, matrix1.m_lines, matrix2.m_matrix, matrix2.m_lines, 1, return_m.m_matrix, return_m.m_lines);
		//return_m.print();
		return return_m;
	}
}
//Operador Multiplicacao por escalar
Matrix operator * (double escalar, Matrix& matrix1)
{
	//Cria uma matriz de retorno
	Matrix return_matrix(matrix1.getLines(), matrix1.getColumns());

	//Faz o produto de cada elemento da matriz pelo escalar
	for (long i = 0; i < return_matrix.m_alloced_lines; i++)
		return_matrix.m_matrix[i] = matrix1.m_matrix[i] * escalar;

	//Retorna a matriz produto por escalar
	return return_matrix;


}
//Operador Multiplicacao por escalar
Matrix operator * (Matrix& matrix1, double escalar)
{
	//Retorna a função anterior, já que esta operação é comutativa
	return escalar * matrix1;
}
//Verificação de igualdade
bool operator == (Matrix &matrix1, Matrix &matrix2)
{
	//Verifica a igualdade de dimensões
	if ((matrix1.getLines() != matrix2.getLines()) || (matrix1.getColumns() != matrix2.getColumns()))
		return false;
	else
	{
		//Varre a matriz e verifica a igualdade de elementos
		for (long i = 0; i < matrix1.m_alloced_lines; i++)
			if (matrix1.m_matrix[i] != matrix2.m_matrix[i]) return false;
		//Matrizes iguais
		return true;
	}
}
//Verificação de inegualdade
bool operator != (Matrix &matrix1, Matrix &matrix2)
{
	return !(matrix1 == matrix2);
}
//Operador de Atribuição	
Matrix &Matrix::operator = (Matrix const &matrix1)
{
	//Verifica dimensões da matriz - se necessário, faz re-alocação
	if (matrix1.m_alloced_lines != m_alloced_lines)
	{
		this->flush();
		m_alloced_lines = 0;
		m_lines = matrix1.m_lines;
		m_columns = matrix1.m_columns;
		m_lines_deleted = matrix1.m_lines_deleted;
		//Inicializa a matriz como null e tenta alocá-la
		m_matrix = NULL;
		if (!alloc())
			printf("Nao foi possivel alocar matriz! \n");
	}
	//Copia os valores na nova matriz
	for (long i = 0; i < matrix1.m_alloced_lines; i++)
		m_matrix[i] = matrix1.m_matrix[i];

	//Retorna esta matriz
	return *this;
}
////Operador de Atribuição	
//Matrix& Matrix::operator=(Matrix&& matrix1) noexcept
//{
//	//Verifica dimensões da matriz - se necessário, faz re-alocação
//	if (this->m_alloced_lines != matrix1.m_alloced_lines)
//	{
//		this->flush();
//		m_alloced_lines = 0;
//		m_lines = std::move(matrix1.m_lines);
//		m_columns = std::move(matrix1.m_columns);
//		m_lines_deleted = std::move(matrix1.m_lines_deleted);
//		//Inicializa a matriz como null e tenta alocá-la
//		m_matrix = std::move(matrix1.m_matrix);
//		if (!alloc())
//			printf("Nao foi possivel alocar matriz! \n");
//	}
//	////Copia os valores na nova matriz
//	//for (long i = 0; i < matrix1.m_alloced_lines; i++)
//	//	m_matrix[i] = matrix1.m_matrix[i];
//	m_matrix = std::move(matrix1.m_matrix);
//
//	matrix1.m_matrix = nullptr;
//	//Retorna esta matriz
//	return *this;
//}
//Retorno do valor na posição especificada
double &Matrix::operator() (long line, long column)
{

	//Verifica se a posição é válida
	if (line > this->m_lines - 1 || column > this->m_columns - 1 || line < 0 || column < 0)
	{
		printf("Not valid position accessed in matrix! (%d,%d)\n", line, column);
		double* ret = new double[1];
		ret[0] = 0;
		return ret[0];
	}
	else
		//Retorna o valor na posição desejada
		return this->m_matrix[line + column * m_lines];
}
//Operador produto escalar entre dois vetores
double dot(Matrix &matrix1, Matrix &matrix2)
{
	//Verificação da possibilidade do produto
	if (matrix1.m_lines != matrix2.m_lines)
	{
		printf("Nao e possivel calcular o produto escalar. Dimensoes incompativeis!");
		return 0;
	}
	else
	{
		double return_value = 0.0;
		for (int i = 0; i < matrix1.m_alloced_lines; i++)
			return_value += matrix1.m_matrix[i] * matrix2.m_matrix[i];
		return return_value;
	}
}
//Operador produto vetorial entre dois vetores
Matrix cross(Matrix &matrix1, Matrix &matrix2)
{
	//Verificação da possibilidade do produto
	if (matrix1.m_columns != 1 || matrix2.m_columns != 1 || matrix1.m_lines != 3 || matrix2.m_lines != 3)
	{
		printf("Nao e possivel calcular o produto vetorial. Dimensoes incompativeis!");
		return 0;
	}
	else
	{
		Matrix return_m(3);
		return_m(0, 0) = matrix1(1, 0)*matrix2(2, 0) - matrix1(2, 0)*matrix2(1, 0);
		return_m(1, 0) = matrix1(2, 0)*matrix2(0, 0) - matrix1(0, 0)*matrix2(2, 0);
		return_m(2, 0) = matrix1(0, 0)*matrix2(1, 0) - matrix1(1, 0)*matrix2(0, 0);
		return return_m;
	}
}
//Inverte uma matriz 2x2
Matrix invert2x2(Matrix &matrix)
{
	//Verificação da possibilidade de inversão
	if (matrix.getColumns() != 2 || matrix.getLines() != 2)
	{
		printf("Nao e possivel inverter a matriz. Dimensoes incompativeis!");
		return 0;
	}
	else
	{
		double a = matrix(0, 0);
		double b = matrix(0, 1);
		double c = matrix(1, 0);
		double d = matrix(1, 1);
		double determ = a * d - b * c;
		Matrix return_m(2, 2);
		return_m(0, 0) = d / determ;
		return_m(0, 1) = -b / determ;
		return_m(1, 0) = -c / determ;
		return_m(1, 1) = a / determ;

		return return_m;
	}
}

//Inverte uma matriz 3x3
Matrix invert3x3(Matrix &matrix)
{
	//Verificação da possibilidade de inversão
	if (matrix.getColumns() != 3 || matrix.getLines() != 3)
	{
		printf("Nao e possivel inverter a matriz. Dimensoes incompativeis!");
		return 0;
	}
	else
	{
		double determinant = matrix(0, 0)*matrix(1, 1)*matrix(2, 2) + matrix(1, 0)*matrix(2, 1)*matrix(0, 2) + matrix(2, 0)*matrix(0, 1)*matrix(1, 2) -
			matrix(0, 0)*matrix(2, 1)*matrix(1, 2) - matrix(2, 0)*matrix(1, 1)*matrix(0, 2) - matrix(1, 0)*matrix(0, 1)*matrix(2, 2);

		Matrix return_m(3, 3);
		return_m(0, 0) = 1.0 / determinant * (matrix(1, 1)*matrix(2, 2) - matrix(1, 2)*matrix(2, 1));
		return_m(0, 1) = 1.0 / determinant * (matrix(0, 2)*matrix(2, 1) - matrix(0, 1)*matrix(2, 2));
		return_m(0, 2) = 1.0 / determinant * (matrix(0, 1)*matrix(1, 2) - matrix(0, 2)*matrix(1, 1));

		return_m(1, 0) = 1.0 / determinant * (matrix(1, 2)*matrix(2, 0) - matrix(1, 0)*matrix(2, 2));
		return_m(1, 1) = 1.0 / determinant * (matrix(0, 0)*matrix(2, 2) - matrix(0, 2)*matrix(2, 0));
		return_m(1, 2) = 1.0 / determinant * (matrix(0, 2)*matrix(1, 0) - matrix(0, 0)*matrix(1, 2));

		return_m(2, 0) = 1.0 / determinant * (matrix(1, 0)*matrix(2, 1) - matrix(1, 1)*matrix(2, 0));
		return_m(2, 1) = 1.0 / determinant * (matrix(0, 1)*matrix(2, 0) - matrix(0, 0)*matrix(2, 1));
		return_m(2, 2) = 1.0 / determinant * (matrix(0, 0)*matrix(1, 1) - matrix(0, 1)*matrix(1, 0));

		return return_m;
	}
}

//Operador produto tensorial entre dois vetores
Matrix dyadic(Matrix &matrix1, Matrix &matrix2)
{
	//Verificação da possibilidade do produto
	if (matrix1.m_columns != 1 || matrix2.m_columns != 1 || matrix1.m_lines != matrix2.m_lines)
	{
		printf("Nao e possivel calcular o produto tensorial. Dimensoes incompativeis!");
		return 0;
	}
	else
	{
		int order = matrix1.m_lines;
		Matrix return_m(order, order);
		for (int i = 0; i < order; i++)
			for (int j = 0; j < order; j++)
				return_m(i, j) = matrix1(i, 0)*matrix2(j, 0);
		return return_m;
	}
}
//Operador skew de um vetor
Matrix skew(Matrix &matrix1)
{
	//Verificação da possibilidade do produto
	if (matrix1.m_columns != 1 || matrix1.m_lines != 3)
	{
		printf("Nao e possivel calcular o produto escalar. Dimensoes incompativeis!");
		return 0;
	}
	else
	{
		Matrix return_m(3, 3);
		return_m(0, 1) = -matrix1(2, 0);
		return_m(0, 2) = +matrix1(1, 0);
		return_m(1, 2) = -matrix1(0, 0);

		return_m(1, 0) = +matrix1(2, 0);
		return_m(2, 0) = -matrix1(1, 0);
		return_m(2, 1) = +matrix1(0, 0);
		return return_m;
	}
}
//Operador axial de um vetor
Matrix axial(Matrix &matrix1)
{
	//Verificação da possibilidade do produto
	if (matrix1.m_columns != 3 || matrix1.m_lines != 3)
	{
		printf("Nao e possivel calcular o produto escalar. Dimensoes incompativeis!");
		return 0;
	}
	else
	{
		Matrix return_m(3);
		return_m(0, 0) = -matrix1(1, 2);
		return_m(1, 0) = +matrix1(0, 2);
		return_m(2, 0) = -matrix1(0, 1);
		return return_m;
	}
}
//Resolve o sistema linear da forma Ax=b (utilizando fatoração LU)
Matrix fullsystem(Matrix &A, Matrix &b, int *flag_error)
{
	int n = A.getLines();
	int nrhs = 1;
	int lda = A.getLines();
	int ldb = b.getLines();
	int info = 1;
	int *ipiv;
	char param = 'N';
	ipiv = new int[b.getLines()];
	//Faz fatoracao LU
	dgetrf(&n, &n, A.getMatrix(), &lda, ipiv, &info);
	if (info != 0)
		*flag_error = 1;
	else
		*flag_error = 0;
	//Resolve o sistema linear
	dgetrs(&param, &n, &nrhs, A.getMatrix(), &lda, ipiv, b.m_matrix, &ldb, &info);
	if (info != 0)
		*flag_error = 1;
	else
	{
		if (*flag_error == 0)
			*flag_error = 0;
	}

	delete[]ipiv;
	return b;
}
//Retorna o endereço de uma matriz
double* Matrix::getMatrix()
{
	return m_matrix;
}

//Retorna a norma de um vetor
double norm(Matrix &matrix1)
{
	if (matrix1.getColumns() != 1)
		printf("Dimensao nao consistente para calculo da norma");
	else
	{
		if (matrix1.getLines() != 3)
		{
			if (matrix1.getLines() == 2)
			{
				double return_value = sqrt(matrix1(0, 0)*matrix1(0, 0) +
					matrix1(1, 0)*matrix1(1, 0));
				return return_value;
			}
			if (matrix1.getLines() == 4)
			{
				double return_value = sqrt(matrix1(0, 0)*matrix1(0, 0) +
					matrix1(1, 0)*matrix1(1, 0) +
					matrix1(2, 0)*matrix1(2, 0) +
					matrix1(3, 0)*matrix1(3, 0));
				return return_value;
			}
			if (matrix1.getLines() == 6)
			{
				double return_value = sqrt(matrix1(0, 0)*matrix1(0, 0) +
					matrix1(1, 0)*matrix1(1, 0) +
					matrix1(2, 0)*matrix1(2, 0) +
					matrix1(3, 0)*matrix1(3, 0) +
					matrix1(4, 0)*matrix1(4, 0) +
					matrix1(5, 0)*matrix1(5, 0));
				return return_value;
			}
			//printf("Norma infinito\n");
			double max = 0;
			for (int i = 0; i < matrix1.getLines(); i++)
			{
				//Detecção de NaN
				if (matrix1(i, 0) == matrix1(i, 0))
				{
					//Detecção de infinito
					if (matrix1(i, 0) >= 1e300 || matrix1(i, 0) <= -1e300)
						return 1e100;
					else
					{
						if (max < abs((long)(matrix1(i, 0))))
						{
							max = abs((long)(matrix1(i, 0)));
							//printf("GL %d\n",i + 1);
						}

					}

				}
				else
					return 1e100;//valor muito alto, pois detectou NaN

			}
			return max;
		}
		else
		{
			double return_value = sqrt(matrix1(0, 0)*matrix1(0, 0) +
				matrix1(1, 0)*matrix1(1, 0) +
				matrix1(2, 0)*matrix1(2, 0));
			return return_value;
		}
	}
	return 0;
}

//Retorna a norma de um vetor considerando somente os 4 primeiros graus de liberdade
double norm4(Matrix &matrix1)
{
	if (matrix1.getLines() < 4)
		printf("Error. Function norm4\n");
	else
	{
		double return_value = sqrt(matrix1(0, 0)*matrix1(0, 0) +
			matrix1(1, 0)*matrix1(1, 0) +
			matrix1(2, 0)*matrix1(2, 0) +
			matrix1(3, 0)*matrix1(3, 0));
		return return_value;
	}
	return 0;
}

//Retorna a transposta de uma matriz
Matrix transp(Matrix &matrix1)
{
	Matrix answer(matrix1.getColumns(), matrix1.getLines());
	for (int j = 0; j < matrix1.getColumns(); j++)
	{
		for (int i = 0; i < matrix1.getLines(); i++)
		{
			answer(j, i) = matrix1(i, j);
		}
	}
	return answer;
}
//Zera a matriz
void zeros(Matrix* matrix1)
{
	for (int j = 0; j < matrix1->getColumns(); j++)
	{
		for (int i = 0; i < matrix1->getLines(); i++)
		{
			(*matrix1)(i, j) = 0.0;
		}
	}
}

//Operador Soma
double operator + (double a, Matrix &matrix2)
{
	//Verifica se as dimensões das matrizes são compatíveis
	if ((matrix2.getLines() != 1) || (matrix2.getColumns() != 1))
	{
		//Mensagem de erro - Dimensões Incompatíveis
		printf("Matriz deve ser unitária! Função operator+(double,matrix)\n");
		//Retorna vazio
		return NULL;
	}
	//Caso as dimensões sejam compatíveis
	else
	{
		return matrix2(0, 0) + a;
	}
}
