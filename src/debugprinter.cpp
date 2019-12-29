#include "debugprinter.h"
#define VERBOSITY 2

void DebugPrinter::printDebug(std::string source, std::string debugmsg, int verbosity) {
  if (verbosity <= VERBOSITY) {
    std::cout << source << ": " << debugmsg << std::endl;
  }
}

void DebugPrinter::saveDebug(std::string source, std::string debugmsg, std::string filename) {
  std::ofstream f;
  f.open(filename);
  if (f) {
    f << source << ": " << debugmsg << std::endl;
    f.close();
  } else {
    std::stringstream ss;
    ss << "Error opening file " << filename << " to save debug log from " << source << std::endl;
    printDebug("DebugPrinter::saveDebug", ss.str(), 1);
    return;
  }
}
