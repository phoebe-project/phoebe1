########################################################################
#                                                                      #
#                            PHOEBE 1.0 GUI                            #
#                                                                      #
########################################################################
#                                                                      #
#   Author of configure.ac: Andrej Prsa <aprsa@villanova.edu>          #
#                                                                      #
#                               * * *                                  #
#                                                                      #
#  When you change configure.ac, don't forget to run auto(re)conf for  #
#                     changes to take effect!                          #
#                                                                      #
#                               * * *                                  #
#                                            Last revision: 2020-09-15 #
########################################################################
#                                                                      #
# This program is free software; you can redistribute it and/or modify #
# it under the terms of the GNU General Public License as published by #
# the Free Software Foundation; either version 2, or (at your option)  #
# any later version.                                                   #
#                                                                      #
# This program is distributed in the hope that it will be useful,      #
# but WITHOUT ANY WARRANTY; without even the implied warranty of       #
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        #
# GNU General Public License for more details.                         #
#                                                                      #
# You should have received a copy of the GNU General Public License    #
# along with this program; if not, write to the Free Software          #
# Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.            #
#                                                                      #
########################################################################

# This configure.ac will work with autoconf 2.50 or later:
  AC_PREREQ([2.71])

# Initialize configure.ac for autoconf:
  AC_INIT([phoebe-gui],[1.0],[phoebe-devel@lists.sourceforge.net])

# Create a dedicated header file phoebe_scripter_build_config.h that will
# contain all #define statements that correspond to whatever ./configure
# found:
  AC_CONFIG_HEADERS([src/phoebe_gui_build_config.h])

# Define the release name, date and type:
  AC_DEFINE(
	PHOEBE_GUI_RELEASE_NAME,
	[["PHOEBE GUI 1.0"]],
	[PHOEBE release name])
  AC_DEFINE(
	PHOEBE_GUI_RELEASE_DATE,
	[["2020-09-15"]],
	[PHOEBE release date])

# Initialize the location of the sources:
  AC_CONFIG_SRCDIR([src/phoebe_gui_main.c])

# Initialize the location of the autoconf macros:
  AC_CONFIG_AUX_DIR(autoconfig)

# Initialize configure.ac for automake:
  AM_INIT_AUTOMAKE([-Wall -Werror gnu])
  AM_MAINTAINER_MODE

# Check for system programs:

  # C compiler:
    AC_PROG_CC

    if test -z $CC; then
      echo ""
      echo "       *** PHOEBE configuration failure ***"
      echo ""
      echo "PHOEBE needs an ANSI-compliant C compiler to build."
      echo "Please install it and run the ./configure script again."
      echo ""
      exit
    fi

  # Check for math library:
  AC_CHECK_LIB([m],[cos])

  # Check for pkg-config:
  AC_PATH_PROG(PKG_CONFIG, pkg-config, no)
  if test "$PKG_CONFIG" = "no" ; then
      echo ""
      echo "       *** PHOEBE configuration failure ***"
      echo ""
      echo "The configure script needs pkg-config suite to determine"
      echo "the presence of various graphical libraries. Please install"
      echo "it and rerun ./configure."
      echo ""
      exit
  fi

  # Glib/GTK+/libglade support:
  AM_PATH_GLIB_2_0(2.6.0,glib_check_passed=1,glib_check_passed=0)
  if test $glib_check_passed == 0; then
      echo ""
      echo "       *** PHOEBE configuration failure ***"
      echo ""
      echo "PHOEBE cannot find the graphical library GLib 2.6.0 or higher."
      echo "Please install it and run the ./configure script again."
      echo ""
      exit
  fi

  AM_PATH_GTK_2_0(2.6.0,gtk_check_passed=1,gtk_check_passed=0)
  if test $gtk_check_passed == 0; then
      echo ""
      echo "       *** PHOEBE configuration failure ***"
      echo ""
      echo "PHOEBE cannot find the graphical library GTK+-2.6.0 or higher."
      echo "Please install it and run the ./configure script again."
      echo ""
      exit
  fi

  PKG_CHECK_MODULES(LIBGLADE,libglade-2.0,glade_check_passed=1,glade_check_passed=0)
  if test $glade_check_passed == 0; then
      echo ""
      echo "       *** PHOEBE configuration failure ***"
      echo ""
      echo "PHOEBE cannot find the graphical library libglade-2.0 or higher."
      echo "Please install it and run the ./configure script again."
      echo ""
      exit
  fi

# Check if PHOEBE library is installed:

  AC_CHECK_LIB(phoebe, phoebe_init, , phoebe_missing=1)

  if test x$phoebe_missing == x1; then
    echo ""
    echo "       *** PHOEBE configuration failure ***"
    echo ""
    echo "PHOEBE GUI needs PHOEBE library installed to be built."
    echo "Please install it and rerun ./configure."
    echo ""
    exit
  fi

  # Do we have update-mime-database and update-desktop-database:
  AC_CHECK_PROG(have_update_mime_database, [update-mime-database], [yes])
  AC_CHECK_PROG(have_update_database_database, [update-database-database], [yes])

  # Make program:
    AC_PROG_MAKE_SET

  # Install program:
    AC_PROG_INSTALL

# Optional debugging support:
  debugstate="no"
  AC_ARG_ENABLE(debug,
    [  --enable-debug          Use verbose debugging mode (default=no)],
    [ac_enable_debug=yes], [ac_enable_debug=no])
  if test $ac_enable_debug = "yes"; then
  AC_DEFINE(PHOEBE_DEBUG_SUPPORT, 1, Define if verbose debugging is required:)
  debugstate="yes"
  fi

# Check for C library features:
  AC_CHECK_HEADERS([stdlib.h string.h])

  AC_C_CONST

# Finally, write everything to Makefiles:
  AC_CONFIG_FILES([
                  Makefile
                  glade/Makefile
                  pixmaps/Makefile
                  src/Makefile
                  ])

# Conclude:
  AC_OUTPUT

# Write out the configuration summary:
  echo ""
  echo "PHOEBE GUI configuration complete."
  echo ""
  echo "Configuration summary for $PACKAGE_STRING:"
  echo "-----------------------------------------------------------"
  echo "C compiler used:                  $CC"
  echo "Top-level install directory:      $prefix"
  echo "PHOEBE GUI binary goes to:        $prefix/bin"
  echo "Verbose debugging messages:       $debugstate"
  echo ""
