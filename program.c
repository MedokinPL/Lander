#include <stdio.h>
#include <stdlib.h>

void doubleToString(double val, char *a, int aLength) {
    // %.2f - 2 point spaces
    snprintf(a, aLength, "%.2f", val);
}

int main() {
  double m = 2000;
  double H_0 = 500;
  double v_0 = 10;
  double F_c = 45000;
  const double g = 1.6;
  double H = H_0;
  double v = v_0;
  while (H > 0)
  {
    H -= v;
    char strH[20], strV[20];

    doubleToString(H, strH, sizeof(strH));
    doubleToString(v, strV, sizeof(strV));
    char buffer[100];
    // %s - string
    snprintf(buffer,sizeof(buffer), "H=%sm, V=%sm/s, OFF", strH, strV);
    printf("%s\n", buffer);
  }
  return 0;
}