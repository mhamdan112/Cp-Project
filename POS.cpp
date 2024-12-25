#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <string>
using namespace std;

// Function to set console text and background color
    void setConsoleColor(int textColor, int backgroundColor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (backgroundColor << 2) | textColor);
}



// Function to display the main menu
void displayMenu() {
    system("cls");
    setConsoleColor(13, 2);
    cout << "\t     Welcome To General Store POS     " << endl;
    cout << "\t**************************************" << endl;
    setConsoleColor(14, 1);  
    cout << "\t\t1. Add Item." << endl;
    cout << "\t\t2. Print Bill." << endl;
    cout << "\t\t3. View Items in Bill." << endl;
    cout << "\t\t4. Update Item Quantity." << endl;
    cout << "\t\t5. Remove Item from Bill." << endl;
    cout << "\t\t6. Add Item to Inventory." << endl;
    cout << "\t\t7.View Inventory." << endl;
    cout << "\t\t8. Exit." << endl;
    cout << "\t\tEnter Choice: ";
    setConsoleColor(15, 1);
}

// Function to add an item to the bill
void addItemToFile() {
    string item;
    int rate, quant;

    setConsoleColor(15, 2);
    cout << "\tEnter Item Name: ";
    cin.ignore();
    getline(cin, item);

    cout << "\tEnter Rate Of Item: ";
    cin >> rate;

    cout << "\tEnter Quantity Of Item: ";
    cin >> quant;

    ofstream out("Bill.txt", ios::app);
    if (!out) {
        cout << "\tError: File Can't Open!" << endl;
    }
    else {
        out << item << " : " << rate << " : " << quant << endl;
        cout << "\tItem Added Successfully!" << endl;
    }
    out.close();
    Sleep(1000);
}



// Function to print the bill and calculate the total amount
void printBill() {
    system("cls");
    int count = 0;
    bool close = false;
    while (!close) {
        system("cls");
        int choice;
        setConsoleColor(3, 1);
        cout << "\t1. Add Bill." << endl;
        cout << "\t2. Close Session." << endl;
        cout << "\tEnter Choice: ";
        cin >> choice;

        if (choice == 1) {
            string item;
            int quant;
            cout << "\tEnter Item: ";
            cin.ignore();
            getline(cin, item);
            cout << "\tEnter Quantity: ";
            cin >> quant;

            ifstream in("Bill.txt");
            if (!in) {
                cout << "\tError: File Can't Be Opened!" << endl;
                return;
            }

            ofstream out("Bill Temp.txt");
            if (!out) {
                cout << "\tError: File Can't Be Created!" << endl;
                return;
            }


            string line;
            bool found = false;

            while (getline(in, line)) {
                stringstream ss(line);
                string itemName;
                int itemRate, itemQuant;
                char delimiter;
                ss >> itemName >> delimiter >> itemRate >> delimiter >> itemQuant;

                if (item == itemName) {
                    found = true;
                    if (quant <= itemQuant) {
                        int amount = itemRate * quant;
                        setConsoleColor(10, 1);
                        cout << "\tItem | Rate | Quantity | Amount" << endl;
                        cout << "\t" << itemName << "\t " << itemRate << "\t " << quant << "\t " << amount << endl;
                        int newQuant = itemQuant - quant;
                        itemQuant = newQuant;
                        count += amount;

                        out << itemName << " : " << itemRate << " : " << itemQuant << endl;
                    }
                    else {
                        cout << "\tSorry, " << item << " Ended!" << endl;
                    }
                }
                else {
                    out << line << endl;
                }
            }

            if (!found) {
                cout << "\tItem Not Available!" << endl;
            }

            out.close();
            in.close();
            remove("Bill.txt");
            rename("Bill Temp.txt", "Bill.txt");
        }
        else if (choice == 2) {
            close = true;
            cout << "\tCounting Total Bill" << endl;
        }
        Sleep(5000);
    }
    

    system("cls");
    setConsoleColor(15, 1);
    cout << endl << endl;
    cout << "\tTotal Bill ----------------- : " << count << endl << endl;
    cout << "\tThanks For Shopping!" << endl;
    Sleep(5000);
}

// Function to view the items already in the bill
void viewItemsInBill() {
    system("cls");
    ifstream in("Bill.txt");

    setConsoleColor(15, 1);
    if (!in) {
        cout << "\tError: No bill data found!" << endl;
    }
    else {
        cout <<"Items in Bill:" << endl;
        cout <<"Item   |Rate|Quantity " << endl;
        string line;
        while (getline(in, line)) {
            cout << line << endl;
        }
    }
    in.close();
    Sleep(5000);
}



