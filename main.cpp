#include <iostream>
#include <math.h>
#include <vector>

bool MainMenu();
void APstats();
void EditLists();
void CalculateMean();
void CalculateStandardDeviation();
void CalculateProbability();
void CalculateSamplingDistribution();
void CalculateConfidenceInterval();
void Calculus();

int main()
{
	while (true) 
	{
		if (!MainMenu())
			break;
		std::cout << "\n\n";
	}
}

bool MainMenu()
{
	std::cout << "Select a category: \n";
	std::cout << "-1: Quit\n";
	std::cout << "1: Calculus\n";
	std::cout << "2: Ap Stats\n";
	int choice;
	std::cin >> choice;
	std::cout << "\n";
	if (choice == -1)
	{
		return false;
	}
	if (choice == 1)
	{
		Calculus();
		return true;
	}
	else if (choice == 2)
	{
		APstats();
		return true;
	}
}

void APstats()
{
	int choice;
	std::cout << "Select an option: \n";
	std::cout << "-1: Back\n";
	std::cout << "0: Edit Lists/Data Sets\n";
	std::cout << "1: Calculate Mean\n";
	std::cout << "2: Calculate Standard Deviation\n";
	std::cout << "3: Calculate Probability\n";
	std::cout << "4: Calculate Sampling Distribution\n";
	std::cout << "5: Calculate Confidence Interval\n";
	std::cin >> choice;
	std::cout << "\n";
	if (choice == -1)
	{
		MainMenu();
	}
	else if (choice == 0)
	{
		EditLists();
	}
	else if (choice == 1)
	{
		CalculateMean();
	}
	else if (choice == 2)
	{
		CalculateStandardDeviation();
	}
	else if (choice == 3)
	{
		CalculateProbability();
	}
	else if (choice == 4)
	{
		CalculateSamplingDistribution();
	}
	else if (choice == 5)
	{
		CalculateConfidenceInterval();
	}
}

void EditLists()
{
	std::cout << "Not Implemented\n";
}

void CalculateMean()
{
	std::cout << "Not Implemented\n";
}

void CalculateStandardDeviation()
{
	std::cout << "Not Implemented\n";
}

void CalculateProbability()
{
	std::cout << "Not Implemented\n";
}

void CalculateSamplingDistribution()
{
	std::cout << "Not Implemented\n";
}

void CalculateConfidenceInterval()
{
	std::cout << "Not Implemented\n";
}

void Calculus()
{
	std::cout << "Not Implemented\n";
}