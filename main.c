#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define SIZE 97

char *hashtable[SIZE];

int string_hash(char *s) {
    char c;
    int p = 31, m = 97;
    int hash_value = 0, p_pow = 1;

    while (c = *s++) {
        hash_value = (hash_value + (c - 'a' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }
    return (hash_value);
}

void inserir(char *s) {
    int posicao = string_hash(s);
    int inicial = posicao;
    char *string = (char *) malloc(strlen(s));
    strcpy(string, s);

    while (hashtable[posicao] != NULL) {
        posicao++;
        if (posicao > 97) posicao = 0;
        if (posicao == inicial) return;
    }

    hashtable[posicao] = string;

}

void remover(char *s) {
    int posicao = string_hash(s);
    int initial = posicao;
    while (hashtable[posicao] != NULL && strcmp(s, hashtable[posicao]) != 0) {
        posicao++;
        if (posicao > SIZE) posicao = 0;
        if (posicao == initial) return;
        if (hashtable[posicao] == NULL) return;
    }

    hashtable[posicao] = NULL;
    int aux = posicao;
    int hash;
    posicao++;
    if (posicao > SIZE) posicao = 0;
    while (hashtable[posicao] != NULL) {
        hash = string_hash(hashtable[posicao]);
        if (hash >= initial && hash <= aux) {
            hashtable[aux] = hashtable[posicao];
            hashtable[posicao] = NULL;
            aux = posicao;
        }
        posicao++;
        if (posicao > SIZE) posicao = 0;
        if (posicao == initial) return;
    }
}

int buscar(char *s) {
    int posicao = string_hash(s);
    int initial = posicao;
    while (hashtable[posicao] != NULL && strcmp(s, hashtable[posicao]) != 0) {
        posicao++;
        if (posicao > SIZE) posicao = 0;
        if (posicao == initial) return -1;
        if (hashtable[posicao] == NULL) return -1;
    }
    return posicao;
}

void print() {
    for (int i = 0; i < SIZE; ++i) {
        if (hashtable[i] != NULL) {
            printf("%d -> %s \n", i, hashtable[i]);
        }
    }
    printf("\n\n");
}

int main() {
    int aux;
    char s[255];

    strcpy(s, "asdas");
    inserir(s);
    print();

    strcpy(s, "asdas");
    inserir(s);
    print();

    strcpy(s, "bdc");
    inserir(s);
    print();

    strcpy(s, "gfb");
    inserir(s);
    print();

    strcpy(s, "ergf");
    inserir(s);
    print();

    strcpy(s, "asdas");
    aux = buscar(s);
    printf("%d -> %s\n", aux, hashtable[aux]);
    print();

    strcpy(s, "asdas");
    remover(s);
    print();
}
