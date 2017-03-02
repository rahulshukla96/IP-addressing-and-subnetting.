#include <stdio.h>
#include <stdlib.h>
#include <math.h>
float calcSHbits(int, int, int, int, int, int);
float calcNSM(float, int, int, float, float, int, int, int);
int calcRange(int, int, int, int, int, int, int);
int calcRange2(int , int, int, int, int, int);
int validsmaskA(int, int, int);
int validsmaskB(int, int, int);
int validsmaskC(int, int, int);
int revEngDisplay(int, int, int, int, int, int, int);

int main()
{
    printf("\n\n\t**********WELCOME TO SUBNET CALCULATOR**********\n\t");
    printf("\n\nThis project has two modules: \n\n\tFirst one deals with IP \SUBNETTING\n\t(Use it to gather basic subnetting information).\n");
    printf("\n\tOther one is for different but most common type of subnetting, \n\twhich is REVERSE ENGINEERING SUBNETTING.\n");
    printf("\nChoose 1 to enter first module and 2 to enter second module -\t");

    char chBegin;
    functionDisplayBegin(chBegin);

    int oct1, oct2, oct3, oct4;
    int i, maxnh, maxsnw, db;
    printf("Please fill in the details of the IP address-\n\n");
    printf("First octate: ");
    scanf("%i", &oct1);

    for(i=0; i<=1000000; i++)
    {

        while(oct1<1 || oct1>255)
        {
            printf("Invalid number entered! Kindly try again.\n");
            printf("First octate: ");
            scanf("%i", &oct1);
        }
        while(oct1>223 && oct1<255)
        {
            printf("You can't enter this number. Such IPs are reserved for government and research purposes. Kindly try again.\n");
            printf("First octate: ");
            scanf("%i", &oct1);
        }
    }
    printf("Second octate: ");
    scanf("%i", &oct2);
    while(oct2<0 || oct2>255)
    {
        printf("Invalid number entered! Kindly try again.\n");
        printf("Second octate: ");
        scanf("%i", &oct2);
    }
    printf("Third octate: ");
    scanf("%i", &oct3);
    while(oct3<0 || oct3>255)
    {
        printf("Invalid number entered! Kindly try again.\n");
        printf("Third octate: ");
        scanf("%i", &oct3);
    }
    printf("Fourth octate: ");
    scanf("%i", &oct4);
    while(oct4<0 || oct4>255)
    {
        printf("Invalid number entered! Kindly try again.\n");
        printf("Fourth octate: ");
        scanf("%i", &oct4);
    }
    printf("\n\nEntered IP address is %i.%i.%i.%i\n", oct1,oct2,oct3,oct4);

    if (oct1>=1 && oct1<=126)
    {
        printf("This is class A IP address. Subnet mask= 255.0.0.0\n\n");
        maxnh = 8388607, maxsnw = 8388608, db = 24; //db is the default number of bits to be played with
        calcSHbits(maxnh, maxsnw, db, oct1, oct2, oct3);
    }

    else
    {
        if(oct1>=128 && oct1<=191)
        {
            printf("This is class B IP address. Subnet mask= 255.255.0.0\n\n");
            maxnh = 32767, db = 16, maxsnw = 32768;
            calcSHbits(maxnh, maxsnw, db, oct1, oct2, oct3);
        }

        else
        {
            printf("This is class C IP address. Subnet mask= 255.255.255.0\n\n");
            maxnh = 126, db = 8, maxsnw = 128;
            calcSHbits(maxnh, maxsnw, db, oct1, oct2, oct3);

        }
    }

    return 0;
}

    float calcSHbits(int maxnh, int maxsnw,int db, int oct1, int oct2, int oct3)
    {
        int hpn, snw, choice;
        float nhb, nsb;
        printf("Kindly choose the preferred option(1 or 2) as per your network requirements: \n\n");
        printf("1. If you want to subnet according to the number of hosts per network \n");
        printf("2. If you want to subnet according to the number of sub-networks \n");
        scanf("%d", &choice);

        if(choice == 1)
        {
            printf("Enter the required number of hosts per sub-network- ");
            scanf("%d", &hpn);

            while(hpn > maxnh)
            {
                printf("Entered number of hosts exceed the maximum number of hosts per network. Try again.\n");
                printf("Enter the required number of hosts per network- ");
                scanf("%d", &hpn);
            }

            nhb = log(hpn+2)/log(2);
            printf("Number of host bits after subnetting= %.0f\n", ceil(nhb));
            printf("Number of IPs that can be assigned to hosts(Number of valid hosts)= %.0f per network\n\n", pow(2, ceil(nhb))-2);

            if((pow(2, ceil(nhb))-2)>512)
            {
                printf("\nSuggestion 1\n");
                printf("\nWe'd like to point out that number of hosts per network from this network configuration is not recommended. It jams the network with traffic.\n");
                printf("To avoid, kindly do not go for any more than 512 hosts per network.\n\n");
            }

            printf("Number of subnet bits = %.0f\n", db-ceil(nhb));
            printf("Number of sub-networks= %.0f\n\n", pow(2, db-ceil(nhb)));

            float var1 = ceil(nhb);
            float var2 = db-ceil(nhb);
            snw = pow(2, var2);

            calcNSM(db, choice, snw, var1, var2, oct1, oct2, oct3);
        }

        if(choice == 2)
        {
            printf("Enter the required number of total sub-networks- ");
            scanf("%d", &snw);

            while(snw > maxsnw)
            {
                printf("Entered number of subnets exceeds the maximum number of sub-networks possible. Try again.\n");
                printf("Enter the required number of total sub-networks- ");
                scanf("%d", &snw);
            }

            nsb = log(snw)/log(2);

            printf("Number of subnet bits = %.0f\n", ceil(nsb));
            printf("Number of sub-networks= %.0f\n\n", pow(2, ceil(nsb)));

            printf("Number of host bits after subnetting= %.0f\n", db-ceil(nsb));
            printf("Number of IPs that can be assigned to hosts(Number of valid hosts per network)= %.0f per network\n\n", pow(2, (db-ceil(nsb)))-2);

            if((pow(2, (db-ceil(nsb)))-2)>512)
            {
                printf("\nSuggestion 1\n");
                printf("\nWe'd like to point out that number of hosts per network from this network configuration is not recommended. It jams the network with traffic.\n");
                printf("To avoid, kindly do not go for any network configuration that allows more than 512 hosts per network.\n\n");
            }


            float var1 = db-ceil(nsb);
            float var2 = ceil(nsb);

            calcNSM(db, choice, snw, var1, var2, oct1, oct2, oct3);
        }

        return 0;
    }


    float calcNSM(float db, int choice, int snw, float var1, float var2, int oct1, int oct2, int oct3 )
    {
        int i, inc, incOct, a = 0;

//for class C
        if(db == 8)
        {
            for(i = 7; i >= var1; i--)
            {
               a = a+pow(2, i);
            }
            printf("The new subnet mask is 255.255.255.%d", a);

            inc = pow(2, var1);
            incOct=4;
        }
//for class B
        else if(db == 16 && var2 >=1 && var2 <=8)
        {
            for(i = 7; i >= (8-var2); i--)
            {
                a = a + pow(2, i);
            }
            printf("The new subnet mask is 255.255.%d.0", a);

            inc = pow(2, (8-var2));
            incOct=3;
        }

        else if(db == 16 && var2 >=9 && var2 <=15)
        {
            for(i=0; i < var2-8; i++)
            {
                a = a+pow(2, (7-i));
            }
            printf("The new subnet mask is 255.255.255.%d", a);

            inc = pow(2, (16-var2));
            incOct= 4;
        }
//for class A
        else if(db == 24 && var2 >=1 && var2 <=8)
        {
            for(i=7; i>=(8-var2); i--)
            {
                a = a+pow(2,i);
            }
            printf("The new subnet mask is 255.%d.0.0", a);

            inc = pow(2, (8-var2));
            incOct=2;
        }
        else if(db == 24 && var2 >= 9 && var2 <= 16)
        {
            for(i = 7; i >= (16-var2); i--)
            {
                a = a+pow(2, i);
            }
            printf("The new subnet mask is 255.255.%d.0", a);

            inc = pow(2, (16-var2));
            incOct= 3;
        }

        else if(db == 24 && var2 >= 17 && var2 <= 23)
        {
            for(i = 7; i >= (24-var2); i--)
            {
                a = a+pow(2, i);
            }
            printf("The new subnet mask is 255.255.255.%d", a);

            inc = pow(2, (24-var2));
            incOct= 4;
        }
        calcRange(snw, choice, oct1, oct2, oct3, inc, incOct);

        return 0;
    }

int calcRange(int snw, int choice, int oct1, int oct2, int oct3, int inc, int incOct)
        {
            int i, j, k, inc2= 0;
            printf("\n");

           //for class A
            if (oct1>=1 && oct1<=126)
            {
                printf("The network ID/address of the entered address is %d.0.0.0\n",oct1);
                printf("The broadcast address of the entered address is %d.255.255.255\n",oct1);

                printf("\nPress any key to display all the %d networks below...\n\n", snw);
                getch();

                printf("\nThe detail of sub-networks is as follows: \n\n");
                printf("1. %d.0.0.0    -    ",oct1);

              //testing done
                    if(incOct == 2)
                    {
                        for(i = 2; i <= ((256/inc)); i++ )
                        {
                            inc2 = inc2+inc;
                            printf(" %d.%d.255.255\n",  oct1,inc2-1);
                            printf("%d. %d.%d.0.0    -    ", i, oct1, inc2);
                        }
                        printf(" %d.255.255.255\n",  oct1);

                    }


            //dual testing done except for serial number's bug
                    else if(incOct == 3)
                    {
                    //printf(" %d.0.0.0\n",  oct1);
                    //printf(" %d.0.%d.0\n",  oct1, inc);

                        for(j = 0; j<256; j++)
                        {
                            printf("%d.%d.0.0    -    ", oct1, j);
                            inc2 = 0;

                            for(i = 2; i <= ((256/inc)); i++ )
                            {
                                inc2 = inc2+inc;
                                printf("%d.%d.%d.255\n",  oct1, j, inc2-1);
                                printf("%d.%d.%d.0    -    ", oct1, j, inc2);

                            }
                            printf("%d.%d.255.255\n",  oct1, j);
                        //printf(" %d.%d.%d.%d\n",  oct1, oct2, j, 0);
                        }
                    }
                //else{printf("You don't want the display.");}

                //if(incOct == 4)
                    else
                    {
                        printf(" %d.0.0.0    -    ",  oct1);
                        printf(" %d.0.0.%d  \n",  oct1, inc-1);

                        for(k = 0; k<=255; k++)
                        {
                        //printf(" %d.%d.0.0\n",  oct1, );

                            for(j = 0; j<256; j++)
                            {
                                //printf(" %d.%d.%d.%d    -    ", oct1, k, j, inc);
                                inc2 = 0;

                                for(i = 0; i < ((256/inc)); i++ )
                                {
                                    //inc2 = inc2+inc;
                                    printf("%d.%d.%d.%d -  ",  oct1, k, j, inc2);
                                    inc2 = inc2+inc;
                                    printf(" %d.%d.%d.%d    \n", oct1, k, j, inc2-1);

                                }
                            }

                        //printf(" %d.%d.%d.%d\n",  oct1, oct2, j, 0);

                        }
                    }
                }
            //else {printf("Try again !");}
            //}

        //for class B
            else if (oct1>=128 && oct1<=191)
            {
                printf("The network ID/address of the entered address is- %d.%d.0.0\n",oct1, oct2);
                printf("The broadcast address of the entered address is- %d.%d.255.255\n",oct1, oct2);

                printf("\nPress any key to display all the %d networks below...\n\n", snw);
                getch();

                printf("\nThe detail of sub-networks is as follows: \n\n");
                printf("1. %d.%d.0.0    -    ",oct1, oct2);

            //dual testing done
                if(incOct == 3)
                {
                    for(i = 2; i <= ((256/inc)); i++ )
                    {
                        //printf(" %d.%d.%d.255\n",  oct1, oct2, inc2-1);
                        inc2 = inc2+inc;
                        //printf("1. %d.%d.0.0\n",oct1, oct2);
                        printf(" %d.%d.%d.255\n",  oct1, oct2, inc2-1);
                        printf("%d. %d.%d.%d.0    -    ", i, oct1, oct2, inc2);
                    }
                    printf(" %d.%d.255.255\n",  oct1, oct2);
                }

             // dual testing done
                //if(incOct == 4)
                else
                {
                //printf(" %d.%d.0.0\n",  oct1, oct2);
                //printf(" %d.%d.0.%d\n",  oct1, oct2, inc);

                    for(j = 0; j<256; j++)
                    {
                        printf(" %d.%d.%d.%d    -    ",  oct1, oct2, j, 0);
                        inc2 = 0;

                        for(i = 2; i <= ((256/inc)); i++ )
                        {
                            inc2 = inc2+inc;
                            printf(" %d.%d.%d.%d\n",  oct1, oct2, j, inc2-1);
                            printf(" %d.%d.%d.%d    -    ",  oct1, oct2, j, inc2);

                        }
                        printf(" %d.%d.%d.255\n",  oct1, oct2, j);
                    }
                }
            }

            //dual testing done. 1 bug found.
            //else if (oct1>=192 && oct1<=223)
            else
            {
                printf("The network ID/address of the entered address is- %d.%d.%d.0\n",oct1, oct2, oct3);
                printf("The broadcast address of the entered address is- %d.%d.%d.255\n",oct1, oct2, oct3);

                printf("\nPress any key to display all the %d networks below...\n\n", snw);
                getch();

                printf("\nThe detalis of sub-networks is as follows: \n\n");
                printf("1. %d.%d.%d.0    -    ",oct1, oct2, oct3);

                for(i = 2; i <= ((256/inc)); i++ )
                {
                    inc2 = inc2+inc;
                    printf(" %d.%d.%d.%d\n",  oct1, oct2, oct3, inc2-1);
                    printf("%d. %d.%d.%d.%d    -    ", i, oct1, oct2, oct3, inc2);
                }
                printf(" %d.%d.%d.255\n",  oct1, oct2, oct3);

            }
            if (choice ==1)
            printf("\n\nYou can choose any number of networks from these ranges. All of them have equal number of hosts. \n\n");

            if(choice == 2)
            printf("\n\nYou can choose any %d networks from this range. \n\n", snw);

    return 0;
}


int functionDisplayBegin(chBegin)
{
    scanf("%c", &chBegin);
    switch (chBegin)
    {
        case '1':
            printf("\n\n\tYou have now entered the module 1: IP Subnetting\n");
            break;
        case '2':
            printf("\n\n\tYou have now entered the module 2: IP subnetting by Reverse Engineering\n");
            revEng();
            break;
        default :
            break;
    }

        while(chBegin != '1' && chBegin != '2')
        {
            printf("\n\tInvalid choice. Wish you knew what are alphabets. \n");
            printf("\tEnter either 1 or 2-");

            functionDisplayBegin(chBegin);
        }

        return 0;

}



int revEng()
{
    int oct1, oct2, oct3, oct4;
    int i;
    printf("Please fill in the details of the IP address-\n\n");
    printf("First octate: ");
    scanf("%i", &oct1);

    for(i=0; i<=1000000; i++)
    {

        while(oct1<1 || oct1>255)
        {
            printf("Invalid number entered! Kindly try again.\n");
            printf("First octate: ");
            scanf("%i", &oct1);
        }
        while(oct1>223 && oct1<=255)
        {
            printf("You can't enter this number. Such IPs are reserved for government and research purposes. Kindly try again.\n");
            printf("First octate: ");
            scanf("%i", &oct1);
        }
    }
    printf("Second octate: ");
    scanf("%i", &oct2);
    while(oct2<0 || oct2>255)
    {
        printf("Invalid number entered! Kindly try again.\n");
        printf("Second octate: ");
        scanf("%i", &oct2);
    }
    printf("Third octate: ");
    scanf("%i", &oct3);
    while(oct3<0 || oct3>255)
    {
        printf("Invalid number entered! Kindly try again.\n");
        printf("Third octate: ");
        scanf("%i", &oct3);
    }
    printf("Fourth octate: ");
    scanf("%i", &oct4);
    while(oct4<0 || oct4>255)
    {
        printf("Invalid number entered! Kindly try again.\n");
        printf("Fourth octate: ");
        scanf("%i", &oct4);
    }
    printf("\n\nEntered IP address is %i.%i.%i.%i\n", oct1,oct2,oct3,oct4);

    if (oct1>=1 && oct1<=126)
    {
        printf("This is class A IP address. Default subnet mask= 255.0.0.0\n\n");
        validsmaskA(oct1, oct2, oct3);
    }
    else
    {
        if(oct1>=128 && oct1<=191)
        {
            printf("This is class B IP address. Default subnet mask= 255.255.0.0\n\n");
            validsmaskB(oct1, oct2, oct3);

        }
        else
        {
            printf("This is class C IP address. Default subnet mask= 255.255.255.0\n\n");
            validsmaskC(oct1, oct2, oct3);
        }
    }
    exit(0);
    return 0;
}



