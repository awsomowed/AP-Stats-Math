#include <iostream>
#include <math.h>
#include <vector>
#include <string>

/* Controls how much extra debug info to print
 * 0 - None
 * 1 - Low
 * 2 - Medium
 * 3 - High
 * 4 - All
 * 5 - Excssive Logging
 * 6 - Potentially broken debug info
 */
static const int DEBUG_LEVEL = 4;

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
	DataSet() {
		mean = 0;
		sd = 0;
	}

	//Add an element to the end of the list
	void AddListElement(float Value) {
		FloatVec.push_back(Value);
	}

	//Insert an element at the specified index on the list
	void InsertListElement(float Value, int Index) {
		FloatVec.insert(FloatVec.begin() + Index, Value);
	}

	void MoveListElement(int start, int end) {
		float temp = FloatVec[start];
		if (end > start)
		{
			for (int i = start; i < end; i++)
			{
				FloatVec[i] = FloatVec[i + 1];
			}
			FloatVec[end] = temp;
		}
		else if (end < start)
		{
			for (int i = start; i > end; i--)
			{
				FloatVec[i] = FloatVec[i - 1];
			}
			FloatVec[end] = temp;
		}
	}

	//Deletes the element at the specified index in the list
	void DeleteElement(int Index) {
		FloatVec.erase(FloatVec.begin() + Index);
	}

	//Gets the element at the specified index in the list
	float GetElement(int Index) {
		return FloatVec[Index];
	}

	//Gets the size of the list
	int ListSize() {
		return FloatVec.size();
	}

	//Returns the mean (does not calculate)
	float GetMean() {
		return mean;
	}

	//Sets the mean
	void SetMean(float newMean) {
		mean = newMean;
	}

	//Gets the standard deviation (does not calculate)
	float GetSD() {
		return sd;
	}

	//Sets the standard deviation
	void SetSD(float newSD) {
		sd = newSD;
	}
};

/* ElementTypes enum
 * By: Brandon Moyer
 *
 * Enum for all equation element types
 */
enum class ElementTypes {
	null = -1,
	Number = 0,
	Variable = 1,
	Parentheses = 2,
	Power = 3,
	Addition = 4,
	Subtraction = 5,
	Multiplication = 6,
	Division = 7,
	Equals = 8,
	Sin = 9,
	Cos = 10,
	Tan = 11,
	ArcSin = 12,
	ArcCos = 13,
	ArcTan = 14,
	Factorial = 15
};

/* EquationElement class
 * By: Brandon Moyer
 *
 * Class that can store an entire equation, broken up into sub elements
 */
class EquationElement {
	/* Errored equations:
	 * (5x^3)^(14x^(2/y))/5+34-sin(2x)
	 */
private:
	ElementTypes type;
	double ElementNumber;
	char ElementVariable;
	//EquationElement* baseElement;
	//EquationElement* otherElement;
	std::vector<EquationElement> SubElements;

public:
	EquationElement(ElementTypes newType) {
		type = newType;
		ElementNumber = 0;
		ElementVariable = '\0';
	}

	//Sub Element methods
	void AddSubElement(EquationElement element) {
		SubElements.push_back(element);
	}

	void InsertSubElement(EquationElement element, int index) {
		SubElements.insert(SubElements.begin() + index, element);
	}

	EquationElement GetSubElement(int index) {
		return SubElements[index];
	}

	void DeleteSubElement(int index) {
		SubElements.erase(SubElements.begin() + index);
	}

	//Element type
	void SetElementType(ElementTypes newType) {
		type = newType;
	}

	ElementTypes GetElementType() {
		return type;
	}

	//Element Number
	void SetElementNumber(double newNumber) {
		ElementNumber = newNumber;
	}

	double GetElementNumber() {
		return ElementNumber;
	}

	//Element variable
	void SetElementVariable(char newVar) {
		ElementVariable = newVar;
	}

	char GetElementVariable() {
		return ElementVariable;
	}

