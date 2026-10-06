# Makefile for WarpTris (Open Watcom C++ on OS/2 / ArcaOS)
# wmake 2.0.1 on ArcaOS - explicit per-file rules (no pattern rules),
# all prerequisites of a target on ONE line (no continuation backslashes).

# ============================================================================
# Configuration
# ============================================================================

NAME    = WarpTris
SRCDIR  = src
BINDIR  = bin

!ifndef WATCOM
WATCOM  = C:\WATCOM
!endif

!ifndef OS2TK
OS2TK   = C:\OS2TK45
!endif

# ============================================================================
# Tools
# ============================================================================

CCPP    = wpp386
LINK    = wlink
RC      = wrc
WIPFC   = wipfc

# ============================================================================
# Flags (per plan.txt section 2; no -bm: it kills the PM start up)
# ============================================================================

CFLAGS  = -bt=os2 -mf -5 -fpi -Oaxt -W3 -ze -d0
CFLAGS  = $(CFLAGS) -i=$(OS2TK)\h -i=$(SRCDIR)

RCFLAGS = -r -bt=os2 -i=$(OS2TK)\h -i=$(SRCDIR) -i=$(SRCDIR)\bitmaps

LFLAGS  = system os2v2_pm
LFLAGS  = $(LFLAGS) option stack=65536
LFLAGS  = $(LFLAGS) option map=$(BINDIR)\$(NAME).map

# ============================================================================
# Files
# ============================================================================

OBJS    = $(BINDIR)\WarpTris.obj $(BINDIR)\lang.obj
ROBJ    = $(BINDIR)\$(NAME).res
RCFILE  = $(SRCDIR)\$(NAME).rc
DEFFILE = $(SRCDIR)\$(NAME).def

HLPS    = $(BINDIR)\help\WarpTris_en.hlp $(BINDIR)\help\WarpTris_es.hlp $(BINDIR)\help\WarpTris_nl.hlp $(BINDIR)\help\WarpTris_de.hlp $(BINDIR)\help\WarpTris_fr.hlp $(BINDIR)\help\WarpTris_it.hlp

# ============================================================================
# Targets
# ============================================================================

all : $(BINDIR)\$(NAME).exe $(HLPS) .SYMBOLIC

$(BINDIR) :
	@if not exist $(BINDIR) mkdir $(BINDIR)

$(BINDIR)\help : $(BINDIR)
	@if not exist $(BINDIR)\help mkdir $(BINDIR)\help

$(BINDIR)\$(NAME).exe : $(OBJS) $(ROBJ) $(DEFFILE)
	@echo Linking $(NAME).exe...
	@$(LINK) $(LFLAGS) name $(BINDIR)\$(NAME).exe file $(BINDIR)\WarpTris.obj, $(BINDIR)\lang.obj library os2386.lib
	@echo Binding resources...
	@$(RC) -q -bt=os2 $(ROBJ) $(BINDIR)\$(NAME).exe
	@if exist $(BINDIR)\$(NAME).exe echo BUILD OK

# ============================================================================
# Objects
# ============================================================================

$(BINDIR)\WarpTris.obj : $(SRCDIR)\WarpTris.CPP $(SRCDIR)\warptris.h $(SRCDIR)\lang.h $(SRCDIR)\Board.H $(SRCDIR)\Figure.H $(SRCDIR)\Digital.H $(SRCDIR)\HighScore.H $(BINDIR)
	@echo Compiling src\WarpTris.CPP
	@$(CCPP) $(CFLAGS) -fo=$@ $(SRCDIR)\WarpTris.CPP

$(BINDIR)\lang.obj : $(SRCDIR)\lang.cpp $(SRCDIR)\lang.h $(BINDIR)
	@echo Compiling src\lang.cpp
	@$(CCPP) $(CFLAGS) -fo=$@ $(SRCDIR)\lang.cpp

# ============================================================================
# Resources
# ============================================================================

$(ROBJ) : $(RCFILE) $(SRCDIR)\warptris.h $(SRCDIR)\warptris.ico $(BINDIR)
	@echo Compiling resources...
	@$(RC) $(RCFLAGS) -fo=$(ROBJ) $(RCFILE)

# ============================================================================
# Help files (one per language, compiled with wipfc)
# ============================================================================

$(BINDIR)\help\WarpTris_en.hlp : help\WarpTris_en.ipf $(BINDIR)\help
	@echo Compiling help\WarpTris_en.ipf
	@$(WIPFC) -o $@ help\WarpTris_en.ipf

$(BINDIR)\help\WarpTris_es.hlp : help\WarpTris_es.ipf $(BINDIR)\help
	@echo Compiling help\WarpTris_es.ipf
	@$(WIPFC) -o $@ help\WarpTris_es.ipf

$(BINDIR)\help\WarpTris_nl.hlp : help\WarpTris_nl.ipf $(BINDIR)\help
	@echo Compiling help\WarpTris_nl.ipf
	@$(WIPFC) -o $@ help\WarpTris_nl.ipf

$(BINDIR)\help\WarpTris_de.hlp : help\WarpTris_de.ipf $(BINDIR)\help
	@echo Compiling help\WarpTris_de.ipf
	@$(WIPFC) -l de_DE -o $@ help\WarpTris_de.ipf

$(BINDIR)\help\WarpTris_fr.hlp : help\WarpTris_fr.ipf $(BINDIR)\help
	@echo Compiling help\WarpTris_fr.ipf
	@$(WIPFC) -l fr_FR -o $@ help\WarpTris_fr.ipf

$(BINDIR)\help\WarpTris_it.hlp : help\WarpTris_it.ipf $(BINDIR)\help
	@echo Compiling help\WarpTris_it.ipf
	@$(WIPFC) -o $@ help\WarpTris_it.ipf

# ============================================================================
# Clean
# ============================================================================

clean : .SYMBOLIC
	@if exist $(BINDIR)\*.obj del $(BINDIR)\*.obj >nul
	@if exist $(BINDIR)\*.res del $(BINDIR)\*.res >nul
	@if exist $(BINDIR)\$(NAME).exe del $(BINDIR)\$(NAME).exe >nul
	@if exist $(BINDIR)\$(NAME).map del $(BINDIR)\$(NAME).map >nul
	@if exist $(BINDIR)\help\*.hlp del $(BINDIR)\help\*.hlp >nul
	@echo Clean complete
