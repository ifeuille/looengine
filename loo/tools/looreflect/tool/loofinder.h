
#ifndef LOOREFLECT_CLASSFINDER_HPP
#define LOOREFLECT_CLASSFINDER_HPP
#pragma once

#include "looreflectedclass.h"
#include "looreflectedenum.h"
#include "utils.h"
#include "clang/Basic/FileManager.h"

class LooFinder : public MatchFinder::MatchCallback {
public:
  struct OneFileDesc {
    std::string m_fileName;
    std::string m_fileNamePrivate;
    std::vector<ReflectedClass> m_classes;
    std::vector<ReflectedEnum> m_enumes;
  };

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
#if 0
    std::error_code ec;
    raw_fd_ostream os(m_fileName, ec, sys::fs::F_None);
    printf("%s", m_fileName.c_str());
    assert(!ec && "error opening file");

    raw_fd_ostream os_private(m_fileNamePrivate, ec, sys::fs::F_None);
    printf("%s", m_fileNamePrivate.c_str());
    assert(!ec && "error opening file");

    for (auto &ref : m_classes)
      ref.Generate(m_context, os, os_private);
    for (auto &ref : m_enumes)
      ref.Generate(m_context, os, os_private);

#else
	for (auto it = m_filedescs.begin(); it != m_filedescs.end(); ++it) {
      std::error_code ec;
      OneFileDesc &desc = it->second;
      raw_fd_ostream os(desc.m_fileName, ec, sys::fs::F_None);
      printf("%s", desc.m_fileName.c_str());
      assert(!ec && "error opening file");

      raw_fd_ostream os_private(desc.m_fileNamePrivate, ec, sys::fs::F_None);
      printf("%s", desc.m_fileNamePrivate.c_str());
      assert(!ec && "error opening file");

      for (auto &ref : desc.m_classes)
        ref.Generate(m_context, os, os_private);
      for (auto &ref : desc.m_enumes)
        ref.Generate(m_context, os, os_private);
    }
#endif
  }

protected:
  void FoundRecord(CXXRecordDecl const *record) {
    //   m_fileName = m_sourceman->getFilename(record->getLocation());
    //   m_fileName.erase(m_fileName.end() - 2, m_fileName.end());
    //   m_fileName.append(".loogen.h");
    //   m_fileNamePrivate = m_sourceman->getFilename(record->getLocation());
    //   m_fileNamePrivate.erase(m_fileNamePrivate.end() -
    //   2,m_fileNamePrivate.end());
    // m_fileNamePrivate.append(".loogenprivate.h");
#if 0
    m_classes.emplace_back(ReflectedClass(record));
    SetFileDirs(m_sourceman->getFilename(record->getLocation()));
#else
    auto filename = m_sourceman->getFilename(record->getLocation());
    OneFileDesc &desc = GetOneFileDesc(filename);
    desc.m_classes.emplace_back(ReflectedClass(record));
#endif
  }

  void FoundField(FieldDecl const *field) {
#if 0
	  m_classes.back().AddField(field);
#else
    auto filename = m_sourceman->getFilename(field->getLocation());
    OneFileDesc &desc = GetOneFileDesc(filename);
    desc.m_classes.back().AddField(field);
#endif
  }

  void FoundFunction(FunctionDecl const *function) {
#if 0
    m_classes.back().AddFunction(function);
#else
    auto filename = m_sourceman->getFilename(function->getLocation());
    OneFileDesc &desc = GetOneFileDesc(filename);
    desc.m_classes.back().AddFunction(function);
#endif
  }

  void FoundEnum(EnumDecl const *em) {
#if 0
    m_enumes.push_back(em);
    SetFileDirs(m_sourceman->getFilename(em->getLocation()));
#else
    auto filename = m_sourceman->getFilename(em->getLocation());
    OneFileDesc &desc = GetOneFileDesc(filename);
    desc.m_enumes.push_back(em);
#endif
    //   m_fileName = m_sourceman->getFilename(em->getLocation());
    //   m_fileName.erase(m_fileName.end() - 2, m_fileName.end());
    //   m_fileName.append(".loogen.h");
    //
    // m_fileNamePrivate = m_sourceman->getFilename(em->getLocation());
    //   m_fileNamePrivate.erase(m_fileNamePrivate.end() -
    //   2,m_fileNamePrivate.end());
    // m_fileNamePrivate.append(".loogenprivate.h");
  }

  void FoundConstantEnum(EnumConstantDecl const *em) {
#if 0
	      m_enumes.back().AddConstantDecl(em);
#else
    auto filename = m_sourceman->getFilename(em->getLocation());
    OneFileDesc &desc = GetOneFileDesc(filename);
    desc.m_enumes.back().AddConstantDecl(em);
#endif
  }

#if 0
  void SetFileDirs(llvm::StringRef str) {
    fs::path path(str.str());
    auto dir = path.parent_path();
    auto name = path.filename();
    auto generatedir = dir / "generate";
    if (!fs::exists(generatedir)) {
      fs::create_directory(generatedir);
    }
    auto ext = name.extension();
    auto apdname = name.stem();
    apdname = apdname.generic_string() + (".loo") + ext.generic_string();
    m_fileName = (generatedir / apdname).generic_string();
    auto priname = name.stem();
    priname = priname.generic_string() + (".looprivate") + ext.generic_string();
    m_fileNamePrivate = (generatedir / priname).generic_string();
  }
#endif

private:
  LooFinder::OneFileDesc &GetOneFileDesc(llvm::StringRef filename) {
    auto it = m_filedescs.find(filename);
    if (it == m_filedescs.end()) {
      OneFileDesc &desc = m_filedescs[filename];
      fs::path path(filename.str());
      auto dir = path.parent_path();
      auto name = path.filename();
      auto generatedir = dir / "generate";
      if (!fs::exists(generatedir)) {
        fs::create_directory(generatedir);
      }
      auto ext = name.extension();
      auto apdname = name.stem();
      apdname = apdname.generic_string() + (".loo") + ext.generic_string();
      desc.m_fileName = (generatedir / apdname).generic_string();
      auto priname = name.stem();
      priname =
          priname.generic_string() + (".looprivate") + ext.generic_string();
      desc.m_fileNamePrivate = (generatedir / priname).generic_string();

      return desc;
    }
    return m_filedescs[filename];
  }

protected:
  ASTContext *m_context;
  SourceManager *m_sourceman;
#if 0
  std::vector<ReflectedClass> m_classes;
  std::vector<ReflectedEnum> m_enumes;
  std::string m_fileName;
  std::string m_fileNamePrivate;
#endif
  std::unordered_map<std::string, OneFileDesc> m_filedescs;

  SmallString<64> str;
};

#endif /* METAREFLECT_CLASSFINDER_HPP */
