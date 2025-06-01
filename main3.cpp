// check elgible list for loan
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
using namespace std;

class Account {
    int accountNumber;
    char name[50];
    char type;
    int deposit;

public:
    void createAccount();
    void showAccount() const;
    void modify();
    void depositAmount(int);
    void withdrawAmount(int);
    void report() const;
    int retAccountNumber() const;
    int retDeposit() const;
    char retType() const;
    const char* retName() const;
};

void Account::createAccount() {
    cout << "\nEnter The account No. : ";
    cin >> accountNumber;
    cout << "\n\nEnter The Name of The account Holder : ";
    cin.ignore();
    cin.getline(name, 50);
    cout << "\nEnter Type of The account (C/S) : ";
    cin >> type;
    type = toupper(type);
    cout << "\nEnter The Initial amount (>=500 for Saving and >=1000 for Current ): ";
    cin >> deposit;
    cout << "\n\n\nAccount Created..";
}

void Account::showAccount() const {
    cout << "\nAccount No. : " << accountNumber;
    cout << "\nAccount Holder Name : " << name;
    cout << "\nType of Account : " << type;
    cout << "\nBalance amount : " << deposit;
}

void Account::modify() {
    cout << "\nAccount No. : " << accountNumber;
    cout << "\nModify Account Holder Name : ";
    cin.ignore();
    cin.getline(name, 50);
    cout << "\nModify Type of Account : ";
    cin >> type;
    type = toupper(type);
    cout << "\nModify Balance amount : ";
    cin >> deposit;
}

void Account::depositAmount(int x) {
    deposit += x;
}

void Account::withdrawAmount(int x) {
    deposit -= x;
}

void Account::report() const {
    cout << accountNumber << setw(10) << " " << name << setw(10)
         << " " << type << setw(6) << deposit << endl;
}

int Account::retAccountNumber() const {
    return accountNumber;
}

int Account::retDeposit() const {
    return deposit;
}

char Account::retType() const {
    return type;
}

const char* Account::retName() const {
    return name;
}

// Function declarations
void writeAccount();
void displayAccount(int);
void modifyAccount(int);
void deleteAccount(int);
void displayAll();
void depositWithdraw(int, int);
void searchAccountByName();
void checkLoanEligibility(int);
void intro();

int main() {
    char ch;
    int num;
    intro();
    do {
        system("cls");
        cout << "\n\n\n\tMAIN MENU";
        cout << "\n\n\t01. NEW ACCOUNT";
        cout << "\n\n\t02. DEPOSIT AMOUNT";
        cout << "\n\n\t03. WITHDRAW AMOUNT";
        cout << "\n\n\t04. BALANCE ENQUIRY";
        cout << "\n\n\t05. ALL ACCOUNT HOLDER LIST";
        cout << "\n\n\t06. CLOSE AN ACCOUNT";
        cout << "\n\n\t07. MODIFY AN ACCOUNT";
        cout << "\n\n\t08. EXIT";
        cout << "\n\n\t09. SEARCH ACCOUNT BY NAME";
        cout << "\n\n\t10. CHECK LOAN ELIGIBILITY";
        cout << "\n\n\tSelect Your Option (1-10): ";
        cin >> ch;

        switch (ch) {
        case '1':
            writeAccount();
            break;
        case '2':
            cout << "\n\n\tEnter The account No. : "; cin >> num;
            depositWithdraw(num, 1);
            break;
        case '3':
            cout << "\n\n\tEnter The account No. : "; cin >> num;
            depositWithdraw(num, 2);
            break;
        case '4':
            cout << "\n\n\tEnter The account No. : "; cin >> num;
            displayAccount(num);
            break;
        case '5':
            displayAll();
            break;
        case '6':
            cout << "\n\n\tEnter The account No. : "; cin >> num;
            deleteAccount(num);
            break;
        case '7':
            cout << "\n\n\tEnter The account No. : "; cin >> num;
            modifyAccount(num);
            break;
        case '8':
            cout << "\n\n\tThanks for using bank management system!";
            break;
        case '9':
            searchAccountByName();
            break;
        case '10':
            cout << "\n\n\tEnter The account No. : "; cin >> num;
            checkLoanEligibility(num);
            break;
        default:
            cout << "\a";
        }
        cin.ignore();
        cin.get();
    } while (ch != '8');
    return 0;
}

void writeAccount() {
    Account ac;
    ofstream outFile;
    outFile.open("account.dat", ios::binary | ios::app);
    ac.createAccount();
    outFile.write(reinterpret_cast<char *> (&ac), sizeof(Account));
    outFile.close();
}

void displayAccount(int n) {
    Account ac;
    bool flag = false;
    ifstream inFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile) {
        cout << "File could not be open !! Press any Key...";
        return;
    }

    while (inFile.read(reinterpret_cast<char *> (&ac), sizeof(Account))) {
        if (ac.retAccountNumber() == n) {
            ac.showAccount();
            flag = true;
        }
    }
    inFile.close();
    if (!flag)
        cout << "\n\nAccount number does not exist";
}

