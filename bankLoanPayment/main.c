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


int main(int argc, char * argv[])
{
    bankLoanPayment(argc, argv);
    return 0;
}