	EquationElement GetNextElement(std::string& elems) {
		if (DEBUG_LEVEL >= 3) std::cout << "Size of elems: " << elems.size() << "\n";
		if (DEBUG_LEVEL >= 3) std::cout << "elems: " << elems << "\n";

		EquationElement* newElement = nullptr;

		int ParenthesesCounter = 0;
		std::string extractedElement;
		//Parentheses
		if (elems[0] == '(') {
			if (DEBUG_LEVEL >= 2) std::cout << "Parentheses Begin\n";
			ParenthesesCounter++;
			for (unsigned int i = 1; i < elems.size(); i++) {
				if (elems[i] == '(') {
					if (DEBUG_LEVEL >= 2) std::cout << "Moving up a nested level\n";
					extractedElement += elems[i];
					ParenthesesCounter++;
				}
				else if (elems[i] == ')') {
					if (DEBUG_LEVEL >= 2) std::cout << "Moving down a nested level\n";
					ParenthesesCounter--;
					if (ParenthesesCounter != 0) {
						extractedElement += elems[i];
					}
					else {
						if (DEBUG_LEVEL >= 2) std::cout << "Found outermost parentheses\n";
						elems.erase(elems.begin() + i);
						elems.erase(elems.begin());
						break;
					}
				}
				else {
					if (DEBUG_LEVEL >= 2) std::cout << "Element inside parentheses\n";
					extractedElement += elems[i];
				}
			}
			if (DEBUG_LEVEL >= 1) std::cout << "Parentheses with content of: " << extractedElement << "\n";
			newElement = new EquationElement(ElementTypes::Parentheses);
			newElement->ElementsFromStr(extractedElement);
			if (DEBUG_LEVEL >= 2) std::cout << "End of parentheses\n";
		}
		//Number
		else if (isdigit(elems[0]) || elems[0] == '.') {
			for (unsigned int i = 0; i < elems.size(); i++) {
				if (isdigit(elems[i]) || elems[i] == '.') {
					extractedElement += elems[i];
				}
				else {
					break;
				}
			}
			if (DEBUG_LEVEL >= 1) std::cout << "Number with value of: " << extractedElement << "\n";
			newElement = new EquationElement(ElementTypes::Number);
			newElement->ElementNumber = std::stod(extractedElement);
		}
		//Add
		else if (elems[0] == '+') {
			extractedElement += elems[0];
			if (DEBUG_LEVEL >= 1) std::cout << "Addition\n";
			newElement = new EquationElement(ElementTypes::Addition);
		}
		//Subtract
		else if (elems[0] == '-') {
			extractedElement += elems[0];
			if (DEBUG_LEVEL >= 1) std::cout << "Subtraction\n";
			newElement = new EquationElement(ElementTypes::Subtraction);
		}
		//Multiply
		else if (elems[0] == '*') {
			extractedElement += elems[0];
			if (DEBUG_LEVEL >= 1) std::cout << "Multiplication\n";
			newElement = new EquationElement(ElementTypes::Multiplication);
		}
		//Divide
		else if (elems[0] == '/') {
			extractedElement += elems[0];
			if (DEBUG_LEVEL >= 1) std::cout << "Division\n";
			newElement = new EquationElement(ElementTypes::Division);
		}
		//Sin
		else if (elems.size() >= 3 && elems.substr(0, 3) == "sin") {
			elems.erase(elems.begin(), elems.begin() + 3);
			if (DEBUG_LEVEL >= 1) std::cout << "Found Sin\n";
			newElement = new EquationElement(ElementTypes::Sin);
			newElement->SubElements.push_back(GetNextElement(elems));
			//newElement->baseElement = &GetNextElement(elems);
		}
		//Cos
		else if (elems.size() >= 3 && elems.substr(0, 3) == "cos") {
			elems.erase(elems.begin(), elems.begin() + 3);
			if (DEBUG_LEVEL >= 1) std::cout << "Found Cos\n";
			newElement = new EquationElement(ElementTypes::Cos);
			newElement->SubElements.push_back(GetNextElement(elems));
			//newElement->baseElement = &GetNextElement(elems);
		}
		//Tan
		else if (elems.size() >= 3 && elems.substr(0, 3) == "tan") {
			elems.erase(elems.begin(), elems.begin() + 3);
			if (DEBUG_LEVEL >= 1) std::cout << "Found Tan\n";
			newElement = new EquationElement(ElementTypes::Tan);
			newElement->SubElements.push_back(GetNextElement(elems));
			//newElement->baseElement = &GetNextElement(elems);
		}
		//ArcSin
		else if (elems.size() >= 6 && elems.substr(0, 6) == "arcsin") {
			elems.erase(elems.begin(), elems.begin() + 6);
			if (DEBUG_LEVEL >= 1) std::cout << "Found ArcSin\n";
			newElement = new EquationElement(ElementTypes::ArcSin);
			newElement->SubElements.push_back(GetNextElement(elems));
			//newElement->baseElement = &GetNextElement(elems);
		}
		//ArcCos
		else if (elems.size() >= 6 && elems.substr(0, 6) == "arccos") {
			elems.erase(elems.begin(), elems.begin() + 6);
			if (DEBUG_LEVEL >= 1) std::cout << "Found ArcCos\n";
			newElement = new EquationElement(ElementTypes::ArcCos);
			newElement->SubElements.push_back(GetNextElement(elems));
			//newElement->baseElement = &GetNextElement(elems);
		}
		//ArcTan
		else if (elems.size() >= 6 && elems.substr(0, 6) == "arctan") {
			elems.erase(elems.begin(), elems.begin() + 6);
			if (DEBUG_LEVEL >= 1) std::cout << "Found ArcTan\n";
			newElement = new EquationElement(ElementTypes::ArcTan);
			newElement->SubElements.push_back(GetNextElement(elems));
			//newElement->baseElement = &GetNextElement(elems);
		}
		//Variables
		else if (isalpha(elems[0])) {
			extractedElement += elems[0];
			if (DEBUG_LEVEL >= 1) std::cout << "Variable\n";
			newElement = new EquationElement(ElementTypes::Variable);
			newElement->ElementVariable = extractedElement[0];
		}

		elems.erase(elems.begin(), elems.begin() + extractedElement.size());

		if (newElement == nullptr)
		{
			if (DEBUG_LEVEL >= 1) std::cout << "newElement is a nullptr, returning null equation element\n";
			return EquationElement(ElementTypes::null);
		}

		//Factorials
		if (elems.size() > 0 && elems[0] == '!') {
			if (DEBUG_LEVEL >= 1) std::cout << "Found Factorial, Converting...\n";
			EquationElement factorialElement(ElementTypes::Factorial);
			factorialElement.SubElements.push_back(*newElement);
			//factorialElement.baseElement = newElement;

			elems.erase(elems.begin());

			if (DEBUG_LEVEL >= 1) std::cout << "Converted to Factorial\n";

			newElement = new EquationElement(factorialElement);

			newElement = &factorialElement;
		}

		//Exponent
		if (elems.size() > 0 && elems[0] == '^') {
			if (DEBUG_LEVEL >= 1) std::cout << "Found Exponent, Converting...\n";

			EquationElement powElement(ElementTypes::Power);
			//powElement.baseElement = newElement;
			powElement.SubElements.push_back(*newElement);
			if (DEBUG_LEVEL >= 3) std::cout << "Added previous element as base element of exponent\n";

			elems.erase(elems.begin());

			if (DEBUG_LEVEL >= 1) std::cout << "Getting Exponent...\n";

			EquationElement expElement = GetNextElement(elems);
			powElement.SubElements.push_back(expElement);
			//powElement.otherElement = &expElement;

			if (DEBUG_LEVEL >= 1) std::cout << "Converted to Exponent\n";

			//newElement = new EquationElement(ElementTypes::None);

			newElement = new EquationElement(powElement);

			if (DEBUG_LEVEL >= 3) std::cout << "Set new element to powElement\n";
		}

		//Equals
		if (elems.size() > 0 && elems[0] == '=') {
			std::cout << "Found Equals, Converting...\n";

			EquationElement equalsElement(ElementTypes::Equals);
			//equalsElement.baseElement = newElement;
			equalsElement.SubElements.push_back(*newElement);

			elems.erase(elems.begin());

			std::cout << "Getting right side...\n";

			EquationElement rightElement = GetNextElement(elems);
			//equalsElement.otherElement = rightElement;
			equalsElement.SubElements.push_back(rightElement);


			newElement = new EquationElement(equalsElement);

			newElement = &equalsElement;
		}

		if (DEBUG_LEVEL >= 1) std::cout << "Found Element: " << extractedElement << "\n";
		if (DEBUG_LEVEL >= 1) std::cout << "Remaining string: " << elems << "\n";

		//return extractedElement;
		if (DEBUG_LEVEL >= 4) std::cout << "Return pointer: " << newElement << "\n";
		if (DEBUG_LEVEL >= 4) { if (newElement != NULL) std::cout << ("Return value: " + (std::string)*newElement) << "\n"; else std::cout << "Return value: {NULL POINTER}\n"; };

		EquationElement returnElement = *newElement;
		return returnElement;
	}

