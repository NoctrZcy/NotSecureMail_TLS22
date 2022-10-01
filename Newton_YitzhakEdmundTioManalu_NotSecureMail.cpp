#include <iostream>
#include <stdlib.h>
#include <vector>
#include <cstring>
#include <cctype>

class SupportingFunctions {
    public : // Variables
        int *dumpInt;

    public : // Functions
        // Cons Dest
        SupportingFunctions() {}
        ~SupportingFunctions() {}

        // String To Char Conversion
        char* toChArr(std::string input) {
            unsigned int size = input.length();
            char* arrOfCh = new char[size + 1];
            std::strcpy(arrOfCh, input.c_str());

            return arrOfCh;
        }

        // Numeric Verifier
        bool isAllNum(std::string input) {
            bool allNum = true;
            char* chArr = this->toChArr(input);

            for (int i = 0; i < input.length(); i++) {
                if (!std::isdigit(chArr[i])) {
                    allNum = false;
                    break;
                }
            }

            return allNum;
        }

        // Dumping Input
        void dumpInput() {
            std::string dump = "";
            std::cin >> dump;
        }

        // Take Only Number Input
        void numInput(std::string option, int interval[2], bool* condition, int* output, bool* breakLoop, std::string breakArg) {
            if (option == breakArg) {
                *breakLoop = true;
                return;
            }
            
            if (this->isAllNum(option)) {
                int numOption = std::stoi(option);
                if (interval[0] <= numOption && numOption <= interval[1]) {
                    system("CLS");
                    *condition = false;
                    *output = numOption;
                }
            } else {
                *condition = true;
            }
        }

        // Take Sentence and Paragraph Inputs
        void getlineString(std::string *address) {
            if (std::cin.peek() == '\n')
                std::cin.ignore();
            
            std::getline(std::cin, *address);
        }
}; typedef SupportingFunctions Supp;

struct Mail { // Mail data structure to contain a mail's informations
    
    std::string sender;
    std::string title;
    std::string message;

    Mail(std::string sender, std::string title, std::string message) {
        this->sender = sender;
        this->title = title;
        this->message = message;
    }
}; typedef struct Mail Mail;

class Account { // Account object to contain an account with the sent and received emails
    private : // Variables
        Supp Supp; // Installing Supporting Function
        std::vector<Account*> accountDatabase;
        unsigned int index;
        std::vector<Mail> *inbox;
        std::vector<Mail> *outbox;
        std::string name;
        std::string password;

    public :  // Supporting Functions
        // Cons Dest
        Account(std::vector<Account*> parent) {
            this->accountDatabase = parent;
            this->index = this->accountDatabase.size() - 1;
            this->inbox = new std::vector<Mail>;
            this->outbox = new std::vector<Mail>;
            this->name  = "Annonymous";
            this->password  = "Annonymous";
        }

        ~Account() {
            delete this->inbox;
        }

        void findAccount(std::string username, int* accIndex, bool* found) {
            *found = false;
            for (unsigned int i = 0; i < this->accountDatabase.size(); i++) {
                if (this->accountDatabase[i]->name == username) {
                    *accIndex = this->accountDatabase[i]->index;

                    // Debug
                    // std::cout << "[Dbg] Account Index : " << accIndex << std::endl;

                    *found = true;
                    break;
                }
            }
        }

    public :  // Functions
        // Main Menu
        int mainMenu() { // App Opening
            //this->mainAcc(); //DEL THIS !!
            std::string option = "";
            int response = -1;

            bool inpValid = false;
            bool wrongInput = false;

            int interval[2] = {1, 3};

            while (!inpValid) {
                system("CLS");
                std::cout << "[App] Welcome to NotSecureMail!" << std::endl;
                std::cout << "[App] Please choose the following options :" << std::endl;
                std::cout << "[App] 1) Login" << std::endl;
                std::cout << "[App] 2) Register" << std::endl;
                std::cout << "[App] 3) Quit" << std::endl;

                if (wrongInput)
                    std::cout << std::endl << "[App] Input Invalid! Please Try Again!" << std::endl << std::endl;

                // Debug
                // std::cout << "[Dbg] Input is : " << option << std::endl;

                std::cout << "[App] Input : ";
                std::cin >> option;

                Supp.numInput(option, interval, &wrongInput, &response, NULL, "");

                if (!wrongInput)
                    return response;
            }

            // Debug
            // std::cout << "[Dbg] Input is : " << option << std::endl;
        }

