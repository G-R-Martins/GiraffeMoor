#pragma once


namespace AuxFunctions
{
	/*************************************************
	 *					                             *
	 * Functions to read comments and check keywords *
	 *					                             *
	 *************************************************/

/*-+-+-+-+-+-*
 *  Headers  *
 *-+-+-+-+-+-*/

	/*Reads comments
		Returns the stream at the initial point after comment reading*/
	static bool ReadComment(FILE* f, char* s);

	/*Tries to read a comment.
		Returns the stream at the point that the next reading is not a comment*/
	static bool TryComment(FILE* f);

	//Checks if readed word is a first level keyword (blue bold words)
	static bool isKeyword(char* word);



/*-+-+-+-+-+-*
 * Functions *
 *-+-+-+-+-+-*/

	bool ReadComment(FILE* f, char* s)
	{
		bool read = false;
		///////////////////////////Comentário///////////////////////////////////////
		if (s[0] == '/' && s[1] == '/')//linha de comentário
		{
			//Leitura até encontrar o caracter de fim de linha
			while (s[0] != '\n')
				auto toignore = fscanf(f, "%c", s);
			read = true;
		}
		else if (s[0] == '/' && s[1] == '*') //bloco de comentário
		{
			//Leitura até encontrar o fim do comentário
			char c1[1];
			char c2[1];
			bool exit = false;
			//Busca pelo fim do bloco em duas fases
			//1) No próprio texto já lido salvo em "s"
			for (int i = 2; i < 999; i++)
			{
				if (s[i] == '*' && s[i + 1] == '/')
					exit = true;
			}
			//2) Fora do próprio texto já lido. Busca de caracter em caracter até encontrar o fim do comentário
			while (!exit)
			{
				//Leitura do primeiro caracter
				  //Se encontrou o primeiro caracter da saída do comentário - tenta verificar o segundo caracter para confirmar saída
				if (fscanf(f, "%c", c1) && c1[0] == '*')
				{
					//Salva a posição (stream) - antes da leitura do segundo caractere
					fpos_t pos;
					fgetpos(f, &pos);
					if (fscanf(f, "%c", c2) && c2[0] == '/')
						exit = true;
					else
						fsetpos(f, &pos);
				}
			}
			read = true;
		}
		return read;
	}

	bool TryComment(FILE* f)
	{
		bool comment = true;//flag que indica que leu comentário na última tentativa
		char s[10000];

		bool at_least_one_line = false; //flag que indica se ao menos uma linha foi lida -> retornar true nesse caso
		while (comment)
		{
			//Salva a posição (stream) - antes da leitura
			fpos_t pos;
			fgetpos(f, &pos);
			//Leitura
			auto ignore = fscanf(f, "%s", s);
			comment = ReadComment(f, s);
			if (!comment)
			{
				if (at_least_one_line)
				{
					fsetpos(f, &pos); //volta à posição original do stream
					return true;
				}
				else
				{
					fsetpos(f, &pos); //volta à posição original do stream - não leu comentário
					return false;
				}
			}
			at_least_one_line = true;
		}
		return true;
	}

	bool isKeyword(char* word)
	{
		if (/*Mandatory*/!strcmp(word, "Environment") || !strcmp(word, "Keypoints") || !strcmp(word, "Lines")
			|| !strcmp(word, "Vessels") || !strcmp(word, "SegmentProperties") || !strcmp(word, "Solution") ||
			/*Optional*/ !strcmp(word, "SegmentSets") || !strcmp(word, "VesselDisplacements") || !strcmp(word, "Platforms") || !strcmp(word, "StiffnessMatrix")
			|| !strcmp(word, "Monitors") || !strcmp(word, "PostProcessing") || !strcmp(word, "GiraffeConvergenceCriteria")
			|| !strcmp(word, "GiraffeSolver") || !strcmp(word, "Constraints") || !strcmp(word, "NodalForces"))
			return true;
		//Other word
		else
			return false;
	}

}
