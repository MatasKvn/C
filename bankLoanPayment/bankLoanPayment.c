/*
9.	Banko skolų dengimas (ADT: eilė, prioritetinė eilė).
Bankas išduoda klientui paskolą, pagal jos sumą ir paskolos laikotarpį sudaromas
grąžinimo grafikas (paskolinta suma grąžinama lygiomis dalimis kas 30 dienų). Deja,
ne visi klientai sugeba grąžinti paskolą laiku. Atėjus mokėjimo dienai klientas gali
turėti tik tiek pinigų, kiek reikia einamajai įmokai pagal grafiką dengti, arba
kažkiek daugiau pinigų(tokiu atveju jis dengia ir įsiskolinimus, jei tokių yra), arba
kažkiek mažiau pinigų (tokiu atveju auga skolos). Palūkanos skaičiuojamos už visą tam
momentui negrąžintą paskolos sumą. Už laiku negrąžintą paskolos dalį imami delspinigiai
(delspinigiai neskaičiuojami nuo palūkanų ir delspinigių). Galimos 2 skolų dengimo strategijos: 1)
dengiamos seniausios skolos, neatsižvelgiant į jų tipą; 2) dengiama pagal prioritetus: pagrindinė suma,
palūkanos, delspinigiai. Įvertinti šių strategijų  ekonominį poveikį klientui.
Visi kiti rodikliai, nuo kurių priklauso procesas, įvedami kaip programos parametrai.

Parametrai:
 + paskolos suma
 + paskolos laikotarpis (menesiai)(ir kiek kieviena menesi vartotojas turi pinigu ??? (kaip masyvas?))
 + palūkanų norma
 + delspinigių norma 

 + 2 Skolų dengimo strategijos
    1) dengiamos seniausios skolos, neatsižvelgiant į jų tipą
    2) dengiama pagal prioritetus: pagrindinė suma, palūkanos, delspinigiai.

 + Vartotojo atlyginimas
 + Didžiausias galimas mokėjimo velavimas
 + Mokėjimo vėlavimo tikimybė

 Iš viso: 8
*/

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "bankLoanPayment.h"

// int isLate(double chance);
// int getRandInt(int low, int high);
// void bankLoanPayment(int argc, char * argv[]);

