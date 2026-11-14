#include <stdio.h>
#include<windows.h>
#include <stdbool.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

void doubleToString(double val, char *a, int aLength) {
    // %.2f - 2 point spaces
    snprintf(a, aLength, "%.2f", val);
}

void changeBool(bool *val) {
    *val = !(*val);
}

int main() {
  double m = 2000;
  double H_0 = 500;
  double v_0 = 10;
  double F_c = 45000;
  double g = 1.6;
  double H = H_0;
  double v = v_0;
  bool turnedOn = false;
  while (H > 0)
  {
    H -= v;
    v += g;
    char strH[20], strV[20];

    doubleToString(H, strH, sizeof(strH));
    doubleToString(v, strV, sizeof(strV));
    char buffer[100];
    const char *engineState = turnedOn ? "ON" : "OFF";
    // %s - string
    snprintf(buffer,sizeof(buffer), "H=%sm, V=%sm/s, %s", strH, strV,engineState);
    printf("%s\n", buffer);
    clock_t start_time = clock();
    clock_t duration = (CLOCKS_PER_SEC * 700) / 1000;

    bool pressed = false;

    while (clock() - start_time < duration) {
        // checking if key was pressed
        if (_kbhit()) {
            char input = _getch();
            if (input == ' ') {
                changeBool(&turnedOn);
                break;
            }
        }
    }
  }
  if  (v>1)
  {
    printf("The lander has crashed.");
  }
  else
  {
    printf("The landing was succesful.");
  }
  return 0;
}