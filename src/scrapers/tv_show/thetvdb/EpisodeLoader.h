#pragma once

#include "globals/Globals.h"
#include "scrapers/tv_show/thetvdb/ApiRequest.h"
#include "tv_shows/TvShowEpisode.h"

#include <QNetworkAccessManager>
#include <QObject>
#include <QString>
#include <QUrl>
#include <QVector>

namespace thetvdb {

/**
 * @brief The EpisodeLoader is responsible for loading a *single* episode.
 */
class EpisodeLoader : public QObject
{
    Q_OBJECT

public:
    /**
     * @param showId      Show's TheTvDb id. Used when the episode's id is not valid.
     * @param episode     Episode to store data in.
     * @param language    TheTvDb's language key.
     * @param infosToLoad Information that should be loaded from TheTvDb
     * @param parent      Parent QObject that owns this instance.
     */
    EpisodeLoader(TvDbId showId,
        TvShowEpisode& episode,
        QString language,
        QSet<ShowScraperInfos> infosToLoad,
        QObject* parent = nullptr);

    static const QSet<ShowScraperInfos> scraperInfos;

    void loadData();

signals:
    void sigLoadDone();

private:
    QNetworkAccessManager m_qnam;
    QSet<ShowScraperInfos> m_loaded;

    TvDbId m_showId;
    TvShowEpisode& m_episode;
    ApiRequest m_apiRequest;
    QSet<ShowScraperInfos> m_infosToLoad;

    void loadSeason();
    void loadEpisode();
    void emitLoaded();
    QUrl getEpisodeUrl() const;
    QUrl getSeasonUrl() const;
};


} // namespace thetvdb
