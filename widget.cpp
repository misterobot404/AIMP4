#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QDir>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    QMenuBar* menuBar = new QMenuBar();

    QMenu *fileStyle = new QMenu("Style");

    QAction *Classic = new QAction("Classic", this);
    connect(Classic, SIGNAL(triggered()), this, SLOT(setStyleClassic()));
    fileStyle->addAction(Classic);

    QAction *AIMP = new QAction("AIMP", this);
    connect(AIMP, SIGNAL(triggered()), this, SLOT(setStyleAIMP()));
    fileStyle->addAction(AIMP);

    QAction *Black = new QAction("Black", this);
    connect(Black, SIGNAL(triggered()), this, SLOT(setStyleBlack()));
    fileStyle->addAction(Black);

    menuBar->addMenu(fileStyle);

    QAction *Exit = new QAction("Exit", this);
    connect(Exit, SIGNAL(triggered()), this, SLOT(close()));
    menuBar->addAction(Exit);

    this->layout()->setMenuBar(menuBar);

    // Настройка таблицы плейлиста
    m_playListModel = new QStandardItemModel(this);
    ui->playlistView->setModel(m_playListModel);    // устанавливаем модель данных
    m_playListModel->setHorizontalHeaderLabels(QStringList()  << tr("Audio Track") << tr("File Path"));
    ui->playlistView->hideColumn(1);    // скрываем колонку, в которой хранится путь к файлу
    ui->playlistView->verticalHeader()->setVisible(false);             // скрываем нумерацию строк
    ui->playlistView->setSelectionBehavior(QAbstractItemView::SelectRows);  // включаем выделение строк
    ui->playlistView->setSelectionMode(QAbstractItemView::SingleSelection); // разрешаем выделять только одну строку
    ui->playlistView->setEditTriggers(QAbstractItemView::NoEditTriggers);   // отключаем редактирование
    ui->playlistView->horizontalHeader()->setStretchLastSection(true); // заполняем колонку на всю ширину

    m_player = new QMediaPlayer(this);
    m_playlist = new QMediaPlaylist(m_player);
    m_player->setPlaylist(m_playlist);          // устанавливаем плейлист в плеер
    m_player->setVolume(70);                    // громкость
    m_playlist->setPlaybackMode(QMediaPlaylist::Loop);  // устанавливаем циклический режим проигрывания плейлиста

    // подключаем кнопки управления к слотам управления
    connect(ui->btn_previous, &QToolButton::clicked, m_playlist, &QMediaPlaylist::previous);
    connect(ui->btn_next, &QToolButton::clicked, m_playlist, &QMediaPlaylist::next);
    connect(ui->btn_play, &QToolButton::clicked, m_player, &QMediaPlayer::play);
    connect(ui->btn_pause, &QToolButton::clicked, m_player, &QMediaPlayer::pause);
    connect(ui->btn_stop, &QToolButton::clicked, m_player, &QMediaPlayer::stop);

    // при даблклике по треку в таблице устанавливаем трек в плейлисте
    connect(ui->playlistView, &QTableView::doubleClicked, [this](const QModelIndex &index){
        m_playlist->setCurrentIndex(index.row());
    });

    // при изменении индекса текущего трека в плейлисте, устанавливаем название файла в специальном лейбле
    connect(m_playlist, &QMediaPlaylist::currentIndexChanged, [this](int index){
        ui->currentTrack->setText(m_playListModel->data(m_playListModel->index(index, 0)).toString());
    });
}

Widget::~Widget()
{
    delete ui;
    delete m_playListModel;
    delete m_playlist;
    delete m_player;
}

void Widget::on_btn_add_clicked()
{    
    QStringList files = QFileDialog::getOpenFileNames(this,
                                                      tr("Open files"),
                                                      QString(),
                                                      tr("Audio Files (*.mp3)"));

    // устанавливаем данные по именам и пути к файлам
    // в плейлист и таблицу отображающую плейлист
    foreach (QString filePath, files) {
        QList<QStandardItem *> items;
        items.append(new QStandardItem(QDir(filePath).dirName()));
        items.append(new QStandardItem(filePath));
        m_playListModel->appendRow(items);
        m_playlist->addMedia(QUrl(filePath));
    }
}

void Widget::setStyleClassic()
{
    Widget::setStyleSheet("");
}

void Widget::setStyleAIMP()
{
    QFile File(":/css/css/classicStyle.qss");
        File.open(QFile::ReadOnly);
        QString StyleSheet = QLatin1String(File.readAll());
        Widget::setStyleSheet(StyleSheet);
}

void Widget::setStyleBlack()
{
    QFile File(":/css/css/blackStyle.qss");
    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());
    Widget::setStyleSheet(StyleSheet);
}

