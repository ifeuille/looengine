#ifndef LOOREFLECT_UTILS_H
#define LOOREFLECT_UTILS_H
#pragma once
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/Frontend/FrontendAction.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "llvm/Support/CommandLine.h"
#include <algorithm>
#include <string>

using namespace llvm;
using namespace clang;
using namespace clang::tooling;
using namespace clang::ast_matchers;

inline bool ends_with(std::string const &value, std::string const &ending) {
  if (ending.size() > value.size()) {
    return false;
  }
  return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

// Get qual type
QualType GetDesugaredType(ASTContext *ctx, QualType t);

inline void GetRealTypeName(ASTContext *ctx, QualType t, raw_ostream &os) {
  QualType retType = GetDesugaredType(ctx, t);
  retType.print(os, ctx->getPrintingPolicy());
}

SmallString<32> GenerateQualifier(ASTContext *ctx, QualType type);

SmallString<8> PrintfFormatForType(ASTContext *ctx, QualType t);

template <unsigned N>
inline StringRef GetAttrValue(Attr const *attr, SmallString<N> &str) {
  str.clear();
  raw_svector_ostream os(str);
  LangOptions langopts;
  PrintingPolicy policy(langopts);
  attr->printPretty(os, policy);
  return str.slice(26, str.size() - 4);
}

inline bool RecordStartAttr(RecordDecl const *decl, clang::attr::Kind kind,
                            const std::string &str) {
  for (auto &attr : decl->attrs()) {
    if (attr->getKind() == kind) {
      SmallString<64> str;
      auto ref = GetAttrValue(attr, str);
      if (ref.startswith(str)) {
        return true;
      }
    }
  }
  return false;
}

/*
a::b::c
=>a_b_c
 */
inline void GetClassNameBaseNSName(std::string &str) {
  for (auto it = str.begin(); it != str.end(); ++it) {
    if (*it == ':') {
      *it = 'g';
	}
  }
}


#endif