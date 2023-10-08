#include<iostream>
#include<cmath>

using namespace std;

float normalized(float nb, float box_size) {
  float n_nb = fmodf(nb, box_size);
  if (n_nb > 0)
    return n_nb;
  else
    return n_nb + box_size;
}

void test_normalize(float a, float box_size) {
 cout << "--\n";
 cout << "nb: " << a << "\nbx: box_size: " << box_size << endl;
 cout << "no: " << normalized(a, box_size) << endl;
}

int main()
{
  test_normalize(1.1, 1);
  test_normalize(3.1, 1);
  test_normalize(-0.1, 1);
  test_normalize(-3.1, 1);
  return 0;
}
