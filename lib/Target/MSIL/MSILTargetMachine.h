//===-- MSILTargetMachine.h - TargetMachine for the MSIL backend *- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file declares the TargetMachine that is used by the MSIL backend.
//
//===----------------------------------------------------------------------===//

#ifndef MSILTARGETMACHINE_H
#define MSILTARGETMACHINE_H
#include "llvm/ADT/Triple.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {

class formatted_raw_ostream;

struct MSILTargetMachine : public TargetMachine {

  const DataLayout DL;	

    static std::string computeDataLayout(StringRef TT, StringRef CPU, StringRef FS, 
	                                   const TargetOptions &Options){
	Triple TargetTriple(TT);
	std::string Ret = "e";
	Ret += DataLayout::getManglingComponent(TargetTriple);

    Ret += "-p:32:32";

    Ret += "-i64:64";

    Ret += "-f80:32";

    Ret += "-n8:16:32";

	Ret += "-S32";
	return Ret;

  }

  MSILTargetMachine(const Target &T, StringRef TT,
                   StringRef CPU, StringRef FS, const TargetOptions &Options,
                   Reloc::Model RM, CodeModel::Model CM,
                   CodeGenOpt::Level OL)
    : TargetMachine(T, TT, CPU, FS, Options), DL(computeDataLayout(TT,CPU,FS,Options)){
		
  }

  virtual void addAnalysisPasses(PassManagerBase &) override;

  virtual bool addPassesToEmitFile(PassManagerBase &PM,
                                   formatted_raw_ostream &Out,
                                   CodeGenFileType FileType,
                                   bool DisableVerify,
                                   AnalysisID StartAfter,
                                   AnalysisID StopAfter) override;

  virtual const DataLayout *getDataLayout() const { return &DL; }
};

extern Target TheMSILTarget;

} // End llvm namespace


#endif
