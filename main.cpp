#include <iostream>

struct DataHolder
{
    // Member Variable
	const static int MAX = 2;
	double val[MAX], result;
	std::string mathOperator;

    // Member Function
	void Display()
	{
	    // will display when the mathOperator is over 1 character
            // reason to catch the error created in division in case
	    if (this->mathOperator.length() != 1) std::cout << this->mathOperator << "\n";
	    // else display in format
	    else std::cout << this->val[0] << " " << this->mathOperator << " " << this->val[1] << " = " << this->result << "\n";
	}
};

// Single LinkedList
struct History
{
	// Address
	History* next = NULL;

	// Data
        // as you can see it is creating a new data in heap already
            // reason it make sure that every node has prepared holder when needed
	DataHolder* data = new DataHolder;

};

// Menus
int MainMenu();
int MathMenu();

// Functionalities
    // Following Single Responsibility Principle
void AddHistory(History*&, History*&, History*&);
void DisplayHistory(History*&);
void ClearHistory(History*&, History*&);
void InputValue(History*&);
void Computation(int, History*&);

// Math Formulas
double Add(double[], const int);
double Subtract(double[], const int);
double Division(double[], const int);
double Multiplication(double[], const int);

int main()
{
    int choice;
    History* temp = NULL; // this will create a temporary holder of datas
	History* head = NULL,* tail = NULL; // this serves as your tracker of head and tail

	while (true)
	{
		switch (MainMenu())
		{
		case 1:
			do
            {
				choice = MathMenu();

				// if choice is 0(false) then it will be converted to true then will break
				if (!choice) break;

                InputValue(temp);

                Computation(choice, temp);

                AddHistory(head, tail, temp);
            }
			while (true);
			break;
		case 2:
			DisplayHistory(head);
			break;
        case 3:
            ClearHistory(head, tail);
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
			<< "3. Clear History\n"
			<< "\n"
			<< "0. Exit\n"
			<< "\n"
			<< ":: ";
		std::cin >> choice;
    // the condition provided below states that if choice is lower than 0 or higher than 3 then its invalid
        // change it depends on the options
	} while (choice < 0 || choice > 3);

	system("cls");

	return choice;
}

int MathMenu()
{
	int choice;

	do
	{
        std::cout
            << "1. Add\n"
            << "2. Subtract\n"
            << "3. Multiply\n"
            << "4. Divide\n"
            << "0. Return\n"
            << "\n"
            << ":: ";
        std::cin >> choice;
	} while (choice < 0 || choice > 4);

	system("cls");

	return choice;
}

void AddHistory(History*& head, History*& tail, History*& temp)
{
    // first it will display result for user
    if (temp->data->mathOperator.length() == 1) std::cout
        << temp->data->val[0] << " "
        << temp->data->mathOperator << " "
        << temp->data->val[1] << " = "
        << temp->data->result << "\n";

    // then the following is the logic on how logging happens

    // if head is empty
	if (!head)
	    // copy the address from temp to head
            // since it will be the first node
		head = temp;
	// if head is not empty
	else
	    // since the there is new node(temp) addition to the LinkedList you need to inform the old tail of the temp(which is the new node)
		tail->next = temp;

    // set the new node(temp) as the tail
    tail = temp;

    // set the next to null since its the tail node
    tail->next = NULL;

	system("pause");
	system("cls");
}

void DisplayHistory(History*& head)
{
    History* temp = head;

    // the condition sets that it will be true when the temp is NULL
    if (!temp)
        std::cout << "-- No History Yet! --\n";
    else
    {
        std::cout << "History\n";

        // this part is the code for traversal until tail is meet
            // you can identify tail when the temp is NULL
        while(temp)
        {
            temp->data->Display();
            temp = temp->next;
        }

    }

    std::cout << "\n";

    system("pause");
    system("cls");
}

void ClearHistory(History*& head, History*& tail)
{
    History* temp,* current = head;

    // the condition sets that it will be true when the head is NULL
    if (!head)
        std::cout << "-- No History Yet! --\n\n";
    else
    {
        // this is also way of traversal but deletes every nodes
        while(temp)
        {
            // temp will hold the next node
            temp = current->next;
            // while the current node will be deleted
            delete current;
            current = temp;
        }

        // since the whole node is deleted it will reset both head and tail
        head = NULL;
        tail = NULL;

        std::cout << "-- History Clear! --\n";
    }

    system("pause");
    system("cls");
}

void InputValue(History*& history)
{
    history = new History;

    // the parameter is coming from MAX of Node Data Holder which will make the same MAX for all
    for (int i = 0; i < history->data->MAX; i++)
	{
		std::cout << "Value " << i + 1 << ":";
		std::cin >> history->data->val[i];
	}
}

void Computation(int choice, History*& history)
{
    switch (choice)
	{
	case 1:
		history->data->mathOperator = "+";
		history->data->result = Add(
                                history->data->val,
                                history->data->MAX
                        );
		break;
	case 2:
		history->data->mathOperator = "-";
		history->data->result = Subtract(
                                history->data->val,
                                history->data->MAX
                        );
		break;
	case 3:
		history->data->mathOperator = "*";
		history->data->result = Multiplication(
                                history->data->val,
                                history->data->MAX
                        );
		break;
	case 4:
		if (!history->data->val[1])
		{
			std::cout << "Division Input Error!\n";
			history->data->mathOperator = "Division Input Error!";
			break;
		}
		history->data->mathOperator = "/";
		history->data->result = Division(
                                history->data->val,
                                history->data->MAX
                        );
		break;
	default:
		break;
	}
}

double Add(double val[], const int MAX) {
    double total = 0;
    for (int i = 0; i < MAX; i++)
        total += val[i];
    return total;
}

double Subtract(double val[], const int MAX) {
    double total = val[0];
    for (int i = 1; i < MAX; i++)
        total -= val[i];
    return total;
}

double Division(double val[], const int MAX) {
    double total = val[0];
    for (int i = 1; i < MAX; i++)
        total /= val[i];
    return total;
}

double Multiplication(double val[], const int MAX) {
    double total = val[0];
    for (int i = 1; i < MAX; i++)
        total *= val[i];
    return total;
}
