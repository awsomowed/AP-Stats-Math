#include <iostream>
#include <math.h>
#include <vector>

/* DataSet Class
 * By: Brandon Moyer
 *
 * Stoes information for a single data set
 * Contains a list, mean, and standard deviation
 */
class DataSet {
private:
	std::vector<float> FloatVec;
	float mean;
	float sd;
public:
	//Constructor
	DataSet()
	{
		mean = 0;
		sd = 0;
	}

	//Add an element to the end of the list
	void AddListElement(float Value)
	{
		FloatVec.push_back(Value);
	}

	//Insert an element at the specified index on the list
	void InsertListElement(float Value, int Index)
	{
		FloatVec.insert(FloatVec.begin() + Index, Value);
	}

	//Deletes the element at the specified index in the list
	void DeleteElement(int Index)
	{
		FloatVec.erase(FloatVec.begin() + Index);
	}

	//Gets the element at the specified index in the list
	float GetElement(int Index)
	{
		return FloatVec[Index];
	}

	//Gets the size of the list
	int ListSize()
	{
		return FloatVec.size();
	}

	//Returns the mean (does not calculate)
	float GetMean()
	{
		return mean;
	}

	//Sets the mean
	void SetMean(float newMean)
	{
		mean = newMean;
	}

	//Gets the standard deviation (does not calculate)
	float GetSD()
	{
		return sd;
	}

	//Sets the standard deviation
	void SetSD(float newSD)
	{
		sd = newSD;
	}
};

//Menu Functions
//[Example] CalculateMean() will prompt the user for the list to use
bool MainMenu();
void APstats();
void EditDataSets();
void EditDataSet(int Set);
void PrintDataSet(int Set);
void AddDataElement(int Set);
void DeleteDataElement(int Set);
void SetDataMean(int Set);
void SetDataSD(int Set);
void CalculateMean();
void CalculateStandardDeviation();
void CalculateProbability();
void CalculateSamplingDistribution();
void CalculateConfidenceInterval();
void Calculus();

//Mathematical Functions
//[Example] Mean(DataSet data) will actually calculate the mean

//Vector that stores all DataSets
static std::vector<DataSet> DataSets;

/* main()
 * By: Brandon Moyer
 * Main Function
 */
int main()
{
	//Repeats infinitely until main menu returns false
	while (MainMenu())
	{
		std::cout << "\n\n";
	}
}

/* MainMenu()
 * By: Brandon Moyer
 * Displays the main menu
 */
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
	return 0;
}

/* APstats()
 * By: Brandon Moyer
 * Displays the Ap stats menu
 */