	void ElementsFromStr(std::string subElems) {
		if (DEBUG_LEVEL >= 3) std::cout << "Size of subElems: " << subElems.size() << "\n";
		while (subElems.size() > 0) {
			if (DEBUG_LEVEL >= 3) std::cout << "Remaining input string (subElems): " << subElems << "\n";
			SubElements.push_back(GetNextElement(subElems));
		}
	}

	operator std::string()
	{
		std::string output;

		if (type == ElementTypes::null)
		{
			if (DEBUG_LEVEL >= 1) std::cout << "Attemted to convert EquationElement with type of null to string\n";
		}
		else if (type == ElementTypes::Number)
		{
			output += std::to_string(ElementNumber);
			//Remove leading zeroes
			while (output[0] == '0' && output[1] == '0')
				output.erase(output.begin());
			//Remove trailing zeroes and decimals
			while (output[output.size() - 1] == '0' || output[output.size() - 1] == '.')
			{
				if (DEBUG_LEVEL >= 6) std::cout << "Number Output: " << output << "\n";
				output.erase(output.end() - 1);
				if (DEBUG_LEVEL >= 6) std::cout << "Removed Trailing: " << output << "\n";
			}
		}
		else if (type == ElementTypes::Variable)
		{
			output += ElementVariable;
		}
		else if (type == ElementTypes::Parentheses)
		{
			output += "(";
			for (unsigned int i = 0; i < SubElements.size(); i++)
			{
				output += SubElements[i];
			}
			output += ")";
		}
		else if (type == ElementTypes::Power)
		{
			if (SubElements.size() > 0) output += SubElements[0]; else std::cout << "Failed to get 0th sub element of a power element\n";
			output += "^";
			if (SubElements.size() > 1) output += SubElements[1]; else std::cout << "Failed to get 1st sub element of a power element\n";
		}
		else if (type == ElementTypes::Addition)
		{
			output += "+";
		}
		else if (type == ElementTypes::Subtraction)
		{
			output += "-";
		}
		else if (type == ElementTypes::Multiplication)
		{
			output += "*";
		}
		else if (type == ElementTypes::Division)
		{
			output += "/";
		}
		else if (type == ElementTypes::Equals)
		{
			output += SubElements[0];
			output += "=";
			output += SubElements[1];
		}
		else if (type == ElementTypes::Sin)
		{
			output += "sin";
			output += SubElements[0];
		}
		else if (type == ElementTypes::Cos)
		{
			output += "cos";
			output += SubElements[0];
		}
		else if (type == ElementTypes::Tan)
		{
			output += "sin";
			output += SubElements[0];
		}
		else if (type == ElementTypes::ArcSin)
		{
			output += "arcsin";
			output += SubElements[0];
		}
		else if (type == ElementTypes::ArcCos)
		{
			output += "arccos";
			output += SubElements[0];
		}
		else if (type == ElementTypes::ArcTan)
		{
			output += "arctan";
			output += SubElements[0];
		}
		else if (type == ElementTypes::Factorial)
		{
			output += SubElements[0];
			output += "!";
		}

		return output;
	}

