########################################################################
#                                                                      #
#    Author of Makefile.am: Andrej Prsa <andrej.prsa@fmf.uni-lj.si>    #
#                                                                      #
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

INCLUDES = @GTK_CFLAGS@

bin_PROGRAMS = phoebe

phoebe_SOURCES = \
	main.c                                                              \
	phoebe_allocations.c              phoebe_allocations.h              \
	phoebe_binning.c                  phoebe_binning.h                  \
	phoebe_calculations.c             phoebe_calculations.h             \
	phoebe_chi2.c                     phoebe_chi2.h                     \
	phoebe_configuration.c            phoebe_configuration.h            \
	phoebe_error_handling.c           phoebe_error_handling.h           \
	phoebe_fortran_implementations.c  phoebe_fortran_implementations.h  \
	phoebe_fortran_routines.f         phoebe_global.h                   \
	phoebe_grid.c                     phoebe_grid.h                     \
	phoebe_gui_accessories.c          phoebe_gui_accessories.h          \
	phoebe_gui.c                      phoebe_gui.h                      \
	phoebe_gui_callbacks.c            phoebe_gui_callbacks.h            \
	phoebe_gui_fitting.c              phoebe_gui_fitting.h              \
	phoebe_gui_keyword.c              phoebe_gui_keyword.h              \
	phoebe_gui_ld.c                   phoebe_gui_ld.h                   \
	phoebe_gui_plot.c                 phoebe_gui_plot.h                 \
	phoebe_gui_support.c              phoebe_gui_support.h              \
	phoebe_limb_darkening.c           phoebe_limb_darkening.h           \
	phoebe_phsv_pcsv.c                phoebe_phsv_pcsv.h                \
	phoebe_plot.c                     phoebe_plot.h                     \
	phoebe_scripting.c                phoebe_scripting.h                \
	phoebe_transformations.c          phoebe_transformations.h

if SM_SUPPORT
phoebe_LDADD = -lplotsub -ldevices -lutils @GTK_LIBS@ @FLIBS@
else
phoebe_LDADD = @GTK_LIBS@ @FLIBS@
endif
phoebe_FFLAGS = -ff2c
