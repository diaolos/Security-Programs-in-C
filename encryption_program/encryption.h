#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *one_time_pad_encr(char *text, char *key)
{
    int i;
    char *cipher;
    cipher = malloc(strlen(text) * sizeof(char));
    printf("Encoding.......... \n");
    for (i = 0; i < strlen(text); i++)
    {
        cipher[i] = (char) text[i] ^  (char) key[i];
    }

    return cipher;
}

char *one_time_pad_decr(char *cipher, char *key)
{
    int i;
    char *text;
    text = malloc(strlen(cipher) * sizeof(char));
    printf("%s\n", key);
    for (i = 0; i < strlen(text); i++)
    {
        text[i] = (char) cipher[i] ^ (char) key[i];
    }
    printf("Your Decrypted text is: %02x \n", cipher);

    return text;
}

char *rail_fence_encr(char plain[100], int rail)
{
    char fence[rail][100];
    char *cipher = malloc(strlen(plain) * sizeof(char));
    int i, j, k, l;
    // rail making
    i = 0;
    j = 0;
    for (k = 0; k < rail; k++)
    {
        memset(fence[k], '_', strlen(plain));
    }
    printf("%d \n", strlen(plain));

    for (i = 0; i < strlen(plain); i++)
    {

        if (i == 0)
        {
            fence[0][0] = plain[i];
            j++;
        }
        else
        {
            while (j < rail)
            {
                fence[j][i] = plain[i];
                j++;
                i++;
            }
            j = j - 2;
            while (j >= 0)
            {
                fence[j][i] = plain[i];
                j--;
                i++;
            }
            j = 1;
            i--;
        }
    }

    printf("\n");
    for (i = 0; i < rail; i++)
    {
        printf("%s", fence[i]);
        printf("\n");
    }
    i = 0;
    j = 0;
    l = 0;
    // making the cipher
    for (i = 0; i < rail; i++)
    {
        for (j = 0; j < strlen(plain); j++)
        {
            if (fence[i][j] != '_' && fence[i][j] != 0)
            {
                cipher[l] = fence[i][j];
                l++;
            }
        }
    }

    return cipher;
}

char *rail_fence_decr(char *cipher, int rail)
{
    char fence[rail][strlen(cipher)];
    char *plain = malloc(strlen(cipher) * sizeof(char));
    int i, j, k, l;
    for (i = 0; i < rail; i++)
    {
        memset(fence[i], 0, strlen(cipher));
    }
    i = 0;
    k = 0;
    j = 0;
    while (j < strlen(cipher))
    {
        if (k == 0)
        {
            fence[0][j] = cipher[i];
            i++;
            k++;
            j++;
        }
        else
        {
            while (k < rail)
            {
                if (j >= strlen(cipher))
                    break;
                fence[k][j] = '-';
                k++;
                j++;
            }
            k = k - 2;
            while (k > 0)
            {
                if (j >= strlen(cipher))
                    break;
                fence[k][j] = '-';
                k--;
                j++;
            }
        }
    }
    l = 0;
    for (i = 0; i < rail; i++)
    {
        for (j = 0; j < strlen(cipher); j++)
        {
            if (fence[i][j] == cipher[l] && i == 0)
            {
                l++;
            }
            else if (fence[i][j] == '-')
            {
                fence[i][j] = cipher[l];
                l++;
            }
        }
    }
    i = 0;
    k = 0;
    j = 0;

    while (i < strlen(cipher))
    {
        if (i == 0)
        {
            plain[i] = fence[0][0];
            k++;
            j++;
            i++;
        }
        else
        {
            while (k < rail)
            {
                plain[i] = fence[k][j];
                k++;
                j++;
                i++;
            }
            k = k - 2;
            while (k >= 0)
            {
                plain[i] = fence[k][j];
                k--;
                j++;
                i++;
            }
            k = 1;
        }
    }
    return plain;
}

char *beaufort_encr(char *plain, char *key)
{
    int i, j, k, l;
    char tabl[26][26];
    int alp = 65;
    char* newkey = malloc(strlen(plain) * sizeof(char));
    char *cipher = malloc(strlen(plain) * sizeof(char));

    j=0;
    for(i = 0; i < strlen(plain); i++){
            if(j >= strlen(key)) j=0;
            newkey[i] = key[j];
        j++;
    }
    
    // make the tablau

    for (i = 0; i < 26; i++)
    {
        k = 0;
        for (j = 0; j < 26; j++)
        {
            if (alp + k <= 90)
            {
                tabl[i][j] = alp + k;
                k++;
            }
            else
            {
                tabl[i][j] = alp + (k - 26);
                k++;
            }
        }
        alp++;
    }
    for (i = 0; i < strlen(plain); i++)
    {
        j = (int)plain[i] -65;
        for (k = 0; k < 26; k++)
        {
            
                if (tabl[k][j] == newkey[i])
                {
                    cipher[i] = tabl[k][0];
                    break;
                }
            
        }
    }

    // travel through
    // return cipher
    return cipher;
    
}

char *beaufort_decr(char *cipher, char *key)
{
    int i, j, k, l;
    char tabl[26][26];
    int alp = 65;
    char* newkey = malloc(strlen(cipher) * sizeof(char));
    char *plain = malloc(strlen(cipher) * sizeof(char));

    // make the new key
    j=0;
    for(i = 0; i < strlen(cipher); i++){
            if(j >= strlen(key)) j=0;
            newkey[i] = key[j];
        j++;
    }
    // make the tablau

    for (i = 0; i < 26; i++)
    {
        k = 0;
        for (j = 0; j < 26; j++)
        {
            if (alp + k <= 90)
            {
                tabl[i][j] = alp + k;
                k++;
            }
            else
            {
                tabl[i][j] = alp + (k - 26);
                k++;
            }
        }
        alp++;
    }
    for (i = 0; i < strlen(cipher); i++)
    {
        j = (int)cipher[i] -65;
        for (k = 0; k < 26; k++)
        {
            
                if (tabl[k][j] == newkey[i])
                {
                    plain[i] = tabl[k][0];
                    break;
                }
            
        }
    }

    // travel through
    // return cipher
    return plain;
    
    return 0;
}
char* affine_encr(char* plain){
    char* cipher = malloc(strlen(plain) * sizeof(char));
    int a = 11; 
    int b = 19;
    int m = 26;
    int key;
    for(int i = 0; i < strlen(plain); i++){
        key = (int)plain[i] - 65;
        cipher[i] = 65 + ((a * key + b)% m);
    }
    return cipher;
}

char* affine_decr(char* cipher){
    char* plain = malloc(strlen(cipher) * sizeof(char));
    int a = 11; 
    int b = 19;
    int m = 26;
    int key;
    int mod; 
    
    for (int x=1; x<m; x++) {
       if ((a*x) % m == 1) {
            a = x;
            break;
       }
    }
    for(int i = 0; i < strlen(cipher); i++){
        key = (int)cipher[i] - 65;
        plain[i] = 65 + ((a)* ((key - b)% m));
    }
    return plain;
}