	friend std::ostream& operator<<(std::ostream& os, EquationElement& obj)
	{
		os << (std::string)obj;
		return os;
	}
};

//Menu Functions
//[Example] CalculateMean() will prompt the user for the list to use
void MainMenu();
void EditGlobals();
void EditDataSets();
void EditDataSet(int Set);
void PrintDataSet(int Set);
void AddDataElement(int Set);
void MoveDataElement(int Set);
void DeleteDataElement(int Set);
void SetDataMean(int Set);
void SetDataSD(int Set);
void EditEquations();
EquationElement InputEquation();
void EditEquation(int Equ);
void APstats();
void CalculateMean();
void CalculateStandardDeviation();
void CalculateProbability();
void CalculateSamplingDistribution();
void CalculateConfidenceInterval();
void Calculus();

//Testing

//Mathematical Functions
//[Example] Mean(DataSet data) will actually calculate the mean

//Vector that stores all DataSets
static std::vector<DataSet> DataSets;

//Vector that stores all Equations
static std::vector<EquationElement> Equations;

/* main()
 * By: Brandon Moyer
 * Main Function
 */
int main() {
	//Shows the main menu
	MainMenu();
}

/* MainMenu()
 * By: Brandon Moyer
 * Displays the main menu
 */
void MainMenu() {
	bool Continue = true;
	while (Continue) {
		std::cout << "Select a category: \n";
		std::cout << "-1: Quit\n";
		std::cout << "0: Edit Data Sets/Equations\n";
		std::cout << "1: Calculus\n";
		std::cout << "2: Ap Stats\n";
		int input = INT16_MAX;
		if (!(std::cin >> input)) {
			input = INT16_MAX;
			std::cin.clear();
			std::cin.ignore();
		}
		std::cout << "\n";
		if (input == -1) {
			Continue = false;
		}
		else if (input == 0) {
			EditGlobals();
		}
		else if (input == 1) {
			Calculus();
		}
		else if (input == 2) {
			APstats();
		}
	}
}

