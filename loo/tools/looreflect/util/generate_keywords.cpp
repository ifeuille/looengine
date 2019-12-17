
#include <stdio.h>
#include <string.h>
#include <list>
#include <vector>

typedef std::string LooByteArray;

struct Keyword
{
    const char *lexem;
    const char *token;
};

static const Keyword pp_keywords[] = {
    { "<", "PP_LANGLE" },
    { ">", "PP_RANGLE" },
    { "(", "PP_LPAREN"},
    { ")", "PP_RPAREN"},
    { ",", "PP_COMMA"},
    { "\n", "PP_NEWLINE"},
    { "#define", "PP_DEFINE"},
    { "#if", "PP_IF"},
    { "#undef", "PP_UNDEF"},
    { "#ifdef", "PP_IFDEF"},
    { "#ifndef", "PP_IFNDEF"},
    { "#elif", "PP_ELIF"},
    { "#else", "PP_ELSE"},
    { "#endif", "PP_ENDIF"},
    { "#include", "PP_INCLUDE"},
    { "defined", "PP_DEFINED"},
    { "+", "PP_PLUS" },
    { "-", "PP_MINUS" },
    { "*", "PP_STAR" },
    { "/", "PP_SLASH" },
    { "%", "PP_PERCENT" },
    { "^", "PP_HAT" },
    { "&", "PP_AND" },
    { "bitand", "PP_AND" },
    { "|", "PP_OR" },
    { "bitor", "PP_OR" },
    { "~", "PP_TILDE" },
    { "compl", "PP_TILDE" },
    { "!", "PP_NOT" },
    { "not", "PP_NOT" },
    { "<<", "PP_LTLT" },
    { ">>", "PP_GTGT" },
    { "==", "PP_EQEQ" },
    { "!=", "PP_NE" },
    { "not_eq", "PP_NE" },
    { "<=", "PP_LE" },
    { ">=", "PP_GE" },
    { "&&", "PP_ANDAND" },
    { "||", "PP_OROR" },
    { "?", "PP_QUESTION" },
    { ":", "PP_COLON" },
    { "##", "PP_HASHHASH"},
    { "%:%:", "PP_HASHHASH"},
    { "#", "PP_HASH"},
    { "\"", "PP_QUOTE"},
    { "\'", "PP_SINGLEQUOTE"},
    { " ", "PP_WHITESPACE" },
    { "\t", "PP_WHITESPACE" },
    { "//", "PP_CPP_COMMENT" },
    { "/*", "PP_C_COMMENT" },
    { "\\", "PP_BACKSLASH" },
    { 0, "PP_NOTOKEN"}
};

