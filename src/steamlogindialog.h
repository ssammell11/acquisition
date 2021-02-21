/*
    Copyright 2014 Ilya Zhuravlev

    This file is part of Acquisition.

    Acquisition is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Acquisition is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Acquisition.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <QDialog>
#include <QNetworkCookie>
#include <QNetworkAccessManager>
#include <memory>
#if defined(USE_WEBENGINE)
#include <QWebEngineView>
#elif defined(USE_WEBKIT)
class QWebView;
#endif

namespace Ui {
class SteamLoginDialog;
}

class QCloseEvent;

class SteamLoginDialog : public QDialog {
    Q_OBJECT
public:
    explicit SteamLoginDialog(QWidget *parent = 0);
    ~SteamLoginDialog();
    void Init();
signals:
    void CookieReceived(const QString &cookie);
    void Closed();
protected:
    virtual void closeEvent(QCloseEvent *e);
private:
    Ui::SteamLoginDialog *ui;
    bool completed_;

#if defined(USE_WEBENGINE)
    QWebEngineView* webView;
    QNetworkAccessManager network_manager_;
#elif defined(USE_WEBKIT)
    void SetSteamCookie(QNetworkCookie);
    void SaveSteamCookie(QNetworkCookie);
    QNetworkCookie LoadSteamCookie();

    std::string settings_path_;
    QWebView *webkitView;
private slots:
    void OnLoadFinished();
#endif
};
