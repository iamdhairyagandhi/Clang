#include <stdio.h>
#include <string.h>
#include "document.h"

void replace_text_in_line(const char* line, const char* target, const char* replacement, char* replace_line);

int init_document(Document* doc, const char* name)
{

	if (doc == NULL || name == NULL || strlen(name) >= MAX_STR_SIZE)
	{
		return FAILURE;
	}
	else
	{
		strcpy(doc->name, name);
		return SUCCESS;
	}
}
int add_paragraph_after(Document* doc, int paragraph_number)
{
	Paragraph new_paragraph;
	int i, num_to_add_new = paragraph_number;

	new_paragraph.number_of_lines = 0;
	if (doc == NULL || doc->number_of_paragraphs == MAX_PARAGRAPHS ||
		paragraph_number > doc->number_of_paragraphs)
	{
		return FAILURE;
	}
	/* checking if a paragraph already exists at the num_to_add_new position,
 *     if so, shifting paragraphs below to make space for the new paragraph. */
	if (num_to_add_new < doc->number_of_paragraphs)
	{
		for (i = doc->number_of_paragraphs; i >= num_to_add_new; i--)
		{
			doc->paragraphs[i] = doc->paragraphs[i - 1];
		}
	}
	doc->paragraphs[num_to_add_new] = new_paragraph;
	doc->number_of_paragraphs++;
	return SUCCESS;
}

int reset_document(Document* doc)
{
	if (doc != NULL)
	{
		doc->number_of_paragraphs = 0;
		return SUCCESS;
	}
	else
	{
		return FAILURE;
	}
}

int print_document(Document* doc)
{
	int i, j;
	if (doc == NULL)
	{
		return FAILURE;
	}
	printf("Document name: \"%s\"\n", doc->name);
	printf("Number of Paragraphs: %d\n", doc->number_of_paragraphs);
	for (i = 0; i < doc->number_of_paragraphs; i++)
	{
		/*
 *         printf("i: %d\n", i);
 *                 printf("Num Lines: %d\n", doc->paragraphs[i].number_of_lines);
 *                         */
		for (j = 0; j < doc->paragraphs[i].number_of_lines; j++)
		{
			/*printf("j: \n",j);*/
			printf("%s\n", doc->paragraphs[i].lines[j]);
		}
		if (i != (doc->number_of_paragraphs - 1))
			printf("\n");
	}
	return SUCCESS;
}

int add_line_after(Document* doc, int paragraph_number, int line_number, const char* new_line)
{
	int i = 0;
	/*
 *           printf("Add line after method 1\n");
 *           */
	if (doc == NULL)
	{
		return FAILURE;
	}
	if (new_line == NULL)
	{
		return FAILURE;
	}

	if (paragraph_number > doc->number_of_paragraphs, paragraph_number < 0)
	{
		return FAILURE;
	}

	if (doc->paragraphs[paragraph_number - 1].number_of_lines == MAX_PARAGRAPH_LINES)
	{
		return FAILURE;
	}

	if (line_number < 0 || doc->paragraphs[paragraph_number - 1].number_of_lines < line_number)
	{
		return FAILURE;
	}

	for (i = doc->paragraphs[paragraph_number - 1].number_of_lines; i > line_number; i--)
	{
		strcpy(doc->paragraphs[paragraph_number - 1].lines[i + 1], doc->paragraphs[paragraph_number - 1].lines[i]);
	}

	strcpy(doc->paragraphs[paragraph_number - 1].lines[line_number], new_line);
	doc->paragraphs[paragraph_number - 1].number_of_lines++;
	return SUCCESS;
}

int get_number_lines_paragraph(Document* doc, int paragraph_number, int* number_of_lines)
{
	if (doc == NULL)
	{
		return FAILURE;
	}
	if (number_of_lines == NULL)
	{
		return FAILURE;
	}
	if (paragraph_number <= doc->number_of_paragraphs)
	{
		*number_of_lines = doc->paragraphs[paragraph_number].number_of_lines;
		return SUCCESS;
	}
	return FAILURE;
}