static const Keyword keywords[] = {
    { "<", "LANGLE" },
    { ">", "RANGLE" },
    { "(", "LPAREN" },
    { ")", "RPAREN" },
    { "...", "ELIPSIS" },
    { ",", "COMMA" },
    { "[", "LBRACK" },
    { "]", "RBRACK" },
    { "<:", "LBRACK" },
    { ":>", "RBRACK" },
    { "<::", "LANGLE_SCOPE" },
    { "{", "LBRACE" },
    { "<%", "LBRACE" },
    { "}", "RBRACE" },
    { "%>", "RBRACE" },
    { "=", "EQ" },
    { "::", "SCOPE" },
    { ";", "SEMIC" },
    { ":", "COLON" },
    { ".*", "DOTSTAR" },
    { "?", "QUESTION" },
    { ".", "DOT" },
    { "dynamic_cast", "DYNAMIC_CAST" },
    { "static_cast", "STATIC_CAST" },
    { "reinterpret_cast", "REINTERPRET_CAST" },
    { "const_cast", "CONST_CAST" },
    { "typeid", "TYPEID" },
    { "this", "THIS" },
    { "template", "TEMPLATE" },
    { "throw", "THROW" },
    { "try", "TRY" },
    { "catch", "CATCH" },
    { "typedef", "TYPEDEF" },
    { "friend", "FRIEND" },
    { "class", "CLASS" },
    { "namespace", "NAMESPACE" },
    { "enum", "ENUM" },
    { "struct", "STRUCT" },
    { "union", "UNION" },
    { "virtual", "VIRTUAL" },
    { "private", "PRIVATE" },
    { "protected", "PROTECTED" },
    { "public", "PUBLIC" },
    { "export", "EXPORT" },
    { "auto", "AUTO" },
    { "register", "REGISTER" },
    { "extern", "EXTERN" },
    { "mutable", "MUTABLE" },
    { "asm", "ASM" },
    { "using", "USING" },
    { "inline", "INLINE" },
    { "explicit", "EXPLICIT" },
    { "static", "STATIC" },
    { "const", "LOO_CONST" },
    { "volatile", "VOLATILE" },
    { "operator", "OPERATOR" },
    { "sizeof", "SIZEOF" },
    { "new", "NEW" },
    { "delete", "DELETE" },
    { "+", "PLUS" },
    { "-", "MINUS" },
    { "*", "STAR" },
    { "/", "SLASH" },
    { "%", "PERCENT" },
    { "^", "HAT" },
    { "&", "AND" },
    { "bitand", "AND" },
    { "|", "OR" },
    { "bitor", "OR" },
    { "~", "TILDE" },
    { "compl", "TILDE" },
    { "!", "NOT" },
    { "not", "NOT" },
    { "+=", "PLUS_EQ" },
    { "-=", "MINUS_EQ" },
    { "*=", "STAR_EQ" },
    { "/=", "SLASH_EQ" },
    { "%=", "PERCENT_EQ" },
    { "^=", "HAT_EQ" },
    { "&=", "AND_EQ" },
    { "|=", "OR_EQ" },
    { "<<", "LTLT" },
    { ">>", "GTGT" },
    { ">>=", "GTGT_EQ" },
    { "<<=", "LTLT_EQ" },
    { "==", "EQEQ" },
    { "!=", "NE" },
    { "not_eq", "NE" },
    { "<=", "LE" },
    { ">=", "GE" },
    { "&&", "ANDAND" },
    { "||", "OROR" },
    { "++", "INCR" },
    { "--", "DECR" },
    { ",", "COMMA" },
    { "->*", "ARROW_STAR" },
    { "->", "ARROW" },
    { "char", "CHAR" },
    { "wchar", "WCHAR" },
    { "bool", "BOOL" },
    { "short", "SHORT" },
    { "int", "INT" },
    { "long", "LONG" },
    { "signed", "SIGNED" },
    { "unsigned", "UNSIGNED" },
    { "float", "FLOAT" },
    { "double", "DOUBLE" },
    { "void", "LOO_VOID" },
    { "case", "CASE" },
    { "default", "DEFAULT" },
    { "if", "IF" },
    { "else", "ELSE" },
    { "switch", "SWITCH" },
    { "while", "WHILE" },
    { "do", "DO" },
    { "for", "FOR" },
    { "break", "BREAK" },
    { "continue", "CONTINUE" },
    { "goto", "GOTO" },
    { "return", "RETURN" },
    { "LOO_OBJECT", "LOO_OBJECT_TOKEN" },
    { "LOO_NAMESPACE", "LOO_NAMESPACE_TOKEN" },
    { "LOO_GADGET", "LOO_GADGET_TOKEN" },
    { "LOO_PROPERTY", "LOO_PROPERTY_TOKEN" },
    { "LOO_PLUGIN_METADATA", "LOO_PLUGIN_METADATA_TOKEN" },
    { "LOO_ENUMS", "LOO_ENUMS_TOKEN" },
    { "LOO_ENUM", "LOO_ENUM_TOKEN" },
    { "LOO_ENUM_NS", "LOO_ENUM_NS_TOKEN" },
    { "LOO_FLAGS", "LOO_FLAGS_TOKEN" },
    { "LOO_FLAG", "LOO_FLAG_TOKEN" },
    { "LOO_FLAG_NS", "LOO_FLAG_NS_TOKEN" },
    { "LOO_DECLARE_FLAGS", "LOO_DECLARE_FLAGS_TOKEN" },
    { "LOO_DECLARE_INTERFACE", "LOO_DECLARE_INTERFACE_TOKEN" },
    { "LOO_DECLARE_METATYPE", "LOO_DECLARE_METATYPE_TOKEN" },
    { "LOO_DECLARE_EXTENSION_INTERFACE", "LOO_DECLARE_INTERFACE_TOKEN" },
    { "LOO_SETS", "LOO_FLAGS_TOKEN" },
    { "LOO_CLASSINFO", "LOO_CLASSINFO_TOKEN" },
    { "LOO_INTERFACES", "LOO_INTERFACES_TOKEN" },
    { "signals", "SIGNALS" },
    { "slots", "SLOTS" },
    { "LOO_SIGNALS", "LOO_SIGNALS_TOKEN" },
    { "LOO_SLOTS", "LOO_SLOTS_TOKEN" },
    { "LOO_PRIVATE_SLOT", "LOO_PRIVATE_SLOT_TOKEN" },
    { "LOO_REFLECT_COMPAT", "LOO_REFLECT_COMPAT_TOKEN" },
    { "LOO_INVOKABLE", "LOO_INVOKABLE_TOKEN" },
    { "LOO_SIGNAL", "LOO_SIGNAL_TOKEN" },
    { "LOO_SLOT", "LOO_SLOT_TOKEN" },
    { "LOO_SCRIPTABLE", "LOO_SCRIPTABLE_TOKEN" },
    { "LOO_PRIVATE_PROPERTY", "LOO_PRIVATE_PROPERTY_TOKEN" },
    { "LOO_REVISION", "LOO_REVISION_TOKEN" },
    { "\n", "NEWLINE" },
    { "\"", "QUOTE" },
    { "\'", "SINGLEQUOTE" },
    { " ", "WHITESPACE" },
    { "\t", "WHITESPACE" },
    { "#", "HASH" },
    { "##", "PP_HASHHASH" },
    { "\\", "BACKSLASH" },
    { "//", "CPP_COMMENT" },
    { "/*", "C_COMMENT" },
    { 0, "NOTOKEN"}
};


