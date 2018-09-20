#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//functions
void TranslateEN();
void TranslateLT();
void InsertEN(char *newWordEN, char *newWordLT);
void InsertLT(char *newWordLT, char *newWordEN);


FILE *fp; //file pointer

int main() {
	char descision = 'Y';
	char word[20];
	int option;

	do {
		printf("1-Translate from English to Lithuanian.\n");
		printf("2-Translate from Lithuanian to English.\n");
		scanf("%d", &option);

		switch (option) {//switches by default break
		case 1: printf("Enter your English word: ");
				scanf("%s", &word);
				TranslateEN(word);
				break;
		case 2: printf("Enter your Lithuanian word: ");
				scanf("%s", &word);
				TranslateLT(word);
				break;
		default: printf("There is no such option.\n");
		break;
		}
		printf("\nAnything else?\n Y/N \n");
		scanf(" %c", &descision);
	} while (descision == 'Y' || descision == 'y');


}

void TranslateEN(char *word) { // translates from english to lithuanian, reads from file and
	char tmpResult[20], allowance = 'Y',newWordEN[20];
	int compare, counter = 0, position;
	fp = fopen("DictionaryEN", "r+");

	fscanf(fp, "%s", tmpResult);
	compare = strcmp(tmpResult, word);
	counter++;
	if (compare == 0) position = counter;
	else {
		while (!feof(fp)) {
			fscanf(fp, "%s", tmpResult);
			compare = strcmp(tmpResult, word);
			counter++;
			if (compare == 0) {
				position = counter;
				break;
			}
		}
	}
	if (compare != 0) { // if word doesn't exist, it gives option to translate your word and write to dictionary
		printf("Your word does not exist. It will be written to the dictionary\n");
		printf("Please enter the translation for the word: ");
		scanf("%s", newWordEN);
		InsertEN(word, newWordEN);
	}
	else { // closes pointer
		counter = 0;
		fclose(fp);
		fp = fopen("DictionaryLT", "r+");

		fscanf(fp, "%s", tmpResult);
		counter++;
		if (position == counter && allowance == 'Y') { // prints translated word
			printf("The translation to the word %s is %s", word, tmpResult);
			allowance = 'N';
		}
		else {
			while (counter < position) {
				fscanf(fp, "%s", tmpResult);
				counter++;
			}
		}
		if (counter == position && allowance == 'Y')	printf("The translation to the word %s is %s", word, tmpResult);
		fclose(fp);
	}
}

void TranslateLT(char *word) { // same as to translate to lithuanian
	char tmpResult[20], allowance = 'Y',newWordLT[20];
	int compare, counter = 0, position;
	fp = fopen("DictionaryLT", "r");

	fscanf(fp, "%s", tmpResult);
	compare = strcmp(tmpResult, word);
	counter++;
	if (compare == 0) {
		position = counter;
		printf("%d", compare);
	}
	else {
		while (!feof(fp)) {
			fscanf(fp, "%s", tmpResult);
			compare = strcmp(tmpResult, word);
			counter++;
			if (compare == 0)  {
				position = counter;
				break;
			}
		}
	}
	if (compare != 0) {
		printf("Your word does not exist. It will be written to the dictionary\n");
		printf("Please enter the translation for the word: ");
		scanf("%s", newWordLT);
		InsertLT(newWordLT,word);
	}
	else {
		counter = 0;
		fclose(fp);
		fp = fopen("DictionaryEN", "r");

		fscanf(fp, "%s", tmpResult);
		counter++;
		if (position == counter && allowance == 'Y') {
			printf("The translation to the word %s is %s", word, tmpResult);
			allowance = 'N';
		}
		else {
			while (counter < position) {
				fscanf(fp, "%s", tmpResult);
				counter++;
			}
		}
		if (counter == position && allowance == 'Y')	printf("The translation to the word %s is %s", word, tmpResult);
	}
	fclose(fp);
}

void InsertEN(char *newWordEN,char *newWordLT) { //function to insert word to dictionary
	fp = fopen("DictionaryEN", "a");
	fprintf(fp, "\n%s", newWordEN);
	fclose(fp);
	fp = fopen("DictionaryLT", "a");
	fprintf(fp, "\n%s", newWordLT);
	fclose(fp);
	printf("The word has been succesfully inserted.\n");
}
void InsertLT(char *newWordLT, char *newWordEN) {
	fp = fopen("DictionaryLT", "a");
	fprintf(fp, "\n%s", newWordLT);
	fclose(fp);
	fp = fopen("DictionaryEN", "a");
	fprintf(fp, "\n%s", newWordEN);
	fclose(fp);
	printf("The word has been succesfully inserted.\n");
}
