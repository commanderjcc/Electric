// Name: Joshua Christensen
// Project: electric
// File: main.cpp
// Purposes: Create a program that allows user to enter # of kilowatt hours and outputs subtotal tax and total and lines up decimals
// Date: 1/14/20

#include <iostream> //Allow for cin and cout
#include <iomanip> //Allow for text justification
#include <cmath> //Allow for Logs and Rounding
#include <ctime> //TODO add time
using namespace std;

//Justify Function,
void justify(char direction, string str, int width, bool newLine = false, char fill = ' ', float num = 0, int precision = 2) {
    cout << resetiosflags(ios::left | ios::right) << setiosflags(ios::fixed | ios::showpoint) << setprecision(precision); //reset all of the flags
    if (num != 0) { //skip all the string stuff if the number is set, if it actually is zero then the "0.00" string we used for str will get used
        if (direction == 'r') {
            cout << setiosflags(ios::right) << setfill(fill) << setw(width) << num; //justify Right
        } else if (direction == 'c') {
            int availableSpace = width - ((int)(log10(num)+3)); //find the amount of space that is available
            if( availableSpace < 0) { //if the space for justifying is less than 0
                cout << setiosflags(ios::left) << setfill(fill) << setw(width) << num; //just output as left justify
                return;
            }
            int stringStartLength = availableSpace/2; //the width before the num
            int stringEndLength = availableSpace-stringStartLength; //the width after the num, uses subtraction to avoid rounding errors
            cout << setiosflags(ios::left) << setfill(fill) << setw(stringStartLength) << "" << num << setw(stringEndLength) << ""; //couts the num sandwiched between to pads of setw()
        } else {
            cout << setiosflags(ios::left) << setfill(fill) << setw(width) << num; //justify Left
        }
    } else if (direction == 'r') {
        cout << setiosflags(ios::right) << setfill(fill) << setw(width) << str; //justify right
    } else if (direction == 'c') {
        int availableSpace = width - str.length(); //find the amount of space that is available
        if( availableSpace < 0) { //if the space for justifying is less than 0
            cout << setiosflags(ios::left) << setfill(fill) << setw(width) << str; //just output as left justify
            return;
        }
        int stringStartLength = availableSpace/2; //the width before the num
        int stringEndLength = availableSpace-stringStartLength; //the width after the num, uses subtraction to avoid rounding errors
        cout << setiosflags(ios::left) << setfill(fill) << setw(stringStartLength) << "" << str << setw(stringEndLength) << ""; //couts the str sandwiched between to pads of setw()
    } else {
        cout << setiosflags(ios::left) << setfill(fill) << setw(width) << str; // justify left
    }

    if (newLine) {
        cout << "\n"; //if there is supposed to be a new line after the phrase, then send it out
    }

    return;
}

int logo() { //Draws the GGE logo
    cout << "              .,,,,,,,,,,,.            " << endl;
    cout << "         ,,,,%@@@,,,,,,,,,,,,,         " << endl;
    cout << "      ,,,,,%@@@,,,,,,,,,,,,,,,,,,      " << endl;
    cout << "    ,,,,,,,@@@,,,,,,,,,,,,,&@@@@%,,    " << endl;
    cout << "   ,,,,,,,@@&,,,,,,,,,,,,,@@@/,@@@,,   " << endl;
    cout << "  ,,,,,,*,,,,,,*@@@@@,,,,@@#,,,,@@,,,  " << endl;
    cout << " ,,,,,,,,,,,,&@@*,,,@@,,,@@%,,,,@@,,,, " << endl;
    cout << ",,,@@@@@@@,,&@@,,,,,@@,,,,@@@&%,,,,,,,," << endl;
    cout << ",@@@,,,,@@&,@@,,,,,,,,,,,,#@@@@,,,,,,,," << endl;
    cout << "&@@,,,,,,,,,@@/,,,,@@@@&,@@#,,,,,,,,,,," << endl;
    cout << "@@&,,,,,/&@@@@@,,,,,,*@@,@@,,,,,,,,,,,," << endl;
    cout << "@@@,,,,&&/@@,&@@@@@@@@@@@@@,,,,,,,/@@,," << endl;
    cout << ",@@@,,,,,,@@@@*,,**,,@@@,#@@@@@@@@@@,,," << endl;
    cout << " ,/@@@@@@@@@,,,,,,,%@,@#,,,,@@@@%,,,,, " << endl;
    cout << "  ,,,,,,*@@@,,,,,,/@,%@,,,,@/,,,,,,,,  " << endl;
    cout << "   ,,,,@@,@@,,,,,,*@@@(,,@@@%,,,,,,,   " << endl;
    cout << "    ,,,@,#@,,,,,,,,,,,,@@@,,,,,,,,,    " << endl;
    cout << "      ,@@@,,,,,,,,,,,,,/@@@,,,,,,      " << endl;
    cout << "         ,,,,,,,,,,,,,@/,,,,,,         " << endl;
    cout << "             ,,,,,,,,,,,,,             " << endl;

    return 0;
}


