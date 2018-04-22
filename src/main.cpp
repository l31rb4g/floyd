#include <QApplication>
#include "window.h"
#include <iostream>


string VERSION = "0.0.1";

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    for (int i=0; i<argc; i++){
        if (strcmp(argv[i], "--version")){
            cout << "Floyd version " + VERSION << endl;
            return 0;
        }
    }

    Window *window = new Window();
    window->show();

    return app.exec();
}

