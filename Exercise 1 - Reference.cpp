#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int placeBetReturn(int& playerGold);
void placeBetVoid(int& playerGold, int& currentBet);

void rollDice(int& die1, int& die2);

void evaluatePayout(int& playerGold, int playerBet, int pDie1, int pDie2, int aiSum);

void playRound(int& playerGold);


int main() {
	srand(time(NULL));

	int playerGold = 1000;

	cout << "Welcome to the Dice Game!" << endl;
	cout << "You start with " << playerGold << " gold." << endl;
	while (playerGold > 0)
	{
		playRound(playerGold);
	}

}
int placeBetReturn(int& playerGold) {
	int bet = 0;

	while (true) {
		cout << "Current Gold: " << playerGold << "\n";
		cout << "Enter your bet: ";
		cin >> bet;

		if (bet > 0 && bet <= playerGold) {
			playerGold -= bet;
			return bet;
		}
		cout << "Invalid bet! You must bet between 1 and " << playerGold << " gold.\n\n";
	}
}

void placeBetVoid(int& playerGold, int& currentBet) {
	while (true) {
		cout << "Current Gold: " << playerGold << "\n";
		cout << "Enter your bet: ";
		cin >> currentBet;

		if (currentBet > 0 && currentBet <= playerGold) {
			playerGold -= currentBet;
			return;
		}
		cout << "Invalid bet! You must bet between 1 and " << playerGold << "gold. \n\n";
	}
}

void rollDice(int& die1, int& die2) {
	die1 = rand() % 6 + 1;
	die2 = rand() % 6 + 1;
}

void evaluatePayout(int& playerGold, int playerBet, int pDie1, int pDie2, int aiSum) {
	int playerSum = pDie1 + pDie2;

	cout << "\nResults:\n";
	cout << "AI Total: " << aiSum << "\n";
	cout << "Player Total: " << playerSum;

	if (playerSum == aiSum);

	if (pDie1 == 1 && pDie2 == 1) {
		cout << "(SNAKE EYES!)";
	}
	cout << "\n\n";

	if (playerSum == aiSum) {
		cout << "It's a draw! Your bet is returned.\n";
		playerGold += playerBet;
	}

	else if (pDie1 == 1 && pDie2 == 1) {
		cout << "Amazing! Snake Eyes! You win thrice your bet! \n";
		playerGold += (playerBet * 3);
	}

	else if (playerSum > aiSum) {
		cout << "You win! You double your bet.\n";
		playerGold += (playerBet * 2);
	}

	else {
		cout << "AI wins! You lost your bet.\n";
	}
}
void playRound(int& playerGold) {
	int currentBet = 0;

	placeBetVoid(playerGold, currentBet);
	cout << "Bet of" << currentBet << " accepted.\n\n";

	int aiDie1 = 0, aiDie2 = 0;
	rollDice(aiDie1, aiDie2);
	int aiSum = aiDie1 + aiDie2;
	cout << "AI has rolled the dice!\n";

	int pDie1 = 0, pDie2 = 0;
	cout << "Press enter to roll your dice!";
	cin.ignore();
	cin.get();

	rollDice(pDie1, pDie2);
	cout << "You rolled a " << pDie1 << " and a " << pDie2 << ".\n";

	evaluatePayout(playerGold, currentBet, pDie1, pDie2, aiSum);
}
