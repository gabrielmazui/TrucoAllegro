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
            if (username[j] == ' ') {
                if (j == *lenUser - 1) {
                    break;
            }
            if (spaceBefore){
                j++;
                continue;
            }
            username[i++] = username[j++];
            spaceBefore = 1;

            }else {
            username[i++] = username[j++];
            spaceBefore = 0;
            }
        }
        if(spaceBefore){
            username[i-1] = '\0';
            *lenUser = i-1;
        }else{
            username[i] = '\0';
            *lenUser = i;
        }
        if(*lenUser - 1 >= 2){
            *verDone = 1;
            return 1;
        }
        *verDone = 1;
        return 0;
    }
