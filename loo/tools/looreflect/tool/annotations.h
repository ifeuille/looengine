#ifndef LOOREFLECT_ANNOTATIONS_H
#define LOOREFLECT_ANNOTATIONS_H
#pragma once
#include "utils.h"
struct ClassAnnotations {
  ClassAnnotations()
      : isSerializable(0), hasBeforeSerialize(0), hasAfterSerialize(0),
        hasCustomSerialize(0), hasCustomDump(0) {}

  bool isSerializable : 1;
  bool hasBeforeSerialize : 1;
  bool hasAfterSerialize : 1;
  bool hasCustomSerialize : 1;
  bool hasCustomDump : 1;

  struct FlagPrinter {
    ClassAnnotations const *annotations;

    explicit FlagPrinter(ClassAnnotations const *ref) : annotations(ref) {}
  };

  FlagPrinter Flags() const noexcept { return FlagPrinter{this}; }
};

inline raw_ostream &operator<<(raw_ostream &os, ClassAnnotations::FlagPrinter const &p) {
  os << "LooClass::kFlagsNull";
  if (p.annotations->hasBeforeSerialize)
    os << " | LooClass::kFlagsHasBeforeSerialize";
  if (p.annotations->hasAfterSerialize)
    os << " | LooClass::kFlagsHasAfterSerialize";
  if (p.annotations->hasCustomSerialize)
    os << " | LooClass::kFlagsHasCustomSerialize";
  if (p.annotations->hasCustomDump)
    os << " | LooClass::kFlagsHasCustomDump";
  return os;
}

struct PropertyAnnotations {
  PropertyAnnotations() : serialized(false), width(0), hasTagName(false) {}

  bool serialized : 1;
  bool isCString : 1;
  bool hasTagName : 1;
  unsigned width : 8;
  SmallString<64> tagName;

  bool IsSerializable(ASTContext *ctx, FieldDecl const *field) {
    auto t = GetDesugaredType(ctx, field->getType());
    if (!t.isPODType(*ctx) && serialized)
      return false;
    return true;
  }

  struct FlagPrinter {
    PropertyAnnotations const *annotations;

    explicit FlagPrinter(PropertyAnnotations const *ref) : annotations(ref) {}
  };

  FlagPrinter Flags() const noexcept { return FlagPrinter{this}; }
};

inline raw_ostream &operator<<(raw_ostream &os,
                               PropertyAnnotations::FlagPrinter const &p) {
  os << "LooField::kFlagsNull";
  if (p.annotations->serialized)
    os << " | LooField::kFlagsSerialized";
  if (p.annotations->isCString)
    os << " | LooField::kFlagsCString";
  return os;
}

struct FunctionAnnotations {
  FunctionAnnotations() : replicated(false), memberFunc(false) {}

  bool replicated : 1;
  bool memberFunc : 1;

  struct FlagPrinter {
    FunctionAnnotations const *annotations;

    explicit FlagPrinter(FunctionAnnotations const *ref) : annotations(ref) {}
  };

  FlagPrinter Flags() const noexcept { return FlagPrinter{this}; }
};

inline raw_ostream &operator<<(raw_ostream &os,
                               FunctionAnnotations::FlagPrinter const &p) {
  os << "LooFunction::kFlagsNull";
  if (p.annotations->replicated)
    os << " | LooFunction::kFlagsReplicated";
  if (p.annotations->memberFunc)
    os << " | LooFunction::kFlagsMember";
  return os;
}


#endif