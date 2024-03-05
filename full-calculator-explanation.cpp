#include <iostream>
#include <string>

struct DataHolder
{
    // Member Variable
    const static int MAX = 2;
    double val[MAX] = { 0, 0 }, result = 0;
    std::string mathOperator = "";

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
int HistoryMenu(int, int);

// Functionalities
    // Following Single Responsibility Principle
void AddHistory(History*&, History*&, History*&);
void DisplayHistory(History*, int, int);
void ClearHistory(History*&);
void InputValue(History*&);
void Computation(int, History*&);
int HistoryFunctionalities(int&, History*&, History*&);
int UpdateHistory();


// Math Formulas
double Add(double[], const int);
double Subtract(double[], const int);
double Division(double[], const int);
double Multiplication(double[], const int);

int main()
{
    int choice, historyCounter = 0;
    History* temp = NULL; // this will create a temporary holder of datas
    History* head = NULL, * tail = NULL; // this serves as your tracker of head and tail

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

                historyCounter++;
            } while (true);
            break;
        case 2:
            HistoryFunctionalities(historyCounter, head, tail);
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
            << "\n"
            << "0. Exit\n"
            << "\n"
            << ":: ";
        std::cin >> choice;
        // the condition provided below states that if choice is lower than 0 or higher than 3 then its invalid
            // change it depends on the options
    } while (choice < 0 || choice > 2);

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

int HistoryMenu(int currentPage, int lastPage, int historyCounter)
{
    int choice = 0, instructionCounter = 0;
    std::string instructions = "";

    if (historyCounter)
    {
        // the logic here is that when in first page it will not show prev
        if (currentPage != 1)
            instructions.append(std::to_string(++instructionCounter) + ". Prev | ");

        // while here is that the next will not appear when the current page is the last page
        if (currentPage != lastPage)
            instructions.append(std::to_string(++instructionCounter) + ". Next | ");

        // while the following will always show but will adjust depends who is going to appear ahead
        instructions.append(std::to_string(++instructionCounter) + ". Update a History | ");
        instructions.append(std::to_string(++instructionCounter) + ". Delete a History | ");
        instructions.append(std::to_string(++instructionCounter) + ". Delete History | ");
    }

    do
    {
        std::cout
            << instructions << "0. Exit\n\n"
            << ":: ";
        std::cin >> choice;

        system("cls");

        if (!choice) return 0;
        // this changes depends on how many instructions is given
    } while (choice < 1 && choice > instructionCounter);

    system("cls");

    // this sets on different configuration of returns
        // set when their is not prev or next
    if (currentPage == 1 && currentPage == lastPage) return choice + 2;
    // set when their is only next
    else if (currentPage == 1) return ++choice;
    // set when their is only prev
    else if (currentPage == lastPage && choice != 1) return ++choice;
    // default
    else return choice;
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

// head are passed by value not reference so it will not be revised
void DisplayHistory(History* head, int currentPage, int lastPage)
{
    // Starting Index computes where to start in the index
    // counter will serve as the counter of how many displayed computations are present
    // i will be the counter for each present nodes
    int counter = 0, startingIndex = (currentPage - 1) * 5, i = 0;
    // the condition sets that it will be true when the head is NULL
    if (!head)
        std::cout << "-- No History Yet! --\n";
    else
    {
        std::cout
            << "Page " << currentPage << " of " << lastPage << "\n\n"
            << "History\n";

        // this part is the code for traversal until tail is meet
            // you can identify tail when the head is NULL
        while (head && counter < 5)
        {
            // this is used to display only the required ones
            if (startingIndex <= i)
            {
                head->data->Display();
                counter++;
            }
            // this will traverse
            head = head->next;

            // index
            i++;
        }

    }

    std::cout << "\n";
}

void ClearHistory(History*& head)
{
    History* temp = NULL, * current = head;

    // the condition sets that it will be true when the head is NULL
    if (!head)
        std::cout << "-- No History Yet! --\n\n";
    else
    {
        // this is also way of traversal but deletes every nodes
        while (temp)
        {
            // temp will hold the next node
            temp = current->next;
            // while the current node will be deleted
            delete current;
            current = temp;
        }

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

int HistoryFunctionalities(int& historyCounter, History*& head, History*& tail)
{
    History* currentNode = head;
    int currentPage = 1, lastPage = (historyCounter - 1) / 5 + 1;

    while (currentPage <= lastPage)
    {
        DisplayHistory(currentNode, currentPage, lastPage);

        switch (HistoryMenu(currentPage, lastPage, historyCounter))
        {
        case 1: // this will prev the page
            currentPage--;
            break;
        case 2: // this will next the page
            currentPage++;
            break;
        case 3:
            std::cout << "1";
            system("pause");
            return 0;
        case 4:
            std::cout << "2";
            system("pause");
            return 0;
        case 5:
            ClearHistory(head);
            tail = NULL;
            head = NULL;
            system("pause");
            return 0;
        case 0:
            return 0;
        }
    };

    return 0;
}

double Add(double val[], const int MAX)
{
    double total = 0;
    for (int i = 0; i < MAX; i++)
        total += val[i];
    return total;
}

double Subtract(double val[], const int MAX)
{
    double total = val[0];
    for (int i = 1; i < MAX; i++)
        total -= val[i];
    return total;
}

double Division(double val[], const int MAX)
{
    double total = val[0];
    for (int i = 1; i < MAX; i++)
        total /= val[i];
    return total;
}

double Multiplication(double val[], const int MAX)
{
    double total = val[0];
    for (int i = 1; i < MAX; i++)
        total *= val[i];
    return total;
}
