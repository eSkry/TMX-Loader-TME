#ifndef TMXL_AUTOSWITCHLOADER
#define TMXL_AUTOSWITCHLOADER

#include "TMXL/Parsers/IParser.h"
#include "TMXL/Map/NodeObject.h"
#include "TMXL/System/Logger.h"

#include <memory>
#include <string>
#include <map>

namespace TMXL {

    class AutoSwitchLoader {
    public:

        void registerParser(const std::string& type, std::shared_ptr<IParser> parser);

        std::shared_ptr<NodeObject> parser(const std::string& fileName);

    private:
        std::map<std::string, std::shared_ptr<IParser>> mParsers;
    };

}

#endif // TMXL_AUTOSWITCHLOADER