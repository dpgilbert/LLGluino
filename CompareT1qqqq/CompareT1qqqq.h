#ifndef COMPARET1QQQQ_H
#define COMPARET1QQQQ_H

#include <iostream>
#include <vector>
#include <map>
#include <cmath>

#include "TH1.h"

#include "../CORE/Tools/utils.h"
#include "../CORE/Tools/goodrun.h"
#include "../CORE/Tools/dorky/dorky.h"
#include "../CORE/Tools/badEventFilter.h"

#include "../MT2CORE/mt2tree.h"
#include "../MT2CORE/sigSelections.h"
#include "../MT2CORE/SR.h"

class CompareT1qqqq {
 public:
  CompareT1qqqq();
  ~CompareT1qqqq();

  void loop (const TChain* chain, const char* sample, const char* outdir, const int maxEvt);
};

#endif
