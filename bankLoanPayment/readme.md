# Ši programa skirta pavaizduoti Banko skolų dengimą
# PARAMETRAI:
 - Paskolos suma (double)
 - Paskolos laikotarpis (mėnesiais) (int)
 - Palūkanų norma (mėnesinė) (double)
 - Delspinigių norma (dieninė) (double)
 - Paskolos dengimo strategija (int)
    - 0 - dengiama seniausia skola, neatsižvelgiant į jų tipą
    - 1 arba !0 - dengiama pagal prioritetus: pagrindinė suma, palūkanos,    delspinigiai
 - Vartotojo alyginimas (mėnesinis) (double)
 - Didžiausias galimas mokėjimo vėlavimas (dienomis) (int)
 - Mokėjimo vėlavimo tikimybė (procentais) (double)
# Išvestis:
 Programa išveda visus pateiktus argumentus.
 Paskui iš eilės išvedinėja kiekvieno mėnesio, kol suma neapmokėta informaciją:
  - Vartotojo sąskaitą
  - Likusią paskolos sumą, mokėjimus ir jų sumą, delspinigius prieš ir po - apmokėjimo.
  - Totalią paskolos sumą.

# Svarbūs punktai:
 Paskolos išsiimti neleidžiama, jei kredito ir palūkanų įmokos didesnės už 40% asmens disponuojamųjų mėnesinių pajamų

# Pavyzdiniai parametrai:
 1500 10 5.0 1.0 0 1000 10 30