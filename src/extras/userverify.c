#include <stdio.h>
#include "../../config/config.h"

int userVerify(int* lenUser, int* verDone){
    *verDone = 0;
    if(*lenUser <= 2){
        *verDone = 1;
        return 0;
    }
    int i = 0;
    int j = 0;
    int spaceBefore = 0;
    while (j < *lenUser){
      if (user.name[j] == ' ') {
            if (j == *lenUser - 1) {
                break;
        }
        if (spaceBefore){
            j++;
            continue;
        }
        user.name[i++] = user.name[j++];
        spaceBefore = 1;

        }else {
            user.name[i++] = user.name[j++];
            spaceBefore = 0;
        }
    }
    if(spaceBefore){
        user.name[i-1] = '\0';
        *lenUser = i-1;
    }else{
        user.name[i] = '\0';
        *lenUser = i;
    }
    if(*lenUser - 1 >= 2){
        *verDone = 1;
        return 1;
    }
    user.name[*lenUser] = '\0';
    *verDone = 1;
    return 0;
}
