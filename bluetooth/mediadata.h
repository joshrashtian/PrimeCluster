#ifndef MEDIADATA_H
#define MEDIADATA_H

#include <QColor>
#include <QList>
#include <QObject>
#include <QQmlEngine>
#include <QString>
#include <QUrl>

struct AlbumArt {
    Q_GADGET
    QML_VALUE_TYPE(albumArt)
    Q_PROPERTY(QUrl url MEMBER url)
    Q_PROPERTY(QList<QColor> colors MEMBER colors)

public:
    QUrl url;
    QList<QColor> colors;

    bool operator==(const AlbumArt &) const = default;
};

class MediaData : public QObject {
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("MediaData is created in C++")

    Q_PROPERTY(QString title READ title NOTIFY titleChanged)
    Q_PROPERTY(QString artist READ artist NOTIFY artistChanged)
    Q_PROPERTY(QString album READ album NOTIFY albumChanged)
    Q_PROPERTY(QString appName READ appName NOTIFY appNameChanged)
    Q_PROPERTY(double duration READ duration NOTIFY durationChanged)
    Q_PROPERTY(double elapsed READ elapsed NOTIFY elapsedChanged)
    Q_PROPERTY(bool playing READ playing NOTIFY playingChanged)
    Q_PROPERTY(AlbumArt art READ art NOTIFY artChanged)

public:
    explicit MediaData(QObject *parent = nullptr);

    QString title() const;
    QString artist() const;
    QString album() const;
    QString appName() const;
    double duration() const;
    double elapsed() const;
    bool playing() const;
    AlbumArt art() const;

    void setTitle(const QString &title);
    void setArtist(const QString &artist);
    void setAlbum(const QString &album);
    void setAppName(const QString &appName);
    void setDuration(double duration);
    void setElapsed(double elapsed);
    void setPlaying(bool playing);
    void setArt(const AlbumArt &art);

signals:
    void titleChanged();
    void artistChanged();
    void albumChanged();
    void appNameChanged();
    void durationChanged();
    void elapsedChanged();
    void playingChanged();
    void artChanged();

private:
    QString m_title = "Umbrella (feat. Jay-Z)";
    QString m_artist = "Rihanna";
    QString m_album = "Good Girl Gone Bad";
    QString m_appName;
    double m_duration = 276.0;
    double m_elapsed = 0.0;
    bool m_playing = false;
    AlbumArt m_art;
};

#endif
