/*
=============================================================================
 Name        : aufgaben.h
 Author      : InfinitePain
 License     : Apache License 2.0
 Description : Header file for Ascii-Numeric Utility
=============================================================================
*/

#ifndef AUFGABEN_H_
#define AUFGABEN_H_

#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include "utilities.h"

int minimum(int *samples, int n)
{
    int temp = samples[0];
    for (int i = 0; i < n; i++)
    {
        if (samples[i] < temp)
        {
            temp = samples[i];
        }
    }
    return temp;
}
int maximum(int *samples, int n)
{
    int temp = samples[0];
    for (int i = 0; i < n; i++)
    {
        if (samples[i] > i)
        {
            temp = samples[i];
        }
    }
    return temp;
}
float mean(int *samples, int n)
{
    float temp = 0;
    for (int i = 0; i < n; i++)
    {
        temp += samples[i];
    }
    temp = temp / n;
    return temp;
}

void Aufgabe1()
{
    printw("Aufgabe 1 - Minimum, Maximum und Mittelwert\n");
    printw("\n");
    printw("Hinweis:\n");
    printw("0 oder direktes Druecken von Enter generiert Zufallszahl.\n");
    printw("Nach 2 Zufallszahlen werden Rest automatisch generiert.\n");
    printw("Anzahl der Zahlen: ");
    refresh();
    int anzahl = 0;
    scanInt(1, &anzahl);
    int counter = 0;
    bool random = false;
    if (anzahl < 0)
    {
        clear();
        refresh();
        return;
    }
    if (anzahl == 0)
    {
        counter++;
        anzahl = rand() % 9 + 1;
        move(getcury(stdscr) - 1, getcurx(stdscr) + 19);
        printw("%i\n", anzahl);
    }

    int samples[anzahl];

    for (int i = 0; i < anzahl; i++)
    {
        if (random)
        {
            samples[i] = rand() % 100;
            printw("%i. Zahl: %i\n", i + 1, samples[i]);
            refresh();
        }
        else
        {
            printw("%i. Zahl: ", i + 1);
            refresh();
            scanInt(3, &samples[i]);
            if (samples[i] == 0)
            {
                move(getcury(stdscr) - 1, getcurx(stdscr) + 9);
                samples[i] = rand() % 100;
                printw("%i\n", samples[i]);
                counter++;
            }
            else if (samples[i] < 0)
            {
                clear();
                refresh();
                return;
            }
            if (counter == 2)
            {
                random = true;
            }
        }
    }
    printw("Minimum aus Samples = %d\n", minimum(samples, anzahl));
    printw("Maximum aus Samples = %d\n", maximum(samples, anzahl));
    printw("Der Mittelwert von Samples = %f\n", mean(samples, anzahl));
    printw("\n");
    printw("Druecken Sie eine beliebige Taste, um fortzufahren...\n");
    refresh();
    getch();
    clear();
    refresh();
}

void printIntArray(int *samples, int n)
{
    printw("SamplesRueckwaerts[%i] = \n{ ", n);
    for (int i = 0; i < n; i++)
    {
        printw("%i, ", samples[n - i - 1]);
    }
    printw("\b\b }\n");
}

void Aufgabe2()
{
    printw("Aufgabe 2 - Ausgabe eines Zahlen-Arrays auf der Konsole\n");
    printw("\n");
    printw("Hinweis:\n");
    printw("0 oder direktes Druecken von Enter generiert Zufallszahl.\n");
    printw("Nach 2 Zufallszahlen werden Rest automatisch generiert.\n");
    printw("Anzahl der Zahlen: ");
    refresh();
    int anzahl;
    int counter = 0;
    bool random = false;
    scanInt(1, &anzahl);
    if (anzahl == 0)
    {
        counter++;
        anzahl = rand() % 9 + 1;
        move(getcury(stdscr) - 1, getcurx(stdscr) + 19);
        printw("%i\n", anzahl);
    }
    if (anzahl < 0)
    {
        clear();
        refresh();
        return;
    }
    int samples[anzahl];
    printw("\n");
    refresh();
    for (int i = 0; i < anzahl; i++)
    {
        if (random)
        {
            samples[i] = rand() % 100;
            printw("%i. Zahl: %i\n", i + 1, samples[i]);
            refresh();
        }
        else
        {
            printw("%i. Zahl: ", i + 1);
            refresh();
            scanInt(3, &samples[i]);
            if (samples[i] == 0)
            {
                move(getcury(stdscr) - 1, getcurx(stdscr) + 9);
                samples[i] = rand() % 100;
                printw("%i\n", samples[i]);
                counter++;
            }
            else if (samples[i] < 0)
            {
                clear();
                refresh();
                return;
            }
            if (counter == 2)
            {
                random = true;
            }
        }
    }
    printIntArray(samples, anzahl);

    refresh();
    printw("Druecken Sie eine beliebige Taste, um fortzufahren...\n");
    getch();
    clear();
    refresh();
}

int printSumIntArray(int *samples, int n)
{
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += samples[i];
    }
    return sum;
}

