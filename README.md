# Symulator Windy — System Wbudowany (SWB)

Projekt zaliczeniowy z przedmiotu **Systemy Wbudowane (SWB)** — rozproszony system sterowania windą oparty na kilku mikrokontrolerach 8051, zaprojektowany w **Keil µVision** i zasymulowany w **Proteus (ISIS)**. Ocena: **5**.

## Opis projektu

System symuluje działanie windy sterowanej kilkoma niezależnymi mikrokontrolerami, połączonymi wspólną magistralą komunikacyjną **RS485**. Użytkownik wybiera piętro za pomocą pinpada, a system odpowiednio steruje silnikami, wyświetla aktualne piętro oraz loguje wykonywane polecenia na wyświetlaczu LCD.

### Architektura (mikrokontrolery)

Projekt składa się z czterech mikrokontrolerów 8052, z których każdy odpowiada za inny podzespół i komunikuje się z resztą systemu przez magistralę RS485 (konwertery U2/U4/U6/U9):

| Mikrokontroler | Plik | Rola |
|---|---|---|
| **U1** | `U1_Master.c` | Jednostka nadrzędna — odczyt pinpada, koordynacja całego systemu |
| **U3** | `U3_7SEG.c` | Sterowanie wyświetlaczem segmentowym — pokazuje aktualne piętro windy |
| **U5** | `U5_Motor.c` | Sterowanie silnikami (ruch windy) poprzez driver silników oraz sygnalizacją (żarówki/diody) |
| **U8** | `U8_LCD.c` | Sterowanie wyświetlaczem LCD — wypisuje wykonywane polecenia/komunikaty systemu |

### Pozostałe elementy makiety

- **Pinpad** (klawiatura matrycowa 4×3) — wybór piętra / wprowadzanie poleceń
- **Wyświetlacz segmentowy** — aktualne piętro windy
- **Wyświetlacz LCD** — log poleceń/komunikatów systemu
- **Silniki + sterownik (U7)** — napęd symulujący ruch kabiny windy
- **Magistrala RS485/RS422** — komunikacja między mikrokontrolerami

## Środowisko i narzędzia

- **Keil µVision 4** — pisanie i kompilacja kodu mikrokontrolerów (C)
- **Proteus (ISIS)** — projekt schematu i symulacja całego układu
- Mikrokontroler: rodzina **8051** (np. AT89C52)

## Struktura repozytorium

```
.
├── src/
│   ├── U1_Master.c       # Jednostka nadrzędna / pinpad
│   ├── U3_7SEG.c         # Wyświetlacz piętra
│   ├── U5_Motor.c        # Sterowanie silnikami
│   └── U8_LCD.c          # Wyświetlacz LCD / log poleceń
├── proteus/
│   └── PROJ2.pdsprj      # Projekt schematu i symulacji Proteus
├── keil/
│   └── Zadanie_projektowe.uvproj   # Projekt µVision
├── docs/
│   └── schemat.png       # Zrzut ekranu schematu z Proteusa
└── README.md
```


## Jak uruchomić symulację

1. Otwórz `Zadanie_projektowe.uvproj` w **Keil µVision**, skompiluj projekt do pliku `.hex`
2. Otwórz `PROJ2.pdsprj` w **Proteus**
3. Wgraj skompilowany `.hex` do odpowiednich mikrokontrolerów w symulacji
4. Uruchom symulację — wybierz piętro na pinpadzie i obserwuj ruch windy, zmianę piętra na wyświetlaczu oraz log na LCD

## Autor
Szymon Trzaskowski
Schemat do projektu został częściowo otrzymany do wykładowcy, Pana mgr inż. Marcina Golucha. Kody projektu oraz korekty schematu wykonane samodzielnie. Projekt obroniony na ocenę 5.
