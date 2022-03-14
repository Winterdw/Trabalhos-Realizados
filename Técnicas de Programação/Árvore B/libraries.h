//Esse arquivo contém todas as inclusões necessárias para o funcionamento do programa principal.
#ifndef LIBRARIES_H
#define LIBRARIES_H
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>

#define NULL_CONST      9223372037
#define DEFAULT_ORDER   4
#define MIN_ORDER       3
#define MAX_ORDER       20

using namespace std;

typedef unsigned    long int   ulint;
typedef const       int        cint;
typedef const       string     cstring;

#include "Serializable.h"
#include "Header.h"
#include "Registry.h"
#include "Archive.h"
#include "Fraction.h"
#include "Node.h"

#endif
