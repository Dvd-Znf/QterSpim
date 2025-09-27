/* SPIM S20 MIPS simulator.
   Terminal interface for SPIM simulator.

   Copyright (c) 1990-2022, James R. Larus.
   All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:

   Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.

   Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

   Neither the name of the James R. Larus nor the names of its contributors may
   be used to endorse or promote products derived from this software without
   specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.
*/
#include <clocale>
#include <QApplication>
#include "spimview.h"

static QStringList parseCommandLine(QStringList args);

SpimView* Window;
QApplication* App;

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  setlocale(
      LC_NUMERIC,
      "C");  // Qt Linux has wrong default
             // https://doc.qt.io/qt-5/qcoreapplication.html#locale-settings
  QCoreApplication::setOrganizationName("Dvd-Znf");
  QCoreApplication::setOrganizationDomain("dvdznf.xyz");
  QCoreApplication::setApplicationName("QterSpim");

  App = &a;
  SpimView win;
  Window = &win;

  // Initialize Spim
  //
  message_out.i = 1;
  console_out.i = 2;

  win.SpimConsole->show();
  win.show();

  QStringList fileNames = parseCommandLine(a.arguments());

  win.sim_ReinitializeSimulator();

  for (int i = 0; i < fileNames.length(); i++) {
    if (fileNames[i] != "") {
      read_assembly_file(fileNames[i].toLocal8Bit().data());
    }
  }

  win.DisplayTextSegments(true);
  win.UpdateDataDisplay();

  a.setStyleSheet(
      "* {"
      "   color: #cdd6f4;"
      "   background-color: #1e1e2e;"
      "}"
      // "*:hover {"
      // "   background-color: #313244;"
      // "}"
      "QTextEdit, QPlainTextEdit {"
      "   background-color: #1e1e2e;"
      "   color: #cdd6f4;"
      "   selection-background-color: #45475a;"
      "   selection-color: #f5e0dc;"
      "}"
      ""
      "QLineEdit {"
      "   background-color: #1e1e2e;"
      "   color: #cdd6f4;"
      "   selection-background-color: #45475a;"
      "   selection-color: #f5e0dc;"
      "}"
      ""
      "QTabWidget::tab-bar {"
      "   left: 5px;"
      "}"
      ""
      "QTabBar::tab {"
      "    background-color: #6c7086;;"
      "    border: 2px solid #6c7086;"
      "    border-bottom-color: #6c7086;"
      "    border-bottom-left-radius: 4px;"
      "    border-bottom-right-radius: 4px;"
      "    min-width: 8ex;"
      "    padding: 2px; padding-left:10px; padding-right:10px;"
      "    font: bold 12px"
      "}"
      ""
      "QTabBar::tab:selected, QTabBar::tab:hover {"
      "       color: #11111b;"
      "       background-color: #cba6f7;"
      "}"
      ""
      "QTabBar::tab:selected {"
      "    border: 2px solid #cba6f7;"
      "    border-bottom-color: #C2C7CB;"
      "}"
      ""
      "QTabBar::tab:!selected {"
      "    margin-top: 2px; /* make non-selected tabs look smaller */"
      "}"
      "QToolBar { "
      "  background: #181825;"
      "  spacing: 3px; /* spacing between items in the tool bar */"
      "}"
      "QMenuBar { "
      "  background: #181825;"
      "  spacing: 3px;"
      "}"
      "QMenu { "
      "  background: #313244;"
      "  spacing: 3px;"
      "}" // margin-top, margin-right, margin-bottom, and margin-left
      "QToolButton{margin: 5px 10px 5px;}"
    );

  return a.exec();
}