void modifyAccount(int n) {
    bool found = false;
    Account ac;
    fstream File;
    File.open("account.dat", ios::binary | ios::in | ios::out);
    if (!File) {
        cout << "File could not be open !! Press any Key...";
        return;
    }

    while (!File.eof() && found == false) {
        int pos = File.tellg();
        File.read(reinterpret_cast<char *> (&ac), sizeof(Account));
        if (ac.retAccountNumber() == n) {
            ac.showAccount();
            cout << "\n\nEnter The New Details of account" << endl;
            ac.modify();
            File.seekp(pos);
            File.write(reinterpret_cast<char *> (&ac), sizeof(Account));
            cout << "\n\n\t Record Updated";
            found = true;
        }
    }
    File.close();
    if (!found)
        cout << "\n\n Record Not Found ";
}

void deleteAccount(int n) {
    Account ac;
    ifstream inFile;
    ofstream outFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile) {
        cout << "File could not be open !! Press any Key...";
        return;
    }
    outFile.open("Temp.dat", ios::binary);
    inFile.seekg(0, ios::beg);
    while (inFile.read(reinterpret_cast<char *> (&ac), sizeof(Account))) {
        if (ac.retAccountNumber() != n) {
            outFile.write(reinterpret_cast<char *> (&ac), sizeof(Account));
        }
    }
    inFile.close();
    outFile.close();
    remove("account.dat");
    rename("Temp.dat", "account.dat");
    cout << "\n\n\tRecord Deleted ..";
}

void displayAll() {
    Account ac;
    ifstream inFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile) {
        cout << "File could not be open !! Press any Key...";
        return;
    }
    cout << "\n\n\t\tACCOUNT HOLDER LIST\n\n";
    cout << "====================================================\n";
    cout << "A/c no.      NAME           Type  Balance\n";
    cout << "====================================================\n";
    while (inFile.read(reinterpret_cast<char *> (&ac), sizeof(Account))) {
        ac.report();
    }
    inFile.close();
}

void depositWithdraw(int n, int option) {
    int amt;
    bool found = false;
    Account ac;
    fstream File;
    File.open("account.dat", ios::binary | ios::in | ios::out);
    if (!File) {
        cout << "File could not be open !! Press any Key...";
        return;
    }

    while (!File.eof() && found == false) {
        int pos = File.tellg();
        File.read(reinterpret_cast<char *> (&ac), sizeof(Account));
        if (ac.retAccountNumber() == n) {
            ac.showAccount();
            if (option == 1) {
                cout << "\n\n\tTO DEPOSIT AMOUNT ";
                cout << "\n\nEnter The amount to be deposited: ";
                cin >> amt;
                ac.depositAmount(amt);
            }
            if (option == 2) {
                cout << "\n\n\tTO WITHDRAW AMOUNT ";
                cout << "\n\nEnter The amount to be withdrawn: ";
                cin >> amt;
                int bal = ac.retDeposit() - amt;
                if ((bal < 500 && ac.retType() == 'S') || (bal < 1000 && ac.retType() == 'C'))
                    cout << "Insufficient balance";
                else
                    ac.withdrawAmount(amt);
            }
            File.seekp(pos);
            File.write(reinterpret_cast<char *> (&ac), sizeof(Account));
            cout << "\n\n\t Record Updated";
            found = true;
        }
    }
    File.close();
    if (!found)
        cout << "\n\n Record Not Found ";
}

void searchAccountByName() {
    char searchName[50];
    Account ac;
    bool found = false;
    ifstream inFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile) {
        cout << "File could not be open !! Press any Key...";
        return;
    }

    cout << "\n\nEnter the name to search: ";
    cin.ignore();
    cin.getline(searchName, 50);

    while (inFile.read(reinterpret_cast<char*>(&ac), sizeof(Account))) {
        if (stricmp(ac.retName(), searchName) == 0) {
            ac.showAccount();
            found = true;
        }
    }
    if (!found)
        cout << "\n\nNo account found with that name!";
    inFile.close();
}

void checkLoanEligibility(int n) {
    Account ac;
    bool found = false;
    ifstream inFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile) {
        cout << "File could not be open !! Press any Key...";
        return;
    }

    while (inFile.read(reinterpret_cast<char*>(&ac), sizeof(Account))) {
        if (ac.retAccountNumber() == n) {
            found = true;
            cout << "\n\nChecking Loan Eligibility for:\n";
            ac.showAccount();

            int balance = ac.retDeposit();
            char type = ac.retType();

            if ((type == 'S' && balance >= 10000) || (type == 'C' && balance >= 20000)) {
                cout << "\n\nStatus: ✅ Eligible for Loan.";
            } else {
                cout << "\n\nStatus: ❌ Not Eligible for Loan.";
                if (type == 'S')
                    cout << "\nRequirement: Minimum ₹10,000 in Savings Account.";
                else
                    cout << "\nRequirement: Minimum ₹20,000 in Current Account.";
            }
            break;
        }
    }
    inFile.close();
    if (!found)
        cout << "\n\nAccount number does not exist.";
}

void intro() {
    cout << "\n\n\n\t  BANK";
    cout << "\n\n\tMANAGEMENT";
    cout << "\n\n\t  SYSTEM";
    cout << "\n\n\n\nMADE BY : ChatGPT Example";
    cout << "\n\nSCHOOL : Demo School\n";
    cin.get();
}