        // Login
        int login() {
            std::string username = "";
            std::string password = "";
            int accIndex = -1;

            std::cout << "[Log] You're currently logging in!" << std::endl;
        
            while (true) {
                std::cout << "[Log] Please input the username of your email! (Input \"-1\" to go back)" << std::endl;
                std::cout << "[Log] Username : ";
                
                std::cin >> username;

                if (username == "-1")
                    return -1;

                bool found = false;
                this->findAccount(username, &accIndex, &found);

                if (found) {
                    // Debug
                    // std::cout << "[Dbg] Account Name : " << this->accountDatabase[accIndex]->name << std::endl;
                    // std::cout << "[Dbg] Account Pass : " << this->accountDatabase[accIndex]->password << std::endl;
                    
                    bool passTrue = false;
                    bool failAttempt = false;
                    while (!passTrue) {
                        system("CLS");
                        std::cout << "[Log] Hi, " << username << "! Please input the password of your account! (Input \"-1\" to go back)" << std::endl;

                        if (failAttempt)
                            std::cout << std::endl << "[Log] Password is not correct!" << std::endl << std::endl;

                        std::cout << "[Log] Password : ";
                        std::cin >> password;

                        if (password == "-1") {
                            system("CLS");
                            break;
                        }
                        
                        if (this->accountDatabase[accIndex]->password == password) {
                            system("CLS");

                            std::cout << "[Log] Login success!" << std::endl;
                            passTrue = true;
                            std::cout << "[Log] Please input anything to continue!" << std::endl;
                            std::cout << "[Log] Input : ";
                            Supp.dumpInput();

                            return accIndex;
                        } else {
                            failAttempt = true;
                        }
                    }
                } else {
                    system("CLS");
                    std::cout << "[Log] Hi, " << username << "! Your username doesn't exist! Please try again." << std::endl;
                }
            }
        }

        // Register
        void regAccount() { // Registering username & password
            std::string username = "";
            std::string password = "";
            Account *newAcc = new Account(this->accountDatabase);

            bool found = false;
            do {
                std::cout << "[Reg] You're currently registering a new account! (Input \"-1\" to go back)" << std::endl;
                std::cout << "[Reg] Please create a username for your email!" << std::endl;
                
                if (found)
                    std::cout << std::endl << "[Reg] Username is already available! Please make another username!" << std::endl << std::endl;

                std::cout << "[Reg] Username : ";
                
                std::cin >> username;

                if (username == "-1")
                    return;

                findAccount(username, Supp.dumpInt, &found);

                system("CLS");
            } while (found);

            newAcc->name = username;

            system("CLS");
            std::cout << "[Reg] Hi, " << username << "! Please create a password for your account! (Input \"-1\" to go back)" << std::endl;
            std::cout << "[Reg] Password : ";

            std::cin >> password;
            if (password == "-1")
                return;

            newAcc->password = password;

            unsigned int index = this->accountDatabase.size();
            newAcc->index = index;

            this->accountDatabase.push_back(newAcc);

            system("CLS");
            std::cout << "[Reg] Your account is succesfully created! Please login to access your account." << std::endl;
            std::cout << "[Reg] Please input anything to go back!" << std::endl;
            std::cout << "[Reg] Input : ";
            Supp.dumpInput();

            // Debug
            // Account *accPtr = this->accountDatabase[index];
            // accPtr->inputMail("Unknown", "Testt", "This");
            // accPtr->inputMail("Unknown1", "Testt", "This");
            // accPtr->inputMail("Unknown2", "Cek", "This");

            // Debug
            // std::cout << "[Dbg] Account username : " << newAcc->name << std::endl;
            // std::cout << "[Dbg] Account password : " << newAcc->password << std::endl;
        }

        // Main Account
        void mainAcc(unsigned int accIndex) {
            Account* loggedAcc = this->accountDatabase[accIndex];
            std::string option = "";
            int response = -1;

            bool loggedIn = true;
            bool wrongInput = false;

            int interval[2] = {1, 4};

            while(loggedIn) {
                system("CLS");

                // Debug
                // std::cout << "[Dbg] Index : " << accIndex << std::endl;

                std::cout << "[Acc] Hi, " << loggedAcc->name << "!" << std::endl;
                std::cout << "[Acc] Let me know what you would like to do!" << std::endl;
                std::cout << "[Acc] Options :"       << std::endl;
                std::cout << "[Acc] 1) Check Inbox"  << std::endl;
                std::cout << "[Acc] 2) Check Outbox" << std::endl;
                std::cout << "[Acc] 3) Send Email"   << std::endl;
                std::cout << "[Acc] 4) Log Out"      << std::endl;

                std::cout << "[Acc] Option : ";
                
                //this->mainMenu(); // DEL THIS !!
                if (wrongInput)
                    std::cout << std::endl << "[App] Input Invalid! Please Try Again!" << std::endl << std::endl;

                std::cin >> option;
                
                Supp.numInput(option, interval, &wrongInput, &response, NULL, "");

                if (!wrongInput) {
                    switch(response) {
                        case 1 :
                            this->mainAccCheckInbox(accIndex);
                            break;
                        case 2 :
                            this->mainAccCheckOutbox(accIndex);
                            break;
                        case 3 :
                            this->mainAccSendEmail(accIndex);
                            break;
                        case 4 :
                            loggedIn = false;
                            break;
                        default :
                            std::cout << "[Sys] Main Account Menu Input Error!" << std::endl;
                    }
                }
            }
        }

