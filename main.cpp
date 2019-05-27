#include <iostream>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

void menu (){
    cout << "1.turn on num lock" << endl;
    cout << "2.turn on caps lock" << endl;
    cout << "3.turn off all" << endl;
    cout << "4.exit" << endl;
}

int screen(int &c){
    menu();
    cout << endl << "Enter your request: " ;
    cin >> c;
}


int main(int argc, char* argv[]) {
    int fd_console = open("/dev/console", O_WRONLY);
    if (fd_console == -1) {
        cerr << "Error opening console file descriptor\n";
        exit(-1);
    }

    ioctl(fd_console, 0x4B32, 0x0);
    while(true)
    {
        int request;
        screen(request);
        switch (request) {
            case 1:
                cout << "*** turning on num lock" << endl;
                ioctl(fd_console, 0x4B32, 0x02);
                break;
            case 2:
                cout << "*** turning on caps lock" << endl;
                ioctl(fd_console, 0x4B32, 0x04);
                break;
            default:
                if(request != 4) {
                    cout << "*** turning off all" << endl;
                    ioctl(fd_console, 0x4B32, 0x0);
                }
        }

        if(request == 4)
        {
            cout << "EXITING" << endl;
            break;
        }
    }
  // turn on caps lock
  ioctl(fd_console, 0x4B32, 0x04);

  // turn on num block 
  ioctl(fd_console, 0x4B32, 0x02);

  // turn off 
//  ioctl(fd_console, 0x4B32, 0x0);

  close(fd_console);
  return 0;
}