int append_line(Document* doc, int paragraph_number, const char* new_line)
{
	int num_lines = 0;
	if (doc == NULL || new_line == NULL)
	{
		return FAILURE;
	}
	else
	{
		num_lines = doc->paragraphs[paragraph_number - 1].number_of_lines;
		if (num_lines < MAX_PARAGRAPH_LINES && paragraph_number <= MAX_PARAGRAPHS)
		{
			add_line_after(doc, paragraph_number, num_lines, new_line);
		}
		return SUCCESS;
	}
}

int remove_line(Document* doc, int paragraph_number, int line_number)
{

	int i = 0;

	if (doc == NULL)
	{
		return FAILURE;
	}
	if (paragraph_number > doc->number_of_paragraphs)
	{
		return FAILURE;
	}

	if (doc->paragraphs[paragraph_number - 1].number_of_lines < line_number)
	{
		return FAILURE;
	}
	for (i = line_number - 1; i < doc->paragraphs[paragraph_number - 1].number_of_lines; i++)
	{
		/* printf("i: %d\n",i);
 *         */
		strcpy(doc->paragraphs[paragraph_number - 1].lines[i], doc->paragraphs[paragraph_number - 1].lines[i + 1]);
	}
	(doc->paragraphs[paragraph_number - 1].number_of_lines)--;
	return SUCCESS;
}

int load_document(Document* doc, char data[][MAX_STR_SIZE + 1], int data_lines)
{
	int i = 0, j = 1;
	if (!data_lines || doc == NULL || data == NULL)
	{
		return FAILURE;
	}
	else
	{
		add_paragraph_after(doc, 0);
		for (i = 0; i < data_lines; i++)
		{
			if (strcmp(data[i], "") == 0)
			{
				add_paragraph_after(doc, j++);
			}
			else
				append_line(doc, j, data[i]);
		}
		return SUCCESS;
	}
}

int replace_text(Document* doc, const char* target, const char* replacement)
{
	int line_num, paragraph_num, i, j;
	char replace_line[MAX_STR_SIZE + 1]; /* line with replaced text */

	if (doc == NULL || target == NULL || replacement == NULL)
	{
		return FAILURE;
	}
	for (i = 0; i < doc->number_of_paragraphs; i++)
	{
		for (j = 0; j < doc->paragraphs[i].number_of_lines; j++)
		{
			/* replacing text in the doc->paragraphs[i].lines[j] line and storing
 *              * the line with the replaced text in replace_line */
			replace_text_in_line(doc->paragraphs[i].lines[j], target, replacement,
				replace_line);
			/* setting the current line to line with replaced text */
			strcpy(doc->paragraphs[i].lines[j], replace_line);
		}
	}
	return SUCCESS;
}

/* replaces appropriate text in a single line */
void replace_text_in_line(const char* line, const char* target, const char* replacement, char* replace_line)
{
	int replace_line_index = 0, i;
	char temp_single_char_str[2];

	for (i = 0; i < strlen(line); i++)
	{
		/* checking if target is present in the part of the line from index i and
 *          * that substring pointer is equal to the pointer of the part of the
 *                   * line at index i(&line[i]). */
		if (strstr(&line[i], target) == &line[i])
		{
			/* since the target string is found, the replacement string is copied
 *             in the replace line and the target text from the line is skipped,
 *             by manually increasing the character index(i, gives the line[i],
 *             the current character in the line we are processing/using in the loop)
 *             by the length of the target string - 1(since the for loop increments the
 *             i by 1 also). So, the next run of the loop the part of the line from
 *             line[i] will represent the character/line after the target word,
 *             essentially, acheiving the goal of skipping the target word. Also for
 *             a similar reason replace_line_index is also incremented by length of
 *             the replacement. */
			strcpy(&replace_line[replace_line_index], replacement);
			replace_line_index += strlen(replacement);
			i += strlen(target) - 1;
		}
		else
		{
			/* the current character of the line is copied into the replace_line
 *              * and replace_line_index is incremented. */
			replace_line[replace_line_index] = line[i];
			replace_line_index++;
		}
	}
	replace_line[replace_line_index] = '\0';
}

