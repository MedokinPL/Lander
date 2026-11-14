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

  char strH0[20];
    char strV0[20];
    char strm[20];
    char strFc[30];



    doubleToString(H_0, strH0, sizeof(strH0));
    doubleToString(v_0, strV0, sizeof(strV0));
    doubleToString(m, strm, sizeof(strm));
    doubleToString(F_c, strFc, sizeof(strFc));

    char buffer[100];
    snprintf(buffer,sizeof(buffer),"m= %skg, H_0=%sm, v_0=%sm/s, F_c = %sN", strm, strH0, strV0, strFc);
    printf("%s\n", buffer);
 while (1) {
        char dec;
        printf("Do you want to change the default data? (y/n)\n");
        scanf(" %c", &dec); 
        
        if (dec == 'y' || dec == 'Y') {
            printf("Which one? (m, H, v, F)\n");
            char param;
            scanf(" %c", &param);
            
            printf("Enter new value: ");
            if (param == 'm' || param == 'M') {
                scanf("%lf", &m);
            } else if (param == 'h' || param == 'H') {
                scanf("%lf", &H_0);
            } else if (param == 'v' || param == 'V') {
                scanf("%lf", &v_0);
            } else if (param == 'f' || param == 'F') {
                scanf("%lf", &F_c);
            } else {
                printf("Unknown parameter!\n");
                continue;
            }
            
            doubleToString(H_0, strH0, sizeof(strH0));
            doubleToString(v_0, strV0, sizeof(strV0));
            doubleToString(m, strm, sizeof(strm));
            doubleToString(F_c, strFc, sizeof(strFc));

            snprintf(buffer, sizeof(buffer), "m= %skg, H_0=%sm, v_0=%sm/s, F_c = %sN", strm, strH0, strV0, strFc);
            printf("Updated: %s\n\n", buffer);
        } else {
            break;
        }
    }

    printf("\nStarting simulation... Press SPACE to toggle engine.\n");

  const double g = 1.6;
  double H = H_0;
  double v = v_0;
  bool turnedOn = false;
  while (H > 0)
  {
    double acceleration = g;
    if (turnedOn) 
    {
      acceleration -= (F_c / m);
    }
    H -= v;
    v += acceleration;
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