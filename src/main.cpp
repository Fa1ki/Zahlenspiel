#include <cstdlib>
#include <ctime>
#include <iostream>
#include <limits>
#include <locale>

#ifdef _WIN32
#include <windows.h>
#endif

void clearScreen();
void runMenu();
void runGame();
int getUserGuess();
char displayMenu();
bool validateUserGuess(int guess, int rightResult);

int maxNumber;

int main() {
  std::setlocale(LC_ALL, "de_DE.UTF-8");

#ifdef _WIN32
  SetConsoleOutputCP(CP_UTF8);
#endif

  std::srand(static_cast<unsigned int>(std::time(0)));

  runMenu();

  return 0;
}

void clearScreen() {
#ifdef _WIN32
  system("cls");
#else
  std::cout << "\033[2J\033[1;1H";
#endif
}

void runMenu() {
  while (true) {
    char input = displayMenu();
    if (input == 'P' || input == 'p') {
      runGame();
    } else if (input == 'Q' || input == 'q') {
      std::cout << "Spiel beendet. Auf Wiedersehen!" << std::endl;
      break;
    } else {
      std::cout << "\nUngültige Eingabe: '" << input
                << "'. Bitte versuche es mit P oder Q.\n";
    }
  }
}

char displayMenu() {
  char input = ' ';
  std::cout << "\nMENU\n\n(P)lay\n(Q)uit\n\n";
  std::cout << "Input: ";
  std::cin >> input;

  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  clearScreen();
  return input;
}

void runGame() {
  std::cout << "\nGebe deine maximale Zahl ein: ";
  while (!(std::cin >> maxNumber) || maxNumber <= 1) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Ungültige Eingabe. Bitte gib eine Zahl größer als 1 ein: ";
  }

  int randomNumber = std::rand() % maxNumber + 1;
  int guess;
  int tries = 0;

  do {
    guess = getUserGuess();

    tries++;
  } while (!validateUserGuess(guess, randomNumber));

  std::cout << "Du hast " << tries
            << " Versuche benötigt, um die Zahl zu erraten.\n\n";
}

int getUserGuess() {
  int guess;

  std::cout << "Deine Zahl: ";
  while (!(std::cin >> guess) || guess <= 0) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Ungültige Eingabe: '" << guess
              << "' Bitte versuche es mit einer positiven Zahl.";
  }
  return guess;
}

bool validateUserGuess(int guess, int rightResult) {
  clearScreen();

  if (guess == rightResult) {
    std::cout << "\nDie gesuchte Zahl war zwischen 1 und " << maxNumber
              << " (eingeschlossen 1 und " << maxNumber << ").";
    std::cout << "\nDeine Eingabe von " << guess << " ist korrekt.\n";
    return true;
  } else if (guess < rightResult) {
    std::cout << "\nDie gesuchte Zahl ist zwischen 1 und " << maxNumber
              << " (eingeschlossen 1 und " << maxNumber << ").";
    std::cout << "\nDie gesuchte Zahl ist größer als " << guess << ".\n";
  } else {
    std::cout << "\nDie gesuchte Zahl ist zwischen 1 und " << maxNumber
              << " (eingeschlossen 1 und " << maxNumber << ").";
    std::cout << "\nDie gesuchte Zahl ist kleiner als " << guess << ".\n";
  }
  return false;
}