void Aufgabe3()
{
    printw("Aufgabe 3 - Konsolen-Ausgabe der Summe eines Arrays\n");
    printw("\n");
    printw("Hinweis:\n");
    printw("0 oder direktes Druecken von Enter generiert Zufallszahl.\n");
    printw("Nach 2 Zufallszahlen werden Rest automatisch generiert.\n");
    printw("Anzahl der Zahlen: ");
    refresh();
    int anzahl;
    int counter = 0;
    bool random = false;
    scanInt(1, &anzahl);
    if (anzahl == 0)
    {
        counter++;
        anzahl = rand() % 9 + 1;
        move(getcury(stdscr) - 1, getcurx(stdscr) + 19);
        printw("%i\n", anzahl);
    }
    if (anzahl < 0)
    {
        clear();
        refresh();
        return;
    }
    int samples[anzahl];
    printw("\n");
    refresh();
    for (int i = 0; i < anzahl; i++)
    {
        if (random)
        {
            samples[i] = rand() % 100;
            printw("%i. Zahl: %i\n", i + 1, samples[i]);
            refresh();
        }
        else
        {
            printw("%i. Zahl: ", i + 1);
            refresh();
            scanInt(3, &samples[i]);
            if (samples[i] == 0)
            {
                move(getcury(stdscr) - 1, getcurx(stdscr) + 9);
                samples[i] = rand() % 100;
                printw("%i\n", samples[i]);
                counter++;
            }
            else if (samples[i] < 0)
            {
                clear();
                refresh();
                return;
            }
            if (counter == 2)
            {
                random = true;
            }
        }
    }
    printw("Die Summe ist: %d\n", printSumIntArray(samples, anzahl));
    refresh();
    printw("Druecken Sie eine beliebige Taste, um fortzufahren...\n");
    getch();
    clear();
    refresh();
}

void Wuerfel1()
{
    int zufallszahl = rand() % 6 + 1;
    switch (zufallszahl)
    {
    case 1:
        printw("Wuerfel 1: Lehm ");
        break;
    case 2:
        printw("Wuerfel 1: Holz ");
        break;
    case 3:
        printw("Wuerfel 1: Schaf ");
        break;
    case 4:
        printw("Wuerfel 1: Erz ");
        break;
    case 5:
        printw("Wuerfel 1: Getreide ");
        break;
    case 6:
        printw("Wuerfel 1: Gold ");
        break;
    }
}
void Wuerfel2()
{
    int zufallszahl = rand() % 6 + 1;
    switch (zufallszahl)
    {
    case 1:
        printw("Wuerfel 2: Sonne\n");
        break;
    case 2:
        printw("Wuerfel 2: Muehle\n");
        break;
    case 3:
        printw("Wuerfel 2: Ritter\n");
        break;
    case 4:
        printw("Wuerfel 2: Fragezeichen\n");
        break;
    case 5:
        printw("Wuerfel 2: Raeuber\n");
        break;
    case 6:
        printw("Wuerfel 2: Raeuber\n");
        break;
    }
}

void Aufgabe4()
{
    printw("Aufgabe 4 - Alea iacta est\n");
    printw("\n");
    printw("Druecken Sie 'Enter' um den naechsten Wurf zu sehen.\n");
    printw("\n");
    mvprintw(getmaxy(stdscr) - 1, 0, "Druecken Sie Taste q, um fortzufahren...");
    refresh();
    move(3, 0);

    int repeat = 1;
    int repeat_max = getmaxy(stdscr) - 4;
    printw("%i.Wurf ", repeat);
    Wuerfel1();
    printw("\b ");
    Wuerfel2();
    int key;
    int y = 4;
    while (1)
    {
        key = getch();
        if (repeat % repeat_max == 0)
        {
            clear();
            move(0, 0);
            printw("Aufgabe 4 - Alea iacta est\n");
            printw("\n");
            printw("Druecken Sie 'Enter' um den naechsten Wurf zu sehen.\n");
            printw("\n");
            mvprintw(getmaxy(stdscr) - 1, 0, "Druecken Sie Taste q, um fortzufahren...");
            refresh();
            move(3, 0);
            y = 3;
        }
        if (key == 'q' || key == 'Q')
        {
            break;
        }
        else if (key == '\n' || key == '\r')
        {
            move(y++, 0);
            repeat++;
            printw("%i.Wurf ", repeat);
            Wuerfel1();
            printw("\b ");
            Wuerfel2();
        }
        else
        {
            beep();
        }
        refresh();
    }
    clear();
    refresh();
}

void rechneMuenzen(FloatInt *betrag, int coinValues[], int coinCount, int maxCoins[], int result[])
{
    FloatInt remaining = *betrag;
    for (int i = 0; i < coinCount; i++)
    {
        FloatInt coinValue = {coinValues[i], 2};
        FloatInt coinNumber;
        div_FloatInt(&remaining, &coinValue, &coinNumber, 2);
        for (int j = 0; j < coinNumber.point; j++)
        {
            coinNumber.value /= 10;
        }
        if (coinNumber.value > maxCoins[i])
        {
            coinNumber.value = maxCoins[i];
        }
        result[i] = coinNumber.value;
        FloatInt totalValue;
        coinNumber.point = 0;
        mul_FloatInt(&coinValue, &coinNumber, &totalValue);
        sub_FloatInt(&remaining, &totalValue, &remaining);
    }
}