int main()
{
    //declare constants
    const double baseRate = 0.0475;
    const double surchargeRate = .1;
    const double cityTaxRate = .03;
    const double latePenalityRate = .04;

    //declare vars needed for calculation
    int kiloWatts = 0;
    double subtotal = 0;
    double surcharge = 0;
    double totalTax = 0;
    double totalBill = 0;
    double lateBill = 0;

    //declare time variables
    time_t now;
    time(&now); //initialize the var with right now
    time_t tenDays = 864000;
    struct tm * tenDaysFromNow = {nullptr};
    char tenDaysFromNowBuffer [10];
    char timeBuffer [39];
    char dateBuffer [39];

    //Calculate time char buffer
    tenDays = now + tenDays;
    tenDaysFromNow = localtime(&tenDays);
    strftime(tenDaysFromNowBuffer,10,"%h %d",tenDaysFromNow);
    strftime(timeBuffer,39,"It is %I:%M %p on",localtime(&now));
    strftime(dateBuffer,39,"%a, %h %d %Y",localtime(&now));

    //get kiloWatt usage
    cout << endl << "Enter KWH used:";
    cin >> kiloWatts;

    //do calculations
    subtotal = kiloWatts * baseRate;
    surcharge = subtotal * surchargeRate;
    totalTax = subtotal * cityTaxRate;
    totalBill = subtotal + surcharge + totalTax + .01;
    lateBill = totalBill * (1 + latePenalityRate);

//    //debug output data
//    cout << "**debug**" << endl;
//    cout << kiloWatts << endl;
//    cout << subtotal << endl;
//    cout << surcharge << endl;
//    cout << totalTax << endl;
//    cout << totalBill << endl;
//    cout << lateBill << endl;
//    cout << endl;

    //Start output
    logo(); //draw logo
    cout << endl;

    //makes header
    justify('r',"",39,true,'#');
    justify('c'," Welcome to GG Electric ",39,true,'#');
    justify('c', " " + string(timeBuffer) + " ",39, true,'#');
    justify('c', " " + string(dateBuffer) + " ",39, true,'#');
    justify('r',"",39,true,'#');
    cout << endl;

    //makes kilowatts used section
    justify('l',"",39,true,'-'); //makes solid '-' line
    justify('l',"Kilowatts Used:",15); //makes Kilowatts used
    justify('r',to_string(kiloWatts)+" KW",24, true, '.'); //adds the dots and the Kilowatts
    justify('l',"",39,true,'-'); //makes solid '-' line

    cout << endl;

    //Makes Base Rate Line
    justify('l',"Base Rate",10);
    justify('r'," " + to_string(kiloWatts) + " @ $",12, false, '>');
    justify('l',"0.00",7, false, ' ', baseRate, 4);
    justify('l',"=> ",3);
    justify('r',"$",1);
    justify('r',"0.00",6,true,' ', subtotal);

    //makes Surcharge Line
    justify('l',"Surcharge",10);
    justify('r'," $",23, false, '>');
    justify('r',"0.00",6, true, ' ', surcharge);

    //Makes Tax Line
    justify('l',"City Tax", 9);
    justify('r'," $",24, false, '>');
    justify('r',"0.00", 6,true, ' ', totalTax);

    //Makes Addition line
    justify('r',"+ _______",39, true);
    cout << endl;

    //Pay this amount Line
    justify('l',"Pay This Amount ",31, false, '>');
    justify('r'," $",2);
    justify('r',"0.00",6, true, ' ', totalBill);
    cout<<endl;

    //Pay after day line
    justify('l', "After " + string(tenDaysFromNowBuffer) + " Pay ",31, false, '>'); //use char buffer as string
    justify('r'," $",2);
    justify('r',"0.00",6, true, ' ',lateBill);

    return 0;
}
