#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define ENC 	"/home/frank/Desktop/crypto/lab 10 /enc.txt"
#define DEC	 	"/home/frank/Desktop/crypto/lab 10 /dec.txt"
#define PLAIN	"/home/frank/Desktop/crypto/lab 10 /plain.txt"

#define N 256   // 2^8
void swap(unsigned char *a, unsigned char *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
int KSA(char *key, unsigned char *S) {
    int len = strlen(key);
    int j = 0;
    for(int i = 0; i < N; i++)
        S[i] = i;
        
    for(int i = 0; i < N; i++) {
        j = (j + S[i] + key[i % len]) % N;

        swap(&S[i], &S[j]);
    }
    return 0;
}
int PRGA(unsigned char *S, char *plaintext, unsigned char *ciphertext) {

    int i = 0;
    int j = 0;

    for(size_t n = 0, len = strlen(plaintext); n < len; n++) {
        i = (i + 1) % N;
        //printf("???%d???\n",i);
        j = (j + S[i]) % N;
		//printf("s[i]= %d >>>%d<<<\n",S[i],j);
        swap(&S[i], &S[j]);
        
        int rnd = S[(S[i] + S[j]) % N];
        //printf(">>>%c<<<",plaintext[0]);
        ciphertext[n] = rnd ^ plaintext[n];
        //printf(">>>%c<<<",plaintext[0]);
       
    }

    return 0;
}

int RC4(char *key, char *plaintext, unsigned char *ciphertext) {

    unsigned char S[N];
    KSA(key, S);

    PRGA(S, plaintext, ciphertext);

    return 0;
}

int main() {

	FILE *file;
	FILE *file_a;
	FILE *file_b;
	FILE *file_c;
	file = (fopen(PLAIN, "r"));
	file_a = (fopen(ENC, "w"));
	file_b = (fopen(ENC, "r"));
	file_c = (fopen(DEC, "w"));

	char data[400];
	
	fscanf(file, "%s ",data); 
	fclose(file);
	char key[] = "khuslen";
	
	printf("Нууцлах текст: %s\nНууцлах түлхүүр: %s\n",data,key);
	
    unsigned char *ciphertext = malloc(sizeof(int) * strlen(data));

    RC4(key, data, ciphertext);

	int count = 0;
	
	printf("Нууцласан текст 16тс: "); 
    for(size_t i = 0, len = strlen(data); i < len; i++)
        {
			printf("%X ", ciphertext[i]);
			
			fprintf(file_a, "%d,",ciphertext[i]);
			count++;
		}
		fclose(file_a);
		printf("\n");
	
	int  number[count];	
	char encData[count];
	int i;

    if (file_b == NULL){
        printf("Error Reading File\n");
        exit (0);
    }
    for (i = 0; i < count; i++){
        fscanf(file_b, "%d,", &number[i] );
    }
    for (i = 0; i < count; i++){
        encData[i] = number[i];
    }
		
	unsigned char *deciphertext = malloc(sizeof(int) * count);
	
	RC4(key, encData, deciphertext);
	
	for(size_t k = 0, len = strlen(encData); k < len; k++)
        {
			printf("%c", deciphertext[k]);
			fprintf(file_c, "%c",deciphertext[k]);
		}	
    return 0;
}
