#include <iostream>
#include <iomanip>
#include <cstring>
#include <cctype>
using namespace std;

// Global Variables
double dailyCollection = 0;
int counts[3] = {0, 0, 0};

//Function prototype
int validateDate(char[]);
int cabinChoice();
double calcTotalCharge(int,double,int,double);
double calcTotalDiscount(double,double,double,double);
int destinationChoice();
int cabinChoice();
void displayIntro();
void formula(double,double,double&,double&,double&,double&,double&);
double getBasePrice(int,int,int);
void getInput1(char[],char[],char[]);
void getInput2(int&,int&);
double getPriceDiscount(double);
int journeyChoice();
double membership();
double promoCode();
void getFamous(int[], char[]);
void getInFamous(int[], char[]);
void output(double,char[],char[]);
void receipt(char[],char[],char[],double,double,double,double,double);

int main()
{
	char sentinel,comfirm;
    char name[50], email[50], phoneNumber[20], depDate[15], retDate[15],famous[30],inFamous[30];
    int adults = 0, child = 0,jChoice,dChoice,cChoice;
    double adultP, childP,totalDiscount,destinationDiscount,memberDiscount,priceDiscount,promoDiscount,totalCharge,net,sst,discAmt,
    finalAmt;

    cout << "Do you want to start the booking system? [Y/N]: ";
    cin >> sentinel;
    
    if (toupper(sentinel) != 'Y') {
        cout << "\n[ERROR]: Booking system was not initiated. Program terminating..." << endl;
        return 0;
    }

    // Main Loop
    while (toupper(sentinel) == 'Y') {
        displayIntro();
        getInput1(name, email, phoneNumber);
        
        jChoice = journeyChoice();
        
        int validDep = 0;
        while (validDep == 0) {
            cout << "Enter Departure Date (DD/MM/YYYY): ";
            cin >> depDate;
            if (validateDate(depDate) == 1) {
                validDep = 1;
            } else {
                cout << "[ERROR]: Invalid date format. Please use DD/MM/YYYY (e.g. 24/10/2026)\n" << endl;
            }
        }

        // Return Date Validation
        if (jChoice == 2) {
            int validRet = 0;
            while (validRet == 0) {
                cout << "Enter Return Date (DD/MM/YYYY): ";
                cin >> retDate;
                if (validateDate(retDate) == 1) {
                    validRet = 1;
                } else {
                    cout << "[ERROR]: Invalid format. Please use DD/MM/YYYY (e.g. 06/12/2026)\n" << endl;
                }
            }
        }

        dChoice = destinationChoice();
        cChoice = cabinChoice();

        // Count Destination Popularity
        if (dChoice >= 1 && dChoice <= 3) {
            counts[dChoice - 1]++;
        }
    
        adultP = getBasePrice(jChoice, dChoice, cChoice);
        childP = adultP * 0.75; 
        
        // Destination Discount For Japan
        if (dChoice == 1) {
            destinationDiscount = 0.15;
        } else {
            destinationDiscount = 0.0;
        }

        getInput2(adults, child);
        promoDiscount = promoCode();
        memberDiscount = membership();

        cout << "\nConfirm booking? (Y/N): ";
        char confirm; 
        cin >> confirm;
	
        // Process Booking If Confirmed
        if (toupper(confirm) == 'Y') {
            totalCharge = calcTotalCharge(adults,adultP,child,childP);
            priceDiscount = getPriceDiscount(totalCharge);
            totalDiscount = calcTotalDiscount(destinationDiscount,priceDiscount,memberDiscount,promoDiscount);
            formula(totalDiscount,totalCharge,discAmt,net,sst,finalAmt,dailyCollection);
            receipt(name, email, phoneNumber, totalCharge,discAmt,net,sst,finalAmt);
            
        	cout << "\n[SUCCESS]: Booking processed successfully." << endl;
        } else {
            cout << "\n[INFO]: Booking cancelled." << endl;
        }
        cout << "Do you want to continue to the next customer? [Y/N]: ";
        cin >> sentinel;
        cout << endl;
    }

    // Output Daily Summary
    
    getFamous(counts, famous);
    getInFamous(counts, inFamous);
    output(dailyCollection, famous, inFamous);
	
	return 0;
}

