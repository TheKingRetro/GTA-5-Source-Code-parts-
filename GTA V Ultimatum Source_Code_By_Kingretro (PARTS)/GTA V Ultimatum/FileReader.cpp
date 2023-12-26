#include "stdafx.h"

YAML::Node MyYAML::Settings;
std::fstream MyYAML::SettingsFile;
const char* MyYAML::Filename;

BOOLEAN MyYAML::Initialized = FALSE;
INT MyYAML::LSaveTick = 0;
INT MyYAML::CSaveTick = 0;