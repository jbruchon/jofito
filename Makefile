# jofito Makefile

CFLAGS ?= -O2 -g

# PREFIX determines where files will be installed. Common examples
# include "/usr" or "/usr/local".
PREFIX = /usr/local

# Certain platforms do not support long options (command line options).
# To disable long options, uncomment the following line.
#CFLAGS += -DOMIT_GETOPT_LONG

# Uncomment for -B/--dedupe.
# This can also be enabled at build time: 'make ENABLE_DEDUPE=1'
#CFLAGS += -DENABLE_DEDUPE

# Uncomment for low memory usage at the expense of speed and features
# This can be enabled at build time: 'make LOW_MEMORY=1'
#LOW_MEMORY=1

# Uncomment this to build in hardened mode.
# This can be enabled at build time: 'make HARDEN=1'
#HARDEN=1

# PROGRAM_NAME determines the installation name and manual page name
PROGRAM_NAME = jofito

# BIN_DIR indicates directory where program is to be installed.
# Suggested value is "$(PREFIX)/bin"
BIN_DIR = $(PREFIX)/bin

# MAN_DIR indicates directory where the jofito man page is to be
# installed. Suggested value is "$(PREFIX)/man/man1"
MAN_BASE_DIR = $(PREFIX)/share/man
MAN_DIR = $(MAN_BASE_DIR)/man1
MAN_EXT = 1

# Required External Tools
CC ?= gcc
INSTALL = install
RM      = rm -f
RMDIR	= rmdir -p
MKDIR   = mkdir -p

# Make Configuration
COMPILER_OPTIONS = -Wall -Wwrite-strings -Wcast-align -Wstrict-aliasing -Wstrict-prototypes -Wpointer-arith -Wundef
COMPILER_OPTIONS += -Wshadow -Wfloat-equal -Waggregate-return -Wcast-qual -Wswitch-default -Wswitch-enum -Wconversion -Wunreachable-code -Wformat=2
COMPILER_OPTIONS += -std=gnu99 -D_FILE_OFFSET_BITS=64 -fstrict-aliasing -pipe
COMPILER_OPTIONS += -DSMA_MAX_FREE=11 -DNO_ATIME

UNAME_S=$(shell uname -s)

# Don't use unsupported compiler options on gcc 3/4 (Mac OS X 10.5.8 Xcode)
ifeq ($(UNAME_S), Darwin)
	GCCVERSION = $(shell expr `LC_ALL=C gcc -v 2>&1 | grep 'gcc version ' | cut -d\  -f3 | cut -d. -f1` \>= 5)
else
	GCCVERSION = 1
endif
ifeq ($(GCCVERSION), 1)
	COMPILER_OPTIONS += -Wextra -Wstrict-overflow=5 -Winit-self
endif

# Are we running on a Windows OS?
ifeq ($(OS), Windows_NT)
	ifndef NO_WINDOWS
		ON_WINDOWS=1
	endif
endif

# Debugging code inclusion
ifdef LOUD
DEBUG=1
COMPILER_OPTIONS += -DLOUD_DEBUG
endif
ifdef DEBUG
COMPILER_OPTIONS += -DDEBUG
else
COMPILER_OPTIONS += -DNDEBUG
endif
ifdef HARDEN
COMPILER_OPTIONS += -Wformat -Wformat-security -D_FORTIFY_SOURCE=2 -fstack-protector-strong -fPIE -fpie -Wl,-z,relro -Wl,-z,now
endif

# Catch someone trying to enable BTRFS in flags and turn on ENABLE_DEDUPE
ifneq (,$(findstring DENABLE_BTRFS,$(CFLAGS) $(CFLAGS_EXTRA)))
	ENABLE_DEDUPE=1
endif
ifneq (,$(findstring DENABLE_DEDUPE,$(CFLAGS) $(CFLAGS_EXTRA)))
	ENABLE_DEDUPE=1
endif

# MinGW needs this for printf() conversions to work
ifdef ON_WINDOWS
	ifndef NO_UNICODE
		UNICODE=1
		COMPILER_OPTIONS += -municode
		PROGRAM_SUFFIX=.exe
	endif
	COMPILER_OPTIONS += -D__USE_MINGW_ANSI_STDIO=1 -DON_WINDOWS=1
	OBJS += jody_win_stat.o
	ifeq ($(UNAME_S), MINGW32_NT-5.1)
		OBJS += winres_xp.o
	else
		OBJS += winres.o
	endif
	override undefine ENABLE_DEDUPE
endif

# Stack size limit can be too small for deep directory trees, so set to 16 MiB
# The ld syntax for Windows is the same for both Cygwin and MinGW
ifndef LOW_MEMORY
ifeq ($(OS), Windows_NT)
COMPILER_OPTIONS += -Wl,--stack=16777216
else ifeq ($(UNAME_S), Darwin)
COMPILER_OPTIONS += -Wl,-stack_size -Wl,0x1000000
else
COMPILER_OPTIONS += -Wl,-z,stack-size=16777216
endif
endif

CFLAGS += $(COMPILER_OPTIONS) $(CFLAGS_EXTRA)

INSTALL_PROGRAM = $(INSTALL) -m 0755
INSTALL_DATA    = $(INSTALL) -m 0644

OBJS += jofito.o oom.o tokenizer.o

all: $(PROGRAM_NAME)

static: $(PROGRAM_NAME)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(PROGRAM_NAME) $(OBJS) -static

static_stripped: $(PROGRAM_NAME)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(PROGRAM_NAME) $(OBJS) -static
	strip $(PROGRAM_NAME)

$(PROGRAM_NAME): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(PROGRAM_NAME) $(OBJS)

winres.o: winres.rc winres.manifest.xml
	./tune_winres.sh
	windres winres.rc winres.o

winres_xp.o: winres_xp.rc
	./tune_winres.sh
	windres winres_xp.rc winres_xp.o

installdirs:
	test -e $(DESTDIR)$(BIN_DIR) || $(MKDIR) $(DESTDIR)$(BIN_DIR)
	test -e $(DESTDIR)$(MAN_DIR) || $(MKDIR) $(DESTDIR)$(MAN_DIR)

install: $(PROGRAM_NAME) installdirs
	$(INSTALL_PROGRAM)	$(PROGRAM_NAME)   $(DESTDIR)$(BIN_DIR)/$(PROGRAM_NAME)
	$(INSTALL_DATA)		$(PROGRAM_NAME).1 $(DESTDIR)$(MAN_DIR)/$(PROGRAM_NAME).$(MAN_EXT)

uninstalldirs:
	-test -e $(DESTDIR)$(BIN_DIR) && $(RMDIR) $(DESTDIR)$(BIN_DIR)
	-test -e $(DESTDIR)$(MAN_DIR) && $(RMDIR) $(DESTDIR)$(MAN_DIR)

uninstall: uninstalldirs
	$(RM)	$(DESTDIR)$(BIN_DIR)/$(PROGRAM_NAME)
	$(RM)	$(DESTDIR)$(MAN_DIR)/$(PROGRAM_NAME).$(MAN_EXT)

test:
	./test.sh

stripped: $(PROGRAM_NAME)
	strip $(PROGRAM_NAME)$(PROGRAM_SUFFIX)

clean:
	$(RM) $(OBJS) $(OBJS_CLEAN) $(PROGRAM_NAME) $(PROGRAM_NAME).exe *~ .*.un~ *.gcno *.gcda *.gcov

distclean: clean
	$(RM) *.pkg.tar.*
	$(RM) -r jofito-*-*/ jofito-*-*.zip

chrootpackage:
	+./chroot_build.sh
package:
	+./generate_packages.sh