void APstats()
{
	int choice;
	std::cout << "Select an option: \n";
	std::cout << "-1: Back\n";
	std::cout << "0: Edit Data Sets\n";
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
		EditDataSets();
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

/* EditDataSets()
 * By: Brandon Moyer
 * Displays all data sets
 */
void EditDataSets()
{
	int choice;
	std::cout << "Select a data set\n";
	std::cout << "-1: Back\n";
	std::cout << "0: New Data Set\n";
	for (int i = 0; i < DataSets.size(); i++)
	{
		std::cout << (i + 1) << ": Data Set " << (i + 1) << "\n";
	}
	std::cin >> choice;
	std::cout << "\n";
	if (choice == -1)
	{
		APstats();
	}
	else if (choice == 0)
	{
		DataSet newSet;
		DataSets.push_back(newSet);
		EditDataSets();
	}
	else if (choice < DataSets.size() + 1)
	{
		EditDataSet(choice - 1);
	}

}

/* EditDataSet(int Set)
 * By: Brandon Moyer
 * Shows menu for editing a data set
 */
void EditDataSet(int Set)
{
	//By using the &, you store a refrence to the data set
	//in the list instead of a copy of the data set
	DataSet& currentSet = DataSets[Set];

	int choice;
	std::cout << "-1: Back\n";
	std::cout << "0: Show Set Data\n";
	std::cout << "1: Add Element\n";
	std::cout << "2: Delete Element\n";
	std::cout << "3: Set Mean\n";
	std::cout << "4: Set Standard Deviation\n";
	std::cin >> choice;
	std::cout << "\n";

	if (choice == -1)
	{
		EditDataSets();
	}
	else if (choice == 0)
	{
		PrintDataSet(Set);
	}
	else if (choice == 1)
	{
		AddDataElement(Set);
	}
	else if (choice == 2)
	{
		DeleteDataElement(Set);
	}
	else if (choice == 3)
	{
		SetDataMean(Set);
	}
	else if (choice == 4)
	{
		SetDataSD(Set);
	}

}

/* PrintDataSet(int Set)
 * By: Brandon Moyer
 * Displays all data in a data set
 */
void PrintDataSet(int Set)
{
	DataSet& currentSet = DataSets[Set];
	std::cout << "List Elements: ";
	for (int i = 0; i < currentSet.ListSize(); i++)
	{
		if (i > 0)
		{
			std::cout << ", ";
		}
		std::cout << currentSet.GetElement(i);
	}
	std::cout << "\n";

	std::cout << "Mean: " << currentSet.GetMean() << "\n";

	std::cout << "Standard Deviation: " << currentSet.GetMean() << "\n";

	std::cout << "\n";

	EditDataSet(Set);
}

/* AddDataElement(int Set)
 * By: Brandon Moyer
 * Displays prompts for adding an element in a specified list
 */
void AddDataElement(int Set)
{
	DataSet& currentSet = DataSets[Set];

	int index;
	std::cout << "Where would you like to add the data (-1 for end)?\n";
	std::cin >> index;
	std::cout << "\n";

	float value;
	std::cout << "What is the data you would like to add?\n";
	std::cin >> value;
	std::cout << "\n";

	if (index == -1)
	{
		currentSet.AddListElement(value);
	}
	else
	{
		currentSet.InsertListElement(value, index);
	}

	EditDataSet(Set);
}

/* DeleteDataElement(int Set)
 * By: Brandon Moyer
 * Displays prompts for deleting an element in a specified list
 */
void DeleteDataElement(int Set)
{
	DataSet& currentSet = DataSets[Set];

	int index;
	std::cout << "What index would you like to remove?\n";
	std::cin >> index;
	std::cout << "\n";

	currentSet.DeleteElement(index);

	EditDataSet(Set);
}

/* SetDataMean(int Set)
 * By: Brandon Moyer
 * Promts the user to enter the mean for a specifed data set
 */
void SetDataMean(int Set)
{
	DataSet& currentSet = DataSets[Set];

	float newMean;
	std::cout << "Enter the new mean: ";
	std::cin >> newMean;
	std::cout << "\n";
	currentSet.SetMean(newMean);

	EditDataSet(Set);
}

/* SetDataSD(int Set)
 * By: Brandon Moyer
 * Prompts the user to enter the standard deviation for a specified data set
 */
void SetDataSD(int Set)
{
	DataSet& currentSet = DataSets[Set];

	float newSD;
	std::cout << "Enter new Standard Deviation: ";
	std::cin >> newSD;
	std::cout << "\n";
	currentSet.SetSD(newSD);

	EditDataSet(Set);
}

/* CalculateMean()
 * By:
 *
 */
void CalculateMean()
{
	std::cout << "Not Implemented\n";
}

/* CalculateStandardDeviation()
 * By:
 *
 */
void CalculateStandardDeviation()
{
	std::cout << "Not Implemented\n";
}

/* CalculateProbability()
 * By:
 *
 */
void CalculateProbability()
{
	std::cout << "Not Implemented\n";
}

/* CalculateSamplingDistribution()
 * By:
 *
 */
void CalculateSamplingDistribution()
{
	std::cout << "Not Implemented\n";
}

/* CalculateConfidenceInterval()
 * By:
 *
 */
void CalculateConfidenceInterval()
{
	std::cout << "Not Implemented\n";
}

/* Calculus()
 * By:
 *
 */
void Calculus()
{
	std::cout << "Not Implemented\n";
}