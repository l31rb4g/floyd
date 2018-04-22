#include <string>
#include <iostream>
#include <fstream>
#include <QWidget>
#include <QVBoxLayout>
#include <QPalette>
#include <QLabel>
#include <QKeyEvent>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include "window.h"
using namespace std;


Window::Window(QWidget *parent): QWidget(parent) {
    int line_height = 45;
    selected = 0;
    string lineStyle = "color:#fff; padding:0 5px;";
    defaultLineStyle = lineStyle + "background:#333;";
    selectedLineStyle = lineStyle + "background:#222;";

    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    layout = new QVBoxLayout;
    layout->setSpacing(2);
    layout->setMargin(2);

    QPalette *palette = new QPalette;
    palette->setColor(QPalette::Background, QColor("#333333"));
    setPalette(*palette);

    line_count = readFile();
    setFixedSize(300, line_height * line_count);
    setLayout(layout);
}


int Window::readFile(){
    int lc = 0;
    string line;
    string file_path = getUserHome() + "/.floyd";
    ifstream f(file_path);
    if (f.is_open()){
        while (getline(f, line)){
            if (line != ""){
                lc++;
                insertLine(lc, line.c_str());
            }
        }
        f.close();
    } else {
        cout << "Unable to open file " << file_path << "\n";
    }

    return lc;
}


void Window::insertLine(int lc, const char *line){
    string label_line = to_string(lc) + ". " + line;
    QLabel *label = new QLabel(label_line.c_str());
    string style;

    if (lc == 1){
        style += selectedLineStyle;
    } else {
        style += defaultLineStyle;
    }

    label->setStyleSheet(style.c_str());
    label->setMargin(0);
    labels.push_back(label);
    lines.push_back(line);
    layout->addWidget(label);
}


void Window::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Down && selected < labels.size()-1) {
        clearSelected();
        selected++;
        labels[selected]->setStyleSheet(selectedLineStyle.c_str());
    }
    else if (event->key() == Qt::Key_Up && selected > 0) {
        clearSelected();
        selected--;
        labels[selected]->setStyleSheet(selectedLineStyle.c_str());
    }
    else if (event->key() == Qt::Key_Return) {
        writeLine(selected);
    }
    else if (event->key() == Qt::Key_Escape) {
        close();
    }
}

void Window::keyReleaseEvent(QKeyEvent *event) {
    if (event->key() >= 48 && event->key() <= 57){
        int number = event->key() - 48;
        clearSelected();
        selected = number - 1;
        if (number <= line_count){
            writeLine(number - 1);
        } else {
            close();
        }
    }
}


void Window::clearSelected() {
    for (int i=0; i<labels.size(); i++){
        labels[i]->setStyleSheet(defaultLineStyle.c_str());
    }
}


void Window::writeLine(int index){
    close();
    string cmd = "xdotool type " + lines[index];
    popen(cmd.c_str(), "r");
}


string Window::getUserHome(){
    struct passwd *pw = getpwuid(getuid());
    const char *homedir = pw->pw_dir;
    return homedir;
}

