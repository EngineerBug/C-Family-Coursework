#include "pig.h"

char * pig(char*);
bool isVowel(char);

/**
 * Will translate a word to pig latin
 * 
 * If the first letter is a vowel, it will add "way" to the end of the word.
 * Else it will move the first run of consenants to the end and add "ay" to the end.
 * 
 * @param word A pointer to the first char of the word to translate
 * @return A pointer to the first char of the translated word
*/
char * pig(char * word){
    char * pig;
    char fst = tolower(word[0]);
    /*vowel*/
    if (isVowel(word[0]) && fst != 'y'){
        /*pig should have enough bytes to fit the word plus 'way' */
        pig = malloc(sizeof(word) + sizeof(char) * 3);

        int index = 0;

        /*add word to the beggining of the array*/
        while (word[index] != '\0'){
            pig[index] = word[index];
            index++;
        }

        /*add 'way' to the end of the array, regardless of the length of [word]*/
        pig[index] = 'w';
        pig[index + 1] = 'a';
        pig[index + 2] = 'y';
        pig[index + 3] = '\0';
        
    /*consonant*/
    } else {
        /*pig should have enough bytes to fit the word plus 'ay' */
        pig = malloc(sizeof(word) + sizeof(char) * 2);

        int wordIndex = 0;
        int pigIndex = 0;

        /*if the first charecter is a 'y' skip it*/
        if (fst == 'y') wordIndex++;

        /*skip the first run of consenants, or if there are no vowels, skip the whole word.*/
        while (!isVowel(word[wordIndex]) && word[wordIndex] != '\0'){
            wordIndex++;
        }

        /*add the remaining letters to the output*/
        while (word[wordIndex] != '\0'){
            pig[pigIndex] = word[wordIndex];
            wordIndex++;
            pigIndex++;
        }

        /*if the first charecter is a 'y' add it to the translation*/
        if (fst == 'y'){
            pig[pigIndex] = word[0];
            pigIndex++;
        }
        /*add the first run of consenants to the output, or if there are no vowels, add the whole word*/
        wordIndex = 0;
        while (!isVowel(word[wordIndex]) && word[wordIndex] != '\0'){
            pig[pigIndex] = word[wordIndex];
            pigIndex++;
            wordIndex++;
        }
        /*add 'ay' to the end*/
        pig[pigIndex] = 'a';
        pig[pigIndex+1] = 'y';
        pig[pigIndex+2] = '\0';
    }

    return pig;
}

/**
 * If the character is a vowel, it will return true.
 * If a charecter is a consonant, it will return false.
 * 
 * Y is treated as a vowel by this function.
 * 
 * @param c The character to check
 * @return If the character is a vowel
*/
bool isVowel(char c){
    c = tolower(c);
    if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y'){
        return true;
    } else {
        return false;
    }
}