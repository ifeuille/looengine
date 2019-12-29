
#ifndef LOOREFLECT_REFLECTED_ENUM_HPP
#define LOOREFLECT_REFLECTED_ENUM_HPP
#pragma once

#include "annotations.h"
#include "utils.h"

class ReflectedEnum {
public:
  ReflectedEnum(EnumDecl const *rec) : m_record(rec) {}


  void Generate(ASTContext *ctx, raw_ostream &os);

  void AddConstantDecl(EnumConstantDecl const *consDecl) {
    m_constnatDecls.push_back(consDecl);
  }


  PropertyAnnotations GenerateEnumValueAttributes(StringRef const &attr);

private:
  template <class T> Attr *GetAnnotateAttr(T *decl) {
    for (auto &attr : decl->attrs()) {
      if (attr->getKind() == attr::Annotate) {
        return attr;
      }
    }
    return nullptr;
  }

  template <unsigned N>
  StringRef GetAnnotations(Attr const *attr, SmallString<N> &str) {
    str.clear();
    raw_svector_ostream os(str);
    LangOptions langopts;
    PrintingPolicy policy(langopts);
    attr->printPretty(os, policy);
    return str.slice(26, str.size() - 4);
  }

  template <class Lambda>
  bool ForEachProperty(StringRef const &annotations, Lambda &&lambda) {
    auto pair = annotations.split(',');
    if (pair.first.size() == 0)
      return true;
    if (!lambda(pair.first.trim()))
      return false;
    return ForEachProperty(pair.second, static_cast<Lambda &&>(lambda));
  }

private:
  EnumDecl const *const m_record;
  std::vector<clang::EnumConstantDecl const *> m_constnatDecls;
};

#endif