static QStringList parseCommandLine(QStringList args) {
  for (int i = 1; i < args.length(); i++) {
#ifdef WIN32
    if (args[i][0] == '/') {
      args[i][0] = '-';
    }
#endif
    if ((args[i] == "-asm") || (args[i] == "-a")) {
      bare_machine = false;
      delayed_branches = false;
      delayed_loads = false;
    } else if ((args[i] == "-bare") || (args[i] == "-b")) {
      bare_machine = true;
      delayed_branches = true;
      delayed_loads = true;
      quiet = true;
    } else if ((args[i] == "-delayed_branches") || (args[i] == "-db")) {
      delayed_branches = true;
    } else if ((args[i] == "-delayed_loads") || (args[i] == "-dl")) {
      delayed_loads = true;
    } else if ((args[i] == "-exception") || (args[i] == "-e")) {
      Window->SetExceptionHandler("", true);
    } else if ((args[i] == "-noexception") || (args[i] == "-ne")) {
      Window->SetExceptionHandler("", false);
    } else if ((args[i] == "-exception_file") || (args[i] == "-ef")) {
      Window->SetExceptionHandler(args[++i], true);
    } else if ((args[i] == "-mapped_io") || (args[i] == "-mio")) {
      mapped_io = true;
    } else if ((args[i] == "-nomapped_io") || (args[i] == "-nmio")) {
      mapped_io = false;
    } else if ((args[i] == "-pseudo") || (args[i] == "-p")) {
      accept_pseudo_insts = true;
    } else if ((args[i] == "-nopseudo") || (args[i] == "-np")) {
      accept_pseudo_insts = false;
    } else if ((args[i] == "-quiet") || (args[i] == "-q")) {
      quiet = true;
    } else if ((args[i] == "-noquiet") || (args[i] == "-nq")) {
      quiet = false;
    } else if ((args[i] == "-trap") || (args[i] == "-t")) {
      Window->SetExceptionHandler("", true);
    } else if ((args[i] == "-notrap") || (args[i] == "-nt")) {
      Window->SetExceptionHandler("", false);
    } else if ((args[i] == "-trap_file") || (args[i] == "-tf")) {
      Window->SetExceptionHandler(args[++i], true);
    } else if ((args[i] == "-stext") || (args[i] == "-st")) {
      initial_text_size = args[++i].toInt();
    } else if ((args[i] == "-sdata") || (args[i] == "-sd")) {
      initial_data_size = args[++i].toInt();
    } else if ((args[i] == "-ldata") || (args[i] == "-ld")) {
      initial_data_limit = args[++i].toInt();
    } else if ((args[i] == "-sstack") || (args[i] == "-ss")) {
      initial_stack_size = args[++i].toInt();
    } else if ((args[i] == "-lstack") || (args[i] == "-ls")) {
      initial_stack_limit = args[++i].toInt();
    } else if ((args[i] == "-sktext") || (args[i] == "-skt")) {
      initial_k_text_size = args[++i].toInt();
    } else if ((args[i] == "-skdata") || (args[i] == "-skd")) {
      initial_k_data_size = args[++i].toInt();
    } else if ((args[i] == "-lkdata") || (args[i] == "-lkd")) {
      initial_k_data_limit = args[++i].toInt();
    } else if ((args[i] == "-file") || (args[i] == "-f")) {
      return args.mid(i + 1);
    } else if (args[i][0] != '-') {
      return args.mid(i);
    } else {
      error(
          "Unknown argument: %s (ignored)\n\n\
        Usage: QtSpim\n\
	-bare			Bare machine (no pseudo-ops, delayed branches and loads)\n\
	-asm			Extended machine (pseudo-ops, no delayed branches and loads) (default)\n\
	-delayed_branches	Execute delayed branches\n\
	-delayed_loads		Execute delayed loads\n\
	-exception		Load exception handler (default)\n\
	-noexception		Do not load exception handler\n\
	-exception_file <file>	Specify exception handler in place of default\n\
	-quiet			Do not print warnings\n\
	-noquiet		Print warnings (default)\n\
	-mapped_io		Enable memory-mapped IO\n\
	-nomapped_io		Do not enable memory-mapped IO (default)\n\
	-file <file> ...	Assembly code file(s)\n\
	\n\
	If argument does not start with a '-', it and all subsequent arguments are file names.\n",
          args[i].toLocal8Bit().data());
    }
  }
  return QStringList();
}