int validsmaskA(int oct1, int oct2, int oct3)
    {
            int i, inc, incOct;
            int bitsBorrowed, snw, hpsnw, totalnwb, bsize, totalhb, flash;
            char smaskuser[15] = "\0";


            char smaska111[15] = {'2', '5', '5', '.', '0', '.', '0', '.', '0', '\0', '\0', '\0', '\0', '\0', '\0'};
            char smaska112[15] = {'2', '5', '5', '.', '0', '.', '0', '.', '0', '0', '\0', '\0', '\0', '\0', '\0'};
            char smaska113[15] = {'2', '5', '5', '.', '0', '.', '0', '.', '0', '0', '0', '\0', '\0', '\0', '\0'};
            char smaska114[15] = {'2', '5', '5', '.', '0', '.', '0', '0', '.', '0', '\0', '\0', '\0', '\0', '\0'};
            char smaska115[15] = {'2', '5', '5', '.', '0', '.', '0', '0', '.', '0', '0', '\0', '\0', '\0', '\0'};
            char smaska116[15] = {'2', '5', '5', '.', '0', '.', '0', '0', '.', '0', '0', '0', '\0', '\0', '\0'};
            char smaska117[15] = {'2', '5', '5', '.', '0', '.', '0', '0', '0', '.', '0', '\0', '\0', '\0', '\0'};
            char smaska118[15] = {'2', '5', '5', '.', '0', '.', '0', '0', '0', '.', '0', '0', '\0', '\0', '\0'};
            char smaska119[15] = {'2', '5', '5', '.', '0', '.', '0', '0', '0', '.', '0', '0', '0', '\0', '\0'};

            char smaska121[15] = {'2', '5', '5', '.', '0', '0', '.', '0', '.', '0', '\0', '\0', '\0', '\0', '\0'};
            char smaska122[15] = {'2', '5', '5', '.', '0', '0', '.', '0', '.', '0', '0', '\0', '\0', '\0', '\0'};
            char smaska123[15] = {'2', '5', '5', '.', '0', '0', '.', '0', '.', '0', '0', '0', '\0', '\0', '\0'};
            char smaska124[15] = {'2', '5', '5', '.', '0', '0', '.', '0', '0', '.', '0', '\0', '\0', '\0', '\0'};
            char smaska125[15] = {'2', '5', '5', '.', '0', '0', '.', '0', '0', '.', '0', '0', '\0', '\0', '\0'};
            char smaska126[15] = {'2', '5', '5', '.', '0', '0', '.', '0', '0', '.', '0', '0', '0', '\0', '\0'};
            char smaska127[15] = {'2', '5', '5', '.', '0', '0', '.', '0', '0', '0', '.', '0', '\0', '\0', '\0'};
            char smaska128[15] = {'2', '5', '5', '.', '0', '0', '.', '0', '0', '0', '.', '0', '0', '\0', '\0'};
            char smaska129[15] = {'2', '5', '5', '.', '0', '0', '.', '0', '0', '0', '.', '0', '0', '0', '\0'};

            char smaska131[15] = {'2', '5', '5', '.', '0', '0', '0', '.', '0', '.', '0', '\0', '\0', '\0', '\0'};
            char smaska132[15] = {'2', '5', '5', '.', '0', '0', '0', '.', '0', '.', '0', '0', '\0', '\0', '\0'};
            char smaska133[15] = {'2', '5', '5', '.', '0', '0', '0', '.', '0', '.', '0', '0', '0', '\0', '\0'};
            char smaska134[15] = {'2', '5', '5', '.', '0', '0', '0', '.', '0', '0', '.', '0', '\0', '\0', '\0'};
            char smaska135[15] = {'2', '5', '5', '.', '0', '0', '0', '.', '0', '0', '.', '0', '0', '\0', '\0'};
            char smaska136[15] = {'2', '5', '5', '.', '0', '0', '0', '.', '0', '0', '.', '0', '0', '0', '\0'};
            char smaska137[15] = {'2', '5', '5', '.', '0', '0', '0', '.', '0', '0', '0', '.', '0', '\0', '\0'};
            char smaska138[15] = {'2', '5', '5', '.', '0', '0', '0', '.', '0', '0', '0', '.', '0', '0', '\0'};
            char smaska139[15] = {'2', '5', '5', '.', '0', '0', '0', '.', '0', '0', '0', '.', '0', '0', '0'};


            char smaska21281[15] = {'2', '5', '5', '.', '1', '2', '8', '.', '0', '.', '0', '\0', '\0', '\0', '\0'};
            char smaska21282[15] = {'2', '5', '5', '.', '1', '2', '8', '.', '0', '.', '0', '0', '\0', '\0', '\0'};
            char smaska21283[15] = {'2', '5', '5', '.', '1', '2', '8', '.', '0', '.', '0', '0', '0', '\0', '\0'};
            char smaska21284[15] = {'2', '5', '5', '.', '1', '2', '8', '.', '0', '0', '.', '0', '\0', '\0', '\0'};
            char smaska21285[15] = {'2', '5', '5', '.', '1', '2', '8', '.', '0', '0', '.', '0', '0', '\0', '\0'};
            char smaska21286[15] = {'2', '5', '5', '.', '1', '2', '8', '.', '0', '0', '.', '0', '0', '0', '\0'};
            char smaska21287[15] = {'2', '5', '5', '.', '1', '2', '8', '.', '0', '0', '0', '.', '0', '\0', '\0'};
            char smaska21288[15] = {'2', '5', '5', '.', '1', '2', '8', '.', '0', '0', '0', '.', '0', '0', '\0'};
            char smaska21289[15] = {'2', '5', '5', '.', '1', '2', '8', '.', '0', '0', '0', '.', '0', '0', '0'};


            char smaska21921[15] = {'2', '5', '5', '.', '1', '9', '2', '.', '0', '.', '0', '\0', '\0', '\0', '\0'};
            char smaska21922[15] = {'2', '5', '5', '.', '1', '9', '2', '.', '0', '.', '0', '0', '\0', '\0', '\0'};
            char smaska21923[15] = {'2', '5', '5', '.', '1', '9', '2', '.', '0', '.', '0', '0', '0', '\0', '\0'};
            char smaska21924[15] = {'2', '5', '5', '.', '1', '9', '2', '.', '0', '0', '.', '0', '\0', '\0', '\0'};
            char smaska21925[15] = {'2', '5', '5', '.', '1', '9', '2', '.', '0', '0', '.', '0', '0', '\0', '\0'};
            char smaska21926[15] = {'2', '5', '5', '.', '1', '9', '2', '.', '0', '0', '.', '0', '0', '0', '\0'};
            char smaska21927[15] = {'2', '5', '5', '.', '1', '9', '2', '.', '0', '0', '0', '.', '0', '\0', '\0'};
            char smaska21928[15] = {'2', '5', '5', '.', '1', '9', '2', '.', '0', '0', '0', '.', '0', '0', '\0'};
            char smaska21929[15] = {'2', '5', '5', '.', '1', '9', '2', '.', '0', '0', '0', '.', '0', '0', '0'};


            char smaska22241[15] = {'2', '5', '5', '.', '2', '2', '4', '.', '0', '.', '0', '\0', '\0', '\0', '\0'};
            char smaska22242[15] = {'2', '5', '5', '.', '2', '2', '4', '.', '0', '.', '0', '0', '\0', '\0', '\0'};
            char smaska22243[15] = {'2', '5', '5', '.', '2', '2', '4', '.', '0', '.', '0', '0', '0', '\0', '\0'};
            char smaska22244[15] = {'2', '5', '5', '.', '2', '2', '4', '.', '0', '0', '.', '0', '\0', '\0', '\0'};
            char smaska22245[15] = {'2', '5', '5', '.', '2', '2', '4', '.', '0', '0', '.', '0', '0', '\0', '\0'};
            char smaska22246[15] = {'2', '5', '5', '.', '2', '2', '4', '.', '0', '0', '.', '0', '0', '0', '\0'};
            char smaska22247[15] = {'2', '5', '5', '.', '2', '2', '4', '.', '0', '0', '0', '.', '0', '\0', '\0'};
            char smaska22248[15] = {'2', '5', '5', '.', '2', '2', '4', '.', '0', '0', '0', '.', '0', '0', '\0'};
            char smaska22249[15] = {'2', '5', '5', '.', '2', '2', '4', '.', '0', '0', '0', '.', '0', '0', '0'};


            char smaska22401[15] = {'2', '5', '5', '.', '2', '4', '0', '.', '0', '.', '0', '\0', '\0', '\0', '\0'};
            char smaska22402[15] = {'2', '5', '5', '.', '2', '4', '0', '.', '0', '.', '0', '0', '\0', '\0', '\0'};
            char smaska22403[15] = {'2', '5', '5', '.', '2', '4', '0', '.', '0', '.', '0', '0', '0', '\0', '\0'};
            char smaska22404[15] = {'2', '5', '5', '.', '2', '4', '0', '.', '0', '0', '.', '0', '\0', '\0', '\0'};
            char smaska22405[15] = {'2', '5', '5', '.', '2', '4', '0', '.', '0', '0', '.', '0', '0', '\0', '\0'};
            char smaska22406[15] = {'2', '5', '5', '.', '2', '4', '0', '.', '0', '0', '.', '0', '0', '0', '\0'};
            char smaska22407[15] = {'2', '5', '5', '.', '2', '4', '0', '.', '0', '0', '0', '.', '0', '\0', '\0'};
            char smaska22408[15] = {'2', '5', '5', '.', '2', '4', '0', '.', '0', '0', '0', '.', '0', '0', '\0'};
            char smaska22409[15] = {'2', '5', '5', '.', '2', '4', '0', '.', '0', '0', '0', '.', '0', '0', '0'};


            char smaska22481[15] = {'2', '5', '5', '.', '2', '4', '8', '.', '0', '.', '0', '\0', '\0', '\0', '\0'};
            char smaska22482[15] = {'2', '5', '5', '.', '2', '4', '8', '.', '0', '.', '0', '0', '\0', '\0', '\0'};
            char smaska22483[15] = {'2', '5', '5', '.', '2', '4', '8', '.', '0', '.', '0', '0', '0', '\0', '\0'};
            char smaska22484[15] = {'2', '5', '5', '.', '2', '4', '8', '.', '0', '0', '.', '0', '\0', '\0', '\0'};
            char smaska22485[15] = {'2', '5', '5', '.', '2', '4', '8', '.', '0', '0', '.', '0', '0', '\0', '\0'};
            char smaska22486[15] = {'2', '5', '5', '.', '2', '4', '8', '.', '0', '0', '.', '0', '0', '0', '\0'};
            char smaska22487[15] = {'2', '5', '5', '.', '2', '4', '8', '.', '0', '0', '0', '.', '0', '\0', '\0'};
            char smaska22488[15] = {'2', '5', '5', '.', '2', '4', '8', '.', '0', '0', '0', '.', '0', '0', '\0'};
            char smaska22489[15] = {'2', '5', '5', '.', '2', '4', '8', '.', '0', '0', '0', '.', '0', '0', '0'};


            char smaska22521[15] = {'2', '5', '5', '.', '2', '5', '2', '.', '0', '.', '0', '\0', '\0', '\0', '\0'};
            char smaska22522[15] = {'2', '5', '5', '.', '2', '5', '2', '.', '0', '.', '0', '0', '\0', '\0', '\0'};
            char smaska22523[15] = {'2', '5', '5', '.', '2', '5', '2', '.', '0', '.', '0', '0', '0', '\0', '\0'};
            char smaska22524[15] = {'2', '5', '5', '.', '2', '5', '2', '.', '0', '0', '.', '0', '\0', '\0', '\0'};
            char smaska22525[15] = {'2', '5', '5', '.', '2', '5', '2', '.', '0', '0', '.', '0', '0', '\0', '\0'};
            char smaska22526[15] = {'2', '5', '5', '.', '2', '5', '2', '.', '0', '0', '.', '0', '0', '0', '\0'};
            char smaska22527[15] = {'2', '5', '5', '.', '2', '5', '2', '.', '0', '0', '0', '.', '0', '\0', '\0'};
            char smaska22528[15] = {'2', '5', '5', '.', '2', '5', '2', '.', '0', '0', '0', '.', '0', '0', '\0'};
            char smaska22529[15] = {'2', '5', '5', '.', '2', '5', '2', '.', '0', '0', '0', '.', '0', '0', '0'};


            char smaska22541[15] = {'2', '5', '5', '.', '2', '5', '4', '.', '0', '.', '0', '\0', '\0', '\0', '\0'};
            char smaska22542[15] = {'2', '5', '5', '.', '2', '5', '4', '.', '0', '.', '0', '0', '\0', '\0', '\0'};
            char smaska22543[15] = {'2', '5', '5', '.', '2', '5', '4', '.', '0', '.', '0', '0', '0', '\0', '\0'};
            char smaska22544[15] = {'2', '5', '5', '.', '2', '5', '4', '.', '0', '0', '.', '0', '\0', '\0', '\0'};
            char smaska22545[15] = {'2', '5', '5', '.', '2', '5', '4', '.', '0', '0', '.', '0', '0', '\0', '\0'};
            char smaska22546[15] = {'2', '5', '5', '.', '2', '5', '4', '.', '0', '0', '.', '0', '0', '0', '\0'};
            char smaska22547[15] = {'2', '5', '5', '.', '2', '5', '4', '.', '0', '0', '0', '.', '0', '\0', '\0'};
            char smaska22548[15] = {'2', '5', '5', '.', '2', '5', '4', '.', '0', '0', '0', '.', '0', '0', '\0'};
            char smaska22549[15] = {'2', '5', '5', '.', '2', '5', '4', '.', '0', '0', '0', '.', '0', '0', '0'};


            char smaska22551[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '0', '.', '0', '\0', '\0', '\0', '\0'};
            char smaska22552[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '0', '.', '0', '0', '\0', '\0', '\0'};
            char smaska22553[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '0', '.', '0', '0', '0', '\0', '\0'};
            char smaska22554[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '0', '0', '.', '0', '\0', '\0', '\0'};
            char smaska22555[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '0', '0', '.', '0', '0', '\0', '\0'};
            char smaska22556[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '0', '0', '.', '0', '0', '0', '\0'};
            char smaska22557[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '0', '0', '0', '.', '0', '\0', '\0'};
            char smaska22558[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '0', '0', '0', '.', '0', '0', '\0'};
            char smaska22559[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '0', '0', '0', '.', '0', '0', '0'};


            char smaska31281[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '1', '2', '8', '.', '0', '\0', '\0'};
            char smaska31282[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '1', '2', '8', '.', '0', '0', '\0'};
            char smaska31283[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '1', '2', '8', '.', '0', '0', '0'};

            char smaska31921[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '1', '9', '2', '.', '0', '\0', '\0'};
            char smaska31922[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '1', '9', '2', '.', '0', '0', '\0'};
            char smaska31923[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '1', '9', '2', '.', '0', '0', '0'};

            char smaska32241[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '2', '4', '.', '0', '\0', '\0'};
            char smaska32242[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '2', '4', '.', '0', '0', '\0'};
            char smaska32243[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '2', '4', '.', '0', '0', '0'};

            char smaska32401[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '4', '0', '.', '0', '\0', '\0'};
            char smaska32402[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '4', '0', '.', '0', '0', '\0'};
            char smaska32403[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '4', '0', '.', '0', '0', '0'};

            char smaska32481[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '4', '8', '.', '0', '\0', '\0'};
            char smaska32482[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '4', '8', '.', '0', '0', '\0'};
            char smaska32483[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '4', '8', '.', '0', '0', '0'};

            char smaska32521[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '2', '.', '0', '\0', '\0'};
            char smaska32522[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '2', '.', '0', '0', '\0'};
            char smaska32523[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '2', '.', '0', '0', '0'};

            char smaska32541[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '4', '.', '0', '\0', '\0'};
            char smaska32542[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '4', '.', '0', '0', '\0'};
            char smaska32543[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '4', '.', '0', '0', '0'};


            char smaska32551[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '5', '.', '0', '\0', '\0'};
            char smaska32552[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '5', '.', '0', '0', '\0'};
            char smaska32553[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '5', '.', '0', '0', '0'};


            char smaska4128[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '5', '.', '1', '2', '8'};
            char smaska4192[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '5', '.', '1', '9', '2'};
            char smaska4224[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '5', '.', '2', '2', '4'};
            char smaska4240[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '5', '.', '2', '4', '0'};
            char smaska4248[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '5', '.', '2', '4', '8'};
            char smaska4252[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '2'};
            //char smaskc8[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '4'};


            printf("\n\tEnter the subnet mask which your network is to be masked with-  \n\t");
            printf("\n\n\tNote: Only first 15 entered characters will be taken into account \n\tbecause that's all you need to enter a valid subnet mask address.\n");
            printf("\n\n\t*Kindly enter no less or no more than 15 digits in your subnet mask.\n\n");
            printf("Subnet mask: ");

            fflush(stdin);
            gets(smaskuser);

            for(i = 0; i < 15; i++)
            {
                while(smaskuser[i] != smaska111[i] && smaskuser[i] != smaska112[i] && smaskuser[i] != smaska113[i] && smaskuser[i] != smaska114[i] &&
                            smaskuser[i] != smaska115[i] && smaskuser[i] != smaska116[i] && smaskuser[i] != smaska117[i] && smaskuser[i] != smaska118[i] &&
                            smaskuser[i] != smaska119[i] &&                                                               smaskuser[i] != smaska121[i] && smaskuser[i] != smaska122[i] &&
                            smaskuser[i] != smaska123[i] && smaskuser[i] != smaska124[i] && smaskuser[i] != smaska125[i] && smaskuser[i] != smaska126[i] &&
                            smaskuser[i] != smaska127[i] && smaskuser[i] != smaska128[i] && smaskuser[i] != smaska129[i] &&
                            smaskuser[i] != smaska131[i] && smaskuser[i] != smaska132[i] && smaskuser[i] != smaska133[i] && smaskuser[i] != smaska134[i] &&
                            smaskuser[i] != smaska135[i] && smaskuser[i] != smaska136[i] && smaskuser[i] != smaska137[i] && smaskuser[i] != smaska138[i] &&
                            smaskuser[i] != smaska139[i] &&

                            smaskuser[i] != smaska21281[i] && smaskuser[i] != smaska21282[i] && smaskuser[i] != smaska21283[i] &&
                            smaskuser[i] != smaska21284[i] && smaskuser[i] != smaska21285[i] && smaskuser[i] != smaska21286[i] &&
                            smaskuser[i] != smaska21287[i] && smaskuser[i] != smaska21288[i] && smaskuser[i] != smaska21289[i] &&

                            smaskuser[i] != smaska21921[i] && smaskuser[i] != smaska21922[i] && smaskuser[i] != smaska21923[i] &&
                            smaskuser[i] != smaska21924[i] && smaskuser[i] != smaska21925[i] && smaskuser[i] != smaska21926[i] &&
                            smaskuser[i] != smaska21927[i] && smaskuser[i] != smaska21928[i] && smaskuser[i] != smaska21929[i] &&

                            smaskuser[i] != smaska22241[i] && smaskuser[i] != smaska22242[i] && smaskuser[i] != smaska22243[i] &&
                            smaskuser[i] != smaska22244[i] && smaskuser[i] != smaska22245[i] && smaskuser[i] != smaska22246[i] &&
                            smaskuser[i] != smaska22247[i] && smaskuser[i] != smaska22248[i] && smaskuser[i] != smaska22249[i] &&

                            smaskuser[i] != smaska22401[i] && smaskuser[i] != smaska22402[i] && smaskuser[i] != smaska22403[i] &&
                            smaskuser[i] != smaska22404[i] && smaskuser[i] != smaska22405[i] && smaskuser[i] != smaska22406[i] &&
                            smaskuser[i] != smaska22407[i] && smaskuser[i] != smaska22408[i] && smaskuser[i] != smaska22409[i] &&

                            smaskuser[i] != smaska22481[i] && smaskuser[i] != smaska22482[i] && smaskuser[i] != smaska22483[i] &&
                            smaskuser[i] != smaska22484[i] && smaskuser[i] != smaska22485[i] && smaskuser[i] != smaska22486[i] &&
                            smaskuser[i] != smaska22487[i] && smaskuser[i] != smaska22488[i] && smaskuser[i] != smaska22489[i] &&

                            smaskuser[i] != smaska22521[i] && smaskuser[i] != smaska22522[i] && smaskuser[i] != smaska22523[i] &&
                            smaskuser[i] != smaska22524[i] && smaskuser[i] != smaska22525[i] && smaskuser[i] != smaska22526[i] &&
                            smaskuser[i] != smaska22527[i] && smaskuser[i] != smaska22528[i] && smaskuser[i] != smaska22529[i] &&

                            smaskuser[i] != smaska22541[i] && smaskuser[i] != smaska22542[i] && smaskuser[i] != smaska22543[i] &&
                            smaskuser[i] != smaska22544[i] && smaskuser[i] != smaska22545[i] && smaskuser[i] != smaska22546[i] &&
                            smaskuser[i] != smaska22547[i] && smaskuser[i] != smaska22548[i] && smaskuser[i] != smaska22549[i] &&

                            smaskuser[i] != smaska22551[i] && smaskuser[i] != smaska22552[i] && smaskuser[i] != smaska22553[i] &&
                            smaskuser[i] != smaska22554[i] && smaskuser[i] != smaska22555[i] && smaskuser[i] != smaska22556[i] &&
                            smaskuser[i] != smaska22557[i] && smaskuser[i] != smaska22558[i] && smaskuser[i] != smaska22559[i] &&

                            smaskuser[i] != smaska31281[i] && smaskuser[i] != smaska31282[i] && smaskuser[i] != smaska31283[i] &&
                            smaskuser[i] != smaska31921[i] && smaskuser[i] != smaska31922[i] && smaskuser[i] != smaska31923[i] &&
                            smaskuser[i] != smaska32241[i] && smaskuser[i] != smaska32242[i] && smaskuser[i] != smaska32243[i] &&
                            smaskuser[i] != smaska32401[i] && smaskuser[i] != smaska32402[i] && smaskuser[i] != smaska32403[i] &&
                            smaskuser[i] != smaska32481[i] && smaskuser[i] != smaska32482[i] && smaskuser[i] != smaska32483[i] &&
                            smaskuser[i] != smaska32521[i] && smaskuser[i] != smaska32522[i] && smaskuser[i] != smaska32523[i] &&
                            smaskuser[i] != smaska32541[i] && smaskuser[i] != smaska32542[i] && smaskuser[i] != smaska32543[i] &&
                            smaskuser[i] != smaska32551[i] && smaskuser[i] != smaska32552[i] && smaskuser[i] != smaska32553[i] &&

                            smaskuser[i] != smaska4128[i] && smaskuser[i] != smaska4192[i] && smaskuser[i] != smaska4224[i] &&
                            smaskuser[i] != smaska4240[i] && smaskuser[i] != smaska4248[i] && smaskuser[i] != smaska4252[i]
                      )
                {
                    printf("\nInvalid subnet mask entered! Try again.\n\t");
                    //char smaskuser[15] = "\0";
                    fflush(stdin);
                    gets(smaskuser);

                    i = 0;
                 }
            }



            if(smaskuser[4] == '0' && smaskuser[5] == '.' && smaskuser[6] == '0' && smaskuser[7] == '.' && smaskuser[8] == '0' &&smaskuser[9] == '\0' &&
                smaskuser[10] == '\0' && smaskuser[11] == '\0' && smaskuser[12] == '\0')
            {
                inc = 0, incOct = 0;

                printf("The entered subnet mask is:  255.0.0.0");
                bitsBorrowed = 0, snw = 0, totalnwb = 8, totalhb = 24, hpsnw = 16777214, flash = 8;
            }

            if(smaskuser[4] == '0' && smaskuser[5] == '.' && smaskuser[6] == '0' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '0' &&
                smaskuser[10] == '\0' && smaskuser[11] == '\0' && smaskuser[12] == '\0')
            {
                inc = 0, incOct = 0;

                printf("The entered subnet mask is:  255.0.0.0");
                bitsBorrowed = 0, snw = 0, totalnwb = 8, totalhb = 24, hpsnw = 16777214, flash = 8;
            }

            if(smaskuser[4] == '0' && smaskuser[5] == '.' && smaskuser[6] == '0' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '\0' &&
                smaskuser[10] == '0' && smaskuser[11] == '\0' && smaskuser[12] == '\0')
            {
                inc = 0, incOct = 0;

                printf("The entered subnet mask is:  255.0.0.0");
                bitsBorrowed = 0, snw = 0, totalnwb = 8, totalhb = 24, hpsnw = 16777214, flash = 8;
            }

            if(smaskuser[4] == '0' && smaskuser[5] == '.' && smaskuser[6] == '0' && smaskuser[7] == '0' && smaskuser[8] == '.' && smaskuser[9] == '0' &&
                smaskuser[10] == '\0' && smaskuser[11] == '\0' && smaskuser[12] == '\0')
            {
                inc = 0, incOct = 0;

                printf("The entered subnet mask is:  255.0.0.0");
                bitsBorrowed = 0, snw = 0, totalnwb = 8, totalhb = 24, hpsnw = 16777214, flash = 8;
            }

            if(smaskuser[4] == '0' && smaskuser[5] == '.' && smaskuser[6] == '0' && smaskuser[7] == '0' && smaskuser[8] == '.' && smaskuser[9] == '0' &&
                smaskuser[10] == '0' && smaskuser[11] == '\0' && smaskuser[12] == '\0')
            {
                inc = 0, incOct = 0;

                printf("The entered subnet mask is:  255.0.0.0");
                bitsBorrowed = 0, snw = 0, totalnwb = 8, totalhb = 24, hpsnw = 16777214, flash = 8;
            }

            if(smaskuser[4] == '0' && smaskuser[5] == '.' && smaskuser[6] == '0' && smaskuser[7] == '0' && smaskuser[8] == '.' && smaskuser[9] == '0' &&
                smaskuser[10] == '0' && smaskuser[11] == '\0' && smaskuser[12] == '\0')
            {
                inc = 0, incOct = 0;

                printf("The entered subnet mask is:  255.0.0.0");
                bitsBorrowed = 0, snw = 0, totalnwb = 8, totalhb = 24, hpsnw = 16777214, flash = 8;
            }

            if(smaskuser[4] == '0' && smaskuser[5] == '.' &&smaskuser[6] == '0' && smaskuser[7] == '0' && smaskuser[8] == '.' && smaskuser[9] == '0' &&
                smaskuser[10] == '0' && smaskuser[11] == '0' && smaskuser[12] == '\0')
            {
                inc = 0, incOct = 0;

                printf("The entered subnet mask is:  255.0.0.0");
                bitsBorrowed = 0, snw = 0, totalnwb = 8, totalhb = 24, hpsnw = 16777214, flash = 8;
            }

            if(smaskuser[4] == '0' && smaskuser[5] == '.' && smaskuser[6] == '0' && smaskuser[7] == '0' && smaskuser[8] == '0' && smaskuser[9] == '.' &&
                smaskuser[10] == '0' && smaskuser[11] == '\0' && smaskuser[12] == '\0')
            {
                inc = 0, incOct = 0;

                printf("The entered subnet mask is:  255.0.0.0");
                bitsBorrowed = 0, snw = 0, totalnwb = 8, totalhb = 24, hpsnw = 16777214, flash = 8;
            }

            if(smaskuser[4] == '0' && smaskuser[5] == '.' && smaskuser[6] == '0' && smaskuser[7] == '0' && smaskuser[8] == '0' && smaskuser[9] == '.' &&
                smaskuser[10] == '0' && smaskuser[11] == '0' && smaskuser[12] == '\0')
            {
                inc = 0, incOct = 0;

                printf("The entered subnet mask is:  255.0.0.0");
                bitsBorrowed = 0, snw = 0, totalnwb = 8, totalhb = 24, hpsnw = 16777214, flash = 8;
            }

            if(smaskuser[4] == '0' && smaskuser[5] == '.' && smaskuser[6] == '0' && smaskuser[7] == '0' && smaskuser[8] == '0' && smaskuser[9] == '.' &&
                smaskuser[10] == '0' && smaskuser[11] == '0' && smaskuser[12] == '0')
            {
                inc = 0, incOct = 0;

                printf("The entered subnet mask is:  255.0.0.0");
                bitsBorrowed = 0, snw = 0, totalnwb = 8, totalhb = 24, hpsnw = 16777214, flash = 8;
            }

            if(smaskuser[4] == '0' && smaskuser[5] == '0' && smaskuser[6] == '.' && smaskuser[7] == '0' && smaskuser[8] == '.' && smaskuser[9] == '0' &&
                smaskuser[10] == '\0' && smaskuser[11] == '\0' && smaskuser[12] == '\0' && smaskuser[13] == '\0')
            {
                inc = 0, incOct = 0;

                printf("The entered subnet mask is:  255.0.0.0");
                bitsBorrowed = 0, snw = 0, totalnwb = 8, totalhb = 24, hpsnw = 16777214, flash = 8;
            }

            if(smaskuser[4] == '0' && smaskuser[5] == '0' && smaskuser[6] == '.' && smaskuser[7] == '0' && smaskuser[8] == '.' && smaskuser[9] == '0' &&
                smaskuser[10] == '0' && smaskuser[11] == '\0' && smaskuser[12] == '\0' && smaskuser[13] == '\0')
            {
                inc = 0, incOct = 0;

                printf("The entered subnet mask is:  255.0.0.0");
                bitsBorrowed = 0, snw = 0, totalnwb = 8, totalhb = 24, hpsnw = 16777214, flash = 8;
            }

            if(smaskuser[4] == '0' && smaskuser[5] == '0' && smaskuser[6] == '.' && smaskuser[7] == '0' && smaskuser[8] == '.' && smaskuser[9] == '0' &&
                smaskuser[10] == '0' && smaskuser[11] == '0' && smaskuser[12] == '\0' && smaskuser[13] == '\0')
            {
                inc = 0, incOct = 0;

                printf("The entered subnet mask is:  255.0.0.0");
                bitsBorrowed = 0, snw = 0, totalnwb = 8, totalhb = 24, hpsnw = 16777214, flash = 8;
            }

            if(smaskuser[4] == '0' && smaskuser[5] == '0' && smaskuser[6] == '.' && smaskuser[7] == '0' && smaskuser[8] == '0' && smaskuser[9] == '.' &&
                smaskuser[10] == '0' && smaskuser[11] == '\0' && smaskuser[12] == '\0' && smaskuser[13] == '\0')
            {
                inc = 0, incOct = 0;

                printf("The entered subnet mask is:  255.0.0.0");
                bitsBorrowed = 0, snw = 0, totalnwb = 8, totalhb = 24, hpsnw = 16777214, flash = 8;
            }

            if(smaskuser[4] == '0' && smaskuser[5] == '0' && smaskuser[6] == '.' && smaskuser[7] == '0' && smaskuser[8] == '0' && smaskuser[9] == '.' &&
                smaskuser[10] == '0' && smaskuser[11] == '0' && smaskuser[12] == '\0' && smaskuser[13] == '\0')
            {
                inc = 0, incOct = 0;

                printf("The entered subnet mask is:  255.0.0.0");
                bitsBorrowed = 0, snw = 0, totalnwb = 8, totalhb = 24, hpsnw = 16777214, flash = 8;
            }

            if(smaskuser[4] == '0' && smaskuser[5] == '0' && smaskuser[6] == '.' && smaskuser[7] == '0' && smaskuser[8] == '0' && smaskuser[9] == '.' &&
                smaskuser[10] == '0' && smaskuser[11] == '0' && smaskuser[12] == '0' && smaskuser[13] == '\0')
            {
                inc = 0, incOct = 0;

                printf("The entered subnet mask is:  255.0.0.0");
                bitsBorrowed = 0, snw = 0, totalnwb = 8, totalhb = 24, hpsnw = 16777214, flash = 8;
            }

            if(smaskuser[4] == '0' && smaskuser[5] == '0' && smaskuser[6] == '.' && smaskuser[7] == '0' && smaskuser[8] == '0' && smaskuser[9] == '0' &&
                smaskuser[10] == '.' && smaskuser[11] == '0' && smaskuser[12] == '\0' && smaskuser[13] == '\0')
            {
                inc = 0, incOct = 0;

                printf("The entered subnet mask is:  255.0.0.0");
                bitsBorrowed = 0, snw = 0, totalnwb = 8, totalhb = 24, hpsnw = 16777214, flash = 8;
            }

            if(smaskuser[4] == '0' && smaskuser[5] == '0' && smaskuser[6] == '.' && smaskuser[7] == '0' && smaskuser[8] == '0' && smaskuser[9] == '0' &&
                smaskuser[10] == '.' && smaskuser[11] == '0' && smaskuser[12] == '0' && smaskuser[13] == '\0')
            {
                inc = 0, incOct = 0;

                printf("The entered subnet mask is:  255.0.0.0");
                bitsBorrowed = 0, snw = 0, totalnwb = 8, totalhb = 24, hpsnw = 16777214, flash = 8;
            }

            if(smaskuser[4] == '0' && smaskuser[5] == '0' && smaskuser[6] == '.' && smaskuser[7] == '0' && smaskuser[8] == '0' && smaskuser[9] == '0' &&
                smaskuser[10] == '.' && smaskuser[11] == '0' && smaskuser[12] == '0' && smaskuser[13] == '0')
            {
                inc = 0, incOct = 0;

                printf("The entered subnet mask is:  255.0.0.0");
                bitsBorrowed = 0, snw = 0, totalnwb = 8, totalhb = 24, hpsnw = 16777214, flash = 8;
            }

            if(smaskuser[4] == '0' && smaskuser[5] == '0' && smaskuser[6] == '0' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '.' &&
                smaskuser[10] == '0' && smaskuser[11] == '\0' && smaskuser[12] == '\0' && smaskuser[13] == '\0' && smaskuser[14] == '\0')
            {
                inc = 0, incOct = 0;

                printf("The entered subnet mask is:  255.0.0.0");
                bitsBorrowed = 0, snw = 0, totalnwb = 8, totalhb = 24, hpsnw = 16777214, flash = 8;
            }

            if(smaskuser[4] == '0' && smaskuser[5] == '0' &&smaskuser[6] == '0' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '.' &&
                smaskuser[10] == '0' && smaskuser[11] == '0' && smaskuser[12] == '\0' && smaskuser[13] == '\0' && smaskuser[14] == '\0')
            {
                inc = 0, incOct = 0;

                printf("The entered subnet mask is:  255.0.0.0");
                bitsBorrowed = 0, snw = 0, totalnwb = 8, totalhb = 24, hpsnw = 16777214, flash = 8;
            }

            if(smaskuser[4] == '0' && smaskuser[5] == '0' && smaskuser[6] == '0' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '.' &&
                smaskuser[10] == '0' && smaskuser[11] == '0' && smaskuser[12] == '0' && smaskuser[13] == '\0' && smaskuser[14] == '\0')
            {
                inc = 0, incOct = 0;

                printf("The entered subnet mask is:  255.0.0.0");
                bitsBorrowed = 0, snw = 0, totalnwb = 8, totalhb = 24, hpsnw = 16777214, flash = 8;
            }

            if(smaskuser[4] == '0' && smaskuser[5] == '0' && smaskuser[6] == '0' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '0' &&
                smaskuser[10] == '.' && smaskuser[11] == '0' && smaskuser[12] == '\0' && smaskuser[13] == '\0' && smaskuser[14] == '\0')
            {
                inc = 0, incOct = 0;

                printf("The entered subnet mask is:  255.0.0.0");
                bitsBorrowed = 0, snw = 0, totalnwb = 8, totalhb = 24, hpsnw = 16777214, flash = 8;
            }

            if(smaskuser[4] == '0' && smaskuser[5] == '0' && smaskuser[6] == '0' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '0' &&
                smaskuser[10] == '.' && smaskuser[11] == '0' && smaskuser[12] == '0' && smaskuser[13] == '\0' && smaskuser[14] == '\0')
            {
                inc = 0, incOct = 0;

                printf("The entered subnet mask is:  255.0.0.0");
                bitsBorrowed = 0, snw = 0, totalnwb = 8, totalhb = 24, hpsnw = 16777214, flash = 8;
            }

            if(smaskuser[4] == '0' && smaskuser[5] == '0' && smaskuser[6] == '0' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '0' &&
                smaskuser[10] == '.' && smaskuser[11] == '0' && smaskuser[12] == '0' && smaskuser[13] == '0' && smaskuser[14] == '\0')
            {
                inc = 0, incOct = 0;

                printf("The entered subnet mask is:  255.0.0.0");
                bitsBorrowed = 0, snw = 0, totalnwb = 8, totalhb = 24, hpsnw = 16777214, flash = 8;
            }

            if(smaskuser[4] == '0' && smaskuser[5] == '0' && smaskuser[6] == '0' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '0' &&
                smaskuser[10] == '0' && smaskuser[11] == '.' && smaskuser[12] == '0' && smaskuser[13] == '\0' && smaskuser[14] == '\0')
            {
                inc = 0, incOct = 0;

                printf("The entered subnet mask is:  255.0.0.0");
                bitsBorrowed = 0, snw = 0, totalnwb = 8, totalhb = 24, hpsnw = 16777214, flash = 8;
            }

            if(smaskuser[4] == '0' && smaskuser[5] == '0' && smaskuser[6] == '0' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '0' &&
                smaskuser[10] == '0' && smaskuser[11] == '.' && smaskuser[12] == '0' && smaskuser[13] == '0' && smaskuser[14] == '\0')
            {
                inc = 0, incOct = 0;

                printf("The entered subnet mask is:  255.0.0.0");
                bitsBorrowed = 0, snw = 0, totalnwb = 8, totalhb = 24, hpsnw = 16777214, flash = 8;
            }

            if(smaskuser[4] == '0' && smaskuser[5] == '0' && smaskuser[6] == '0' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '0' &&
                smaskuser[10] == '0' && smaskuser[11] == '.' && smaskuser[12] == '0' && smaskuser[13] == '0' && smaskuser[14] == '0')
            {
                inc = 0, incOct = 0;

                printf("The entered subnet mask is:  255.0.0.0");
                bitsBorrowed = 0, snw = 0, totalnwb = 8, totalhb = 24, hpsnw = 16777214, flash = 8;
            }

            if(smaskuser[4] == '1' && smaskuser[5] == '2' && smaskuser[6] == '8' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '.' &&
                smaskuser[10] == '0' && smaskuser[11] == '\0' && smaskuser[12] == '\0' && smaskuser[13] == '\0' && smaskuser[14] == '\0')
            {
                inc = 128, incOct = 2;

                printf("The entered subnet mask is:  255.128.0.0");
                bitsBorrowed = 1, snw = 2, totalnwb = 9, totalhb = 23, hpsnw = 8388606, flash = 9;
            }

            if(smaskuser[4] == '1' && smaskuser[5] == '2' && smaskuser[6] == '8' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '.' &&
                smaskuser[10] == '0' && smaskuser[11] == '0' && smaskuser[12] == '\0' && smaskuser[13] == '\0' && smaskuser[14] == '\0')
            {
                inc = 128, incOct = 2;

                printf("The entered subnet mask is:  255.128.0.0");
                bitsBorrowed = 1, snw = 2, totalnwb = 9, totalhb = 23, hpsnw = 8388606, flash = 9;
            }

            if(smaskuser[4] == '1' && smaskuser[5] == '2' && smaskuser[6] == '8' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '.' &&
                smaskuser[10] == '0' && smaskuser[11] == '0' && smaskuser[12] == '0' && smaskuser[13] == '\0' && smaskuser[14] == '\0')
            {
                inc = 128, incOct = 2;

                printf("The entered subnet mask is:  255.128.0.0");
                bitsBorrowed = 1, snw = 2, totalnwb = 9, totalhb = 23, hpsnw = 8388606, flash = 9;
            }

            if(smaskuser[4] == '1' && smaskuser[5] == '2' && smaskuser[6] == '8' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '0' &&
                smaskuser[10] == '.' && smaskuser[11] == '0' && smaskuser[12] == '\0' && smaskuser[13] == '\0' && smaskuser[14] == '\0')
            {
                inc = 128, incOct = 2;

                printf("The entered subnet mask is:  255.128.0.0");
                bitsBorrowed = 1, snw = 2, totalnwb = 9, totalhb = 23, hpsnw = 8388606, flash = 9;
            }

            if(smaskuser[4] == '1' && smaskuser[5] == '2' && smaskuser[6] == '8' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '0' &&
                smaskuser[10] == '.' && smaskuser[11] == '0' && smaskuser[12] == '0' && smaskuser[13] == '\0' && smaskuser[14] == '\0')
            {
                inc = 128, incOct = 2;

                printf("The entered subnet mask is:  255.128.0.0");
                bitsBorrowed = 1, snw = 2, totalnwb = 9, totalhb = 23, hpsnw = 8388606, flash = 9;
            }

            if(smaskuser[4] == '1' && smaskuser[5] == '2' && smaskuser[6] == '8' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '0' &&
                smaskuser[10] == '.' && smaskuser[11] == '0' && smaskuser[12] == '0' && smaskuser[13] == '0' && smaskuser[14] == '\0')
            {
                inc = 128, incOct = 2;

                printf("The entered subnet mask is:  255.128.0.0");
                bitsBorrowed = 1, snw = 2, totalnwb = 9, totalhb = 23, hpsnw = 8388606, flash = 9;
            }

            if(smaskuser[4] == '1' && smaskuser[5] == '2' && smaskuser[6] == '8' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '0' &&
                smaskuser[10] == '0' && smaskuser[11] == '.' && smaskuser[12] == '0' && smaskuser[13] == '\0' && smaskuser[14] == '\0')
            {
                inc = 128, incOct = 2;

                printf("The entered subnet mask is:  255.128.0.0");
                bitsBorrowed = 1, snw = 2, totalnwb = 9, totalhb = 23, hpsnw = 8388606, flash = 9;
            }

            if(smaskuser[4] == '1' && smaskuser[5] == '2' && smaskuser[6] == '8' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '0' &&
                smaskuser[10] == '0' && smaskuser[11] == '.' && smaskuser[12] == '0' && smaskuser[13] == '0' && smaskuser[14] == '\0')
            {
                inc = 128, incOct = 2;

                printf("The entered subnet mask is:  255.128.0.0");
                bitsBorrowed = 1, snw = 2, totalnwb = 9, totalhb = 23, hpsnw = 8388606, flash = 9;
            }

            if(smaskuser[4] == '1' && smaskuser[5] == '2' && smaskuser[6] == '8' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '0' &&
                smaskuser[10] == '0' && smaskuser[11] == '.' && smaskuser[12] == '0' && smaskuser[13] == '0' && smaskuser[14] == '0')
            {
                inc = 128, incOct = 2;

                printf("The entered subnet mask is:  255.128.0.0");
                bitsBorrowed = 1, snw = 2, totalnwb = 9, totalhb = 23, hpsnw = 8388606, flash = 9;
            }

            if(smaskuser[4] == '1' && smaskuser[5] == '9' && smaskuser[6] == '2' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '.' &&
                smaskuser[10] == '0' && smaskuser[11] == '\0' && smaskuser[12] == '\0' && smaskuser[13] == '\0' && smaskuser[14] == '\0')
            {
                inc = 64, incOct = 2;

                printf("The entered subnet mask is:  255.192.0.0");
                bitsBorrowed = 2, snw = 4, totalnwb = 10, totalhb = 22, hpsnw = 4194302, flash = 10;
            }

            if(smaskuser[4] == '1' && smaskuser[5] == '9' && smaskuser[6] == '2' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '.' &&
                smaskuser[10] == '0' && smaskuser[11] == '0' && smaskuser[12] == '\0' && smaskuser[13] == '\0' && smaskuser[14] == '\0')
            {
                inc = 64, incOct = 2;

                printf("The entered subnet mask is:  255.192.0.0");
                bitsBorrowed = 2, snw = 4, totalnwb = 10, totalhb = 22, hpsnw = 4194302, flash = 10;
            }

            if(smaskuser[4] == '1' && smaskuser[5] == '9' && smaskuser[6] == '2' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '.' &&
                smaskuser[10] == '0' && smaskuser[11] == '0' && smaskuser[12] == '0' && smaskuser[13] == '\0' && smaskuser[14] == '\0')
            {
                inc = 64, incOct = 2;

                printf("The entered subnet mask is:  255.192.0.0");
                bitsBorrowed = 2, snw = 4, totalnwb = 10, totalhb = 22, hpsnw = 4194302, flash = 10;
            }

            if(smaskuser[4] == '1' && smaskuser[5] == '9' && smaskuser[6] == '2' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '0' &&
                smaskuser[10] == '.' && smaskuser[11] == '0' && smaskuser[12] == '\0' && smaskuser[13] == '\0' && smaskuser[14] == '\0')
            {
                inc = 64, incOct = 2;

                printf("The entered subnet mask is:  255.192.0.0");
                bitsBorrowed = 2, snw = 4, totalnwb = 10, totalhb = 22, hpsnw = 4194302, flash = 10;
            }

            if(smaskuser[4] == '1' && smaskuser[5] == '9' && smaskuser[6] == '2' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '0' &&
                smaskuser[10] == '.' && smaskuser[11] == '0' && smaskuser[12] == '0' && smaskuser[13] == '\0' && smaskuser[14] == '\0')
            {
                inc = 64, incOct = 2;

                printf("The entered subnet mask is:  255.192.0.0");
                bitsBorrowed = 2, snw = 4, totalnwb = 10, totalhb = 22, hpsnw = 4194302, flash = 10;
            }

            if(smaskuser[4] == '1' && smaskuser[5] == '9' && smaskuser[6] == '2' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '0' &&
                smaskuser[10] == '.' && smaskuser[11] == '0' && smaskuser[12] == '0' && smaskuser[13] == '0' && smaskuser[14] == '\0')
            {
                inc = 64, incOct = 2;

                printf("The entered subnet mask is:  255.192.0.0");
                bitsBorrowed = 2, snw = 4, totalnwb = 10, totalhb = 22, hpsnw = 4194302, flash = 10;
            }

            if(smaskuser[4] == '1' && smaskuser[5] == '9' && smaskuser[6] == '2' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '0' &&
                smaskuser[10] == '0' && smaskuser[11] == '.' && smaskuser[12] == '0' && smaskuser[13] == '\0' && smaskuser[14] == '\0')
            {
                inc = 64, incOct = 2;

                printf("The entered subnet mask is:  255.192.0.0");
                bitsBorrowed = 2, snw = 4, totalnwb = 10, totalhb = 22, hpsnw = 4194302, flash = 10;
            }

            if(smaskuser[4] == '1' && smaskuser[5] == '9' && smaskuser[6] == '2' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '0' &&
                smaskuser[10] == '0' && smaskuser[11] == '.' && smaskuser[12] == '0' && smaskuser[13] == '0' && smaskuser[14] == '\0')
            {
                inc = 64, incOct = 2;

                printf("The entered subnet mask is:  255.192.0.0");
                bitsBorrowed = 2, snw = 4, totalnwb = 10, totalhb = 22, hpsnw = 4194302, flash = 10;
            }

            if(smaskuser[4] == '1' && smaskuser[5] == '9' && smaskuser[6] == '2' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '0' &&
                smaskuser[10] == '0' && smaskuser[11] == '.' && smaskuser[12] == '0' && smaskuser[13] == '0' && smaskuser[14] == '0')
            {
                inc = 64, incOct = 2;

                printf("The entered subnet mask is:  255.192.0.0");
                bitsBorrowed = 2, snw = 4, totalnwb = 10, totalhb = 22, hpsnw = 4194302, flash = 10;
            }

            if(smaskuser[4] == '2' && smaskuser[5] == '2' && smaskuser[6] == '4' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '.' &&
                smaskuser[10] == '0' && smaskuser[11] == '\0' && smaskuser[12] == '\0' && smaskuser[13] == '\0' && smaskuser[14] == '\0')
            {
                inc = 32, incOct = 2;

                printf("The entered subnet mask is:  255.224.0.0");
                bitsBorrowed = 3, snw = 8, totalnwb = 11, totalhb = 21, hpsnw = 2097150, flash = 11;
            }

            if(smaskuser[4] == '2' && smaskuser[5] == '2' && smaskuser[6] == '4' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '.' &&
                smaskuser[10] == '0' && smaskuser[11] == '0' && smaskuser[12] == '\0' && smaskuser[13] == '\0' && smaskuser[14] == '\0')
            {
                inc = 32, incOct = 2;

                printf("The entered subnet mask is:  255.224.0.0");
                bitsBorrowed = 3, snw = 8, totalnwb = 11, totalhb = 21, hpsnw = 2097150, flash = 11;
            }

            if(smaskuser[4] == '2' && smaskuser[5] == '2' && smaskuser[6] == '4' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '.' &&
                smaskuser[10] == '0' && smaskuser[11] == '0' && smaskuser[12] == '0' && smaskuser[13] == '\0' && smaskuser[14] == '\0')
            {
                inc = 32, incOct = 2;

                printf("The entered subnet mask is:  255.224.0.0");
                bitsBorrowed = 3, snw = 8, totalnwb = 11, totalhb = 21, hpsnw = 2097150, flash = 11;
            }

            if(smaskuser[4] == '2' && smaskuser[5] == '2' && smaskuser[6] == '4' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '0' &&
                smaskuser[10] == '.' && smaskuser[11] == '0' && smaskuser[12] == '\0' && smaskuser[13] == '\0' && smaskuser[14] == '\0')
            {
                inc = 32, incOct = 2;

                printf("The entered subnet mask is:  255.224.0.0");
                bitsBorrowed = 3, snw = 8, totalnwb = 11, totalhb = 21, hpsnw = 2097150, flash = 11;
            }

            if(smaskuser[4] == '2' && smaskuser[5] == '2' && smaskuser[6] == '4' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '0' &&
                smaskuser[10] == '.' && smaskuser[11] == '0' && smaskuser[12] == '0' && smaskuser[13] == '\0' && smaskuser[14] == '\0')
            {
                inc = 32, incOct = 2;

                printf("The entered subnet mask is:  255.224.0.0");
                bitsBorrowed = 3, snw = 8, totalnwb = 11, totalhb = 21, hpsnw = 2097150, flash = 11;
            }

            if(smaskuser[4] == '2' && smaskuser[5] == '2' && smaskuser[6] == '4' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '0' &&
                smaskuser[10] == '.' && smaskuser[11] == '0' && smaskuser[12] == '0' && smaskuser[13] == '0' && smaskuser[14] == '\0')
            {
                inc = 32, incOct = 2;

                printf("The entered subnet mask is:  255.224.0.0");
                bitsBorrowed = 3, snw = 8, totalnwb = 11, totalhb = 21, hpsnw = 2097150, flash = 11;
            }

            if(smaskuser[4] == '2' && smaskuser[5] == '2' && smaskuser[6] == '4' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '0' &&
                smaskuser[10] == '0' && smaskuser[11] == '.' && smaskuser[12] == '0' && smaskuser[13] == '\0' && smaskuser[14] == '\0')
            {
                inc = 32, incOct = 2;

                printf("The entered subnet mask is:  255.224.0.0");
                bitsBorrowed = 3, snw = 8, totalnwb = 11, totalhb = 21, hpsnw = 2097150, flash = 11;
            }

            if(smaskuser[4] == '2' && smaskuser[5] == '2' && smaskuser[6] == '4' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '0' &&
                smaskuser[10] == '0' && smaskuser[11] == '.' && smaskuser[12] == '0' && smaskuser[13] == '0' && smaskuser[14] == '\0')
            {
                inc = 32, incOct = 2;

                printf("The entered subnet mask is:  255.224.0.0");
                bitsBorrowed = 3, snw = 8, totalnwb = 11, totalhb = 21, hpsnw = 2097150, flash = 11;
            }

            if(smaskuser[4] == '2' && smaskuser[5] == '2' && smaskuser[6] == '4' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '0' &&
                smaskuser[10] == '0' && smaskuser[11] == '.' && smaskuser[12] == '0' && smaskuser[13] == '0' && smaskuser[14] == '0')
            {
                inc = 32, incOct = 2;

                printf("The entered subnet mask is:  255.224.0.0");
                bitsBorrowed = 3, snw = 8, totalnwb = 11, totalhb = 21, hpsnw = 2097150, flash = 11;
            }

            if(smaskuser[4] == '2' && smaskuser[5] == '4' && smaskuser[6] == '0' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '.' &&
                smaskuser[10] == '0' && smaskuser[11] == '\0' && smaskuser[12] == '\0' && smaskuser[13] == '\0' && smaskuser[14] == '\0')
            {
                inc = 16, incOct = 2;

                printf("The entered subnet mask is:  255.240.0.0");
                bitsBorrowed = 4, snw = 16, totalnwb = 12, totalhb = 20, hpsnw = 1048574, flash = 12;
            }

            if(smaskuser[4] == '2' && smaskuser[5] == '4' && smaskuser[6] == '0' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '.' &&
                smaskuser[10] == '0' && smaskuser[11] == '0' && smaskuser[12] == '\0' && smaskuser[13] == '\0' && smaskuser[14] == '\0')
            {
                inc = 16, incOct = 2;

                printf("The entered subnet mask is:  255.240.0.0");
                bitsBorrowed = 4, snw = 16, totalnwb = 12, totalhb = 20, hpsnw = 1048574, flash = 12;
            }

            if(smaskuser[4] == '2' && smaskuser[5] == '4' && smaskuser[6] == '0' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '.' &&
                smaskuser[10] == '0' && smaskuser[11] == '0' && smaskuser[12] == '0' && smaskuser[13] == '\0' && smaskuser[14] == '\0')
            {
                inc = 16, incOct = 2;

                printf("The entered subnet mask is:  255.240.0.0");
                bitsBorrowed = 4, snw = 16, totalnwb = 12, totalhb = 20, hpsnw = 1048574, flash = 12;
            }

            if(smaskuser[4] == '2' && smaskuser[5] == '4' && smaskuser[6] == '0' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '0' &&
                smaskuser[10] == '.' && smaskuser[11] == '0' && smaskuser[12] == '\0' && smaskuser[13] == '\0' && smaskuser[14] == '\0')
            {
                inc = 16, incOct = 2;

                printf("The entered subnet mask is:  255.240.0.0");
                bitsBorrowed = 4, snw = 16, totalnwb = 12, totalhb = 20, hpsnw = 1048574, flash = 12;
            }

            if(smaskuser[4] == '2' && smaskuser[5] == '4' && smaskuser[6] == '0' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '0' &&
                smaskuser[10] == '.' && smaskuser[11] == '0' && smaskuser[12] == '0' && smaskuser[13] == '\0' && smaskuser[14] == '\0')
            {
                inc = 16, incOct = 2;

                printf("The entered subnet mask is:  255.240.0.0");
                bitsBorrowed = 4, snw = 16, totalnwb = 12, totalhb = 20, hpsnw = 1048574, flash = 12;
            }

            if(smaskuser[4] == '2' && smaskuser[5] == '4' && smaskuser[6] == '0' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '0' &&
                smaskuser[10] == '.' && smaskuser[11] == '0' && smaskuser[12] == '0' && smaskuser[13] == '0' && smaskuser[14] == '\0')
            {
                inc = 16, incOct = 2;

                printf("The entered subnet mask is:  255.240.0.0");
                bitsBorrowed = 4, snw = 16, totalnwb = 12, totalhb = 20, hpsnw = 1048574, flash = 12;
            }

            if(smaskuser[4] == '2' && smaskuser[5] == '4' && smaskuser[6] == '0' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '0' &&
                smaskuser[10] == '0' && smaskuser[11] == '.' && smaskuser[12] == '0' && smaskuser[13] == '\0' && smaskuser[14] == '\0')
            {
                inc = 16, incOct = 2;

                printf("The entered subnet mask is:  255.240.0.0");
                bitsBorrowed = 4, snw = 16, totalnwb = 12, totalhb = 20, hpsnw = 1048574, flash = 12;
            }

            if(smaskuser[4] == '2' && smaskuser[5] == '4' && smaskuser[6] == '0' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '0' &&
                smaskuser[10] == '0' && smaskuser[11] == '.' && smaskuser[12] == '0' && smaskuser[13] == '0' && smaskuser[14] == '\0')
            {
                inc = 16, incOct = 2;

                printf("The entered subnet mask is:  255.240.0.0");
                bitsBorrowed = 4, snw = 16, totalnwb = 12, totalhb = 20, hpsnw = 1048574, flash = 12;
            }

            if(smaskuser[4] == '2' && smaskuser[5] == '4' && smaskuser[6] == '0' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '0' &&
                smaskuser[10] == '0' && smaskuser[11] == '.' && smaskuser[12] == '0' && smaskuser[13] == '0' && smaskuser[14] == '0')
            {
                inc = 16, incOct = 2;

                printf("The entered subnet mask is:  255.240.0.0");
                bitsBorrowed = 4, snw = 16, totalnwb = 12, totalhb = 20, hpsnw = 1048574, flash = 12;
            }

            if(smaskuser[4] == '2' && smaskuser[5] == '4' && smaskuser[6] == '8' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '.' &&
                smaskuser[10] == '0' && smaskuser[11] == '\0' && smaskuser[12] == '\0' && smaskuser[13] == '\0' && smaskuser[14] == '\0')
            {
                inc = 8, incOct = 2;

                printf("The entered subnet mask is:  255.248.0.0");
                bitsBorrowed = 5, snw = 32, totalnwb = 13, totalhb = 19, hpsnw = 524286, flash = 13;
            }

            if(smaskuser[4] == '2' && smaskuser[5] == '4' && smaskuser[6] == '8' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '.' &&
                smaskuser[10] == '0' && smaskuser[11] == '0' && smaskuser[12] == '\0' && smaskuser[13] == '\0' && smaskuser[14] == '\0')
            {
                inc = 8, incOct = 2;

                printf("The entered subnet mask is:  255.248.0.0");
                bitsBorrowed = 5, snw = 32, totalnwb = 13, totalhb = 19, hpsnw = 524286, flash = 13;
            }

            if(smaskuser[4] == '2' && smaskuser[5] == '4' && smaskuser[6] == '8' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '.' &&
                smaskuser[10] == '0' && smaskuser[11] == '0' && smaskuser[12] == '0' && smaskuser[13] == '\0' && smaskuser[14] == '\0')
            {
                inc = 8, incOct = 2;

                printf("The entered subnet mask is:  255.248.0.0");
                bitsBorrowed = 5, snw = 32, totalnwb = 13, totalhb = 19, hpsnw = 524286, flash = 13;
            }

            if(smaskuser[4] == '2' && smaskuser[5] == '4' && smaskuser[6] == '8' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '0' &&
                smaskuser[10] == '.' && smaskuser[11] == '0' && smaskuser[12] == '\0' && smaskuser[13] == '\0' && smaskuser[14] == '\0')
            {
                inc = 8, incOct = 2;

                printf("The entered subnet mask is:  255.248.0.0");
                bitsBorrowed = 5, snw = 32, totalnwb = 13, totalhb = 19, hpsnw = 524286, flash = 13;
            }

            if(smaskuser[4] == '2' && smaskuser[5] == '4' && smaskuser[6] == '8' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '0' &&
                smaskuser[10] == '.' && smaskuser[11] == '0' && smaskuser[12] == '0' && smaskuser[13] == '\0' && smaskuser[14] == '\0')
            {
                inc = 8, incOct = 2;

                printf("The entered subnet mask is:  255.248.0.0");
                bitsBorrowed = 5, snw = 32, totalnwb = 13, totalhb = 19, hpsnw = 524286, flash = 13;
            }

            if(smaskuser[4] == '2' && smaskuser[5] == '4' && smaskuser[6] == '8' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '0' &&
                smaskuser[10] == '.' && smaskuser[11] == '0' && smaskuser[12] == '0' && smaskuser[13] == '0' && smaskuser[14] == '\0')
            {
                inc = 8, incOct = 2;

                printf("The entered subnet mask is:  255.248.0.0");
                bitsBorrowed = 5, snw = 32, totalnwb = 13, totalhb = 19, hpsnw = 524286, flash = 13;
            }

            if(smaskuser[4] == '2' && smaskuser[5] == '4' && smaskuser[6] == '8' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '0' &&
                smaskuser[10] == '0' && smaskuser[11] == '.' && smaskuser[12] == '0' && smaskuser[13] == '\0' && smaskuser[14] == '\0')
            {
                inc = 8, incOct = 2;

                printf("The entered subnet mask is:  255.248.0.0");
                bitsBorrowed = 5, snw = 32, totalnwb = 13, totalhb = 19, hpsnw = 524286, flash = 13;
            }

            if(smaskuser[4] == '2' && smaskuser[5] == '4' && smaskuser[6] == '8' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '0' &&
                smaskuser[10] == '0' && smaskuser[11] == '.' && smaskuser[12] == '0' && smaskuser[13] == '0' && smaskuser[14] == '\0')
            {
                inc = 8, incOct = 2;

                printf("The entered subnet mask is:  255.248.0.0");
                bitsBorrowed = 5, snw = 32, totalnwb = 13, totalhb = 19, hpsnw = 524286, flash = 13;
            }

            if(smaskuser[4] == '2' && smaskuser[5] == '4' && smaskuser[6] == '8' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '0' &&
                smaskuser[10] == '0' && smaskuser[11] == '.' && smaskuser[12] == '0' && smaskuser[13] == '0' && smaskuser[14] == '0')
            {
                inc = 8, incOct = 2;

                printf("The entered subnet mask is:  255.248.0.0");
                bitsBorrowed = 5, snw = 32, totalnwb = 13, totalhb = 19, hpsnw = 524286, flash = 13;
            }

            if(smaskuser[4] == '2' && smaskuser[5] == '5' && smaskuser[6] == '2' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '.' &&
                smaskuser[10] == '0' && smaskuser[11] == '\0' && smaskuser[12] == '\0' && smaskuser[13] == '\0' && smaskuser[14] == '\0')
            {
                inc = 4, incOct = 2;

                printf("The entered subnet mask is:  255.252.0.0");
                bitsBorrowed = 6, snw = 64, totalnwb = 14, totalhb = 18, hpsnw = 262142, flash = 14;
            }

            if(smaskuser[4] == '2' && smaskuser[5] == '5' && smaskuser[6] == '2' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '.' &&
                smaskuser[10] == '0' && smaskuser[11] == '0' && smaskuser[12] == '\0' && smaskuser[13] == '\0' && smaskuser[14] == '\0')
            {
                inc = 4, incOct = 2;

                printf("The entered subnet mask is:  255.252.0.0");
                bitsBorrowed = 6, snw = 64, totalnwb = 14, totalhb = 18, hpsnw = 262142, flash = 14;
            }

            if(smaskuser[4] == '2' && smaskuser[5] == '5' && smaskuser[6] == '2' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '.' &&
                smaskuser[10] == '0' && smaskuser[11] == '0' && smaskuser[12] == '0' && smaskuser[13] == '\0' && smaskuser[14] == '\0')
            {
                inc = 4, incOct = 2;

                printf("The entered subnet mask is:  255.252.0.0");
                bitsBorrowed = 6, snw = 64, totalnwb = 14, totalhb = 18, hpsnw = 262142, flash = 14;
            }

            if(smaskuser[4] == '2' && smaskuser[5] == '5' && smaskuser[6] == '2' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '0' &&
                smaskuser[10] == '.' && smaskuser[11] == '0' && smaskuser[12] == '\0' && smaskuser[13] == '\0' && smaskuser[14] == '\0')
            {
                inc = 4, incOct = 2;

                printf("The entered subnet mask is:  255.252.0.0");
                bitsBorrowed = 6, snw = 64, totalnwb = 14, totalhb = 18, hpsnw = 262142, flash = 14;
            }

            if(smaskuser[4] == '2' && smaskuser[5] == '5' && smaskuser[6] == '2' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '0' &&
                smaskuser[10] == '.' && smaskuser[11] == '0' && smaskuser[12] == '0' && smaskuser[13] == '\0' && smaskuser[14] == '\0')
            {
                inc = 4, incOct = 2;

                printf("The entered subnet mask is:  255.252.0.0");
                bitsBorrowed = 6, snw = 64, totalnwb = 14, totalhb = 18, hpsnw = 262142, flash = 14;
            }

            if(smaskuser[4] == '2' && smaskuser[5] == '5' && smaskuser[6] == '2' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '0' &&
                smaskuser[10] == '.' && smaskuser[11] == '0' && smaskuser[12] == '0' && smaskuser[13] == '0' && smaskuser[14] == '\0')
            {
                inc = 4, incOct = 2;

                printf("The entered subnet mask is:  255.252.0.0");
                bitsBorrowed = 6, snw = 64, totalnwb = 14, totalhb = 18, hpsnw = 262142, flash = 14;
            }

            if(smaskuser[4] == '2' && smaskuser[5] == '5' && smaskuser[6] == '2' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '0' &&
                smaskuser[10] == '0' && smaskuser[11] == '.' && smaskuser[12] == '0' && smaskuser[13] == '\0' && smaskuser[14] == '\0')
            {
                inc = 4, incOct = 2;

                printf("The entered subnet mask is:  255.252.0.0");
                bitsBorrowed = 6, snw = 64, totalnwb = 14, totalhb = 18, hpsnw = 262142, flash = 14;
            }

            if(smaskuser[4] == '2' && smaskuser[5] == '5' && smaskuser[6] == '2' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '0' &&
                smaskuser[10] == '0' && smaskuser[11] == '.' && smaskuser[12] == '0' && smaskuser[13] == '0' && smaskuser[14] == '\0')
            {
                inc = 4, incOct = 2;

                printf("The entered subnet mask is:  255.252.0.0");
                bitsBorrowed = 6, snw = 64, totalnwb = 14, totalhb = 18, hpsnw = 262142, flash = 14;
            }

            if(smaskuser[4] == '2' && smaskuser[5] == '5' && smaskuser[6] == '2' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '0' &&
                smaskuser[10] == '0' && smaskuser[11] == '.' && smaskuser[12] == '0' && smaskuser[13] == '0' && smaskuser[14] == '0')
            {
                inc = 4, incOct = 2;

                printf("The entered subnet mask is:  255.252.0.0");
                bitsBorrowed = 6, snw = 64, totalnwb = 14, totalhb = 18, hpsnw = 262142, flash = 14;
            }

            if(smaskuser[4] == '2' && smaskuser[5] == '5' && smaskuser[6] == '4' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '.' &&
                smaskuser[10] == '0' && smaskuser[11] == '\0' && smaskuser[12] == '\0' && smaskuser[13] == '\0' && smaskuser[14] == '\0')
            {
                inc = 2, incOct = 2;

                printf("The entered subnet mask is:  255.254.0.0");
                bitsBorrowed = 7, snw = 128, totalnwb = 15, totalhb = 17, hpsnw = 131070, flash = 15;
            }

            if(smaskuser[4] == '2' && smaskuser[5] == '5' && smaskuser[6] == '4' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '.' &&
                smaskuser[10] == '0' && smaskuser[11] == '0' && smaskuser[12] == '\0' && smaskuser[13] == '\0' && smaskuser[14] == '\0')
            {
                inc = 2, incOct = 2;

                printf("The entered subnet mask is:  255.254.0.0");
                bitsBorrowed = 7, snw = 128, totalnwb = 15, totalhb = 17, hpsnw = 131070, flash = 15;
            }

            if(smaskuser[4] == '2' && smaskuser[5] == '5' && smaskuser[6] == '4' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '.' &&
                smaskuser[10] == '0' && smaskuser[11] == '0' && smaskuser[12] == '0' && smaskuser[13] == '\0' && smaskuser[14] == '\0')
            {
                inc = 2, incOct = 2;

                printf("The entered subnet mask is:  255.254.0.0");
                bitsBorrowed = 7, snw = 128, totalnwb = 15, totalhb = 17, hpsnw = 131070, flash = 15;
            }

            if(smaskuser[4] == '2' && smaskuser[5] == '5' && smaskuser[6] == '4' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '0' &&
                smaskuser[10] == '.' && smaskuser[11] == '0' && smaskuser[12] == '\0' && smaskuser[13] == '\0' && smaskuser[14] == '\0')
            {
                inc = 2, incOct = 2;

                printf("The entered subnet mask is:  255.254.0.0");
                bitsBorrowed = 7, snw = 128, totalnwb = 15, totalhb = 17, hpsnw = 131070, flash = 15;
            }

            if(smaskuser[4] == '2' && smaskuser[5] == '5' && smaskuser[6] == '4' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '0' &&
                smaskuser[10] == '.' && smaskuser[11] == '0' && smaskuser[12] == '0' && smaskuser[13] == '\0' && smaskuser[14] == '\0')
            {
                inc = 2, incOct = 2;

                printf("The entered subnet mask is:  255.254.0.0");
                bitsBorrowed = 7, snw = 128, totalnwb = 15, totalhb = 17, hpsnw = 131070, flash = 15;
            }

            if(smaskuser[4] == '2' && smaskuser[5] == '5' && smaskuser[6] == '4' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '0' &&
                smaskuser[10] == '.' && smaskuser[11] == '0' && smaskuser[12] == '0' && smaskuser[13] == '0' && smaskuser[14] == '\0')
            {
                inc = 2, incOct = 2;

                printf("The entered subnet mask is:  255.254.0.0");
                bitsBorrowed = 7, snw = 128, totalnwb = 15, totalhb = 17, hpsnw = 131070, flash = 15;
            }

            if(smaskuser[4] == '2' && smaskuser[5] == '5' && smaskuser[6] == '4' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '0' &&
                smaskuser[10] == '0' && smaskuser[11] == '.' && smaskuser[12] == '0' && smaskuser[13] == '\0' && smaskuser[14] == '\0')
            {
                inc = 2, incOct = 2;

                printf("The entered subnet mask is:  255.254.0.0");
                bitsBorrowed = 7, snw = 128, totalnwb = 15, totalhb = 17, hpsnw = 131070, flash = 15;
            }

            if(smaskuser[4] == '2' && smaskuser[5] == '5' && smaskuser[6] == '4' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '0' &&
                smaskuser[10] == '0' && smaskuser[11] == '.' && smaskuser[12] == '0' && smaskuser[13] == '0' && smaskuser[14] == '\0')
            {
                inc = 2, incOct = 2;

                printf("The entered subnet mask is:  255.254.0.0");
                bitsBorrowed = 7, snw = 128, totalnwb = 15, totalhb = 17, hpsnw = 131070, flash = 15;
            }

            if(smaskuser[4] == '2' && smaskuser[5] == '5' && smaskuser[6] == '4' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '0' &&
                smaskuser[10] == '0' && smaskuser[11] == '.' && smaskuser[12] == '0' && smaskuser[13] == '0' && smaskuser[14] == '0')
            {
                inc = 2, incOct = 2;

                printf("The entered subnet mask is:  255.254.0.0");
                bitsBorrowed = 7, snw = 128, totalnwb = 15, totalhb = 17, hpsnw = 131070, flash = 15;
            }

            if(smaskuser[4] == '2' && smaskuser[5] == '5' && smaskuser[6] == '5' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '.' &&
                smaskuser[10] == '0' && smaskuser[11] == '\0' && smaskuser[12] == '\0' && smaskuser[13] == '\0' && smaskuser[14] == '\0')
            {
                inc = 1, incOct = 2;

                printf("The entered subnet mask is:  255.255.0.0");
                bitsBorrowed = 8, snw = 256, totalnwb = 16, totalhb = 16, hpsnw = 65534, flash = 16;
            }

            if(smaskuser[4] == '2' && smaskuser[5] == '5' && smaskuser[6] == '5' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '.' &&
                smaskuser[10] == '0' && smaskuser[11] == '0' && smaskuser[12] == '\0' && smaskuser[13] == '\0' && smaskuser[14] == '\0')
            {
                inc = 1, incOct = 2;

                printf("The entered subnet mask is:  255.255.0.0");
                bitsBorrowed = 8, snw = 256, totalnwb = 16, totalhb = 16, hpsnw = 65534, flash = 16;
            }

            if(smaskuser[4] == '2' && smaskuser[5] == '5' && smaskuser[6] == '5' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '.' &&
                smaskuser[10] == '0' && smaskuser[11] == '0' && smaskuser[12] == '0' && smaskuser[13] == '\0' && smaskuser[14] == '\0')
            {
                inc = 1, incOct = 2;

                printf("The entered subnet mask is:  255.255.0.0");
                bitsBorrowed = 8, snw = 256, totalnwb = 16, totalhb = 16, hpsnw = 65534, flash = 16;
            }

            if(smaskuser[4] == '2' && smaskuser[5] == '5' && smaskuser[6] == '5' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '0' &&
                smaskuser[10] == '.' && smaskuser[11] == '0' && smaskuser[12] == '\0' && smaskuser[13] == '\0' && smaskuser[14] == '\0')
            {
                inc = 1, incOct = 2;

                printf("The entered subnet mask is:  255.255.0.0");
                bitsBorrowed = 8, snw = 256, totalnwb = 16, totalhb = 16, hpsnw = 65534, flash = 16;
            }

            if(smaskuser[4] == '2' && smaskuser[5] == '5' && smaskuser[6] == '5' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '0' &&
                smaskuser[10] == '.' && smaskuser[11] == '0' && smaskuser[12] == '0' && smaskuser[13] == '\0' && smaskuser[14] == '\0')
            {
                inc = 1, incOct = 2;

                printf("The entered subnet mask is:  255.255.0.0");
                bitsBorrowed = 8, snw = 256, totalnwb = 16, totalhb = 16, hpsnw = 65534, flash = 16;
            }

            if(smaskuser[4] == '2' && smaskuser[5] == '5' && smaskuser[6] == '5' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '0' &&
                smaskuser[10] == '.' && smaskuser[11] == '0' && smaskuser[12] == '0' && smaskuser[13] == '0' && smaskuser[14] == '\0')
            {
                inc = 1, incOct = 2;

                printf("The entered subnet mask is:  255.255.0.0");
                bitsBorrowed = 8, snw = 256, totalnwb = 16, totalhb = 16, hpsnw = 65534, flash = 16;
            }

            if(smaskuser[4] == '2' && smaskuser[5] == '5' && smaskuser[6] == '5' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '0' &&
                smaskuser[10] == '0' && smaskuser[11] == '.' && smaskuser[12] == '0' && smaskuser[13] == '\0' && smaskuser[14] == '\0')
            {
                inc = 1, incOct = 2;

                printf("The entered subnet mask is:  255.255.0.0");
                bitsBorrowed = 8, snw = 256, totalnwb = 16, totalhb = 16, hpsnw = 65534, flash = 16;
            }

            if(smaskuser[4] == '2' && smaskuser[5] == '5' && smaskuser[6] == '5' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '0' &&
                smaskuser[10] == '0' && smaskuser[11] == '.' && smaskuser[12] == '0' && smaskuser[13] == '0' && smaskuser[14] == '\0')
            {
                inc = 1, incOct = 2;

                printf("The entered subnet mask is:  255.255.0.0");
                bitsBorrowed = 8, snw = 256, totalnwb = 16, totalhb = 16, hpsnw = 65534, flash = 16;
            }

            if(smaskuser[4] == '2' && smaskuser[5] == '5' && smaskuser[6] == '5' && smaskuser[7] == '.' && smaskuser[8] == '0' && smaskuser[9] == '0' &&
                smaskuser[10] == '0' && smaskuser[11] == '.' && smaskuser[12] == '0' && smaskuser[13] == '0' && smaskuser[14] == '0')
            {
                inc = 1, incOct = 2;

                printf("The entered subnet mask is:  255.255.0.0");
                bitsBorrowed = 8, snw = 256, totalnwb = 16, totalhb = 16, hpsnw = 65534, flash = 16;
            }




            if(smaskuser[4] == '2' && smaskuser[5] == '5' && smaskuser[6] == '5' && smaskuser[7] == '.')
            {
                    if(smaskuser[8] == '1' && smaskuser[9] == '2' && smaskuser[10] == '8' && smaskuser[11] == '.' && smaskuser[12] == '0' &&
                        smaskuser[13] == '\0' && smaskuser[14] == '\0')
                    {
                        inc = 128, incOct = 3;

                        printf("The entered subnet mask is:  255.255.128.0");
                        bitsBorrowed = 9, snw = 512, totalnwb = 17, totalhb = 15, hpsnw = 32766, flash = 17;
                    }

                    if(smaskuser[8] == '1' && smaskuser[9] == '2' && smaskuser[10] == '8' && smaskuser[11] == '.' && smaskuser[12] == '0' &&
                        smaskuser[13] == '0' && smaskuser[14] == '\0')
                    {
                        inc = 128, incOct = 3;

                        printf("The entered subnet mask is:  255.255.128.0");
                        bitsBorrowed = 9, snw = 512, totalnwb = 17, totalhb = 15, hpsnw = 32766, flash = 17;
                    }

                    if(smaskuser[8] == '1' && smaskuser[9] == '2' && smaskuser[10] == '8' && smaskuser[11] == '.' && smaskuser[12] == '0' &&
                        smaskuser[13] == '0' && smaskuser[14] == '0')
                    {
                        inc = 128, incOct = 3;

                        printf("The entered subnet mask is:  255.255.128.0");
                        bitsBorrowed = 9, snw = 512, totalnwb = 17, totalhb = 15, hpsnw = 32766, flash = 17;
                    }

                    if(smaskuser[8] == '1' && smaskuser[9] == '9' && smaskuser[10] == '2' && smaskuser[11] == '.' && smaskuser[12] == '0' &&
                        smaskuser[13] == '\0' && smaskuser[14] == '\0')
                    {
                        inc = 64, incOct = 3;

                        printf("The entered subnet mask is:  255.255.192.0");
                        bitsBorrowed = 10, snw = 1024, totalnwb = 18, totalhb = 14, hpsnw = 16382, flash = 18;
                    }

                    if(smaskuser[8] == '1' && smaskuser[9] == '9' && smaskuser[10] == '2' && smaskuser[11] == '.' && smaskuser[12] == '0' &&
                        smaskuser[13] == '0' && smaskuser[14] == '\0')
                    {
                        inc = 64, incOct = 3;

                        printf("The entered subnet mask is:  255.255.192.0");
                        bitsBorrowed = 10, snw = 1024, totalnwb = 18, totalhb = 14, hpsnw = 16382, flash = 18;
                    }

                    if(smaskuser[8] == '1' && smaskuser[9] == '9' && smaskuser[10] == '2' && smaskuser[11] == '.' && smaskuser[12] == '0' &&
                        smaskuser[13] == '0' && smaskuser[14] == '0')
                    {
                        inc = 64, incOct = 3;

                        printf("The entered subnet mask is:  255.255.192.0");
                        bitsBorrowed = 10, snw = 1024, totalnwb = 18, totalhb = 14, hpsnw = 16382, flash = 18;
                    }

                    if(smaskuser[8] == '2' && smaskuser[9] == '2' && smaskuser[10] == '4' && smaskuser[11] == '.' && smaskuser[12] == '0' &&
                        smaskuser[13] == '\0' && smaskuser[14] == '\0')
                    {
                        inc = 32, incOct = 3;

                        printf("The entered subnet mask is:  255.255.224.0");
                        bitsBorrowed = 11, snw = 2048, totalnwb = 19, totalhb = 13, hpsnw = 8190, flash = 19;
                    }

                    if(smaskuser[8] == '2' && smaskuser[9] == '2' && smaskuser[10] == '4' && smaskuser[11] == '.' && smaskuser[12] == '0' &&
                        smaskuser[13] == '0' && smaskuser[14] == '\0')
                    {
                        inc = 32, incOct = 3;

                        printf("The entered subnet mask is:  255.255.224.0");
                        bitsBorrowed = 11, snw = 2048, totalnwb = 19, totalhb = 13, hpsnw = 8190, flash = 19;
                    }

                    if(smaskuser[8] == '2' && smaskuser[9] == '2' && smaskuser[10] == '4' && smaskuser[11] == '.' && smaskuser[12] == '0' &&
                        smaskuser[13] == '0' && smaskuser[14] == '0')
                    {
                        inc = 32, incOct = 3;

                        printf("The entered subnet mask is:  255.255.224.0");
                        bitsBorrowed = 11, snw = 2048, totalnwb = 19, totalhb = 13, hpsnw = 8190, flash = 19;
                    }

                    if(smaskuser[8] == '2' && smaskuser[9] == '4' && smaskuser[10] == '0' && smaskuser[11] == '.' && smaskuser[12] == '0' &&
                        smaskuser[13] == '\0' && smaskuser[14] == '\0')
                    {
                        inc = 16, incOct = 3;

                        printf("The entered subnet mask is:  255.255.240.0");
                        bitsBorrowed = 12, snw = 4096, totalnwb = 20, totalhb = 12, hpsnw = 4094, flash = 20;
                    }

                    if(smaskuser[8] == '2' && smaskuser[9] == '4' && smaskuser[10] == '0' && smaskuser[11] == '.' && smaskuser[12] == '0' &&
                        smaskuser[13] == '0' && smaskuser[14] == '\0')
                    {
                        inc = 16, incOct = 3;

                        printf("The entered subnet mask is:  255.255.240.0");
                        bitsBorrowed = 12, snw = 4096, totalnwb = 20, totalhb = 12, hpsnw = 4094, flash = 20;
                    }

                    if(smaskuser[8] == '2' && smaskuser[9] == '4' && smaskuser[10] == '0' && smaskuser[11] == '.' && smaskuser[12] == '0' &&
                        smaskuser[13] == '0' && smaskuser[14] == '0')
                    {
                        inc = 16, incOct = 3;

                        printf("The entered subnet mask is:  255.255.240.0");
                        bitsBorrowed = 12, snw = 4096, totalnwb = 20, totalhb = 12, hpsnw = 4094, flash = 20;
                    }

                    if(smaskuser[8] == '2' && smaskuser[9] == '4' && smaskuser[10] == '8' && smaskuser[11] == '.' && smaskuser[12] == '0' &&
                        smaskuser[13] == '\0' && smaskuser[14] == '\0')
                    {
                        inc = 8, incOct = 3;

                        printf("The entered subnet mask is:  255.255.248.0");
                        bitsBorrowed = 13, snw = 8192, totalnwb = 21, totalhb = 11, hpsnw = 2046, flash = 21;
                    }

                    if(smaskuser[8] == '2' && smaskuser[9] == '4' && smaskuser[10] == '8' && smaskuser[11] == '.' && smaskuser[12] == '0' &&
                        smaskuser[13] == '0' && smaskuser[14] == '\0')
                    {
                        inc = 8, incOct = 3;

                        printf("The entered subnet mask is:  255.255.248.0");
                        bitsBorrowed = 13, snw = 8192, totalnwb = 21, totalhb = 11, hpsnw = 2046, flash = 21;
                    }

                    if(smaskuser[8] == '2' && smaskuser[9] == '4' && smaskuser[10] == '8' && smaskuser[11] == '.' && smaskuser[12] == '0' &&
                        smaskuser[13] == '0' && smaskuser[14] == '0')
                    {
                        inc = 8, incOct = 3;

                        printf("The entered subnet mask is:  255.255.248.0");
                        bitsBorrowed = 13, snw = 8192, totalnwb = 21, totalhb = 11, hpsnw = 2046, flash = 21;
                    }

                    if(smaskuser[8] == '2' && smaskuser[9] == '5' && smaskuser[10] == '2' && smaskuser[11] == '.' && smaskuser[12] == '0' &&
                        smaskuser[13] == '\0' && smaskuser[14] == '\0')
                    {
                        inc = 4, incOct = 3;

                        printf("The entered subnet mask is:  255.255.252.0");
                        bitsBorrowed = 14, snw = 16384, totalnwb = 22, totalhb = 10, hpsnw = 1022, flash = 22;
                    }

                    if(smaskuser[8] == '2' && smaskuser[9] == '5' && smaskuser[10] == '2' && smaskuser[11] == '.' && smaskuser[12] == '0' &&
                        smaskuser[13] == '0' && smaskuser[14] == '\0')
                    {
                        inc = 4, incOct = 3;

                        printf("The entered subnet mask is:  255.255.252.0");
                        bitsBorrowed = 14, snw = 16384, totalnwb = 22, totalhb = 10, hpsnw = 1022, flash = 22;
                    }

                    if(smaskuser[8] == '2' && smaskuser[9] == '5' && smaskuser[10] == '2' && smaskuser[11] == '.' && smaskuser[12] == '0' &&
                        smaskuser[13] == '0' && smaskuser[14] == '0')
                    {
                        inc = 4, incOct = 3;

                        printf("The entered subnet mask is:  255.255.252.0");
                        bitsBorrowed = 14, snw = 16384, totalnwb = 22, totalhb = 10, hpsnw = 1022, flash = 22;
                    }

                    if(smaskuser[8] == '2' && smaskuser[9] == '5' && smaskuser[10] == '4' && smaskuser[11] == '.' && smaskuser[12] == '0' &&
                        smaskuser[13] == '\0' && smaskuser[14] == '\0')
                    {
                        inc = 2, incOct = 3;

                        printf("The entered subnet mask is:  255.255.254.0");
                        bitsBorrowed = 15, snw = 32768, totalnwb = 23, totalhb = 9, hpsnw = 510, flash = 23;
                    }

                    if(smaskuser[8] == '2' && smaskuser[9] == '5' && smaskuser[10] == '4' && smaskuser[11] == '.' && smaskuser[12] == '0' &&
                        smaskuser[13] == '0' && smaskuser[14] == '\0')
                    {
                        inc = 2, incOct = 3;

                        printf("The entered subnet mask is:  255.255.254.0");
                        bitsBorrowed = 15, snw = 32768, totalnwb = 23, totalhb = 9, hpsnw = 510, flash = 23;
                    }

                    if(smaskuser[8] == '2' && smaskuser[9] == '5' && smaskuser[10] == '4' && smaskuser[11] == '.' && smaskuser[12] == '0' &&
                        smaskuser[13] == '0' && smaskuser[14] == '0')
                    {
                        inc = 2, incOct = 3;

                        printf("The entered subnet mask is:  255.255.254.0");
                        bitsBorrowed = 15, snw = 32768, totalnwb = 23, totalhb = 9, hpsnw = 510, flash = 23;
                    }

                    if(smaskuser[8] == '2' && smaskuser[9] == '5' && smaskuser[10] == '5' && smaskuser[11] == '.' && smaskuser[12] == '0' &&
                        smaskuser[13] == '\0' && smaskuser[14] == '\0')
                    {
                        inc = 1, incOct = 3;

                        printf("The entered subnet mask is:  255.255.255.0");
                        bitsBorrowed = 16, snw = 65536, totalnwb = 24, totalhb = 8, hpsnw = 254, flash = 24;
                    }

                    if(smaskuser[8] == '2' && smaskuser[9] == '5' && smaskuser[10] == '5' && smaskuser[11] == '.' && smaskuser[12] == '0' &&
                        smaskuser[13] == '0' && smaskuser[14] == '\0')
                    {
                        inc = 1, incOct = 3;

                        printf("The entered subnet mask is:  255.255.255.0");
                        bitsBorrowed = 16, snw = 65536, totalnwb = 24, totalhb = 8, hpsnw = 254, flash = 24;
                    }

                    if(smaskuser[8] == '2' && smaskuser[9] == '5' && smaskuser[10] == '5' && smaskuser[11] == '.' && smaskuser[12] == '0' &&
                        smaskuser[13] == '0' && smaskuser[14] == '0')
                    {
                        inc = 1, incOct = 3;

                        printf("The entered subnet mask is:  255.255.255.0");
                        bitsBorrowed = 16, snw = 65536, totalnwb = 24, totalhb = 8, hpsnw = 254, flash = 24;
                    }

                    //else do nothing;
            }

            else if(smaskuser[4] == '2' && smaskuser[5] == '5' && smaskuser[6] == '5' && smaskuser[7] == '.' && smaskuser[8] == '2' && smaskuser[9] == '5' &&
                smaskuser[10] == '5'   && smaskuser[11] == '.')
            {
                    if(smaskuser[12] == '1' && smaskuser[13] == '2' && smaskuser[14] == '8')
                    {
                        inc = 128, incOct = 4;

                        printf("The entered subnet mask is:  255.255.255.128");
                        bitsBorrowed = 17, snw = 131072, totalnwb = 25, totalhb = 7, hpsnw = 126, flash = 25;
                    }
                    if(smaskuser[12] == '1' && smaskuser[13] == '9' && smaskuser[14] == '2')
                    {
                        inc = 64, incOct = 4;

                        printf("The entered subnet mask is:  255.255.255.192");
                        bitsBorrowed = 18, snw = 262144, totalnwb = 26, totalhb = 6, hpsnw = 62, flash = 26;
                    }
                    if(smaskuser[12] == '2' && smaskuser[13] == '2' && smaskuser[14] == '4')
                    {
                        inc = 32, incOct = 4;

                        printf("The entered subnet mask is:  255.255.255.224");
                        bitsBorrowed = 19, snw = 524288, totalnwb = 27, totalhb = 5, hpsnw = 30, flash = 27;
                    }
                    if(smaskuser[12] == '2' && smaskuser[13] == '4' && smaskuser[14] == '0')
                    {
                        inc = 16, incOct = 4;

                        printf("The entered subnet mask is:  255.255.255.240");
                        bitsBorrowed = 20, snw = 1048576, totalnwb = 28, totalhb = 4, hpsnw = 14, flash = 28;
                    }
                    if(smaskuser[12] == '2' && smaskuser[13] == '4' && smaskuser[14] == '8')
                    {
                        inc = 8, incOct = 4;

                        printf("The entered subnet mask is:  255.255.255.248");
                        bitsBorrowed = 21, snw = 2097152, totalnwb = 29, totalhb = 3, hpsnw = 6, flash = 29;
                    }
                    if(smaskuser[12] == '2' && smaskuser[13] == '5' && smaskuser[14] == '2')
                    {
                        inc = 4, incOct = 4;

                        printf("The entered subnet mask is:  255.255.255.252");
                        bitsBorrowed = 22, snw = 4194304, totalnwb = 30, totalhb = 2, hpsnw = 2, flash = 30;
                    }
            }

            else
            {
                    printf("\n\n\tThe entered subnet mask is utterly stupid !\n\tRead a bit about subnet masks and come back later.\n");
                    exit(1);
            }

                        revEngDisplay(bitsBorrowed, snw, totalnwb, totalhb, hpsnw, inc, flash);
                        calcRange2(oct1, oct2, oct3, snw, inc, incOct);

            return 0;
    }




