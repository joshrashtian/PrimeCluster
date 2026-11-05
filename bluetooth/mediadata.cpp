#include "mediadata.h"

MediaData::MediaData(QObject *parent) : QObject(parent) {}

QString MediaData::title() const { return m_title; }
QString MediaData::artist() const { return m_artist; }
QString MediaData::album() const { return m_album; }
QString MediaData::appName() const { return m_appName; }
double MediaData::duration() const { return m_duration; }
double MediaData::elapsed() const { return m_elapsed; }
bool MediaData::playing() const { return m_playing; }
AlbumArt MediaData::art() const { return m_art; }

void MediaData::setTitle(const QString &title) {
    if (m_title != title) {
        m_title = title;
        emit titleChanged();
    }
}

void MediaData::setArtist(const QString &artist) {
    if (m_artist != artist) {
        m_artist = artist;
        emit artistChanged();
    }
}

void MediaData::setAlbum(const QString &album) {
    if (m_album != album) {
        m_album = album;
        emit albumChanged();
    }
}

void MediaData::setAppName(const QString &appName) {
    if (m_appName != appName) {
        m_appName = appName;
        emit appNameChanged();
    }
}

void MediaData::setDuration(double duration) {
    if (!qFuzzyCompare(m_duration, duration)) {
        m_duration = duration;
        emit durationChanged();
    }
}

void MediaData::setElapsed(double elapsed) {
    if (!qFuzzyCompare(m_elapsed, elapsed)) {
        m_elapsed = elapsed;
        emit elapsedChanged();
    }
}

void MediaData::setPlaying(bool playing) {
    if (m_playing != playing) {
        m_playing = playing;
        emit playingChanged();
    }
}

void MediaData::setArt(const AlbumArt &art) {
    if (m_art != art) {
        m_art = art;
        emit artChanged();
    }
}