int validateDate(char date[]) {
    // Check if length is exactly 10 (DD/MM/YYYY)
    if (strlen(date) != 10) {
        return 0;
    }

    // Check for slashes at correct positions
    if (date[2] != '/' || date[5] != '/') {
        return 0;
    }

    // Check if all other characters are digits
    for (int i = 0; i < 10; i++) {
        if (i == 2 || i == 5) continue; // Skip the slashes
        if (!isdigit(date[i])) {
            return 0;
        }
    }

    return 1; // Valid
}

void displayIntro()
{
	cout << "\n=========== KODO AIRLINES ==========" << endl;
    cout << "    Flight Ticket Management System    " << endl;
    cout << "====================================" << endl;
}

void getInput1(char name[],char email[],char phoneNumber[])
{
	cin.ignore();
	cout << "Enter Customer Name: ";
    cin.getline(name, 50);
    cout << "Enter Email Address: "; 
    cin.getline(email, 50);
    cout << "Enter Phone Number: ";
    cin.getline(phoneNumber, 20);
}

int journeyChoice()
{
	int jChoice;
	int ab = 0;
        while (ab == 0) {
            cout << "\nSelect Journey Type (1. One-way, 2. Round-trip): ";
            cin >> jChoice;
            if ( jChoice == 1 || jChoice == 2) {
                ab = 1;
            } else {
                cout << "[ERROR]: Invalid input format." << endl;
            }
        }
    return jChoice;
}

int destinationChoice()
{
	int dChoice;
	int ab = 0;
        while (ab == 0) {
            cout << "1. Malaysia - Japan\n2. Malaysia - Singapore\n3. Malaysia - USA\nEnter choice: ";
            cin >> dChoice;
            if ( dChoice == 1 || dChoice == 2 || dChoice == 3) {
                ab = 1;
            } else {
                cout << "[ERROR]: Invalid input format." << endl;
            }
        }
    return dChoice;
}

int cabinChoice() 
{
    int cChoice;
    int ab = 0;
        while (ab == 0) {
            cout << "\nSelect Cabin (1. Economy, 2. Business, 3. First): ";
            cin >> cChoice;
            if ( cChoice == 1 || cChoice == 2 || cChoice == 3) {
                ab = 1;
            } else {
                cout << "[ERROR]: Invalid input format." << endl;
            }
        }
    return cChoice;
}

double getBasePrice(int jChoice, int dChoice, int cChoice) 
{
    double price = 0;

    // One-way Trip
    if (jChoice == 1) {
        if (dChoice == 1) { // Japan
            if (cChoice == 1) {
                price = 2100; 
            } else if (cChoice == 2) {
            price = 3150;
            } else {
                price = 6300;
            }
        } else if (dChoice == 2) { // Singapore
            if (cChoice == 1) {
                price = 80;
            } else if (cChoice == 2) {
                price = 120;
            } else {
                price = 240;
            }
        } else { // USA
            if (cChoice == 1) {
                price = 3000;
            } else if (cChoice == 2) {
                price = 4500;
            } else {
                price = 9000;
            }
        }
    } else { // Round-trip
        if (dChoice == 1) { // Japan
            if (cChoice == 1) {
                price = 3150;
            } else if (cChoice == 2) {
                price = 4725;
            } else {
                price = 9450;
            }
        } else if (dChoice == 2) { // Singapore
            if (cChoice == 1) {
                price = 120;
            } else if (cChoice == 2) {
                price = 180;
            } else {
                price = 270;
            }
        } else { // USA
            if (cChoice == 1) {
                price = 4500;
            } else if (cChoice == 2) {
                price = 6750;
            } else {
                price = 13500;
            }
        }
    }
    return price;
}

void getInput2(int& adults, int& child) 
{
    cout << "Enter number of adults: "; 
    cin >> adults;
    cout << "Enter number of children: "; 
    cin >> child;
}

