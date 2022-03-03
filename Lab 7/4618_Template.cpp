#include "CControl.h"

using namespace std;

void lab3_demo() {
    std::cout << "\n***********************************";
    std::cout << "\n* ELEX4618 Lab 3 Demo";
    std::cout << "\n***********************************";
    std::cout << "\n(1) joystick_demo";
    std::cout << "\n(2) DIO_demo";
    std::cout << "\n(3) button_demo";
    std::cout << "\n(4) servo_demo";
    std::cout << "\nCMD> ";
}

// For lab 3 demo
CControl comms;
void joystick_demo();
void DIO_demo();
void button_demo();
void servo_demo();
#define MAXANALOG 1023.0f;


int main(int argc, char* argv[])
{
    comms.init_com();
    int cmd = -1;
    do
    {
        lab3_demo();
        std::cin >> cmd;
        switch (cmd)
        {
        case 1: joystick_demo(); break;
        case 2: DIO_demo(); break;
        case 3: button_demo(); break;
        case 4: servo_demo(); break;
        }
    } while (cmd != 0);
}

void joystick_demo() {
    int xval, yval;
    float xscale, yscale;
    do {
        yval = comms.get_analog(26);
        yscale = (float)yval * 100 / MAXANALOG;
        xval = comms.get_analog(2);
        xscale = (float)xval * 100 / MAXANALOG;
        //std::cout << setprecision(2);
        std::cout << "Y AXIS: " << yval << "(" << yscale << "%)" << "\t";
        std::cout << "X AXIS: " << xval << "(" << xscale << "%)" << endl;
    } while (!GetAsyncKeyState(VK_ESCAPE));
}

void DIO_demo() {
    // Digital IO test
    int input;
    do {
        cout << "DIGITAL TEST: CH? = ";
        cin >> input;
        if (input < 0) return;
        cout << endl;
        comms.set_data(DIGITAL, 37, input);
    } while (!GetAsyncKeyState(VK_ESCAPE));
}

void button_demo() {
    int counter = 0;
    // Debounced pushbutton test
    do {
        if (comms.get_button(33)) counter++;
        cout << counter << endl;
    } while (!GetAsyncKeyState(VK_ESCAPE));
}

void servo_demo() {
    // Servo cycle test
    do {
        comms.set_servo(179);
        Sleep(1000);
        comms.set_servo(1);
        Sleep(1000);
    } while (!GetAsyncKeyState(VK_ESCAPE));

}
