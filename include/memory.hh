#pragma region    //librairie externes
#include "cstring"
#include "memory"

#include "stdio.h"
#include "stdlib.h"
#include <cstdint>
#pragma endregion //librairie externes

#ifndef MEMOIRE_HH
#define MEMOIRE_HH

#pragma region    //declaration des variables

using namespace std;


#pragma endregion //declaration des variables

#pragma region    // declaration des fonctions

template <typename T>
void smart_malloc(unique_ptr<T[]> *array, uint8_t *dim_array);

#pragma endregion // declaration des fonctions
#endif
