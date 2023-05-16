/**
 ** This file is part of the NoteBook project.
 ** Copyright 2022 ji wang <matheuter@gmail.com>.
 **
 ** This program is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU Lesser General Public License as
 ** published by the Free Software Foundation, either version 3 of the
 ** License, or (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU Lesser General Public License for more details.
 **
 ** You should have received a copy of the GNU Lesser General Public License
 ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **/

#ifndef ICONFIGURE_H
#define ICONFIGURE_H

#define MAPLE_NAMESPACE_BEGIN namespace Maple {
#define MAPLE_NAMESPACE_END }
#define USERSPACE       (0x100)

#define ACTION          ("action")
#define ACTION_CREATE   (USERSPACE + 1)

#define PLUGIN_DOCUMNETAREA     "org.notebook.plugin.documentarea"
#define PLUGIN_DOCUMNETVIEW     "org.notebook.plugin.documentview"
#define PLUGIN_SEARCHENGINE     "org.notebook.plugin.searchengine"
#define PLUGIN_DOCUMNETFACTORY  "org.notebook.plugin.documentfactory"


template <typename T, T v>
struct integral_constant
{
    static constexpr T value = v;
    typedef T value_type;
    typedef integral_constant<T, v> type;

    constexpr value_type operator()() const noexcept { return value; }
    constexpr operator value_type() const noexcept { return value; }
};

enum MeteGroup
{
    UserMeteGroup,
    ServiceMeteGroup,
    SystemMeteGroup,
    DocumentMeteGroup
};


enum DockWidgetArea
{
    DA_BOTTOM,
    DA_LEFT,
    DA_RIGHT
};

//lexer names
#define BATCH "batch"
#define CPP "cpp"
#define CSHarP "c#"
#define CMAKE "cmake"
#define COFFEESCRIPT "coffeeScript"
#define CSS "css"
#define DIFF "diff"
#define FORTRAN "fortran"
#define FORTRAN77 "fortran77"
#define HTML "html"
#define JAVA "java"
#define JAVASCRIPT "javaScript"
#define LUA "lua"
#define MAKEFILE "make"
#define MATLAB "matlab"
#define PASCAL "pascal"
#define PERL "perl"
#define PYTHON "python"
#define POSTSCRIPT "postscript"
#define PROPERTIES "properties"
#define RUBY "ruby"
#define SQL "sql"
#define TCL "tcl"
#define TEX "teX"
#define VHDL "vhdl"
#define VERILOG "verilog"
#define XML "xml"
#define YAML "yaml"
#define PDF "pdf"


#define ANSI "ANSI"
#define Big5 "Big5"
#define Big5_HKSCS "Big5-HKSCS"
#define CP949 "CP949"
#define EUC_JP "EUC-JP"
#define EUC_KR "EUC-KR"
#define GB18030 "GB18030"
#define HP_ROMAN8 "HP-ROMAN8"
#define IBM_850 "IBM 850"
#define IBM_866 "IBM 866"
#define IBM_874 "IBM 874"
#define ISO_2022_JP "ISO 2022-JP"
#define ISO_8859 "ISO 8859"
#define KOI8_R "KOI8-R"
#define KOI8_U "KOI8-U"
#define Macintosh "Macintosh"
#define Shift_JIS "Shift-JIS"
#define TIS_620 "TIS-620"
#define TSCII "TSCII"
#define UTF_8 "utf-8"
#define UTF_16 "UTF-16"
#define UTF_16BE "UTF-16BE"
#define UTF_16LE "UTF-16LE"
#define UTF_32 "UTF-32"
#define UTF_32BE "UTF-32BE"
#define UTF_32LE "UTF-32LE"
#define Windows_1250 "Windows-1250"


#ifdef  _WIN32 || _WIN64
#ifndef NO_KNOWLEDGE_PLUGIN
    #ifndef DECL_EXPORT
        #define DECL_EXPORT __declspec(dllexport)
    #endif
    #ifndef DECL_IMPORT
        #define DECL_IMPORT __declspec(dllimport)
    #endif
#else
    #ifndef DECL_EXPORT
        #define DECL_EXPORT
    #endif
    #ifndef DECL_IMPORT
        #define DECL_IMPORT
    #endif
#endif
#else
    #ifndef DECL_EXPORT
        #define DECL_EXPORT
    #endif
    #ifndef DECL_IMPORT
        #define DECL_IMPORT
    #endif
#endif

#ifndef MAPLE_EXPORT
    #define MAPLE_EXPORT DECL_EXPORT
#endif

#ifndef MAPLE_IMPORT
    #define MAPLE_IMPORT
#endif

#endif // ICONFIGURE_H
