/*
  A black/white List checker disabler
*/

#ifndef BLACK_WHITE_LIST_CHECKER_DISABLER_H
#define BLACK_WHITE_LIST_CHECKER_DISABLER_H

#include <clang/StaticAnalyzer/Core/BugReporter/BugReporter.h>
#include <clang/StaticAnalyzer/Core/PathSensitive/CheckerContext.h>
#include <fnmatch.h>
#include "jsonxx.h"
#include <regex>

class BlackWhiteListCheckerDisabler {
   bool PathWildCardMatch(jsonxx::Array &, const std::string &) const;
   bool RegexMatch(jsonxx::Array &, const std::string &) const;
   bool PrefixMatch(jsonxx::Array &, const std::string &) const;
   bool ParseBlackWhiteField(std::string &) const;
   bool CheckBlackWhiteListConfiguration() const;
   void WalkDeclContext(const clang::DeclContext *);

   const clang::SourceLocation sLoc;
   std::string checker;
   std::string struct_name;
   std::string class_name;
   std::string namespace_name;
   llvm::StringRef relPath;

public:
   BlackWhiteListCheckerDisabler(const clang::Decl *,
                                 const char *,
                                 clang::ento::BugReporter &,
                                 const clang::SourceLocation &);

   BlackWhiteListCheckerDisabler(clang::ento::CheckerContext &C,
                                 const char *checker,
                                 clang::ento::BugReporter &BR,
                                 const clang::SourceLocation &sLoc);
   bool isDisabled();

};

#endif
