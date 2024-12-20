#pragma region // librairie externes

#include <cstdint>
#include <random>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "etudiant.hh"
#include "memory.hh"

#pragma endregion // librairie externes

#ifndef MAIN_H
#define MAIN_H

#pragma region // declaration des variables

const etudiant name1 = {"bernard", "alfred"};
const etudiant name2 = {"michel", "blanc"};
const etudiant name3 = {"laballe", "saitlire"};
const etudiant name4 = {"jean", "pierre"};
const etudiant name5 = {"arture", "guillere"};

enum operation { modifier = 'd', ajouter = 'o', note = 't',afficher = 'f' };

#pragma endregion // declaration des variables

#pragma region // declaration des fonctions

void init(void);
void loop(void);

#pragma endregion // declaration des fonctions
#endif
