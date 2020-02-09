#include "fieldgenerator.h"
#include "functiongenerator.h"
#include "looreflectedclass.h"
#include "utils.h"
template<int N>
void GenerateGlobalRegisterClass(SmallString<N>& str, raw_ostream &os)
{
  std::string s = str.c_str();
  GetClassNameBaseNSName(s);
  s.append("_GlobalRegister");
  os << "#ifndef __LOOREFLECT__\n";
  os << "struct " << s.c_str()<< "{\n";
  //constructor
  os << s.c_str() << "(){\n";
  os << "looreflect::LooReflectManager::get().regist_type(";
  os << "looreflect::LooGetClass<" << str << ">()";
  os << ",REAL_MODULE_NAME);\n}\n";
  //destructor
  os << "~"<< s.c_str() << "(){\n";
  os << "looreflect::LooReflectManager::get().remove_type(";
  os << "looreflect::Hash(\"" << str << "\")";
  os << ",REAL_MODULE_NAME);\n}\n";

  os << "};\n"; 
  os << s.c_str() << " s_" << s.c_str() << ";\n";

  os << "#endif\n";
}

void ReflectedClass::Generate(ASTContext *ctx, raw_ostream &os, raw_ostream &os_private) {
  SmallString<256> str;
  SmallString<256> type;
  bool nobase = true;
  SmallString<256> basetype = "const_cast<LooClass*>(LooGetClass<";
  raw_svector_ostream stos(type);
  m_record->printQualifiedName(stos);

  /* Verify CLASS annotation. */
  for (auto &attr : m_record->attrs()) {
    if (attr->getKind() == attr::Annotate) {
      auto ref = GetAnnotations(attr, str);
      assert(ref.startswith("loo-class") && "incorrect annotation");
    }
  }

  /* File header: */
  os << "/* this file is auto-generated. do not edit! */\n";
  os << "#pragma once\n";
  os << "#include \"looreflect/looreflect.h\"\n";
  os << "#ifndef __LOOREFLECT__\n";
  os << "#include \"looreflect/looreflectmanager.h\"\n";
  os << "#endif\n";
  os << "namespace looreflect\n{\n\n";

  SmallVector<PropertyAnnotations, 8> propertyAnnotations;
  SmallVector<FunctionAnnotations, 8> functionAnnotations;
  if (m_record->bases_begin() != nullptr) {
    auto bases = m_record->bases();
    for (auto it : bases) {
      auto baseTypePtr = it.getType().getTypePtr();
      if (baseTypePtr) {
        auto parentdecl = baseTypePtr->getAsCXXRecordDecl();
        if (parentdecl) {
          //只反射可反射的类,且第一个
          for (auto &attr : parentdecl->attrs()) {
            if (attr->getKind() == attr::Annotate) {
              auto ref = GetAnnotations(attr, str);
              if (ref.startswith("loo-class")) {
                nobase = false;
                break;
              }
            }
          }

          if (!nobase) {
            raw_svector_ostream stos_parent(basetype);
            parentdecl->printQualifiedName(stos_parent);
            basetype.append(">())");
            nobase = false;
            break;
          }
        }
      }
    }
  }

  /* Generate PROPERTY annotations. */
  for (auto &field : m_fields) {
    Attr *attr = GetAnnotateAttr(field);
    assert(attr != nullptr);
    propertyAnnotations.push_back(
        GenerateFieldAttributes(GetAnnotations(attr, str)));
  }

  /* Generate FUNCTION annotations. */
  for (auto &func : m_functions) {
    Attr *attr = GetAnnotateAttr(func);
    assert(attr != nullptr);
    functionAnnotations.push_back(
        GenerateFunctionAttributes(GetAnnotations(attr, str)));
  }

  /* Mark class as serializable if one or more fields are serialized. */
  ClassAnnotations classFlags;
  classFlags.isSerializable =
      std::any_of(propertyAnnotations.begin(), propertyAnnotations.end(),
                  [](PropertyAnnotations &v) { return v.serialized; });
  classFlags.hasBeforeSerialize = HasFunctionOfName("BeforeSerialize");
  classFlags.hasAfterSerialize = HasFunctionOfName("AfterSerialize");
  classFlags.hasCustomSerialize = HasFunctionOfName("Serialize");
  classFlags.hasCustomDump = HasFunctionOfName("dump");
  os << "template<> struct IsSerializable<" << type
     << "> { static constexpr bool value = "
     << (classFlags.isSerializable ? "true" : "false") << "; };\n";

  os << "template<> struct HasBeforeSerialize<" << type
     << "> { static constexpr bool value = "
     << (classFlags.hasBeforeSerialize ? "true" : "false") << "; };\n";

  os << "template<> struct HasAfterSerialize<" << type
     << "> { static constexpr bool value = "
     << (classFlags.hasAfterSerialize ? "true" : "false") << "; };\n";

  os << "template<> struct HasCustomSerialize<" << type
     << "> { static constexpr bool value = "
     << (classFlags.hasCustomSerialize ? "true" : "false") << "; };\n";

  os << "template<> struct HasCustomDump<" << type
     << "> { static constexpr bool value = "
     << (classFlags.hasCustomDump ? "true" : "false") << "; };\n";

  os << "namespace detail\n{\n";

  /* GetClass function */
  /* os << "template<> struct ClassResolver<" << type << ">;\n"; */
  os << "template<>\n"
     << "inline LooClass const *\n"
     /* << "ClassResolver<" << type << ">::Get() noexcept\n" */
     /* << "GetClass<" << type << ">() noexcept\n" */
     << "LooGetClassImpl(LooClassTag<" << type << ">) noexcept\n"
     << "{\n"
     << "static detail::LooClassBuilder<" << type << ", " << m_fields.size()
     << ", " << m_functions.size() << ">"
     << " reflected([](auto self) {\n";

  /* Fields */
  FieldGenerator fieldGenerator(ctx, type, "self->fields");
  for (unsigned i = 0, n = m_fields.size(); i < n; ++i)
    fieldGenerator.Generate(i, m_fields[i], propertyAnnotations[i], os);

  /* Functions */
  FunctionGenerator funcGenerator(ctx, type, "self->functions");
  for (unsigned i = 0, n = m_functions.size(); i < n; ++i)
    funcGenerator.Generate(i, m_functions[i], functionAnnotations[i], os);

  os << "});\n"
     << "static LooClass cache(\n"
     << "sizeof(" << type << "),\n"
     << "Hash(\"" << type << "\"),\n"
     << (nobase ? "nullptr" : basetype.c_str())
     << ",\n" // nullptr/*TODO: baseclass*/,\n"
     << "reflected.fields,\n"
     << "reflected.fields + reflected.numFields,\n"
     << "reflected.functions,\n"
     << "reflected.functions + reflected.numFunctions,\n"
     << "\"" << type << "\",\n"
     << classFlags.Flags() << ");\n"
     << "return &cache;\n";
  os << "}\n\n";

  /* GetType function */
  /* os << "template<> struct TypeResolver<" << type << ">;\n"; */
  os << "template<>\n"
     << "inline LooType const *\n"
     /* << "TypeResolver<" << type << ">::Get() noexcept\n" */
     /* << "GetType<" << type << ">() noexcept\n" */
     << "LooGetTypeImpl(LooTypeTag<" << type << ">) noexcept\n"
     << "{\n"
     /* << "return ClassResolver<" << type << ">::Get();\n" */
     << "return LooGetClass<" << type << ">();\n"
     << "}\n";
  

  os << "} /* namespace detail */\n";
  os << "} /* namespace looreflect */\n\n";

  os << "// utils functions for class instance\n";
  os << "const looreflect::LooType *" << type << "::GetType() const { ";
  os << "return looreflect::LooGetClass<" << type<<">();}\n\n";

  //private
	os_private << "namespace looreflect\n{\n\n";
	os_private << "namespace detail\n{\n\n";
	GenerateGlobalRegisterClass(type, os_private);
	os_private << "} /* namespace detail */\n";
	os_private << "} /* namespace looreflect */\n\n";
}

    /* ========================================================================= */
