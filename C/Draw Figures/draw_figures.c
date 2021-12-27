#include <stdio.h>
int drawRectangle();
int drawTriangle();

int main(){
    int choice=-1;
    int length,width;
    int size;
    char character;

    do {
    printf("Enter 1(rectangle), 2(triangle), 3(other), 0(quit): ");
    scanf("%d",&choice);

        if(choice == 1){

                drawRectangle();

        }
        else if(choice == 2){
                drawTriangle();

        }
        else if(choice == 3){
            int i, j, line = 12;
            for (i = line/2; j <= line; i = j+2) {
                for (j = 1; j < line-i; j = j+2)
                    printf(" ");
                for (j = 1; j <= i; j++)
                    printf("*");
                for (j = 1; j <= line-i; j++)
                    printf(" ");
                for (j = 1; j <= i-1; j++)
                    printf("*");
                printf("\n");
            }
            for (i = line; i >= 0; i--) {
                for (j = i; j < line; j++)
                    printf(" ");
                for (j = 1; j <= ((i * 2) - 1); j++)
                    printf("*");
                printf("\n");
            }
        }
        else if (choice==0){

        } else
            printf("Invalid choice.\n");
    } while(choice!=0);
    printf("Bye Bye.");

    return 0;

}



int drawRectangle() {
    char character;
    int length;
    int width;
    printf("Enter character, width and length: ");
    scanf(" %c %d %d", &character, &width, &length);
    if((character == '*' ||character == '%'||character == '#') && (length>0 && width>0)){
        int i,j;
        for(i=0; i<width; i++) {
            for (j = 0; j < length; j++) {
                printf("%c",character);
            }
            printf("\n");
        }
    } else {
        printf("Invalid data provided.\n");
    }

}
int drawTriangle(){
    int size;
    char character;
    printf("Enter character and size: ");
    scanf(" %c %d", &character, &size);

     if((character == '*' ||character == '%'||character == '#') && size>0){
         int i, j, k;
         for (i=0; i < size; i++) {
             for ( j = size - 1 - i; j > 0; j--) {
                 printf(" ");
             }
             for ( k = 0; k < (2 * i) + 1; k++) {
                 printf("%c", character);
             }
             printf("\n");
         }
    }
    else {
         printf("Invalid data provided.\n");
    }


}
