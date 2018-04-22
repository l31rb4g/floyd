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
        int line_count;
        string defaultLineStyle;
        string selectedLineStyle;
        QVector<QLabel*> labels;
        QVBoxLayout *layout;
        vector<string> lines;

        int readFile();
        void insertLine(int line_count, const char *line);
        void keyPressEvent(QKeyEvent *);
        void clearSelected();
        void writeLine(int index);
        string getUserHome();

};
