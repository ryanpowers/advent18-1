/*
 ============================================================================
 Name        : advent1a.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

//int main(void)
//{
//    FILE *input, *output;
//    int32_t freq = 0;
//    uint32_t counter = 100;
//
//    input = fopen("input.txt", "r");
//    output = fopen("output.txt", "w");
//    if (input && output)
//    {
//        int32_t offset;
//
//        while ( counter-- )
//        {
//            while ( fscanf(input, "%i", &offset) == 1 )
//            {
//                freq += offset;
//                fprintf(output, "%i\n", freq);
//            }
//            rewind(input);
//        }
//
//        printf("freq is %i\n", freq);
//
//        fclose(input);
//        fclose(output);
//        return 0;
//    }
//
//    return 1;
//}

//uint32_t searchFor(FILE * input, int32_t val);
uint32_t loadInstr(char const * fname);

static int32_t cumulative[1023] __attribute__ ((section (".noinit")));

//int main(void)
//{
//    if ( loadInstr("input.txt") == 0 )
//    {
//        uint32_t index = 0;
//        uint32_t scanner = 0;
//        uint32_t duploc = -1;
//        int32_t dup;
//        int32_t freq = 0;
//        int32_t temp;
//
//        while (index < 0xffffffff)
//        {
//            freq += instr[index%1024];
//            scanner = index;
//            temp = freq;
//            do
//            {
//                scanner = scanner + 1;
//                temp += instr[scanner % 1024];
//            } while ((temp != freq) && (scanner < 0xffffffff));
//            printf("found a dup: %i at %u and %u\n", freq, index, scanner);
//            index++;
//            if (scanner < duploc)
//            {
//                duploc = scanner;
//                dup = freq;
//            }
//        }
//
//        printf("found nearest dup: %i at %u and %u\n", dup, index, duploc);
//
//        return 0;
//    }
//
//    return 1;
//}

int main(void)
{
    if ( loadInstr("input.txt") == 0 )
    {
        uint32_t closest = -1;
        uint32_t closestfreq;

        /* nth freq = 590 * (n % 1023) + cumulative[n / 1023] */
        /* to find if a freq is in the sequence:
         * freq - cumulative[i] is divisible by 590
         */

        for (uint32_t freqloc = 0; freqloc < sizeof(cumulative)/sizeof(cumulative[0]); freqloc++)
        {
//            bool found = false;
            int32_t freq = cumulative[freqloc];

            /* next duplicate is x*cumulative[1023] + cumulative[y] */
            /* freq - cumulative[y] = x*cumulative[1023] */
            /* x = (freq - cumulative[y])/cumulative[1023] */
            /* next match = x * 1024 + y iff x is a positive non-zero whole number */

            for (uint32_t y = 0; y < sizeof(cumulative)/sizeof(cumulative[0]); y++)
            {
                int32_t x = (freq - cumulative[y]) / cumulative[sizeof(cumulative)/sizeof(cumulative[0])-1];
                if ( (x > 0) && /*( (x % cumulative[sizeof(cumulative)/sizeof(cumulative[0])-1]) == 0) ) */ ((x * cumulative[1022]) == (freq - cumulative[y])) )
                {
//                    printf("%i (at %u) repeats at %u\n", freq, freqloc, x * 1023 + y);
//                    found = true;
                    if ((x * sizeof(cumulative)/sizeof(cumulative[0]) + y) < closest)
                    {
                        closest = x * sizeof(cumulative)/sizeof(cumulative[0]) + y;
                        closestfreq = freq;
                    }
                }
            }
//            if (!found)
//            {
//                printf("%i does not repeat\n", freq);
//            }
        }

        printf("closest repeated freq is %i\n", closestfreq);

        return 0;
    }

    return 1;
}

uint32_t loadInstr(char const * fname)
{
    FILE *input;
    uint32_t index = 0;
    int32_t offset;
    int32_t last;
    int c, sign;

    input = fopen(fname, "r");
    if (input)
    {
//        offset = 0;
//        sign = fgetc(input);
//        c = fgetc(input);
//        while( c != '\n' )
//        {
//            offset = offset * 10 + (c - '0');
//            c = fgetc(input);
//        }
//        offset = offset * ((sign == '-') ? -1 : 1);
//        cumulative[index++] = offset;
//        last = offset;
//        do
//        {
//            offset = 0;
//            sign = fgetc(input);
//            c = fgetc(input);
//            while( (c != '\n') && (c >= 0) )
//            {
//                offset = offset * 10 + (c - '0');
//                c = fgetc(input);
//            }
//            offset = offset * ((sign == '-') ? -1 : 1);
//            cumulative[index++] = last + offset;
//            last += offset;
//        } while( !feof(input) );
//        fclose(input);
//        return 0;
//    }
        while ( fscanf(input, "%i", &offset) == 1 )
        {
            if ( index == 0 )
            {
                cumulative[index] = offset;
            }
            else
            {
                cumulative[index] = cumulative[index-1] + offset;
            }
            index++;
        }

        fclose(input);
        return 0;
    }
    return 1;
}

//uint32_t searchFor(FILE * input, int32_t val)
//{
//    int32_t test;
//    while ( fscanf(input, "%i", &test) == 1 )
//    {
//        if (test == val)
//        {
//            return (ftell(input));
//        }
//    }
//    return -1;
//}