// Function to update the quantity of an item in the bill
void updateItemQuantityInBill() {
    string item;
    int newQuant;
    bool found = false;

    setConsoleColor(15, 1);
    cout << "\tEnter Item to Update: ";
    cin.ignore();
    getline(cin, item);
    cout << "\tEnter New Quantity: ";
    cin >> newQuant;

    ifstream in("Bill.txt");
    if (!in) {
        cout << "\tError: File Can't Be Opened!" << endl;
        return;
    }

    ofstream out("Bill Temp.txt");
    if (!out) {
        cout << "\tError: File Can't Be Created!" << endl;
        return;
    }

    string line;
    while (getline(in, line)) {
        stringstream ss(line);
        string itemName;
        int itemRate, itemQuant;
        char delimiter;
        ss >> itemName >> delimiter >> itemRate >> delimiter >> itemQuant;

        if (item == itemName) {
            found = true;
            itemQuant = newQuant;
            out << itemName << " : " << itemRate << " : " << itemQuant << endl;
            cout << "\tItem Quantity Updated!" << endl;
        }
        else {
            out << line << endl;
        }
    }

    if (!found) {
        cout << "\tItem Not Found!" << endl;
    }

    in.close();
    out.close();
    remove("Bill.txt");
    rename("Bill Temp.txt", "Bill.txt");
    Sleep(3000);
}




// Function to remove an item from the bill
void removeItemFromBill() {
    string item;
    bool found = false;

    setConsoleColor(15, 1);
    cout << "\tEnter Item to Remove: ";
    cin.ignore();
    getline(cin, item);

    ifstream in("Bill.txt");
    if (!in) {
        cout << "\tError: File Can't Be Opened!" << endl;
        return;
    }

    ofstream out("Bill Temp.txt");
    if (!out) {
        cout << "\tError: File Can't Be Created!" << endl;
        return;
    }

    string line;
    while (getline(in, line)) {
        stringstream ss(line);
        string itemName;
        int itemRate, itemQuant;
        char delimiter;
        ss >> itemName >> delimiter >> itemRate >> delimiter >> itemQuant;

        if (item == itemName) {
            found = true;
            cout << "\tItem Removed!" << endl;
        }
        else {
            out << line << endl;
        }
    }

    if (!found) {
        cout << "\tItem Not Found!" << endl;
    }

    in.close();
    out.close();
    remove("Bill.txt");
    rename("Bill Temp.txt", "Bill.txt");
    Sleep(5000);
}
// function to add item in inventory
void additemtoInventory(){
	string item;
	int rate, quant;
	setConsoleColor(15, 2);
	cout<<"\tEnter Item name : ";
	cin.ignore();
	getline(cin,item);
	cout << "\tEnter Rate Of Item: ";
    cin >> rate;
    cout << "\tEnter Quantity Of Item: ";
    cin >> quant;
    ofstream out("Inventory.txt", ios::app);
    if(!out){
	
      cout<<"\tError! File cannot be opened!"<<endl;
  }
    else {
        out << item << " : " << rate << " : " << quant << endl;
        cout << "\tItem Added to Inventory Successfully!" << endl;
    }
    out.close();
    Sleep(1000);
    remove("Bill.txt");
    rename("Inventory Temp.txt", "Inventory.txt");
}
// function to view Item in inventory
void viewInventory() {
    system("cls");
    ifstream in("Inventory.txt");

    setConsoleColor(15, 1);
    if (!in) {
        cout << "\tError: No inventory data found!" << endl;
    }
    else {
        cout << "Items in Inventory:" << endl;
        cout << "Item   | Rate | Quantity" << endl;
        string line;
        while (getline(in, line)) {
            cout << line << endl;
        }
    }
    in.close();
    Sleep(5000);
}


int main() {
    bool exit = false;
    while (!exit) {
        displayMenu();

        int val;
        cin >> val;

        switch (val) {
        case 1:
            addItemToFile();
            break;
        case 2:
            printBill();
            break;
        case 3:
            viewItemsInBill();
            break;
        case 4:
            updateItemQuantityInBill();
            break;
        case 5:
            removeItemFromBill();
            break;
        case 6:
        	additemtoInventory();
        	break;
        case 7:
        	viewInventory();
        	break;
        case 8:
            system("cls");
            exit = true;
            setConsoleColor(5, 2);
            cout << "\tGood Luck have a Nice day!" << endl;
            Sleep(3000);
            break;
        default:
            cout << "\tInvalid Choice! Please try again." << endl;
            Sleep(5000);
            break;
        }
    }


    return 0;
}
