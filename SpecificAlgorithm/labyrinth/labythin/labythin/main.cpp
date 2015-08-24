//
//  main.cpp
//  labythin
//
//  Created by 王波 on 15/8/24.
//  Copyright (c) 2015年 wangbo. All rights reserved.
//

#include <iostream>
#include "labyrinth.h"

int main(int argc, const char * argv[]) {
    
    srand((unsigned int) time(NULL) );
    labySize = LABY_MAX / 2 + rand() % (LABY_MAX / 2);
    printf("Using a laby of size  %d ...\n", labySize); getchar();
    (1 < argc) ? readLaby(argv[1]) : randLaby();
    displayLaby();
    
    labyrinth(laby, startCell, goalCell) ?
    
    printf("\nRoute found\a\n") :
    printf("\nNo route found\a\n");
    return 0;
    
}