inline bool is_ident_start(char s)
{
    return ((s >= 'a' && s <= 'z')
            || (s >= 'A' && s <= 'Z')
            || s == '_' || s == '$'
        );
}

inline bool is_ident_char(char s)
{
    return ((s >= 'a' && s <= 'z')
            || (s >= 'A' && s <= 'Z')
            || (s >= '0' && s <= '9')
            || s == '_' || s == '$'
        );
}
struct State
{
    State(const char* token):token(token), nextindex(0),
            defchar(0), defnext(0), ident(0) {
        memset( next, 0, sizeof(next));
    }
    LooByteArray token;
    int next[128];
    int nextindex;

    char defchar;
    int defnext;

    const char *ident;

    bool operator==(const State& o) const
        {
            return (token == o.token
                    && nextindex == o.nextindex
                    && defchar == o.defchar
                    && defnext == o.defnext
                    && ident == o.ident);
        }
};

//void newState(std::vector<State> &states, const char *token, const char *lexem, bool pre)
void newState (std::vector<State> &states, const std::string& token, const char *lexem, bool pre)
{
    const char * ident = 0;
    if (is_ident_start(*lexem))
        ident = pre?"PP_CHARACTER" : "CHARACTER";
    else if (*lexem == '#')
        ident = pre?"PP_HASH" : "HASH";

    int state = 0;
    while (*lexem) {
        int next = states[state].next[(int)*lexem];
        if (!next) {
            const char * t = 0;
            if (ident)
                t = ident;
            else
                t = pre?"PP_INCOMPLETE":"INCOMPLETE";
            next = states.size();
            //states += State(t);
			states.push_back (State (t));
            states[state].next[(int)*lexem] = next;
            states[next].ident = ident;
        }
        state = next;
        ++lexem;
        if (ident && !is_ident_char(*lexem))
            ident = 0;
    }
    states[state].token = token;
}

void newState(std::vector<State> &states, const char *token,  char lexem)
{
    int next = states[0].next[(int)lexem];
    if (!next) {
        next = states.size();
        //states += State(token);
		states.push_back (token);
        states[0].next[(int)lexem] = next;
    } else {
        states[next].token = LooByteArray (token);
    }
}


