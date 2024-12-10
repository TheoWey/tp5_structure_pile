#pragma region    //librairie externes
#include <stdio.h>
#include <stdlib.h>
#include <cstdint>
#include <random>
#include <time.h>

#include "etudiant.h"

#pragma endregion //librairie externes

#ifndef MAIN_H
#define MAIN_H

#pragma region    //declaration des variables

const etudiant name1 = {"bernard","alfred"};
const etudiant name2={"michel" ,"blanc"};
const etudiant name3={"laballe","saitlire"};
const etudiant name4={"jean"   ,"pierre"};
const etudiant name5={"arture" ,"guillere"};

#pragma endregion //declaration des variables

#pragma region    // declaration des fonctions

void init(void);
void loop(void);

void new_etu(unique_ptr<fiche_etu[]> *fiche,uint8_t *nb_etu);

#pragma endregion // declaration des fonctions
#endif