/* Generator                                                                 */
/* ========================================================================= */
PropertyAnnotations
ReflectedClass::GenerateFieldAttributes(StringRef const &attr) {
  assert(attr.startswith("loo-property") && "incorrect annotation");
  auto pair = attr.split(";");

  PropertyAnnotations ret;
  auto setAttributes = [&ret](StringRef const &s) -> bool {
    if (s.equals_lower("serialized")) {
      return (ret.serialized = true);

    } else if (s.startswith_lower("width")) {
      size_t idx = s.find_first_of('=');
      auto sref = s.substr(idx + 1);
      unsigned width;
      sref.getAsInteger(10, width);
      ret.width = width;
      return true;

    } else if (s.equals_lower("cstring")) {
      return (ret.isCString = true);
    }

    return false;
  };

  ForEachProperty(pair.second, setAttributes);
  return ret;
}

FunctionAnnotations
ReflectedClass::GenerateFunctionAttributes(StringRef const &attr) {
  assert(attr.startswith("loo-function") && "incorrect annotation");
  auto pair = attr.split(";");

  FunctionAnnotations ret;
  auto setAttributes = [&ret](StringRef const &s) -> bool {
    if (s.equals_lower("replicated")) {
      return (ret.replicated = true);
    }

    return false;
  };

  ForEachProperty(pair.second, setAttributes);
  return ret;
}
