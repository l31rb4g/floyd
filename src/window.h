#include <string>
#include <QWidget>
#include <QVBoxLayout>
#include <QVector>
#include <QLabel>
using namespace std;


class Window: public QWidget {

    public:
        Window(QWidget *parent = 0);

    protected:
        int selected;
        string defaultLineStyle;
        string selectedLineStyle;
        QVector<QLabel*> labels;
        QVBoxLayout *layout;
        int readFile();
        void insertLine(int line_count, const char *line);
        void keyPressEvent(QKeyEvent *);
        //void keyReleaseEvent(QKeyEvent *);
        void clearSelected();

};