int highlight_text(Document* doc, const char* target)
{
	char result[MAX_STR_SIZE + 1] = "";

	if (doc == NULL || target == NULL)
	{
		return FAILURE;
	}
	else
	{

		strcat(result, HIGHLIGHT_START_STR);
		strcat(result, target);
		strcat(result, HIGHLIGHT_END_STR);

		replace_text(doc, target, result);
		return SUCCESS;
	}
}
int remove_text(Document* doc, const char* target)
{

	if (doc == NULL || target == NULL)
	{
		return FAILURE;
	}
	else
	{
		replace_text(doc, target, "");
		return SUCCESS;
	}
}
int checkForBlank(char* str) {
	int j, lineBlank = 1;;

	for (j = 0; str[j]; j++) {
		if (!isspace(str[j])) {
			lineBlank = 0;
			break;
		}
	}
	return lineBlank;
}
int load_file(Document* doc, const char* filename) {
	int para_num = 0;
	FILE* in = fopen(filename, "r");
	int add_para_bool = 0;
	int append_line_bool = 0;
	char line[100 + 1];
	if (doc == NULL) {
		return FAILURE;
	}
	if (filename == NULL) {
		return FAILURE;
	}
	if (in == NULL) {
		return FAILURE;
	}

	if (add_paragraph_after(doc, para_num) == FAILURE) {
		return FAILURE;
	}
	para_num++;
	while (fgets(line, 100 + 1, in)) {
		line[strlen(line) - 1] = '\0';
		if (checkForBlank(line)) {
			if (add_paragraph_after(doc, para_num) == FAILURE) {
				return FAILURE;
			}

			para_num++;
		}
		else {
			if (append_line(doc, para_num, line) == FAILURE) {
				return FAILURE;
			}
		}
	}
	fclose(in);
	return SUCCESS;
}
/*int load_file(Document* doc, const char* filename)
{
	FILE* file = fopen(filename, "r");
	char input[MAX_STR_SIZE + 1];
	int paragraph = 0, ispresent = 0;

	if (doc == NULL || filename == NULL || file == NULL)
	{
		return FAILURE;
	}
	else
	{
		if (!ispresent)
		{
			ispresent++;
			add_paragraph_after(doc, paragraph);
			printf("Paragraph_num :%d", paragraph);
			fgets(input, MAX_STR_SIZE + 1, file);
			while (!feof(file))
			{
				input[strlen(input) - 1] = '\0';
				if (input[0] == '\0' || input[0] == '\n')
				{
					paragraph++;
					add_paragraph_after(doc, paragraph);
				}
				else
				{

					append_line(doc, paragraph + 1, input);
				}
				fgets(input, MAX_STR_SIZE + 1, file);
			}
		}

		if (ispresent)
		{
			fgets(input, MAX_STR_SIZE + 1, file);
			while (!feof(file))
			{

				if (input[0] == '\0' || input[0] == '\n')
				{
					add_paragraph_after(doc, 0);
				}
				else
				{
					input[strlen(input) - 1] = '\0';
					append_line(doc, 1, input);
				}
				fgets(input, MAX_STR_SIZE + 1, file);
			}
		}
	}
	fclose(file);
	return SUCCESS;
}
*/
int save_document(Document* document, const char* filename)
{
	FILE* file = fopen(filename, "w");
	int para, line, nextline_printed = 0;

	if (document == NULL || filename == NULL || file == NULL) {
		return FAILURE;
	}
	for (para = 0; para < document->number_of_paragraphs; para++)
	{
		for (line = 0; line < document->paragraphs[para].number_of_lines; line++)
		{
			fputs(document->paragraphs[para].lines[line], file);
			fputs("\n", file);
		}
		if (nextline_printed)
		{
			if (para + 1 < document->number_of_paragraphs &&
				document->paragraphs[para + 1].number_of_lines != 0)
			{
				fputs("\n", file);
			}
		}

		if (!nextline_printed)
		{
			nextline_printed++;
			if (document->paragraphs[0].number_of_lines != 0 &&
				document->number_of_paragraphs > 1)
			{
				fputs("\n", file);
			}
		}
	}
	fclose(file);
	return SUCCESS;
}

