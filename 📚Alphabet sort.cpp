#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

//Функции:
size_t Chars_Number (FILE* file);
//------------------------------------------------------------------------------
/*
 Функция вычисляет количество символов в файле.

 @param[in] file - указатель на файл.

 Возвращает размер файла.

*/
//------------------------------------------------------------------------------

int Comparator_Final (void const* left_value_void_p, void const* right_value_void_p); //Просто ассистент компаратора, приводит типы.

void SortLinesUp ( char** P_Lines, int NumberOfLines );
//------------------------------------------------------------------------------
/*
 Функция сортирует строки по возрастанию.

 @param[in] P_Lines        -  Массив указателей на символьный тип
 @param[in] NumberOfLines  -  Количество строк

*/
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
long int SizeOfFile (FILE* file);
//Вычисляет размер файла
//------------------------------------------------------------------------------

int NumberOfLines (char* text, int size_text);
//------------------------------------------------------------------------------
/*
Функция вычисляет количество строк и заменяет '\n' на '\0'

 @param[in] text           -  Указатель  на массив символов.
 @param[in] size_text      -  Количество строк

 @return NumberOfLines     -

*/
//------------------------------------------------------------------------------


void PutPointers (char* text, int size_text, char** P_Lines, int NumberOfLines);
//------------------------------------------------------------------------------

/*
Функция расставляет указатели на начало строк

@param[in]  t ext        - указатель на массив символов.
@param[in]  size_text    - кооичество символов в файле.
@param[in]  P_lines      - массив указателей на начало строк.
@param[in] NumberOfLines - количество строк в файле.
*/

//------------------------------------------------------------------------------

int CompareChar (char const* left_value, char const* right_value);
//------------------------------------------------------------------------------
/*
Функция сравнивает два символа.

@param[in] left_value - левый символ.
@param[in] right_value - левый символ.

*/
//------------------------------------------------------------------------------

int CompareCharBack (char const* left, char const* right);

//------------------------------------------------------------------------------
/*
Функция сортирует два символа (назад).

@param[in] left_value - левый символ.
@param[in] right_value - левый символ.

*/
//------------------------------------------------------------------------------

void PointersOnTheBeginnings ( char** P_Lines_sort, int size_arr );
//------------------------------------------------------------------------------
/*
Функция перемещает указатели на начало строк.

@param[in] P_Lines_sort - массив указателей на строки.
@param[in] size_arr     - размер массива.
*/
//------------------------------------------------------------------------------

void Output(char** P_Lines, int number_of_lines);
//------------------------------------------------------------------------------
/*
Функция выводит отсортированный текст.

@param[in] P_Lines        - массив указателей на строки.
@param[in] NumberOfLines  - количество строк.
*/
//------------------------------------------------------------------------------

int main ()
{
    FILE* input_file = NULL;

    if ((input_file = fopen ("input.txt", "r")) == NULL)
        {
        printf ("Не могу открыть файл\n");
        return 0;
        }

    //long  int NumberOfChars = SizeOfFile (input_file);

    long  int NumberOfChars = Chars_Number(input_file);



    char* text = (char*) calloc (NumberOfChars, sizeof (char));
    assert (text != NULL);

    fread (text, sizeof (char), NumberOfChars, input_file);

    int Number_Of_Lines = NumberOfLines (text, NumberOfChars);

    char** P_Lines = (char**) calloc (Number_Of_Lines, sizeof (char*));

    PutPointers (text, NumberOfChars, P_Lines, Number_Of_Lines);

    qsort (P_Lines, Number_Of_Lines, sizeof (char*), Comparator_Final );

  /*  for (int i = 0; i < Number_Of_Lines; i ++)
    {
      printf ("%c\n", *(P_Lines[i]));
    } */


    PointersOnTheBeginnings(P_Lines, Number_Of_Lines);


    /*for (int i = 0; i < Number_Of_Lines; i ++)
    {
      printf ("%c\n", *(P_Lines[i]));
    }*/

    Output (P_Lines, Number_Of_Lines);

    fclose (input_file);

    free (text);
    free (P_Lines);
}



