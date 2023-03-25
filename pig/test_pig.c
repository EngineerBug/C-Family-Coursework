#include "pig.h"
#include "pig.c"

int main(){
    /*create an array of words*/
    char * words[] = {"happy", "duck", "glove", "evil", "eight", "yowler", "crystal",
                    "hAppy", "Duck", "glovE", "Evil", "EIGHT", "Yowler", "crYstal"};

    /*create an array of pig latin words*/
    char * pigWords[] = {"appyhay", "uckday", "oveglay", "evilway", "eightway", "owleryay", "ystalcray",
                       "Appyhay", "uckDay", "ovEglay", "Evilway", "EIGHTway", "owlerYay", "Ystalcray"};

    /*test each word*/
    for (int i = 0; i<14; i++){
        char * piggy = pig(words[i]);
        assert(strcmp(piggy, pigWords[i]) == 0);
        free(piggy);
    }

    printf("All tests passed!\n");
    return 0;
}