void Aufgabe5()
{
    printw("Aufgabe 5 - Muenzautomat\n");
    printw("\n");
    printw("Hinweis:\n");
    printw("0 oder direktes Druecken von Enter generiert Zufallszahl.\n");

    FloatInt betrag;
    bool validInput = false;
    int invalidInputCount = 0;
    int posy = 4;
    while (!validInput)
    {
        mvprintw(posy++, 0, "Betrag(0-200,00): ");
        scanFloatInt(3, 2, &betrag);
        FloatInt temp;
        sub_FloatInt(&betrag, &((FloatInt){200, 0}), &temp);
        if (betrag.value == -1)
        {
            refresh();
            clear();
            return;
        }
        else if (temp.value <= 0)
        {
            validInput = true;
        }
        else
        {
            posy = 4;
            mvprintw(posy++, 0, "Ungueltige Eingabe!\n");
            invalidInputCount++;
        }

        if (invalidInputCount >= 3)
        {
            printw("Zu viele ungueltige Eingaben.\n");
            printw("Druecken Sie eine beliebige Taste, um fortzufahren...\n");
            getch();
            refresh();
            clear();
            refresh();
            return;
        }
    }
    clear();
    move(0, 0);
    printw("Aufgabe 5 - Muenzautomat\n");
    printw("\n");
    printw("Hinweis:\n");
    printw("0 oder direktes Druecken von Enter generiert Zufallszahl.\n");
    printw("Betrag(0-200,00): ");
    refresh();

    if (betrag.value == 0)
    {
        betrag.value = rand() % 20000 + 1;
        betrag.point = 2;
    }
    printw("%i.%02i", betrag.value / 100, betrag.value % 100);
    printw("\n");
    refresh();
    int coinValues[] = {200, 100, 50, 20, 10, 5, 2, 1};
    int maxCoins[] = {100, 100, 100, 100, 100, 100, 100, 5};
    int coinCount = sizeof(coinValues) / sizeof(coinValues[0]);
    int minCoinsResult[coinCount];
    int maxCoinsResult[coinCount];
    FloatInt maxBetrag = betrag;
    FloatInt minBetrag = betrag;
    maxBetrag.value = 100 * (200 + 100 + 50 + 20 + 10 + 5 + 2) - maxBetrag.value;

    rechneMuenzen(&maxBetrag, coinValues, coinCount, maxCoins, maxCoinsResult);
    rechneMuenzen(&minBetrag, coinValues, coinCount, maxCoins, minCoinsResult);
    if (maxCoinsResult[coinCount - 1] > 0)
    {
        maxCoinsResult[coinCount - 2]++;
    }
    maxCoinsResult[0] = 100 - maxCoinsResult[0];
    maxCoinsResult[1] = 100 - maxCoinsResult[1];
    maxCoinsResult[2] = 100 - maxCoinsResult[2];
    maxCoinsResult[3] = 100 - maxCoinsResult[3];
    maxCoinsResult[4] = 100 - maxCoinsResult[4];
    maxCoinsResult[5] = 100 - maxCoinsResult[5];
    maxCoinsResult[6] = 100 - maxCoinsResult[6];

    printw("Sie erhalten minimum %i Muenzen\n", minCoinsResult[0] + minCoinsResult[1] + minCoinsResult[2] + minCoinsResult[3] + minCoinsResult[4] + minCoinsResult[5] + minCoinsResult[6] + minCoinsResult[7]);
    printw("%03i x  2 Euro     %03i x 10 Cent\n", minCoinsResult[0], minCoinsResult[4]);
    printw("%03i x  1 Euro     %03i x  5 Cent\n", minCoinsResult[1], minCoinsResult[5]);
    printw("%03i x 50 Cent     %03i x  2 Cent\n", minCoinsResult[2], minCoinsResult[6]);
    printw("%03i x 20 Cent     %03i x  1 Cent\n", minCoinsResult[3], minCoinsResult[7]);
    printw("\n");

    printw("Sie erhalten maximum %i Muenzen\n", maxCoinsResult[0] + maxCoinsResult[1] + maxCoinsResult[2] + maxCoinsResult[3] + maxCoinsResult[4] + maxCoinsResult[5] + maxCoinsResult[6] + maxCoinsResult[7]);
    printw("%03i x  2 Euro     %03i x 10 Cent\n", maxCoinsResult[0], maxCoinsResult[4]);
    printw("%03i x  1 Euro     %03i x  5 Cent\n", maxCoinsResult[1], maxCoinsResult[5]);
    printw("%03i x 50 Cent     %03i x  2 Cent\n", maxCoinsResult[2], maxCoinsResult[6]);
    printw("%03i x 20 Cent     %03i x  1 Cent\n", maxCoinsResult[3], maxCoinsResult[7]);
    printw("\n");

    printw("Druecken Sie eine beliebige Taste, um fortzufahren...\n");
    refresh();
    getch();
    clear();
    refresh();
}

#endif /*AUFGABE_H_*/
