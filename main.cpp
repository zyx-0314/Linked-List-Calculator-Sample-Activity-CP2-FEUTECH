#include <iostream>

struct Computation
{
	const static int MAX = 2;
	double val[MAX];
	std::string mathOperator;


	Computation(double val[MAX])
	{
		for (int i = 0; i < 2; i++)
			this->val[i] = val[i];
	}

	double Add() { 
		this->mathOperator = "+";
		return val[0] + val[1]; 
	}

	double Subtract() { 
		this->mathOperator = "-";
		return val[0] - val[1];
	}

	double Division() { 
		this->mathOperator = "/";
		return val[0] / val[1];
	}

	double Multiplication() { 
		this->mathOperator = "*";
		return val[0] * val[1];
	}
};

struct History
{
	// Single LinkedList

	// Address
	History* next = NULL;
	// Data
	// Sample 1: The data integrated inside the node
	double val[2] = { 0,0 }, result = 0;
	std::string mathOperator = "";

	// Sample 2: Using another Struct to store data
	Computation* data = NULL;

};

// menus
int MainMenu();
bool MathMenu(History*&, History*&, History*&);

int main()
{
	bool loop = true;
	History* head = NULL,* tail = NULL,* temp = NULL;

	while (true)
	{
		switch (MainMenu())
		{
		case 1:
			do
				loop = MathMenu(head, tail, temp);
			while (loop);
			break;
		case 2:
			std::cout << "History";
			break;
		case 0:
			exit(0);
		default:
			break;
		}
	}
}

int MainMenu()
{
	int choice;

	do
	{
		std::cout
			<< "1. Calculator\n"
			<< "2. History\n"
			<< "0. Exit\n"
			<< "\n"
			<< ":: ";
		std::cin >> choice;
	} while (choice < 0 || choice > 2);

	system("cls");

	return choice;
}

bool MathMenu(History*& head, History*& tail, History*& temp)
{
	int choice, counter = 0;
	// option 1
	History* history = new History;
	// option 2
	double val[2];	// work as placeholder

	std::cout
		<< "1. Add\n"
		<< "2. Subtract\n"
		<< "3. Multiply\n"
		<< "4. Divide\n"
		<< "0. Return\n"
		<< "\n"
		<< ":: ";
	std::cin >> choice;

	system("cls");

	if (!choice)
		return 0;

	for (int i = 0; i < 2; i++)
	{
		// Option 1
		std::cout << "(Option1) Value " << counter + 1 << ":";
		std::cin >> history->val[counter];
		// Option 2
		std::cout << "(Option2) Value " << counter + 1 << ":";
		std::cin >> val[counter];

		counter++;
	}

	// Option 2
	history->data = new Computation(val);

	switch (choice)
	{
	case 1:
		// Option 1
		history->mathOperator = "+";
		std::cout << history->val[0] << history->mathOperator << history->val[1] << " = " << history->val[0] + history->val[1] << "\n";

		// Option 2
		history->data->mathOperator = "+";
		std::cout << history->data->val[0] << history->data->mathOperator << history->data->val[1] << " = " << history->data->Add() << "\n";
		break;
	case 2:
		// Option 1
		history->mathOperator = "-";
		std::cout << history->val[0] << history->mathOperator << history->val[1] << " = " << history->val[0] - history->val[1] << "\n";

		// Option 2
		history->data->mathOperator = "-";
		std::cout << history->data->val[0] << history->data->mathOperator << history->data->val[1] << " = " << history->data->Subtract() << "\n";
		break;
	case 3:
		// Option 1
		history->mathOperator = "*";
		std::cout << history->val[0] << history->mathOperator << history->val[1] << " = " << history->val[0] * history->val[1] << "\n";

		// Option 2
		history->data->mathOperator = "*";
		std::cout << history->data->val[0] << history->data->mathOperator << history->data->val[1] << " = " << history->data->Multiplication() << "\n";
		break;
	case 4:
		if (!val[1])
		{
			std::cout << "Invalid!\n";
			break;
		}
		// Option 1
		history->mathOperator = "/";
		std::cout << history->val[0] << history->mathOperator << history->val[1] << " = " << history->val[0] / history->val[1] << "\n";

		// Option 2
		history->data->mathOperator = "/";
		std::cout << history->data->val[0] << history->data->mathOperator << history->data->val[1] << " = " << history->data->Division() << "\n";
		break;
	default:
		break;
	}

	// if head is empty
	if (!head)
	{
		head = new History;
		head = history;
		head->next = NULL;

		tail = new History;
		tail = head;
	}
	// if head is not empty
	else
	{
		temp = new History;
		temp = history;
		tail->next = temp;

		tail = temp;
	}

	system("pause");
	system("cls");

	return 1;
}