//------------------------------------------------------------------------------
/*
long int SizeOfFile (FILE* file)  // Вычисление размера файла.
{
	assert (file);

	struct stat stbuf;
	int m = stat (file, &stbuf);

	if ( m!= 0)
			{
					printf("Не могу узнать размер файла %s\n", file);
			}

	return stbuf.st_size;

}
*/
//------------------------------------------------------------------------------

int NumberOfLines (char* text, int size_text)
{
    int i = 0, Number_Of_Strings = 0;

    assert (text != NULL);

    for (i = 0; i < size_text + 1; i++)
    {

        if (text[i] == '\n')
        {
            text[i] = '\0';
	          Number_Of_Strings++;
            if (isspace(text[i+1])) i++;
	      }
    }

    return Number_Of_Strings;
}

//------------------------------------------------------------------------------

void PutPointers (char* text, int size_text, char** P_Lines, int NumberOfLines)
{
    int i = 0, IsNewLine = 0, k = 0;

    assert (text != NULL);

    for (i = 0; i < size_text + 1; i++) {
        if (!isspace(text[i]) && IsNewLine == 0 && isalpha(text [i])) {
	    P_Lines[k] = &text[i];
            k++;
            IsNewLine = 1;
        }

	if (text[i] == '\0')
	    IsNewLine= 0;

    }
}

//------------------------------------------------------------------------------

int CompareChar (char const* left_value, char const* right_value)
{

    assert (left_value != NULL);
    assert (right_value != NULL);

    while ( *(left_value) != '\0' || *(right_value) != '\0' )
    {
    if (tolower (*left_value) < tolower (*right_value))
        return -1;

    if (tolower (*left_value) > tolower (*right_value))
        return 1;

    if (tolower (*left_value) == tolower (*right_value))
        {
        if (*left_value == '\0' || *right_value == '\0')
            return -1;

        left_value++;
        right_value++;
        }
    }
}

//------------------------------------------------------------------------------

int Comparator_Final (void const* left_value_void_ptr, void const* right_value_void_ptr) {
    assert (left_value_void_ptr != NULL);
    assert (right_value_void_ptr != NULL);

    char const** left_value_ptr = (char const**)  left_value_void_ptr;
    char const** right_value_ptr = (char const**) right_value_void_ptr;

    char const* left_value = *left_value_ptr;
    char const* right_value = *right_value_ptr;

    return CompareChar(left_value, right_value);
}

//------------------------------------------------------------------------------

int CompareCharBack (char const* left, char const* right)
{
    assert (left  != NULL);
    assert (right != NULL);

    if (tolower (*left) > tolower (*right))
          {
              return -1;
          }

    if (tolower (*left) < tolower (*right))
          {
              return 1;
          }

    if (tolower (*left) == tolower (*right))
          {
              if (*left == '\0' || *right== '\0')
	            return 1;

            return CompareCharBack (left + 1, right + 1);
          }
}

//------------------------------------------------------------------------------

void PointersOnTheBeginnings ( char** P_Lines_Sort, int size_arr )
{
    int i = 0;
    for (i = 0; i < size_arr; i++)
        {
        while (* (P_Lines_Sort[i] - 1) != '\0')
            P_Lines_Sort[i] = P_Lines_Sort[i] - 1;
        }
}

//------------------------------------------------------------------------------

void Output(char** P_Lines, int NumberOfLines)
{
    FILE* output_file = NULL;

    if ((output_file = fopen ("output.txt", "w")) == NULL)
    {
	  printf ("Возникли проблемы с файлом\n");
    return;
    }

    for (int i = 0; i < NumberOfLines; i++)
        fprintf (output_file, "%s\n", P_Lines[i]);

    fclose (output_file);
}

//------------------------------------------------------------------------------

size_t Chars_Number (FILE* file) {
    assert (file != NULL);

    fseek (file, 0, SEEK_END);

    size_t number_of_chars = ftell (file);

    fseek (file, 0, SEEK_SET);

    return number_of_chars;
}