double promoCode() {
    double promoDiscount = 0.00;
    char code[20];
    int isDone = 0;

    while (isDone == 0) {
        cout << "\nEnter Promo Code (or 'NONE' to skip): ";
        cin >> code;

        if (strcmp(code, "CheapFlight") == 0) {
            cout << "\n[SUCCESS]: 10% discount applied!" << endl;
            promoDiscount = 0.10;
            isDone = 1;
        } 
        else if (strcmp(code, "NONE") == 0 || strcmp(code, "none") == 0) {
            promoDiscount = 0.00;
            isDone = 1;
        } 
        else {
            cout << "\n[ERROR]: Invalid promo code '" << code << "'. Please try again." << endl;
        }
    }
    return promoDiscount;
}

double membership() 
{
	double memberDiscount;
    char member;
    cout << "Membership? (Y/N): "; 
    cin >> member;
    if (toupper(member) == 'Y') {
        memberDiscount = 0.15;
    } else {
    memberDiscount = 0.0;
	}
    return memberDiscount;
}

double calcTotalCharge(int adults, double adultP, int child, double childP) 
{
    double totalCharge;
	totalCharge = (adults * adultP) + (child * childP);
	return totalCharge;
}

double getPriceDiscount(double totalCharge)
{
	double priceDiscount;
	if(totalCharge >= 6700 ) {
		priceDiscount = 0.05;
	} else {
		priceDiscount = 0.00;
	}
	return priceDiscount;
}

double calcTotalDiscount(double destinationDiscount,double priceDiscount,double memberDiscount,double promoDiscount)
{
	double totalDiscount;
	totalDiscount = destinationDiscount + priceDiscount + memberDiscount + promoDiscount;
	return totalDiscount;
}

void formula(double totalDiscount,double totalCharge,double& discAmt,double& net,double& sst,double& finalAmt,double& dailyCollection) 
{
    discAmt = totalCharge * totalDiscount;
    net = totalCharge - discAmt;
    sst = net * 0.06;
    finalAmt = net + sst;
    dailyCollection = dailyCollection + finalAmt;
}

void receipt(char name[], char email[], char phoneNumber[], double totalCharge, double discAmt, 
             double net, double sst, double finalAmt) 
{
    cout << fixed << setprecision(2);
    cout << "\n========= BOOKING SUMMARY =========" << endl;
    cout << "Name: " << name << endl;
    cout << "Email: " << email << endl;
    cout << "Phone: " << phoneNumber << endl;
    cout << "Total Charge: RM" << totalCharge << endl;
    cout << "Discount: RM" << discAmt << endl;
    cout << "Net Total: RM" << net << endl;
    cout << "SST (6%): RM" << sst << endl;
    cout << "-----------------------------------" << endl;
    cout << "FINAL AMOUNT: RM" << finalAmt << endl;
    cout << "====================================" << endl;
}

void getFamous(int counts[], char famous[]) 
{
    if (counts[0] >= counts[1] && counts[0] >= counts[2]) {
        strcpy(famous, "Malaysia - Japan");
    } else if (counts[1] >= counts[0] && counts[1] >= counts[2]) {
        strcpy(famous, "Malaysia - Singapore");
    } else {
        strcpy(famous, "Malaysia - United States");
    }
}

void getInFamous(int counts[], char inFamous[]) 
{
     if (counts[0] <= counts[1] && counts[0] <= counts[2]) {
        strcpy(inFamous, "Malaysia - Japan");
    } else if (counts[1] <= counts[0] && counts[1] <= counts[2]) {
        strcpy(inFamous, "Malaysia - Singapore");
    } else {
        strcpy(inFamous, "Malaysia - United States");
    }
}

void output(double dailyCollection, char famous[], char inFamous[]) 
{
    cout << fixed << setprecision(2);
    cout << "\n========= DAILY TOTAL COLLECTION ==========" << endl;
    cout << "Total Collection: RM" << dailyCollection << endl;
    cout << "Famous Destination  : " << famous << endl;
    cout << "Infamous Destination: " << inFamous << endl;
    cout << "===========================================" << endl;
}
