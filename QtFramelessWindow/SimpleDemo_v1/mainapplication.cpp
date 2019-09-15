#include "mainapplication.h"
#include <QtWidgets>

class MainApplication::MainApplicationPrivate
{
public:
    QString appName = QStringLiteral("SimpleDemo");
    QString appVersion = QStringLiteral("0.1");
    QString orgDomain = QStringLiteral("com.demo");
    QString orgName = QStringLiteral("demo");

    QTranslator qtTranslator;
    QTranslator appTranslator;
};

MainApplication::MainApplication(int &argc, char** argv)
    : QApplication(argc, argv), d(new MainApplicationPrivate)
{
    setApplicationName(d->appName);
    setApplicationVersion(d->appVersion);
    setOrganizationDomain(d->orgDomain);
    setOrganizationName(d->orgName);

    const auto systemLocale = QLocale::system().name();

    if (d->appTranslator.load(":/" + systemLocale)) {
        this->installTranslator(&d->appTranslator);
    }

    if (d->qtTranslator.load(":/qt_" + systemLocale)) {
        this->installTranslator(&d->qtTranslator);
    }

    auto font = this->font();
    font.setFamily(QStringLiteral("Microsoft YaHei UI"));
    if (QFontInfo(font).family() != "Microsoft YaHei UI") {
        font.setFamily("Microsoft YaHei");
    }
    this->setFont(font);
}

MainApplication::~MainApplication() {}
