// file che raccoglie le librerie incluse e necessarie al funzionamento del programma
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <random>
#include <filesystem>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QByteArray>
#include <fstream>
// #include <sstream>
// standard keywords utilizzate
// funzioni matematiche
using std::acos; // arcocoseno
using std::max;
using std::min;
using std::sin; // seno
// generatori randomici
using std::default_random_engine;
using std::random_device;
// distribuzioni utilizzate
using std::lognormal_distribution;
using std::normal_distribution;
using std::poisson_distribution;
using std::uniform_real_distribution;
// keywords
using std::cerr;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::ostream;
using std::istreambuf_iterator;
using std::filesystem::remove;
using std::filesystem::exists;
using std::string;
using std::to_string;
using std::vector;
// using std::stringstream;
// using std::setw;