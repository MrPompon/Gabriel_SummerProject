// stdafx.h

#pragma once

#include <SDKDDKVer.h>
#include <stdio.h>

/* c++ headers */
#include <cassert>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <vld.h>
/* sfml headers and libraries */
#include <SFML/Main.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#if !defined(NDEBUG)
#	pragma comment(lib, "sfml-main-d.lib")
#	pragma comment(lib, "sfml-system-d.lib")
#	pragma comment(lib, "sfml-window-d.lib")
#	pragma comment(lib, "sfml-graphics-d.lib")
#	pragma comment(lib, "sfml-audio-d.lib")
#else
#	pragma comment(lib, "sfml-main.lib")
#	pragma comment(lib, "sfml-system.lib")
#	pragma comment(lib, "sfml-window.lib")
#	pragma comment(lib, "sfml-graphics.lib")
#	pragma comment(lib, "sfml-audio.lib")
#endif

/* engine specific includes */
#include "Math.hpp"
#include "Action.hpp"