        void mainAccCheckInbox(int accIndex) {
            system("CLS");

            Mail* importInbox;
            std::string option = "";

            bool wrongInput = false;
            int output = -1;

            Account *accPtr = this->accountDatabase[accIndex];
            std::vector<Mail> *inboxPtr = accPtr->inbox;
            unsigned int size = inboxPtr->size();

            // Debug
            // std::cout << "[Dbg] Size : " << size << std::endl;

            if (size == 0) {
                std::cout << "[Email] Your inbox is empty!" << std::endl;
                std::cout << "[Email] Please input anything to go back!" << std::endl;
                std::cout << "[Email] Input : ";
                Supp.dumpInput();
            } else {
                bool wrongInput = false;
                bool breakLoop = false;
                bool continueLoop = false;

                do {
                    output = -1;
                    if (continueLoop)   // Break continue-loop from opening emails
                        continueLoop = false;

                    std::cout << "[Email] Here's your email(s) :" << std::endl << std::endl;

                    for (int index = 0; index < size; index++) {
                        importInbox = &(inboxPtr->at(index));
                        std::cout << "[" << importInbox->sender << "] " << importInbox->title << std::endl;
                    }

                    int interval[2] = {1, (int) size};
                    std::cout << std::endl;
                    std::cout << "[Email] Please select the desired email! (input \"-1\" to go back!)" << std::endl;

                    if (wrongInput)
                        std::cout << std::endl << "[Email] Input Invalid!" << std::endl << std::endl;

                    std::cout << "[Email] Input : ";

                    std::cin >> option;

                    Supp.numInput(option, interval, &wrongInput, &output, &breakLoop, "-1");

                    if (breakLoop)
                        break;

                    if (!wrongInput) {
                        accPtr->getMail(output-1, "INBOX");
                
                        std::cout << std::endl << "[Email] Enter anything to go back : ";
                        Supp.dumpInput();

                        continueLoop = true; // To Continue the Loop
                    }

                    system("CLS");
                } while (wrongInput || continueLoop);
            }
        };

        void mainAccCheckOutbox(int accIndex) {
            system("CLS");

            Mail* importOutbox;
            std::string option = "";

            bool wrongInput = false;
            int output = -1;

            Account *accPtr = this->accountDatabase[accIndex];
            std::vector<Mail> *outboxPtr = accPtr->outbox;
            unsigned int size = outboxPtr->size();
            
            // Debug
            // std::cout << "[Dbg] Size : " << size << std::endl;

            if (size == 0) {
                std::cout << "[Email] Your outbox is empty!" << std::endl;
                std::cout << "[Email] Please input anything to go back!" << std::endl;
                std::cout << "[Email] Input : ";
                Supp.dumpInput();
            } else {
                bool wrongInput = false;
                bool breakLoop = false;
                bool continueLoop = false;

                do {
                    output = -1;
                    if (continueLoop)   // Break continue-loop from opening emails
                        continueLoop = false;

                    std::cout << "[Email] Here's your email(s) :" << std::endl << std::endl;

                    for (int index = 0; index < size; index++) {
                        importOutbox = &(outboxPtr->at(index));
                        std::cout << "[" << importOutbox->sender << "] " << importOutbox->title << std::endl;
                    }

                    int interval[2] = {1, (int) size};
                    std::cout << std::endl;
                    std::cout << "[Email] Please select the desired email! (input \"-1\" to go back!)" << std::endl;

                    if (wrongInput)
                        std::cout << std::endl << "[Email] Input Invalid!" << std::endl << std::endl;

                    std::cout << "[Email] Input : ";

                    std::cin >> option;

                    Supp.numInput(option, interval, &wrongInput, &output, &breakLoop, "-1");

                    if (breakLoop)
                        break;

                    if (!wrongInput) {
                        accPtr->getMail(output-1, "OUTBOX");
                
                        std::cout << std::endl << "[Email] Enter anything to go back : ";
                        Supp.dumpInput();

                        continueLoop = true; // To Continue the Loop
                    }

                    system("CLS");
                } while (wrongInput || continueLoop);
            }
        };