void makeTable(const Keyword keywords[])
{
    int i,c;
    bool pre = (keywords == pp_keywords);
    std::vector<State> states;
    /*states += State(pre?"PP_NOTOKEN":"NOTOKEN");*/
	states.push_back (State (pre ? "PP_NOTOKEN" : "NOTOKEN"));
    // identifiers
    for (c = 'a'; c <= 'z'; ++c)
        newState(states, pre?"PP_CHARACTER":"CHARACTER", c);
    for (c = 'A'; c <= 'Z'; ++c)
        newState(states, pre?"PP_CHARACTER":"CHARACTER", c);

    newState(states, pre?"PP_CHARACTER":"CHARACTER", '_');
    newState(states, pre?"PP_CHARACTER":"CHARACTER", '$');

    // add digits
    for (c = '0'; c <= '9'; ++c)
        newState(states, pre?"PP_DIGIT":"DIGIT", c);

    // keywords
    for (i = 0; keywords[i].lexem; ++i)
        newState(states, keywords[i].token, keywords[i].lexem, pre);

    // some floats
    for (c = '0'; c <= '9'; ++c)
        newState(states, pre?"PP_FLOATING_LITERAL":"FLOATING_LITERAL",
                 (LooByteArray (".") + char (c)).data(), pre);

    // simplify table with default transitions
    int transindex = -1;
    for (i = 0; i < states.size(); ++i) {
        int n = 0;
        int defchar = -1;
        for (c = 0; c < 128; ++c)
            if (states[i].next[c]) {
                ++n;
                defchar = c;
            }
        if (!n)
            continue;
        if (n == 1) {
            states[i].defnext = states[i].next[defchar];
            states[i].defchar = defchar;
            continue;
        }
        states[i].nextindex = ++transindex;
    }

#if 1
    // compress table
    int j, k;
    for (i = 0; i < states.size(); ++i) {
        for (j = i + 1; j < states.size(); ++j) {
            if ( states[i] == states[j] ) {
                for (k = 0; k < states.size(); ++k) {
                    if (states[k].defnext == j)
                        states[k].defnext = i;
                    if (states[k].defnext > j)
                        --states[k].defnext;
                    for (c = 0; c < 128; ++c) {
                        if (states[k].next[c] == j)
                            states[k].next[c] = i;
                        if (states[k].next[c] > j)
                            --states[k].next[c];
                    }
                }
                //states.removeAt(j);
				states.erase (states.begin() + j);
                --j;
            }
        }
    }
#endif
    printf("static const short %skeyword_trans[][128] = {\n",
           pre?"pp_":"");
    for (i = 0; i < states.size(); ++i) {
        if (i && !states[i].nextindex)
            continue;
        printf("%s    {", i?",\n":"");
        for (c = 0; c < 128; ++c)
            printf("%s%s%d",
                   c?",":"",
                   (!c || c%16)?"":"\n     ",
                   states[i].next[c]
                   );
        printf("}");
    }
    printf("\n};\n\n");

    printf("static const struct\n{\n"
           "   %sToken token;\n"
           "   short next;\n"
           "   char defchar;\n"
           "   short defnext;\n"
           "   %sToken ident;\n"
           "} %skeywords[] = {\n",
           pre ? "PP_":"",
           pre ? "PP_":"",
           pre ? "pp_":"");
    for (i = 0; i < states.size(); ++i) {
        printf("%s    {%s, %d, %d, %d, %s}",
               i?",\n":"",
               states[i].token.data(),
               states[i].nextindex,
               states[i].defchar,
               states[i].defnext,
               states[i].ident?states[i].ident:(pre?"PP_NOTOKEN":"NOTOKEN"));
    }
    printf("\n};\n");
}

int main(int argc, char **)
{
    printf("// auto generated\n"
           "// DO NOT EDIT.\n\n");
    if ( argc > 1 )
        makeTable(pp_keywords);
    else
        makeTable(keywords);
    return 0;
}
