#include <stdio.h>
#include <windows.h>
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

int main(int argc, char *argv[]) {
    double m = 2000;
    double H_0 = 500;
    double v_0 = 10;
    double F_c = 4500;
    char fileName[100] = "LOG";
    if (argc > 1) {
        snprintf(fileName, sizeof(fileName), "%s", argv[1]);
    }
    FILE *fpt;

    char strH0[20];
    char strV0[20];
    char strm[20];
    char strFc[30];



    doubleToString(H_0, strH0, sizeof(strH0));
    doubleToString(v_0, strV0, sizeof(strV0));
    doubleToString(m, strm, sizeof(strm));
    doubleToString(F_c, strFc, sizeof(strFc));

    char buffer[100];
    snprintf(buffer,sizeof(buffer),"m= %skg, H_0=%sm, v_0=%sm/s, F_c = %sN, filename: %s.csv", strm, strH0, strV0, strFc, fileName);
    printf("%s\n", buffer);

    while (1) {
        char dec;
        printf("Do you want to change the default data? (y/n)\n");
        scanf(" %c", &dec); 
        
        if (dec == 'y' || dec == 'Y') {
            printf("Which one? (m, H, v, F, n)\n");
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
            } else if (param == 'n' || param == 'N') {
                scanf("%19s", fileName);
            } else {
                printf("Unknown parameter!\n");
                continue;
            }
            
            doubleToString(H_0, strH0, sizeof(strH0));
            doubleToString(v_0, strV0, sizeof(strV0));
            doubleToString(m, strm, sizeof(strm));
            doubleToString(F_c, strFc, sizeof(strFc));

            snprintf(buffer, sizeof(buffer), "m= %skg, H_0=%sm, v_0=%sm/s, F_c = %sN, filename: %s.csv", strm, strH0, strV0, strFc, fileName);
            printf("Updated: %s\n\n", buffer);
        } else {
            break;
        }
    }

    printf("\nStarting simulation... Press SPACE to toggle engine.\n");

    const double g = 1.6;
    const double dt = 0.5; 
    double H = H_0;
    double v = v_0;
    double t = 0.0;
    bool turnedOn = false;
    char fullFilename[30];
    snprintf(fullFilename, sizeof(fullFilename), "%s.csv", fileName);
    fpt = fopen(fullFilename, "w+"); 
    if (fpt != NULL) {
        fprintf(fpt, "Time,Height,Speed,StateOfEngine\n");
    }
    while (H > 0)
    {
        double acceleration = g;
        if (turnedOn) 
        {
            acceleration -= (F_c / m);
        }
        H -= v * dt;
        v += acceleration * dt;
        t += dt;
        int engineStateNum = turnedOn ? 1 : 0;
        const char *engineStateStr = turnedOn ? "ON" : "OFF";
        
        if (fpt != NULL) {
            fprintf(fpt, "%.2f,%.2f,%.2f,%d\n", t, H, v, engineStateNum);
        }

        char strH[20], strV[20];
        doubleToString(H, strH, sizeof(strH));
        doubleToString(v, strV, sizeof(strV));
        printf("H=%sm, V=%sm/s, Engine=%s\n", strH, strV, engineStateStr);
        clock_t start_time = clock();
        clock_t duration = (CLOCKS_PER_SEC * 500) / 1000;

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
        printf("The lander has crashed.\n");
    }
    else
    {
        printf("The landing was succesful.\n");
    }
    if (fpt != NULL) 
    {
        fclose(fpt);
        printf("Data successfully saved to %s\n", fullFilename);
    }
    return 0;
}