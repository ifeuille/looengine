
#ifndef LOOREFLECT_CLASSFINDER_HPP
#define LOOREFLECT_CLASSFINDER_HPP
#pragma once

#include "looreflectedclass.h"
#include "looreflectedenum.h"
#include "utils.h"

class LooFinder : public MatchFinder::MatchCallback {
public:
  template <unsigned N>
  StringRef GetAnnotations(Attr const *attr, SmallString<N> &str) {
    str.clear();
    raw_svector_ostream os(str);
    LangOptions langopts;
    PrintingPolicy policy(langopts);
    attr->printPretty(os, policy);
    return str.slice(26, str.size() - 4);
  }

  virtual void run(MatchFinder::MatchResult const &result) override {
    m_context = result.Context;
    m_sourceman = result.SourceManager;
    str.clear();

    CXXRecordDecl const *record =
        result.Nodes.getNodeAs<clang::CXXRecordDecl>("id");

    if (record /*&& RecordStartAttr(record, clang::attr::Annotate,"reflect-class")*/) {
      return FoundRecord(record);
    }

    FieldDecl const *field = result.Nodes.getNodeAs<clang::FieldDecl>("id");
    if (field)
      return FoundField(field);

    FunctionDecl const *function =
        result.Nodes.getNodeAs<clang::FunctionDecl>("id");
    if (function)
      return FoundFunction(function);

    // for enum
    EnumDecl const *enumDecl = result.Nodes.getNodeAs<clang::EnumDecl>("id");
    if (enumDecl)
      return FoundEnum(enumDecl);
    EnumConstantDecl const *constantDecl =
        result.Nodes.getNodeAs<clang::EnumConstantDecl>("id");
    if (constantDecl) {
      return FoundConstantEnum(constantDecl);
    }
  }

  virtual void onStartOfTranslationUnit() override {}

  virtual void onEndOfTranslationUnit() override {
    /* For stdout output. */
    /* raw_fd_ostream os(1, false); */
    std::error_code ec;
    raw_fd_ostream os(m_fileName, ec, sys::fs::F_None);
    printf("%s", m_fileName.c_str());
    assert(!ec && "error opening file");
    for (auto &ref : m_classes)
      ref.Generate(m_context, os);
    for (auto &ref : m_enumes)
      ref.Generate(m_context, os);
  }

protected:
  void FoundRecord(CXXRecordDecl const *record) {
    m_fileName = m_sourceman->getFilename(record->getLocation());
    m_fileName.erase(m_fileName.end() - 2, m_fileName.end());
    m_fileName.append(".loogen.h");
    m_classes.emplace_back(ReflectedClass(record));
  }

  void FoundField(FieldDecl const *field) { m_classes.back().AddField(field); }

  void FoundFunction(FunctionDecl const *function) {
    m_classes.back().AddFunction(function);
  }

  void FoundEnum(EnumDecl const *em) {
    m_fileName = m_sourceman->getFilename(em->getLocation());
    m_fileName.erase(m_fileName.end() - 2, m_fileName.end());
    m_fileName.append(".loogen.h");
    m_enumes.push_back(em);
  }

  void FoundConstantEnum(EnumConstantDecl const *em) {
    m_enumes.back().AddConstantDecl(em);
  }

protected:
  ASTContext *m_context;
  SourceManager *m_sourceman;
  std::vector<ReflectedClass> m_classes;
  std::vector<ReflectedEnum> m_enumes;
  std::string m_fileName;
  SmallString<64> str;
};

#endif /* METAREFLECT_CLASSFINDER_HPP */
