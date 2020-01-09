#include "enumconstantgenerator.h"
#include "looreflectedenum.h"
#include "utils.h"

template <int N>
void GenerateGlobalRegisterEnum(SmallString<N> &str, raw_ostream &os) {
  std::string s = str.c_str();
  GetClassNameBaseNSName(s);
  s.append("_GlobalRegister");
  os << "#ifndef __LOOREFLECT__\n";
  os << "struct " << s.c_str() << "{\n";

    // constructor
  os << s.c_str() << "(){\n";
  os << "looreflect::LooReflectManager::get().regist_type(";
  os << "looreflect::LooGetEnum<" << str << ">()";
  os << ",REAL_MODULE_NAME);\n}\n";
  // destructor
  os << "~" << s.c_str() << "(){\n";
  os << "looreflect::LooReflectManager::get().remove_type(";
  os << "looreflect::Hash(\"" << str << "\")";
  os << ",REAL_MODULE_NAME);\n}\n";

  os << "};\n"; 

  os << s.c_str() << " s_" << s.c_str() << ";\n";
  os << "#endif\n";
}
void ReflectedEnum::Generate(ASTContext *ctx, raw_ostream &os, raw_ostream &os_private) {
  if (m_constnatDecls.size() == 0) {
    return;
  }
  SmallString<64> str;
  SmallString<64> type;
  raw_svector_ostream stos(type);
  m_record->printQualifiedName(stos);

  /* File header: */
  os << "/* this file is auto-generated. do not edit! */\n";
  os << "#pragma once\n";
  os << "#include \"looreflect/looreflect.h\"\n";
  os << "#ifndef __LOOREFLECT__\n";
  os << "#include \"looreflect/looreflectmanager.h\"\n";
  os << "#endif\n";
  os << "namespace looreflect\n{\n\n";

  SmallVector<PropertyAnnotations, 8> propertyAnnotations;

    /* Verify ENUM annotation. */
  for (auto &attr : m_record->attrs()) {
	if (attr->getKind() == attr::Annotate) {
		auto ref = GetAnnotations(attr, str);
		assert(ref.startswith("loo-enum") && "incorrect annotation");
    }
  }

  for (auto &enumconstant : m_constnatDecls) {
    Attr *attr = GetAnnotateAttr(enumconstant);
    assert(attr != nullptr);
    propertyAnnotations.push_back(
        GenerateEnumValueAttributes(GetAnnotations(attr, str)));
  }

  /* Mark class as serializable if one or more fields are serialized. */
  ClassAnnotations classFlags;
  classFlags.isSerializable =
      std::any_of(propertyAnnotations.begin(), propertyAnnotations.end(),
                  [](PropertyAnnotations &v) { return v.serialized; });
  os << "template<> struct IsSerializable<" << type
     << "> { static constexpr bool value = "
     << (classFlags.isSerializable ? "true" : "false") << "; };\n";

  os << "namespace detail\n{\n";

  os << "template<>\n"
     << "LooEnum const *\n"
     << "LooGetEnumImpl(LooEnumTag<" << type << ">) noexcept\n"
     << "{\n"
     << "static detail::LooEnumBuilder<" << type << ", " << m_constnatDecls.size()
     << ">"
     << " reflected([](auto self) {\n";

  /* Enum Constant */
  for (auto &enumconstant : m_constnatDecls) {
    Attr *attr = GetAnnotateAttr(enumconstant);
    assert(attr != nullptr);
    propertyAnnotations.push_back(
        GenerateEnumValueAttributes(GetAnnotations(attr, str)));
  }
  EnumConstantGenerator enumValueGenerator(ctx, type, "self->enumValues");
  for (int i = 0; i < m_constnatDecls.size(); ++i) {
    enumValueGenerator.Generate(i, m_constnatDecls[i], propertyAnnotations[i],
                                os);
  }

  os << "});\n"
     << "static LooEnum cache(\n"
     << "sizeof(" << type << "),\n"
     << "Hash(\"" << type << "\"),\n"
     << "reflected.enumValues,\n"
     << "reflected.enumValues + reflected.numValues,\n"
     << "\"" << type << "\",\n"
     << classFlags.Flags() << ");\n"
     << "return &cache;\n";
  os << "}\n\n";

  /* GetType function */
  /* os << "template<> struct TypeResolver<" << type << ">;\n"; */
  os << "template<>\n"
     << "LooType const *\n"
     /* << "TypeResolver<" << type << ">::Get() noexcept\n" */
     /* << "GetType<" << type << ">() noexcept\n" */
     << "LooGetTypeImpl(LooTypeTag<" << type << ">) noexcept\n"
     << "{\n"
     /* << "return ClassResolver<" << type << ">::Get();\n" */
     << "return LooGetEnum<" << type << ">();\n"
     << "}\n";


  os << "} /* namespace detail */\n";
  os << "} /* namespace looreflect */\n\n";

    // private
  os_private << "namespace looreflect\n{\n\n";
  os_private << "namespace detail\n{\n\n";
  GenerateGlobalRegisterEnum(type, os_private);
  os_private << "} /* namespace detail */\n";
  os_private << "} /* namespace looreflect */\n\n";
}

/* ========================================================================= */
/* Generator                                                                 */
/* ========================================================================= */
PropertyAnnotations
ReflectedEnum::GenerateEnumValueAttributes(StringRef const &attr) {
  assert(attr.startswith("loo-property") && "incorrect annotation");
  auto pair = attr.split(";");

  PropertyAnnotations ret;
  auto setAttributes = [&ret](StringRef const &s) -> bool {
    if (s.equals_lower("serialized")) {
      return (ret.serialized = true);
    } else if (s.startswith_lower("tagname")) {
      size_t idx = s.find_first_of('=');
      auto sref = s.substr(idx + 1);
      ret.tagName = sref;
      ret.hasTagName = true;
      return true;
    }
    return false;
  };

  ForEachProperty(pair.second, setAttributes);
  return ret;
}
