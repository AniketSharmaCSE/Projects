#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main_exit;

struct date {
    int month, day, year;
};

struct account {
    char name[60];
    int acc_no;
    int pin;
    char address[60];
    char aadharNum[15];
    double phone;
    char acc_type[10];
    float amt;
    struct date dob;
    struct date deposit;
    struct date withdraw;
};

void menu();
void new_acc();
void view_list();
void edit();
void transact();
void erase();
void see();
float interest(float t, float amount, int rate);
void fordelay(int j);
void close();

int main() {
    int i;
    printf("\n\n\n\t\t\t\t  Welcome to Bank Management System\n\n\t\t\t\t\t Loading ");

    for (i = 0; i <= 6; i++) {
        fordelay(100000000);
        printf(". ");
    }

    system("cls");
    menu();

    return 0;
}

void menu() {
    int choice;
    system("cls");
    system("color 7");
    printf("\n\n\t\t\t       BANKING MANAGEMENT SYSTEM");
    printf("\n\n\n\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2 WELCOME TO THE MAIN MENU \xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    printf("\n\n\t\t[1] Create a new account\n\t\t[2] Update information of existing account\n\t\t[3] Transactions\n\t\t[4] Check the details of existing account\n\t\t[5] Remove existing account\n\t\t[6] View customer's list\n\t\t[7] Exit\n\n\n\t\t Enter your choice:");
    scanf("%d", &choice);

    system("cls");
    switch (choice) {
        case 1:
            new_acc();
            break;
        case 2:
            edit();
            break;
        case 3:
            transact();
            break;
        case 4:
            see();
            break;
        case 5:
            erase();
            break;
        case 6:
            view_list();
            break;
        case 7:
            close();
            break;
    }
}

void new_acc() {
    struct account add;
    FILE *ptr;

    ptr = fopen("record.dat", "a+");
    // Input data for the new account
    printf("\t\t\t==== ADD RECORD  ====\n");
    printf("\nEnter today's date(mm/dd/yyyy): ");
    scanf("%d/%d/%d", &add.deposit.month, &add.deposit.day, &add.deposit.year);
    printf("\nEnter the account number: ");
    scanf("%d", &add.acc_no);
    // Add validation to check if the account number already exists
    // If it exists, prompt the user to enter a different account number
    // Otherwise, proceed with adding the account details
    printf("\nEnter the name: ");
    scanf("%s", add.name);
    printf("\nEnter the date of birth(mm/dd/yyyy): ");
    scanf("%d/%d/%d", &add.dob.month, &add.dob.day, &add.dob.year);
    printf("\nEnter the address: ");
    scanf("%s", add.address);
    printf("\nEnter the Aadhaar number: ");
    scanf("%s", add.aadharNum);
    printf("\nEnter the phone number: ");
    scanf("%lf", &add.phone);
    printf("\nEnter the amount to deposit: $");
    scanf("%f", &add.amt);
    printf("\nEnter the new PIN number for the user: ");
    scanf("%d", &add.pin);
    printf("\nType of account:\n\t#Saving\n\t#Current\n\nEnter your choice: ");
    scanf("%s", add.acc_type);
    // Write account details to file
    fprintf(ptr, "%d %s %d/%d/%d %d %s %s %.0lf %s %.2f %d/%d/%d\n",
            add.acc_no, add.name, add.dob.month, add.dob.day, add.dob.year,
            add.pin, add.address, add.aadharNum, add.phone, add.acc_type,
            add.amt, add.deposit.month, add.deposit.day, add.deposit.year);
    fclose(ptr);
    printf("\nAccount created successfully!\n");

    // Prompt user to return to main menu or exit
    printf("\n\nEnter 1 to go to the main menu and 0 to exit: ");
    scanf("%d", &main_exit);
    if (main_exit == 1)
        menu();
    else
        close();
}

void view_list() {
    struct account view;
    FILE *ptr;

    ptr = fopen("record.dat", "r");
    if (ptr == NULL) {
        printf("\nError opening file!");
        menu();
    }
    printf("\nACC. NO.\tNAME\t\tADDRESS\t\tPHONE\t\tACCOUNT TYPE\t\tAMOUNT\n");

    while (fscanf(ptr, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d",
                  &view.acc_no, view.name, &view.dob.month, &view.dob.day,
                  &view.dob.year, &view.pin, view.address, view.aadharNum,
                  &view.phone, view.acc_type, &view.amt,
                  &view.deposit.month, &view.deposit.day,
                  &view.deposit.year) != EOF) {
        printf("\n%6d\t %10s\t\t%10s\t\t%.0lf\t\t%s\t\t%.2f", view.acc_no,
               view.name, view.address, view.phone, view.acc_type, view.amt);
    }
    fclose(ptr);
    // Prompt user to return to main menu or exit
    printf("\n\nEnter 1 to go to the main menu and 0 to exit: ");
    scanf("%d", &main_exit);
    if (main_exit == 1)
        menu();
    else
        close();
}

void edit() {
    int choice, test = 0;
    FILE *ptr;
    struct account account;

    ptr = fopen("record.dat", "r+");
    if (ptr == NULL) {
        printf("\nError opening file!");
        menu();
    }

    printf("\nEnter the account number you want to update: ");
    scanf("%d", &choice);
    while (fscanf(ptr, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d",
                  &account.acc_no, account.name, &account.dob.month,
                  &account.dob.day, &account.dob.year, &account.pin,
                  account.address, account.aadharNum, &account.phone,
                  account.acc_type, &account.amt, &account.deposit.month,
                  &account.deposit.day, &account.deposit.year) != EOF) {
        if (account.acc_no == choice) {
            printf("\nAccount found! Enter new details:\n");
            printf("\nEnter the new name: ");
            scanf("%s", account.name);
            printf("\nEnter the new address: ");
            scanf("%s", account.address);
            printf("\nEnter the new phone number: ");
            scanf("%lf", &account.phone);
            fseek(ptr, -sizeof(account), SEEK_CUR);
            fprintf(ptr, "%d %s %d/%d/%d %d %s %s %.0lf %s %.2f %d/%d/%d\n",
                    account.acc_no, account.name, account.dob.month,
                    account.dob.day, account.dob.year, account.pin,
                    account.address, account.aadharNum, account.phone,
                    account.acc_type, account.amt, account.deposit.month,
                    account.deposit.day, account.deposit.year);
            printf("\nAccount updated successfully!");
            test = 1;
            break;
        }
    }
    fclose(ptr);
    if (test == 0) {
        printf("\nAccount not found!");
    }

    // Prompt user to return to main menu or exit
    printf("\n\nEnter 1 to go to the main menu and 0 to exit: ");
    scanf("%d", &main_exit);
    if (main_exit == 1)
        menu();
    else
        close();
}

void transact() {
    int choice, test = 0;
    FILE *ptr;
    struct account account;

    ptr = fopen("record.dat", "r+");
    if (ptr == NULL) {
        printf("\nError opening file!");
        menu();
    }

    printf("\nEnter the account number for transaction: ");
    scanf("%d", &choice);
    while (fscanf(ptr, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d",
                  &account.acc_no, account.name, &account.dob.month,
                  &account.dob.day, &account.dob.year, &account.pin,
                  account.address, account.aadharNum, &account.phone,
                  account.acc_type, &account.amt, &account.deposit.month,
                  &account.deposit.day, &account.deposit.year) != EOF) {
        if (account.acc_no == choice) {
            printf("\nAccount found! What do you want to do?\n");
            printf("1. Deposit\n2. Withdraw\n\nEnter your choice: ");
            scanf("%d", &choice);

            if (choice == 1) {
                float deposit_amount;
                printf("\nEnter the amount you want to deposit: $");
                scanf("%f", &deposit_amount);
                account.amt += deposit_amount;
                fseek(ptr, -sizeof(account), SEEK_CUR);
                fprintf(ptr, "%d %s %d/%d/%d %d %s %s %.0lf %s %.2f %d/%d/%d\n",
                        account.acc_no, account.name, account.dob.month,
                        account.dob.day, account.dob.year, account.pin,
                        account.address, account.aadharNum, account.phone,
                        account.acc_type, account.amt, account.deposit.month,
                        account.deposit.day, account.deposit.year);
                printf("\nDeposit successful!");
            } else if (choice == 2) {
                float withdraw_amount;
                printf("\nEnter the amount you want to withdraw: $");
                scanf("%f", &withdraw_amount);
                if (withdraw_amount <= account.amt) {
                    account.amt -= withdraw_amount;
                    fseek(ptr, -sizeof(account), SEEK_CUR);
                    fprintf(ptr, "%d %s %d/%d/%d %d %s %s %.0lf %s %.2f %d/%d/%d\n",
                            account.acc_no, account.name, account.dob.month,
                            account.dob.day, account.dob.year, account.pin,
                            account.address, account.aadharNum, account.phone,
                            account.acc_type, account.amt, account.deposit.month,
                            account.deposit.day, account.deposit.year);
                    printf("\nWithdrawal successful!");
                } else {
                    printf("\nInsufficient balance!");
                }
            } else {
                printf("\nInvalid choice!");
            }

            test = 1;
            break;
        }
    }
    fclose(ptr);
    if (test == 0) {
        printf("\nAccount not found!");
    }

    // Prompt user to return to main menu or exit
    printf("\n\nEnter 1 to go to the main menu and 0 to exit: ");
    scanf("%d", &main_exit);
    if (main_exit == 1)
        menu();
    else
        close();
}



float interest(float t, float amount, int rate) {
    float SI;
    SI = (rate * t * amount) / 100.0;
    return (SI);
}

void fordelay(int j) {
    int i, k;
    for (i = 0; i < j; i++)
        k = i;
}

void close() {
    printf("\nExiting...\n");
}
void erase() {
    int account_no;
    FILE *old, *newrec;
    struct account account;
    int found = 0;

    old = fopen("record.dat", "r");
    newrec = fopen("new.dat", "w");

    printf("\nEnter the account number of the customer you want to delete: ");
    scanf("%d", &account_no);

    while (fscanf(old, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d",
                  &account.acc_no, account.name, &account.dob.month,
                  &account.dob.day, &account.dob.year, &account.pin,
                  account.address, account.aadharNum, &account.phone,
                  account.acc_type, &account.amt, &account.deposit.month,
                  &account.deposit.day, &account.deposit.year) != EOF) {
        if (account.acc_no != account_no) {
            fprintf(newrec, "%d %s %d/%d/%d %d %s %s %.0lf %s %.2f %d/%d/%d\n",
                    account.acc_no, account.name, account.dob.month,
                    account.dob.day, account.dob.year, account.pin,
                    account.address, account.aadharNum, account.phone,
                    account.acc_type, account.amt, account.deposit.month,
                    account.deposit.day, account.deposit.year);
        } else {
            found = 1;
        }
    }

    fclose(old);
    fclose(newrec);

    remove("record.dat");
    rename("new.dat", "record.dat");

    if (found == 0) {
        printf("\nRecord not found!");
    } else {
        printf("\nRecord deleted successfully!");
    }

    // Prompt user to return to main menu or exit
    printf("\n\nEnter 1 to go to the main menu and 0 to exit: ");
    scanf("%d", &main_exit);
    if (main_exit == 1)
        menu();
    else
        close();
}

void see() {
    int choice;
    FILE *ptr;
    struct account account;
    int found = 0;

    ptr = fopen("record.dat", "r");
    if (ptr == NULL) {
        printf("\nError opening file!");
        menu();
    }

    printf("\nDo you want to check by:\n1. Account number\n2. Name\nEnter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        int account_no;
        printf("\nEnter the account number: ");
        scanf("%d", &account_no);

        while (fscanf(ptr, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d",
                      &account.acc_no, account.name, &account.dob.month,
                      &account.dob.day, &account.dob.year, &account.pin,
                      account.address, account.aadharNum, &account.phone,
                      account.acc_type, &account.amt, &account.deposit.month,
                      &account.deposit.day, &account.deposit.year) != EOF) {
            if (account.acc_no == account_no) {
                found = 1;
                printf("\nAccount found!\n");
                printf("Account No.: %d\nName: %s\nDOB: %d/%d/%d\nPIN: %d\nAddress: %s\nAadhar Number: %s\nPhone number: %.0lf\nType Of Account: %s\nAmount deposited: $%.2f\nDate Of Deposit: %d/%d/%d\n",
                       account.acc_no, account.name, account.dob.month,
                       account.dob.day, account.dob.year, account.pin,
                       account.address, account.aadharNum, account.phone,
                       account.acc_type, account.amt, account.deposit.month,
                       account.deposit.day, account.deposit.year);
                break;
            }
        }
    } else if (choice == 2) {
        char name[60];
        printf("\nEnter the name: ");
        scanf("%s", name);

        while (fscanf(ptr, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d",
                      &account.acc_no, account.name, &account.dob.month,
                      &account.dob.day, &account.dob.year, &account.pin,
                      account.address, account.aadharNum, &account.phone,
                      account.acc_type, &account.amt, &account.deposit.month,
                      &account.deposit.day, &account.deposit.year) != EOF) {
            if (strcmp(account.name, name) == 0) {
                found = 1;
                printf("\nAccount found!\n");
                printf("Account No.: %d\nName: %s\nDOB: %d/%d/%d\nPIN: %d\nAddress: %s\nAadhar Number: %s\nPhone number: %.0lf\nType Of Account: %s\nAmount deposited: $%.2f\nDate Of Deposit: %d/%d/%d\n",
                       account.acc_no, account.name, account.dob.month,
                       account.dob.day, account.dob.year, account.pin,
                       account.address, account.aadharNum, account.phone,
                       account.acc_type, account.amt, account.deposit.month,
                       account.deposit.day, account.deposit.year);
                break;
            }
        }
    } else {
        printf("\nInvalid choice!");
    }

    fclose(ptr);

    if (found == 0) {
        printf("\nAccount not found!");
    }

    // Prompt user to return to main menu or exit
    printf("\n\nEnter 1 to go to the main menu and 0 to exit: ");
    scanf("%d", &main_exit);
    if (main_exit == 1)
        menu();
    else
        close();
}

#include <stdio.h>

remove("record.dat");
rename("new.dat", "record.dat");

if (found == 0) {
    printf("\nRecord not found!");
} else {
    printf("\nRecord deleted successfully!");
}

// Prompt user to return to main menu or exit
printf("\n\nEnter 1 to go to the main menu and 0 to exit: ");
scanf("%d", &main_exit);
if (main_exit == 1)
    menu();
else
    close();
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <stdbool.h>

    int main_exit;

    struct date {
        int month, day, year;
    };

    struct account {
        char name[60];
        int acc_no;
        int pin;

        double phone;
        char acc_type[10];
        float amt;
        struct date dob;
        struct date deposit;
        struct date withdraw;
    };

    void menu() {
        int choice;
        system("cls");
        system("color 7");
        printf("\n\n\t\t\t       BANKING MANAGEMENT SYSTEM");
        printf("\n\n\n\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2 WELCOME TO THE MAIN MENU \xB2\xB2\xB2\xB2\xB2\xB2\xB2");
        printf("\n\n\t\t[1] Create a new account\n\t\t[2] Update information of existing account\n\t\t[3] Transactions\n\t\t[4] Check the details of existing account\n\t\t[5] Remove existing account\n\t\t[6] View customer's list\n\t\t[7] Exit\n\n\n\t\t Enter your choice:");
        scanf("%d", &choice);

        system("cls");
        switch (choice) {
            case 1:
                new_acc();
                break;
            case 2:
                edit();
                break;
            case 3:
                transact();
                break;
            case 4:
                see();
                break;
            case 5:
                erase();
                break;
            case 6:
                view_list();
                break;
            case 7:
                close();
                break;
            default:
                printf("\nInvalid choice! Please enter a valid option.");
                break;
        }
    }

    void new_acc() {
        int test = 0;
        FILE *ptr;
        struct account add;
        ptr = fopen("record.dat", "a+");
        if (ptr == NULL) {
            printf("\nError opening file!");
            menu();
        }

        printf("\nEnter the account number: ");
        scanf("%d", &add.acc_no);

        // Add validation to check if the account number already exists
        // If it exists, prompt the user to enter a different account number
        // Otherwise, proceed with adding the account details
        printf("\nEnter the name: ");
        scanf("%s", add.name);
        printf("\nEnter the date of birth(mm/dd/yyyy): ");
        scanf("%d/%d/%d", &add.dob.month, &add.dob.day, &add.dob.year);
        printf("\nEnter the PIN: ");
        scanf("%d", &add.pin);
        printf("\nEnter the address: ");
        scanf("%s", add.address);
        printf("\nEnter the Aadhar number: ");
        scanf("%s", add.aadharNum);
        printf("\nEnter the phone number: ");
        scanf("%lf", &add.phone);
        printf("\nEnter the type of account(Saving/Current): ");
        scanf("%s", add.acc_type);
        printf("\nEnter the amount to deposit: $");
        scanf("%f", &add.amt);
        printf("\nEnter the date of deposit(mm/dd/yyyy): ");
        scanf("%d/%d/%d", &add.deposit.month, &add.deposit.day, &add.deposit.year);

        fprintf(ptr, "%d %s %d/%d/%d %d %s %s %.0lf %s %.2f %d/%d/%d\n",
                add.acc_no, add.name, add.dob.month, add.dob.day, add.dob.year,
                add.pin, add.address, add.aadharNum, add.phone, add.acc_type,
                add.amt, add.deposit.month, add.deposit.day, add.deposit.year);

        fclose(ptr);
        printf("\nAccount created successfully!\n");

        // Prompt user to return to main menu or exit
        printf("\n\nEnter 1 to go to the main menu and 0 to exit: ");
        scanf("%d", &main_exit);
        if (main_exit == 1)
            menu();
        else
            close();
    }

    void edit() {
        int choice, test = 0;
        FILE *ptr;
        struct account account;

        ptr = fopen("record.dat", "r+");
        if (ptr == NULL) {
            printf("\nError opening file!");
            menu();
        }

        printf("\nEnter the account number you want to update: ");
        scanf("%d", &choice);
        while (fscanf(ptr, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d",
                      &account.acc_no, account.name, &account.dob.month,
                      &account.dob.day, &account.dob.year, &account.pin,
                      account.address, account.aadharNum, &account.phone,
                      account.acc_type, &account.amt, &account.deposit.month,
                      &account.deposit.day, &account.deposit.year) != EOF) {
            if (account.acc_no == choice) {
                printf("\nAccount found! Enter new details:\n");
                printf("\nEnter the new name: ");
                scanf("%s", account.name);
                printf("\nEnter the new address: ");
                scanf("%s", account.address);
                printf("\nEnter the new phone number: ");
                scanf("%lf", &account.phone);
                fseek(ptr, -sizeof(account), SEEK_CUR);
                fprintf(ptr, "%d %s %d/%d/%d %d %s %s %.0lf %s %.2f %d/%d/%d\n",
                        account.acc_no, account.name, account.dob.month,
                        account.dob.day, account.dob.year, account.pin,
                        account.address, account.aadharNum, account.phone,
                        account.acc_type, account.amt, account.deposit.month,
                        account.deposit.day, account.deposit.year);
                printf("\nAccount updated successfully!");
                test = 1;
                break;
            }
        }
        fclose(ptr);
        if (test == 0) {
            printf("\nAccount not found!");
        }

        // Prompt user to return to main menu or exit
        printf("\n\nEnter 1 to go to the main menu and 0 to exit: ");
        scanf("%d", &main_exit);
        if (main_exit == 1)
            menu();
        else
            close();
    }

    void transact() {
        int choice, test = 0;
        FILE *ptr;
        struct account account;

        ptr = fopen("record.dat", "r+");
        if (ptr == NULL) {
            printf("\nError opening file!");
            menu();
        }

        printf("\nEnter the account number for transaction: ");
        scanf("%d", &choice);
        while (fscanf(ptr, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d",
                      &account.acc_no, account.name, &account.dob.month,
                      &account.dob.day, &account.dob.year, &account.pin,
                      account.address, account.aadharNum, &account.phone,
                      account.acc_type, &account.amt, &account.deposit.month,
                      &account.deposit.day, &account.deposit.year) != EOF) {
            if (account.acc_no == choice) {
                printf("\nAccount found! Enter transaction details:\n");
                int transaction_choice;
                printf("\n[1] Deposit\n[2] Withdraw\n\nEnter your choice: ");
                scanf("%d", &transaction_choice);
                if (transaction_choice == 1) {
                    float deposit_amount;
                    printf("\nEnter the amount you want to deposit: $");
                    scanf("%f", &deposit_amount);
                    account.amt += deposit_amount;
                    fseek(ptr, -sizeof(account), SEEK_CUR);
                    fprintf(ptr, "%d %s %d/%d/%d %d %s %s %.0lf %s %.2f %d/%d/%d\n",
                            account.acc_no, account.name, account.dob.month,
                            account.dob.day, account.dob.year, account.pin,
                            account.address, account.aadharNum, account.phone,
                            account.acc_type, account.amt, account.deposit.month,
                            account.deposit.day, account.deposit.year);
                    printf("\nDeposit successful!");
                } else if (transaction_choice == 2) {
                    float withdraw_amount;
                    printf("\nEnter the amount you want to withdraw: $");
                    scanf("%f", &withdraw_amount);
                    if (withdraw_amount <= account.amt) {
                        account.amt -= withdraw_amount;
                        fseek(ptr, -sizeof(account), SEEK_CUR);
                        fprintf(ptr, "%d %s %d/%d/%d %d %s %s %.0lf %s %.2f %d/%d/%d\n",
                                account.acc_no, account.name, account.dob.month,
                                account.dob.day, account.dob.year, account.pin,
                                account.address, account.aadharNum, account.phone,
                                account.acc_type, account.amt, account.deposit.month,
                                account.deposit.day, account.deposit.year);
                        printf("\nWithdrawal successful!");
                    } else {
                        printf("\nInsufficient balance!");
                    }
                } else {
                    printf("\nInvalid choice!");
                }
                test = 1;
                break;
            }
        }
        fclose(ptr);
        if (test == 0) {
            printf("\nAccount not found!");
        }

        // Prompt user to return to main menu or exit
        printf("\n\nEnter 1 to go to the main menu and 0 to exit: ");
        scanf("%d", &main_exit);
        if (main_exit == 1)
            menu();
        else
            close();
    }

    void see() {
        FILE *ptr;
        int test = 0, choice;
        struct account account;
        ptr = fopen("record.dat", "r");
        if (ptr == NULL) {
            printf("\nError opening file!");
            menu();
        }

        printf("\nEnter the account number: ");
        scanf("%d", &choice);

        while (fscanf(ptr, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d",
                      &account.acc_no, account.name, &account.dob.month,
                      &account.dob.day, &account.dob.year, &account.pin,
                      account.address, account.aadharNum, &account.phone,
                      account.acc_type, &account.amt, &account.deposit.month,
                      &account.deposit.day, &account.deposit.year) != EOF) {
            if (account.acc_no == choice) {
                test = 1;
                printf("\nAccount found!\n");
                printf("Account No.: %d\nName: %s\nDOB: %d/%d/%d\nPIN: %d\nAddress: %s\nAadhar Number: %s\nPhone number: %.0lf\nType Of Account: %s\nAmount deposited: $%.2f\nDate Of Deposit: %d/%d/%d\n",
                       account.acc_no, account.name, account.dob.month,
                       account.dob.day, account.dob.year, account.pin,
                       account.address, account.aadharNum, account.phone,
                       account.acc_type, account.amt, account.deposit.month,
                       account.deposit.day, account.deposit.year);
                break;
            }
        }
        fclose(ptr);
        if (test == 0) {
            printf("\nAccount not found!");
        }

        // Prompt user to return to main menu or exit
        printf("\n\nEnter 1 to go to the main menu and 0 to exit: ");
        scanf("%d", &main_exit);
        if (main_exit == 1)
            menu();
        else
            close();
    }

    void erase() {
        int account_no;
        FILE *old, *newrec;
        struct account account;
        int found = 0;

        old = fopen("record.dat", "r");
        newrec = fopen("new.dat", "w");
        printf("\nEnter the account number of the customer you want to delete: ");
        scanf("%d", &account_no);

        while (fscanf(old, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d",
                      &account.acc_no, account.name, &account.dob.month,
                      &account.dob.day, &account.dob.year, &account.pin,
                      account.address, account.aadharNum, &account.phone,
                      account.acc_type, &account.amt, &account.deposit.month,
                      &account.deposit.day, &account.deposit.year) != EOF) {
            if (account.acc_no != account_no) {
                fprintf(newrec, "%d %s %d/%d/%d %d %s %s %.0lf %s %.2f %d/%d/%d\n",
                        account.acc_no, account.name, account.dob.month,
                        account.dob.day, account.dob.year, account.pin,
                        account.address, account.aadharNum, account.phone,
                        account.acc_type, account.amt, account.deposit.month,
                        account.deposit.day, account.deposit.year);
            } else {
                found = 1;
            }
        }
        fclose(old);
        fclose(newrec);

        remove("record.dat");
        rename("new.dat", "record.dat");

        if (found == 0) {
            printf("\nRecord not found!");
        } else {
            printf("\nRecord deleted successfully!");
        }

        // Prompt user to return to main menu or exit
        printf("\n\nEnter 1 to go to the main menu and 0 to exit: ");
        scanf("%d", &main_exit);
        if (main_exit == 1)
            menu();
        else
            close();
    }

    void view_list() {
        FILE *ptr;
        struct account account;
        int test = 0;
        ptr = fopen("record.dat", "r");
        if (ptr == NULL) {
            printf("\nError opening file!");
            menu();
        }

        printf("\nACCOUNT LIST\n\n");
        printf("====================================================\n");
        printf("Account No.\t\tName\t\tType\t\tBalance\n");
        printf("====================================================\n");

        while (fscanf(ptr, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d",
                      &account.acc_no, account.name, &account.dob.month,
                      &account.dob.day, &account.dob.year, &account.pin,
                      account.address, account.aadharNum, &account.phone,
                      account.acc_type, &account.amt, &account.deposit.month,
                      &account.deposit.day, &account.deposit.year) != EOF) {
            printf("%-16d%-16s%-16s$%.2f\n", account.acc_no, account.name,
                   account.acc_type, account.amt);
            test++;
        }
        fclose(ptr);
        if (test == 0) {
            printf("\nNo accounts found!");
        }

        // Prompt user to return to main menu or exit
        printf("\n\nEnter 1 to go to the main menu and 0 to exit: ");
        scanf("%d", &main_exit);
        if (main_exit == 1)
            menu();
        else
            close();
    }

    void close() {
        printf("\nExiting...\n");
    }

    int main() {
        system("cls");
        menu();
        return 0;
    }