#include "mifz_math.hpp"
#include <math.h>

float periodic_normalization(float nb, float box_size) {
  float n_nb = fmodf(nb, box_size);
  if (n_nb > 0)
    return n_nb;
  else
    return n_nb + box_size;
}