void EditGlobals() {
	bool Continue = true;
	while (Continue) {
		std::cout << "Select an option: \n";
		std::cout << "-1: Back\n";
		std::cout << "1: Edit Data Sets\n";
		std::cout << "2: Edit Equations\n";
		int input{};
		if (!(std::cin >> input)) {
			input = INT16_MAX;
			std::cin.clear();
			std::cin.ignore();
		}
		std::cout << "\n";
		if (input == -1) {
			Continue = false;
		}
		else if (input == 1) {
			EditDataSets();
		}
		else if (input == 2) {
			EditEquations();
		}
	}

}

/* EditDataSets()
 * By: Brandon Moyer
 * Displays all data sets
 */
void EditDataSets() {
	bool Continue = true;
	while (Continue) {
		std::cout << "Select a data set\n";
		std::cout << "-1: Back\n";
		std::cout << "0: New Data Set\n";
		for (unsigned int i = 0; i < DataSets.size(); i++) {
			std::cout << (i + 1) << ": Data Set " << (i + 1) << "\n";
		}
		int input{};
		if (!(std::cin >> input)) {
			input = INT16_MAX;
			std::cin.clear();
			std::cin.ignore();
		}
		std::cout << "\n";
		if (input == -1) {
			Continue = false;
		}
		else if (input == 0) {
			DataSet newSet;
			DataSets.push_back(newSet);
		}
		else if (unsigned(input) < DataSets.size() + 1) {
			EditDataSet(input - 1);
		}
	}
}

/* EditDataSet(int Set)
 * By: Brandon Moyer
 * Shows menu for editing a data set
 */
void EditDataSet(int Set) {
	//By using the &, you store a refrence to the data set
	//in the list instead of a copy of the data set
	DataSet& currentSet = DataSets[Set];

	bool Continue = true;
	while (Continue) {
		std::cout << "-1: Back\n";
		std::cout << "0: Show Set Data\n";
		std::cout << "1: Add Element\n";
		std::cout << "2: Move Element\n";
		std::cout << "3: Delete Element\n";
		std::cout << "4: Set Mean\n";
		std::cout << "5: Set Standard Deviation\n";
		int input{};
		if (!(std::cin >> input)) {
			input = INT16_MAX;
			std::cin.clear();
			std::cin.ignore();
		}
		std::cout << "\n";

		if (input == -1) {
			Continue = false;
		}
		else if (input == 0) {
			PrintDataSet(Set);
		}
		else if (input == 1) {
			AddDataElement(Set);
		}
		else if (input == 2)
		{
			MoveDataElement(Set);
		}
		else if (input == 3) {
			DeleteDataElement(Set);
		}
		else if (input == 4) {
			SetDataMean(Set);
		}
		else if (input == 5) {
			SetDataSD(Set);
		}
	}
}

