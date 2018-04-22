#include <string>
#include <iostream>
#include <fstream>
#include <QWidget>
#include <QVBoxLayout>
#include <QPalette>
#include <QLabel>
#include <QKeyEvent>
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

    int line_count = readFile();
    setFixedSize(300, line_height * line_count);
    setLayout(layout);
}


int Window::readFile(){
    int line_count = 0;
    string line;
    string file_path = "/home/l31rb4g/.floyd";
    ifstream f(file_path);
    if (f.is_open()){
        cout << "File opened\n";
        while (getline(f, line)){
            if (line != ""){
                line_count++;
                insertLine(line_count, line.c_str());
            }
        }
        f.close();
    } else {
        cout << "Unable to open file " << file_path << "\n";
    }

    return line_count;
}


void Window::insertLine(int line_count, const char *line){
    string label_line = to_string(line_count) + ". " + line;
    QLabel *label = new QLabel(label_line.c_str());
    string style;

    if (line_count == 1){
        style += selectedLineStyle;
    } else {
        style += defaultLineStyle;
    }

    label->setStyleSheet(style.c_str());
    label->setMargin(0);
    labels.push_back(label);
    layout->addWidget(label);
}


void Window::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Down && selected < labels.size()-1) {
        selected++;
        clearSelected();
        labels[selected]->setStyleSheet(selectedLineStyle.c_str());
    }
    else if (event->key() == Qt::Key_Up && selected > 0) {
        selected--;
        clearSelected();
        labels[selected]->setStyleSheet(selectedLineStyle.c_str());
    }
}


void Window::clearSelected() {
    for (int i=0; i<labels.size(); i++){
        labels[i]->setStyleSheet(defaultLineStyle.c_str());
    }
}
 
//void Window::keyReleaseEvent(QKeyEvent *event) {
    //if(event->key() == Qt::Key_) {
        //cout << "You released ESC" << "\n";;
    //}
//}
