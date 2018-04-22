#include <QWidget>
#include <QVBoxLayout>


class Window: public QWidget {

    public:
        Window(QWidget *parent = 0);

    protected:
        int selected;
        QVBoxLayout *layout;
        int readFile();
        void insertLine(int line_count, const char *line);
        void keyPressEvent(QKeyEvent *);
        //void keyReleaseEvent(QKeyEvent *);

};
