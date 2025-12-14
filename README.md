# QterSpim  
  
A cuter frontend for the assembly language MIPS R2000/R3000 simulator.  
Forked from [SPIM](https://sourceforge.net/projects/spimsimulator/), this repo hosts the UI interface code and aims to make it a more modern and richer experience with built-in assembly editing.  
  
QterSpim is a self-contained Simulator/IDE that runs MIPS32 assembly language programs.   
It also provides a minimal set of operating system services.  
  
## Instalation
WIP!  

## Getting started
WIP!  

## Development
QterSpim uses the [Qt framework](https://doc.qt.io/) to provide a native GUI interface across all platforms.  
- The `QtSpim/` directory contains the root of the Qt project  
- The `CPU/` backend is kept and managed [separatly](https://github.com/Dvd-Znf/Spim-CPU)  

### Prelude

You will need to install the relevant toolkits for your platform,  
You should have access to these tools: `qmake`, `uic`, `bison`, `flex` and a C/C++ toolchain including `make`.

You can use whatever editor you wish.  
While the original project recommended using QtCreator, I wouldn't.  
QtDesigner likes to get a bit quirky at night on my machine,  

The `QtSpim.pro` file has been patched and _should_ work fine by default on all platforms now.  

### Building
#### First time setup
Inside `QtSpim/` run `qmake`,  
This will genarate a `Makefile` which will be used from now on.  

#### Compiling
Running `make` will build the executable `QtSpim`,  
If you edit any of the source files and then subsequently run `make` again,  
Only the changed files will be recompiled.  

Changes to resources outside ui, C++ or header files will require a clean build, see bellow

#### Clean
`make clean` will remove produced object files  
`make distclean` will remove everything, including the Makefile itself  

### Notes on the VCS transition
Original Subversion revisions/commits have been lost in the process of forking and swithing to git.   
The root git commit is also _not_ the last SVN revision from SourceForge, it already contains _a lot_ of patches,  
See root commit message for a changelog.  

### The original project has been retired:
> SPIM is no longer supported.   
> The code has been stable for many years, with a few occasional bugs.   
> But, as I reach retirement, it is clear to me that SPIM should retire as well.   
> Feel free to fork a copy and fix the bugs yourself!  
> [(Message from original author)](https://sourceforge.net/p/spimsimulator/code/HEAD/tree/README#l229)  
  
## Licensing:

SPIM is Copyright (c) 1990-2023, by James R. Larus. 
All rights reserved.

Original versions of SPIM are distributed under the following BSD license:

```
Redistribution and use in source and binary forms, with or without modification, are
permitted provided that the following conditions are met:

    Redistributions of source code must retain the above copyright notice, this list of
    conditions and the following disclaimer.

    Redistributions in binary form must reproduce the above copyright notice, this list of
    conditions and the following disclaimer in the documentation and/or other materials
    provided with the distribution.

    Neither the name of the James R. Larus nor the names of its contributors may be used to
    endorse or promote products derived from this software without specific prior written
    permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS
OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
```


QterSPIM is linked to the Qt library, which is distributed under the GNU Lesser General Public License
version 3 and GNU Lesser General Public License version 2.1.

GNU Lesser General Public License, version 2.1  http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html  
GNU Lesser General Public License, version 3  http://www.gnu.org/licenses/lgpl-3.0.html
