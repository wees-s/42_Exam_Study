#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Função para verificar se a string resultante é válida (ignorando espaços)
bool isValid(char* s) {
    int count = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == '(') count++;
        else if (s[i] == ')') {
            count--;
            if (count < 0) return false;
        }
    }
    return count == 0;
}

// Funçao de Backtracking
void solve(char* s, int index, int remOpen, int remClose) {
    // Caso base: se processamos todos os caracteres e as remoções terminaram
    if (index == strlen(s)) {
        if (remOpen == 0 && remClose == 0 && isValid(s)) {
            printf("\"%s\"\n", s);
        }
        return;
    }

    char originalChar = s[index];

    // Opção 1: Tentar remover o caractere atual (substituir por espaço)
    if (originalChar == '(' && remOpen > 0) {
        s[index] = ' ';
        solve(s, index + 1, remOpen - 1, remClose);
        s[index] = originalChar; // Backtrack
    } 
    else if (originalChar == ')' && remClose > 0) {
        s[index] = ' ';
        solve(s, index + 1, remOpen, remClose - 1);
        s[index] = originalChar; // Backtrack
    }

    // Opção 2: Manter o caractere atual (ou se for um espaço/letra, apenas pular)
    // Para evitar duplicatas em sequências como "(((", só removemos o primeiro
    // Se decidirmos não remover, apenas seguimos adiante.
    solve(s, index + 1, remOpen, remClose);
}

int main() {
    char str[] = "(()()))()))"; // Exemplo de entrada
    int remOpen = 0, remClose = 0;
    int balance = 0;

    // Passo 1: Calcular o mínimo de ( e ) que devem sair
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '(') {
            balance++;
        } else if (str[i] == ')') {
            if (balance > 0) balance--;
            else remClose++;
        }
    }
    remOpen = balance;

    printf("Entrada: %s\nPossibilidades:\n", str);
    solve(str, 0, remOpen, remClose);

    return 0;
}