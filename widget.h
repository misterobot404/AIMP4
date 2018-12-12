#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QStandardItemModel>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QMenuBar>
#include <QFileDialog>
#include <QDir>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QUrl>
#include <QSlider>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_btn_add_clicked();
    void setStyleClassic();
    void setStyleAIMP();
    void setStyleBlack();    
    void dragEnterEvent( QDragEnterEvent * event );
    void dropEvent ( QDropEvent * event );

    void on_horizontalSlider_sliderMoved(int position);

private:
    Ui::Widget *ui;
    QStandardItemModel  *m_playListModel;   // модель данных плейлиста для отображения
    QMediaPlayer        *m_player;          // проигрыватель треков
    QMediaPlaylist      *m_playlist;        // плейлиста проигрывателя
};

#endif // WIDGET_H