int validsmaskB(int oct1, int oct2, int oct3)
    {
            int i, inc, incOct;
            int bitsBorrowed, snw, hpsnw, totalnwb, bsize, totalhb, flash;
            char smaskuser[15] = "\0";

            char smaskb11[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '0', '.', '0', '\0', '\0', '\0', '\0'};
            char smaskb12[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '0', '.', '0', '0', '\0', '\0', '\0'};
            char smaskb13[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '0', '.', '0', '0', '0', '\0', '\0'};
            char smaskb14[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '0', '0', '.', '0', '\0', '\0', '\0'};
            char smaskb15[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '0', '0', '.', '0', '0', '\0', '\0'};
            char smaskb16[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '0', '0', '.', '0', '0', '0', '\0'};
            char smaskb17[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '0', '0', '0', '.', '0', '\0', '\0'};
            char smaskb18[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '0', '0', '0', '.', '0', '0', '\0'};
            char smaskb19[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '0', '0', '0', '.', '0', '0', '0'};

            char smaskb21[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '1', '2', '8', '.', '0', '\0', '\0'};
            char smaskb22[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '1', '2', '8', '.', '0', '0', '\0'};
            //char smaskc13[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '5', '.', '0', '\0'};
            char smaskb23[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '1', '2', '8', '.', '0', '0', '0'};

            char smaskb31[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '1', '9', '2', '.', '0', '\0', '\0'};
            char smaskb32[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '1', '9', '2', '.', '0', '0', '\0'};
            //char smaskc13[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '5', '.', '0', '\0'};
            char smaskb33[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '1', '9', '2', '.', '0', '0', '0'};

            char smaskb41[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '2', '4', '.', '0', '\0', '\0'};
            char smaskb42[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '2', '4', '.', '0', '0', '\0'};
            //char smaskc13[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '5', '.', '0', '\0'};
            char smaskb43[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '2', '4', '.', '0', '0', '0'};

            char smaskb51[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '4', '0', '.', '0', '\0', '\0'};
            char smaskb52[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '4', '0', '.', '0', '0', '\0'};
            //char smaskc13[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '5', '.', '0', '\0'};
            char smaskb53[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '4', '0', '.', '0', '0', '0'};

            char smaskb61[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '4', '8', '.', '0', '\0', '\0'};
            char smaskb62[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '4', '8', '.', '0', '0', '\0'};
            //char smaskc13[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '5', '.', '0', '\0'};
            char smaskb63[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '4', '8', '.', '0', '0', '0'};

            char smaskb71[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '2', '.', '0', '\0', '\0'};
            char smaskb72[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '2', '.', '0', '0', '\0'};
            //char smaskc13[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '5', '.', '0', '\0'};
            char smaskb73[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '2', '.', '0', '0', '0'};

            char smaskb81[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '4', '.', '0', '\0', '\0'};
            char smaskb82[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '4', '.', '0', '0', '\0'};
            //char smaskc13[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '5', '.', '0', '\0'};
            char smaskb83[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '4', '.', '0', '0', '0'};


            char smaskc11[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '5', '.', '0', '\0', '\0'};
            char smaskc12[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '5', '.', '0', '0', '\0'};
            //char smaskc13[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '5', '.', '0', '\0'};
            char smaskc13[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '5', '.', '0', '0', '0'};
            char smaskc2[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '5', '.', '1', '2', '8'};
            char smaskc3[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '5', '.', '1', '9', '2'};
            char smaskc4[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '5', '.', '2', '2', '4'};
            char smaskc5[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '5', '.', '2', '4', '0'};
            char smaskc6[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '5', '.', '2', '4', '8'};
            char smaskc7[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '2'};
            //char smaskc8[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '4'};

            printf("\n\tEnter the subnet mask which your network is to be masked with-  \n\t");
            printf("\n\n\tNote: Only first 15 entered characters will be taken into account \n\tbecause that's all you need to enter a valid subnet mask address.\n");
            printf("\n\n\t*Kindly enter no less or no more than 15 digits in your subnet mask.\n\n");
            printf("Subnet mask: ");

            fflush(stdin);
            gets(smaskuser);

            for(i = 0; i < 15; i++)
            {
                while(smaskuser[i] != smaskb11[i] && smaskuser[i] != smaskb12[i] && smaskuser[i] != smaskb13[i] &&  smaskuser[i] != smaskb14[i]
                && smaskuser[i] != smaskb15[i] && smaskuser[i] != smaskb16[i] && smaskuser[i] != smaskb17[i] && smaskuser[i] != smaskb18[i] &&
                smaskuser[i] != smaskb19[i] &&
                smaskuser[i] != smaskb21[i] && smaskuser[i] != smaskb22[i] && smaskuser[i] != smaskb23[i] &&
                smaskuser[i] != smaskb31[i] && smaskuser[i] != smaskb32[i] && smaskuser[i] != smaskb33[i] &&
                smaskuser[i] != smaskb41[i] && smaskuser[i] != smaskb42[i] && smaskuser[i] != smaskb43[i] &&
                smaskuser[i] != smaskb51[i] && smaskuser[i] != smaskb52[i] && smaskuser[i] != smaskb53[i] &&
                smaskuser[i] != smaskb61[i] && smaskuser[i] != smaskb62[i] && smaskuser[i] != smaskb63[i] &&
                smaskuser[i] != smaskb71[i] && smaskuser[i] != smaskb72[i] && smaskuser[i] != smaskb73[i] &&
                smaskuser[i] != smaskb81[i] && smaskuser[i] != smaskb82[i] && smaskuser[i] != smaskb83[i] &&

                smaskuser[i] != smaskc11[i] && smaskuser[i] != smaskc12[i] && smaskuser[i] != smaskc13[i] &&smaskuser[i] != smaskc2[i]
                &&smaskuser[i] != smaskc3[i] && smaskuser[i] != smaskc4[i] &&smaskuser[i] != smaskc5[i] &&
                smaskuser[i] != smaskc6[i] && smaskuser[i] != smaskc7[i])
                {
                    printf("\nInvalid subnet mask entered! Try again.\n\t");
                    //char smaskuser[15] = "\0";

                    fflush(stdin);
                    gets(smaskuser);

                    i = 0;
                 }
            }


        if(smaskuser[8] == '0' && smaskuser[9] ==  '.' && smaskuser[10] == '0' && smaskuser[11] == '\0' && smaskuser[12] == '\0')
        {
                inc = 0, incOct = 0;

                printf("\nThe entered subnet mask is:  255.255.0.0");
                bitsBorrowed = 0, snw = 0, totalnwb = 16, totalhb =  16, hpsnw = 65534, flash = 16;
        }

        else if(smaskuser[8] == '0' && smaskuser[9] ==  '.' && smaskuser[10] == '0' && smaskuser[11] == '0' && smaskuser[12] == '\0')
        {
                inc = 0, incOct = 0;

                printf("\nThe entered subnet mask is:  255.255.0.0");
                bitsBorrowed = 0, snw = 0, totalnwb = 16, totalhb =  16, hpsnw = 65534, flash = 16;

        }
        else if(smaskuser[8] == '0' && smaskuser[9] ==  '.'  && smaskuser[10] == '0' && smaskuser[11] == '0' && smaskuser[12] == '0')
        {
                inc = 0, incOct = 0;

                printf("\nThe entered subnet mask is:  255.255.0.0");
                bitsBorrowed = 0, snw = 0, totalnwb = 16, totalhb =  16, hpsnw = 65534, flash = 16;

        }
        else if(smaskuser[8] == '0' && smaskuser[9] ==  '0'  && smaskuser[10] == '.' && smaskuser[11] == '0' && smaskuser[12] == '\0' && smaskuser[13] == '\0')
        {
                inc = 0, incOct = 0;

                printf("\nThe entered subnet mask is:  255.255.0.0");
                bitsBorrowed = 0, snw = 0, totalnwb = 16, totalhb =  16, hpsnw = 65534, flash = 16;
        }

        else if(smaskuser[8] == '0' && smaskuser[9] ==  '0'  && smaskuser[10] == '.' && smaskuser[11] == '0' && smaskuser[12] == '0' && smaskuser[13] == '\0')
        {
               inc = 0, incOct = 0;

                printf("\nThe entered subnet mask is:  255.255.0.0");
                bitsBorrowed = 0, snw = 0, totalnwb = 16, totalhb =  16, hpsnw = 65534, flash = 16;
        }

        else if(smaskuser[8] == '0' && smaskuser[9] ==  '0'  && smaskuser[10] == '.' && smaskuser[11] == '0' && smaskuser[12] == '0' && smaskuser[13] == '0')
        {
                inc = 0, incOct = 0;

                printf("\nThe entered subnet mask is:  255.255.0.0");
                bitsBorrowed = 0, snw = 0, totalnwb = 16, totalhb =  16, hpsnw = 65534, flash = 16;
        }

        else if(smaskuser[8] == '0' && smaskuser[9] ==  '0'  && smaskuser[10] == '0' && smaskuser[11] == '.' && smaskuser[12] == '0' && smaskuser[13] == '\0' && smaskuser[14] == '\0')
        {
               inc = 0, incOct = 0;

                printf("\nThe entered subnet mask is:  255.255.0.0");
                bitsBorrowed = 0, snw = 0, totalnwb = 16, totalhb =  16, hpsnw = 65534, flash = 16;
        }

        else if(smaskuser[8] == '0' && smaskuser[9] ==  '0'  && smaskuser[10] == '0' && smaskuser[11] == '.' && smaskuser[12] == '0' && smaskuser[13] == '0' && smaskuser[14] == '\0')
        {
                inc = 0, incOct = 0;

                printf("\nThe entered subnet mask is:  255.255.0.0");
                bitsBorrowed = 0, snw = 0, totalnwb = 16, totalhb =  16, hpsnw = 65534, flash = 16;
        }

        else if(smaskuser[8] == '0' && smaskuser[9] ==  '0'  && smaskuser[10] == '0' && smaskuser[11] == '.' && smaskuser[12] == '0' && smaskuser[13] == '0' && smaskuser[14] == '0')
        {
                inc = 0, incOct = 0;

                printf("\nThe entered subnet mask is:  255.255.0.0");
                bitsBorrowed = 0, snw = 0, totalnwb = 16, totalhb =  16, hpsnw = 65534, flash = 16;
        }

        else
        {
            if(smaskuser[8] == '1' && smaskuser[9] ==  '2' && smaskuser[10] == '8' && smaskuser[12] == '0')
            {
                inc = 128, incOct = 3;

                printf("\nThe entered subnet mask is:  255.255.128.0");
                bitsBorrowed = 1, snw = 2, totalnwb = 17, totalhb =  15, hpsnw = 32766, flash = 17;
            }

            else if(smaskuser[8] == '1' && smaskuser[9] ==  '9' && smaskuser[10] == '2' && smaskuser[12] == '0')
            {
                inc = 64, incOct = 3;

                printf("\nThe entered subnet mask is:  255.255.192.0");
                bitsBorrowed = 2, snw = 4, totalnwb = 18, totalhb = 14, hpsnw = 16382, flash = 18;
            }

            else if(smaskuser[8] == '2' && smaskuser[9] ==  '2' && smaskuser[10] == '4' && smaskuser[12] == '0')
            {
                inc = 32, incOct = 3;

                printf("\nThe entered subnet mask is:  255.255.224.0");
                bitsBorrowed = 3, snw = 8, totalnwb = 19, totalhb = 13, hpsnw = 8190, flash = 19;
            }

            else if(smaskuser[8] == '2' && smaskuser[9] ==  '4' && smaskuser[10] == '0' && smaskuser[12] == '0')
            {
                inc = 16, incOct = 3;

                printf("\nThe entered subnet mask is:  255.255.240.0");
                bitsBorrowed = 4, snw = 16, totalnwb = 20, totalhb = 12, hpsnw = 4094, flash = 20;
            }

            else if(smaskuser[8] == '2' && smaskuser[9] ==  '4' && smaskuser[10] == '8' && smaskuser[12] == '0')
            {
                inc = 8, incOct = 3;

                printf("\nThe entered subnet mask is:  255.255.248.0");
                bitsBorrowed = 5, snw = 32, totalnwb = 21, totalhb = 11, hpsnw = 2046, flash = 21;
            }

            else if(smaskuser[8] == '2' && smaskuser[9] ==  '5' && smaskuser[10] == '2' && smaskuser[12] == '0')
            {
                inc = 4, incOct = 3;

                printf("\nThe entered subnet mask is:  255.255.252.0");
                bitsBorrowed = 6, snw = 64, totalnwb = 22, totalhb = 10, hpsnw = 1022, flash = 22;
            }

            else if(smaskuser[8] == '2' && smaskuser[9] ==  '5' && smaskuser[10] == '4' && smaskuser[12] == '0')
            {
                inc = 2, incOct = 3;

                printf("\nThe entered subnet mask is:  255.255.254.0");
                bitsBorrowed = 7, snw = 128, hpsnw = 510, totalnwb = 23;
                bitsBorrowed = 7, snw = 128, totalnwb = 23, totalhb = 9, hpsnw = 510, flash = 23;
            }

            else if(smaskuser[8] == '2' && smaskuser[9] ==  '5' && smaskuser[10] == '5' && smaskuser[12] == '0')
            {
                inc = 1, incOct = 3;

                printf("\nThe entered subnet mask is:  255.255.255.0");
                bitsBorrowed = 8, snw = 256, totalnwb = 24, totalhb = 8, hpsnw = 254, flash = 24;
            }

            else if(smaskuser[8] == '2' && smaskuser[9] ==  '5' && smaskuser[10] == '5' && smaskuser[11] == '.' &&
                smaskuser[12] == '1' && smaskuser[13] ==  '2' && smaskuser[14] == '8')
            {
                inc = 128, incOct = 4;

                printf("\nThe entered subnet mask is:  255.255.255.128");
                bitsBorrowed = 9, snw = 512, totalnwb = 25, totalhb = 7, hpsnw = 126, flash = 25;
            }

            else if(smaskuser[8] == '2' && smaskuser[9] ==  '5' && smaskuser[10] == '5' && smaskuser[11] == '.' &&
                smaskuser[12] == '1' && smaskuser[13] ==  '9' && smaskuser[14] == '2')
            {
                inc = 64, incOct = 4;

                printf("\nThe entered subnet mask is:  255.255.255.192");
                bitsBorrowed = 10, snw = 1024, totalnwb = 26, totalhb = 6, hpsnw = 62, flash = 26;
            }

            else if(smaskuser[8] == '2' && smaskuser[9] ==  '5' && smaskuser[10] == '5' && smaskuser[11] == '.' &&
                smaskuser[12] == '2' && smaskuser[13] ==  '2' && smaskuser[14] == '4')
            {
                inc = 32, incOct = 4;

                printf("\nThe entered subnet mask is:  255.255.255.224");
                bitsBorrowed = 11, snw = 2048, hpsnw = 62, totalnwb = 27;
                bitsBorrowed = 11, snw = 2048, totalnwb = 27, totalhb = 5, hpsnw = 30, flash = 27;
            }

            else if(smaskuser[8] == '2' && smaskuser[9] ==  '5' && smaskuser[10] == '5' && smaskuser[11] == '.' &&
                smaskuser[12] == '2' && smaskuser[13] ==  '4' && smaskuser[14] == '0')
            {
                inc = 16, incOct = 4;

                printf("\nThe entered subnet mask is:  255.255.255.240\n");
                bitsBorrowed = 12, snw = 4096, totalnwb = 28, totalhb = 4, hpsnw = 14, flash = 28;
            }

            else if(smaskuser[8] == '2' && smaskuser[9] ==  '5' && smaskuser[10] == '5' && smaskuser[11] == '.' &&
                smaskuser[12] == '2' && smaskuser[13] ==  '4' && smaskuser[14] == '8')
            {
                inc = 8, incOct = 4;

                printf("\nThe entered subnet mask is:  255.255.255.248");
                bitsBorrowed = 13, snw = 8192, totalnwb = 29, totalhb = 3, hpsnw = 6, flash = 29;
            }

            else if(smaskuser[8] == '2' && smaskuser[9] ==  '5' && smaskuser[10] == '5' && smaskuser[11] == '.' &&
                smaskuser[12] == '2' && smaskuser[13] ==  '5' && smaskuser[14] == '2')
            {
                inc = 4, incOct = 4;

                printf("\nThe entered subnet mask is:  255.255.255.252");
                bitsBorrowed = 14, snw = 16384, totalnwb = 30, totalhb = 2, hpsnw = 2, flash = 30;
            }



            else
            {
                    printf("\n\n\tThe entered subnet mask is utterly stupid !\n\tRead a bit about subnet masks and come back later.\n");
                    exit(0);
            }

        }

            revEngDisplay(bitsBorrowed, snw, totalnwb, totalhb, hpsnw, inc, flash);
            calcRange2(oct1, oct2, oct3, snw, inc, incOct);

        return 0;
    }

    int validsmaskC(int oct1, int oct2, int oct3)
    {
            int i, inc, incOct = 4;
            int bitsBorrowed, snw, hpsnw, totalnwb, bsize, totalhb, flash;
            char smaskuser[15] = "\0";

            char smaskc11[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '5', '.', '0', '\0', '\0'};
            char smaskc12[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '5', '.', '0', '0', '\0'};
            char smaskc13[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '5', '.', '0', '0', '0'};
            char smaskc2[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '5', '.', '1', '2', '8'};
            char smaskc3[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '5', '.', '1', '9', '2'};
            char smaskc4[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '5', '.', '2', '2', '4'};
            char smaskc5[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '5', '.', '2', '4', '0'};
            char smaskc6[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '5', '.', '2', '4', '8'};
            char smaskc7[15] = {'2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '5', '.', '2', '5', '2'};

            printf("\n\tEnter the subnet mask which your network is to be masked with-  \n\t");
            printf("\n\n\tNote: Only first 15 entered characters will be taken into account \n\tbecause that's all you need to enter a valid subnet mask address.\n");
            printf("\n\n\t*Kindly enter no less or no more than 15 digits in your subnet mask.\n\n");
            printf("Subnet mask: ");

            fflush(stdin);
            gets(smaskuser);

            for(i = 0; i < 15; i++)
            {
                while(smaskuser[i] != smaskc11[i] && smaskuser[i] != smaskc12[i] && smaskuser[i] != smaskc13[i] &&smaskuser[i] != smaskc2[i]
                &&smaskuser[i] != smaskc3[i] && smaskuser[i] != smaskc4[i] &&smaskuser[i] != smaskc5[i] &&
                smaskuser[i] != smaskc6[i] && smaskuser[i] != smaskc7[i])
                {
                    printf("\nInvalid subnet mask entered! Try again.\n\t");

                    fflush(stdin);
                    gets(smaskuser);

                    i = 0;
                }
            }


            if(smaskuser[12] == '0' )
            {
                inc = 256;
                printf("\n\nThe entered subnet mask is:  255.255.255.0\n\n");
                bitsBorrowed = 0, snw = 1, totalnwb = 24, totalhb = 8, hpsnw = 254, flash = 24;

            }
            else if(smaskuser[12] == '1' && smaskuser[13] ==  '2' && smaskuser[14] == '8')
            {
                inc = 128;
                printf("\n\nThe entered subnet mask is:  255.255.255.128\n\n");
                bitsBorrowed = 1, snw = 2, hpsnw = 126, totalnwb = 25;
                bitsBorrowed = 1, snw = 2, totalnwb = 25, totalhb = 7, hpsnw =126, flash = 25;
            }

            else if(smaskuser[12] == '1' && smaskuser[13] ==  '9' && smaskuser[14] == '2')
            {
                inc = 64;
                printf("\n\nThe entered subnet mask is:  255.255.255.192\n\n");
                bitsBorrowed = 2, snw = 4, totalnwb = 26, totalhb = 6, hpsnw = 62, flash = 26;
            }

            else if(smaskuser[12] == '2' && smaskuser[13] ==  '2' && smaskuser[14] == '4')
            {
                inc = 32;
                printf("\n\nThe entered subnet mask is:  255.255.255.224\n\n");
                bitsBorrowed = 3, snw = 8, totalnwb = 27, totalhb = 5, hpsnw = 30, flash = 27;
            }

            else if(smaskuser[12] == '2' && smaskuser[13] ==  '4' && smaskuser[14] == '0')
            {
                inc = 16;
                printf("\n\nThe entered subnet mask is:  255.255.255.240\n\n");
                bitsBorrowed = 4, snw = 16, totalnwb = 28, totalhb = 4, hpsnw = 14, flash = 28;
            }

            else if(smaskuser[12] == '2' && smaskuser[13] ==  '4' && smaskuser[14] == '8')
            {
                inc = 8;
                printf("\n\nThe entered subnet mask is:  255.255.255.248\n\n");
                bitsBorrowed = 5, snw = 32, totalnwb = 29, totalhb = 3, hpsnw = 6, flash = 29;
            }

            else if(smaskuser[12] == '2' && smaskuser[13] ==  '5' && smaskuser[14] == '2')
            {
                inc = 4;
                printf("\n\nThe entered subnet mask is:  255.255.255.252\n\n");
                bitsBorrowed = 6, snw = 64, totalnwb = 30, totalhb = 2, hpsnw = 2, flash = 30;
            }


            else
            {
                    printf("\n\n\tThe entered subnet mask is utterly stupid !\n\tRead a bit about subnet masks and come back later.\n");
                    exit(0);
            }

            revEngDisplay(bitsBorrowed, snw, totalnwb, totalhb, hpsnw, inc, flash);
            calcRange2(oct1, oct2, oct3, snw, inc, incOct);

    return 0;
}


    int revEngDisplay(int bitsBorrowed, int snw, int totalnwb, int totalhb, int hpsnw, int inc, int flash)
            {
                printf("\n*This subnet mask in slash notation, is expressed as: /%d\n", flash);
                printf("\nA class A network with this subnet mask has following details:\n\t ");
                printf("1) The number of bits borrowed from host bits are : %d\n\t", bitsBorrowed);
                printf("2) Total number of network bits are: %d\n\t", totalnwb);
                printf("3) The total number of subnetworks: %d\n\t", snw);
                printf("4) Total number of host bits are: %d\n\t", totalhb);
                printf("5) The total number of valid hosts per subnetwork: %d\n\t", hpsnw);
                printf("6) The block size(increment) is: %d\n", inc);

                return 0;
            }

int calcRange2(int oct1, int oct2, int oct3, int snw, int inc, int incOct)
{
        int i, j, k, inc2 = 0;
        char ch;


        if (oct1>=1 && oct1<=126)
            {
                printf("\nThe network ID/address of the entered address is %d.0.0.0\n",oct1);
                printf("The broadcast address of the entered address is %d.255.255.255\n",oct1);

                printf("\nThe above entered IP address with custom subnet mask lies in one of the following network ranges.\n\n ");
                printf("\nPress any key to display all the %d networks below...\n\n", snw);
                getch();

                printf("\nThe detail of sub-networks is as follows: \n\n");
                printf("1. %d.0.0.0    -    ",oct1);

              //testing done
                    if(incOct == 2)
                    {
                        for(i = 2; i <= ((256/inc)); i++ )
                        {
                            inc2 = inc2+inc;
                            printf(" %d.%d.255.255\n",  oct1,inc2-1);
                            printf("%d. %d.%d.0.0    -    ", i, oct1, inc2);
                        }
                        printf(" %d.255.255.255\n",  oct1);

                    }


            //dual testing done except for serial number's bug
                    else if(incOct == 3)
                    {
                    //printf(" %d.0.0.0\n",  oct1);
                    //printf(" %d.0.%d.0\n",  oct1, inc);

                        for(j = 0; j<256; j++)
                        {
                            printf("%d.%d.0.0    -    ", oct1, j);
                            inc2 = 0;

                            for(i = 2; i <= ((256/inc)); i++ )
                            {
                                inc2 = inc2+inc;
                                printf("%d.%d.%d.255\n",  oct1, j, inc2-1);
                                printf("%d.%d.%d.0    -    ", oct1, j, inc2);

                            }
                            printf("%d.%d.255.255\n",  oct1, j);
                        //printf(" %d.%d.%d.%d\n",  oct1, oct2, j, 0);
                        }
                    }

                //else{printf("You don't want the display.");}

                //if(incOct == 4)
                    else
                    {
                        printf(" %d.0.0.0    -    ",  oct1);
                        printf(" %d.0.0.%d  \n",  oct1, inc-1);

                        for(k = 0; k<=255; k++)
                        {
                        //printf(" %d.%d.0.0\n",  oct1, );

                            for(j = 0; j<256; j++)
                            {
                                //printf(" %d.%d.%d.%d    -    ", oct1, k, j, inc);
                                inc2 = 0;

                                for(i = 0; i < ((256/inc)); i++ )
                                {
                                    //inc2 = inc2+inc;
                                    printf("%d.%d.%d.%d -  ",  oct1, k, j, inc2);
                                    inc2 = inc2+inc;
                                    printf(" %d.%d.%d.%d    \n", oct1, k, j, inc2-1);

                                }
                            }
                        //printf(" %d.%d.%d.%d\n",  oct1, oct2, j, 0);

                        }
                    }
                }


        else if (oct1>=128 && oct1<=191)   //means class B network
            {
                printf("\nThe network ID/address of the entered address is- %d.%d.0.0\n",oct1, oct2);
                printf("The broadcast address of the entered address is- %d.%d.255.255\n",oct1, oct2);

                printf("\nThe above entered IP address with custom subnet mask lies in one of the following network ranges.\n\n ");
                printf("\nPress any key to display all the %d networks below...\n\n", snw);
                getch();

                printf("\nThe detail of sub-networks is as follows: \n\n");
                printf("1. %d.%d.0.0    -    ",oct1, oct2);

            //dual testing done
                if(incOct == 3)
                {
                    for(i = 2; i <= ((256/inc)); i++ )
                    {
                        //printf(" %d.%d.%d.255\n",  oct1, oct2, inc2-1);
                        inc2 = inc2+inc;
                        //printf("1. %d.%d.0.0\n",oct1, oct2);
                        printf(" %d.%d.%d.255\n",  oct1, oct2, inc2-1);
                        printf("%d. %d.%d.%d.0    -    ", i, oct1, oct2, inc2);
                    }
                    printf(" %d.%d.255.255\n",  oct1, oct2);
                }

            // dual testing done
                //if(incOct == 4)
                else
                {
                //printf(" %d.%d.0.0\n",  oct1, oct2);
                //printf(" %d.%d.0.%d\n",  oct1, oct2, inc);

                    for(j = 0; j<256; j++)
                    {
                        printf(" %d.%d.%d.%d    -    ",  oct1, oct2, j, 0);
                        inc2 = 0;

                        for(i = 2; i <= ((256/inc)); i++ )
                        {
                            inc2 = inc2+inc;
                            printf(" %d.%d.%d.%d\n",  oct1, oct2, j, inc2-1);
                            printf(" %d.%d.%d.%d    -    ",  oct1, oct2, j, inc2);

                        }
                        printf(" %d.%d.%d.255\n",  oct1, oct2, j);
                    }
                }
            }


        else//(oct1>=192 && oct1<=223)  //means class C network
        {
                printf("\nThe network ID/address of the entered address is- %d.%d.%d.0\n",oct1, oct2, oct3);
                printf("The broadcast ID of the entered address is- %d.%d.%d.255\n",oct1, oct2, oct3);

                printf("\nThe above entered IP address with custom subnet mask lies in one of the following network ranges.\n\n ");
                printf("\nPress any key to display all the %d networks below...\n\n", snw);
                getch();

                printf("\nThe details of sub-networks for this subnet mask is as follows: \n\n");
                printf("1. %d.%d.%d.0    -    ",oct1, oct2, oct3);

                for(i = 2; i <= ((256/inc)); i++ )
                {
                    inc2 = inc2+inc;
                    //inc3 = 1
                    printf(" %d.%d.%d.%d\n",  oct1, oct2, oct3, inc2-1);
                    //printf("Valid host(IP) range in this network : %d.%d.%d.%d - %d.%d.%d.%d", oct1, oct2, oct3, inc2)
                    printf("%d. %d.%d.%d.%d    -    ", i, oct1, oct2, oct3, inc2);
                }
                printf(" %d.%d.%d.255\n",  oct1, oct2, oct3);

        }
        return 0;

}