/* PrintDataSet(int Set)
 * By: Brandon Moyer
 * Displays all data in a data set
 */
void PrintDataSet(int Set) {
	DataSet& currentSet = DataSets[Set];
	std::cout << "List Elements: ";
	for (int i = 0; i < currentSet.ListSize(); i++) {
		if (i > 0) {
			std::cout << ", ";
		}
		std::cout << currentSet.GetElement(i);
	}
	std::cout << "\n";

	std::cout << "Mean: " << currentSet.GetMean() << "\n";

	std::cout << "Standard Deviation: " << currentSet.GetMean() << "\n";

	std::cout << "\n";
}

/* AddDataElement(int Set)
 * By: Brandon Moyer
 * Displays prompts for adding an element in a specified list
 */
void AddDataElement(int Set) {
	DataSet& currentSet = DataSets[Set];

	//std::cout << "Where would you like to add the data (-1 for end)?\n";
	//int index{};
	//if (!(std::cin >> index)) {
	//	index = INT16_MAX;
	//	std::cin.clear();
	//	std::cin.ignore();
	//}
	//std::cout << "\n";

	std::cout << "What is the data you would like to add?\n";
	float value;
	while (!(std::cin >> value)) {
		std::cin.clear();
		std::cin.ignore();
		std::cout << "Invalid input, try again: ";
	}
	//std::cin >> value;
	//std::cin.clear();
	//std::cin.ignore(256);
	std::cout << "\n";

	//if (index == -1) {
	currentSet.AddListElement(value);
	//}
	//else {
	//	currentSet.InsertListElement(value, index);
	//}
}

void MoveDataElement(int Set) {
	DataSet& currentSet = DataSets[Set];

	std::cout << "What is the element you would like to move?\n";
	int start;
	while (!(std::cin >> start))
	{
		std::cin.clear();
		std::cin.ignore();
		std::cout << "Invalid input, try again: ";
	}
	std::cout << "\n";

	std::cout << "What is the position you would like to move to?\n";
	int end;
	while (!(std::cin >> end))
	{
		std::cin.clear();
		std::cin.ignore();
		std::cout << "Invalid input, try again: ";
	}
	std::cout << "\n";

	currentSet.MoveListElement(start - 1, end - 1);
}

/* DeleteDataElement(int Set)
 * By: Brandon Moyer
 * Displays prompts for deleting an element in a specified list
 */
void DeleteDataElement(int Set) {
	DataSet& currentSet = DataSets[Set];

	std::cout << "What index would you like to remove?\n";
	int index{};
	if (!(std::cin >> index)) {
		index = INT16_MAX;
		std::cin.clear();
		std::cin.ignore();
	}
	std::cout << "\n";

	currentSet.DeleteElement(index);
}

/* SetDataMean(int Set)
 * By: Brandon Moyer
 * Promts the user to enter the mean for a specifed data set
 */
void SetDataMean(int Set) {
	DataSet& currentSet = DataSets[Set];

	std::cout << "Enter the new mean: ";
	float newMean;
	if (!(std::cin >> newMean)) {
		newMean = INT16_MAX;
		std::cin.clear();
		std::cin.ignore();
	}
	std::cout << "\n";
	currentSet.SetMean(newMean);
}

/* SetDataSD(int Set)
 * By: Brandon Moyer
 * Prompts the user to enter the standard deviation for a specified data set
 */
void SetDataSD(int Set) {
	DataSet& currentSet = DataSets[Set];

	std::cout << "Enter new Standard Deviation: ";
	float newSD;
	if (!(std::cin >> newSD)) {
		newSD = INT16_MAX;
		std::cin.clear();
		std::cin.ignore();
	}
	std::cout << "\n";
	currentSet.SetSD(newSD);
}

