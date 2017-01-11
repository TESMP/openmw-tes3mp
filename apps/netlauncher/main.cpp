#include <QApplication>
#include <components/settings/settings.hpp>
#include <components/files/configurationmanager.hpp>
#include "Main.hpp"
#include "NetController.hpp"

std::string loadSettings (Settings::Manager & settings)
{
    Files::ConfigurationManager mCfgMgr;
    // Create the settings manager and load default settings file
    const std::string localdefault = (mCfgMgr.getLocalPath() / "tes3mp-client-default.cfg").string();
    const std::string globaldefault = (mCfgMgr.getGlobalPath() / "tes3mp-client-default.cfg").string();

    // prefer local
    if (boost::filesystem::exists(localdefault))
        settings.loadDefault(localdefault);
    else if (boost::filesystem::exists(globaldefault))
        settings.loadDefault(globaldefault);
    else
        throw std::runtime_error ("No default settings file found! Make sure the file \"tes3mp-client-default.cfg\" was properly installed.");

    // load user settings if they exist
    const std::string settingspath = (mCfgMgr.getUserConfigPath() / "tes3mp-client.cfg").string();
    if (boost::filesystem::exists(settingspath))
        settings.loadUser(settingspath);

    return settingspath;
}

int main(int argc, char *argv[])
{
    Settings::Manager mgr;
    Files::ConfigurationManager cfgMgr;

    loadSettings(mgr);

    std::string addr = mgr.getString("address", "Master");
    int port = mgr.getInt("port", "Master");

    // initialize resources, if needed
    // Q_INIT_RESOURCE(resfile);

    NetController::Create(addr, port);
    atexit(NetController::Destroy);
    QApplication app(argc, argv);
    Main d;
    d.show();
    // create and show your widgets here
    return app.exec();
}