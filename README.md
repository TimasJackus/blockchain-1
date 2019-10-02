# Hash generatorius (v0.1)

## Funkcijos idėja

Sugeneruojami 4 64-bitų `bitset`'ai, perskaitoma simbolių eilutė, kuri po matematinių operacijų paverčiama į skaičių, pagal kurį yra keičiamos `bitset`'o reikšmės, sukant ciklą ir dalinant skaičių iš konstantos. Skaičių dalinant iš 64, gauta liekana nulemia, kurio bito reikšmė bus pakeista.

Programos paleidimas su `g++` kompiliatoriumi:

`g++ main.cpp -o main.out && ./main.out {parametrai}`

Galimi parametrai:
* `--string { string }`,
* `--files { filename1 ... filenameN }`,
* `--time { filename }`,
* `--compare { filename }`.

Perduoti parametrą **būtina**, tačiau nuskaitomas tik pirmas perduotas parametras.

## --string

Šis parametras skirtas perduoti simbolių eilutei, kurią programa apdoroja maišos funkcija ir išveda rezultatą į `outputs/string.txt` failą.

Pvz.: `g++ main.cpp -o main.out && ./main.out --string lietuva`.

## --files

Šis parametras skirtas perduoti failų masyvui, kurių turiny skaito kaip simbolių eilutę ir išveda rezultatus į `outputs/files.txt` failą, kiekvienam įvestam failui, išvedama viena eilutė į išvesties failą.

Pvz.: `g++ main.cpp -o main.out && ./main.out --files test-data/1-1.txt test-data/1-2.txt test-data/2-1.txt test-data/2-2.txt test-data/3-1.txt test-data/3-2.txt`.

## --measure

Šis parametras skirtas išmatuoti per kiek laiko "užhash'uojama" kiekviena failo eilutė. Rezultatas išvedamas į `outputs/measured.txt` failą.

Pvz.: `g++ main.cpp -o main.out && ./main.out --measure test-data/konstitucija.txt`.

## --compare

Šis parametras skirtas palyginti simbolių eilučių poras ar jų maišos funkcijos išvestys nesutampa bei apskaičiuojamas procentinis maišos funkcijos išvesčių "skirtingumas".

Pvz.: `g++ main.cpp -o main.out && ./main.out --compare test-data/string-pairs-2.txt`.


# Testinių failų pavyzdžių rezultatai:

| Failo pavadinimas | Išvesties rezultatas |
| ----------------- |:--------------------:|
| test-data/1-1.txt | 2382337240411d69d787bbe2452ebf6b6f748867ba77e09a6f748867ba77e08a |
| test-data/1-2.txt | 80e300171282029c38f4902915e75d3aca32434314f8825035ccbcbceb077daf |
| test-data/2-1.txt| d057dada6854c698fabe073b358d34f3c3e9faeb9270a32c3c1645146d8f5cc2 |
| test-data/2-2.txt | 11b12ed418eb8fa1f9a6b4683274503ce8dbe31eb42ebde417241cf10bd1421a |
| test-data/3-1.txt | 3e2dc046ab6fea351144d1a7019586d92ef3b06423559fcfe6a2b175f2446e97 |
| test-data/3-2.txt| 18d5c1b175cac8c5d5925556cf41c64da748369d171fe74158b7c962e8e058af |

# Hash funkcijos efektyvumas

Funkcijos veikimo laikas hash'uojant kiekvieną eilutę iš `konstitucija.txt` failo: `0.017342 s.`

# Simbolių eilučių porų lyginimas

| Failas | Simbolių eilučių porų skaičius | Rezultatas |
| ------ |:------------------------------:|:----------:|
| string-pairs-1.txt | 1 000 000 | Mean: 93.7501%.<br>Max: 100%.<br>Min: 68.75%.<br>TEST PASSED!|
| string-pairs-2.txt | 100 000 | Mean: 93.7605%.<br>Max: 100%.<br>Min: 76.5625%.<br>TEST PASSED! |

Nei viename faile nebuvo sutapusių išvesties rezultatų, tad abu testai pavykę.