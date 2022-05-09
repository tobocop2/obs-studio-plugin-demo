#pragma once
#include <QString>
#include <QWidget>
#include <functional>
#include <string>
#include <util/util.hpp>

#define FN_EXTERN extern
#ifdef _MSC_VER
#define FN_IMPORT __declspec(dllimport)
#define FN_HIDE
#else
#define FN_IMPORT
#define FN_HIDE __attribute__((visibility("hidden")))
#endif

struct FN_HIDE QCefCookieManager {
    virtual ~QCefCookieManager() {}

    virtual bool DeleteCookies(const std::string &url,
                               const std::string &name) = 0;

    virtual bool SetStoragePath(const std::string &storage_path,
                                bool persist_session_cookies = false) = 0;

    virtual bool FlushStore() = 0;

    typedef std::function<void(bool)> cookie_exists_cb;

    virtual void CheckForCookie(const std::string &site,
                                const std::string &cookie,
                                cookie_exists_cb callback) = 0;
};

class FN_HIDE QCefWidget : public QWidget {
    Q_OBJECT

    protected:
        inline QCefWidget(QWidget* parent) : QWidget(parent) {}

    public:
        virtual void setURL(const std::string& url)              = 0;
        virtual void setStartupScript(const std::string& script) = 0;
        virtual void allowAllPopups(bool allow)                  = 0;
        virtual void closeBrowser()                              = 0;
        virtual void reloadPage()                                = 0;
};

struct FN_HIDE QCef {
    virtual ~QCef() {}

    virtual bool init_browser(void) = 0;
    virtual bool initialized(void) = 0;
    virtual bool wait_for_browser_init(void) = 0;

    virtual QCefWidget *
    create_widget(QWidget *parent, 
                  const std::string &url,
                  QCefCookieManager *cookie_manager = nullptr) = 0;

    virtual QCefCookieManager *
    create_cookie_manager(const std::string &storage_path,
                          bool persist_session_cookies = false) = 0;

    virtual BPtr<char> get_cookie_path(const std::string &storage_path) = 0;

    virtual void add_popup_whitelist_url(const std::string &url,
                         QObject *obj) = 0;
    virtual void add_force_popup_url(const std::string &url,
                                     QObject *obj) = 0;
};

namespace obs {
    namespace browser {
        FN_HIDE QCef* instance();

        FN_HIDE int version();
    } 
} 
