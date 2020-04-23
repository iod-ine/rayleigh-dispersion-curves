#include "medium.h"
#include "rayleigh.h"

int main() {
    Medium *M = LoadMediumFromFile();
    delete M;
    return 0;
}