void EditEquations()
{
	bool Continue = true;
	while (Continue) {
		std::cout << "Select an Equation\n";
		std::cout << "-1: Back\n";
		std::cout << "0: New Equation\n";
		for (unsigned int i = 0; i < Equations.size(); i++) {
			std::cout << (i + 1) << ": " << Equations[i] << "\n";
			//std::cout << (i + 1) << ": Equation " << (i + 1) << "\n";
		}
		int input;
		bool cinRes = true;
		cinRes = !(std::cin >> input);
		if (cinRes) {
			input = INT16_MAX;
			std::cin.clear();
			std::cin.ignore();
		}
		std::cout << "\n";
		if (input == -1) {
			Continue = false;
		}
		else if (input == 0) {
			Equations.push_back(InputEquation());
		}
		else if (unsigned(input) < Equations.size() + 1) {
			EditEquation(input - 1);
		}
	}
}

/* InputEquation()
 * By: Brandon Moyer
 * Gets an equation as a string and converts it to a single EquationElement object
*/
EquationElement InputEquation() {
	std::string inputStr;

	std::cout << "Enter an equation: ";

	std::cin.ignore();
	std::getline(std::cin, inputStr);

	EquationElement BaseElement(ElementTypes::Parentheses);
	BaseElement.ElementsFromStr(inputStr);

	std::cout << "\n";

	return BaseElement;
}

/* EditEquation(int Equ)
 * By:
 *
 */
void EditEquation(int Equ)
{
	std::cout << "Not Implemented\n";
}

/* APstats()
 * By: Brandon Moyer
 * Displays the Ap stats menu
 */
void APstats() {
	bool Continue = true;
	while (Continue) {
		std::cout << "Select an option: \n";
		std::cout << "-1: Back\n";
		std::cout << "0: Edit Data Sets/Equations\n";
		std::cout << "1: Calculate Mean\n";
		std::cout << "2: Calculate Standard Deviation\n";
		std::cout << "3: Calculate Probability\n";
		std::cout << "4: Calculate Sampling Distribution\n";
		std::cout << "5: Calculate Confidence Interval\n";
		int input{};
		if (!(std::cin >> input)) {
			input = INT16_MAX;
			std::cin.clear();
			std::cin.ignore();
		}
		std::cout << "\n";
		if (input == -1) {
			Continue = false;
		}
		else if (input == 0) {
			EditDataSets();
		}
		else if (input == 1) {
			CalculateMean();
		}
		else if (input == 2) {
			CalculateStandardDeviation();
		}
		else if (input == 3) {
			CalculateProbability();
		}
		else if (input == 4) {
			CalculateSamplingDistribution();
		}
		else if (input == 5) {
			CalculateConfidenceInterval();
		}
	}
}

/* CalculateMean()
 * By:
 *
 */
void CalculateMean() {
	//Demo code
	DataSet* set;

	if (true) {
		set = &DataSets[0];
	}
	set->GetElement(0);
}

/* CalculateStandardDeviation()
 * By:
 *
 */
void CalculateStandardDeviation() {
	std::cout << "Not Implemented\n";
}

/* CalculateProbability()
 * By:
 *
 */
void CalculateProbability() {
	std::cout << "Not Implemented\n";
}

/* CalculateSamplingDistribution()
 * By:
 *
 */
void CalculateSamplingDistribution() {
	std::cout << "Not Implemented\n";
}

/* CalculateConfidenceInterval()
 * By:
 *
 */
void CalculateConfidenceInterval() {
	std::cout << "Not Implemented\n";
}

/* Calculus()
 * By:
 *
 */
void Calculus() {
	bool Continue = true;
	while (Continue)
	{
		std::cout << "Select an option\n";
		std::cout << "-1: Back\n";
		int input{};
		if (!(std::cin >> input)) {
			input = INT16_MAX;
			std::cin.clear();
			std::cin.ignore();
		}
		std::cout << "\n";
		if (input == -1) {
			Continue = false;
		}
	}
}