void bankLoanPayment(int argc, char * argv[])
{
    srand(time(NULL));

    printf("No. arguments: %d\n", argc);

    if(argc != 8+1){
        printf("Required parameters not provided!"); 
    }

    // parameters
    double sum = atof(argv[1]);                          // sum of the loan
    int period = atoi(argv[2]);                          // period of the load (in months)
    double interestRate = atof(argv[3]);                 // interest rate (monthly)
    double kickbackRate = atof(argv[4]);                 // kickback rate (applied daily)
    int strategy = atoi(argv[5]);                        // 0 - without priorities, 1 - with priorities
    double userIncome = atof(argv[6]);                   // monthly income of the user
    int maxDaysLate = atoi(argv[7]);                     // maximum days of the the user may be late on making payments
    double chanceOfBeingLate = atof(argv[8]);            // chance of the user being late to make payments
    

    // print give parameters
    printf(" sum: %lf\n period: %d\n interestRate: %lf\n kickbackRate: %lf\n strategy: %d\n"
    ,sum, period, interestRate, kickbackRate, strategy);
    printf(" userIncome: %.2lf\n maxDaysLate: %d with a chance of %.2lf\n\n ", userIncome, maxDaysLate, chanceOfBeingLate);

    // check if user is eligble for a loan
    if(userIncome*0.4 <= sum/period + sum/100*interestRate){
        printf(" %2.lf <= %2.lf\n",userIncome*0.4,sum/period +sum/100*interestRate);
        printf("User does meet the requirements to be eligible for a loan.\n");
    }

    //
    queue payments;
    initializeQueue(&payments);

    double uSum = sum;
    double userBalance = 0;
    double uKickback = 0;
    double uInterest = 0;
    double uPayment = 0;
    int daysLate;

    double uTotalSum = 0;

    //TEMP print before cycle
    printf(" Monthly User Income: %.2lf\n", userIncome);
    printf(" Balance: %.2lf\n", userBalance);
    printf(" Loan Sum: %.2lf\n\n\n", uSum);
    //TEMP

    int i = 0;
    double a;
    int c;
    node * temp;
    while (uSum > 0 || payments.head->value >= 0.01)
    {
        ++i;
        
        userBalance += userIncome*0.4;
        
        uPayment = 0;
        uInterest = 0;
        if(uSum > 0){
            uPayment = sum/(period);
            uInterest = uSum/100*interestRate;
            uSum -= uPayment;
        }
        uTotalSum += uPayment + uInterest + uKickback;
        
        // enqueing payment and interest
        if(uPayment) enqueuePriority(&payments, uPayment, (strategy == 0) ? 1 : 3);
        if(uInterest) enqueuePriority(&payments, uInterest, (strategy == 0) ? 1 : 2);

        // print statistics
        printf("Month[%d]: BEFORE PAYMENT\n", i);
        printf(" User Balance: %.2lf\n", userBalance);
        printf("  Loan Leftover Sum: %.2lf\n", uSum);
        printf("   Payment: %.2lf enqueued\n", uPayment);
        printf("   Interest: %.2lf enqueued\n", uInterest);

        // kickback payment enqueing
        if(isLate(chanceOfBeingLate)){
            printf("  LATE!\n");
            daysLate = getRandInt(0, maxDaysLate);
            c = countElements(&payments);
            temp=payments.head;
            for(int i=0; i<c; ++i)
            {
                if(temp->value){
                    a = temp->value/100*kickbackRate*daysLate;
                    uTotalSum += a;

                    if(a >= 0.01){
                        printf("    Payment[%d]: %.2lf unpaid for %d days,\n     kickback payment of %.2lf enqueued\n",i+1, temp->value,daysLate,a);
                        enqueuePriority(&payments, a, 1);
                    }
                }
                temp = temp->next;
            }
        }
        
        // print sum of payments BEFORE PAYMENT
        printf("   Sum of payments: %.2lf\n", sumQueue(&payments));
        temp = payments.head;
        int count = 0;
        while(temp!=NULL)
        {
            printf("     Payment %d: %.2lf\n", count, temp->value);
            ++count;
            temp = temp->next;
        }

        //payment processing 
        temp = payments.head;
        count = 0;
        while(temp->value <= userBalance && temp->next != NULL && userBalance != 0){
            ++count;
            userBalance -= temp->value;
            temp->value = 0;
            temp = temp->next;
            dequeue(&payments);
        }
        if(userBalance >= temp->value && temp->next == NULL){
            ++count;
            userBalance -= temp->value;
            temp->value = 0;
        }
        printf("    %d payments made\n");

        printf("Month[%d]: AFTER PAYMENT\n", i);
        printf(" User Balance: %.2lf\n", userBalance);
        printf("  Loan Leftover Sum: %.2lf\n", uSum);
        printf("  Sum of payments: %.2lf\n", sumQueue(&payments));
        

        // print payments AFTER PAYMENT (queue)
        temp=payments.head;
        count = 0;
        while(temp!=NULL)
        {
            printf("   Payment %d: %.2lf\n", count+1, temp->value);
            ++count;
            temp = temp->next;
        }

        printf("=======================================\n");
    }

    deleteQueue(&payments);
    printf("Loan sum: %.2lf\n", sum);
    printf("Total ammount paid: %.2lf\n", uTotalSum);
}

int isLate(double chance)
{
    // printf("CHANCE: %lf", chance);
    if(rand()%101 <= chance){
        return 1;
    }
    return 0;
}

int getRandInt(int low, int high)
{
    int value = rand()%(high-low+1)+low;
    return value;
}