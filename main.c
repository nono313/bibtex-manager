/* 
Bibtex Project - Main.c
Maxime B. & Nathan O. (TC03)
maxime.bourgeois@utbm.fr nathan.olff@utbm.fr

Main.c : insert a description here.
*/

#include <bibtexmanager.h>
#include <time.h>

int main(int argc, char** argv)
{		
	AbstractList library, tmpLibrary, libraryDateAuthor, libraryAuthorDate;
	AuthorPublications authorPublication;
	DatePublications datePublications;
	Author tmpAuthor;
	
	char* userAnswer;
	int userDecision = 0;
	
	library = initList(sizeof(Entry));
	tmpLibrary = initList(sizeof(tmpLibrary));
	libraryAuthorDate = initList(sizeof(AuthorPublications));
	libraryDateAuthor = initList(sizeof(DatePublications));
		
	userAnswer = (char*) malloc(500*sizeof(char));
	
	printf("\n== Managing of a bibtex file ==\n");
	
	do
	{		
		do
		{
			printf("Write the name of the bibtex file : ");
			gets(userAnswer);
			
			library = parseBibtexFile(userAnswer);
			printf("\n");
		}while(isEmpty(library));
		
		tmpLibrary = library;
		
		do
		{				
			printf("The insertEntry and removeEntry are done but not for user.\n\n");
			
			printf("If you want to do the 6, do the 1 before.\n");
			printf("If you want to do the 7, do the 2 before.\n\n");
			
			do
			{				
				printf("Which function do you want to use on this bibtex file ?\n");
				printf("1 : sortLibraryAuthorDate\n");
				printf("2 : sortLibraryDateAuthor\n");
				printf("3 : getAuthorReferences\n");
				printf("4 : getYearReferences\n");
				printf("5 : printLibrary\n");
				printf("6 : printAuthorsPublications\n");
				printf("7 : printDatesPublications\n");
				printf("8 : exportLibrary\n");
				printf("9 : exportAuthorsPublications\n");
				printf("10 : exportDatePublications\n");
				printf("11 : removeEntry\n\n");
				
				scanf("%d", &userDecision);
			}while(userDecision < 0 || userDecision > 11);
			
			printf("\n");
			
			switch (userDecision) {
				case 1 :
					libraryAuthorDate = sortLibraryAuthorDate(library);
					
					printf("== Library sorted in AuthorsPublications ==\n\n");
					printf("If you want to print it, use the function  6 : printAuthorsPublications\n\n");
					
					break;

				case 2 :
					libraryDateAuthor = sortLibraryDateAuthor(library);
					printf("== Library sorted in DatesPublications ==\n\n");
					printf("If you want to print it, use the function  7 : printDatesPublications\n\n");					
					break;
					
				case 3 :
					do
					{
						printf("Write the author's first name : ");
						clean_stdin();
						gets(userAnswer);
					}while(strcmp(userAnswer, "") == 0);
					
					tmpAuthor.firstName = (char*) malloc(sizeof(char)*(strlen(userAnswer)+1));
					strcpy(tmpAuthor.firstName, userAnswer);
					
					do
					{
						printf("Write the author's last name : ");
						scanf("%s", userAnswer);
					}while(strcmp(userAnswer, "") == 0);
					
					tmpAuthor.lastName = (char*) malloc(sizeof(char)*(strlen(userAnswer)+1));
					strcpy(tmpAuthor.lastName, userAnswer);
					
					authorPublication = getAuthorPublications(library, tmpAuthor);
					
					if(isEmpty(authorPublication.publicationsList))
					{
						printf("\n\t\t%s %s\n", tmpAuthor.firstName, tmpAuthor.lastName);
						printf("No publication for this author.\n\n");
					}
					else
						printAuthorPublications(authorPublication);
				
					break;

				case 4 :					
					do
					{
						printf("Write the year : ");
						clean_stdin();
						gets(userAnswer);
					}while(strcmp(userAnswer, "") == 0);				
					
					datePublications = getDatePublications(library, userAnswer);
					
					if(isEmpty(datePublications.publicationsList))
					{
						printf("\n\t\t%s\n\n", datePublications.year);
						printf("No publication for this year.\n\n");
					}
					else
						printDatePublications(datePublications);
						
					break;
					
				case 5 :
					printLibrary(library);
					break;

				case 6 :
					if(isEmpty(libraryAuthorDate))
					{
						printf("The list of AuthorDatePublications is empty.\n");
						do {
							printf("Do you want to create it with the sortLibraryAuthorDate function ? (Y/N)\n");
							clean_stdin();
							userAnswer[0] = getchar();
						} while(userAnswer[0] != 'Y' && userAnswer[0] != 'y' && userAnswer[0] != 'N' && userAnswer[0] != 'n');
						if(userAnswer[0] == 'Y' || userAnswer[0] == 'y')
						{
							printListAuthorPublications(libraryAuthorDate);
						}
					}
					else
						printListAuthorPublications(libraryAuthorDate);
					break;
					
				case 7 :					
					if(isEmpty(libraryAuthorDate))
					{
						printf("The list of DateAuthorPublications is empty.\n");
						do {
							printf("Do you want to create it with the sortLibraryDateAuthor function ? (Y/N)\n");
							clean_stdin();
							userAnswer[0] = getchar();
						} while(userAnswer[0] != 'Y' && userAnswer[0] != 'y' && userAnswer[0] != 'N' && userAnswer[0] != 'n');
						if(userAnswer[0] == 'Y' || userAnswer[0] == 'y')
						{
							printListDatePublications(libraryDateAuthor);
						}
					}
					else
						printListDatePublications(libraryDateAuthor);	
					break;
				case 8 :
					do
					{
						printf("Write the name of the HTML file in which the Library will be exported : ");
						clean_stdin();
						gets(userAnswer);
					}while(strcmp(userAnswer, "") == 0);
			
					exportToHTML(library,userAnswer);
					printf("The Library has been exported in %s\n", userAnswer);
					
					break;
				case 9 :
					do
					{
						printf("Write the name of the HTML file in which the AuthorsPublications will be exported : ");
						clean_stdin();
						gets(userAnswer);
					}while(strcmp(userAnswer, "") == 0);
					if(isEmpty(libraryAuthorDate))
					{
						libraryAuthorDate = sortLibraryAuthorDate(library);
					}
					exportAuthorsPublications(libraryAuthorDate,userAnswer);
					printf("The list of AuthorPublications has been exported in %s\n", userAnswer);
					
					break;

				case 10 :
					do
					{
						printf("Write the name of the HTML file in which the DatePublications will be exported : ");
						clean_stdin();
						gets(userAnswer);
					}while(strcmp(userAnswer, "") == 0);
					if(isEmpty(libraryDateAuthor))
					{
						libraryDateAuthor = sortLibraryAuthorDate(library);
					}
					exportDatePublications(libraryDateAuthor,userAnswer);
					printf("The list of DatePublications has been exported in %s\n", userAnswer);
					
					break;	
				case 11 :
					printf("Pleas give the key of the Entry you want to remove : ");
					scanf("%s", userAnswer);
					if(checkEntry(library, userAnswer))
					{
						removeEntry(library, userAnswer);
						printf("== The Entry \"%s\" has been deleted. ==\n\n", userAnswer);
						if(!isEmpty(libraryDateAuthor))
						{
							libraryDateAuthor = sortLibraryAuthorDate(library);
						}
						if(!isEmpty(libraryAuthorDate))
						{
							libraryAuthorDate = sortLibraryAuthorDate(library);
						}
					}
					else
						printf("== The Entry \"%s\" doesn't exist in the library ==\n\n", userAnswer);					
					break;
			}
		 	
		 	do
			{
				printf("Do you want to do an other operation on this file ? (Y/N) ");
				clean_stdin();
				scanf("%s", userAnswer);
			}while(strcmp(stringToUpper(userAnswer), "Y") != 0 && strcmp(stringToUpper(userAnswer), "N") != 0);
		}while(strcmp(stringToUpper(userAnswer), "Y") == 0);
		freeDatePublications(libraryDateAuthor);
		freeAuthorsPublications(libraryAuthorDate);
		freeLibrary(library, TRUE);		
		do
		{
			printf("Do you want to open a new file ? (Y/N) ");
			scanf("%s", userAnswer);
		}while(strcmp(stringToUpper(userAnswer), "Y") != 0 && strcmp(stringToUpper(userAnswer), "N") != 0);
						
		printf("\n");
	}
	while(strcmp(stringToUpper(userAnswer), "Y") == 0);
			
	free(userAnswer);
	
	return EXIT_SUCCESS;
}