        void mainAccSendEmail(int accIndexC) {
            system("CLS");

            std::string username = "";
            std::string title = "";
            std::string desc = "";

            Account *accPtr = this->accountDatabase[accIndexC];

            int accIndex = -1;
            bool found = false;

            while (true) {
                std::cout << "[Email] Please input the recipient (\"-1\" to cancel) : ";
                std::cin >> username;

                if (username == "-1")
                    return;

                this->findAccount(username, &accIndex, &found);

                if (found)
                    break;

                system("CLS");
                std::cout << "[Email] Account not found! Please type another existing account!" << std::endl << std::endl;
            }

            std::cout << "[Email] Please input the title  (\"-1\" to cancel) : ";
            Supp.getlineString(&title);
            if (title == "-1")
                return;

            std::cout << "[Email] Please input the e-mail (\"-1\" to cancel) : ";
            Supp.getlineString(&desc);
            if (desc == "-1")
                return;

            // Debug
            // int beforeMail = this->accountDatabase[accIndex]->inbox->size();            
            
            this->accountDatabase[accIndexC]->inputMail(this->accountDatabase[accIndex], title, desc);

            system("CLS");

            // Debug
            // std::cout << "[Dbg] Index : " << accIndex << std::endl;
            // std::cout << "[Dbg] Mails from " << beforeMail << " to " << this->accountDatabase[accIndex]->inbox->size() << std::endl;

            std::cout << "[Email] The mail has been sent!" << std::endl;
            std::cout << "[Email] Enter anything to go back : ";
        };

        // Profiling
        void setName(std::string newName) {
            std::string tempName = this->name;            
            this->name = newName;
            std::cout << "[Profile] Name is changed from " << tempName << " to " << newName << "!" << std::endl;
        }

        void setPass(std::string newPass) {
            this->password = newPass;
            std::cout << "[Profile] Password has been changed!" << std::endl;
        }

        // Emailing
        void getMail(unsigned int index, std::string type) {
            bool withAp = true;
            if (this->name[this->name.length() - 1] == 's')
                withAp = false;

            if (type == "INBOX")
                if (index >= this->inbox->size()) {
                    system("CLS");
                    
                    std::cout << "[Email] Index is out of bounds! We can't show you any message!";
                } else {
                    system("CLS");
                    
                    std::cout << "[" << this->name;
                    if (withAp)
                        std::cout << "'s ";
                    else
                        std::cout << "\' ";

                    std::cout << "Email]" << "\n["  << this->inbox->at(index).title   << "]" << std::endl;
                    std::cout << "From : "          << this->inbox->at(index).sender  << std::endl;
                    std::cout << "Message : "       << this->inbox->at(index).message << std::endl;
                }
            else if (type == "OUTBOX")
                if (index >= this->outbox->size()) {
                    system("CLS");
                    
                    std::cout << "[Email] Index is out of bounds! We can't show you any message!";
                } else {
                    system("CLS");
                    
                    std::cout << "[" << this->name;
                    if (withAp)
                        std::cout << "'s ";
                    else
                        std::cout << "\' ";

                    std::cout << "Email]" << "\n["  << this->outbox->at(index).title   << "]" << std::endl;
                    std::cout << "To : "            << this->outbox->at(index).sender  << std::endl;
                    std::cout << "Message : "       << this->outbox->at(index).message << std::endl;
                }
        }

        void inputMail(Account* recipient, std::string title, std::string message) {
            recipient->inbox->push_back(Mail(this->name, title, message));
            this->outbox->push_back(Mail(recipient->name, title, message));
        }
};

int main() {
    std::vector<Account*> accountList;
    Account *newAcc = new Account(accountList);
    accountList.push_back(newAcc);

    // accountList[0]->regAccount();
    // accountList[0]->setName("");
    // accountList[0]->inputMail("Anon", "New Title", "Hello World!");
    // accountList[0]->getMail(0);
    int option = -1;
    int accIndex = -1;

    while (accIndex < 0) {
        option = accountList[0]->mainMenu();

        switch (option) {
            case 1 :
                accIndex = accountList[0]->login();
                break;
            case 2 :
                accountList[0]->regAccount();
                break;
            case 3 :
                std::cout << "[App] Thanks for using NotSecureMail!";
                return 0;
            default :
                std::cout << "[Sys] Main Menu Input Error!" << std::endl;
        }

        if (accIndex >= 0) {
            accountList[0]->mainAcc(accIndex);
        }

        // Re-loop
        accIndex = -1;
    }

    return 0;
}