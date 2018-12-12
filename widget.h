#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QStandardItemModel>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QMenuBar>

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
private:
    Ui::Widget *ui;
    QStandardItemModel  *m_playListModel;   // модель данных плейлиста для отображения
    QMediaPlayer        *m_player;          // проигрыватель треков
    QMediaPlaylist      *m_playlist;        // плейлиста проигрывателя
};

#endif // WIDGET_H
